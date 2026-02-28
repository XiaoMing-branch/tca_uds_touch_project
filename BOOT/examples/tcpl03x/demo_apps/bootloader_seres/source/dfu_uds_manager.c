/**
 *****************************************************************************
 * @brief   dfu_uds_manager source file.
 *
 * @file    dfu_uds_manager.c
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

#include "dfu_uds_manager.h"
#include "pal_systick.h"
#include "pal_lin_comm.h"
#include "pal_lin_tl.h"
#include "pal_store.h"
#include "pal_wdg.h"
#include "aes_cmac.h"
#include "utilities.h"
#include "logging.h"

#define CFG_SUPPORT_DEBUG 0

#if 1 == CFG_SUPPORT_DEBUG
#define LOG_DFU(...)                     \
    do                                   \
    {                                    \
        log_debug("[DFU] " __VA_ARGS__); \
    } while (0)
#else
#define LOG_DFU(...)
#endif

__attribute__((section(".ARM.__at_0x00003900"))) const uint8_t boot_version[8u] = {'B', 'T', ':', 'B', '.', '0', '1', 0x20u};
__attribute__((section(".ARM.__at_0x00003908"))) const uint8_t hardware_version[8u] = {'H', 'W', ':', 'B', '.', '1', '.', '0'};
__attribute__((section(".ARM.__at_0x10000000"))) uint8_t flash_driver[66u] = {0u};

uint8_t seed[16u] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};
uint8_t key[16u] = { 0x88, 0xB3, 0x4F, 0x45, 0xE1, 0x0D, 0xBB, 0xC3, 0x5D, 0xBF, 0x7E, 0xCF, 0x86, 0x8E, 0x73, 0x60};

uint8_t seed_use[16u] = {0u};
uint8_t flash_driver_cmac[16u] = {0u};
uint8_t app_cmac[16u] = {0u};
uint8_t g_config_word_state;
user_cfg_t g_user_info = {0u};
ota_cfg_t g_ota_info = {0u};
uint8_t g_negResponseCode;
uint8_t diagnosticTxBuffer[CUS_UDS_SEND_BUFFER_SIZE];
dfu_manager_context_t dfu_ctx = {0u};
uint8_t lin_configured_NAD = 0x68u;
volatile uint16_t timer_1s_cnt = 0u;
uint16_t lock_failed_cnt = 0u;

ServiceUDS_TypeDef uds_request_info =
{
    .sessionMode = DEFALUT_SESSION,
};

uint8_t seed_cmac_succ = AS_FALSE;
uint8_t flashdrv_cmac_succ = AS_FALSE;
uint8_t app_cmac_succ = AS_FALSE;
uint8_t seed_00_ret = AS_FALSE;
uint8_t app_cmac_start = AS_FALSE;
uint8_t unlock_failed_store_flag = AS_FALSE;
uint8_t diagnostic_session_overtime_flag = AS_FALSE;
extern void lin_lld_isr_callback(uint32_t isr);

/********************************************************
** \brief   JumpToApp
**
** \param   None
**
** \retval  None
*********************************************************/
static void JumpToApp(void)
{
    NVIC_DisableIRQ(TIMER_IRQn);
    NVIC_DisableIRQ(LINSCI_IRQn);
    NVIC_DisableIRQ(SysTick_IRQn);
    pal_lin_deinit(LIN_BUS_0);
#ifdef CFG_SUPPORT_DEBUG
    logging_deinit();
#endif
    FUNC_PTR pAppFunc = (FUNC_PTR) * (uint32_t *)(FLASH_APP_ADDR + 0x100u + 4u); /* APP 头部0x100大小为用户数据*/
    __set_MSP(*(uint32_t *)(FLASH_APP_ADDR + 0x100u));
    pAppFunc();
}

/********************************************************
** \brief   queue_lin_empty
**
** \param   None
**
** \retval  uint8_t
*********************************************************/
static uint8_t queue_lin_empty(void)
{
    return ((dfu_ctx.queue_list.head == dfu_ctx.queue_list.tail) ? 1 : 0);
}

/********************************************************
** \brief   dfu_image_erase
**
** \param   None
**
** \retval  uint8_t
*********************************************************/
static uint8_t dfu_image_erase(void)
{
    if (ll_flash_erase_drv(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, FLASH_DFU_INFO_SIZE + FLASH_APP_IMAGE_SIZE))
    {
        return DFU_MSG_SUCCESS;
    }

    return DFU_MSG_ERASE_ERROR;
}

/********************************************************
** \brief   dfu_image_program
**
** \param   uint32_t            addr
** \param   packet_unit_t*      buffer
** \param   uint32_t            length
**
** \retval  uint8_t
*********************************************************/
static uint8_t dfu_image_program(uint32_t addr, uint8_t *data, uint16_t length)
{
    if ((addr < FLASH_APP_ADDR) || (addr >= FLASH_APP_END_ADDR))
    {
        return DFU_MSG_PROGRA_ERROR;
    }

    uint8_t res = DFU_MSG_SUCCESS;
    ll_flash_write_drv(FLASH_TYPE_NVM, addr, data, length);

    return (res);
}
/********************************************************
** \brief   dfu_do_notify_cp
**
** \param   uint8_t     sid
** \param   uint8_t     sub_func
** \param   uint8_t*    data
** \param   uint16_t    length
**
** \retval  None
*********************************************************/
static void dfu_do_notify_cp(uint8_t sid, uint8_t sub_func, uint8_t *data, uint16_t length)
{
    uint8_t response[20u];
    uint8_t len = 2u + length;

    response[0u] = sid + 0x40u;
    response[1u] = sub_func;

    for (uint16_t i = 0u; i < length; i++)
    {
        response[2u + i] = data[i];
    }

    lin_uds_send(lin_configured_NAD, response, len);
}

static void dfu_do_notify_cp_ex(uint8_t sid, uint8_t *data, uint16_t length)
{
    uint8_t response[40u];
    uint8_t len = 1u + length;

    response[0u] = sid + 0x40u;

    for (uint16_t i = 0u; i < length; i++)
    {
        response[1u + i] = data[i];
    }

    lin_uds_send(lin_configured_NAD, response, len);
}

/********************************************************
** \brief   dfu_do_notify_response
**
** \param   uint8_t     resp_type
** \param   uint8_t     sid
** \param   uint8_t     resp_value
**
** \retval  None
*********************************************************/
static void dfu_do_notify_response(uint8_t resp_type, uint8_t sid, uint8_t resp_value)
{
    if (POSITIVE == resp_type)
    {
        dfu_do_notify_cp(sid, resp_value, NULL, 0u);
    }
    else
    {
        lin_uds_negative_response(lin_configured_NAD, sid, resp_value);
    }
}

