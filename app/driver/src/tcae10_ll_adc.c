/**
 *****************************************************************************
 * @brief   adc driver source file.
 *
 * @file    tcae10_ll_adc.c
 * @author  AE/FAE team
 * @date    2024.01.01
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2024 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */

#include "tcae10_ll_adc.h"
#include "system_tcae10.h"
#include "tcae10_ll_cortex.h"
#include "tcae10_ll_flash.h"

#define ADC_ISR_FLAG       (0x1FUL)

#define ADDR_TEMP_TRIM_PARAM            0x00800044UL
#define ADDR_VBAT_TRIM_PARAM            0x00800038UL

const uint16_t vcr_value[ADC_VCR_MAX] = {236, 314, 394, 437, 552, 631, 710, 789};
const uint16_t vref_value[ADC_VREF_MAX] = {2500, 2000, 1500};

static uint32_t adc_isr_flag = 0;
bool adc_isr_enable = false;
static ISR_FUNC_CALLBACK adc_isr_callback = NULL;

typedef struct
{
    uint32_t code1      : 16;
    uint32_t code2      : 16;//only for temp
} trim_value_t;

typedef struct
{
    float tos_value;
    float k_value;
} temp_trim_value_t;

typedef struct
{
    float a;
    float b;
    float c;
} vaon_coef_t;

typedef struct
{
    uint16_t gain;
    int16_t offset;
} adc_ch_trim_t;

trim_value_t vbat_trim_value;
temp_trim_value_t vtemp_temp_value[2];
vaon_coef_t vaon_coef_value;
adc_ch_trim_t vf_ch_trim_value[3];
adc_ch_trim_t aon_ch_trim_value;

