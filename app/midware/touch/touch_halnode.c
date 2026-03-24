/**
*****************************************************************************
* @brief  touch halnode source
* @file   touch_halnode.c
* @author AE/FAE team
* @date   28/JUL/2023
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <b>&copy; Copyright (c) 2023 Tinychip Microelectronics Co.,Ltd.</b>
*
*****************************************************************************
*/

#include "string.h"
#include "tcae10_ll_def.h"
#include "tc_log.h"
#include "touch_halnode.h"
#include "touch_tool.h"
#include "touch_config.h"
#include "misc.h"

const static char *TAG = "TOUCH_HALNODE";

volatile TOUCH_HalInterface_Type *current_touch_node = NULL;    //当前touch节点
volatile int current_touch_trigadc = 1;         //当前touch是否触发adc采集

#if TOUCH_VAON_DENOISE
//Chip 1
#define TOUCH_DENOISE_TSENSOR_0     2936
#define TOUCH_DENOISE_VAON_0        2.284
#define TOUCH_DENOISE_TSENSOR_50    3414
#define TOUCH_DENOISE_VAON_50       2.263
#define TOUCH_DENOISE_TSENSOR_100   3905
#define TOUCH_DENOISE_VAON_100      2.234
//Chip 2
//#define TOUCH_DENOISE_TSENSOR_0     2931
//#define TOUCH_DENOISE_VAON_0        2.398
//#define TOUCH_DENOISE_TSENSOR_50    3416
//#define TOUCH_DENOISE_VAON_50       2.341
//#define TOUCH_DENOISE_TSENSOR_100   3889
//#define TOUCH_DENOISE_VAON_100      2.289

static struct
{
    float a;
    float b;
    float c;
} TouchDenoiseFactor;       //降噪系数
#endif

#if TOUCH_EXTSYNC_TRIG_ENABLE       //外部同步触发
volatile TOUCH_ExtSync_Type touch_extsync = {0, 0};
#endif

//将无符号adc数据转成有符号
static __INLINE T_SiData adc_get_data(void)
{
    return ((int16_t)(ADC->FIFO_DATA << 2)) >> 2;
}

static void touch_charge_low_init(struct TOUCH_HalInterface_Type *self);                             //相关寄存器初始化
static void touch_charge_set_channel(struct TOUCH_HalInterface_Type *self, const TOUCH_HalChConfig_Type *channel_cfg);         //设置当前采集的通道参数
static void touch_charge_set_gainer(struct TOUCH_HalInterface_Type *self, const TOUCH_HalGainer_Type *gainer); //设置增益器
static void touch_charge_set_ioenable(struct TOUCH_HalInterface_Type *self, uint8_t channel, uint8_t enable);  //设置对应touch通道是否接地，enable为1表示正常touch模式，为0表示接地模式
static void touch_charge_trig(struct TOUCH_HalInterface_Type *self, TOUCH_HALTRIG_TYPE t, uint32_t para);           //trig
static T_SiData touch_charge_get_data(struct TOUCH_HalInterface_Type *self);                         //获取touch的rawdata

#if TOUCH_VAON_DENOISE
    static float touch_calc_vaon(int *code_vaon_trim);      //计算vaon
#endif

static __INLINE void touch_adcreg_bkup(TOUCH_AdcBkupReg_Type *reg)
{
    reg->imr = ADC->IMR;
    reg->ctrl0 = ADC->CTRL0 & (~0x1U);
    reg->ctrl1 = ADC->CTRL1;
    reg->ctrl2 = ADC->CTRL2;
    reg->ctrl3 = ADC->CTRL3;
    reg->ctrl_ana = ADC->CTRL_ANA;
}

static __INLINE void touch_adcreg_recover(const TOUCH_AdcBkupReg_Type *reg)
{
    ADC->IMR = reg->imr;
    ADC->CTRL0 = reg->ctrl0;
    ADC->CTRL1 = reg->ctrl1;
    ADC->CTRL2 = reg->ctrl2;
    ADC->CTRL3 = reg->ctrl3;
    ADC->CTRL_ANA = reg->ctrl_ana;
}