/********************************************************
** \brief   session control response (SID=0x10)
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/

void dfu_session_parameter_resp(uint8_t sessiontype)
{
    uint8_t session_parameter[4u];
    session_parameter[0u] = (P2_SERVER_MAX >> 8u) & 0xFFu;
    session_parameter[1u] = (P2_SERVER_MAX & 0xFFu);
    session_parameter[2u] = (P2E_SERVER_MAX >> 8u) & 0xFFu;
    session_parameter[3u] = (P2E_SERVER_MAX & 0xFFu);
    dfu_do_notify_cp(0x10u, sessiontype, session_parameter, sizeof(session_parameter));
}

/********************************************************
** \brief   last_dfu_info_get
**
** \param   last_dfu_info_t*        info
**
** \retval  uint8_t
*********************************************************/
static uint8_t last_dfu_info_get(void)
{
    pal_store_read(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)&dfu_ctx.dfu_info, sizeof(last_dfu_info_t));

    if (DFU_INFO_MAGIC != dfu_ctx.dfu_info.magic)
    {
        return DFU_MSG_ERROR;
    }
    if ((g_ota_info.app_req_ext_program_flag == 0x01u) || (g_ota_info.app_req_ext_program_flag == 0x03u))
    {
        dfu_ctx.op_code = DFU_CMD_PROGRAM_SESSION;
        uds_request_info.sessionMode = PROGRAM_SESSION;
        if (g_ota_info.app_req_ext_program_flag == 0x01u)
        {
            dfu_session_parameter_resp(0x02u);
            delay_ms(1u);
        }
        g_ota_info.app_req_ext_program_flag = 0x00u;
        pal_store_data_set(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
        return DFU_MSG_ERROR;
    }

    return DFU_MSG_SUCCESS;
}

static uint8_t uds_diag_DID_chk(uint16_t ucSess)
{
    uint8_t ucRet;
    switch (ucSess)
    {
    /* Seres part num:6106150-RQ01 */
    case 0xF187u:
    /* Seres 供应商code:3233 */
    case 0xF18Au:
    /* Seres ECU name:EHIS_FL */
    case 0xF197u:
    case 0xF089u:
    case 0xF180u:
    case 0xF184u:
        ucRet = 1u;
        break;
    case 0xF189u:
    case 0x0216u:
        // 判断APP标志位是否有效，如果无效，则表明APP不存在，响应NRC31
        pal_store_read(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)&dfu_ctx.dfu_info, sizeof(last_dfu_info_t));
        if (DFU_INFO_MAGIC == dfu_ctx.dfu_info.magic)
        {
            ucRet = 1u;
            break;
        }
    default:
        ucRet = 0u;
        break;
    }
    return ucRet;
}

void uds_diagnostic_configword_remap_nad(void)
{
    uint8_t nad_temp = g_user_info.nad_info;

    if ((nad_temp == 0x68u) || (nad_temp == 0x6Au) ||
            (nad_temp == 0x69u) || (nad_temp == 0x6Bu))
    {
        lin_configured_NAD = nad_temp;
    }
    else
    {
        lin_configured_NAD = 0x68;
    }

    if (g_ota_info.lock_failed_index > 3u) /* 参数合理性检查 */
    {
        g_ota_info.lock_failed_index = 0u;
    }
    LOG_DFU("lock index =%d\r\n", g_ota_info.lock_failed_index);
}

/********************************************************
** \brief   last_dfu_info_update
**
** \param   last_dfu_info_t*        info
**
** \retval  uint8_t
*********************************************************/
static uint8_t last_dfu_info_update(last_dfu_info_t *info)
{
    ll_flash_write_drv(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)info, sizeof(last_dfu_info_t));
    return (DFU_MSG_SUCCESS);
}

/********************************************************
** \brief   dfu_process_exit
**
** \param   uint8_t     reason
**
** \retval  None
*********************************************************/
static void dfu_process_exit(uint8_t reason)
{
    if (DFU_MSG_SUCCESS == reason)
    {
        dfu_ctx.dfu_info.magic = DFU_INFO_MAGIC;
        last_dfu_info_update(&dfu_ctx.dfu_info);
    }
}
/********************************************************
** \brief   session_control_handle
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void session_control_handle(uint8_t *param, uint16_t length)
{
    if (length == BOOT_Frame_length_2)
    {
        switch (param[1u])
        {
        case 0x01u:
        case 0x81u:
            if (uds_request_info.sessionMode == PROGRAM_SESSION)
            {
                pal_store_read(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)&dfu_ctx.dfu_info, sizeof(last_dfu_info_t));
                if (DFU_INFO_MAGIC == dfu_ctx.dfu_info.magic) // APP标志位有效的情况下，才允许复位，否则就停留在BootLoader
                {
                    if ((param[1] == 0x81u) || (lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu)) // 抑制正响应或功能寻址直接复位
                    {
                        NVIC_SystemReset();
                    }
                    else // 01则记录标志位，用于APP响应50 01
                    {
                        pal_store_data_get(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                        if (g_ota_info.app_need_res_flag != true)
                        {
                            g_ota_info.app_need_res_flag = true;
                            pal_store_data_set(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                        }
                        delay_ms(5u);
                        NVIC_SystemReset();
                    }
                }
                else
                {
                    dfu_ctx.op_code = DFU_CMD_DEFAULT_SESSION;
                    uds_request_info.sessionMode = DEFALUT_SESSION;
                    seed_cmac_succ = AS_FALSE;
                    seed_00_ret = AS_FALSE;
                }
            }
            else
            {
                dfu_ctx.op_code = DFU_CMD_DEFAULT_SESSION;
                uds_request_info.sessionMode = DEFALUT_SESSION;
                seed_cmac_succ = AS_FALSE;
                seed_00_ret = AS_FALSE;
            }
            if ((uds_request_info.sessionMode == DEFALUT_SESSION) && (param[1u] == 0x01u))
            {
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_session_parameter_resp(param[1u]);
                }
            }
            break;
        case 0x03u:
            if (uds_request_info.sessionMode != PROGRAM_SESSION)
            {
                uds_request_info.sessionMode = EXTEND_SESSION;
                dfu_ctx.op_code = DFU_CMD_EXTEND_SESSION;
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_session_parameter_resp(param[1u]);
                }
            }
            else
            {
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOTSUPPORTED_INACTIVESESSION); // NRC7E
                }
            }
            seed_cmac_succ = AS_FALSE;
            seed_00_ret = AS_FALSE;
            break;
        case 0x83u:
            uds_request_info.sessionMode = EXTEND_SESSION;
            dfu_ctx.op_code = DFU_CMD_EXTEND_SESSION;
            seed_cmac_succ = AS_FALSE;
            seed_00_ret = AS_FALSE;
            break;
        case 0x02u:
        case 0x82u:
            if (dfu_ctx.op_code >= DFU_CMD_ROUTINE_PROGRAM_CHECK)
            {
                dfu_ctx.op_code = DFU_CMD_PROGRAM_SESSION;
                uds_request_info.sessionMode = PROGRAM_SESSION;
                dfu_ctx.boot_state = BOOT_STATE_UPGRADE;
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_session_parameter_resp(0x02u);
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
            }
            seed_cmac_succ = AS_FALSE;
            seed_00_ret = AS_FALSE;
            break;
        default:
            if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
            {
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
            }
            break;
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

/********************************************************
** \brief   cpmpare_key
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static uint8_t cpmpare_key(uint8_t *seed, uint8_t *key, uint8_t length)
{
    /*compare key seed*/
    for (uint8_t i = 0u; i < length; i++)
    {
        if (seed[i] != key[i])
        {
            return 0u;
        }
    }
    return 1u;
}

