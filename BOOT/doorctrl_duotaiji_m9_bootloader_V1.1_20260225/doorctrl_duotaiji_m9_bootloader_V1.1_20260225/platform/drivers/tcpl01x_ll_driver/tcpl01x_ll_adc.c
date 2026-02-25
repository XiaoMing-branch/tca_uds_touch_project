/**
 *****************************************************************************
 * @brief       adc driver source file.
 *
 * @file        tcpl01x_ll_adc.c
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

#include "tcpl01x_ll_adc.h"
#include "system_tcpl01x.h"
#include "tcpl01x_ll_cortex.h"
#include "tcpl01x_ll_flash.h"

#define ADC_ISR0_FLAG       (0x20000000UL)
#define ADC_ISR1_FLAG       (0xF0UL)

#define ADDR_TEMP_TRIM_PARAM        0x00800684
#define ADDR_VBAT_TRIM_PARAM        0x00800694

const uint8_t gain1_value[ADC_GAIN1_MAX] = {2, 5, 7, 10, 12, 15, 17, 20};
const uint16_t vcr_value[ADC_VCR_MAX] = {365, 415, 466, 516, 567, 617, 668, 719, 769, 820, 871, 921, 971, 1022, 1073, 1123};
const uint16_t vref_value[ADC_VREF_MAX] = {2035, 1528, 769};

static uint32_t adc_isr0_flag, adc_isr1_flag = 0;
bool adc_isr_enable = false;
static ISR_FUNC_CALLBACK adc_isr_callback = NULL;
static ISR_FUNC_CALLBACK otp_isr_callback = NULL;

typedef struct
{
    uint32_t code   : 16;
    uint32_t value  : 16;//only for temp
} trim_value_t;

trim_value_t vbat_trim_value;
trim_value_t vtemp_temp_value;

/********************************************************
** \brief   ll_adc_clk_config
**
** \param   ll_clk_config_t*    config
**
** \retval  None
*********************************************************/
static void ll_adc_clk_config(ll_clk_config_t *config)
{
    uint32_t reg_val = 0;
    AFE_CLOCK_CONFIG_UNLOCK();
    //clk rtst
    afe_bit_set(&AFE_CRG->ADC_CLKRST_CTRL, AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_SHIFT);
    afe_bit_clear(&AFE_CRG->ADC_CLKRST_CTRL, AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_SHIFT);
    //fclk div config
    uint8_t div = !config->fclk_div ? 1 : config->fclk_div;
    reg_val = AFE_CRG_ADC_CLKRST_CTRL_FCLK_EN_ADC_SET(1) | AFE_CRG_ADC_CLKRST_CTRL_FCLK_DIV_ADC_SET(div);
    afe_reg_write(&AFE_CRG->ADC_CLKRST_CTRL, reg_val);
    AFE_CLOCK_CONFIG_LOCK();
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
    if (config->isr_enable)
    {

        adc_isr0_flag = config->isr1 & ADC_ISR0_FLAG; /* int0 use backup flag*/
        adc_isr1_flag = config->isr & ADC_ISR1_FLAG;

        adc_isr_callback = callback;
    }
    else
    {
        adc_isr0_flag = 0;
        adc_isr1_flag = 0;
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
    uint32_t reg_val = 0;
    volatile uint32_t *preg = &ADC->CTRL_CAL_1;
    volatile uint32_t *nvr_addr = (volatile uint32_t *)(0x00800634);

    union
    {
        uint32_t trim_value;
        struct
        {
            uint32_t adc_out_cal     : 12 ; // 11 : 0
            uint32_t reserved1       : 4  ; // 15 : 12
            uint32_t adc_out_offset  : 11 ; // 26 : 16
            uint32_t reserved0       : 5  ; // 31 : 27
        } bits;
    } adc_trim_ab;

    union
    {
        uint32_t status;
        struct
        {
            uint32_t reserved        : 7  ; // 6 : 0
            uint32_t adc_ch_trim     : 1  ; // 7
            uint32_t reserved1       : 1  ; // 8
            uint32_t adc_trim        : 1  ; // 9
            uint32_t reserved2         : 22 ; // 31 : 10
        } bits;
    } adc_trim_status;

    FLASH_UNLOCK_CONFIG();
    FLASH_UNLOCK_NVR_ACCESS();

    adc_trim_status.status = (uint16_t)(*(volatile uint32_t *)(0x00800604));

    if (adc_trim_status.bits.adc_ch_trim == 0)
    {
        for (uint8_t i = 0; i < 7; i++)
        {
            adc_trim_ab.trim_value = *(nvr_addr++);
            //            adc_trim_ab.bits.adc_out_offset <<= 1;
            afe_reg_write(preg++, adc_trim_ab.trim_value);
        }

        preg = &ADC->CTRL_CAL_9;

        for (uint8_t i = 0; i < 3; i++)
        {
            reg_val = *(nvr_addr++);
            afe_reg_write(preg++, reg_val);
        }
    }

    if (adc_trim_status.bits.adc_trim == 0)
    {
        preg = &ADC->TRIM_ADSAR_VALUE0;
        nvr_addr = (volatile uint32_t *)(0x00800660);

        for (uint8_t i = 0; i < 9; i++)
        {
            reg_val = *(nvr_addr++);
            afe_reg_write(preg++, reg_val);
        }
    }

    FLASH_LOCK_NVR_ACCESS();
    FLASH_LOCK_CONFIG();

}

/********************************************************
** \brief   ll_adc_calibration_load
**
** \param   uint16_t*       vbat_trim
** \param   uint16_t*       temp_trim
**
** \retval  None
*********************************************************/
static void ll_adc_calibration_load(trim_value_t *vbat_trim, trim_value_t *temp_trim)
{

    uint32_t nvr_read_val;

    ll_flash_read(FLASH_TYPE_NVR, ADDR_VBAT_TRIM_PARAM, (uint8_t *)&nvr_read_val, sizeof(uint32_t));

    vbat_trim->code = (0xFFFFFFFF == nvr_read_val) ? 320 : (nvr_read_val & 0xFFFF);

    ll_flash_read(FLASH_TYPE_NVR, ADDR_TEMP_TRIM_PARAM, (uint8_t *)&nvr_read_val, sizeof(trim_value_t));

    if (0xFFFFFFFF != nvr_read_val)
    {
        temp_trim->code = nvr_read_val & 0xFFFF;
        temp_trim->value = (nvr_read_val >> 16) & 0xFFFF;
    }
    else
    {
        temp_trim->code = 0X0244;
        temp_trim->value = 0X0BB8;
    }
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
    afe_syscfg_int_flag_clear(ADC_ISR0_FLAG, ADC_ISR1_FLAG);
    afe_syscfg_int_disable(ADC_ISR0_FLAG, ADC_ISR1_FLAG); //disable isr_falg
    adc_isr_enable = false;

    afe_bit_set(&AFE_CRG->ADC_CLKRST_CTRL, AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_SHIFT);
    afe_bit_clear(&AFE_CRG->ADC_CLKRST_CTRL, AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_SHIFT);

    afe_reg_write(&ADC->CTRL0, 0x04);
    afe_reg_write(&ADC->CTRL1, 0x0F);
    afe_reg_write(&ADC->CTRL2, 0x85C448EF);
    afe_reg_write(&ADC->CTRL3, 0x00);
    afe_reg_write(&ADC->CTRL4, 0x00);
    afe_reg_write(&ADC->CTRL_GAIN_0, 0x00080012);
    afe_reg_write(&ADC->CTRL_GAIN_1, 0x0C000C00);
    afe_reg_write(&ADC->CTRL_GAIN_2, 0x02ED0C00);
    afe_reg_write(&ADC->CTRL_GAIN_3, 0x03FE02F5);
    afe_reg_write(&ADC->CTRL_ANA, 0X00);

    adc_isr0_flag = 0;
    adc_isr1_flag = 0;
    adc_isr_callback = NULL;
}

/********************************************************
** \brief   ll_adc_init
**
** \param   ll_uart_bus_t   bus
** \param   uint32_t        baudrate
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_init(adc_config_t *config, ISR_FUNC_CALLBACK callback)
{
    uint32_t reg_val = 0;

    ll_adc_deinit();

    ll_adc_clk_config(&config->clk_cfg);

    ll_adc_trim_value_load();

    ll_adc_calibration_load(&vbat_trim_value, &vtemp_temp_value);

    //reg_val |= ADC_CTRL0_TRIG_EN_SET(config->trig_mode);

    /* adc ctrl0: */
    reg_val |= ADC_CTRL0_AUTO_ADC_EN_SET(1) | ADC_CTRL0_FIFO_THRHLD_SET(config->trig_num - 1) | ADC_CTRL0_FIFO_FORMAT_SET(1);
    afe_reg_write(&ADC->CTRL0, reg_val);
    //

    /* adc ctrl1: */
    reg_val = 0x0F | ADC_CTRL1_CHNL_SAMP_NUM_SET(2) | ADC_CTRL1_CHNL_AVG_EN_SET(1) |
              ADC_CTRL1_TRIG_NUM_SET(config->trig_num - 1);
    afe_reg_write(&ADC->CTRL1, reg_val);

    /* adc ctrl2: 使用默认值*/
    reg_val = ADC_CTRL2_INIT_CYCLE_SET(0xEF) | ADC_CTRL2_CHNL_INIT_CYCLE_SET(0x12) | ADC_CTRL2_SAMP_DLY_CYCLE_SET(0x01) |
              ADC_CTRL2_SAMP_CYCLE_SET(0x1f) | ADC_CTRL2_SAMP_PRE_CYCLE_SET(4);

    afe_reg_write(&ADC->CTRL2, reg_val);

    /* ADC fifo clr */
    ll_adc_fifo_clear();

    ll_adc_isr_config(&config->isr_cfg, callback);

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_vref_config
**
** \param   adc_vref_e      vref
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_vref_config(adc_vref_e vref)
{
    if (vref > ADC_VREF_MAX)
    {
        return LL_PARAM_INVALID;
    }

    afe_reg_write(&ADC->CTRL_ANA, (uint32_t)vref);
    return LL_OK;
}

/********************************************************
** \brief   ll_adc_gain_config
**
** \param   adc_channel_e   channel
** \param   adc_pga_cfg_t*  config
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_gain_config(adc_channel_e channel, adc_cfg_t *config)
{
    uint32_t reg_val;

    switch (channel)
    {
        case ADC_CHANNEL_TEMP:
            afe_reg_read(&ADC->CTRL_GAIN_0, &reg_val);
            reg_val &= 0xffff0000;
            reg_val |= ADC_CTRL_GAIN_0_GAIN1_SEL_0_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_0_GAIN2_SEL_0_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_0_VCR_SEL_0_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_0_VCA_SEL_0_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_0_OP_SEL_0_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_0, reg_val);
            break;

        case ADC_CHANNEL_VBAT:
            afe_reg_read(&ADC->CTRL_GAIN_0, &reg_val);
            reg_val &= 0x0000ffff;
            reg_val |= ADC_CTRL_GAIN_0_GAIN1_SEL_1_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_0_GAIN2_SEL_1_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_0_VCR_SEL_1_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_0_VCA_SEL_1_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_0_OP_SEL_1_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_0, reg_val);
            break;

        case ADC_CHANNEL_VC0:
            afe_reg_read(&ADC->CTRL_GAIN_1, &reg_val);
            reg_val &= 0xffff0000;
            reg_val |= ADC_CTRL_GAIN_1_GAIN1_SEL_2_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_1_GAIN2_SEL_2_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_1_VCR_SEL_2_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_1_VCA_SEL_2_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_1_OP_SEL_2_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_1, reg_val);
            break;

        case ADC_CHANNEL_VC1:
            afe_reg_read(&ADC->CTRL_GAIN_1, &reg_val);
            reg_val &= 0x0000ffff;
            reg_val |= ADC_CTRL_GAIN_1_GAIN1_SEL_3_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_1_GAIN2_SEL_3_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_1_VCR_SEL_3_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_1_VCA_SEL_3_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_1_OP_SEL_3_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_1, reg_val);
            break;

        case ADC_CHANNEL_VC2:
            afe_reg_read(&ADC->CTRL_GAIN_2, &reg_val);
            reg_val &= 0xffff0000;
            reg_val |= ADC_CTRL_GAIN_2_GAIN1_SEL_4_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_2_GAIN2_SEL_4_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_2_VCR_SEL_4_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_2_VCA_SEL_4_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_2_OP_SEL_4_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_2, reg_val);
            break;

        case ADC_CHANNEL_VPN0:
            afe_reg_read(&ADC->CTRL_GAIN_2, &reg_val);
            reg_val &= 0x0000ffff;
            reg_val |= ADC_CTRL_GAIN_2_GAIN1_SEL_5_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_2_GAIN2_SEL_5_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_2_VCR_SEL_5_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_2_VCA_SEL_5_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_2_OP_SEL_5_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_2, reg_val);
            break;

        case ADC_CHANNEL_VPN1:
            afe_reg_read(&ADC->CTRL_GAIN_3, &reg_val);
            reg_val &= 0xffff0000;
            reg_val |= ADC_CTRL_GAIN_3_GAIN1_SEL_6_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_3_GAIN2_SEL_6_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_3_VCR_SEL_6_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_3_VCA_SEL_6_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_3_OP_SEL_6_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_3, reg_val);
            break;

        case ADC_CHANNEL_VPN2:
            afe_reg_read(&ADC->CTRL_GAIN_3, &reg_val);
            reg_val &= 0x0000ffff;
            reg_val |= ADC_CTRL_GAIN_3_GAIN1_SEL_7_SET(config->gain1);
            reg_val |= ADC_CTRL_GAIN_3_GAIN2_SEL_7_SET(config->gain2);
            reg_val |= ADC_CTRL_GAIN_3_VCR_SEL_7_SET(config->vcr);
            reg_val |= ADC_CTRL_GAIN_3_VCA_SEL_7_SET(config->vca);
            reg_val |= ADC_CTRL_GAIN_3_OP_SEL_7_SET(config->op_sel);
            afe_reg_write(&ADC->CTRL_GAIN_3, reg_val);
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_isr_enable
**
** \param   ll_sci_bus_e    bus
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_isr_enable(bool enable)
{
    afe_syscfg_int_flag_clear(ADC_ISR0_FLAG, ADC_ISR1_FLAG);

    if (enable)
    {
        afe_syscfg_int_enable(adc_isr0_flag,  adc_isr1_flag); //enable isr_falg
    }
    else
    {
        afe_syscfg_int_disable(ADC_ISR0_FLAG,  ADC_ISR1_FLAG); //enable isr_falg
    }

    adc_isr_enable = enable;

    return LL_OK;

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

    uint32_t reg_val = 0;

    afe_reg_write(&ADC->CTRL_ANA, (uint32_t)cfg->vref);

    afe_reg_read(&ADC->CTRL1, &reg_val);
    reg_val &= ADC_CTRL1_ADC_IN_SEL_CLR;
    reg_val |= ADC_CTRL1_ADC_IN_SEL_SET(channel);
    afe_reg_write(&ADC->CTRL1, reg_val);

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
    uint32_t reg_val = 0;

    afe_reg_read(&ADC->FIFO_STATE, &reg_val);

    return (reg_val & 0x0F);
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
    uint8_t status = 0;
    (void)(&status);
    uint32_t reg_val = 0;
    uint8_t len = ll_adc_fifo_length_get();

    if (len >= length)
    {
        for (uint8_t i = 0; i < len - length; i++)
        {
            afe_reg_read(&ADC->FIFO_DATA, &reg_val);
        }

    }

    len = length > len ? len : length;

    for (uint8_t i = 0; i < len; i++)
    {
        afe_reg_read(&ADC->FIFO_DATA, &reg_val);

        buffer[i] = reg_val & 0x7FF;

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

    uint8_t len = ll_adc_fifo_length_get();

    for (uint8_t i = 0; i < len; i++)
    {
        afe_reg_read(&ADC->FIFO_DATA, &reg_val);
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
    uint32_t reg_val = 0;

    afe_reg_read(&ADC->CTRL0, &reg_val);

    reg_val &= ADC_CTRL0_SW_START_CLR;
    afe_reg_write(&ADC->CTRL0, reg_val);

    if (enable)
    {
        reg_val |= ADC_CTRL0_SW_START_SET(1);
        afe_reg_write(&ADC->CTRL0, reg_val);
    }
}

/********************************************************
** \brief   ll_adc_it_start
**
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_it_start(bool enable)
{
    ll_adc_fifo_clear();
    ll_adc_isr_enable(true);

    ll_adc_softwart_start(true);

    return LL_OK;
}


/********************************************************
** \brief   ll_adc_gain1_value_get
**
** \param   adc_gain1_e     gain
** \param   uint8_t*        value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_gain1_value_get(adc_gain1_e gain, uint8_t *value)
{
    if (gain >= ADC_GAIN1_MAX)
    {
        return LL_PARAM_INVALID;
    }

    *value = gain1_value[gain];
    return LL_OK;
}

/********************************************************
** \brief   ll_adc_gain2_value_get
**
** \param   adc_gain2_e     gain
** \param   uint8_t*        value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_gain2_value_get(adc_gain2_e gain, uint8_t *value)
{
    if (gain >= ADC_GAIN2_MAX)
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
** \brief   ll_adc_crtl_config
**
** \param   uint32_t*       value
** \param   bool            is_write
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_crtl_config(uint32_t *value, bool is_write)
{
    if (!is_write)
    {
        afe_reg_read(&ADC->CTRL0, &value[0]);
        afe_reg_read(&ADC->CTRL1, &value[1]);
        afe_reg_read(&ADC->CTRL2, &value[2]);
    }
    else
    {
        afe_reg_write(&ADC->CTRL0, value[0]);
        afe_reg_write(&ADC->CTRL1, value[1]);
        afe_reg_write(&ADC->CTRL2, value[2]);

        /* ADC fifo clr */
        ll_adc_fifo_clear();

    }

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_temp_calculate_func
**
** \param   adc_vcr_e       vcr
** \param   uint16_t*       value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_adc_temp_calculate_func(int16_t code, adc_cfg_t *cfg,  uint16_t *value)
{
#define FAMILY_K  5.41

    if (NULL == cfg)
    {
        return LL_PARAM_INVALID;
    }

    int16_t code_val = code;
    uint16_t vref, vcr;
    uint8_t gain1, gain2;
    float v_temp, v_temp_trim;

    ll_adc_gain1_value_get(cfg->gain1, &gain1);
    ll_adc_gain2_value_get(cfg->gain2, &gain2);

    ll_adc_vref_value_get(cfg->vref, &vref);
    ll_adc_vcr_value_get(cfg->vcr, &vcr);

    v_temp = (code_val * vref) / (gain1 * 1024.f);
    v_temp_trim = (vtemp_temp_value.code * vref) / (gain1 * 1024.f);

    *value = FAMILY_K * (v_temp - v_temp_trim) + (vtemp_temp_value.value  & 0xFFFF) / 100; //NVR中存储的环境温度值放大了100倍;
    return LL_OK;
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

    int16_t code_val =  12000 * 1.0 / vbat_trim_value.code * code;

    float ratio = 5e-06 * code_val + 0.8502;

    *value = code_val / ratio;

    return LL_OK;
}

