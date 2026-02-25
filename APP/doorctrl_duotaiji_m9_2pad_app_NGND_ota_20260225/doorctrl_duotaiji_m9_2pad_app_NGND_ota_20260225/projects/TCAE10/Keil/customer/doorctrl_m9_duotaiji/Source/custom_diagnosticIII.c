/**
  ******************************************************************************
  * @brief  application main file.
  *
  * @file   custom_diagnosticlll.c
  * @author AE/FAE team
  * @date
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <b>&copy; Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd.</b>
  *
  ******************************************************************************
  */
#include "diagnosticIII.h"
#include "tc_log.h"
#include "lin.h"
#include "pal_store.h"
#include "store_manager.h"
#include "utilities.h"
#include "touch_include.h"
#include "lin_frame.h"
#include "custom_diagnosticIII.h"
#include "touch_config.h"

static const char *TAG = "custom";

#if defined APP_MATCH_BOOT
__attribute__((section(".ARM.__at_0x00004000"))) const char g_lin_sequence_num_version[24] = "SW:1.01.B_251230_3197_01";                                                                                        /* 24 byte*/
__attribute__((section(".ARM.__at_0x00004018"))) const char g_seres_app_software_version[21] = {'S', 'W', ':', 'E', 'H', 'I', 'S', 'F', 'L', '.', '1', '.', '3', 'C', '.', '0', '1', 0x20, 0x20, 0x20, 0x20};   /* 21 byte*/
#else
const char g_lin_sequence_num_version[24] = "SW:1.01.B_251230_3197_01";                                                                                        /* 24 byte*/
const char g_seres_app_software_version[21] = {'S', 'W', ':', 'E', 'H', 'I', 'S', 'F', 'L', '.', '1', '.', '3', 'C', '.', '0', '1', 0x20, 0x20, 0x20, 0x20};   /* 21 byte*/
#endif

/* general defines for UDS Session*/
#define UDS_TRUE 0x01u
#define UDS_FALSE 0x00u

#define P2_SERVER_MAX (500)
#define P2E_SERVER_MAX (200)

#define FLASH_SECTOR_SIZE (512)
#define FLASH_BASE_ADDR (0x00000000UL)
#define FLASH_END_ADDR (0x00010000UL)
#define CUS_CFG_WORD_BASE_ADDR (0x0000F800UL)                   /* 0.5k */
#define CUS_SYSTEM_PARAM_BASE_ADDR (0x0000FA00UL)               /* 0.5k */
#define FLASH_BOOT_SIZE (0x00003E00UL)                          /* 15.5k */
#define FLASH_DFU_INFO_ADDR (FLASH_BASE_ADDR + FLASH_BOOT_SIZE) /* 15.5k */
#define FLASH_DFU_INFO_SIZE (FLASH_SECTOR_SIZE)                 /* 0.5k */
// #define FLASH_APP_ADDR                  (FLASH_DFU_INFO_ADDR + FLASH_DFU_INFO_SIZE) /* 16k */
#define FLASH_APP_PARAM_SIZE (0x00000800UL)                                           /* 2K*/
#define FLASH_APP_IMAGE_SIZE (FLASH_END_ADDR - FLASH_APP_ADDR - FLASH_APP_PARAM_SIZE) /* 46k */
#define FLASH_APP_END_ADDR (FLASH_END_ADDR - FLASH_APP_PARAM_SIZE)
#define FLASH_BOOT_VERSION_ADDR (0x00003900u)
#define FLASH_HW_VERSION_ADDR (0x00003908u)

#define CUS_UDS_RECEIVE_BUFFER_SIZE (20)
#define CUS_UDS_SEND_BUFFER_SIZE (66)
#define UDS_SESSION_POSIT_RESP_LEN 3u
#define UDS_SESSION_NEG_RESP_LEN 3u
#define UDS_SUPPRESS_POS_RESP_INDIC_BIT 0x80u
#define UDS_SID_MASK_WO_RESP_IND_BIT 0x7Fu
#define UDS_NEG_RESP_RSID 0x7Fu
#define UDS_POS_RESP_CODE 0x40u
#define UDS_DIAG_SESSION_POSIT_RESP_LEN 6u
#define UDS_DIAG_SESSION_REQ_LEN 2u
#define UDS_DIAG_ROUTE_POSIT_RESP_LEN 5u
#define UDS_DIAG_ROUTE_REQ_LEN 4u
#define UDS_READ_BY_DID_MIN_RESP_LEN 3u
#define UDS_READ_BY_DID_REQ_LEN 3u

#define CUS_UDS_PRODUCT_IDENT 0xF3u

/* negative response code for UDS services */
#define UDS_SERVICE_NOT_SUPPORTED_11 0x11u /* This response code is in general supported by each diagnostic service */
#define UDS_SUBFUNC_NOT_SUPP_12 0x12u
#define UDS_INCOR_LEN_INVALID_FORMAT_13 0x13u
#define UDS_RESPONSE_TOO_LONG_14 0x14u
#define UDS_BUSY_REPEAT_REQUEST_21 0x21u
#define UDS_COND_NOT_CORRECT_22 0x22u
#define UDS_REQU_SEQU_ERROR_24 0x24u
#define UDS_REQUEST_OUT_OF_RANGE_31 0x31u
#define UDS_GENERAL_PROGRAMMING_FAIL_72 0x72u
#define UDS_REQ_CORR_REC_RESP_PEND_78 0x78u
#define UDS_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION_7F 0x7Fu