static __INLINE void touch_adcchannel_close(void)
{
    //adc采集通道配置成接地，本片子不支持
    ADC->CTRL0_F.SW_ADC_EN = 0; //关闭ADC
    CAPTOUCH->CTRL1_F.SHLD_EN = 0;  //关闭shield
    CAPTOUCH->CTRL1_F.CAPTOUCH_EN = 0;  //关闭touch，否则低功耗下会有40ua的漏电
}

void Touch_HalInterface_SetReady(TOUCH_HalInterface_Type *interface, int v)
{
    interface->ready = (v);
};

TOUCH_HalInterface_Type *Touch_HalChargeCreate(TOUCH_HalCharge_Type *nd, const TOUCH_HalConfig_Type *touchcfg, const TOUCH_HalAdcConfig_Type *adccfg)
{
#if TOUCH_VAON_DENOISE
    float a[3][CRAMMER_BUF_LEN] =
    {
        {TOUCH_DENOISE_TSENSOR_0 * TOUCH_DENOISE_TSENSOR_0, TOUCH_DENOISE_TSENSOR_0, 1},
        {TOUCH_DENOISE_TSENSOR_50 * TOUCH_DENOISE_TSENSOR_50, TOUCH_DENOISE_TSENSOR_50, 1},
        {TOUCH_DENOISE_TSENSOR_100 * TOUCH_DENOISE_TSENSOR_100, TOUCH_DENOISE_TSENSOR_100, 1},
    };
    float b[3] = {TOUCH_DENOISE_VAON_0 * 1000000, TOUCH_DENOISE_VAON_50 * 1000000, TOUCH_DENOISE_VAON_100 * 1000000};

    if (!SiCrammerParseXYZ(a, b, &TouchDenoiseFactor.a, &TouchDenoiseFactor.b, &TouchDenoiseFactor.c))
    {
        TC_LOGE(TAG, "TouchDenoiseFactor Calc Error");
    }
#endif

    memcpy(&nd->touchcfg, touchcfg, sizeof(*touchcfg));
    memcpy(&nd->adccfg, adccfg, sizeof(*adccfg));

    nd->interface.rself = nd;
    nd->interface.ready = 0;
    nd->interface.low_init = touch_charge_low_init;
    nd->interface.set_channel = touch_charge_set_channel;
    nd->interface.set_gainer = touch_charge_set_gainer;
    nd->interface.set_ioenable = touch_charge_set_ioenable;
    nd->interface.trig = touch_charge_trig;
    nd->interface.get_data = touch_charge_get_data;

    return &nd->interface;
}

//void Touch_HalGainerInit(TOUCH_HalGainer_Type *gainer)      //根据增益器参数，初始化内部使用数据
//{
//    if (!gainer)
//    {
//        TC_LOGE(TAG, "gainer is null");
//    }

//    if (gainer->pga.enable != 0)     //计算pga寄存器
//    {
//        gainer->pga.m_pga_ctrl_reg = ((uint32_t)gainer->pga.stg1_power | ((uint32_t)gainer->pga.stg2_power << 2));
//        gainer->pga.m_pga_ctrl_reg &= (~(3U << 7));
//        gainer->pga.m_pga_ctrl_reg |= (uint32_t)1U << 8; //bug:pga chop resetb control bit, low active
//        gainer->pga.m_pga_ctrl_reg <<= 8;
//        gainer->pga.m_pga_ctrl_reg |= 0x1U;

//        gainer->pga.m_pga_chnlx_reg = (((uint32_t)gainer->pga.stg1_gain << 24) | ((uint32_t)gainer->pga.stg2_gain << 27));

//        if (gainer->pga.offset_enable != 0)    //计算pga的offset寄存器值
//        {
//            SARADC_IDAC_CFG_T idac_cfg = Calculate_IdacGroup(gainer->pga.offset_uv, gainer->pga.stg1_gain);
//            gainer->pga.m_pga_chnlx_reg |= (0x1U | ((uint32_t)idac_cfg.idac1Cur << 1) | ((uint32_t)idac_cfg.idac1CurDir << 7) | ((uint32_t)idac_cfg.idac2Cur << 8) | ((uint32_t)idac_cfg.idac2CurDir << 20));
//        }
//    }
//}

