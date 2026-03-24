/**
 *****************************************************************************
 * @brief   lin snpd example source file.
 *
 * @file    lin_snpd.c
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

#include "lin.h"
#include "lin_snpd.h"
#include "store_manager.h"
#include "pal_lin_comm.h"
#include "logging.h"

#define LOG_SPND(...)  do{log_debug("[SNPD] " __VA_ARGS__);}while(0)
#define LIN_SNPD_TIMEOUT   40000

lin_snpd_context_t *lin_snpd_ctx;

#if (SNPD_TEST_MODE == SNPD_TEST_MODE_LIN)
struct aa_adc_data adc_raw_data[AA_SLAVE_NUM];
#endif
/********************************************************
** \brief   lin_snpd_raw_adc_out
**
** \param   uint8_t                     org_nad
** \param   uint8_t                     new_nad
**
** \retval  None
*********************************************************/
void lin_snpd_raw_adc_out(uint8_t org_nad, uint8_t new_nad)
{
#if (SNPD_TEST_MODE == SNPD_TEST_MODE_PRINT)
    uint16_t raw_code[20] = {0};
    uint16_t length = pal_lin_aa_raw_code_get(raw_code, 4);

    for (uint16_t i = 1; i < length; i++)
    {
        LOG_SPND("nad = %d = %08x\r\n", new_nad, raw_code[i]);
    }

#elif (SNPD_TEST_MODE == SNPD_TEST_MODE_LIN)
    uint8_t count = 0;
    count = new_nad % 0x10;

    if (count > AA_SLAVE_NUM - 1)
    {
        count = 15;
    }

    adc_raw_data[count].org_nad = org_nad;
    adc_raw_data[count].new_nad = new_nad;

    for (uint8_t i = 0; i < 5; i++)
    {
        adc_raw_data[count].adc[i] = 0;
    }

    uint8_t raw_len = pal_lin_aa_raw_code_get(adc_raw_data[count].adc, 5);

    for (uint8_t i = raw_len; i < 5; i++)
    {
        adc_raw_data[count].adc[i] = 11;
    }

#else
    (void) org_nad;
    (void) new_nad;
#endif
}

/********************************************************
** \brief   lin_snpd_enter
**
** \param   None
**
** \retval  None
*********************************************************/
static void lin_snpd_enter(void)
{
#if CFG_SUPPORT_LIN_SNPD && CFG_SUPPORT_LIN_SNPD_LED

    if (NULL != lin_snpd_ctx->enter_func)
    {
        lin_snpd_ctx->enter_func();
    }

#endif
    uint16_t aa_cur_th[4];
    aa_cur_th[0] = ((g_sys_cfgs.cur_th_st12 & 0xFF00) >> 8) | ((g_sys_cfgs.cur_th_st12 & 0xFF) << 8);
    aa_cur_th[1] = ((g_sys_cfgs.cur_th_st12 & 0xFF000000) >> 24) | ((g_sys_cfgs.cur_th_st12 & 0xFF0000) >> 8);
    aa_cur_th[2] = ((g_sys_cfgs.cur_th_st34 & 0xFF00) >> 8) | ((g_sys_cfgs.cur_th_st34 & 0xFF) << 8);
    aa_cur_th[3] = ((g_sys_cfgs.cur_th_st34 & 0xFF000000) >> 24) | ((g_sys_cfgs.cur_th_st34 & 0xFF0000) >> 8);

    /* aa and colormix mutex */
//    meas_pn_sample_suspend(LED_CHANNLE_0);
    memset(lin_snpd_ctx->status, 0, LIN_AA_STATUS_MAX);
#if (SNPD_TEST_MODE == SNPD_TEST_MODE_LIN)
    memset(adc_raw_data, 0, AA_SLAVE_NUM * sizeof(struct aa_adc_data));
#endif
    pal_lin_aa_enter(aa_cur_th);

}

