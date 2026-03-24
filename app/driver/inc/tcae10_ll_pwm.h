/**
 *****************************************************************************
 * @brief   pwm driver header.
 *
 * @file    tcae10_ll_pwm.h
 * @author
 * @date    2024.04.20
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */
#ifndef __TCPL01X_LL_PWM_H__
#define __TCPL01X_LL_PWM_H__

#include "tcae10_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define PWM_INT_CH0_CNT_MAX         PWM_IMR_CNT0_OVF_INT_MSK_MASK               //Mask PWM channel0 counter max overflow interrupt
#define PWM_INT_CH0_PWM_SET         PWM_IMR_CH0_PWM_SET_INT_MSK_MASK            //Mask PWM channel0 PWM output set interrupt
#define PWM_INT_CH0_PWM_CLR         PWM_IMR_CH0_PWM_CLR_INT_MSK_MASK            //Mask PWM channel0 PWM output clear interrupt
#define PWM_INT_CH1_CNT_MAX         PWM_IMR_CNT0_OVF_INT_MSK_MASK               //Mask PWM channel1 counter max overflow interrupt
#define PWM_INT_CH1_PWM_SET         PWM_IMR_CH1_PWM_SET_INT_MSK_MASK            //Mask PWM channel1 PWM output set interrupt
#define PWM_INT_CH1_PWM_CLR         PWM_IMR_CH1_PWM_CLR_INT_MSK_MASK            //Mask PWM channel1 PWM output clear interrupt
#define PWM_INT_CH2_CNT_MAX         PWM_IMR_CNT0_OVF_INT_MSK_MASK               //Mask PWM channel2 counter max overflow interrupt
#define PWM_INT_CH2_PWM_SET         PWM_IMR_CH2_PWM_SET_INT_MSK_MASK            //Mask PWM channel2 PWM output set interrupt
#define PWM_INT_CH2_PWM_CLR         PWM_IMR_CH2_PWM_CLR_INT_MSK_MASK

#define PWM_INT_CH3_CNT_MAX         PWM_IMR_CNT1_OVF_INT_MSK_MASK                //Mask PWM channel2 counter max overflow interrupt
#define PWM_INT_CH3_PWM_SET         PWM_IMR_CH3_PWM_SET_INT_MSK_MASK            //Mask PWM channel2 PWM output set interrupt
#define PWM_INT_CH3_PWM_CLR         PWM_IMR_CH3_PWM_CLR_INT_MSK_MASK

#define PWM_INIT_FLAG   (PWM_INT_CH0_PWM_CLR | PWM_INT_CH0_CNT_MAX | \
                              PWM_INT_CH1_PWM_CLR | PWM_INT_CH1_CNT_MAX | \
                              PWM_INT_CH2_PWM_CLR | PWM_INT_CH2_CNT_MAX)

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
    PWM_MODE_DOUBLE_PERIOD = 0,
    PWM_MODE_INDEPENDENT,       //independent mode
    PWM_MODE_SOFTWARE,          //Software mode
    PWM_MODE_FIXED,
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
  * @brief  led fall sr time enumeration
  */
typedef enum
{
    LED_FALL_SR_TIME_81NS = 0,
    LED_FALL_SR_TIME_200NS,
    LED_FALL_SR_TIME_400NS,
    LED_FALL_SR_TIME_660NS,
    LED_FALL_SR_TIME_MAX,
} led_fall_sr_time_e;

/**
  * @brief  led rise sr time enumeration
  */
typedef enum
{
    LED_RISE_SR_TIME_116NS = 0,
    LED_RISE_SR_TIME_200NS,
    LED_RISE_SR_TIME_400NS,
    LED_RISE_SR_TIME_630NS,
    LED_RISE_SR_TIME_MAX,
} led_rise_sr_time_e;

/**
  * @brief  led pwm counter mode enumeration
  */
typedef enum
{
    PWM_COUNTER_MODE_UP = 0,
    PWM_COUNTER_MODE_UP_DOWN,
    PWM_COUNTER_MODE_MAX,
} pwm_counter_mode_e;

/**
  * @brief  led pwm sync mode enumeration
  */
typedef enum
{
    PWM_SYNC_MODE_NULL = 0,         /*!< no Synchronization */
    PWM_SYNC_MODE_CH0_CH1,          /*!< Sync channel 0~1 */
    PWM_SYNC_MODE_CH0_CH1_CH2,      /*!< Sync channel 0~2 */
    PWM_SYNC_MODE_CH0_CH1_CH2_CH3,  /*!< Sync channel 0~3 */
    PWM_SYNC_MODE_MAX,
} pwm_sync_mode_e;

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
    LED_DRIVER_MAX,
} led_driver_current_e;

/**
  * @brief  led diag current enumeration
  */
typedef enum
{
    LED_DIAG_MAX,
} led_diag_current_e;

typedef struct
{
    ll_clk_config_t     clk_cfg;
    ll_isr_config_t     isr_cfg;

    pwm_counter_mode_e  count_mode;
    pwm_sync_mode_e     sync_mode;
    uint16_t            period;

    pwm_outmode_e       out_mode;


    pwm_polarity_e      polarity; /*!1'b0 : PWM channel0 output 1'b1 valid; 1'b1 : PWM channel0 output 1'b0 valid; */

    pwm_hvio_mode_e     hvio_mode;


} pwm_config_t;

ll_status_e ll_pwm_isr_flag_enable(ll_pwm_bus_e bus, uint32_t isr, bool enable);
ll_status_e ll_pwm_isr_enable(ll_pwm_bus_e bus, bool enable);
ll_status_e ll_pwm_isr_clear(ll_pwm_bus_e bus, uint32_t flag);
ll_status_e ll_pwm_isr_flag_get(ll_pwm_bus_e bus, uint32_t *flag);

void ll_pwm_enable(pwm_hvio_mode_e mode, bool enable);
ll_status_e ll_pwm_channel_threshold_config(pwm_channel_e channel, uint16_t threshold_h, uint16_t threshold_l);
ll_status_e ll_pwm_channel_period_config(pwm_channel_e channel, uint16_t period);
ll_status_e ll_pwm_high_threshold_get(pwm_channel_e channel, uint16_t *value);
ll_status_e LL_pwm_channel_counter_get(pwm_channel_e channel, uint16_t *value);
void ll_pwm_break_set(bool enable);
ll_status_e ll_pwm_status_get(pwm_channel_e channel, uint8_t *value);
ll_status_e ll_led_driver_current_config(pwm_channel_e channel, led_driver_current_e current);
ll_status_e ll_led_diag_current_config(pwm_channel_e channel, led_diag_current_e current);
ll_status_e ll_led_diagnose_enable(pwm_channel_e channel, bool enable);
ll_status_e ll_led_switch_enable(ll_pwm_bus_e bus, bool enable);
ll_status_e ll_led_fall_rise_time_set(pwm_channel_e channel, led_rise_sr_time_e rise_time, led_fall_sr_time_e fall_time);
ll_status_e ll_pwm_deinit(ll_pwm_bus_e bus);
ll_status_e ll_pwm_init(ll_pwm_bus_e bus, pwm_config_t *config, ISR_FUNC_CALLBACK callback);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_PWM_H__ */
