/**
 *****************************************************************************
 * @brief   pal meas source file.
 *
 * @file    pal_meas.c
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

#include "pal_meas_def.h"
#include "utilities.h"

// to do: 不同通道以及通道中断接口注册
/**
* @brief 电池电压校准开关，关闭时采用底层原始的计算公式计算
*/
#define VBAT_CALIBRATION    0

#define VBAT_GAIN_CHANGE_MAX    0x380
#define VBAT_GAIN_CHANGE_MIN    0x135


/**
 * @brief ADC TRIG NUM
 */
#if defined (__TCPL01X__)
#define ADC_TRIGGER_NUMBER    4
#elif defined (__TCPL03X__)
#define ADC_TRIGGER_NUMBER    4
#else
#define ADC_TRIGGER_NUMBER    4
#endif

extern adc_cfg_t default_vbvt_param_table[2];
extern adc_cfg_t seft_check_param_table[RGB_TYPE_MAX][LED_MEAS_SERIAL_MAX];
extern uint8_t lin_lld_sci_get_state(void);


void adc_callback_handle(uint32_t isr);

const uint32_t led_mes_flag_table[CH_TRIG_SRC_MAX] = {PWM_INT_CH0_PWM_CLR, PWM_INT_CH0_CNT_MAX, PWM_INT_CH1_PWM_CLR, PWM_INT_CH1_CNT_MAX, PWM_INT_CH2_PWM_CLR, PWM_INT_CH2_CNT_MAX};


#if CFG_SUPPORT_SERIAL_NUM_CHECK
typedef struct
{
    uint16_t value_l;
    uint16_t value_h;
} seft_adpat_value_t;

const seft_adpat_value_t seft_adpat_value[RGB_TYPE_MAX] =
{
    {
        .value_l = 1600,
        .value_h = 2000,
    },
    {
        .value_l = 2200,
        .value_h = 2600,
    },
    {
        .value_l = 2500,
        .value_h = 2900,
    },
};
#endif

led_measure_context_t led_meas_context[LED_CHANNLE_MAX];


/********************************************************
** \brief   led_meas_vf_status_set
**
** \param   None
**
** \retval  None
*********************************************************/
static void led_meas_vf_status_set(vf_sample_ctx_t *vf_sample, led_vf_status_type_e type, uint8_t enable)
{

    if (enable)
    {
        vf_sample->vf_status |= type;
    }
    else
    {
        vf_sample->vf_status &= ~type;
    }
}

/********************************************************
** \brief   led_meas_vf_status_get
**
** \param   None
**
** \retval  None
*********************************************************/
static uint8_t led_meas_vf_status_get(vf_sample_ctx_t *vf_sample, led_vf_status_type_e type)
{
    return (!!(vf_sample->vf_status & type));
}

/********************************************************
** \brief   sample_exception_recovery
**
** \param   None
**
** \retval  None
*********************************************************/
static void led_meas_pn_recovery(led_measure_context_t *ctx)
{
    ll_adc_isr_enable(false);
    ll_pwm_isr_enable(LL_PWM_BUS_0, false);
    led_meas_vf_status_set(&ctx->vf_samp, (led_vf_status_type_e)(LED_VF_DATA_STATUS | LED_VF_SUSPEND_STATUS), false);
}