static void touch_charge_low_init(struct TOUCH_HalInterface_Type *self)                             //相关寄存器初始化
{
    TOUCH_HalCharge_Type *rself = self->rself;

    //Touch配置
#if TOUCH_USE_EXT_LDO
#else
    ASYSCFG_CONFIG_UNLOCK();
    ASYSCFG->LDO12C_CTRL_F.LDO12C_EN = 1;
    ASYSCFG_CONFIG_LOCK();
#endif

    CRG_CONFIG_UNLOCK();
    CRG->CAPTOUCH_CLKRST_CTRL_F.RST_CAPTOUCH = 1;
    __NOP();
    __NOP();
    CRG->CAPTOUCH_CLKRST_CTRL_F.RST_CAPTOUCH = 0;
    __NOP();
    __NOP();

    CRG->CAPTOUCH_CLKRST_CTRL_F.PCLK_EN_CAPTOUCH = 0x1;
    CRG->CAPTOUCH_CLKRST_CTRL_F.FCLK_EN_CAPTOUCH = 0x1;
    CRG->CAPTOUCH_CLKRST_CTRL_F.FCLK_DIV_CAPTOUCH = rself->touchcfg.clock_divider;
    CRG_CONFIG_LOCK();
		
		CAPTOUCH->ICR = 0xFFFFFFFF;	//清中断标志

    CAPTOUCH->CTRL1_F.SAMP_OVF_EN = 1;    //采样超时功能
    CAPTOUCH->CTRL1_F.SAMP_OVF_TIME = 0xFFF;
    CAPTOUCH->CTRL1_F.TW_TRIG_EN = 0;     //关闭tinywork触发
    CAPTOUCH->CTRL1_F.TRIG_ADC_EN = 1;    //触发adc使能
    CAPTOUCH->CTRL1_F.DSTSW_DIS = 0;      //高温下减小漏电
    CAPTOUCH->CTRL2_F.INIT_TIME = rself->touchcfg.init_time;
    CapTouch_Hopping(rself->touchcfg.hop_period);

    CapTouch_Enable(ENABLE);

    //Adc配置
    CRG_CONFIG_UNLOCK();
    CRG->ADC_CLKRST_CTRL_F.RST_ADC = 1;
    __NOP();
    __NOP();
    CRG->ADC_CLKRST_CTRL_F.RST_ADC = 0;
    __NOP();
    __NOP();

    CRG->ADC_CLKRST_CTRL_F.PCLK_EN_ADC = 1;
    CRG->ADC_CLKRST_CTRL_F.FCLK_DIV_ADC = rself->adccfg.clock_divider;
    CRG->ADC_CLKRST_CTRL_F.FCLK_EN_ADC = 0x1;
    CRG_CONFIG_LOCK();

    ADC->CTRL0_F.TRIG_EN = TRIG_TOUCH;
    ADC->CTRL0_F.FIFO_THRHLD = 1;
    ADC->CTRL0_F.IRQ_MODE = 2;
    ADC->CTRL0_F.VCM_SEL = rself->adccfg.vcm_sel;
    ADC->CTRL0_F.I_SEL = rself->adccfg.i_sel;
    ADC->CTRL0_F.SW_ADC_EN = 0x0;
    ADC->CTRL0_F.AUTO_ADC_EN = 0x0;

    ADC->CTRL1_F.INT1_SNS_EN = 0;
    ADC->CTRL1_F.INT0_SNS_EN = 0;
    ADC->CTRL1_F.DIV_EN = 0;
    ADC->CTRL1_F.SW_CONT_MODE = 0;
    ADC->CTRL1_F.CHNL_SAMP_NUM = 0;
    ADC->CTRL1_F.SCAN_CHNL_NUM = 0;
    ADC->CTRL1_F.VREF_SEL = rself->adccfg.vref_sel;
    ADC->CTRL1_F.IN_SEL = ADC_CHANNEL_TOUCH;

    ADC->CTRL2_F.SAMP_CYCLE = rself->adccfg.samp_cycle;
    ADC->CTRL2_F.INIT_CYCLE = rself->adccfg.init_cycle;

    ADC->CTRL0_F.VREFBUF_EN = 1;        //vref打开

    touch_adcreg_bkup(&rself->adc_bkup_reg);

    CapTouch_InterruptEnable(CAPTOUCH_SAMP_OVF | CAPTOUCH_TRIG_DONE);
}