#define CONFIGURE_WORD_STATE_INIT 0
#define CONFIGURE_WORD_STATE_START 1
#define CONFIGURE_WORD_STATE_ASIGN 2
#define CONFIGURE_WORD_STATE_SAVE 3
#define CONFIGURE_WORD_STATE_END 4

/**
 * Note:ota dfu info struct, this should be align with bootloader
 */
typedef struct
{
    uint8_t fingerprint[10];
    uint32_t magic;
    uint32_t image_size;
} last_dfu_info_t;

/**
 * @brief ota sys info
 */
typedef struct
{
    uint8_t app_req_ext_program_flag;
    uint8_t app_need_res_flag; /* boot to app flag */
    uint8_t lock_failed_index; /* 27 sid lock failed index */
} ota_cfg_t __attribute__((aligned(1)));

uint8_t diagnosticRxBuffer[CUS_UDS_RECEIVE_BUFFER_SIZE] = {0};
uint8_t diagnosticTxBuffer[CUS_UDS_SEND_BUFFER_SIZE] = {0};
uint8_t diagRxSize = 0;
uint8_t negResponseCode = 0;
last_dfu_info_t g_dfu_info = {0};
user_cfg_t g_user_info = {0};
ota_cfg_t g_ota_info = {0};
uint8_t g_config_word_state = 0;
uint8_t session_mode = SESSION_MODE_DEFAULT;
uint8_t program_condition_check = 0;
uint16_t lock_failed_cnt = 0;
uint8_t unlock_failed_store_flag = 0;
uint32_t diagnostic_session_cnt = 0;

static void guserinfo_save(void);
static void gsysinfo_save(void);
static void enable_swd(void); // 使能swd接口

void send_negative_response_message(uint8_t negrespcode)
{
    uint16_t msglen = UDS_SESSION_NEG_RESP_LEN;
    diagnosticTxBuffer[0u] = UDS_NEG_RESP_RSID;
    diagnosticTxBuffer[1u] = diagnosticRxBuffer[0u];
    diagnosticTxBuffer[2u] = negrespcode;
    if ((ld_tx_status() == LD_COMPLETED) || (ld_tx_status() == LD_N_AS_TIMEOUT))
    {
        ld_send_message(msglen, diagnosticTxBuffer);
    }
}

void send_positive_response_message(uint16_t msglen)
{
    diagnosticTxBuffer[0u] = diagnosticRxBuffer[0u] + UDS_POS_RESP_CODE;
    if ((ld_tx_status() == LD_COMPLETED) || (ld_tx_status() == LD_N_AS_TIMEOUT))
    {
        ld_send_message(msglen, diagnosticTxBuffer);
    }
}

static uint8_t uds_diag_DID_chk(uint16_t ucSess)
{
    uint8_t ucRet;
    switch (ucSess)
    {
    /* Seres part num:6106150-RQ01 */
    case 0xF187:
    /* Seres 供应商code:3233 */
    case 0xF18A:
    /* Seres ECU name:EHIS_FL */
    case 0xF197:
    case 0xF189:
    case 0xF089:
    case 0xF180:
    case 0xF184:
    case 0x0216:
        ucRet = UDS_TRUE;
        break;
    default:
        ucRet = UDS_FALSE;
        break;
    }
    return ucRet;
}

static void user_read_data_by_id(uint16_t did, uint16_t *len)
{
    uint8_t loc;
    static const char *seres_part_numbers[] = {"4280310-RW02"};
    uint8_t seres_supplier_code[10] = {0x33, 0x31, 0x39, 0x37, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
    uint8_t seres_ecu_name[10] = {'E', 'H', 'I', 'S', '_', 'F', 'L', 0x20, 0x20, 0x20};
    uint8_t boot_version[8] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
    uint8_t hard_version[8] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};

    switch (did)
    {
    /* Seres part num:6106150-RQ01 */
    case 0xF187:
        *len = 12;
        for (loc = 0u; loc < 12; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_part_numbers[0][loc]);
        }
        break;
    /* Seres 供应商code:3233 */
    case 0xF18A:
        *len = 10;
        for (loc = 0u; loc < 10; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_supplier_code[loc]);
        }
        break;
    /* Seres ECU name:EHIS_FL */
    case 0xF197:
        *len = 10;
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
        for (loc = 0u; loc < 10; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(seres_ecu_name[loc]);
        }
        break;
    /* Seres LIN slave sequence num:SW:1.01.A_250606_3233_00 */
    case 0xF189:
        *len = 24;
        for (loc = 0u; loc < 24; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(g_lin_sequence_num_version[loc]);
        }
        break;
    /* Seres software version*/
    case 0x0216:
        *len = 21;

        /* copy seres_software_version[] */
        for (loc = 0u; loc < 21; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(g_seres_app_software_version[loc]);
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
    case 0xF184:
        *len = 10;
        // pal_store_read(FLASH_TYPE_NVM, FLASH_DFU_INFO_ADDR, (uint8_t *)&g_dfu_info, sizeof(last_dfu_info_t));
        store_slow_smart_read(FLASH_DFU_INFO_ADDR, (uint8_t *)&g_dfu_info, sizeof(last_dfu_info_t));
        for (loc = 0u; loc < 10; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(g_dfu_info.fingerprint[loc]);
        }
        break;
    /* hardware verison info */
    case 0xF089:
        *len = 8;
        ll_flash_read(FLASH_TYPE_NVM, FLASH_HW_VERSION_ADDR, (uint8_t *)hard_version, sizeof(hard_version));
        for (loc = 0u; loc < 8; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(hard_version[loc]);
        }
        break;
    /* bootloader verison info */
    case 0xF180:
        *len = 8;
        ll_flash_read(FLASH_TYPE_NVM, FLASH_BOOT_VERSION_ADDR, (uint8_t *)boot_version, sizeof(boot_version));
        for (loc = 0u; loc < 8; loc++)
        {
            diagnosticTxBuffer[UDS_READ_BY_DID_MIN_RESP_LEN + loc] = (uint8_t)(boot_version[loc]);
        }
        break;
    default:
        break;
    }
}

