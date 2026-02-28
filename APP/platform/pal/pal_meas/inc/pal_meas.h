/**
 *****************************************************************************
 * @brief   pal meas header file.
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

#ifndef __PAL_MEAS_H__
#define __PAL_MEAS_H__

#include "pal_func_def.h"
#include "pal_meas_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CFG_SUPPORT_MEAS_INSTANNCE  1
#if CFG_SUPPORT_MEAS_INSTANNCE
#define MEAS_INSTANCE   static
#define MEAS_LED_CHANNEL_INVALID(channel) (false)
#else
#define MEAS_INSTANCE
#define MEAS_LED_CHANNEL_INVALID(channel) ((channel>=LED_CHANNLE_MAX) ? true:false)
#endif

/**
 * @brief meas volt type enumeration
 */
typedef enum
{
    MEAS_VOLT_TEMP = 0U,
    MEAS_VOLT_VBAT,
    MEAS_VOLT_PN,
    MEAS_VOLT_PN_0 = MEAS_VOLT_PN,
    MEAS_VOLT_PN_1,
    MEAS_VOLT_PN_2,
    MEAS_VOLT_MAX,
} meas_volt_type_e;

/**
 * @brief meas trig src enumeration
 */
typedef enum
{
    CH0_TRIG_PWM_CLR,
    CH0_TRIG_CNT_MAX,
    CH1_TRIG_PWM_CLR,
    CH1_TRIG_CNT_MAX,
    CH2_TRIG_PWM_CLR,
    CH2_TRIG_CNT_MAX,
    CH_TRIG_SRC_MAX,
} trig_src_e;

/**
 * @brief meas vf status enumeration
 */
typedef enum
{
    LED_VF_SAMPLE_STATUS = (0x01U << 0),        /* PN volt sample flag*/
    LED_VF_DATA_STATUS = (0x01U << 1),          /* RGB PN volt data ready*/
    LED_VF_SUSPEND_STATUS = (0x01U << 2),       /* PN volt acquire flag*/
    LED_VF_ACQUIRE_STATUS = (0x01U << 3),       /* PN volt statci sample flag*/
    LED_VF_STATIC_SAMP_STATUS = (0x01U << 4),
} led_vf_status_type_e;

/**
 * @brief meas vf channel status struct
 */
typedef struct
{
    uint16_t intensity;
    bool data_ready;
} vf_channel_status_t;

/**
 * @brief meas vf status struct
 */
typedef struct
{
    uint16_t sample_status : 1;
    uint16_t data_status : 1;
    uint16_t suspend_status : 1;
    uint16_t acquire_status : 1;
    uint16_t static_samp_status : 1;
} vf_sample_status_t;

/**
 * @brief meas vf sample context struct
 */
typedef struct
{
    uint8_t channel;
    trig_src_e trig_src;
    vf_channel_status_t ch_status[RGB_TYPE_MAX];
    uint16_t vf_code[RGB_TYPE_MAX];
    union
    {
        uint16_t vf_status;
        vf_sample_status_t vf_status_bit;
    };

} vf_sample_ctx_t;

/**
 * @brief led meas context struct
 */
typedef struct
{
    //uint8_t analog_num;
    uint8_t serial_num;
    uint8_t *rgb_vf_mux;

    vf_sample_ctx_t vf_samp; //此结构体为PWM0-2的三通道未做RGB映射

} led_measure_context_t;

/**
 * @brief led rgb safty threshold struct
 */
typedef struct
{
    uint16_t ceil_value;
    uint16_t floor_value;
} rgb_safty_threshold_t;

#if !CFG_SUPPORT_MEAS_INSTANNCE
bool led_meas_init(led_channel_e channel);
bool led_meas_gains_config(led_channel_e channel, uint8_t *serial_num);
bool led_meas_voltage_code_get(meas_volt_type_e type, uint16_t *value);
bool led_meas_volt_calc_func(meas_volt_type_e type, uint16_t raw_code, int16_t *value);

bool led_meas_pn_code_read(led_channel_e channel);
bool led_meas_pn_voltage_get(led_channel_e channel, rgb_type_e rgb, uint16_t *value);

bool led_meas_pn_calc_func(led_channel_e channel, rgb_type_e rgb, uint16_t raw_code, int16_t *value);
bool led_meas_pn_status_reflash(led_channel_e channel);
bool led_meas_pn_process(led_channel_e channel, uint32_t pwm_isr);
bool led_meas_pn_suspend(led_channel_e channel);
bool led_meas_pn_resume(led_channel_e channel);
bool led_meas_pn_acquire(led_channel_e channel);
bool led_meas_pn_status_get(led_channel_e channel, led_vf_status_type_e type, uint8_t *status);
bool led_meas_pn_status_set(led_channel_e channel, led_vf_status_type_e type, uint8_t status);
bool led_meas_pn_threshold_get(led_channel_e channel, rgb_type_e rgb, rgb_safty_threshold_t *value);
#endif


#ifdef __cplusplus
}
#endif

#endif /*__PAL_MEAS_H__*/