static void touch_charge_set_channel(struct TOUCH_HalInterface_Type *self, const TOUCH_HalChConfig_Type *channel_cfg)         //设置当前采集的通道参数
{
    TOUCH_HalCharge_Type *rself = self->rself;

    rself->captouch_mode = channel_cfg->captouch_mode;

    CAPTOUCH->CTRL0_F.CHNL_SEL = channel_cfg->channel;
    CAPTOUCH->CTRL1_F.CREF_SEL = channel_cfg->cref_sel;
    CAPTOUCH->CTRL1_F.CAPTOUCH_MODE = channel_cfg->captouch_mode;

//    CAPTOUCH->CTRL1_F.SHLD_EN = channel_cfg->shield.shld_en;      //移到trig处使能，shield通道会消耗约1ma电流
    rself->shld_en = channel_cfg->shield.shld_en;
    CAPTOUCH->CTRL1_F.SHLD_EN = 0;
    CAPTOUCH->CTRL0_F.SHLD_I = channel_cfg->shield.shld_i;
    CAPTOUCH->CTRL0_F.SHLD_SEL = channel_cfg->shield.shld_sel;

    CAPTOUCH->CTRL1_F.CMP_EN = channel_cfg->compensate.cmp_en;
    CAPTOUCH->CTRL3_F.IDAC_INP = channel_cfg->compensate.idac_inp;
    CAPTOUCH->CTRL3_F.IDAC_INN = channel_cfg->compensate.idac_inn;
    CAPTOUCH->CTRL3_F.IDAC_TIME = channel_cfg->compensate.idac_time;
    CAPTOUCH->CTRL3_F.SW_IDAC_SEL_P = channel_cfg->compensate.idac_p_en;
    CAPTOUCH->CTRL3_F.SW_IDAC_SEL_N = channel_cfg->compensate.idac_n_en;
    CAPTOUCH->CTRL3_F.SW_IDAC_MODE = 0;
    if (channel_cfg->compensate.cmp_en)
    {
        CAPTOUCH->CTRL3_F.IDAC_EN = 1;
    }
    else
    {
        CAPTOUCH->CTRL3_F.IDAC_EN = 0;
    }

    CAPTOUCH->CTRL1_F.CAPTOUCH_EN = 1;      //开启touch
}

static void touch_charge_set_gainer(struct TOUCH_HalInterface_Type *self, const TOUCH_HalGainer_Type *gainer) //设置增益器
{
    TOUCH_HalCharge_Type *rself = self->rself;

    //恢复adc配置
    touch_adcreg_recover(&rself->adc_bkup_reg);

    if (gainer->init_time == 0x0)
    {
        CAPTOUCH->CTRL2_F.INIT_TIME = rself->touchcfg.init_time;
    }
    else
    {
        CAPTOUCH->CTRL2_F.INIT_TIME = gainer->init_time;
    }
    CAPTOUCH->CTRL1_F.TRAN_LOOP = gainer->tran_loop;
    CAPTOUCH->CTRL2_F.TRAN_TIME = gainer->tran_time;
    CAPTOUCH->CTRL2_F.CHG_TIME = gainer->chg_time;
    ADC->CTRL1_F.PGA_EN = gainer->pga.enable;
    if (gainer->pga.enable)
    {
        ADC->CTRL1_F.PGA_BP = 0;
    }
    else
    {
        ADC->CTRL1_F.PGA_BP = 1;
    }
    ADC->CTRL1_F.PGA_GAIN_SEL = gainer->pga.pga_gain_sel;
#if TOUCH_VAON_DENOISE
    ADC->CTRL1_F.BUFP_EN = 1;
    ADC->CTRL1_F.BUFN_EN = 1;
    ADC->CTRL1_F.BUFP_BP = 0;
    ADC->CTRL1_F.BUFN_BP = 0;
#else
    if (gainer->pga.buf_en)
    {
        ADC->CTRL1_F.BUFP_EN = 1;
        ADC->CTRL1_F.BUFN_EN = 1;
        ADC->CTRL1_F.BUFP_BP = 0;
        ADC->CTRL1_F.BUFN_BP = 0;
    }
    else
    {
        ADC->CTRL1_F.BUFP_EN = 0;
        ADC->CTRL1_F.BUFN_EN = 0;
        ADC->CTRL1_F.BUFP_BP = 1;
        ADC->CTRL1_F.BUFN_BP = 1;
    }
#endif
    ADC->CTRL0_F.VCR_EN = gainer->pga.vcr_en;
    ADC->CTRL0_F.VCR_SEL = gainer->pga.vcr_sel;
}