static void key_reset_by_nad(void)
{
    uint8_t key_lf[16] = {
        0x88, 0xB3, 0x4F, 0x45,
        0xE1, 0x0D, 0xBB, 0xC3,
        0x5D, 0xBF, 0x7E, 0xCF,
        0x86, 0x8E, 0x73, 0x60
    };
    uint8_t key_rf[16] = {
        0x32, 0xA9, 0x83, 0x03,
        0xAD, 0x07, 0xAE, 0x9C,
        0x2B, 0x46, 0x1F, 0xDE,
        0x1D, 0xA5, 0x46, 0x76
    };
    uint8_t key_lr[16] = {
        0x48, 0x54, 0x24, 0xF9,
        0xF5, 0x76, 0x3E, 0x2B,
        0x99, 0x87, 0xD0, 0x11,
        0x1A, 0x8B, 0xD2, 0x82
    };
    uint8_t key_rr[16] = {
        0x2A, 0x7E, 0xF5, 0x25,
        0x7E, 0x01, 0xE6, 0x06,
        0xCD, 0x0C, 0x68, 0xFE,
        0xA0, 0x3E, 0x5E, 0x5C
    };

    if (g_user_info.nad_info == 0x68)
    {
        memcpy(key, key_lf, sizeof(key_lf));
    }
    else if (g_user_info.nad_info == 0x69)
    {
        memcpy(key, key_rf, sizeof(key_rf));
    }
    else if (g_user_info.nad_info == 0x6A)
    {
        memcpy(key, key_lr, sizeof(key_lr));
    }
    else if (g_user_info.nad_info == 0x6B)
    {
        memcpy(key, key_rr, sizeof(key_rr));
    }
}