void uds_diagnostic_session_control(void)
{
    uint8_t ucSess = 0u;
    uint8_t usMsgLen = 0u;

    usMsgLen = diagRxSize;
    if (UDS_DIAG_SESSION_REQ_LEN == usMsgLen)
    {
        ucSess = diagnosticRxBuffer[1u];
        switch (ucSess)
        {
        case 0x01:
        case 0x81:
            session_mode = SESSION_MODE_DEFAULT;
            break;
        case 0x02:
        case 0x82:
            if (program_condition_check == 1)
            {
                program_condition_check = 0;
                /* program req_ext_program_flag && reset*/
                if (ucSess == 0x02)
                    g_ota_info.app_req_ext_program_flag = 1;
                else
                    g_ota_info.app_req_ext_program_flag = 3;
                gsysinfo_save();
                delay1ms(1);
                ll_wdg_enable(false);
                NVIC_SystemReset();
            }
            else
            {
                if (ucSess == 0x02)
                {
                    send_negative_response_message(UDS_COND_NOT_CORRECT_22); // NRC22
                }
            }

            break;

        case 0x03:
        case 0x83:
            session_mode = SESSION_MODE_EXTEND;
            break;
        default:
            send_negative_response_message(UDS_SUBFUNC_NOT_SUPP_12); // NRC12
            break;
        }
        if ((ucSess == 0x01) || (ucSess == 0x03))
        {
            diagnosticTxBuffer[1] = ucSess;
            diagnosticTxBuffer[2] = (uint8_t)((P2_SERVER_MAX >> 8) & 0xFF);
            diagnosticTxBuffer[3] = (uint8_t)(P2_SERVER_MAX & 0xFF);
            diagnosticTxBuffer[4] = (uint8_t)((P2E_SERVER_MAX >> 8) & 0xFF);
            diagnosticTxBuffer[5] = (uint8_t)(P2E_SERVER_MAX & 0xFF);
            usMsgLen = 6;
            send_positive_response_message(usMsgLen);
        }
    }
    else
    {
        send_negative_response_message(UDS_INCOR_LEN_INVALID_FORMAT_13); // NRC13
    }
}

void uds_diagnostic_route_control(void)
{

    uint16_t ucSess = 0u;
    uint8_t usMsgLen = 0u;
    negResponseCode = 0;

    usMsgLen = diagRxSize;
    if (UDS_DIAG_ROUTE_REQ_LEN == usMsgLen)
    {
        if ((diagnosticRxBuffer[1] == 0x01) || (diagnosticRxBuffer[1] == 0x81))
        {
            ucSess = (uint16_t)((diagnosticRxBuffer[2] << 8) | diagnosticRxBuffer[3]);
            diagnosticRxBuffer[1] = 0x01;
            if (ucSess == 0x0203)
            {
                if (session_mode == SESSION_MODE_EXTEND)
                {

                    if (((door_cmd.VehicleSpeedValid == 1) && (door_cmd.VehicleSpeed < 0x36)) || (door_cmd.VehicleSpeedValid == 0))
                    {
                        program_condition_check = 1;
                    }
                    else
                    {
                        send_negative_response_message(UDS_COND_NOT_CORRECT_22); // NRC22
                    }
                }
                else
                {
                    negResponseCode = UDS_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION_7F;
                }
            }
            else if ((ucSess == 0xFF01) || (ucSess == 0xFF00) || (ucSess == 0xDD02))
            {
                negResponseCode = UDS_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION_7F;
            }
            else
            {
                negResponseCode = UDS_REQUEST_OUT_OF_RANGE_31;
            }
        }
        else
        {
            negResponseCode = UDS_SUBFUNC_NOT_SUPP_12;
        }
    }
    else
    {
        negResponseCode = UDS_INCOR_LEN_INVALID_FORMAT_13;
    }

    if (0 == negResponseCode) /* positive response */
    {
        usMsgLen = UDS_DIAG_ROUTE_POSIT_RESP_LEN;
        diagnosticTxBuffer[1u] = diagnosticRxBuffer[1];
        diagnosticTxBuffer[2u] = diagnosticRxBuffer[2];
        diagnosticTxBuffer[3u] = diagnosticRxBuffer[3];
        diagnosticTxBuffer[4u] = 0x00;
        switch (ucSess)
        {
        case 0x0203:
            send_positive_response_message(usMsgLen);
            break;
        }
    }
    if (negResponseCode != 0) /* negative response */
    {
        send_negative_response_message(negResponseCode);
    }
}
void uds_diagnostic_dtc_control(void)
{
    if (session_mode == SESSION_MODE_EXTEND)
    {
        if (diagRxSize == 2u)
        {
            if (diagnosticRxBuffer[1] == 0x81)
            {
            }
            else if (diagnosticRxBuffer[1] == 0x82)
            {
            }
            else if (diagnosticRxBuffer[1] == 0x01)
            {
                diagnosticTxBuffer[1] = 0x01;
                send_positive_response_message(2u);
            }
            else if (diagnosticRxBuffer[1] == 0x02)
            {
                diagnosticTxBuffer[1] = 0x02;
                send_positive_response_message(2u);
            }
            else
            {
                if ((lin_current_rcvd_nad() == 0x7E) || (lin_current_rcvd_nad() == 0x7F))
                {
                }
                else
                {
                    send_negative_response_message(UDS_SUBFUNC_NOT_SUPP_12); // NRC12
                }
            }
        }
        else
        {
            send_negative_response_message(UDS_INCOR_LEN_INVALID_FORMAT_13); // NRC13
        }
    }
    else
    {
        if ((lin_current_rcvd_nad() == 0x7E) || (lin_current_rcvd_nad() == 0x7F))
        {
        }
        else
        {
            send_negative_response_message(UDS_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION_7F); // NRC7F
        }
    }
}