/********************************************************
** \brief   ll_adc_clk_config
**
** \param   ll_clk_config_t*    config
**
** \retval  None
*********************************************************/
static void ll_adc_clk_config(ll_clk_config_t *config)
{
    CRG_CONFIG_UNLOCK();

    /*ADC doesn't have an option to select its fclk
    the default and only fclk for ADC is RC48MHz*/
    CRG->ADC_CLKRST_CTRL_F.PCLK_EN_ADC = true;
    CRG->ADC_CLKRST_CTRL_F.FCLK_EN_ADC = true;
    CRG->ADC_CLKRST_CTRL_F.FCLK_DIV_ADC = config->fclk_div;

    CRG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_adc_isr_config
**
** \param   ll_isr_config_t*      config
** \param   AFE_FUNC_CALLBAC      callback
**
** \retval  None
*********************************************************/
static void ll_adc_isr_config(ll_isr_config_t *config, ISR_FUNC_CALLBACK callback)
{
    ADC->IMR |= ADC_ISR_FLAG;
    adc_isr_enable = false;

    if (config->isr_enable)
    {
        adc_isr_flag = config->isr & ADC_ISR_FLAG;

        adc_isr_callback = callback;
    }
    else
    {
        adc_isr_flag = 0;
        adc_isr_callback = NULL;
    }
}

/********************************************************
** \brief   ll_adc_trim_value_load
**
** \param   None
**
** \retval  None
*********************************************************/
static void ll_adc_trim_value_load(void)
{
    TEST->TEST_LOCK = 0x76543210;

    TEST->ADC_TRIM0 = 0x74371F1D;
    TEST->ADC_TRIM1 = 0xFA007C;
    TEST->ADC_TRIM2 = 0x2EF0177;
    TEST->ADC_TRIM3 = 0xB0404F8;
    TEST->ADC_TRIM4 = 0x16010B04;
    TEST->ADC_TRIM5 = 0x108020ff;
    TEST->ADC_TRIM6 = 0x3F402100;
    TEST->ADC_TRIM7 = 0x7900;
    // uint32_t trim_version = REG_TRIM_VERSION();

    // if ((trim_version & 0xFF) == 0x03 && (((trim_version >> 8) & 0x3F) >= 0x01))
    // {
    //     TEST->ADC_TRIM0 = REG_READ32(0x00800038);
    //     TEST->ADC_TRIM1 = REG_READ32(0x0080003C);
    //     TEST->ADC_TRIM2 = REG_READ32(0x00800040);
    //     TEST->ADC_TRIM3 = REG_READ32(0x00800044);
    //     TEST->ADC_TRIM4 = REG_READ32(0x00800048);
    //     TEST->ADC_TRIM5 = REG_READ32(0x0080004C);
    //     TEST->ADC_TRIM6 = REG_READ32(0x00800050);
    //     TEST->ADC_TRIM7 = REG_READ32(0x00800054);
    // }
}

/********************************************************
** \brief   ll_adc_calibration_load
**
** \param   trim_value_t*       vbat_trim
** \param   temp_trim_value_t*  temp_trim
** \param   vaon_coef_t*        vaon_coef
**
** \retval  None
*********************************************************/
static void ll_adc_calibration_load(trim_value_t *vbat_trim, temp_trim_value_t *temp_trim, vaon_coef_t *vaon_coef)
{
    uint32_t trim_value;
    int32_t aon_value;
    trim_value_t *value = (trim_value_t *)&trim_value;
    uint32_t trim_version = REG_TRIM_VERSION();
    /* vbat trim */
    trim_value =  REG_READ32(0x0080005CUL);
    vbat_trim->code1 =  value->code1;
    vbat_trim->code2 = value->code2;

    if (((trim_version & 0xFF) > 0x03) || (((trim_version & 0xFF) == 0x03) && (((trim_version >> 8) & 0x3F) >= 0x01)))
    {

        /* vtemp trim */
        trim_value =  REG_READ32(0x00800078UL);
        temp_trim[0].tos_value  = (value->code1 != 0xFFFF) ? value->code1 : 0x0500;
        temp_trim[0].k_value  = (value->code2 != 0xFFFF) ? value->code2 : 0x0B00;
        temp_trim[0].k_value = temp_trim[0].k_value / 16;

        trim_value =  REG_READ32(0x0080007CUL);
        temp_trim[1].tos_value  = (value->code1 != 0xFFFF) ? value->code1 : 0x0500;
        temp_trim[1].k_value  = (value->code2 != 0xFFFF) ? value->code2 : 0x0B00;
        temp_trim[1].k_value = temp_trim[1].k_value / 16;

        aon_value =  REG_READ32(0x008000B8UL);
        vaon_coef->a =  5.0 * aon_value / 68719476.736 / 4096.0 / 4096.0;
        aon_value =  REG_READ32(0x008000BCUL);
        vaon_coef->b =  5.0 * aon_value / 268435.456 / 4096.0;
        aon_value =  REG_READ32(0x008000C0UL);
        vaon_coef->c =  5.0 * aon_value / 4.096;
    }
    else
    {
        temp_trim[0].tos_value =  temp_trim[0].k_value = 1;
        temp_trim[1].tos_value =  temp_trim[1].k_value = 1;
        vaon_coef->a = vaon_coef->b = vaon_coef->c = 1;
    }
}

static void ll_adc_temp_calibration_load(temp_trim_value_t *temp_trim)
{
    uint32_t trim_value;
    trim_value_t *value = (trim_value_t *)&trim_value;
    uint32_t trim_version = REG_TRIM_VERSION();

    if (((trim_version & 0xFF) > 0x03) || (((trim_version & 0xFF) == 0x03) && (((trim_version >> 8) & 0x3F) >= 0x01)))
    {

        /* vtemp trim */
        trim_value =  REG_READ32(0x00800078UL);
        temp_trim[0].tos_value  = (value->code1 != 0xFFFF) ? value->code1 : 0x0500;
        temp_trim[0].k_value  = (value->code2 != 0xFFFF) ? value->code2 : 0x0B00;
        temp_trim[0].k_value = temp_trim[0].k_value / 16;

        trim_value =  REG_READ32(0x0080007CUL);
        temp_trim[1].tos_value  = (value->code1 != 0xFFFF) ? value->code1 : 0x0500;
        temp_trim[1].k_value  = (value->code2 != 0xFFFF) ? value->code2 : 0x0B00;
        temp_trim[1].k_value = temp_trim[1].k_value / 16;
    }
    else
    {
        temp_trim[0].tos_value =  temp_trim[0].k_value = 1;
        temp_trim[1].tos_value =  temp_trim[1].k_value = 1;
    }
}

/********************************************************
** \brief   ll_adc_vf_calibration_load
**
** \param   adc_ch_trim_t*     vf_ch_trim
** \param   adc_ch_trim_t*     aon_ch_trim
**
** \retval  ll_status_e
*********************************************************/
static ll_status_e ll_adc_vf_calibration_load(adc_ch_trim_t *vf_ch_trim, adc_ch_trim_t *aon_ch_trim)
{
    uint32_t trim_value;

    for (adc_channel_e channel = ADC_CHANNEL_VPN0; channel <= ADC_CHANNEL_VPN2; channel++)
    {
        uint8_t index = channel - ADC_CHANNEL_VPN0;
        trim_value = REG_READ32(0x0080006CUL + (index << 2));
        vf_ch_trim[index].gain = (trim_value & 0x00003FFFUL);
        trim_value = (trim_value >> 16 & 0x00003FFFUL);

        if (trim_value & (1 << 13))
        {
            vf_ch_trim[index].offset = (int16_t)(trim_value | 0xE000);
        }
        else
        {
            vf_ch_trim[index].offset = (int16_t)(trim_value & 0x1FFF);
        }
    }

    trim_value = REG_READ32(0x00800084UL);
    aon_ch_trim->gain = (trim_value & 0x0000FFFFUL);
    trim_value = (trim_value >> 16 & 0x00003FFFUL);

    if ((trim_value & (1 << 13)) != 0)
    {
        aon_ch_trim->offset = (int16_t)(trim_value | 0xE000);
    }
    else
    {
        aon_ch_trim->offset = (int16_t)(trim_value & 0x1FFF);
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_scan_channel_config
**
** \param   adc_scan_channel_e  scan_channel
** \param   adc_scan_config_t*  config
**
** \retval  None
*********************************************************/
static void ll_adc_scan_channel_config(adc_scan_channel_e scan_channel, adc_scan_config_t *config)
{

    switch (scan_channel)
    {
    case ADC_SCAN_CHANNEL_0:
        ADC->CTRL_SCAN01_F.SCAN_CHNL_0 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_1:
        ADC->CTRL_SCAN01_F.SCAN_CHNL_1 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_2:
        ADC->CTRL_SCAN23_F.SCAN_CHNL_2 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_3:
        ADC->CTRL_SCAN23_F.SCAN_CHNL_3 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_4:
        ADC->CTRL_SCAN45_F.SCAN_CHNL_4 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_5:
        ADC->CTRL_SCAN45_F.SCAN_CHNL_5 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_6:
        ADC->CTRL_SCAN67_F.SCAN_CHNL_6 = config->scan_channel_cfg;
        break;

    case ADC_SCAN_CHANNEL_7:
        ADC->CTRL_SCAN67_F.SCAN_CHNL_7 = config->scan_channel_cfg;
        break;

    default:
        break;
    }
}

/********************************************************
** \brief   averge_calculate_func
**
** \param   uint16_t*           data
** \param   uint16_t            length
**
** \retval  uint16_t            averge
*********************************************************/
__attribute__((weak)) uint16_t averge_calculate_utils(uint16_t *data, uint16_t length)
{
    uint16_t avg, min, max;
    uint32_t sum = 0;

    min = UINT16_MAX;
    max = 0;

    for (uint8_t i = 0; i < length; i++)
    {
        min = ((min < data[i]) ? min : data[i]);
        max = ((max > data[i]) ? max : data[i]);
        sum += data[i];
    }

    if (length >= 3)
    {
        avg = (sum - max - min + ((length - 2) >> 1)) / (length - 2);
    }
    else
    {
        avg = (sum + (length >> 1)) / length;
    }

    return avg;
}

/********************************************************
** \brief   ll_adc_deinit
**
** \param   None
**
** \retval  void
*********************************************************/
void ll_adc_deinit(void)
{
    ADC->ICR |= 0x1F;
    ADC->IMR &= ~0x1F;

    adc_isr_enable = false;

    CRG_CONFIG_UNLOCK();
    CRG->ADC_CLKRST_CTRL_F.RST_ADC = 1;
    __NOP();
    __NOP();
    CRG->ADC_CLKRST_CTRL_F.RST_ADC = 0;
    __NOP();
    __NOP();
    CRG_CONFIG_LOCK();

    adc_isr_flag = 0;

    adc_isr_callback = NULL;
}

/********************************************************
** \brief   ll_adc_init
**
** \param   ll_uart_bus_t   bus
** \param   uint32_t        baudrateISR_FUNC_CALLBACK
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_init(adc_config_t *config, ISR_FUNC_CALLBACK callback)
{
    ll_adc_deinit();

    ll_adc_clk_config(&config->clk_cfg);

    ll_adc_trim_value_load();

    ll_adc_vf_calibration_load(vf_ch_trim_value, &aon_ch_trim_value);

    ll_adc_calibration_load(&vbat_trim_value, vtemp_temp_value, &vaon_coef_value);

    ADC->CTRL0_F.TRIG_EN = config->trig_mode;

    ADC->CTRL0_F.FIFO_THRHLD = config->trig_num - 1;
    ADC->CTRL0_F.I_SEL = 1;

    ADC->CTRL0_F.SW_ADC_EN = true;
    ADC->CTRL0_F.AUTO_ADC_EN = false;

    /* adc ctrl1: */
    ADC->CTRL1_F.SW_CONT_MODE = 0; //continuous mode
    ADC->CTRL1_F.SCAN_CHNL_NUM = 0; //scan channel num, N +1
    ADC->CTRL1_F.CHNL_SAMP_NUM =  config->trig_num - 1;

    ADC->CTRL1_F.DIV_EN = 1;

    /* adc ctrl2: 使用默认值*/
    if (DEFAULT_SYSTEM_CLOCK < 48000000UL)
    {
        ADC->CTRL2_F.SAMP_CYCLE = 0x03 >> 1;
        ADC->CTRL2_F.INIT_CYCLE = 0x1E0 >> 1;
    }
    else
    {
        ADC->CTRL2_F.SAMP_CYCLE = 0x0F;
        ADC->CTRL2_F.INIT_CYCLE = 0x320;
    }

    /* ADC fifo clr */
    ll_adc_fifo_clear();

    ll_adc_isr_config(&config->isr_cfg, callback);

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_scan_channel_config
**
** \param   adc_channel_e   channel
** \param   adc_cfg_t*      cfg
** \param   uint8_t         scan_num
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_vf_scan_config(adc_channel_e channel, adc_cfg_t *cfg, uint8_t scan_num)
{
    /* adc ctrl0: */
    ADC->CTRL0_F.FIFO_THRHLD = scan_num - 1;
    /* adc ctrl1: */
    ADC->CTRL1_F.SW_CONT_MODE = 0; //continuous mode
    ADC->CTRL1_F.SCAN_CHNL_NUM = scan_num - 1; //scan channel num, N +1
    ADC->CTRL1_F.CHNL_SAMP_NUM =  0;

    adc_scan_config_t scan_config =
    {
        .scan_config_bit.pga_bypass = cfg->adc_pag_bypass,
        .scan_config_bit.pga_bufn_bypass = cfg->adc_buf_bypass,
        .scan_config_bit.pga_bufp_bypass = cfg->adc_buf_bypass,
        .scan_config_bit.pga_gain = cfg->gain,
    };
    scan_config.scan_config_bit.channel = channel;
    ll_adc_scan_channel_config(ADC_SCAN_CHANNEL_2, &scan_config);
    ll_adc_scan_channel_config(ADC_SCAN_CHANNEL_3, &scan_config);
    ll_adc_scan_channel_config(ADC_SCAN_CHANNEL_4, &scan_config);
    ll_adc_scan_channel_config(ADC_SCAN_CHANNEL_5, &scan_config);

    scan_config.scan_config_bit.channel = ADC_CHANNEL_TEMP1;
    scan_config.scan_config_bit.pga_bypass = false;
    scan_config.scan_config_bit.pga_bufn_bypass = false;
    scan_config.scan_config_bit.pga_bufp_bypass = false;
    scan_config.scan_config_bit.pga_gain = ADC_GAIN_X16;
    ll_adc_scan_channel_config(ADC_SCAN_CHANNEL_0, &scan_config);

    scan_config.scan_config_bit.channel = ADC_CHANNEL_TAO_TEST;
    scan_config.scan_config_bit.pga_bypass = true;
    scan_config.scan_config_bit.pga_bufn_bypass = true;
    scan_config.scan_config_bit.pga_bufp_bypass = false;
    scan_config.scan_config_bit.pga_gain = ADC_GAIN_X1;
    ll_adc_scan_channel_config(ADC_SCAN_CHANNEL_1, &scan_config);

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_gain_config
**
** \param   adc_channel_e   channel
** \param   adc_cfg_t*      cfg
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_gain_config(adc_channel_e channel, adc_cfg_t *cfg)
{
    if (channel > ADC_CHANNEL_MAX)
    {
        return LL_PARAM_INVALID;
    }

    ADC->CTRL0_F.VCR_EN = cfg->vcr_enable;

    if (cfg->vcr_enable)
    {
        ADC->CTRL0_F.VCR_SEL = cfg->vcr;
    }

    ADC->CTRL0_F.VCM_SEL = cfg->vcm;
    ADC->CTRL1_F.PGA_GAIN_SEL = (cfg->adc_pag_en && !cfg->adc_pag_bypass) ? cfg->gain : 0;
    ADC->CTRL1_F.VREF_SEL = cfg->vref;

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_isr_enable
**
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_isr_enable(bool enable)
{
    adc_isr_enable = enable;

    ADC->ICR |= ADC_ISR_FLAG;


    if (enable)
    {
        NVIC_ClearPendingIRQ(ADC_IRQn);
        ADC->IMR &= ~adc_isr_flag;
        NVIC_EnableIRQ(ADC_IRQn);
    }
    else
    {
        ADC->IMR |= adc_isr_flag;
        // NVIC_DisableIRQ(ADC_IRQn);
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_channel_offset_load
**
** \param   adc_channel_e       channel
**
** \retval  ll_status_e
*********************************************************/
static void ll_adc_channel_offset_load(adc_channel_e channel)
{
    uint32_t trim_version = REG_TRIM_VERSION();

    ASYSCFG_CONFIG_UNLOCK();

    /* change offset & gain */
    if (((trim_version & 0xFF) > 0x03) || (trim_version & 0xFF) == 0x03 && (((trim_version >> 8) & 0x3F) >= 0x01))
    {
        switch (channel)
        {
        case ADC_CHANNEL_VBAT:
            if (((trim_version & 0xFF) > 0x03) || (trim_version & 0xFF) == 0x03 && (((trim_version >> 8) & 0x3F) >= 0x02))
            {
                ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x0080005c);
                ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x0080005c) >> 16;
            }
            else
            {
                ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = 0x1000;
                ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = 0;
            }

            break;

        case ADC_CHANNEL_VC0:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800060);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800060) >> 16;
            break;

        case ADC_CHANNEL_VC1:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800064);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800064) >> 16;
            break;

        case ADC_CHANNEL_VC2:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800068);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800068) >> 16;
            break;

        case ADC_CHANNEL_VPN0:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x0080006c);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x0080006c) >> 16;
            break;

        case ADC_CHANNEL_VPN1:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800070);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800070) >> 16;
            break;

        case ADC_CHANNEL_VPN2:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800074);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800074) >> 16;
            break;

        default:
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800058);
            ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800058) >> 16;
            break;
        }
    }
    else
    {
        ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = 0x1000;
        ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = 0;
    }

    ASYSCFG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_adc_select_channel