/********************************************************
** \brief   security_access_handle
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void security_access_handle(uint8_t *param, uint16_t length)
{
    uint8_t out[16u];
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if ((length == BOOT_Frame_length_2) || (length == BOOT_Frame_length_18))
    {
        if (uds_request_info.sessionMode == PROGRAM_SESSION)
        {
            switch (param[1u])
            {
            case 0x09u:
                if (length == BOOT_Frame_length_2)
                {
                    if (g_ota_info.lock_failed_index < 3u)
                    {
                        if (seed_cmac_succ == AS_TRUE)
                        {
                            if (seed_00_ret == AS_TRUE)
                            {
                                seed_cmac_succ = AS_FALSE;
                                seed_00_ret = AS_FALSE;
                                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_SEQUEENCE_ERROR); // NRC24
                            }
                            else
                            {
                                for (uint8_t i = 0u; i < 16u; i++)
                                {
                                    seed_use[i] = 0u;
                                }
                                dfu_do_notify_cp(param[0u], param[1u], (unsigned char *)seed_use, sizeof(seed_use));
                                seed_00_ret = AS_TRUE;
                            }
                        }
                        else
                        {
                            if ((dfu_ctx.op_code == DFU_CMD_PROGRAM_SESSION) || (dfu_ctx.op_code == DFU_CMD_SECURITY_SEED_REQUEST))
                            {
                                for (uint8_t i = 0u; i < 16u; i++)
                                {
                                    seed_use[i] = seed[i];
                                }
                                dfu_ctx.op_code = DFU_CMD_SECURITY_SEED_REQUEST;

                                dfu_do_notify_cp(param[0u], param[1u], (unsigned char *)seed_use, sizeof(seed_use));
                            }
                            else
                            {
                                seed_cmac_succ = AS_FALSE;
                                seed_00_ret = AS_FALSE;
                                dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
                            }
                        }
                    }
                    else
                    {
                        seed_cmac_succ = AS_FALSE;
                        seed_00_ret = AS_FALSE;
                        dfu_ctx.op_code = DFU_CMD_PROGRAM_SESSION;
                        dfu_do_notify_response(NEGATIVE, param[0u], REQUIREDTIMEDELAY_NOTEXPIRED); // NRC37
                    }
                }
                else
                {
                    seed_cmac_succ = AS_FALSE;
                    seed_00_ret = AS_FALSE;
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
                break;
            case 0x0au:
                if (length == BOOT_Frame_length_18)
                {
                    if (dfu_ctx.op_code == DFU_CMD_SECURITY_SEED_REQUEST)
                    {
                        key_reset_by_nad();
                        aes_cmac(key, seed_use, sizeof(seed_use), (unsigned char *)out);
                        if (cpmpare_key(out, &param[2u], 16u) == 1u)
                        {
                            dfu_ctx.op_code = DFU_CMD_SECURITY_KEY_CHECK;
                            seed_cmac_succ = AS_TRUE;
                            // 解锁成功，清除27解锁失败次数计数器
                            pal_store_data_get(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                            g_ota_info.lock_failed_index = 0u;
                            pal_store_data_set(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                            dfu_do_notify_response(POSITIVE, param[0u], param[1u]);
                        }
                        else
                        {
                            dfu_ctx.op_code = DFU_CMD_PROGRAM_SESSION;
                            if (g_ota_info.lock_failed_index < 3u)
                            {
                                //  解锁失败，27解锁失败次数计数器存到flash里
                                pal_store_data_get(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                                g_ota_info.lock_failed_index++;
                                // pal_store_data_set(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                            }
                            if (g_ota_info.lock_failed_index <= 2u)
                            {
                                seed_cmac_succ = AS_FALSE;
                                seed_00_ret = AS_FALSE;
                                dfu_do_notify_response(NEGATIVE, param[0], INVALID_KEY); // NRC35
                            }
                            else if (g_ota_info.lock_failed_index == 3u)
                            {
                                seed_cmac_succ = AS_FALSE;
                                seed_00_ret = AS_FALSE;
                                dfu_do_notify_response(NEGATIVE, param[0u], ENOA); // NRC36
                            }
                            else
                            {
                                seed_cmac_succ = AS_FALSE;
                                seed_00_ret = AS_FALSE;
                                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_SEQUEENCE_ERROR); // NRC24
                                break;
                            }
                            pal_store_data_set(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
                        }
                    }
                    else
                    {
                        seed_cmac_succ = AS_FALSE;
                        seed_00_ret = AS_FALSE;
                        dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_SEQUEENCE_ERROR); // NRC24
                    }
                }
                else
                {
                    seed_cmac_succ = AS_FALSE;
                    seed_00_ret = AS_FALSE;
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
                break;
            default:
                seed_cmac_succ = AS_FALSE;
                seed_00_ret = AS_FALSE;
                dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
                break;
            }
        }
        else
        {
            seed_cmac_succ = AS_FALSE;
            seed_00_ret = AS_FALSE;
            dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
        }
    }
    else
    {
        seed_cmac_succ = AS_FALSE;
        seed_00_ret = AS_FALSE;
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

/********************************************************
** \brief   firmware_info_sync_handle
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void firmware_info_sync_handle(uint8_t *param, uint16_t length)
{
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if (length > BOOT_Frame_length_3)
    {
        if (uds_request_info.sessionMode == PROGRAM_SESSION)
        {
            if ((param[1u] == 0xF1u) && (param[2u] == 0x84u))
            {
                if (length == BOOT_Frame_length_13)
                {
                    if ((dfu_ctx.op_code == DFU_CMD_SECURITY_KEY_CHECK) && (seed_cmac_succ == AS_TRUE))
                    {
                        dfu_ctx.op_code = DFU_CMD_WRITE_FINGER;
                        memcpy(dfu_ctx.dfu_info.fingerprint, &param[3u], 10u);
                        dfu_do_notify_cp(param[0u], param[1u], &param[2u], 1u);
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], SECURITY_ACCESS_DENIED); // NRC33
                    }
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

/********************************************************
** \brief   request_download_handle
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void request_download_handle(uint8_t *param, uint16_t length)
{
    uint8_t req_down_resp[2u];
    uint32_t req_addr = 0u;
    uint32_t req_size = 0u;
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if (uds_request_info.sessionMode == PROGRAM_SESSION)
    {
        if (length == BOOT_Frame_length_11)
        {
            if (seed_cmac_succ == AS_TRUE)
            {
                if (param[1] == 0x00u)
                {
                    if (param[2] == 0x44u)
                    {
                        req_addr = (param[3u] << 24u) | (param[4u] << 16u) | (param[5u] << 8u) | param[6u];
                        req_size = (param[7u] << 24u) | (param[8u] << 16u) | (param[9u] << 8u) | param[10u];
                        if ((dfu_ctx.op_code == DFU_CMD_WRITE_FINGER) || (dfu_ctx.op_code == DFU_CMD_SECURITY_KEY_CHECK))
                        {
                            if ((req_addr == FLASH_DRIVER_ADDR) && (req_size == FLASH_DRIVER_LENGTH))
                            {
                                dfu_ctx.flashdrv_write_addr = req_addr;
                                dfu_ctx.flashdrv_write_size = req_size;
                                dfu_ctx.op_code = DFU_CMD_FLASH_DRIVER_REQUEST;

                                dfu_ctx.write_length = 0u;
                                dfu_ctx.receive_length = 0u;

                                dfu_ctx.queue_list.tail = 0u;
                                dfu_ctx.queue_list.head = 0u;
                                dfu_ctx.recevice_index = 0x01u;
                                dfu_ctx.write_index = 0u;

                                req_down_resp[0] = 0x02u;
                                req_down_resp[1] = 0x02u;
                                dfu_do_notify_cp(param[0u], 0x20u, req_down_resp, sizeof(req_down_resp));
                                LOG_DFU("add=0x%x, size=0x%x\n", req_addr, req_size);
                            }
                            else
                            {
                                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
                            }
                        }
                        else if (dfu_ctx.op_code == DFU_CMD_APP_ERASE)
                        {
                            dfu_ctx.write_addr = req_addr;
                            dfu_ctx.dfu_info.image_size = req_size;
                            if (FLASH_APP_ADDR == dfu_ctx.write_addr)
                            {
                                dfu_ctx.op_code = DFU_CMD_APP_REQUEST;

                                dfu_ctx.write_length = 0u;
                                dfu_ctx.receive_length = 0u;

                                dfu_ctx.queue_list.tail = 0u;
                                dfu_ctx.queue_list.head = 0u;
                                dfu_ctx.recevice_index = 0x01u;
                                dfu_ctx.write_index = 0u;

                                req_down_resp[0] = 0x02u;
                                req_down_resp[1] = 0x02u;
                                dfu_do_notify_cp(param[0u], 0x20u, req_down_resp, sizeof(req_down_resp));
                                LOG_DFU("add=0x%x, size=0x%x\n", req_addr, req_size);
                            }
                            else
                            {
                                LOG_DFU("nrc31=0x%x, size=0x%x\n", req_addr, req_size);
                                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
                            }
                        }
                        else
                        {
                            dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
                        }
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
                    }
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SECURITY_ACCESS_DENIED); // NRC33
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
    }
}

/********************************************************
** \brief   transfer_data_handle
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void transfer_data_handle(uint8_t *param, uint16_t length)
{
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if (uds_request_info.sessionMode == PROGRAM_SESSION)
    {
        if (length <= 0x202u)
        {
            if ((dfu_ctx.op_code == DFU_CMD_FLASH_DRIVER_REQUEST) || (dfu_ctx.op_code == DFU_CMD_FLASH_DRIVER_TRANSFER))
            {
                dfu_ctx.op_code = DFU_CMD_FLASH_DRIVER_TRANSFER;
                memcpy(flash_driver, &param[2u], dfu_ctx.flashdrv_write_size);
                LOG_DFU("drv len=%d\n", dfu_ctx.flashdrv_write_size);
                dfu_do_notify_response(POSITIVE, param[0u], param[1u]);
            }
            else if ((dfu_ctx.op_code == DFU_CMD_APP_REQUEST) || (dfu_ctx.op_code == DFU_CMD_APP_TRANSFER))
            {
                dfu_ctx.op_code = DFU_CMD_APP_TRANSFER;
                dfu_ctx.recevice_index = param[1u];
                dfu_ctx.receive_length += (length - 2u);
                dfu_ctx.program_flag = 1u;
                if (DFU_MSG_SUCCESS == dfu_image_program(dfu_ctx.write_addr, &param[2u], length - 2u))
                {
                    if ((++(dfu_ctx.queue_list.head)) >= QUEUE_LIN_LEN)
                    {
                        dfu_ctx.queue_list.head = 0u;
                    }

                    dfu_ctx.write_index = dfu_ctx.recevice_index;

                    dfu_ctx.write_addr += (length - 2u);
                    dfu_ctx.write_length += (length - 2u);
                    dfu_do_notify_response(POSITIVE, param[0u], param[1u]);
                }
                else
                {
                    dfu_ctx.queue_list.tail = 0u;
                    dfu_ctx.queue_list.head = 0u;
                    dfu_do_notify_response(NEGATIVE, param[0u], GENERAL_PROGRAM_FAILURE); // NRC72
                    LOG_DFU("write error\r\n");
                }

                if ((dfu_ctx.receive_length >= DFU_PROGRAM_LENGTH) ||
                        ((dfu_ctx.receive_length + dfu_ctx.write_length) == dfu_ctx.dfu_info.image_size))
                {
                    if ((++(dfu_ctx.queue_list.tail)) >= QUEUE_LIN_LEN)
                    {
                        dfu_ctx.queue_list.tail = 0u;
                    }
                }
                if (dfu_ctx.write_length == dfu_ctx.dfu_info.image_size) // 避免多发
                {
                    dfu_ctx.queue_list.tail = 0u; // 队列清空
                    dfu_ctx.queue_list.head = 0u;
                }
                LOG_DFU("app index=%d len=%d\n", dfu_ctx.recevice_index, length);
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
    }
}

/********************************************************
** \brief   pal_lin_init
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void request_transfer_exit_handle(uint8_t *param, uint16_t length)
{
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if (uds_request_info.sessionMode == PROGRAM_SESSION)
    {
        if (length == BOOT_Frame_length_1)
        {
            if (dfu_ctx.op_code == DFU_CMD_FLASH_DRIVER_TRANSFER)
            {
                dfu_ctx.op_code = DFU_CMD_FLASH_DRIVER_EXIT;
                dfu_do_notify_cp_ex(param[0u], NULL, 0u);
            }
            else if (dfu_ctx.op_code == DFU_CMD_APP_TRANSFER)
            {
                dfu_ctx.op_code = DFU_CMD_APP_EXIT;
                dfu_do_notify_cp_ex(param[0u], NULL, 0u);
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_SEQUEENCE_ERROR); // NRC24
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
    }
}

/********************************************************
** \brief   routine_control_handle
**
** \param   uint8_t*        param
** \param   uint16_t        length
**
** \retval  None
*********************************************************/
static void routine_control_handle(uint8_t *param, uint16_t length)
{
    uint8_t pre_program_resp[3u] = {0u};
    uint8_t data_tmp[32u] = {0u};

    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if ((0x01u == param[1u]) || (0x81u == param[1u]))
    {
        uint16_t routine_id = (param[2u] << 8u) | param[3u];
        param[1u] = 0x01u;
        switch (routine_id)
        {
        case 0x0203u:
            if (uds_request_info.sessionMode == EXTEND_SESSION)
            {
                if (length == BOOT_Frame_length_4)
                {
                    if ((dfu_ctx.op_code == DFU_CMD_EXTEND_SESSION) || (dfu_ctx.op_code == DFU_CMD_ROUTINE_PROGRAM_CHECK))
                    {
                        dfu_ctx.op_code = DFU_CMD_ROUTINE_PROGRAM_CHECK;
                        pre_program_resp[0u] = param[2u];
                        pre_program_resp[1u] = param[3u];
                        pre_program_resp[2u] = 0u;
                        dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, sizeof(pre_program_resp));
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
                    }
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
            }
            break;
        case 0xDD02u: // 签名校验
            if (uds_request_info.sessionMode == PROGRAM_SESSION)
            {
                if (length == BOOT_Frame_length_20)
                {
                    if (dfu_ctx.op_code == DFU_CMD_FLASH_DRIVER_EXIT)
                    {
                        sha256(flash_driver, dfu_ctx.flashdrv_write_size, data_tmp);
                        aes_cmac(key, data_tmp, 32, (uint8_t *)flash_driver_cmac);

                        if (cpmpare_key(flash_driver_cmac, &param[4u], 16u) == 1u)
                        {
                            dfu_ctx.op_code = DFU_CMD_FLASH_DRIVER_CMAC_CHECK;
                            flashdrv_cmac_succ = AS_TRUE;
                            pre_program_resp[0u] = param[2u];
                            pre_program_resp[1u] = param[3u];
                            pre_program_resp[2u] = 0u;
                            dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, sizeof(pre_program_resp));
                        }
                        else
                        {
                            flashdrv_cmac_succ = AS_FALSE;
                            pre_program_resp[0u] = param[2u];
                            pre_program_resp[1u] = param[3u];
                            pre_program_resp[2u] = 1u;
                            dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, sizeof(pre_program_resp));
                        }
                    }
                    else if (dfu_ctx.op_code == DFU_CMD_APP_EXIT)
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], RCRRP); // NRC78
                        timer_1s_cnt = 0u;
                        app_cmac_start = AS_TRUE;
                        sha256((uint8_t *)FLASH_APP_ADDR, dfu_ctx.dfu_info.image_size, data_tmp);
                        aes_cmac(key, data_tmp, 32, (uint8_t *)app_cmac);

                        app_cmac_start = AS_FALSE;
                        if (cpmpare_key(app_cmac, &param[4u], 16u) == 1u)
                        {
                            dfu_ctx.op_code = DFU_CMD_APP_CMAC_CHECK;
                            app_cmac_succ = AS_TRUE;
                            pre_program_resp[0u] = param[2u];
                            pre_program_resp[1u] = param[3u];
                            pre_program_resp[2u] = 0u;
                            dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, sizeof(pre_program_resp));
                        }
                        else
                        {
                            app_cmac_succ = AS_FALSE;
                            pre_program_resp[0u] = param[2u];
                            pre_program_resp[1u] = param[3u];
                            pre_program_resp[2u] = 1u;
                            dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, sizeof(pre_program_resp));
                        }
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
                    }
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
            }
            break;
        case 0xFF00u: // 擦除FLASH
            if (uds_request_info.sessionMode == PROGRAM_SESSION)
            {
                if (length == BOOT_Frame_length_12)
                {
                    if ((dfu_ctx.op_code == DFU_CMD_FLASH_DRIVER_CMAC_CHECK) && (flashdrv_cmac_succ == AS_TRUE))
                    {
                        lin_uds_negative_response(lin_configured_NAD, param[0u], RCRRP);
                        delay_ms(90u);
                        dfu_image_erase();
                        dfu_ctx.op_code = DFU_CMD_APP_ERASE;
                        pre_program_resp[0u] = param[2u];
                        pre_program_resp[1u] = param[3u];
                        dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, 2u);
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
                    }
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
            }
            break;
        case 0xFF01u: // 应用程序兼容性检查
            if (uds_request_info.sessionMode == PROGRAM_SESSION)
            {
                if (length == BOOT_Frame_length_4)
                {
                    if ((dfu_ctx.op_code == DFU_CMD_APP_CMAC_CHECK) && (app_cmac_succ == AS_TRUE))
                    {
                        dfu_ctx.op_code = DFU_CMD_APP_COMPATIBLE_CHECK;
                        pre_program_resp[0u] = param[2u];
                        pre_program_resp[1u] = param[3u];
                        pre_program_resp[2u] = 0u;
                        /* 更新APP标志位*/
                        dfu_process_exit(DFU_MSG_SUCCESS);
                        dfu_do_notify_cp(param[0u], param[1u], (uint8_t *)pre_program_resp, sizeof(pre_program_resp));
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], CONDITION_NOT_CORRECT); // NRC22
                    }
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
            }
            break;
        default:
            dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
            break;
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
    }
}