void uds_diagnostic_clear_dtc_info(void)
{
    uint8_t usMsgLen = 0u;
    usMsgLen = diagRxSize;
    if (usMsgLen == 0x04u)
    {
        if ((diagnosticRxBuffer[1u] == 0xFF) && (diagnosticRxBuffer[2u] == 0xFF) && (diagnosticRxBuffer[3u] == 0xFF))
        {
            send_positive_response_message(1u);
        }
        else
        {
            send_negative_response_message(UDS_REQUEST_OUT_OF_RANGE_31);
        }
    }
    else
    {
        send_negative_response_message(UDS_INCOR_LEN_INVALID_FORMAT_13);
    }
}
void uds_communction_control(void)
{
    if (session_mode == SESSION_MODE_EXTEND)
    {
        if (diagRxSize == 3u)
        {
            if ((diagnosticRxBuffer[1u] == 0x00) || (diagnosticRxBuffer[1u] == 0x03))
            {
                if ((diagnosticRxBuffer[2u] == 0x01) || (diagnosticRxBuffer[2u] == 0x03))
                {
                    if (((door_cmd.VehicleSpeedValid == 1) && (door_cmd.VehicleSpeed < 0x36)) || (door_cmd.VehicleSpeedValid == 0))
                    {
                        diagnosticTxBuffer[1u] = diagnosticRxBuffer[1u];
                        send_positive_response_message(2u);
                    }
                    else
                    {
                        send_negative_response_message(UDS_COND_NOT_CORRECT_22); // NRC22
                    }
                }
                else
                {
                    if ((lin_current_rcvd_nad() == 0x7E) || (lin_current_rcvd_nad() == 0x7F))
                    {
                    }
                    else
                    {
                        send_negative_response_message(UDS_REQUEST_OUT_OF_RANGE_31); // NRC31
                    }
                }
            }
            else if ((diagnosticRxBuffer[1u] == 0x80) || (diagnosticRxBuffer[1u] == 0x83))
            {
                if ((diagnosticRxBuffer[2u] == 0x01) || (diagnosticRxBuffer[2u] == 0x03))
                {
                    if (((door_cmd.VehicleSpeedValid == 1) && (door_cmd.VehicleSpeed < 0x36)) || (door_cmd.VehicleSpeedValid == 0))
                    {
                    }
                    else
                    {
                        send_negative_response_message(UDS_COND_NOT_CORRECT_22); // NRC22
                    }
                }
                else
                {
                    if ((lin_current_rcvd_nad() == 0x7E) || (lin_current_rcvd_nad() == 0x7F))
                    {
                    }
                    else
                    {
                        send_negative_response_message(UDS_REQUEST_OUT_OF_RANGE_31); // NRC31
                    }
                }
            }
            else
            {
                if ((lin_current_rcvd_nad() == 0x7E) || (lin_current_rcvd_nad() == 0x7F))
                {
                }
                else
                {
                    send_negative_response_message(UDS_SUBFUNC_NOT_SUPP_12); // NRC12
                }
            }
        }
        else
        {
            send_negative_response_message(UDS_INCOR_LEN_INVALID_FORMAT_13); // NRC13
        }
    }
    else
    {
        if ((lin_current_rcvd_nad() == 0x7E) || (lin_current_rcvd_nad() == 0x7F))
        {
        }
        else
        {
            send_negative_response_message(UDS_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION_7F); // NRC7F
        }
    }
}
void uds_tester_present_control(void)
{
    if (diagRxSize == 2)
    {
        if (diagnosticRxBuffer[1u] == 0x80)
        {
        }
        else if (diagnosticRxBuffer[1u] == 0x00)
        {
            diagnosticTxBuffer[1u] = diagnosticRxBuffer[1u];
            send_positive_response_message(2);
        }
        else
        {
            send_negative_response_message(UDS_SUBFUNC_NOT_SUPP_12); // NRC12
        }
    }
    else
    {
        send_negative_response_message(UDS_INCOR_LEN_INVALID_FORMAT_13); // NRC13
    }
}
void uds_diagnostic_rest(void)
{
    uint8_t mslen = 0;
    mslen = diagRxSize;
    if (mslen == 2)
    {
        if (diagnosticRxBuffer[1u] == 0x01)
        {
            if (((door_cmd.VehicleSpeedValid == 1) && (door_cmd.VehicleSpeed < 0x36)) || (door_cmd.VehicleSpeedValid == 0))
            {
                diagnosticTxBuffer[1u] = diagnosticRxBuffer[1u];
                send_positive_response_message(2);
                for (uint8_t i = 0; i < 60; i++)
                {
                    delay1ms(1);
                }

                ll_wdg_enable(false);
                NVIC_SystemReset();
            }
            else
            {
                send_negative_response_message(UDS_COND_NOT_CORRECT_22); // NRC22
            }
        }
        else if (diagnosticRxBuffer[1u] == 0x81)
        {
            if (((door_cmd.VehicleSpeedValid == 1) && (door_cmd.VehicleSpeed < 0x36)) || (door_cmd.VehicleSpeedValid == 0))
            {
                ll_wdg_enable(false);
                NVIC_SystemReset();
            }
            else
            {
                send_negative_response_message(UDS_COND_NOT_CORRECT_22); // NRC22
            }
        }
        else
        {
            send_negative_response_message(UDS_SUBFUNC_NOT_SUPP_12); // NRC12
        }
    }
    else
    {
        send_negative_response_message(UDS_INCOR_LEN_INVALID_FORMAT_13); // NRC13
    }
}
void uds_diagnostic_readdata_by_id(void)
{
    uint8_t result = UDS_FALSE;
    uint8_t positresp = UDS_FALSE;
    uint16_t msglen = 0u, datalen;
    uint16_t locdid = 0xFFFFu;

    msglen = diagRxSize;

    /* message length correct check */
    if (UDS_READ_BY_DID_REQ_LEN == msglen)
    {
        locdid = ((uint16_t)diagnosticRxBuffer[1u] << 8u) + diagnosticRxBuffer[2u];
        result = uds_diag_DID_chk(locdid);
        /* DID supported */
        if (result)
        {
            /*call the user function to process the service after all checks are correct*/
            user_read_data_by_id(locdid, &datalen);
            positresp = UDS_TRUE;
            msglen = (datalen + UDS_READ_BY_DID_MIN_RESP_LEN);
        }
        else
        {
            negResponseCode = UDS_REQUEST_OUT_OF_RANGE_31;
        }
    }
    else
    {
        negResponseCode = UDS_INCOR_LEN_INVALID_FORMAT_13;
    }

    if (UDS_TRUE == positresp) /*positive response*/
    {
        diagnosticTxBuffer[1u] = (uint8_t)(locdid >> 8u);
        diagnosticTxBuffer[2u] = (uint8_t)locdid;
        send_positive_response_message(msglen);
    }
    else /*negative response*/
    {
        send_negative_response_message(negResponseCode);
    }
}