static void touch_charge_set_ioenable(struct TOUCH_HalInterface_Type *self, uint8_t channel, uint8_t enable)  //设置对应touch通道是否接地，enable为1表示正常touch模式，为0表示接地模式
{
    (void)self;
    Touch_IOEnable(channel, enable);
}

static void touch_charge_trig(struct TOUCH_HalInterface_Type *self, TOUCH_HALTRIG_TYPE t, uint32_t para)              //trig
{
    TOUCH_HalCharge_Type *rself = self->rself;

    current_touch_node = self;
    current_touch_trigadc = (int32_t)para;
    if (para)      //触发adc采集
    {
        CAPTOUCH->CTRL1_F.TRIG_ADC_EN = 1;
    }
    else
    {
        CAPTOUCH->CTRL1_F.TRIG_ADC_EN = 0;
    }

    //清adc的fifo
    uint16_t i = 0;
    while (ADC->FIFO_STATE_F.ENTRY_VALID != 0 && i < 64)
    {
        ++i;
        (void)(adc_get_data());
    }

#if TOUCH_EXTSYNC_TRIG_ENABLE       //外部同步触发
    if (touch_extsync.enable)
    {
        uint8_t last_sync_cnt = touch_extsync.sync_cnt;
        while (touch_extsync.enable && last_sync_cnt == touch_extsync.sync_cnt)
        {
            continue;
        }
    }
#endif

    ADC->CTRL0_F.SW_ADC_EN = 0x1;       //开启adc
    CAPTOUCH->CTRL1_F.SHLD_EN = rself->shld_en; //使能shield

    if (t == TOUCH_TRIG_SOFTWARE)
    {
        CAPTOUCH->CTRL1_F.TW_TRIG_EN = 0;
        CAPTOUCH->CTRL0_F.SW_TRIG = 1;
    }
    else
    {
        CAPTOUCH->CTRL1_F.TW_TRIG_EN = 1;
    }

#if TOUCH_TRIG_IN_SLEEP_MODE             //sleep模式中trig，以降低功耗
    ll_lpm_mcu_enter(SLEEP_MODE, 0);        //cpu和systick停止运行
#endif
}