static void reset_handle(uint8_t *param, uint16_t length)
{
    if (length == BOOT_Frame_length_2)
    {
        if (param[1] == 0x01u)
        {
            if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
            {
            }
            else
            {
                dfu_do_notify_response(POSITIVE, param[0], param[1]);
            }

            delay_ms(50u);
            NVIC_SystemReset();
        }
        else if (param[1] == 0x81u)
        {
            NVIC_SystemReset();
        }
        else
        {
            if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
            {
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
            }
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

static void clear_dtc_info_handle(uint8_t *param, uint16_t length)
{
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
    }
}

static void enable_swd(void) // 使能swd接口
{
    ll_gpio_afio_config(GPIO_PIN_0, AFIO_MUX_0); // SWCLK
    ll_gpio_afio_config(GPIO_PIN_1, AFIO_MUX_0); // SWDIO
}

static void assign_config_word_handle(uint8_t *param, uint16_t length)
{
    uint8_t fuc_id;
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if (length == BOOT_Frame_length_6)
    {
        if ((0xF3u == param[1u]) && (0x3F == param[2u]) && (0x02u == param[4u]))
        {
            // if (seed_cmac_succ == AS_TRUE)
            //{
            fuc_id = param[3u];
            switch (fuc_id)
            {
            case 0x01u:
                /* start */
                g_config_word_state = CONFIGURE_WORD_STATE_START;
                break;

            case 0x02u:
                /* assign */
                if (g_config_word_state == CONFIGURE_WORD_STATE_START)
                {
                    if ((param[5u] == LEFT_FRONT_DOOR) || (param[5u] == LEFT_REAR_DOOR) ||
                            (param[5u] == RIGHT_FRONT_DOOR) || (param[5u] == RIGHT_REAR_DOOR))
                    {
                        g_user_info.config_word = param[5u];

                        g_config_word_state = CONFIGURE_WORD_STATE_ASIGN;
                        LOG_DFU("cfg %x\n", g_user_info.config_word);
                    }
                }
                break;

            case 0x03u:
                /* save */
                if (g_config_word_state == CONFIGURE_WORD_STATE_ASIGN)
                {
                    pal_store_data_set(CFG_WORD_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
                    pal_store_data_get(CFG_WORD_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
                    uds_diagnostic_configword_remap_nad();
                    if ((lin_get_uds_nad() == 0x68u) || (lin_get_uds_nad() == 0x6Au) ||
                            (lin_get_uds_nad() == 0x69u) || (lin_get_uds_nad() == 0x6Bu))
                    {
                        enable_swd(); // 使能swd功能
                    }
                    g_config_word_state = CONFIGURE_WORD_STATE_SAVE;
                    LOG_DFU("SAVE\n");
                }
                break;

            case 0x04u:
                /* end */
                g_config_word_state = CONFIGURE_WORD_STATE_END;
                break;

            default:
                break;
            }
            //}
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

static void read_by_identify_handle(uint8_t *param, uint16_t length)
{
    uint8_t rsp_data[5u] = {0u};
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    if (length == BOOT_Frame_length_6)
    {
        if ((param[1u] == 0xF3u) && (param[2u] == 0x3Fu) && (param[3u] == 0xFFu) && (param[4u] == 0x02u))
        {
            if ((param[5u] == LEFT_FRONT_DOOR) || (param[5u] == LEFT_REAR_DOOR) ||
                    (param[5u] == RIGHT_FRONT_DOOR) || (param[5u] == RIGHT_REAR_DOOR))
            {
                pal_store_data_get(CFG_WORD_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
                if (g_user_info.config_word == param[5u])
                {
                    rsp_data[0u] = 0x00u;
                    rsp_data[1u] = 0x00u;
                    rsp_data[2u] = 0x00u;
                    rsp_data[3u] = 0x02u;
                    rsp_data[4u] = g_user_info.config_word;
                    dfu_do_notify_cp_ex(param[0u], rsp_data, 5u);
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], GENERAL_PROGRAM_FAILURE); // NRC72
                }
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

static void user_read_data_by_id(uint16_t did, uint16_t *len)
{
    uint8_t loc;
    static const char *seres_part_numbers[] = {"4280310-RW02"};
    uint8_t seres_supplier_code[10u] = {'3', '1', '9', '7', 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u};
    uint8_t seres_ecu_name[10u] = {'E', 'H', 'I', 'S', '_', 'F', 'L', 0x20u, 0x20u, 0x20u};
    uint8_t seres_software_version[21u] = {0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u};
    uint8_t hardware_version[8u] = {0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u};
    uint8_t boot_version[8u] = {0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u};

    switch (did)
    {
    case 0xF187u:
        *len = 12u;
        for (loc = 0u; loc < 12u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_part_numbers[0][loc]);
        }

        break;
    /* Seres 供应商code:3233 */
    case 0xF18Au:
        *len = 10u;
        for (loc = 0u; loc < 10u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_supplier_code[loc]);
        }
        break;
    /* Seres ECU name:EHIS_FL */
    case 0xF197u:
        *len = 10u;

        if (g_user_info.config_word == LEFT_FRONT_DOOR) // 左前门把手
        {
            seres_ecu_name[5] = 'F';
            seres_ecu_name[6] = 'L';
        }
        else if (g_user_info.config_word == LEFT_REAR_DOOR) // 左后门把手
        {
            seres_ecu_name[5] = 'R';
            seres_ecu_name[6] = 'L';
        }
        else if (g_user_info.config_word == RIGHT_FRONT_DOOR) // 右前门把手
        {
            seres_ecu_name[5] = 'F';
            seres_ecu_name[6] = 'R';
        }
        else if (g_user_info.config_word == RIGHT_REAR_DOOR) // 右后门把手
        {
            seres_ecu_name[5] = 'R';
            seres_ecu_name[6] = 'R';
        }
        for (loc = 0u; loc < 10u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_ecu_name[loc]);
        }
        break;
    /* Seres LIN slave sequence num:SW:1.01.A_250606_3233_00 */
    case 0xF189u:
        *len = 24u;
        ll_flash_read(FLASH_TYPE_NVM, FLASH_SEQ_NUM_ADDR, (uint8_t *)&diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN], 24u);

        break;
    /* Seres software version*/
    case 0x0216u:
        *len = 21u;
        /* copy seres_software_version[] */
        ll_flash_read(FLASH_TYPE_NVM, FLASH_SERES_APP_SOFTVER_ADDR, (uint8_t *)&seres_software_version[0u], 21u);
        for (loc = 0u; loc < 21u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_software_version[loc]);
        }

        if (g_user_info.config_word == LEFT_FRONT_DOOR) // 左前门把手
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 7] = 'F';
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 8] = 'L';
        }
        else if (g_user_info.config_word == LEFT_REAR_DOOR) // 左后门把手
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 7] = 'R';
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 8] = 'L';
        }
        else if (g_user_info.config_word == RIGHT_FRONT_DOOR) // 右前门把手
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 7] = 'F';
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 8] = 'R';
        }
        else if (g_user_info.config_word == RIGHT_REAR_DOOR) // 右后门把手
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 7] = 'R';
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + 8] = 'R';
        }
        break;
    /* Seres fingerprint info*/
    case 0xF184u:
        *len = 10u;
        pal_store_read(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)&dfu_ctx.dfu_info, sizeof(last_dfu_info_t));
        for (loc = 0u; loc < 10u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(dfu_ctx.dfu_info.fingerprint[loc]);
        }
        break;
    /* hardware verison info */
    case 0xF089u:
        *len = 8u;
        ll_flash_read(FLASH_TYPE_NVM, FLASH_HW_VERSION_ADDR, (uint8_t *)hardware_version, sizeof(hardware_version));
        for (loc = 0u; loc < 8u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(hardware_version[loc]);
        }
        break;
    /* bootloader verison info */
    case 0xF180u:
        *len = 8u;
        ll_flash_read(FLASH_TYPE_NVM, FLASH_BOOT_VERSION_ADDR, (uint8_t *)boot_version, sizeof(boot_version));
        for (loc = 0u; loc < 8u; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(boot_version[loc]);
        }
        break;
    default:
        break;
    }
}

