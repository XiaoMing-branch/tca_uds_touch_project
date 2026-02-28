/**
 *****************************************************************************
 * @brief   pal timer source file.
 *
 * @file    pal_timer.c
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

#include "pal_timer.h"

extern void timer_callback_handle(uint32_t isr);
/********************************************************
** \brief   timer_callback_handle
**
** \param   isr
**
** \retval  None
*********************************************************/
__attribute__((weak)) void timer_callback_handle(uint32_t isr)
{

}

/********************************************************
** \brief  struct timer_control_instance_t
**
** timer frequency = src / clk_div / count
** timer period = 1/frequency
** ex: frequency = 48M/10/480 =10 000HZ
**     period =1/10000s = 0.1ms =100us
*********************************************************/
timer_control_instance_t timer_ctrl_instance =
{
    .src = FCLK_SRC_48M,
    .clk_div = TIMER_SRC_FDIV,
    .count = TIMER_BASE_PERIOD,
    .dis_repeat = false,
    .callback = timer_callback_handle,
};

/********************************************************
** \brief   pal_timer_init
**
** \param   timer_control_instance_t    instance
**
** \retval  None
*********************************************************/
void pal_timer_init(timer_control_instance_t *instance)
{
    timer_config_t config =
    {
        .clk_cfg = {
            .clk_source = instance->src,
            .fclk_div = instance->clk_div,
        },
        .isr_cfg = {
            .isr_enable = true,
            .priority = 2,
        },
        .initial_value = instance->count,
        .repeat_disable = instance->dis_repeat,

    };
    ll_timer_init(&config, instance->callback);
    ll_timer_isr_enable(true);
    ll_timer_enable(true);
}

/********************************************************
** \brief   pal_timer_deinit
**
** \param   timer_control_instance_t
**
** \retval  None
*********************************************************/
void pal_timer_deinit(timer_control_instance_t *instance)
{
    ll_timer_deinit();
    memset(instance, 0, sizeof(timer_control_instance_t));
}

