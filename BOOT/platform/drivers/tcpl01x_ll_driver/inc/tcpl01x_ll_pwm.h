/**
 *****************************************************************************
 * @brief   pwm driver header.
 *
 * @file    tcpl01x_ll_pwm.h
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

#ifndef __TCPL01X_LL_PWM_H__
#define __TCPL01X_LL_PWM_H__

#include "tcpl01x_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PWM_INT_CH0_CNT_MAX         AFE_SYSCFG_IMR0_CH0_CNT_MAX_INT_MSK_MASK                //Mask PWM channel0 counter max overflow interrupt
#define PWM_INT_CH0_PWM_SET         AFE_SYSCFG_IMR0_CH0_PWM_SET_INT_MSK_MASK                //Mask PWM channel0 PWM output set interrupt
#define PWM_INT_CH0_PWM_CLR         AFE_SYSCFG_IMR0_CH0_PWM_CLR_INT_MSK_MASK                //Mask PWM channel0 PWM output clear interrupt
#define PWM_INT_CH1_CNT_MAX         AFE_SYSCFG_IMR0_CH1_CNT_MAX_INT_MSK_MASK                //Mask PWM channel1 counter max overflow interrupt
#define PWM_INT_CH1_PWM_SET         AFE_SYSCFG_IMR0_CH1_PWM_SET_INT_MSK_MASK                //Mask PWM channel1 PWM output set interrupt
#define PWM_INT_CH1_PWM_CLR         AFE_SYSCFG_IMR0_CH1_PWM_CLR_INT_MSK_MASK                //Mask PWM channel1 PWM output clear interrupt
#define PWM_INT_CH2_CNT_MAX         AFE_SYSCFG_IMR0_CH2_CNT_MAX_INT_MSK_MASK                //Mask PWM channel2 counter max overflow interrupt
#define PWM_INT_CH2_PWM_SET         AFE_SYSCFG_IMR0_CH2_PWM_SET_INT_MSK_MASK                //Mask PWM channel2 PWM output set interrupt
#define PWM_INT_CH2_PWM_CLR         AFE_SYSCFG_IMR0_CH2_PWM_CLR_INT_MSK_MASK                //Mask PWM channel2 PWM output clear interrupt

#if 0
#define PWM_CONFIG_LOCK()                                       \
    do {                                                        \
        afe_reg_write(AFE_PWM->WR_LOCK, 0x12345678);            \
        } while (0)

#define PWM_CONFIG_UNLOCK()                                     \
    do {                                                        \
        afe_reg_write(AFE_PWM->WR_LOCK, 0xAAAA5555);            \
        } while (0)
#else
#define PWM_CONFIG_LOCK()
#define PWM_CONFIG_UNLOCK()
#endif

#define PWM_INIT_FLAG   (PWM_INT_CH0_PWM_CLR | PWM_INT_CH0_CNT_MAX | \
                              PWM_INT_CH1_PWM_CLR | PWM_INT_CH1_CNT_MAX | \
                              PWM_INT_CH2_PWM_CLR | PWM_INT_CH2_CNT_MAX)


#define PWM_INIT_ALL_FLAG     (0x1FFUL)

/**
  * @brief  ll sci bus enumeration
  */
typedef enum
{
    LL_PWM_BUS_0 = 0,
    LL_PWM_BUS_MAX,
} ll_pwm_bus_e;

/**
  * @brief  ll uart bus enumeration
  */
typedef enum
{
    HVIO_MODE_LED = 0,
    HVIO_MODE_PWM
} pwm_hvio_mode_e;

/**
  * @brief  ll pwm channel enumeration
  */
typedef enum
{
    PWM_CHANNEL_0 = 0,
    PWM_CHANNEL_1,
    PWM_CHANNEL_2,
    PWM_CHANNEL_MAX
} pwm_channel_e;

/**
  * @brief  ll pwm channel enumeration
  */
