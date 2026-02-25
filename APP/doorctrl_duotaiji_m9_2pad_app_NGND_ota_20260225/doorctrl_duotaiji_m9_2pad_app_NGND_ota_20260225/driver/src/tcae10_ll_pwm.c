/**
 *****************************************************************************
 * @brief   pwm driver source file.
 *
 * @file    tcae10_ll_pwm.c
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

#include "tcae10_ll_gpio.h"
#include "tcae10_ll_pwm.h"
#include "system_tcae10.h"
#include "tcae10_ll_cortex.h"

#define PWM_ISR_FLAG       (0xFFFFUL)

static ISR_FUNC_CALLBACK pwm_isr_callback = NULL;
/********************************************************
** \brief   ll_pwm_clk_config
**
** \param   ll_clk_config_t*    config
**
** \retval  None
*********************************************************/
static void ll_pwm_clk_config(ll_clk_config_t *config)
{
    CRG_CONFIG_UNLOCK();

    CRG->PWM_CLKRST_CTRL_F.PCLK_EN_PWM = 1;
    CRG->PWM_CLKRST_CTRL_F.FCLK_EN_PWM = 1;
    CRG->PWM_CLKRST_CTRL_F.FCLK_SEL_PWM = config->clk_source;
    CRG->PWM_CLKRST_CTRL_F.FCLK_DIV_PWM = config->fclk_div;

    CRG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_pwm_gpio_config
**
** \param   pwm_hvio_mode_e      mode
**
** \retval  None
*********************************************************/
static void ll_pwm_gpio_config(pwm_hvio_mode_e mode)
{
    gpio_afio_mux_e afio_mux = (HVIO_MODE_LED == mode) ? AFIO_MUX_0 : AFIO_MUX_1;
    ll_gpio_afio_config(GPIO_PIN_6, afio_mux);
    ll_gpio_afio_config(GPIO_PIN_7, afio_mux);
    ll_gpio_afio_config(GPIO_PIN_8, afio_mux);
}

/********************************************************
** \brief   ll_pwm_isr_config
**
** \param   ll_isr_config_t*      config
** \param   AFE_FUNC_CALLBAC      callback
**
** \retval  None
*********************************************************/
static void ll_pwm_isr_config(ll_isr_config_t *config, ISR_FUNC_CALLBACK callback)
{
    PWM->ICR |= PWM_ISR_FLAG;

    if (config->isr_enable)
    {
        PWM->IMR &= ~(config->isr & PWM_ISR_FLAG);
        pwm_isr_callback = callback;
    }
    else
    {
        PWM->IMR = PWM_ISR_FLAG;
        pwm_isr_callback = NULL;
    }
}

/********************************************************
** \brief   ll_pwm_isr_flag_enable
**
** \param   ll_pwm_bus_e    bus
** \param   uint32_t        isr_flag
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_isr_flag_enable(ll_pwm_bus_e bus, uint32_t isr, bool enable)
{
    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    PWM->ICR |= PWM_ISR_FLAG;

    if (enable)
    {
        PWM->IMR = PWM_ISR_FLAG;
        PWM->IMR &= ~(isr & PWM_ISR_FLAG);  //enable isr_flag
    }
    else
    {
        PWM->IMR |= (isr & PWM_ISR_FLAG);   //disable isr_flag
    }

    return LL_OK;

}

/********************************************************
** \brief   ll_pwm_isr_enable
**
** \param   ll_pwm_bus_e    bus
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_isr_enable(ll_pwm_bus_e bus, bool enable)
{
    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    PWM->ICR |= PWM_ISR_FLAG;

    if (enable)
    {
        NVIC_ClearPendingIRQ(PWM_IRQn);
        NVIC_EnableIRQ(PWM_IRQn);
    }
    else
    {
        // NVIC_DisableIRQ(PWM_IRQn);
        PWM->IMR |= PWM_ISR_FLAG;   //disable isr_flag
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_isr_clear
**
** \param   ll_pwm_bus_e    bus
** \param   uint32_t        flag
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_isr_clear(ll_pwm_bus_e bus, uint32_t flag)
{
    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    PWM->ICR |= flag;

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_isr_flag_get
**
** \param   ll_pwm_bus_e    bus
** \param   uint32_t*       flag
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_isr_flag_get(ll_pwm_bus_e bus, uint32_t *flag)
{
    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    *flag = PWM->ISR;

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_enable
**
** \param   ll_hvio_mode_e      mode
** \param   bool                enable
**
** \retval  None
*********************************************************/
void ll_pwm_enable(pwm_hvio_mode_e mode, bool enable)
{
    if (HVIO_MODE_LED == mode)
    {
        /* Use LEDs, it's necessary to enanble 5V and adc_ref_buf */
        PWM->LED_CTRL_F.LED_LDO5V_EN = enable;

        while (PWM->LED_CTRL_F.LED_LDO_RDY == 0);

        PWM->LED_CTRL_F.LED_EN = enable ? 1 : 0;
    }

    PWM->CH_CTRL_F.CH0_EN = 1;
    PWM->CH_CTRL_F.CH1_EN = 1;
    PWM->CH_CTRL_F.CH2_EN = 1;

    PWM->CTRL_F.CH_SYNC_EN = (enable ? 1 : 0);
    PWM->CNT_CTRL_F.CNT0_EN = (enable ? 1 : 0);
}

/********************************************************
** \brief   ll_pwm_channel_threshold_config
**
** \param   pwm_channel_e      channel
** \param   uint16_t           threshold_h
** \param   uint16_t           threshold_l
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_channel_threshold_config(pwm_channel_e channel, uint16_t threshold_h, uint16_t threshold_l)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    switch (channel)
    {
        case PWM_CHANNEL_0:
            PWM->CH0_PWM_CFG_F.HT0 = threshold_h;
            PWM->CH0_PWM_CFG_F.LT0 = threshold_l;
            break;

        case PWM_CHANNEL_1:
            PWM->CH1_PWM_CFG_F.HT1 = threshold_h;
            PWM->CH1_PWM_CFG_F.LT1 = threshold_l;
            break;

        case PWM_CHANNEL_2:
            PWM->CH2_PWM_CFG_F.HT2 = threshold_h;
            PWM->CH2_PWM_CFG_F.LT2 = threshold_l;
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_channel_period_config
**
** \param   pwm_channel_e      channel
** \param   uint16_t           period
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_channel_period_config(pwm_channel_e channel, uint16_t period)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    PWM->CNT_CFG_F.PERIOD0 = period;

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_high_threshold_get
**
** \param   pwm_channel_e       channel
** \param   uint16_t*           value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_high_threshold_get(pwm_channel_e channel, uint16_t *value)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    switch (channel)
    {
        case PWM_CHANNEL_0:
            *value = PWM->CH0_PWM_CFG_F.HT0;
            break;

        case PWM_CHANNEL_1:
            *value = PWM->CH1_PWM_CFG_F.HT1;
            break;

        case PWM_CHANNEL_2:
            *value = PWM->CH2_PWM_CFG_F.HT2;
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   LL_pwm_channel_counter_get
**
** \param   pwm_channel_e           channel
** \param   uint16_t*               value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e LL_pwm_channel_counter_get(pwm_channel_e channel, uint16_t *value)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_break_set
**
** \param   bool            enable
**
** \retval  None
*********************************************************/
void ll_pwm_break_set(bool enable)
{
    PWM->LED_CTRL_F.LED_LDO5V_EN = !enable;

    while (PWM->LED_CTRL_F.LED_LDO_RDY == 0);

    PWM->LED_CTRL_F.LED_EN = !enable ? 1 : 0;
}

/********************************************************
** \brief   ll_pwm_status_get
**
** \param   pwm_channel_e           channel
** \param   uint8_t*                value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_status_get(pwm_channel_e channel, uint8_t *value)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    *value = PWM->STATUS  & 0x3F;
    return LL_OK;
}

/********************************************************
** \brief   ll_led_driver_current_config
**
** \param   pwm_channel_e           channel
** \param   led_driver_current_e    current
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_driver_current_config(pwm_channel_e channel, led_driver_current_e current)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    switch (channel)
    {
        case PWM_CHANNEL_0:
            PWM->LED_LC0_CTRL_F.LED_LC0_DISPU_EN = 0;
            PWM->LED_LC0_CTRL_F.LED_LC0_IOUT_SEL = current;
            break;

        case PWM_CHANNEL_1:
            PWM->LED_LC1_CTRL_F.LED_LC1_DISPU_EN = 0;
            PWM->LED_LC1_CTRL_F.LED_LC1_IOUT_SEL = current;
            break;

        case PWM_CHANNEL_2:
            PWM->LED_LC2_CTRL_F.LED_LC2_DISPU_EN = 0;
            PWM->LED_LC2_CTRL_F.LED_LC2_IOUT_SEL = current;
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_led_diag_current_config
**
** \param   pwm_channel_e           channel
** \param   led_diag_current_e      current
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_diag_current_config(pwm_channel_e channel, led_diag_current_e current)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_led_diagnose_enable
**
** \param   pwm_channel_e       channel
** \param   bool                enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_diagnose_enable(pwm_channel_e channel, bool enable)
{

    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    switch (channel)
    {
        case PWM_CHANNEL_0:
            PWM->LED_LC0_CTRL_F.LED_LC0_DIAG_EN = enable ? 1 : 0;
            break;

        case PWM_CHANNEL_1:
            PWM->LED_LC1_CTRL_F.LED_LC1_DIAG_EN = enable ? 1 : 0;
            break;

        case PWM_CHANNEL_2:
            PWM->LED_LC2_CTRL_F.LED_LC2_DIAG_EN = enable ? 1 : 0;
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_led_fall_rise_time_set
**
** \param   pwm_channel_e           channel
** \param   led_rise_sr_time_e      rise_time
** \param   led_fall_sr_time_e      fall_time
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_fall_rise_time_set(pwm_channel_e channel, led_rise_sr_time_e rise_time, led_fall_sr_time_e fall_time)
{

    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    switch (channel)
    {
        case PWM_CHANNEL_0:
            PWM->LED_LC0_CTRL_F.LED_LC0_SEL_TR = rise_time;
            PWM->LED_LC0_CTRL_F.LED_LC0_SEL_TF = fall_time;
            break;

        case PWM_CHANNEL_1:
            PWM->LED_LC1_CTRL_F.LED_LC1_SEL_TR = rise_time;
            PWM->LED_LC1_CTRL_F.LED_LC1_SEL_TF = fall_time;
            break;

        case PWM_CHANNEL_2:
            PWM->LED_LC2_CTRL_F.LED_LC2_SEL_TR = rise_time;
            PWM->LED_LC2_CTRL_F.LED_LC2_SEL_TF = fall_time;
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_led_switch_enable
**
** \param   ll_pwm_bus_e        bus
** \param   bool                enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_switch_enable(ll_pwm_bus_e bus, bool enable)
{
    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    PWM->CH_CTRL_F.CH3_EN = (enable ? 1 : 0);
    PWM->CNT_CTRL_F.CNT1_EN = (enable ? 1 : 0);
    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_deinit
**
** \param   ll_pwm_bus_e        bus
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_deinit(ll_pwm_bus_e bus)
{

    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    CRG_CONFIG_UNLOCK();
    CRG->PWM_CLKRST_CTRL_F.RST_PWM = 1;
    __NOP();
    __NOP();
    CRG->PWM_CLKRST_CTRL_F.RST_PWM = 0;
    __NOP();
    __NOP();
    CRG_CONFIG_LOCK();

    pwm_isr_callback = NULL;

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_init
**
** \param   ll_pwm_bus_e        bus
** \param   pwm_config_t*       config
** \param   ISR_FUNC_CALLBACK   callback
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_init(ll_pwm_bus_e bus, pwm_config_t *config, ISR_FUNC_CALLBACK callback)
{
    uint32_t reg_val, period, threshold  = 0;
    (void)(&reg_val);
    (void)(&period);
    (void)(&threshold);

    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    ll_pwm_clk_config(&config->clk_cfg);

    /* gpio config */
    ll_pwm_gpio_config(config->hvio_mode);

    PWM->CNT_CTRL_F.CNT0_MODE = config->count_mode;
    PWM->CNT_CTRL_F.CNT0_ONE_SHOT_EN = 0;
    /* Enable by cnt0_en =1 and sync_en=1 */
    PWM->CNT_CTRL_F.CNT0_EN_MODE = 0;
    PWM->CNT_CFG_F.PERIOD0 = config->period;

    if (config->sync_mode != PWM_SYNC_MODE_NULL)
    {
        PWM->CTRL_F.CH_SYNC_EN = 1;
        PWM->CTRL_F.CH_SYNC_SEL = config->sync_mode;
    }
    else
    {
        PWM->CTRL_F.CH_SYNC_EN = 0;
    }

    PWM->CTRL_F.AUTO_LD_EN = 1;
    PWM->CTRL_F.BRK_EN = 1;
    PWM->CTRL_F.PWM_SW_EN = false;

    PWM->CH_CTRL_F.CH0_CNT_SEL = 0; /* sel counter0 */
    PWM->CH_CTRL_F.CH1_CNT_SEL = 0; /* sel counter0 */
    PWM->CH_CTRL_F.CH2_CNT_SEL = 0; /* sel counter0 */

    PWM->CH_CTRL_F.CH0_PTY = config->polarity;
    PWM->CH_CTRL_F.CH1_PTY = config->polarity;
    PWM->CH_CTRL_F.CH2_PTY = config->polarity;

    PWM->CH_CTRL_F.CH0_MODE = config->out_mode;
    PWM->CH_CTRL_F.CH1_MODE = config->out_mode;
    PWM->CH_CTRL_F.CH2_MODE = config->out_mode;

    ADC->CTRL0_F.VREFBUF_EN = true;  /* 5V out same as tcpl01x adc bias  */
    ll_pwm_isr_config(&config->isr_cfg, callback);

    return LL_OK;
}

