/**
 *****************************************************************************
 * @brief   pal meas def header file.
 *
 * @file    pal_meas.h
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

#ifndef __PAL_MEAS_DEF_H__
#define __PAL_MEAS_DEF_H__

#include "pal_meas.h"
#include "pal_led.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief
 *
 */
#define LED_MEAS_SERIAL_1       (0u)
#define LED_MEAS_SERIAL_2       (1u)
#define LED_MEAS_SERIAL_3       (2u)
#if defined (__TCPL01X__)
#define LED_MEAS_SERIAL_MAX     (3u)
#elif defined __TCPL03X__
#define LED_MEAS_SERIAL_MAX     (1u)
#endif

/**
 * @brief default led serial num
 */
#define DEFAULT_LED_SERIAL_NUM  LED_MEAS_SERIAL_1

typedef bool (*meas_init)(led_channel_e);
typedef bool (*meas_gain_config)(led_channel_e, uint8_t *);
typedef bool (*meas_voltage_code_get)(meas_volt_type_e, uint16_t *);
typedef bool (*meas_volt_calc_func)(meas_volt_type_e, uint16_t, int16_t *);
typedef void (*meas_pn_code_read)(led_channel_e);
typedef bool (*meas_pn_voltage_get)(led_channel_e, rgb_type_e, uint16_t *);
typedef bool (*meas_pn_calc_func)(led_channel_e, rgb_type_e, uint16_t, int16_t *);
typedef void (*meas_pn_status_reflash)(led_channel_e);
typedef bool (*meas_pn_process)(led_channel_e, uint32_t);
typedef bool (*meas_pn_suspend)(led_channel_e);
typedef bool (*meas_pn_resume)(led_channel_e);
typedef void (*meas_pn_acquire)(led_channel_e);
typedef bool (*meas_pn_status_get)(led_channel_e, led_vf_status_type_e, uint8_t *);
typedef bool (*meas_pn_status_set)(led_channel_e, led_vf_status_type_e, uint8_t);
typedef bool (*meas_pn_threshold_get)(led_channel_e, rgb_type_e, rgb_safty_threshold_t *);

typedef struct meas_manager_instance_t_
{
    bool (*meas_init)(led_channel_e);
    bool (*meas_gain_config)(led_channel_e, uint8_t *);
    bool (*meas_voltage_code_get)(meas_volt_type_e, uint16_t *);
    bool (*meas_volt_calc_func)(meas_volt_type_e, uint16_t, int16_t *);

    bool (*meas_pn_code_read)(led_channel_e);
    bool (*meas_pn_voltage_get)(led_channel_e, rgb_type_e, uint16_t *);
    bool (*meas_pn_calc_func)(led_channel_e, rgb_type_e, uint16_t, int16_t *);

    bool (*meas_pn_status_reflash)(led_channel_e);
    bool (*meas_pn_process)(led_channel_e, uint32_t);
    bool (*meas_pn_suspend)(led_channel_e);
    bool (*meas_pn_resume)(led_channel_e);
    bool (*meas_pn_acquire)(led_channel_e);
    bool (*meas_pn_status_get)(led_channel_e, led_vf_status_type_e, uint8_t *);
    bool (*meas_pn_status_set)(led_channel_e, led_vf_status_type_e, uint8_t);
    bool (*meas_pn_threshold_get)(led_channel_e, rgb_type_e, rgb_safty_threshold_t *);
} meas_manager_instance_t;

#ifdef __cplusplus
}
#endif

#endif /*__PAL_MEAS_DEF_H__*/