static T_SiData touch_charge_get_data(struct TOUCH_HalInterface_Type *self)                             //获取touch的rawdata
{
    T_SiData touchData;
    uint16_t i;
    TOUCH_HalCharge_Type *rself = self->rself;

    CAPTOUCH->CTRL1_F.SHLD_EN = 0;  //touch已采集完，可关闭shield通道

    //忙等采集adc结果
    i = 0;
    uint32_t waitNum = (rself->captouch_mode == CHARGE_DISCHARGE_BALANCE_MODE ? 2 : 1);
    while (ADC->FIFO_STATE_F.ENTRY_VALID < waitNum && i < 0xFFFFU)
    {
        ++i;
        continue;
    }
    if (i < 0xFFFFU)
    {
        if (rself->captouch_mode == CHARGE_DISCHARGE_BALANCE_MODE)
        {
            T_SiData touchData1 = adc_get_data();
            T_SiData touchData2 = adc_get_data();
#if LOG_LOCAL_LEVEL != TC_LOG_NONE
#if TOUCH_CHECK_RAWDATA
            if (touchData1 > 6000 || touchData1 < -6000)
            {
                TC_LOGE(TAG, "touch1 adc overflow : %d", touchData1);
            }
            if (touchData2 > 6000 || touchData2 < -6000)
            {
                TC_LOGE(TAG, "touch2 adc overflow : %d", touchData2);
            }
//            TC_LOGI(TAG, "touchDatas:%d,%d", touchData1, touchData2);
#endif
#endif
            touchData = touchData1 - touchData2 + 6554;     //数值+6554修正为正值（1.2/1.5*8192 = 6554）
        }
        else
        {
            touchData = adc_get_data();
#if LOG_LOCAL_LEVEL != TC_LOG_NONE
#if TOUCH_CHECK_RAWDATA
            if (touchData > 6000 || touchData < -6000)
            {
                TC_LOGE(TAG, "touch adc overflow : %d", touchData);
            }
#endif
#endif
        }
    }
    else
    {
        touchData = 0;
        TC_LOGE(TAG, "adc timeout");
    }

#if TOUCH_VAON_DENOISE
    int code_vaon_trim;
    float vaon = touch_calc_vaon(&code_vaon_trim) / 1000000;
//    printf("vaon:%f,code_vaon:%d\r\n", vaon, code_vaon_trim);
//    printf("before touchData:%d\r\n", touchData);
    if (rself->adccfg.vref_sel == ADC_VREF_1500)
    {
        touchData = ((vaon * touchData) / code_vaon_trim) * 3000;
    }
    else
    {
        touchData = ((vaon * touchData) / code_vaon_trim) * 3000;
    }
//    printf("after touchData:%d\r\n", touchData);
#endif

    touch_adcchannel_close();       //采完adc通道接地后，会减小一点点噪音
    Touch_HalInterface_SetReady(self, 0);           //清就绪标志

    return touchData;
}