/********************************************************
** \brief   ll_adc_vcr_value_get
**
** \param   adc_vcr_e       vcr
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
    uint8_t gain1, gain2;

    ll_adc_gain1_value_get(cfg->gain1, &gain1);
    ll_adc_gain2_value_get(cfg->gain2, &gain2);

    ll_adc_vref_value_get(cfg->vref, &vref);
    ll_adc_vcr_value_get(cfg->vcr, &vcr);

    if ((code & (1 << 10)) != 0)
    {
        code_val = -1 * ((~code + 1) & 0x3FF);
    }

    if (ADC_OP_GAIN0_1 == cfg->op_sel)
    {
        *value = (40 * (code_val * (vref / (1024.f * gain2)) + vcr) / gain1);
    }
    else
    {
        *value = (40 * code_val * vref) / (gain1 * 1024.f);
    }

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
    uint16_t timeout = 50; //500us的超时时间
    //设置参考电压
    ll_adc_select_channel(channel, cfg);

    //关闭adc接收中断
    ll_adc_isr_enable(false);
    //启动转换
    ll_adc_softwart_start(true);

    //等待转换完成
    while (trig_num != ll_adc_fifo_length_get())
    {
        if (timeout-- <= 0)
        {
            return LL_ERROR;
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
        return LL_ERROR;
    }

    return LL_OK;
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
    AFE_SYSCFG_UNLOCK();

    if (enable)
    {
        afe_bit_set(&AFE_SYSCFG->INT_SNS_CTRL, AFE_SYSCFG_INT_SNS_CTRL_INT_SNS_EN_SHIFT);
    }
    else
    {
        afe_bit_clear(&AFE_SYSCFG->INT_SNS_CTRL, AFE_SYSCFG_INT_SNS_CTRL_INT_SNS_EN_SHIFT);
    }

    AFE_SYSCFG_LOCK();

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
    uint32_t reg_val;
    /* adc ctrl0: */
    reg_val = ADC_CTRL0_TRIG_EN_SET(0x80) | ADC_CTRL0_AUTO_ADC_EN_SET(1) | ADC_CTRL0_FIFO_FORMAT_SET(1);
    afe_reg_write(&ADC->CTRL0, reg_val);

    /* adc ctrl1: */
    reg_val = ADC_CTRL1_ADC_IN_SEL_SET(0x08);
    afe_reg_write(&ADC->CTRL1, reg_val);

    if (LIN_AA_STYPE_STEPS_2 == type)
    {
        afe_reg_read(&ADC->CTRL2, &reg_val);
        reg_val = ADC_CTRL2_INIT_CYCLE_SET(0x3EF);
        afe_reg_write(&ADC->CTRL2, reg_val);
    }

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
    AFE_SYSCFG_UNLOCK();

    if (enable)
    {
        afe_bit_set(&AFE_SYSCFG->BIAS_CTRL, AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_SHIFT);
    }
    else
    {
        afe_bit_clear(&AFE_SYSCFG->BIAS_CTRL, AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_SHIFT);
    }

    AFE_SYSCFG_LOCK();

    return LL_OK;
}