void uds_pal_store_data_set(uint32_t addr, uint8_t *data, uint16_t length)
{
    //    uint8_t nvrdata[STORE_SECTOR_SIZE] __attribute((aligned(4)));
    //    uint32_t offset = addr % STORE_SECTOR_SIZE;
    //    uint32_t crc __attribute__((unused));

    //    ll_flash_read(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);

    //    if (memcmp((uint8_t *)&nvrdata[offset], data, length))
    //    {
    //        memcpy((uint8_t *)&nvrdata[offset], data, length);
    //        extern uint16_t crc16_calculate_func(uint16_t init_crc, const uint8_t *data, uint16_t length);
    //        crc = crc16_calculate_func(0xFFFF, (uint8_t *)&nvrdata[offset], length);
    //        memcpy(&nvrdata[offset + length], &crc, sizeof(uint32_t));
    //        ll_flash_smart_write(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);
    //    }
    pal_store_data_set(addr, data, length);
}

void uds_diagnostic_configword_remap_nad(void)
{
    if (LEFT_FRONT_DOOR == g_user_info.config_word) // 左前门把手
    {
        lin_configured_NAD = 0x68;
        lin_initial_NAD = 0x68;
        g_user_info.nad_info = 0x68;
#if (CONFIG_BYTE_WRITE_EN == 1)
        guserinfo_save(); // 写入加速
#endif
        lin_configuration_RAM[5] = 0x1;
        lin_configuration_ROM[5] = 0x1;
        LI0_response_error_signal = LI0_EHIS_FL_ResponseError;
        response_error = LI0_EHIS_FL_ResponseError;
        lin_response_error_byte_offset[1] = LIN_BYTE_OFFSET_LI0_EHIS_FL_ResponseError;
        lin_response_error_bit_offset[1] = LIN_BIT_OFFSET_LI0_EHIS_FL_ResponseError;
    }
    else if (LEFT_REAR_DOOR == g_user_info.config_word) // 左后门把手
    {
        lin_configured_NAD = 0x6A;
        lin_initial_NAD = 0x6A;
        g_user_info.nad_info = 0x6A;
#if (CONFIG_BYTE_WRITE_EN == 1)
        guserinfo_save(); // 写入加速
#endif
        lin_configuration_RAM[5] = 0x5;
        lin_configuration_ROM[5] = 0x5;
        LI0_response_error_signal = LI0_EHIS_RL_ResponseError;
        response_error = LI0_EHIS_RL_ResponseError;
        lin_response_error_byte_offset[1] = LIN_BYTE_OFFSET_LI0_EHIS_RL_ResponseError;
        lin_response_error_bit_offset[1] = LIN_BIT_OFFSET_LI0_EHIS_RL_ResponseError;
    }
    else if (RIGHT_FRONT_DOOR == g_user_info.config_word) // 右前门把手
    {
        lin_configured_NAD = 0x69;
        lin_initial_NAD = 0x69;
        g_user_info.nad_info = 0x69;
#if (CONFIG_BYTE_WRITE_EN == 1)
        guserinfo_save(); // 写入加速
#endif
        lin_configuration_RAM[5] = 0x5;
        lin_configuration_ROM[5] = 0x5;
        LI0_response_error_signal = LI0_EHIS_FR_ResponseError;
        response_error = LI0_EHIS_FR_ResponseError;
        lin_response_error_byte_offset[1] = LIN_BYTE_OFFSET_LI0_EHIS_FR_ResponseError;
        lin_response_error_bit_offset[1] = LIN_BIT_OFFSET_LI0_EHIS_FR_ResponseError;
    }
    else if (RIGHT_REAR_DOOR == g_user_info.config_word) // 右后门把手
    {
        lin_configured_NAD = 0x6B;
        lin_initial_NAD = 0x6B;
        g_user_info.nad_info = 0x6B;
#if (CONFIG_BYTE_WRITE_EN == 1)
        guserinfo_save(); // 写入加速
#endif
        lin_configuration_RAM[5] = 0x2;
        lin_configuration_ROM[5] = 0x2;
        LI0_response_error_signal = LI0_EHIS_RR_ResponseError;
        response_error = LI0_EHIS_RR_ResponseError;
        lin_response_error_byte_offset[1] = LIN_BYTE_OFFSET_LI0_EHIS_RR_ResponseError;
        lin_response_error_bit_offset[1] = LIN_BIT_OFFSET_LI0_EHIS_RR_ResponseError;
    }
}

