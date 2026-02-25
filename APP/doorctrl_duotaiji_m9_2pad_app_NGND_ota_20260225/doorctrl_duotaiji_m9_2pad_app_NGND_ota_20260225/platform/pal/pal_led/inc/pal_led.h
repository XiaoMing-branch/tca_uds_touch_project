/**
 *****************************************************************************
 * @brief   pal led header file.
 *
 * @file    pal_led.h
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
#ifndef __PAL_LED_H__
#define __PAL_LED_H__

#include "pal_func_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*LED_FUNC_CALLBACK)(uint32_t);

/**
  * @brief  rgb channel struct
  */
typedef struct
{
    uint8_t rgb[RGB_TYPE_MAX];
} rgb_channel_t;

/**
  * @brief  led current struct
  */
typedef struct
{
    uint8_t driver;
    uint8_t diagnose;
} led_current_t;

/**
  * @brief  static pnvolt sample struct
  */
typedef struct
{
    uint16_t duty_cycle[RGB_TYPE_MAX];
    bool valid;
} static_pnvolt_sample_t;

/**
  * @brief  led control instance struct
  */
typedef struct
{
    rgb_channel_t channel;
    led_current_t current;

    bool is_open;

    static_pnvolt_sample_t static_sample;
    ISR_FUNC_CALLBACK  callback;

    /* data */
} led_control_instance_t;

void pal_led_init(led_channel_e channel, led_control_instance_t *instance);
void pal_led_enable(led_channel_e channel, bool enable);
void pal_led_break(led_channel_e channel, bool enable);
void pal_led_dutcycle_set(led_channel_e channel, uint16_t *duty_cycle);
void pal_led_dutcycle_get(led_channel_e channel, uint16_t *duty_cycle);
void pal_led_current_set(led_channel_e channel, uint8_t current);
void pal_led_current_get(led_channel_e channel, uint8_t *current);
void pal_led_static_pnvolt_set(led_channel_e channel, bool enable);
void pal_led_channel_mux_get(led_channel_e channel, uint8_t **channel_mux);

extern led_control_instance_t led0_ctrl_instance;

#ifdef __cplusplus
}
#endif
#endif /*__PAL_LED_H__*/