/********************************************************
** \brief   ll_led_switch_init
**
** \param   ll_pwm_bus_e        bus
** \param   uint16_t            period
** \param   pwm_polarity_e      polarity
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_switch_init(ll_pwm_bus_e bus, uint16_t period, pwm_polarity_e polarity)
{

    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    PWM->CNT_CTRL_F.CNT1_MODE = PWM_COUNTER_MODE_UP;
    PWM->CNT_CTRL_F.CNT1_ONE_SHOT_EN = 0;
    PWM->CNT_CTRL_F.CNT1_EN_MODE = 1; /* Enable by cnt1_en =1 and sync_en=1 */
    PWM->CNT_CFG_F.PERIOD1 = period;

    PWM->CH_CTRL_F.CH3_CNT_SEL = 1; /* sel counter1 */
    PWM->CH_CTRL_F.CH3_PTY = polarity;

    PWM->CH_CTRL_F.CH3_MODE = PWM_MODE_INDEPENDENT;

    PWM->CH3_PWM_CFG_F.HT3 = period >> 2;
    PWM->CH3_PWM_CFG_F.LT3 = 0;

    return LL_OK;
}

/********************************************************
** \brief   PWM_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
//void PWM_IRQHandler(void)
//{
//    uint32_t isr = PWM->ISR;

//    if (isr & PWM_ISR_FLAG)
//    {
//        if (NULL != pwm_isr_callback)
//        {
//            pwm_isr_callback(isr);
//        }

//        PWM->ICR |= isr;
//    }
//}
