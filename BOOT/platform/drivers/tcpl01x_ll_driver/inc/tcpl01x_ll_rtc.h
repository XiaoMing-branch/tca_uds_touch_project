/**
 *****************************************************************************
 * @brief   rtc driver header file.
 *
 * @file    tcpl01x_ll_rtc.h
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

#ifndef __TCPL01X_LL_RTC_H__
#define __TCPL01X_LL_RTC_H__

#include "tcpl01x_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define RTC_INT_TRIG_0_FLAG          AFE_SYSCFG_IMR1_RTC_TRIG_0_INT_MSK_MASK                 //Mask RTC trig 0 interrupt.
#define RTC_INT_CNT_FLAG             AFE_SYSCFG_IMR1_RTC_CNT_INT_MSK_MASK                    //Mask RTC counter overflow interrupt.
#define RTC_INI_ALARM_FLAG           AFE_SYSCFG_IMR1_RTC_ALARM_INT_MSK_MASK                  //Mask RTC counter alarm interrupt.

typedef struct
{
    uint8_t sec;         //00-59
    uint8_t min;         //00-59
    uint8_t hour;        //00-23
    uint8_t day;         //01-31
    uint8_t month;       //01-12
    uint8_t year;        //00-99
} rtc_time_t;

typedef struct
{
    uint8_t sec;         //00-59
    uint8_t min;         //00-59
    uint8_t hour;        //00-23
} rtc_alarm_t;

typedef struct
{
    // ll_clk_config_t clk_cfg;
    ll_isr_config_t isr_cfg;
    uint32_t period_cnt;  /*RTC cnt period num, Period time is (N+1)*30.5us, */
} rtc_config_t;

ll_status_e ll_rtc_init(rtc_config_t *config, ISR_FUNC_CALLBACK callback);
ll_status_e ll_rtc_isr_enable(bool enable);
void ll_rtc_time_set(rtc_time_t *time);
void ll_rtc_time_get(rtc_time_t *time);
void ll_rtc_alarm_set(rtc_alarm_t *time);
void ll_rtc_alarm_get(rtc_alarm_t *time);
void ll_rtc_trig0_set(uint16_t trig_num);
void RTC_IRQHandler(uint32_t isr0, uint32_t isr1);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_RTC_H__ */