void read_data_by_identify_handle(uint8_t *param, uint16_t length)
{
    uint8_t result = NEGATIVE;
    uint8_t positresp = NEGATIVE;
    uint16_t msglen = 0u, datalen;
    uint16_t locdid = 0xFFFFu;
    msglen = length;
    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
    {
        return;
    }
    /* message length correct check */
    if (UDS_READ_BY_DID_REQ_LEN == msglen)
    {
        locdid = ((uint16_t)param[1u] << 8u) + param[2u];
        result = uds_diag_DID_chk(locdid);
        /* DID supported */
        if (result)
        {
            /*call the user function to process the service after all checks are correct*/
            user_read_data_by_id(locdid, &datalen);
            positresp = POSITIVE;
            msglen = (datalen + UDS_READ_BY_DID_MIN_RESP_LEN);
        }
        else
        {
            g_negResponseCode = REQUEST_OUT_RANGE; // NRC31
        }
    }
    else
    {
        g_negResponseCode = IMLOIF; // NRC13
    }

    if (POSITIVE == positresp) /*positive response*/
    {
        diagnosticTxBuffer[1u] = (uint8_t)(locdid >> 8u);
        diagnosticTxBuffer[2u] = (uint8_t)locdid;
        dfu_do_notify_cp_ex(param[0u], &diagnosticTxBuffer[1u], msglen - 1u);
    }
    else /*negative response*/
    {
        dfu_do_notify_response(NEGATIVE, param[0u], g_negResponseCode);
    }
}