/********************************************************
** \brief   led_meas_pn_channel_setup
**
** \param   led_channel_e       channel
** \param   led_channel_e       init_flag
**
** \retval  uint8_t     flag
*********************************************************/
static bool led_meas_pn_channel_setup(led_measure_context_t *ctx, bool init_flag)
{
    uint8_t adc_channel;

    if (PWM_CHANNEL_2 == ctx->vf_samp.channel)
    {
        ll_adc_isr_enable(false);
        ll_pwm_isr_enable(LL_PWM_BUS_0, false);
        led_meas_vf_status_set(&ctx->vf_samp, LED_VF_DATA_STATUS, true);
        led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SUSPEND_STATUS, false);
        ctx->vf_samp.channel = PWM_CHANNEL_0;
    }
    else
    {
        if (init_flag)
        {
            led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SAMPLE_STATUS, false);
            ctx->vf_samp.channel = PWM_CHANNEL_0;
        }
        else
        {
            ctx->vf_samp.channel += 1 ;
        }

        if (ctx->serial_num >= 3)
        {
            adc_channel = ADC_CHANNEL_VC0 + ctx->vf_samp.channel;
        }
        else
        {
            adc_channel = ADC_CHANNEL_VPN0 + ctx->vf_samp.channel;
        }

        rgb_type_e rgb;

        for (rgb = 0; rgb < RGB_TYPE_MAX; rgb++)
        {
            if (ctx->vf_samp.channel == ctx->rgb_vf_mux[rgb])
            {
                break;
            }
        }

        adc_cfg_t *cfg = &seft_check_param_table[rgb][ctx->serial_num];

        if (NULL == cfg)
        {
            return false;
        }

        ll_adc_select_channel((adc_channel_e)adc_channel, cfg);

        if (init_flag)
        {
            /*
            放在这里而不是放在开启中断后面是因为清零中断标识与使能中断之间有可能会有中断源进入导致使能中断后会立马进入中断，
            其实中断源发生在中断触发之前的30us以内,考虑到已经预留死区裕量大于30us，故将限制提前到此处。
            */
            led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SAMPLE_STATUS, true);
            ll_adc_fifo_clear();
            ll_adc_isr_enable(true);
#if defined (__TCPL01X__)
            ll_pwm_isr_flag_enable(LL_PWM_BUS_0, led_mes_flag_table[ctx->vf_samp.trig_src], 0, true);
#elif defined (__TCPL03X__)
            ll_pwm_isr_flag_enable(LL_PWM_BUS_0, led_mes_flag_table[ctx->vf_samp.trig_src], true);
            ll_pwm_isr_enable(LL_PWM_BUS_0, true);
#endif
        }
    }

    return true;
}

#if CFG_SUPPORT_SERIAL_NUM_CHECK
/********************************************************
** \brief   led_meas_serial_num_check
**
** \param   None
**
** \retval  None
*********************************************************/
static bool led_meas_serial_num_check(led_channel_e channel, uint8_t *serial_num)
{
    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];


    uint8_t analog_channel;
    uint16_t temp_buffer[ADC_TRIGGER_NUMBER] = {0};
    rgb_type_e rgb = RGB_RED;
    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_STATIC_SAMP_STATUS, true);
    pal_led_static_pnvolt_set(channel, true);

    for (rgb_type_e  rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
    {
        ll_led_diagnose_enable(rgb, true);
    }

    // for (rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
    {
        uint16_t raw_code;
        int16_t volt;

        for (uint8_t i = 0; i < LED_MEAS_SERIAL_MAX; i++)
        {
            adc_cfg_t *cfg = (adc_cfg_t *)&seft_check_param_table[rgb][i];

            if (i >= 2) //大于等于三灯珠需要使用VC通道
            {
                analog_channel = ctx->rgb_vf_mux[rgb] + ADC_CHANNEL_VC0;
            }
            else
            {
                analog_channel = ctx->rgb_vf_mux[rgb] + ADC_CHANNEL_VPN0;
            }

            if (NULL != cfg)
            {
                cfg->vca = 0;
                /*VCA_SEL=0*/
                ll_adc_gain_config(analog_channel, cfg);
            }

            if (LL_OK == ll_adc_channnel_start((adc_channel_e)analog_channel, cfg, temp_buffer, ADC_TRIGGER_NUMBER))
            {
                raw_code = averge_calculate_utils(temp_buffer, ADC_TRIGGER_NUMBER);
            }

            ll_adc_volt_calculate_func(raw_code, cfg, (uint16_t *)&volt);

            if (volt >= seft_adpat_value[rgb].value_l * (i + 1) && volt <= seft_adpat_value[rgb].value_h * (i + 1))
            {
                *serial_num = i;
                break;
            }
        }
    }

    for (pwm_channel_e  ch = PWM_CHANNEL_0; ch < PWM_CHANNEL_MAX; ch++)
    {
        ll_led_diagnose_enable(ch, false);
    }

    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_STATIC_SAMP_STATUS, false);
    pal_led_static_pnvolt_set(channel, false);
    return true;
}
#endif

