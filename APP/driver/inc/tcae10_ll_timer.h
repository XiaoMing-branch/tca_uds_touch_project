/**
 *****************************************************************************
 * @brief   timer driver header.
 *
 * @file    tcae10_ll_timer.h
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

#ifndef __TCAE10_LL_TIMER_H__
#define __TCAE10_LL_TIMER_H__

#include "tcae10_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct
{
    ll_clk_config_t clk_cfg;
    ll_isr_config_t isr_cfg;
    uint16_t initial_value; /*!< Specifies the initial decrement alue, the timer will decremnt from this value.
                                This parameter can be any value between 0x00 and 0xFFFF */

    bool repeat_disable;    /*!< if loop is disabled, the timer will decrement N times
                                N is specified by loop_repeat_counts*/
    bool trigger_mode;
} timer_config_t;

void ll_timer_deinit(void);
void ll_timer_init(timer_config_t *config, ISR_FUNC_CALLBACK callback);
ll_status_e ll_timer_isr_enable(bool enable);
bool ll_timer_isr_get(void);
void ll_timer_trig_enable(bool enable);
void ll_timer_enable(bool enable);
void ll_timer_counter_set(uint16_t value);
uint16_t ll_timer_counter_get(void);

#if defined(__cplusplus)
}
#endif
#endif /* __TCAE10_LL_TIMER_H__ */
