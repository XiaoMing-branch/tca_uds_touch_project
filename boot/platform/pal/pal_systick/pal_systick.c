/**
 *****************************************************************************
 * @brief   pal systick source file.
 *
 * @file    pal_systick.c
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

#include "pal_func_def.h"
#include "pal_systick.h"

static volatile uint32_t systick_count = 0;

extern void os_task_update(void);

/********************************************************
** \brief   os_task_update
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((weak)) void os_task_update(void)
{
}

/********************************************************
** \brief   SysTick_Handler
**
** \param   None
**
** \retval  None
*********************************************************/
void SysTick_Handler(void)
{
    os_task_update();

    /* systick increase */
    systick_count++;
}

/********************************************************
** \brief   systick_count_get
**
** \param   None
**
** \retval  uint32_t
*********************************************************/
uint32_t systick_count_get(void)
{
    return (systick_count);
}

/********************************************************
** \brief   systick_diff
**
** \param   uint32_t        start_tick
**
** \retval  uint32_t
*********************************************************/
uint32_t systick_diff(uint32_t start_tick)
{
    uint32_t tick_diff = 0;

    if (systick_count_get() >= start_tick)
    {
        tick_diff = systick_count_get() - start_tick;
    }
    else
    {
        // tick overflow
        tick_diff = 0xFFFFFFFF - start_tick + systick_count_get();
    }

    return (tick_diff);
}

/********************************************************
** \brief   delay_ms
**
** \param   uint32_t        ms
**
** \retval  None
*********************************************************/
void delay_ms(uint32_t ms)
{
    interrupt_disable();
    uint32_t curret_systick = systick_count_get();
    interrupt_enable();

    while (ms > systick_diff(curret_systick));
}

/********************************************************
** \brief   delay_us
**
** \param   uint32_t        us
**
** \retval  None
*********************************************************/
void delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told;
    uint32_t tnow;
    uint32_t tcnt = 0;
    uint32_t reload;

    reload = SysTick->LOAD;

    ticks = us * (DEFAULT_SYSTEM_CLOCK / 1000000);

    tcnt = 0;
    told = SysTick->VAL;

    while (1)
    {
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }

            told = tnow;

            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}