adc_config_t m_config =
{
    .clk_cfg = {
        .fclk_div = 1,
    },
    .isr_cfg = {
        .isr = ADC_INT_FIFO_RDY_FLAG,
        .isr_enable = true,
    },
    .trig_num = ADC_TRIGGER_NUMBER,
    .trig_mode = TRIG_SOFTWARE,
};

/********************************************************
** \brief   信号链初始化
**
** \param   None
**
** \retval  None
*********************************************************/
MEAS_INSTANCE bool led_meas_init(led_channel_e channel)
{

    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];
    memset((void *)ctx, 0, sizeof(led_measure_context_t));

    ll_adc_init(&m_config, adc_callback_handle);

    /* Temperature sensor enable */
    ll_adc_tsensor_enable(true);

    pal_led_channel_mux_get(channel, &ctx->rgb_vf_mux);

    ctx->vf_samp.trig_src = CH0_TRIG_CNT_MAX;
    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SAMPLE_STATUS, true);


    return true;
}



/********************************************************
** \brief   led_meas_gain_config
**
** \param   led_channel_e       channel
** \param   uint8_t*            serial_num
**
** \retval  None
** \note    Vs-Vled = 40 * ( ( code * Vref / ( 1024 * Gain2 )  + VCR ) / Gain1 )
**           VR = 40 * ( ( code * 1528 / ( 1024 * 8 )  + 668 ) / 17 )
**           VG = 40 * ( ( code * 1528 / ( 1024 * 4 )  + 769 ) / 15 )
**           VB = 40 * ( ( code * 1528 / ( 1024 * 8 )  + 820 ) / 15 )
*********************************************************/
MEAS_INSTANCE bool led_meas_gain_config(led_channel_e channel, uint8_t *serial_num)
{


    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];
#if defined (__TCPL01X__)

    for (adc_channel_e ch = ADC_CHANNEL_TEMP; ch < ADC_CHANNEL_VC0; ch++)
    {
        adc_cfg_t *cfg = &default_vbvt_param_table[ch];

        if (NULL != cfg)
        {
            /*VCA_SEL=0,OP_SEL=1*/
            cfg->vca = ADC_VCA_0;
            ll_adc_gain_config((adc_channel_e)ch, cfg);
        }
    }

    if (*serial_num == LED_MEAS_SERIAL_MAX)
    {

#if CFG_SUPPORT_SERIAL_NUM_CHECK

        if (!led_meas_serial_num_check(channel, serial_num))
        {
            *serial_num = DEFAULT_LED_SERIAL_NUM;
        }

#else
        *serial_num = DEFAULT_LED_SERIAL_NUM;
#endif

    }

    ctx->serial_num = *serial_num;
    adc_channel_e adc_channel = ctx->serial_num >= LED_MEAS_SERIAL_3 ? ADC_CHANNEL_VC0 : ADC_CHANNEL_VPN0;

    for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
    {
        adc_cfg_t *cfg = &seft_check_param_table[rgb][ctx->serial_num]; //待完善

        if (NULL != cfg)
        {
            cfg->vca = ADC_VCA_0;

            /*VCA_SEL=0,OP_SEL=1*/
            ll_adc_gain_config((adc_channel_e)(ctx->rgb_vf_mux[rgb] + adc_channel), cfg);
        }
    }

#elif defined (__TCPL03X__)
    ctx->serial_num = DEFAULT_LED_SERIAL_NUM;
#endif


    return true;
}


/********************************************************
** \brief   led_meas_voltage_code_get
**
** \param   int16_t*    value:输出值
**
** \retval  bool            true:success false:failed
*********************************************************/
MEAS_INSTANCE bool led_meas_voltage_code_get(meas_volt_type_e type, uint16_t *value)
{
    uint8_t adc_channel ;
    adc_cfg_t *cfg = NULL;
    uint16_t adc_value[ADC_TRIGGER_NUMBER];

    if (MEAS_VOLT_TEMP == type)
    {
        cfg = &default_vbvt_param_table[MEAS_VOLT_TEMP];
        adc_channel = ADC_CHANNEL_TEMP;
    }
    else
    {
        cfg = &default_vbvt_param_table[MEAS_VOLT_VBAT];
        adc_channel = ADC_CHANNEL_VBAT;
    }

    if (LL_OK != ll_adc_channnel_start((adc_channel_e)adc_channel, cfg, adc_value, ADC_TRIGGER_NUMBER))
    {
        return (false);
    }

    *value = averge_calculate_utils(adc_value, ADC_TRIGGER_NUMBER);

    return (true);
}