void uds_diagnostic_assign_NAD(void)
{
    uint8_t fuc_id;

    if ((0xF3 == diagnosticRxBuffer[1u]) && (0x3F == diagnosticRxBuffer[2u]))
    {
        fuc_id = diagnosticRxBuffer[3u];
        switch (fuc_id)
        {
        case 0x01:
            /* start */
            g_config_word_state = CONFIGURE_WORD_STATE_START;
            break;

        case 0x02:
            /* assign */
            if (g_config_word_state == CONFIGURE_WORD_STATE_START)
            {
                if ((diagnosticRxBuffer[5u] == LEFT_FRONT_DOOR) || (diagnosticRxBuffer[5u] == LEFT_REAR_DOOR) || 
                    (diagnosticRxBuffer[5u] == RIGHT_FRONT_DOOR) || (diagnosticRxBuffer[5u] == RIGHT_REAR_DOOR))
                {
#if (CONFIG_BYTE_WRITE_EN == 1)
                    g_user_info.config_word = diagnosticRxBuffer[5u];
                    uds_diagnostic_configword_remap_nad();
#endif
                    g_config_word_state = CONFIGURE_WORD_STATE_ASIGN;
                    TC_LOGI(TAG, "cfg %x\n", g_user_info.config_word);
                }
            }
            break;

        case 0x03:
            /* save */
            if (g_config_word_state == CONFIGURE_WORD_STATE_ASIGN)
            {
                //                uds_pal_store_data_set(CUS_SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
#if (CONFIG_BYTE_WRITE_EN == 1)
                guserinfo_save(); // 写入加速
#endif
                g_config_word_state = CONFIGURE_WORD_STATE_SAVE;
                TC_LOGI(TAG, "save\n");
                if (lin_current_rcvd_nad() != 0x7F)
                {
                    enable_swd(); // 使能swd功能
                }
            }
            break;

        case 0x04:
            /* end */
            g_config_word_state = CONFIGURE_WORD_STATE_END;
            break;

        default:
            break;
        }
    }
}
void lin_handle_uds(void)
{
    uint8_t idx = diagnosticRxBuffer[0u];

    negResponseCode = 0u;
    if (program_condition_check == 1)
    {
        if (lin_current_rcvd_nad() == lin_configured_NAD)
        {
            if ((diagnosticRxBuffer[0] == 0x10) && ((diagnosticRxBuffer[1] == 0x02) || (diagnosticRxBuffer[1] == 0x82)))
            {
                program_condition_check = 1;
            }
            else if ((diagnosticRxBuffer[0] == 0x3E) && ((diagnosticRxBuffer[1] == 0x00) || (diagnosticRxBuffer[1] == 0x80)))
            {
                program_condition_check = 1;
            }
            else
            {
                if (((diagnosticRxBuffer[0] == 0x85) && (diagnosticRxBuffer[1] == 0x82)) || ((diagnosticRxBuffer[0] == 0x28) && (diagnosticRxBuffer[1] == 0x83) && (diagnosticRxBuffer[2] == 0x03)))
                {
                    program_condition_check = 1;
                }
                else
                {
                    program_condition_check = 0;
                }
            }
        }
    }
    switch (idx)
    {
    case SERVICE_CLEAR_DTC_INFO: // 14
        uds_diagnostic_clear_dtc_info();
        break;
    case SERVICE_SESSION_CONTROL: // 10
        uds_diagnostic_session_control();
        break;
    case SERVICE_ROUTINE_CONTROL: // 31
        uds_diagnostic_route_control();
        break;
    case SERVICE_READ_DATA_BY_IDENTIFY: // 22
        uds_diagnostic_readdata_by_id();
        break;
    case SERVICE_ASSIGN_NAD_VIA_SNPD: // B5
        uds_diagnostic_assign_NAD();
        break;
    case SERVICE_DTC_CONTROL: // 85
        uds_diagnostic_dtc_control();
        break;
    case SERVICE_COMMUNICATION_CONTROL: // 28
        uds_communction_control();
        break;
    case SERVICE_TESTER_PRESENT: // 3E
        uds_tester_present_control();
        break;
    case SERVICE_ECU_RESET: // 11
        uds_diagnostic_rest();
        break;
    case SERVICE_WRITE_DATA_BY_IDENTIFY: // 2E
    case SERVICE_REQUEST_DOWNLOAD:       // 34
    case SERVICE_TRANSFER_DATA:          // 36
    case SERVICE_REQUEST_TRANSFER_EXIT:  // 37
        send_negative_response_message(UDS_SERVICE_NOT_SUPPORTED_INACTIVE_SESSION_7F);
        break;
    case SERVICE_SECURITY_ACCESS: // 27
        send_negative_response_message(UDS_SUBFUNC_NOT_SUPP_12);
        break;
    default:
        send_negative_response_message(SERVICE_NOT_SUPPORTED);
        break;
    }
}