/********************************************************
** \brief   lin_snpd_exit
**
** \param   None
**
** \retval  None
*********************************************************/
static void lin_snpd_exit(void)
{
    pal_lin_aa_exit();
    /* aa and colormix mutex */
//    meas_pn_sample_resume(LED_CHANNLE_0);

#if CFG_SUPPORT_LIN_SNPD && CFG_SUPPORT_LIN_SNPD_LED

    if (NULL != lin_snpd_ctx->exit_func)
    {
        lin_snpd_ctx->exit_func();
    }

#endif
}

/********************************************************
** \brief   lin_snpd_select
**
** \param   None
**
** \retval  None
*********************************************************/
static void lin_snpd_select(void)
{
    pal_lin_aa_ready();
}

/********************************************************
** \brief   lin_snpd_status_get
**
** \param   lin_aa_status_e     type
**
** \retval  uint8_t
*********************************************************/
uint8_t lin_snpd_status_get(lin_aa_status_e type)
{
    if (type >= LIN_AA_STATUS_MAX)
    {
        return 0;
    }

    return (lin_snpd_ctx->status[type]);
}

#if (CFG_SUPPORT_LIN_SNPD_TIMEOUT && CFG_SUPPORT_LIN_SNPD)
/********************************************************
** \brief   lin_snpd_timeout
**
** \param   None
**
** \retval  void
*********************************************************/
static void lin_snpd_timeout_check(void)
{
    if (LIN_AA_STATE_IDLE != lin_snpd_status_get(LIN_AA_STATUS_STATE))
    {
        if (lin_snpd_ctx->timeout >= LIN_SNPD_TIMEOUT)
        {
            lin_snpd_status_set(LIN_AA_STATUS_STATE, LIN_AA_STATE_IDLE);
            lin_snpd_exit();
        }
        else
        {
            lin_snpd_ctx->timeout++;
        }
    }
    else
    {
        lin_snpd_ctx->timeout = 0;
    }
}
#endif

/********************************************************
** \brief   lin_snpd_status_get
**
** \param   lin_aa_status_e     type
** \param   uint8_t             value
**
** \retval  None
*********************************************************/
void lin_snpd_status_set(lin_aa_status_e type, uint8_t value)
{
    if (NULL == lin_snpd_ctx)
    {
        return;
    }

    if (type < LIN_AA_STATUS_MAX)
    {
        lin_snpd_ctx->status[type] = value;
    }
}

#if CFG_SUPPORT_LIN_SNPD
/********************************************************
** \brief   lin_snpd_process_handle
**
** \param   None
**
** \retval  None
*********************************************************/
void lin_snpd_process_handle(void)
{
    if (NULL == lin_snpd_ctx)
    {
        return;
    }

#if (CFG_SUPPORT_LIN_SNPD_TIMEOUT && CFG_SUPPORT_LIN_SNPD)
    /* timeout check */
    lin_snpd_timeout_check();
#endif

    uint8_t aa_step = lin_snpd_status_get(LIN_AA_STATUS_STEP);

    if (!aa_step)
    {
        return;
    }

    if (LIN_SNPD_CMD_ENTER == aa_step || LIN_SNPD_CMD_EXIT == aa_step)
    {
        if (LIN_SNPD_CMD_EXIT == aa_step)
        {
            lin_snpd_exit();
        }

        lin_snpd_status_set(LIN_AA_STATUS_STATE, LIN_AA_STATE_IDLE);
    }

    switch (lin_snpd_status_get(LIN_AA_STATUS_STATE))
    {
        case LIN_AA_STATE_IDLE:
            if (LIN_SNPD_CMD_ENTER == aa_step)
            {
                lin_snpd_enter();
                lin_snpd_status_set(LIN_AA_STATUS_STATE, LIN_AA_STATE_ENTER);
            }

            break;

        case LIN_AA_STATE_ENTER:
            if (LIN_SNPD_CMD_NAD == aa_step && lin_snpd_status_get(LIN_AA_STATUS_SELECT))
            {
                lin_configured_NAD = lin_snpd_status_get(LIN_AA_STATUS_NAD);
                lin_snpd_select();
                lin_snpd_status_set(LIN_AA_STATUS_SELECT, 0);
                lin_snpd_status_set(LIN_AA_STATUS_STATE, LIN_AA_STATE_SAVE);
            }

            if (lin_snpd_status_get(LIN_AA_STATUS_RAW_CODE))
            {
                lin_snpd_status_set(LIN_AA_STATUS_RAW_CODE, false);
                lin_snpd_raw_adc_out((uint8_t)g_sys_cfgs.org_nad, lin_snpd_status_get(LIN_AA_STATUS_NAD));
            }

            break;

        case LIN_AA_STATE_SAVE:
            if (LIN_SNPD_CMD_SAVE == aa_step)
            {
                /* 将new nad 保存到flash中to do */
                lin_snpd_nad_write(lin_configured_NAD);
                lin_snpd_status_set(LIN_AA_STATUS_STATE, LIN_AA_STATE_EXIT);
            }

            break;

        case LIN_AA_STATE_EXIT:
            if (LIN_SNPD_CMD_EXIT == aa_step)
            {
                lin_snpd_exit();
                lin_snpd_status_set(LIN_AA_STATUS_STATE, LIN_AA_STATE_IDLE);
            }

            break;

        default:
            break;
    }

    lin_snpd_status_set(LIN_AA_STATUS_STEP, 0);
}
#endif