#if TOUCH_VAON_DENOISE
static float touch_calc_vaon(int *code_vaon_trim)       //计算vaon
{
    int tsensor_code;
    int vaon_code;
    typedef union
    {
        uint16_t    ChannelCfg;
        struct
        {
            uint16_t                ADC_Channel_Sel     : 5;
            uint16_t                PGA_Bypass          : 1;
            uint16_t                PGA_Bufn_Bypass     : 1;
            uint16_t                PGA_Bufp_Bypass     : 1;
            uint16_t                ADC_PGA_GainSel     : 4;
            uint16_t                reserved            : 4;
        } ChannelCfg_f;

    } ADC_ChannelConfig_t;

    TEST->TEST_LOCK = 0x76543210;
    TEST->TEST_ANA_CTRL_F.TESTMUX_TAO_SEL = 2;
    TEST->TEST_ANA_CTRL_F.TEST_AON = 1;
    TEST->TEST_ANA_CTRL_F.TESTMUX_TO_ADC_EN = 1;
    TEST->TEST_ANA_CTRL_F.TESTMUX_SEL_BUF = 1;
    TEST->TEST_ANA_CTRL_F.TESTMUX_BUF_EN = 1;
    TEST->TEST_ANA_CTRL_F.TESTMUX_TAO_EN = 1;

    ADC->CTRL0_F.VCR_EN = 0;
    ADC->CTRL0_F.VCR_SEL = ADC_VCR_SEL_236_7;
    ADC->CTRL0_F.TRIG_EN = 0;
    ADC->CTRL0_F.FIFO_THRHLD = 0;
    ADC->CTRL0_F.IRQ_MODE = 2;
    ADC->CTRL0_F.VCM_SEL = ADC_VCM_SEL_205;
    ADC->CTRL0_F.VREFBUF_EN = 1;
    ADC->CTRL0_F.I_SEL = ADC_IBIAS_0p5x;
    ADC->CTRL0_F.AUTO_ADC_EN = 0;
    ADC->CTRL0_F.SW_ADC_EN = 1;

//    ADC->CTRL2_F.SAMP_CYCLE = 0xF / 2;
//    ADC->CTRL2_F.INIT_CYCLE = 0x1E0 / 2;
    ADC->CTRL2_F.SAMP_CYCLE = 0x3;
    ADC->CTRL2_F.INIT_CYCLE = 0xF;

    ADC->CTRL1_F.INT1_SNS_EN = 1;
    ADC->CTRL1_F.INT0_SNS_EN = 1;
    ADC->CTRL1_F.PGA_EN = 0;
    ADC->CTRL1_F.PGA_BP = 1;
    ADC->CTRL1_F.PGA_GAIN_SEL = ADC_GAIN_X1;
    ADC->CTRL1_F.BUFP_EN = 1;
    ADC->CTRL1_F.BUFN_EN = 1;
    ADC->CTRL1_F.BUFP_BP = 0;
    ADC->CTRL1_F.BUFN_BP = 0;
    ADC->CTRL1_F.DIV_EN = 1;
    ADC->CTRL1_F.SW_CONT_MODE = 0;
    ADC->CTRL1_F.CHNL_SAMP_NUM = 0;
    ADC->CTRL1_F.SCAN_CHNL_NUM = 1;                         //一次采集2通道
    ADC->CTRL1_F.VREF_SEL = ADC_VREF_2500;
    ADC->CTRL1_F.IN_SEL = ADC_CHANNEL_TAO_TEST;

    ADC_ChannelConfig_t channel_cfg;
    channel_cfg.ChannelCfg_f.PGA_Bufp_Bypass = 0;
    channel_cfg.ChannelCfg_f.PGA_Bufn_Bypass = 0;
    channel_cfg.ChannelCfg_f.PGA_Bypass = 1;
    channel_cfg.ChannelCfg_f.ADC_PGA_GainSel = ADC_GAIN_X1;
    channel_cfg.ChannelCfg_f.ADC_Channel_Sel = ADC_CHANNEL_TAO_TEST;
    ADC->CTRL_SCAN01_F.SCAN_CHNL_0 = channel_cfg.ChannelCfg;

    channel_cfg.ChannelCfg_f.PGA_Bufp_Bypass = 0;
    channel_cfg.ChannelCfg_f.PGA_Bufn_Bypass = 0;
    channel_cfg.ChannelCfg_f.PGA_Bypass = 0;
    channel_cfg.ChannelCfg_f.ADC_PGA_GainSel = ADC_GAIN_X16;
    channel_cfg.ChannelCfg_f.ADC_Channel_Sel = ADC_CHANNEL_TEMP1;
    ADC->CTRL_SCAN01_F.SCAN_CHNL_1 = channel_cfg.ChannelCfg;

    for (int i = 0; i <= 16 && ADC->FIFO_STATE_F.ENTRY_VALID > 0; ++i)         //清buffer
    {
        ADC->FIFO_DATA;
    }
    ADC->CTRL0_F.SW_START = 1;

    for (int j = 0; j < 0xFFFF && !ADC->FIFO_STATE_F.ENTRY_VALID; ++j)
    {
        continue;
    }
    vaon_code = ll_adc_getcode();

    for (int j = 0; j < 0xFFFF && !ADC->FIFO_STATE_F.ENTRY_VALID; ++j)
    {
        continue;
    }
    tsensor_code = ll_adc_getcode();

    ADC->CTRL0_F.SW_ADC_EN = 0; //关闭ADC

    int ostrim = ((* (volatile uint32_t *)(0x00800084)) >> 16) & 0x3FFF;
    int gain_trim = (* (volatile uint32_t *)(0x00800084)) & 0x3FFF;

    int code_t_trim = (tsensor_code - ostrim) * (((float)gain_trim) / 4096);
    *code_vaon_trim = (vaon_code - ostrim) * (((float)gain_trim) / 4096);

    return TouchDenoiseFactor.a * code_t_trim * code_t_trim + TouchDenoiseFactor.b * code_t_trim + TouchDenoiseFactor.c;
}
#endif
