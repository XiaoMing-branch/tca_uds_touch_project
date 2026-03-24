/**
 *****************************************************************************
 * @brief   lin_task source file.
 *
 * @file    lin_task.c
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
#include "lin_process.h"
#include "lin_snpd.h"
#include "colormixing.h"

#if CFG_SUPPORT_LIN_SNPD && CFG_SUPPORT_LIN_SNPD_LED
color_coordinate_t target_color = {0};
#endif

static lin_snpd_context_t  lin_snpd_ctx =
{
    .timeout = 0,
    .status = {0},
    .enter_func = NULL,
    .exit_func = NULL,
};

extern void lin_diag_service_handle(void);
extern void lin_uncd_frame_handle(void);
extern void lin_master_frame_handle(void);

/********************************************************
** \brief   lin_master_frame_handle
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((weak)) void lin_master_frame_handle(void)
{
#if CFG_SUPPORT_LIN_MASTER
    //do noting
    // static bool test_flag = false;
    // uint8_t buffer[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    // if (!test_flag)
    // {
    //     lin_lld_sci_tx_master(0x01, buffer, 8);
    // }
    // else
    // {
    //     lin_lld_sci_rx_master(0x02, buffer, 8);

    // }

    // test_flag = !test_flag;
#endif
}

/********************************************************
** \brief   lin_uncd_frame_handle
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((weak)) void lin_uncd_frame_handle(void)
{
    //do noting
}

/********************************************************
** \brief   task_lin_handle
**
** \param   None
**
** \retval  None
*********************************************************/
static void task_lin_handle(void)
{
    lin_diag_service_handle();
    lin_uncd_frame_handle();
    lin_lld_sci_timeout();
#if CFG_SUPPORT_LIN_SNPD
    lin_snpd_process_handle();
#endif
}

#if CFG_SUPPORT_LIN_MASTER
/********************************************************
** \brief   task_lin_handle
**
** \param   None
**
** \retval  None
*********************************************************/
static void task_lin_master_handle(void)
{
    lin_master_frame_handle();
}
#endif

#if CFG_SUPPORT_LIN_SNPD
/********************************************************
** \brief   lin_task_busy_status
**
** \param   None
**
** \retval  bool
*********************************************************/
bool lin_task_busy_status(void)
{
    return (!!lin_snpd_status_get(LIN_AA_STATUS_STATE));
}
#if CFG_SUPPORT_LIN_SNPD_LED
/********************************************************
** \brief   color_snpd_enter
**
** \param   None
**
** \retval  None
*********************************************************/
static void color_recovery_snpd_enter(void)
{
    color_pwm_t color_pwm = {0};
    cm_target_Yxy_lighting_get(LED_CHANNEL_0, &target_color);
    cm_set_target_pwm(LED_CHANNEL_0, &color_pwm);
    cm_target_pwm_lighting(LED_CHANNEL_0);
}

/********************************************************
** \brief   color_snpd_exit
**
** \param   None
**
** \retval  None
*********************************************************/
static void color_recovery_snpd_exit(void)
{
    cm_set_target_Yxy(LED_CHANNEL_0, &target_color);
    cm_target_Yxy_lighting(LED_CHANNEL_0, 1);
}
#endif
#endif

/********************************************************
** \brief   lin_task_init
**
** \param   None
**
** \retval  None
*********************************************************/
void lin_task_init(void)
{
    lin_process_init();

#if CFG_SUPPORT_LIN_SNPD
#if CFG_SUPPORT_LIN_SNPD_LED
    lin_snpd_ctx.enter_func = color_recovery_snpd_enter;
    lin_snpd_ctx.exit_func = color_recovery_snpd_exit;
#endif /* __CFG_SUPPORT_LIN_SNPD_LED__*/
    lin_snpd_init(&lin_snpd_ctx);
#endif /* __CFG_SUPPORT_LIN_SNPD__*/
    OS_TASK_CREATE(task_lin_handle, 1, 1, 1);
#if CFG_SUPPORT_LIN_MASTER
    lin_sci_master_init();
    OS_TASK_CREATE(task_lin_master_handle, 20, 20, 1);
#endif
}