/********************************************************
** \brief   led_meas_pn_code_read
**
** \param   None
**
** \retval  None
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_code_read(led_channel_e channel)
{
    uint16_t adc_value[ADC_TRIGGER_NUMBER];

    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    ll_led_diagnose_enable((pwm_channel_e)ctx->vf_samp.channel, false);

    ll_adc_fifo_get(adc_value, ADC_TRIGGER_NUMBER);

    ctx->vf_samp.vf_code[ctx->vf_samp.channel] = averge_calculate_utils(adc_value, ADC_TRIGGER_NUMBER);

    ctx->vf_samp.ch_status[ctx->vf_samp.channel].data_ready = true;

    led_meas_pn_channel_setup(ctx, false);

    return true;
}

/********************************************************
** \brief   led_meas_pn_voltage_get
**
** \param   led_channel_e   channel:led 通道
** \param   rgb_type_e      rgb_type_e: rgb通道
** \param   int16_t*        value: value
**
** \retval  bool            true:success false:failed
*********************************************************/

MEAS_INSTANCE bool led_meas_pn_voltage_get(led_channel_e channel, rgb_type_e rgb, uint16_t *value)
{

    if (MEAS_LED_CHANNEL_INVALID(channel) || rgb >= RGB_TYPE_MAX)
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];


    if (NULL == ctx || !ctx->vf_samp.ch_status[ctx->rgb_vf_mux[rgb]].data_ready)
    {
        return false;
    }

    *value = ctx->vf_samp.vf_code[ctx->rgb_vf_mux[rgb]];

    ctx->vf_samp.ch_status[ctx->rgb_vf_mux[rgb]].data_ready = false;
    return true;
}



/********************************************************
** \brief   led_meas_volt_calc_func
**
** \param   int16_t*    value:输出值
**
** \retval  None
*********************************************************/
MEAS_INSTANCE bool led_meas_volt_calc_func(meas_volt_type_e type, uint16_t raw_code, int16_t *value)
{
    adc_cfg_t *cfg = NULL;

    if (MEAS_VOLT_TEMP == type)
    {
        cfg = &default_vbvt_param_table[MEAS_VOLT_TEMP];
        ll_adc_temp_calculate_func(raw_code, cfg, (uint16_t *)value);
    }
    else
    {
        cfg = &default_vbvt_param_table[MEAS_VOLT_VBAT];

#if VBAT_CALIBRATION
        ll_adc_vbat_calculate_func(raw_code, (uint16_t *)value);
#else
        ll_adc_volt_calculate_func(raw_code, cfg, (uint16_t *)value);
#endif


#if defined (__TCPL01X__)

        if (raw_code > VBAT_GAIN_CHANGE_MAX && ADC_GAIN1_X5 == cfg->gain1)
        {
            cfg->gain1 = ADC_GAIN1_X2;
            ll_adc_gain_config(ADC_CHANNEL_VBAT, cfg);
        }

        if (raw_code < VBAT_GAIN_CHANGE_MIN && ADC_GAIN1_X2 == cfg->gain1)
        {
            cfg->gain1 = ADC_GAIN1_X5;
            ll_adc_gain_config(ADC_CHANNEL_VBAT, cfg);
        }

#endif
    }

    return true;
}

/********************************************************
** \brief   led_meas_pn_voltage_get
**
** \param   led_channel_e   channel:led 通道
** \param   rgb_type_e      rgb_type_e: rgb通道
** \param   int16_t*        value: value
**
** \retval  bool            true:success false:failed
*********************************************************/

MEAS_INSTANCE bool led_meas_pn_calc_func(led_channel_e channel, rgb_type_e rgb, uint16_t raw_code, int16_t *value)
{

    if (MEAS_LED_CHANNEL_INVALID(channel) || rgb >= RGB_TYPE_MAX)
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];


    if (NULL == ctx)
    {
        return false;
    }

    adc_cfg_t *cfg = &seft_check_param_table[rgb][ctx->serial_num]; //待完善

    ll_adc_volt_calculate_func(raw_code, cfg, (uint16_t *)value);
    return true;
}

