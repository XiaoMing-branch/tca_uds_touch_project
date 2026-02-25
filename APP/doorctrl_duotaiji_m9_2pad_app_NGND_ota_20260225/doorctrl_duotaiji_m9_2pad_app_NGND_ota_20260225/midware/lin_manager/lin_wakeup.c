/**
 *****************************************************************************
 * @brief  lin wakeup source file.
 * @file   lin_wakeup.c
 * @author AE/FAE team
 * @date   09/Jan/2024
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
#include "lin.h"
#include "pal_pmu.h"
#include "lin_wakeup.h"

extern uint8_t g_lighting_init;
extern void meas_manager_value_clear(void);
extern void led_color_wakeup_recovery_handle(void);

/********************************************************
** \brief   meas_manager_value_clear
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((weak)) void meas_manager_value_clear(void)
{
    //do noting
}

/********************************************************
** \brief   led_color_wakeup_recovery_handle
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((weak)) void led_color_wakeup_recovery_handle(void)
{
    //do noting
}

/********************************************************
** \brief   system_low_power_init
**
** \param   None
**
** \retval  None
** \note    EEPSLEEP_MODE=580ua, SLEEPWALK_MODE=23ua
*********************************************************/
static void lin_sleep_mode_set(sleep_mode_e mode)
{
    /* low power enter */
    pmu_lpm_enter(mode);

    /* low power exit */
    pmu_lpm_exit();
}

/********************************************************
** \brief   system_low_power_init
**
** \param   None
**
** \retval  None
*********************************************************/
void system_low_power_init(void)
{
    pmu_lpm_init();
}

/********************************************************
** \brief   sleep_mode_enter
**
** \param   None
**
** \retval  None
*********************************************************/
#ifdef CFG_LIN_CONFORM_TEST
    extern volatile uint8_t bus_wake_flag;
    extern uint32_t bus_wake_cnts;
#endif
void sleep_mode_enter(void)
{
    if (lin_goto_sleep_flg == 1)
    {
        lin_goto_sleep_flg = 0;

#ifdef CFG_LIN_CONFORM_TEST
        bus_wake_flag = 0;
        bus_wake_cnts = 0;
#endif

        lin_sleep_mode_set(DEEPSLEEP_MODE);

        /* meas_manager_value_clear */
        meas_manager_value_clear();
        /* led color restore */
        led_color_wakeup_recovery_handle();
    }
}
