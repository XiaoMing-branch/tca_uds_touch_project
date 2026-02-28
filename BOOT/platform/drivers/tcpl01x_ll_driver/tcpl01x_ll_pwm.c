/**
 *****************************************************************************
 * @brief   uart driver source file.
 *
 * @file    tcpl01x_ll_uart.c
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

#include "tcpl01x_ll_pwm.h"
#include "system_tcpl01x.h"
#include "tcpl01x_ll_cortex.h"

static uint32_t pwm_isr0_flag = 0 ;
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
    uint32_t reg_val = 0;
    AFE_CLOCK_CONFIG_UNLOCK();
    //clk rtst
    afe_bit_set(&AFE_CRG->PWM_CLKRST_CTRL, AFE_CRG_PWM_CLKRST_CTRL_RST_PWM_SHIFT);
    afe_bit_clear(&AFE_CRG->PWM_CLKRST_CTRL, AFE_CRG_PWM_CLKRST_CTRL_RST_PWM_SHIFT);
    //fclk div config
    reg_val = AFE_CRG_PWM_CLKRST_CTRL_FCLK_EN_PWM_SET(1) | AFE_CRG_PWM_CLKRST_CTRL_FCLK_DIV_PWM_SET(config->fclk_div);
    afe_reg_write(&AFE_CRG->PWM_CLKRST_CTRL, reg_val);
    AFE_CLOCK_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_pwm_gpio_config
**
** \param   ll_hvio_mode_e      mode
**
** \retval  None
*********************************************************/
static void ll_pwm_gpio_config(pwm_hvio_mode_e mode)
{
    uint32_t reg_val = (HVIO_MODE_LED == mode) ? 1 : 2;

    afe_reg_write(&AFE_PINMUX->OUT0_CFG, reg_val);
    afe_reg_write(&AFE_PINMUX->OUT1_CFG, reg_val);

    afe_reg_write(&AFE_PINMUX->OUT2_CFG, reg_val);

    if (HVIO_MODE_LED == mode)
    {
        //Enable of bias of active mode for LED and LIN AA
        reg_val = AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_SET(1);
        afe_reg_write(&AFE_SYSCFG->BIAS_CTRL, 1);
    }

    //LED DIS CFG
    PINMUX->LED_DIS_CFG_F.LED_DIS_SRC_SEL = 0;
    reg_val = AFE_PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_SET(0);
    afe_reg_write(&AFE_PINMUX->LED_DIS_CFG, reg_val);
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
    if (config->isr_enable)
    {
        pwm_isr0_flag = config->isr & PWM_INIT_ALL_FLAG;   /* int1 use backup flag*/
        pwm_isr_callback = callback;

    }
    else
    {
        pwm_isr0_flag = 0;
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

    // afe_syscfg_int_flag_clear(PWM_INIT_ALL_FLAG, 0);

    if (enable)
    {
        afe_syscfg_int_enable(isr & PWM_INIT_ALL_FLAG,  0); //enable isr_falg
    }
    else
    {
        afe_syscfg_int_disable(isr & PWM_INIT_ALL_FLAG,  0); //enable isr_falg
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

    afe_syscfg_int_flag_clear(PWM_INIT_ALL_FLAG, 0);

    if (enable)
    {
        afe_syscfg_int_enable(pwm_isr0_flag,  0); //enable isr_falg
    }
    else
    {
        afe_syscfg_int_disable(PWM_INIT_ALL_FLAG,  0); //enable isr_falg
    }

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
    uint32_t reg_val;

    if (HVIO_MODE_LED == mode)
    {
        afe_reg_read(&AFE_PWM->LED_CTRL, &reg_val);

        if (enable)
        {
            reg_val |= SYSCFG_LED_CTRL_LED_DIS_SET(1);
        }
        else
        {
            reg_val &= SYSCFG_LED_CTRL_LED_DIS_CLR;
        }

        afe_reg_write(&AFE_PWM->LED_CTRL, reg_val);
    }

    afe_reg_read(&AFE_PWM->CTRL, &reg_val);

    if (enable)
    {
        reg_val |= AFE_PWM_CTRL_GLB_EN_SET(1) | AFE_PWM_CTRL_SYNC_EN_SET(1) | AFE_PWM_CTRL_PWM_SW_EN_SET(1) | AFE_PWM_CTRL_GLB_LD_EN_SET_SET(1) ;
    }
    else
    {
        reg_val &= AFE_PWM_CTRL_GLB_EN_CLR & AFE_PWM_CTRL_SYNC_EN_CLR & AFE_PWM_CTRL_PWM_SW_EN_CLR & AFE_PWM_CTRL_GLB_LD_EN_SET_CLR;
    }

    afe_reg_write(&AFE_PWM->CTRL, reg_val);

}

/********************************************************
** \brief   ll_pwm_channel_threshold_config
**
** \param   pwm_channel_e       channel
** \param   uint16_t            threshold_h
** \param   uint16_t            threshold_l
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_channel_threshold_config(pwm_channel_e channel, uint16_t threshold_h, uint16_t threshold_l)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    uint32_t ref_val = AFE_PWM_CH0_PWM_CFG_HT0_SET(threshold_h) | AFE_PWM_CH0_PWM_CFG_LT0_SET(threshold_l);

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_write(&AFE_PWM->CH0_PWM_CFG, ref_val);
            break;

        case PWM_CHANNEL_1:
            afe_reg_write(&AFE_PWM->CH1_PWM_CFG, ref_val);
            break;

        case PWM_CHANNEL_2:
            afe_reg_write(&AFE_PWM->CH2_PWM_CFG, ref_val);
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_channel_period_config
**
** \param   pwm_channel_e       channel
** \param   uint16_t            period
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_channel_period_config(pwm_channel_e channel, uint16_t period)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_write(&AFE_PWM->CH0_CNT_CFG, AFE_PWM_CH0_CNT_CFG_PERIOD0_SET(period));
            break;

        case PWM_CHANNEL_1:
            afe_reg_write(&AFE_PWM->CH1_CNT_CFG, AFE_PWM_CH1_CNT_CFG_PERIOD1_SET(period));
            break;

        case PWM_CHANNEL_2:
            afe_reg_write(&AFE_PWM->CH2_CNT_CFG, AFE_PWM_CH2_CNT_CFG_PERIOD2_SET(period));
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_channel_enable
**
** \param   pwm_channel_e       channel
** \param   bool                enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_channel_enable(pwm_channel_e channel, bool enable)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    uint8_t status = 0;
    (void)(&status);
    volatile uint32_t *reg = NULL;

    switch (channel)
    {
        case PWM_CHANNEL_0:
            reg = &AFE_PWM->CH0_CTRL;
            break;

        case PWM_CHANNEL_1:
            reg = &AFE_PWM->CH1_CTRL;
            break;

        case PWM_CHANNEL_2:
            reg = &AFE_PWM->CH2_CTRL;
            break;

        default:
            break;
    }

    if (enable)
    {
        afe_bit_set(reg, 0);
    }
    else
    {
        afe_bit_clear(reg, 0);
    }

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

    uint32_t reg_val;
    uint8_t status = 0;
    (void)(&status);

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_read(&AFE_PWM->CH0_PWM_CFG, &reg_val);
            *value = reg_val >> AFE_PWM_CH0_PWM_CFG_HT0_SHIFT;
            break;

        case PWM_CHANNEL_1:
            afe_reg_read(&AFE_PWM->CH1_PWM_CFG, &reg_val);
            *value = reg_val >> AFE_PWM_CH1_PWM_CFG_HT1_SHIFT;
            break;

        case PWM_CHANNEL_2:
            afe_reg_read(&AFE_PWM->CH2_PWM_CFG, &reg_val);
            *value = reg_val >> AFE_PWM_CH2_PWM_CFG_HT2_SHIFT;
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_pwm_channel_counter_get
**
** \param   pwm_channel_e       channel
** \param   uint16_t*           value
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_pwm_channel_counter_get(pwm_channel_e channel, uint16_t *value)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    uint32_t reg_val;

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_read(&AFE_PWM->CH0_CNT_VAL, &reg_val);
            break;

        case PWM_CHANNEL_1:
            afe_reg_read(&AFE_PWM->CH1_CNT_VAL, &reg_val);
            break;

        case PWM_CHANNEL_2:
            afe_reg_read(&AFE_PWM->CH2_CNT_VAL, &reg_val);
            break;

        default:
            break;
    }

    *value = reg_val;

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
    SYSCFG_UNLOCK();

    SYSCFG->LED_CTRL_F.LED_DIS = (enable) ? 1 : 0;

    SYSCFG_LOCK();
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

    uint32_t reg_val;

    afe_reg_read(&AFE_PWM->PWM_STATUS, &reg_val);
    *value = reg_val & 0x0F;

    return LL_OK;
}

/********************************************************
** \brief   ll_led_driver_current_config
**
** \param   pwm_channel_e           channel
** \param   led_driver_current_e    driver_current
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_driver_current_config(pwm_channel_e channel, led_driver_current_e current)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;

    PWM_CONFIG_UNLOCK();

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_read(&AFE_PWM->LED_LC0_CTRL, &reg_val);
            reg_val &= AFE_PWM_LED_LC0_CTRL_LED_LC0_IOUT_SEL_CLR;
            reg_val |= AFE_PWM_LED_LC0_CTRL_LED_LC0_IOUT_SEL_SET(current);
            afe_reg_write(&AFE_PWM->LED_LC0_CTRL, reg_val);
            break;

        case PWM_CHANNEL_1:
            afe_reg_read(&AFE_PWM->LED_LC1_CTRL, &reg_val);
            reg_val &= AFE_PWM_LED_LC1_CTRL_LED_LC1_IOUT_SEL_CLR;
            reg_val |= AFE_PWM_LED_LC1_CTRL_LED_LC1_IOUT_SEL_SET(current);
            afe_reg_write(&AFE_PWM->LED_LC1_CTRL, reg_val);
            break;

        case PWM_CHANNEL_2:
            afe_reg_read(&AFE_PWM->LED_LC2_CTRL, &reg_val);
            reg_val &= AFE_PWM_LED_LC2_CTRL_LED_LC2_IOUT_SEL_CLR;
            reg_val |= AFE_PWM_LED_LC2_CTRL_LED_LC2_IOUT_SEL_SET(current);
            afe_reg_write(&AFE_PWM->LED_LC2_CTRL, reg_val);
            break;

        default:
            break;
    }

    PWM_CONFIG_LOCK();

    return LL_OK;
}

/********************************************************
** \brief   ll_led_driver_current_get
**
** \param   pwm_channel_e           channel
** \param   led_driver_current_e    *current
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_driver_current_get(pwm_channel_e channel, led_driver_current_e *current)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;

    PWM_CONFIG_UNLOCK();

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_read(&AFE_PWM->LED_LC0_CTRL, &reg_val);
            break;

        case PWM_CHANNEL_1:
            afe_reg_read(&AFE_PWM->LED_LC1_CTRL, &reg_val);
            break;

        case PWM_CHANNEL_2:
            afe_reg_read(&AFE_PWM->LED_LC2_CTRL, &reg_val);
            break;

        default:
            break;
    }

    PWM_CONFIG_LOCK();
    *current = (reg_val >> 8) & 0x0F;
    return LL_OK;
}

/********************************************************
** \brief   ll_led_diag_current_config
**
** \param   pwm_channel_e           channel
** \param   led_diag_current_e      diag_current
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_diag_current_config(pwm_channel_e channel, led_diag_current_e current)
{
    if (channel >= PWM_CHANNEL_MAX)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;

    PWM_CONFIG_UNLOCK();

    switch (channel)
    {
        case PWM_CHANNEL_0:
            afe_reg_read(&AFE_PWM->LED_LC0_CTRL, &reg_val);
            reg_val &= AFE_PWM_LED_LC0_CTRL_LED_LC0_DISPU_EN_CLR;
            reg_val &= AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_I_SEL_CLR;
            reg_val |= AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_I_SEL_SET(current);
            afe_reg_write(&AFE_PWM->LED_LC0_CTRL, reg_val);
            break;

        case PWM_CHANNEL_1:
            afe_reg_read(&AFE_PWM->LED_LC1_CTRL, &reg_val);
            reg_val &= AFE_PWM_LED_LC1_CTRL_LED_LC1_DISPU_EN_CLR;
            reg_val &= AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_I_SEL_CLR;
            reg_val |= AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_I_SEL_SET(current);
            afe_reg_write(&AFE_PWM->LED_LC1_CTRL, reg_val);
            break;

        case PWM_CHANNEL_2:
            afe_reg_read(&AFE_PWM->LED_LC2_CTRL, &reg_val);
            reg_val &= AFE_PWM_LED_LC2_CTRL_LED_LC2_DISPU_EN_CLR;
            reg_val &= AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_I_SEL_CLR;
            reg_val |= AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_I_SEL_SET(current);
            afe_reg_write(&AFE_PWM->LED_LC2_CTRL, reg_val);
            break;

        default:
            break;
    }

    PWM_CONFIG_LOCK();

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

    uint8_t status;
    (void)(&status);
    volatile uint32_t *reg_addr;

    switch (channel)
    {
        case PWM_CHANNEL_0:
            reg_addr = &AFE_PWM->LED_LC0_CTRL;
            break;

        case PWM_CHANNEL_1:
            reg_addr = &AFE_PWM->LED_LC1_CTRL;
            break;

        case PWM_CHANNEL_2:
            reg_addr = &AFE_PWM->LED_LC2_CTRL;
            break;

        default:
            break;
    }

    if (enable)
    {
        afe_bit_set(reg_addr, 0);
    }
    else
    {
        afe_bit_clear(reg_addr, 0);
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_led_ctrl_config_get
**
** \param   uint32_t*  led_ctrl
** \param   uint32_t*  ctrl
**
** \retval  None
*********************************************************/
void ll_led_ctrl_config_get(uint32_t *led_ctrl, uint32_t *ctrl)
{
    afe_reg_read(&AFE_PWM->LED_CTRL, led_ctrl);
    afe_reg_read(&AFE_PWM->CTRL, ctrl);
}

/********************************************************
** \brief   ll_led_ctrl_config
**
** \param   uint32_t   led_ctrl
** \param   uint32_t   ctrl
**
** \retval  None
*********************************************************/
void ll_led_ctrl_config(uint32_t led_ctrl, uint32_t ctrl)
{
    afe_reg_write(&AFE_PWM->LED_CTRL, led_ctrl);
    afe_reg_write(&AFE_PWM->CTRL, ctrl);
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

    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }

    uint32_t reg_val, period  = 0;

    ll_pwm_clk_config(&config->clk_cfg);
    PWM_CONFIG_UNLOCK();
    ll_pwm_gpio_config(config->hvio_mode);

    afe_reg_write(&AFE_PWM->CTRL, 0);

    reg_val = AFE_PWM_CH0_CTRL_CH0_EN_SET(1) | AFE_PWM_CH0_CTRL_CH0_PTY_SET(config->polarity) | AFE_PWM_CH0_CTRL_CH0_MODE_SET(config->out_mode);
    reg_val |=  AFE_PWM_CH0_CTRL_CH0_BRK_EN_SET(1) | AFE_PWM_CH0_CTRL_CH0_AUTO_LD_EN_SET(1);

    period = AFE_PWM_CH0_CNT_CFG_PERIOD0_SET(config->period);

    afe_reg_write(&AFE_PWM->CH0_CTRL, reg_val);
    afe_reg_write(&AFE_PWM->CH0_CNT_CFG, period);
    afe_reg_write(&AFE_PWM->CH1_CTRL, reg_val);
    afe_reg_write(&AFE_PWM->CH1_CNT_CFG, period);
    afe_reg_write(&AFE_PWM->CH2_CTRL, reg_val);
    afe_reg_write(&AFE_PWM->CH2_CNT_CFG, period);

    ll_pwm_isr_config(&config->isr_cfg, callback);

    PWM_CONFIG_LOCK();
    return LL_OK;
}

/********************************************************
** \brief   ll_led_switch_init
**
** \param   ll_pwm_bus_e        bus
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_led_switch_init(ll_pwm_bus_e bus)
{
    if (bus >= LL_PWM_BUS_MAX)
    {
        return LL_ERROR;
    }
    AFE_CLOCK_CONFIG_UNLOCK();

    uint32_t reg_val = 0;

    afe_bit_set(&AFE_CRG->GPIO_CLKRST_CTRL, AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT);
    afe_bit_clear(&AFE_CRG->GPIO_CLKRST_CTRL, AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT);

    reg_val = (AFE_CRG_GPIO_CLKRST_CTRL_FCLK_EN_GPIO_SET(1) | AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_SET(0));
    afe_reg_write(&AFE_CRG->GPIO_CLKRST_CTRL, reg_val);

    AFE_CLOCK_CONFIG_LOCK();

    reg_val = 0;
    afe_reg_read(&AFE_PWM->CTRL, &reg_val);
    reg_val |= AFE_PWM_CTRL_PWM_SW_EN_SET(1);
    afe_reg_write(&AFE_PWM->CTRL, reg_val);

    reg_val = 2;
    afe_reg_write(&AFE_PINMUX->IO3_CFG, reg_val);

    ll_pwm_enable(HVIO_MODE_LED, true);

    return LL_OK;
}

/********************************************************
** \brief   PWM_IRQHandler
**
** \param   uint32_t        isr0
** \param   uint32_t        isr1
**
** \retval  None
*********************************************************/
__attribute__((section("RAMCODE")))
void PWM_IRQHandler(uint32_t isr0, uint32_t isr1)
{

    if (isr0 & PWM_INIT_ALL_FLAG)
    {
        if (NULL != pwm_isr_callback)
        {
            pwm_isr_callback(isr0);
        }

        afe_syscfg_int_flag_clear(PWM_INIT_ALL_FLAG, 0);
    }
}