void communcation_control_handle(uint8_t *param, uint16_t length)
{
    if (uds_request_info.sessionMode == EXTEND_SESSION)
    {
        if (length == BOOT_Frame_length_3)
        {
            if ((param[1u] == 0x00u) || (param[1u] == 0x03u))
            {
                if ((param[2u] == 0x01u) || (param[2u] == 0x03u))
                {
                    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                    {
                    }
                    else
                    {
                        dfu_do_notify_response(POSITIVE, param[0u], param[1u]);
                    }
                }
                else
                {
                    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                    {
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
                    }
                }
            }
            else if ((param[1u] == 0x80u) || (param[1u] == 0x83u))
            {
                if ((param[2u] == 0x01u) || (param[2u] == 0x03u))
                {
                }
                else
                {
                    if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                    {
                    }
                    else
                    {
                        dfu_do_notify_response(NEGATIVE, param[0u], REQUEST_OUT_RANGE); // NRC31
                    }
                }
            }
            else
            {
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
                }
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
        }
    }
    else
    {
        if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
        {
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
        }
    }
}
void dtc_control_handle(uint8_t *param, uint16_t length)
{
    if (uds_request_info.sessionMode == EXTEND_SESSION)
    {
        if (length == BOOT_Frame_length_2)
        {
            if (param[1u] == 0x01u)
            {
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_do_notify_response(POSITIVE, param[0u], param[1u]);
                }
            }
            else if (param[1u] == 0x02u)
            {
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_do_notify_response(POSITIVE, param[0u], param[1u]);
                }
            }
            else if (param[1] == 0x81u)
            {
            }
            else if (param[1] == 0x82u)
            {
            }
            else
            {
                if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
                {
                }
                else
                {
                    dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
                }
            }
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
        }
    }
    else
    {
        if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
        {
        }
        else
        {
            dfu_do_notify_response(NEGATIVE, param[0u], SERVICENOTSUPPORTED_INACTIVESESSION); // NRC7F
        }
    }
}
void diagnostic_session_handle(uint8_t *param, uint16_t length)
{
    if (length == BOOT_Frame_length_2)
    {
        if (param[1] == 0x00u)
        {
            if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
            {
            }
            else
            {
                dfu_do_notify_response(POSITIVE, param[0], param[1]);
            }
        }
        else if (param[1] == 0x80u)
        {
        }
        else
        {
            if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
            {
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, param[0u], SUBFUNCTION_NOT_SUPPORTED); // NRC12
            }
        }
    }
    else
    {
        dfu_do_notify_response(NEGATIVE, param[0u], IMLOIF); // NRC13
    }
}

const dfu_process_context_t dfu_process_ctx[] =
{
    {SERVICE_SESSION_CONTROL, session_control_handle},             // 0x10 物理寻址+功能寻址
    {SERVICE_ECU_RESET, reset_handle},                             // 0x11 物理寻址+功能寻址
    {SERVICE_SECURITY_ACCESS, security_access_handle},             // 0x27 物理寻址
    {SERVICE_FIRMWARE_INFO_SYNC, firmware_info_sync_handle},       // 0x2E 物理寻址
    {SERVICE_ROUTINE_CONTROL, routine_control_handle},             // 0x31 物理寻址
    {SERVICE_REQUEST_DOWNLOAD, request_download_handle},           // 0x34 物理寻址
    {SERVICE_TRANSFER_DATA, transfer_data_handle},                 // 0x36 物理寻址
    {SERVICE_REQUEST_TRANSFER_EXIT, request_transfer_exit_handle}, // 0x37 物理寻址
    {SERVICE_CLEAR_DTC_INFO, clear_dtc_info_handle},               // 0x14 物理寻址+功能寻址
    {SERVICE_ASSIGN_NAD_VIA_SNPD, assign_config_word_handle},      // 0xB5
    {SERVICE_READ_BY_IDENTIFY, read_by_identify_handle},           // 0xB2
    {SERVICE_READ_DATA_BY_IDENTIFY, read_data_by_identify_handle}, // 0x22 物理寻址
    {SERVICE_COMMUNCATION_CONTROL, communcation_control_handle},   // 0x28 功能寻址
    {SERVICE_DTC_CONTROL, dtc_control_handle},                     // 0x85 功能寻址
    {SERVICE_TESTER_PRESENT, diagnostic_session_handle},           // 0x3E 功能寻址
};