/********************************************************
** \brief   led_meas_pn_status_reflash
**
** \param   led_channel_e   channel:led 通道
** \param   rgb_type_e      rgb_type_e: rgb通道
** \param   int16_t*        value: value
**
** \retval  bool            true:success false:failed
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_status_reflash(led_channel_e channel)
{

    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    if (NULL == ctx)
    {
        return false;
    }

    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SAMPLE_STATUS, false);

    uint16_t rgb_pwm_th[RGB_TYPE_MAX] __attribute__((unused));
    //获取当前rgb通道的亮度情况
    pal_led_dutcycle_get(LED_CHANNLE_0, &rgb_pwm_th[RGB_RED]);

    for (uint8_t rgb = 0; rgb < RGB_TYPE_MAX; rgb++)
    {
        ctx->vf_samp.ch_status[ctx->rgb_vf_mux[rgb]].intensity = rgb_pwm_th[rgb];
    }

    uint16_t max_value = MAX3_VALUE_GET(ctx->vf_samp.ch_status[PWM_CHANNEL_0].intensity, ctx->vf_samp.ch_status[PWM_CHANNEL_1].intensity, ctx->vf_samp.ch_status[PWM_CHANNEL_2].intensity);

    if (ctx->vf_samp.ch_status[PWM_CHANNEL_0].intensity == max_value)
    {
        ctx->vf_samp.trig_src = (!ctx->vf_samp.ch_status[PWM_CHANNEL_0].intensity) ? CH0_TRIG_CNT_MAX : CH0_TRIG_PWM_CLR;
    }
    else
    {
        ctx->vf_samp.trig_src = (ctx->vf_samp.ch_status[PWM_CHANNEL_1].intensity == max_value) ? CH1_TRIG_PWM_CLR : CH2_TRIG_PWM_CLR;
    }

    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SAMPLE_STATUS, true);

    return true;
}


/********************************************************
** \brief   led_meas_pn_process
**
** \param   None
**
** \retval  None
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_process(led_channel_e channel, uint32_t pwm_isr)
{
    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    if (!led_meas_vf_status_get(&ctx->vf_samp, LED_VF_SAMPLE_STATUS))
    {
        led_meas_pn_recovery(ctx);
        return false;
    }

    if (lin_lld_sci_get_state() == 0 || lin_lld_sci_get_state() == 0x0A || led_meas_vf_status_get(&ctx->vf_samp, LED_VF_STATIC_SAMP_STATUS))
    {
        if (pwm_isr & led_mes_flag_table[ctx->vf_samp.trig_src])
        {
            if ((ctx->vf_samp.ch_status[ctx->vf_samp.channel].intensity != 0) || led_meas_vf_status_get(&ctx->vf_samp, LED_VF_STATIC_SAMP_STATUS))
            {
                ll_led_diagnose_enable((pwm_channel_e)ctx->vf_samp.channel, true);
                ll_adc_softwart_start(true);
            }
            else
            {
                //为了避免参考电压切换后直接进行采样带来数据不稳定，本采样方案丢弃当前的采样时隙，等待一下采样时序到来再进行采样
                led_meas_pn_channel_setup(ctx, false);
                return false;
            }
        }
        else
        {
            led_meas_pn_recovery(ctx);
            return false;
        }
    }

    return true;
}

/********************************************************
** \brief   this function is used to suspend the pn sample routine
**
** \param   None
**
** \retval  None
** \note if the adc is on routine,user need reset the adc and load the trim value before start it
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_suspend(led_channel_e channel)
{

    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    ll_adc_deinit();
    ll_pwm_isr_enable(LL_PWM_BUS_0, false);

    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SUSPEND_STATUS, true);

    return true;
}

/********************************************************
** \brief   this function is used to resume the pn measure routine
**
** \param   None
**
** \retval  None
** \note if the adc is on routine,user need reset the adc and load the trim value before start it
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_resume(led_channel_e channel)
{
    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    led_meas_init(channel);
    led_meas_gain_config(channel, &ctx->serial_num);
    led_meas_vf_status_set(&ctx->vf_samp, (led_vf_status_type_e)(LED_VF_SUSPEND_STATUS | LED_VF_DATA_STATUS), false);

    return true;
}

/********************************************************
** \brief   led_meas_pn_acquire 开启pwm中断触发adc转换
**
** \param   None
**
** \retval  None
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_acquire(led_channel_e channel)
{

    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];


    if (!led_meas_vf_status_get(&ctx->vf_samp, (led_vf_status_type_e)(LED_VF_ACQUIRE_STATUS | LED_VF_STATIC_SAMP_STATUS)) || led_meas_vf_status_get(&ctx->vf_samp, (led_vf_status_type_e)LED_VF_DATA_STATUS))
    {
        return false;
    }

    __disable_irq();

    if (led_meas_vf_status_get(&ctx->vf_samp, LED_VF_SUSPEND_STATUS))
    {
        __enable_irq();
        return false;
    }

    led_meas_vf_status_set(&ctx->vf_samp, LED_VF_SUSPEND_STATUS, true);

    __enable_irq();
    led_meas_pn_channel_setup(ctx, true);
    return true;
}

/********************************************************
** \brief   led_meas_pn_status_get
**
** \param   led_channel_e                   channel
** \param   led_vf_status_type_e            type
** \param   uint8_t*                        status
**
** \retval  bool
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_status_get(led_channel_e channel, led_vf_status_type_e type, uint8_t *status)
{
    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    *status = led_meas_vf_status_get(&ctx->vf_samp, type);
    return true;
}

/********************************************************
** \brief   led_meas_pn_status_get
**
** \param   led_channel_e                   channel
** \param   led_vf_status_type_e            type
** \param   uint8_t                         status
**
** \retval  bool
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_status_set(led_channel_e channel, led_vf_status_type_e type, uint8_t status)
{
    if (MEAS_LED_CHANNEL_INVALID(channel))
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];
    led_meas_vf_status_set(&ctx->vf_samp, type, status);

    return true;
}

/********************************************************
** \brief   led_meas_pn_threshold_get
**
** \param   uint8_t                     channel:pwm channel
** \param   rgb_type_e                  rgb
** \param   rgb_safty_threshold_t*      value
**
** \retval  bool            true:success false:failed
*********************************************************/
MEAS_INSTANCE bool led_meas_pn_threshold_get(led_channel_e channel, rgb_type_e rgb, rgb_safty_threshold_t *value)
{
    if (MEAS_LED_CHANNEL_INVALID(channel) || rgb >= RGB_TYPE_MAX)
    {
        return false;
    }

    led_measure_context_t *ctx = &led_meas_context[channel];

    // adc_cfg_t *cfg = &seft_check_param_table[rgb][ctx->serial_num];

    // if (NULL == cfg)
    // {
    //     return false;
    // }

    if (LED_MEAS_SERIAL_1 == ctx->serial_num)
    {
        switch (rgb)
        {
            case RGB_RED:
                value->ceil_value = 2020;
                value->floor_value = 1585;
                break;

            case RGB_GREEN:
                value->ceil_value = 3204;
                value->floor_value = 2217;
                break;

            case RGB_BLUE:
                value->ceil_value = 3032;
                value->floor_value = 2415;
                break;

            default:
                break;
        }
    }

    // ll_adc_volt_calculate_func(0x3ff, cfg, &value->ceil_value);
    // ll_adc_volt_calculate_func(0x1f, cfg, &value->floor_value);
    return true;
}

const meas_manager_instance_t led_meas_instance_def =
{
    .meas_init = led_meas_init,
    .meas_gain_config = led_meas_gain_config,
    .meas_voltage_code_get = led_meas_voltage_code_get,
    .meas_volt_calc_func = led_meas_volt_calc_func,
    .meas_pn_code_read = led_meas_pn_code_read,
    .meas_pn_voltage_get = led_meas_pn_voltage_get,
    .meas_pn_calc_func = led_meas_pn_calc_func,
    .meas_pn_status_reflash = led_meas_pn_status_reflash,
    .meas_pn_process = led_meas_pn_process,

    .meas_pn_suspend = led_meas_pn_suspend,
    .meas_pn_resume = led_meas_pn_resume,
    .meas_pn_acquire = led_meas_pn_acquire,
    .meas_pn_status_get = led_meas_pn_status_get,

    .meas_pn_status_set = led_meas_pn_status_set,
    .meas_pn_threshold_get = led_meas_pn_threshold_get,
};
