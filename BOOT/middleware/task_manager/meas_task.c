/**
 *****************************************************************************
 * @brief   meas_task source file.
 *
 * @file    meas_task.c
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

#include "osal.h"
#include "app.h"
#include "measure.h"
#include "logging.h"

#if CFG_SUPPORT_FAULT_DET
#include "monitor_manager.h"
#endif

#define LOG_MEAS(...)  do{log_debug("[MEAS] " __VA_ARGS__);}while(0)

task_handle_t task_meas_handle;
extern bool lin_task_busy_status(void);

#if CFG_SUPPORT_SINGAL_BIN
extern const sft_adpat_value_t sft_adpat_value;
#endif

#if CFG_SUPPORT_LED_CTRL
/********************************************************
** \brief   task_meas_pn_handle
**
** \param   None
**
** \retval  None
*********************************************************/
static void task_meas_pn_handle(void)
{
    static led_channel_e mux_channel;
    mux_channel = meas_pn_acquire_channel_get();

    if (meas_pn_process_handle(mux_channel, !!CFG_SUPPORT_COLOR_COMP))
    {
        mux_channel++;

        if (mux_channel >= LED_CHANNEL_MAX)
        {
            mux_channel = LED_CHANNEL_0;
        }

#if CFG_SUPPORT_LIN_SNPD

        if (!lin_task_busy_status())
#endif
        {
            meas_pn_acquire_handle(mux_channel);

            if (meas_pn_static_sample_status_get(LED_CHANNEL_0) || meas_pn_static_sample_status_get(LED_CHANNEL_1))
            {
                OS_TASK_MODE_SET(task_meas_handle, OS_TASK_MODE_LOOP);
            }
            else
            {
                OS_TASK_MODE_SET(task_meas_handle, OS_TASK_MODE_TIME_SLICE);
            }
        }
    }
}
#endif

/********************************************************
** \brief   task_meas_safty_handle
**
** \param   None
**
** \retval  None
*********************************************************/
static void task_meas_safty_handle(void)
{
#if CFG_SUPPORT_LIN_SNPD

    if (!lin_task_busy_status())
#endif
    {
        meas_safty_handle();
    }

#if CFG_SUPPORT_FAULT_DET
    monitor_detect_handle();
#endif
}

/********************************************************
** \brief   meas_task_init
**
** \param   None
**
** \retval  None
*********************************************************/
void meas_task_init(void)
{
    for (led_channel_e channel = LED_CHANNEL_0; channel < LED_CHANNEL_MAX ; channel++)
    {
        meas_manager_init(channel);
#if CFG_SUPPORT_SINGAL_BIN
        meas_typical_pn_init(channel, (sft_adpat_value_t *)&sft_adpat_value);
#endif
    }

    meas_safty_calucate_func(MEAS_VOLT_VBAT);
    meas_safty_calucate_func(MEAS_VOLT_TEMP);

#if CFG_SUPPORT_FAULT_DET
    monitor_manager_init();
#endif

#if CFG_SUPPORT_LED_CTRL
    task_meas_handle = OS_TASK_CREATE(task_meas_pn_handle, 20, 20, 1);
    OS_TASK_CREATE(task_meas_safty_handle, 30, 30, 1);
#endif
}