/********************************************************
** \brief   lin_snpd_init
**
** \param   lin_snpd_context_t     ctx
**
** \retval  None
*********************************************************/
void lin_snpd_init(lin_snpd_context_t *ctx)
{
    lin_snpd_ctx = ctx;
}

/********************************************************
** \brief   autoaddress_config_for_dfu
**
** \param   None
**
** \retval  None
*********************************************************/
void autoaddress_config_for_dfu(void)
{
    uint32_t value = ll_timer_counter_get();
    lin_configured_NAD = value & 0x0F;
    lin_snpd_nad_write(lin_configured_NAD);
}

/********************************************************
** \brief   lin_snpd_nad_read
**
** \param   uint8_t*        nad
**
** \retval  None
*********************************************************/
void lin_snpd_nad_read(uint8_t *nad)
{
    *nad = (uint8_t)g_sys_cfgs.nad;
}

#ifdef CFG_LIN_CONFORM_TEST
/********************************************************
** \brief   lin_snpd_id_read
**
** \param   None
**
** \retval  None
*********************************************************/
void lin_snpd_id_read(void)
{
//    memcpy(lin_configuration_RAM, (*g_sys_cfgs.frame_id_cfg), SYSTEM_ID_CFG_SIZE);
}
#endif

/********************************************************
** \brief   lin_snpd_nad_write
**
** \param   uint8_t         nad
**
** \retval  None
*********************************************************/
void lin_snpd_nad_write(uint8_t nad)
{
    g_sys_cfgs.nad = nad;
    store_system_data_set(SYSTEM_CFG_PARAM, (uint8_t *)&g_sys_cfgs, SYSTEM_CFG_SIZE);
}

/********************************************************
** \brief   lin_snpd_cur_th_get
**
** \param   uint32_t*       st12
** \param   uint32_t*       st34
**
** \retval  None
*********************************************************/
void lin_snpd_cur_th_get(uint32_t *st12, uint32_t *st34)
{
    *st12 = g_sys_cfgs.cur_th_st12;
    *st34 = g_sys_cfgs.cur_th_st34;
}

/********************************************************
** \brief   lin_snpd_cur_th_set
**
** \param   uint32_t*       st12
** \param   uint32_t*       st34
**
** \retval  uint8_t
*********************************************************/
void lin_snpd_cur_th_set(uint32_t *st12, uint32_t *st34)
{
    g_sys_cfgs.cur_th_st12 = *st12;
    g_sys_cfgs.cur_th_st34 = *st34;

    store_system_data_set(SYSTEM_CFG_PARAM, (uint8_t *)&g_sys_cfgs, SYSTEM_CFG_SIZE);
}
