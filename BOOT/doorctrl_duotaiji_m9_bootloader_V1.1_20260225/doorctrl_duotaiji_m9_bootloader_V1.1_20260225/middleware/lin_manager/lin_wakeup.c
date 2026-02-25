/**
 *****************************************************************************
 * @brief   lin wakeup source file.
 *
 * @file    lin_wakeup.c
 * @author  AE/FAE team
 * @date    09/Jan/2024
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
#include "pal_gpio.h"
#include "lin_wakeup.h"

#ifdef CFG_LIN_CONFORM_TEST
#include "pal_gpio.h"
static uint32_t bus_wakeup_cnt = 0;
uint8_t lin_slave_wakeup_flag = 0;
#define SYSTEM_SLEEP_MODE           SLEEPWALK_MODE
#else
#define SYSTEM_SLEEP_MODE           DEEPSLEEP_MODE
#endif

extern void lin_goto_idle_state(void);
extern void meas_manager_value_clear(void);
extern void led_disp_wakeup_recovery_handle(void);

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
** \brief   led_disp_wakeup_recovery_handle
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((weak)) void led_disp_wakeup_recovery_handle(void)
{
    //do noting
}

#ifdef CFG_LIN_CONFORM_TEST
/********************************************************
** \brief   lin_gpio_callback
**
** \param   uint32_t gpio_pin
**
** \retval  None
*********************************************************/
__attribute__((weak)) void lin_gpio_callback(uint32_t gpio_pin)
{
    if (lin_slave_wakeup_flag == 0 && GPIO_PIN_0 != gpio_pin)
    {
        return;
    }

    lin_slave_wakeup_flag = 1;
    bus_wakeup_cnt = 0;
}

/********************************************************
** \brief   lin_gpio_callback
**
** \param   uint32_t gpio_pin
**
** \retval  None
*********************************************************/
void lin_slave_wakeup_master_handle(void)
{
    if (lin_slave_wakeup_flag == 0)
    {
        return;
    }

    bus_wakeup_cnt++;

    switch (bus_wakeup_cnt)
    {
        case 1:
        case 19:
        case 35:
            ll_lin_ctrl_brk_tx(LL_SCI_BUS_1, 8);
            break;

        case 200:
            bus_wakeup_cnt = 0;
            break;

        default:
            break;
    }
}

/********************************************************
** \brief   system_low_power_init
**
** \param   None
**
** \retval  None
** \note    EEPSLEEP_MODE=580ua, SLEEPWALK_MODE=23ua
*********************************************************/
static void lin_gpio_wakeup_init(sleep_mode_e mode)
{
    gpio_config_t gpio_config =
    {
        .gpio_pin = GPIO_PIN_0,
        .mode = GPIO_MODE_IN_PP,
        .pull_mode = GPIO_PULL_DOWN,
        .pull_down_type = GPIO_PULLDOWN_SW_ONLY,
        .afio = AFIO_MUX_1,
        .trigger_flag = GPIO_TRIGGER_RISING_EDGE,
    };

    pal_gpio_init(&gpio_config, lin_gpio_callback);
}
#endif

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
#ifdef CFG_LIN_CONFORM_TEST
    lin_slave_wakeup_flag = 0;
#endif
#if CFG_SUPPORT_LIN_MASTER
#ifdef  __TCPL03X__
    pal_gpio_output(GPIO_PIN_5, false);
#endif
#endif
    /* low power enter */
    pmu_lpm_enter(mode);

#ifdef CFG_LIN_CONFORM_TEST
    lin_goto_idle_state();
#endif

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

#ifdef CFG_LIN_CONFORM_TEST
    lin_gpio_wakeup_init(SLEEPWALK_MODE);
#endif
}

/********************************************************
** \brief   sleep_mode_enter
**
** \param   None
**
** \retval  None
*********************************************************/
void sleep_mode_enter(void)
{
#ifdef CFG_LIN_CONFORM_TEST
    lin_slave_wakeup_master_handle();
#endif

    if (lin_goto_sleep_flg == 1)
    {
        lin_goto_sleep_flg = 0;

        lin_sleep_mode_set(SYSTEM_SLEEP_MODE);
        /* meas_manager_value_clear */
        meas_manager_value_clear();
        /* led color restore */
        led_disp_wakeup_recovery_handle();
    }
}