**
** \param   adc_channel_e       channel
** \param   adc_cfg_t*          cfg
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_select_channel(adc_channel_e channel, adc_cfg_t *cfg)
{
    if (channel >= ADC_CHANNEL_MAX || cfg->vref >= ADC_VREF_MAX)
    {
        return LL_PARAM_INVALID;
    }

    while (ADC->CHNL_STATUS_F.ADC_BUSY);

    ll_adc_gain_config(channel, cfg);

    if (channel >= ADC_CHANNEL_VC0 && channel <= ADC_CHANNEL_VPN2)
    {
        TEST_CONFIG_UNLOCK();

        TEST->TEST_ANA_CTRL_F.TESTMUX_TAO_SEL = 2;
        TEST->TEST_ANA_CTRL_F.TEST_AON = 1;
        TEST->TEST_ANA_CTRL_F.TESTMUX_TO_ADC_EN = 1;
        TEST->TEST_ANA_CTRL_F.TESTMUX_SEL_BUF = 1;
        TEST->TEST_ANA_CTRL_F.TESTMUX_BUF_EN = 1;
        TEST->TEST_ANA_CTRL_F.TESTMUX_TAO_EN = 1;

        TEST_CONFIG_LOCK();

        ASYSCFG_CONFIG_UNLOCK();

        ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = 0x1000;
        ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = 0;

        ASYSCFG_CONFIG_LOCK();

        ADC->CTRL0_F.VREFBUF_EN = true;
        ADC->CTRL1_F.BUFP_EN = cfg->adc_buf_en;
        ADC->CTRL1_F.BUFN_EN = cfg->adc_buf_en;
        ll_adc_vf_scan_config(channel, cfg, 6);
    }
    else
    {
        ll_adc_channel_offset_load(channel);

        ADC->CTRL0_F.VREFBUF_EN = true;

        ADC->CTRL1_F.BUFP_EN = cfg->adc_buf_en;
        ADC->CTRL1_F.BUFN_EN = cfg->adc_buf_en;

        ADC->CTRL1_F.BUFP_BP = cfg->adc_buf_bypass;
        ADC->CTRL1_F.BUFN_BP = cfg->adc_buf_bypass;

        ADC->CTRL1_F.PGA_EN = cfg->adc_pag_en;
        ADC->CTRL1_F.PGA_BP = cfg->adc_pag_bypass;

        /* adc ctrl0: */
        ADC->CTRL0_F.FIFO_THRHLD = 3;
        /* adc ctrl1: */
        ADC->CTRL1_F.SW_CONT_MODE = 0; //continuous mode
        ADC->CTRL1_F.SCAN_CHNL_NUM = 0; //scan channel num, N +1
        ADC->CTRL1_F.CHNL_SAMP_NUM =  3;

        ADC->CTRL1_F.IN_SEL = channel;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_fifo_length_get
**
** \param   None
**
** \retval  uint8_t
*********************************************************/
uint8_t ll_adc_fifo_length_get(void)
{
    return (ADC->FIFO_STATE & 0x0F);
}

/********************************************************
** \brief   ll_adc_fifo_get
**
** \param   None
**
** \retval  uint32_t
*********************************************************/
uint16_t ll_adc_fifo_get(uint16_t *buffer, uint16_t length)
{
    uint8_t len = ll_adc_fifo_length_get();

    if (len >= length)
    {
        for (uint8_t i = 0; i < len - length; i++)
        {
            buffer[0] = ADC->FIFO_DATA;
        }
    }

    len = length > len ? len : length;

    for (uint8_t i = 0; i < len; i++)
    {
        buffer[i] = ADC->FIFO_DATA & 0x3FFF;
    }

    return len;
}

/********************************************************
** \brief   ll_adc_fifo_clear
**
** \param   None
**
** \retval  uint32_t
*********************************************************/
uint16_t ll_adc_fifo_clear(void)
{
    uint32_t reg_val = 0;
    (void)(&reg_val);

    uint8_t len = ll_adc_fifo_length_get();

    for (uint8_t i = 0; i < len; i++)
    {
        reg_val = ADC->FIFO_DATA;
    }

    return len;
}

/********************************************************
** \brief   ll_adc_softwart_start
**
** \param   bool        enable
**
** \retval  void
*********************************************************/
void ll_adc_softwart_start(bool enable)
{
    if (enable)
    {
        ADC->CTRL0_F.SW_START = true;
    }
    else
    {
        ADC->CTRL0_F.SW_START = false;
    }
}

/********************************************************
** \brief   ll_adc_gain1_value_get
**
** \param   adc_gain1_e     gain
** \param   uint8_t*        value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_gain_value_get(adc_gain_e gain, uint8_t *value)
{
    if (gain >= ADC_GAIN_MAX)
    {
        return LL_PARAM_INVALID;
    }

    *value = gain + 1;
    return LL_OK;
}

/********************************************************
** \brief   ll_adc_vcr_value_get
**
** \param   adc_vcr_e       vcr
** \param   uint16_t*        value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_vcr_value_get(adc_vcr_e vcr, uint16_t *value)
{

    if (vcr >= ADC_VCR_MAX)
    {
        return LL_PARAM_INVALID;
    }

    *value = vcr_value[vcr];
    return LL_OK;
}

/********************************************************
** \brief   ll_adc_vref_value_get
**
** \param   adc_vcr_e       vcr
** \param   uint8_t*        value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_vref_value_get(adc_vref_e vref, uint16_t *value)
{

    if (vref >= ADC_VREF_MAX)
    {
        return LL_PARAM_INVALID;
    }

    *value = vref_value[vref];
    return LL_OK;
}

/********************************************************
** \brief   ll_adc_temp_calculate_func
**
** \param   temp_channel_e  channel
** \param   int16_t         code
** \param   adc_cfg_t*      cfg
** \param   uint16_t*       value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_temp_calculate_func(temp_channel_e channel, int16_t code, adc_cfg_t *cfg,  uint16_t *value)
{
    if (NULL == cfg || channel >= TEMP_CHANNEL_MAX)
    {
        return LL_PARAM_INVALID;
    }

    *value = (code * 2.5 - vtemp_temp_value[channel].tos_value) / vtemp_temp_value[channel].k_value - 273.15;

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_temp_calculate
**
** \param   temp_channel_e  channel
** \param   int16_t         code
**
** \retval  int value
*********************************************************/
int ll_adc_temp_calculate(temp_channel_e channel, int16_t code)
{
    static uint8_t load_trim = 0;

    if (!load_trim)
    {
        ll_adc_temp_calibration_load(vtemp_temp_value);
        load_trim = 1;
    }

    return (code * 2.5 - vtemp_temp_value[channel].tos_value) / vtemp_temp_value[channel].k_value - 273.15;
}

/********************************************************
** \brief   ll_adc_vbat_calculate_func
**
** \param   adc_vcr_e       vcr
** \param   uint16_t*       value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_vbat_calculate_func(int16_t code, uint16_t *value)
{
    return LL_OK;
}

/********************************************************
** \brief   ll_adc_vcr_value_get
**
** \param   adc_vcr_e       vcr
** \param   adc_cfg_t*      cfg
** \param   uint16_t*       value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_volt_calculate_func(int16_t code, adc_cfg_t *cfg, uint16_t *value)
{

    if (NULL == cfg)
    {
        return LL_PARAM_INVALID;
    }

    int16_t code_val = code;
    uint16_t vref, vcr;
    uint8_t gain;

    if (cfg->adc_pag_en && !cfg->adc_pag_bypass)
    {
        ll_adc_gain_value_get(cfg->gain, &gain);
    }
    else
    {
        gain = 1;
    }

    if (cfg->vcr_enable)
    {
        ll_adc_vcr_value_get(cfg->vcr, &vcr);
    }
    else
    {
        vcr = 0;
    }

    ll_adc_vref_value_get(cfg->vref, &vref);

    if (code & (1 << 13))
    {
        code_val = (int16_t)(code | 0xE000);
    }
    else
    {
        code_val = (int16_t)(code & 0x1FFF);
    }

    *value = cfg->ratio * ((code_val * vref) / (gain * 8192.f) + vcr);

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_vf_convert_func
**
** \param   uint16_t*     buffer
** \param   uint16_t*     value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_vf_calculate_func(adc_channel_e channel, uint16_t *buffer, uint16_t *value)
{
    uint8_t index;
    int32_t aon_t_code;
    int32_t aon_v_code;
    int32_t led_v_code;
    float vaon;

    led_v_code = buffer[0];
    aon_t_code = buffer[1];
    aon_v_code = buffer[2];
    index = channel - ADC_CHANNEL_VPN0;

    aon_v_code = (aon_v_code - aon_ch_trim_value.offset) * aon_ch_trim_value.gain;
    aon_t_code = (aon_t_code - aon_ch_trim_value.offset) * aon_ch_trim_value.gain;
    led_v_code = (led_v_code - vf_ch_trim_value[index].offset) * vf_ch_trim_value[index].gain;

    vaon = vaon_coef_value.a * aon_t_code * aon_t_code + vaon_coef_value.b * aon_t_code + vaon_coef_value.c;
    *value = 0.5 + vaon * led_v_code  / aon_v_code;

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_channnel_start
**
** \param   adc_channel_e       channel
** \param   adc_cfg_t*          cfg
** \param   uint16_t*           buffer
** \param   uint8_t             trig_num
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_channnel_start(adc_channel_e channel, adc_cfg_t *cfg, uint16_t *buffer, uint8_t trig_num)
{
    ll_status_e st = LL_OK;
    uint16_t timeout = 50;

    ll_adc_select_channel(channel, cfg);

    ll_adc_isr_enable(false);

    ll_adc_softwart_start(true);

    while (trig_num != ll_adc_fifo_length_get())
    {
        if (timeout-- <= 0)
        {
            st = LL_ERROR;
            break;
        }

        for (uint8_t i = 0; i < 100; i++) //10us
        {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }

    if (trig_num != ll_adc_fifo_get(buffer, trig_num))
    {
        st = LL_ERROR;
    }

    return st;
}

/********************************************************
** \brief   ll_adc_tsensor_enable
**
** \param   bool          enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_tsensor_enable(bool enable)
{
    if (enable)
    {
        ADC->CTRL1_F.INT0_SNS_EN = true;
        ADC->CTRL1_F.INT1_SNS_EN = true;
    }
    else
    {
        ADC->CTRL1_F.INT0_SNS_EN = false;
        ADC->CTRL1_F.INT1_SNS_EN = false;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_lin_aa_enable
**
** \param   lin_aa_type_e   type
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_lin_aa_enable(lin_aa_type_e type, bool enable)
{
    ll_adc_deinit();
    ll_adc_trim_value_load();

    ASYSCFG_CONFIG_UNLOCK();

    ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_CAL = REG_READ32(0x00800058);
    ASYSCFG->ADC_CAL_CTRL_F.ADC_OUT_OFFSET = REG_READ32(0x00800058) >> 16;

    ASYSCFG_CONFIG_LOCK();

    PWM->LED_CTRL_F.LED_LDO5V_EN = 1;
    /* adc ctrl0: */
    ADC->CTRL0_F.VREFBUF_EN = 1;
    ADC->CTRL0_F.TRIG_EN = TRIG_LIN;
    ADC->CTRL0_F.SW_ADC_EN = false;
    ADC->CTRL0_F.AUTO_ADC_EN = true;
    ADC->CTRL0_F.FIFO_THRHLD = 0;

    /* adc ctrl1: */
    ADC->CTRL1_F.IN_SEL = ADC_CHANNEL_LIN;
    ADC->CTRL1_F.SW_CONT_MODE = false;
    ADC->CTRL1_F.CHNL_SAMP_NUM = 0;
    ADC->CTRL1_F.SCAN_CHNL_NUM = 0;

    if (LIN_AA_STYPE_STEPS_2 == type)
    {
        ADC->CTRL2_F.INIT_CYCLE = 0x3EF >> 1;
    }
    else
    {
        ADC->CTRL2_F.INIT_CYCLE = 0xF0 >> 1;
    }

    /* path setting */
    ADC->CTRL1_F.BUFN_BP = true;
    ADC->CTRL1_F.BUFP_BP = true;
    ADC->CTRL1_F.BUFN_EN = false;
    ADC->CTRL1_F.BUFP_EN = false;
    ADC->CTRL1_F.PGA_BP = true;
    ADC->CTRL1_F.PGA_EN = false;

    ADC->CTRL1_F.PGA_GAIN_SEL = ADC_GAIN_X1;
    ADC->CTRL1_F.DIV_EN = false;

    /* ADC fifo clr */
    ll_adc_fifo_clear();

    return LL_OK;
}

/********************************************************
** \brief   ll_bias_control_enable
**
** \param   bool          enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_bias_control_enable(bool enable)
{

    return LL_OK;
}

/********************************************************
** \brief   ADC_IRQHandler
**
** \param   uint32_t        isr0
** \param   uint32_t        isr1
**
** \retval  None
*********************************************************/
void ADC_IRQHandler(void)
{
    uint32_t isr = ADC->ISR & ADC_ISR_FLAG;

    if (isr)
    {
        if (NULL != adc_isr_callback)
        {
            adc_isr_callback(isr);
        }

        ADC->ICR |= isr;
    }
}
