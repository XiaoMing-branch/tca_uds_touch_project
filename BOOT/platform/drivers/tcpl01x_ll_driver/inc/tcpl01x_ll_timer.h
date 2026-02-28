/**
 *****************************************************************************
 * @brief   timer driver header.
 *
 * @file    tcpl01x_ll_timer.h
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

#ifndef __TCPL01X_LL_TIMER_H__
#define __TCPL01X_LL_TIMER_H__

#include "tcpl01x_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct
{
    ll_clk_config_t clk_cfg;
    ll_isr_config_t isr_cfg;

    uint8_t prescale;                   /*!< Specifies the clock's prescaler, so the counter clock frequency is FCLK/(prescale+1)
                                            This value can be any number between 0x00 and 0xFF */
    uint16_t initial_value;             /*!< Specifies the initial decrement alue, the timer will decremnt from this value.
                                            This parameter can be any value between 0x00 and 0xFFFF */
    bool prescale_autoload;             /*!< When Auto Load is enabled, the prescale, repeats count and initial value can be changed
                                            during the counter is running*/
    bool init_value_autoload;           /*!< when this parameter is true user can chane the initial counter
                                            value during the timer is running */
    bool repeat_disable;                /*!< if loop is disabled, the timer will decrement N times
                                            N is specified by loop_repeat_counts*/
    uint8_t repeat_counts;              /*!< Specifis the times counter will repeat decrementing if loop_disable is true
                                            This value can be any bumber between 0x00 and 0xFF */
    bool repeat_count_autoload;         /*!< when this parameter is true user can change the repeates count
                                            during the timer is running*/
} timer_config_t;

void ll_timer_deinit(void);
void ll_timer_init(timer_config_t *config, ISR_FUNC_CALLBACK callback);
ll_status_e ll_timer_isr_enable(bool enable);
void ll_timer_enable(bool enable);
void ll_timer_counter_set(uint16_t value);
uint16_t ll_timer_counter_get(void);
void ll_timer_repeat_num_set(uint8_t value);
uint8_t ll_timer_repeat_num_get(void);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_TIMER_H__ */