#define DFU_PROCESS_STEP_MAX (sizeof(dfu_process_ctx) / sizeof(dfu_process_context_t))

void lin_update_random_value(void)
{
    static uint8_t random_i = 0u;
    static uint8_t auto_add_cnt = 0u;
    if (random_i < 16u)
    {
        seed[random_i] = seed[random_i] + random_i + dfu_ctx.uds_timeout + auto_add_cnt;
        random_i++;
    }
    else
    {
        random_i = 0u;
    }
    auto_add_cnt++;
}
void lin_exception_handle(void)
{
    if (unlock_failed_store_flag == AS_TRUE)
    {
        unlock_failed_store_flag = AS_FALSE;
        pal_store_data_set(SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
    }
    if (diagnostic_session_overtime_flag == AS_TRUE)
    {
        diagnostic_session_overtime_flag = AS_FALSE;
        uds_request_info.sessionMode = DEFALUT_SESSION;
        dfu_ctx.op_code = DFU_CMD_DEFAULT_SESSION;
        pal_store_read(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)&dfu_ctx.dfu_info, sizeof(last_dfu_info_t));
        if (DFU_INFO_MAGIC == dfu_ctx.dfu_info.magic)
        {
            NVIC_SystemReset();
        }
    }
}

/********************************************************
** \brief   lin_diag_service_handle
**
** \param   None
**
** \retval  None
*********************************************************/
void lin_diag_service_handle(void)
{
    uint16_t length = 0u;
    uint8_t i;
    uint8_t *ptr = ((uint8_t *)&dfu_ctx.queue_list.packet[dfu_ctx.queue_list.tail] + 2u);
    lin_uds_receive(lin_configured_NAD, ptr, &length);
    uint8_t sid = ptr[0u];
    if (length)
    {
        for (i = 0u; i < DFU_PROCESS_STEP_MAX; i++)
        {
            if (sid == dfu_process_ctx[i].sid)
            {

                if (NULL != dfu_process_ctx[i].func)
                {
                    dfu_process_ctx[i].func(ptr, length);
                }
                break;
            }
        }
        if (i == DFU_PROCESS_STEP_MAX)
        {
            if ((lin_get_uds_nad() == 0x7Eu) || (lin_get_uds_nad() == 0x7Fu))
            {
            }
            else
            {
                dfu_do_notify_response(NEGATIVE, ptr[0u], SERVICE_NOT_SUPPORTED);
            }
        }
        dfu_ctx.uds_timeout = 0u;
    }
}

/********************************************************
** \brief   dfu_timeout_handle
**
** \param   None
**
** \retval  None
*********************************************************/
void dfu_timeout_handle(void)
{
    dfu_ctx.uds_timeout++;
    if (dfu_ctx.uds_timeout > LIN_UDS_TIMEOUT)
    {
        dfu_ctx.uds_timeout = 0u;
        // 5S未收到任意报文，诊断会话超时,置位超时标志位，在主循环里去判断APP标志位是否有效，有效则复位后进入APP的默认会话，无效则停留在bootloader的默认会话
        diagnostic_session_overtime_flag = AS_TRUE;
    }
}
void dfu_store_system_data_init(void)
{
    ll_flash_read(STORE_TYPE_SEL, CFG_WORD_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
    ll_flash_read(STORE_TYPE_SEL, SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
    uds_diagnostic_configword_remap_nad();
}

/********************************************************
** \brief   dfu_manager_init
**
** \param   None
**
** \retval  None
*********************************************************/
void dfu_manager_init(void)
{
    wdg_init(10000u);
    Gen_CMACkey(key);
#ifdef CFG_SUPPORT_DEBUG
    logging_init();
#endif
    dfu_store_system_data_init();
    memset(&dfu_ctx, 0u, sizeof(dfu_ctx));
    pal_lin_init(LIN_BUS_0, LIN_MODE_SLV, LIN_BAUD_RATE, lin_lld_isr_callback);

    LOG_DFU("lin_configured_NAD = %02X\r\n", lin_configured_NAD);
}

/********************************************************
** \brief   main_loops
**
** \param   None
**
** \retval  None
*********************************************************/

void main_loops(void)
{
    static uint32_t LoopCnt = 0u;
    static uint8_t random_i = 0u;
    wdg_reload();
    lin_diag_service_handle();
    lin_exception_handle();
    lin_update_random_value();

    if (dfu_ctx.boot_state == BOOT_STATE_IDLE)
    {
        delay_ms(1u);

        /* about 42ms+5ms */
        if ((++LoopCnt) > 50u)
        {
            LoopCnt = 0u;

            if (DFU_MSG_SUCCESS == last_dfu_info_get())
            {
                LOG_DFU("BOOT_STATE_USER_APP\r\n");
                dfu_ctx.boot_state = BOOT_STATE_USER_APP;
            }
            else
            {
                LOG_DFU("BOOT_STATE_UPGRADE\r\n");
                dfu_ctx.boot_state = BOOT_STATE_UPGRADE;
            }
        }
    }
    else if (dfu_ctx.boot_state == BOOT_STATE_USER_APP)
    {
        JumpToApp(); /* jump user app*/
    }
}

/********************************************************
** \brief   os_task_update
**
** \param   None
**
** \retval  None
*********************************************************/
uint8_t clear_wdg_cnt = 0u;
void os_task_update(void)
{
    dfu_timeout_handle();
    if (app_cmac_start == AS_TRUE)
    {
        if ((++timer_1s_cnt) > 1800u)
        {
            timer_1s_cnt = 0u;
            dfu_do_notify_response(NEGATIVE, 0x31u, RCRRP); // NRC78,算APP CMAC的时候，每隔1.8s响应一次NRC78
        }
        if ((++clear_wdg_cnt) > 100u)
        {
            clear_wdg_cnt = 0u;
            wdg_reload();
        }
    }
    if (g_ota_info.lock_failed_index > 2u) // 满3次的情况下，隔10s释放一次
    {
        if ((++lock_failed_cnt) > 10000u)
        {
            lock_failed_cnt = 0u;
            g_ota_info.lock_failed_index = 2u;
            // 置位一个27解锁失败次数更新的存储标志位，在主循环去操作flash
            unlock_failed_store_flag = AS_TRUE;
        }
    }
}