typedef enum
{
    PWM_MODE_OUT_0 = 0,     //always output 0 mode
    PWM_MODE_OUT_1,         //always output 1 mode
    PWM_MODE_EDGE_ALIGN,    //edge-aligned mode
    PWM_MODE_DOUBLE_PERIOD, //double period mode,in this mode, if SW_LT1=SW_HT1, PWM output is central-aligned.
    PWM_MODE_INDEPENDENT,   //independent mode
    PWM_MODE_SIGLE_SHOT,    //single-shot mode
    PWM_MODE_SOFT_CTRL,     //Software mode
    PWM_MODE_TYPE_MAX
} pwm_outmode_e;

/**
  * @brief  ll pwm channel enumeration
  */
typedef enum
{
    PWM_POLARITY_HIGH = 0,     //high level is valid
    PWM_POLARITY_LOW,
    PWM_POLARITY_MAX
} pwm_polarity_e;

/**
  * @brief  led diag current enumeration
  */
typedef enum
{
    LED_DIAG_125UA = 0,
    LED_DIAG_250UA,
    LED_DIAG_375UA,
    LED_DIAG_500UA,
    LED_DIAG_625UA,
    LED_DIAG_750UA,
    LED_DIAG_875UA,
    LED_DIAG_1000UA,
    LED_DIAG_MAX,
} led_diag_current_e;

/**
  * @brief  led driver current enumeration
  */
typedef enum
{
    LED_DRIVER_5MA = 0,
    LED_DRIVER_10MA,
    LED_DRIVER_15MA,
    LED_DRIVER_20MA,
    LED_DRIVER_25MA,
    LED_DRIVER_30MA,
    LED_DRIVER_35MA,
    LED_DRIVER_40MA,
    LED_DRIVER_45MA,
    LED_DRIVER_50MA,
    LED_DRIVER_55MA,
    LED_DRIVER_60MA,
    LED_DRIVER_MAX,
} led_driver_current_e;

typedef struct
{
    ll_clk_config_t   clk_cfg;
    ll_isr_config_t   isr_cfg;
    pwm_outmode_e     out_mode;
    pwm_polarity_e    polarity; /*!1'b0 : PWM channel0 output 1'b1 valid; 1'b1 : PWM channel0 output 1'b0 valid; */
    uint16_t          period;
    pwm_hvio_mode_e   hvio_mode;

} pwm_config_t;

ll_status_e ll_pwm_isr_flag_enable(ll_pwm_bus_e bus, uint32_t isr, bool enable);
ll_status_e ll_pwm_isr_enable(ll_pwm_bus_e bus, bool enable);
void ll_pwm_enable(pwm_hvio_mode_e mode, bool enable);
ll_status_e ll_pwm_channel_threshold_config(pwm_channel_e channel, uint16_t threshold_h, uint16_t threshold_l);
ll_status_e ll_pwm_channel_period_config(pwm_channel_e channel, uint16_t period);
ll_status_e ll_pwm_channel_enable(pwm_channel_e channel, bool enable);
ll_status_e ll_pwm_high_threshold_get(pwm_channel_e channel, uint16_t *value);
ll_status_e ll_pwm_channel_counter_get(pwm_channel_e channel, uint16_t *value);
void ll_pwm_break_set(bool enable);
ll_status_e ll_pwm_status_get(pwm_channel_e channel, uint8_t *value);
ll_status_e ll_led_driver_current_config(pwm_channel_e channel, led_driver_current_e current);
ll_status_e ll_led_driver_current_get(pwm_channel_e channel, led_driver_current_e *current);
ll_status_e ll_led_diag_current_config(pwm_channel_e channel, led_diag_current_e current);
ll_status_e ll_led_diagnose_enable(pwm_channel_e channel, bool enable);
void ll_led_ctrl_config_get(uint32_t *led_ctrl, uint32_t *ctrl);
void ll_led_ctrl_config(uint32_t led_ctrl, uint32_t ctrl);
ll_status_e ll_pwm_init(ll_pwm_bus_e bus, pwm_config_t *config, ISR_FUNC_CALLBACK callback);
ll_status_e ll_led_switch_init(ll_pwm_bus_e bus);
void PWM_IRQHandler(uint32_t isr0, uint32_t isr1);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_PWM_H__ */