void lin_custom_diag_service_handle(uint8_t sid, uint8_t *ptr, uint16_t length)
{
    diagRxSize = length;
    memcpy(diagnosticRxBuffer, ptr, length);
    diagnostic_session_cnt = 0; // 清除诊断会话
    lin_handle_uds();
}

void lin_diagservice_read_by_identifier(uint8_t *ptr, uint16_t length)
{
    uint8_t id;
    uint16_t supid, fid;

    /* Get supplier and function indentification in request */
    supid = (uint16_t)(ptr[3] << 8) | ptr[2];
    fid = (uint16_t)(ptr[5] << 8) | ptr[4];
    /* Check Supplier ID and Function ID */

    if (((supid != product_id.supplier_id) && (supid != LD_ANY_SUPPLIER)))
    {
        tl_slaveresp_cnt = 0;
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
        tl_service_status = LD_SERVICE_IDLE;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
        TC_LOGI(TAG, "no reply %x-%x\n", supid, product_id.supplier_id);
        return;
    }

    id = ptr[1];

    switch (ptr[1])
    {
    case CUS_UDS_PRODUCT_IDENT:
        if ((ptr[2] == 0x3F) && (ptr[3] == 0xFF) && (ptr[4] == 0x02))
        {
            if ((ptr[5] == LEFT_FRONT_DOOR) || (ptr[5] == LEFT_REAR_DOOR) || (ptr[5] == RIGHT_FRONT_DOOR) || (ptr[5] == RIGHT_REAR_DOOR))
            {
                pal_store_data_get(CUS_SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
                if (g_user_info.config_word == ptr[5])
                {
                    pal_store_data_get(CUS_SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
                    ptr[1] = 0x00;
                    ptr[2] = 0x00;
                    ptr[3] = 0x00;
                    ptr[4] = 0x02;
                    ptr[5] = g_user_info.config_word;
                    lin_diag_positive_notify(ptr[0], &ptr[1], 5);
                }
                else
                {
                    lin_diag_negative_notify(ptr[0], 0x72);
                }
            }
            else
            {
                lin_diag_negative_notify(ptr[0], 0x31);
            }
        }
        else
        {
            lin_diag_negative_notify(ptr[0], 0x31);
        }

        break;
    default:
        if ((id >= LIN_READ_USR_DEF_MIN) && (id <= LIN_READ_USR_DEF_MAX))
        {
            uint8_t data_callout[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
            uint8_t data_len = 0;
            extern uint8_t ld_read_by_id_callout(uint8_t id, uint8_t *data);
            uint8_t retval = ld_read_by_id_callout(id, data_callout);

            /*If the User ID is supported, make positive response*/
            if (retval == LD_POSITIVE_RESPONSE)
            {
                for (uint8_t i = 0; i < 5; i++)
                {
                    if (data_callout[i] != 0xFF)
                    {
                        for (uint8_t j = 0; j < 5; j++)
                        {
                            if (data_callout[4 - j] != 0xFF)
                            {
                                data_len = 5 - j;
                                break;
                            }
                        }

                        lin_diag_positive_notify(ptr[0], &data_callout[0], data_len);
                        break;
                    }

                    /* If all data_callout is 0xFF, then make negative response*/
                    if (i == 4)
                    {
                        /* Make a negative slave response PDU */
                        lin_diag_negative_notify(ptr[0], SUBFUNCTION_NOT_SUPPORTED);
                    }
                }
            }
            else if (retval == LD_NEGATIVE_RESPONSE)
                /*If the User ID is not supported, make negative response*/
            {
                /* Make a negative slave response PDU */
                lin_diag_negative_notify(ptr[0], SUBFUNCTION_NOT_SUPPORTED);
            }
            else if (retval == LD_ID_NO_RESPONSE)
            {
            }
        }
        else
        {
            /* Make a negative slave response PDU */
            lin_diag_negative_notify(ptr[0], SUBFUNCTION_NOT_SUPPORTED);
        }

        break;
    } /* End of switch */
}

void lin_diag_service_hook(void)
{
    uint8_t result;

    if (LD_COMPLETED == ld_tx_status())
    {
#ifdef LINUDS_WRITEBYID
        if (pendWritebyID) /*request to set session is received?*/
        {
            if (pendWritebyID)
            {
                pendWritebyID = UDS_FALSE;
            }
            /*call the user function to process the service after all checks are correct*/
            result = user_WriteDataById(writedid, writelen, &writedatarecord[0]);
            /* successfully write data? */
            if (result)
            {
                diagnosticTxBuffer[1u] = (uds_uc8)(writedid >> 8u);
                diagnosticTxBuffer[2u] = (uds_uc8)writedid;
                send_positive_response_message(UDS_SESSION_POSIT_RESP_LEN);
            }
#ifdef LINUDS_WRITEBYID_NRC_GPF
            else
            {
                negResponseCode = UDS_GENERAL_PROGRAMMING_FAIL_72;
                send_negative_response_message(negResponseCode);
            }
#endif /* #ifdef LINUDS_WRITEBYID_NRC_GPF */
        }
#endif /* #ifdef LINUDS_WRITEBYID */
    }
}

void store_system_data_init(void)
{
    store_slow_smart_read(CUS_CFG_WORD_BASE_ADDR, (uint8_t *)&g_user_info, sizeof(g_user_info));
    store_slow_smart_read(CUS_SYSTEM_PARAM_BASE_ADDR, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
    uds_diagnostic_configword_remap_nad();
    if (g_ota_info.lock_failed_index > 3)
    {
        g_ota_info.lock_failed_index = 3;
    }
}

static void guserinfo_save(void)
{
    uint32_t wbuf[2] = {0xFFFFFFFF, 0xFFFFFFFF};
    uint8_t *pb = (uint8_t *)wbuf;

    uint32_t crc = crc16_calculate_func(0xFFFF, (uint8_t *)&g_user_info, sizeof(g_user_info));
    memcpy(pb, (uint8_t *)&g_user_info, sizeof(g_user_info));
    memcpy(&pb[sizeof(g_user_info)], &crc, sizeof(crc));

    pal_store_erase(STORE_TYPE_SEL, CUS_CFG_WORD_BASE_ADDR, FLASH_SECTOR_SIZE);
    pal_store_write(STORE_TYPE_SEL, CUS_CFG_WORD_BASE_ADDR, (uint8_t *)wbuf, sizeof(wbuf));
}

static void gsysinfo_save(void)
{
    uint32_t wbuf[2] = {0xFFFFFFFF, 0xFFFFFFFF};
    uint8_t *pb = (uint8_t *)wbuf;

    uint32_t crc = crc16_calculate_func(0xFFFF, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
    memcpy(pb, (uint8_t *)&g_ota_info, sizeof(g_ota_info));
    memcpy(&pb[sizeof(g_ota_info)], &crc, sizeof(crc));

    pal_store_erase(STORE_TYPE_SEL, CUS_SYSTEM_PARAM_BASE_ADDR, FLASH_SECTOR_SIZE);
    pal_store_write(STORE_TYPE_SEL, CUS_SYSTEM_PARAM_BASE_ADDR, (uint8_t *)wbuf, sizeof(wbuf));
}

static void enable_swd(void) // 使能swd接口
{
    ll_gpio_afio_config(GPIO_PIN_0, AFIO_MUX_0); // SWCLK
    ll_gpio_afio_config(GPIO_PIN_1, AFIO_MUX_0); // SWDIO

    TouchEnableSamp(0); // 关闭touch功能
}

void lin_customized_operation(void)
{
    /* Check boot jump to app flag and process it */
    uint16_t usMsgLen = 6;
    /* TC_LOGI(TAG, "Jump %d\n", g_ota_info.app_need_res_flag); */
    if (g_ota_info.app_need_res_flag == true)
    {
        g_ota_info.app_need_res_flag = false;
        gsysinfo_save();
        diagnosticTxBuffer[0u] = SERVICE_SESSION_CONTROL + UDS_POS_RESP_CODE;
        diagnosticTxBuffer[1u] = 0x01;
        diagnosticTxBuffer[2u] = (P2_SERVER_MAX >> 8) & 0xFF;
        diagnosticTxBuffer[3u] = (P2_SERVER_MAX & 0xFF);
        diagnosticTxBuffer[4u] = (P2E_SERVER_MAX >> 8) & 0xFF;
        diagnosticTxBuffer[5u] = (P2E_SERVER_MAX & 0xFF);
        /* TC_LOGI(TAG, "send ok\n"); */
        ld_send_message(usMsgLen, diagnosticTxBuffer);
    }
}

void LinDiagnosticSessionCheck(void)
{
    extern uint8_t session_mode;
    extern unsigned int diagnostic_session_cnt;

    if (session_mode > SESSION_MODE_DEFAULT)
    {
        diagnostic_session_cnt++;
        if (diagnostic_session_cnt > 2500) /* 5s*/
        {
            diagnostic_session_cnt = 0;
            session_mode = SESSION_MODE_DEFAULT;
            program_condition_check = 0;
        }
    }
    else
    {
        diagnostic_session_cnt = 0;
    }
    if (g_ota_info.lock_failed_index > 2)
    {
        if ((++lock_failed_cnt) > 5000)
        {
            lock_failed_cnt = 0;
            g_ota_info.lock_failed_index--;
            /* 置位一个27解锁失败次数更新的存储标志位，在主循环去操作flash
               只在g_ota_info.lock_failed_index == 3时去减少一次，给一次机会，不会一直减到0
            */
            unlock_failed_store_flag = 1;
        }
    }
}
void SysDoFlashRoutine27Service(void)
{
    if (unlock_failed_store_flag == 1)
    {
        unlock_failed_store_flag = 0;
        gsysinfo_save();
    }
}