/********************************************************
** \brief   ll_otp_check_enable
**
** \param   bool          enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_otp_check_enable(bool enable, ISR_FUNC_CALLBACK callback)
{

    afe_syscfg_int_flag_clear(OTP_INT_FLAG, 0);

    if (enable)
    {
        otp_isr_callback = callback;
        afe_syscfg_int_enable(OTP_INT_FLAG, 0);
    }
    else
    {
        otp_isr_callback = NULL;
        afe_syscfg_int_disable(OTP_INT_FLAG, 0);

    }

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
__attribute__((section("RAMCODE")))
void ADC_IRQHandler(uint32_t isr0, uint32_t isr1)
{
    if (adc_isr_enable && (isr0 & ADC_ISR0_FLAG || isr1 & ADC_ISR1_FLAG))
    {
        if (NULL != adc_isr_callback)
        {
            adc_isr_callback(isr1 & ADC_ISR1_FLAG);
        }

        afe_syscfg_int_flag_clear(ADC_ISR0_FLAG, ADC_ISR1_FLAG);
    }
}

__attribute__((section("RAMCODE")))
void OTP_IRQHandler(uint32_t isr0, uint32_t isr1)
{
    if (isr0 & AFE_SYSCFG_ISR0_OTP_INT_STATUS_MASK)
    {
        if (otp_isr_callback)
        {
            otp_isr_callback(isr0);
        }

        afe_syscfg_int_flag_clear(OTP_INT_FLAG, 0);
    }
}
