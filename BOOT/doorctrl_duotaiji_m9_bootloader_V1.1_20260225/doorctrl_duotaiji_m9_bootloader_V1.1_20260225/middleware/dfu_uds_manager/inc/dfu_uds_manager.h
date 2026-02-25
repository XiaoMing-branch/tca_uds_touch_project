/**
 *****************************************************************************
 * @brief   dfu_uds header file.
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

#ifndef __DFU_UDS_MANAGER_H__
#define __DFU_UDS_MANAGER_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define diagnostic services id */
#define SERVICE_SESSION_CONTROL             0x10      /**< service session control */
#define SERVICE_SECURITY_ACCESS             0x27    /**< service security access */
#define SERVICE_ECU_RESET                   0x11    /**< service ecu reset */
#define SERVICE_FIRMWARE_INFO_SYNC          0x2E      /**< service firmware info sync */
#define SERVICE_ROUTINE_CONTROL             0x31    /**< service routine control */
#define SERVICE_REQUEST_DOWNLOAD            0x34    /**< service request download */
#define SERVICE_TRANSFER_DATA               0x36    /**< service transfer data */
#define SERVICE_REQUEST_TRANSFER_EXIT       0x37    /**< service transfer exit */
#define SERVICE_LINK_CONTROL                0x87    /**< service link control */

#define REQUEST_ID_ERROR         0
#define PHYSICAL_ADDR            1
#define FUNCTION_ADDR            2

#define DEFALUT_SESSION          1
#define PROGRAM_SESSION          2
#define EXTEND_SESSION           4

#define SECURITY_LEVEL0          1
#define SECURITY_LEVEL1          3
#define SECURITY_LEVEL2          7

#if defined (__TCPL01X__)
#define CFG_SUPPORT_DFU_V3      (0)
#elif defined (__TCPL03X__)
#define CFG_SUPPORT_DFU_V3      (1)
#else
#define CFG_SUPPORT_DFU_V3      (1)
#endif

#define DFU_INFO_MAGIC                  (0xDEADBEEFUL)
#define LIN_UDS_TIMEOUT                 (3000)//3s,unit =1ms
#define DFU_ERASE_WAITTIME              (800)
#define DFU_PROGRAM_WAITTIME            (60)
#define DFU_PROGRAM_LENGTH              (512)
#define DFU_PACKET_HEAD_CRC_LENGTH      (6) //SID(1byte)+Index(1byte)+Image+CRC(4byte)
#define DFU_PACKET_BLOCK_LENGTH         (DFU_PROGRAM_LENGTH + DFU_PACKET_HEAD_CRC_LENGTH)
#define DFU_PROGRAM_WORDS               (DFU_PROGRAM_LENGTH >> 2)

#define FLASH_SECTOR_SIZE               (512)
#define FLASH_BASE_ADDR                 (0x00000000UL)
#define FLASH_END_ADDR                  (0x00010000UL)

#if 1 == CFG_SUPPORT_DFU_V3
#define FLASH_BOOT_SIZE                 (0x00001E00UL) /* 7.5k */
#define FLASH_DFU_INFO_ADDR             (FLASH_BASE_ADDR + FLASH_BOOT_SIZE) /* 7.5k */
#define FLASH_DFU_INFO_SIZE             (FLASH_SECTOR_SIZE) /* 0.5k */
#define FLASH_APP_ADDR                  (FLASH_DFU_INFO_ADDR + FLASH_DFU_INFO_SIZE)  /* 8k */
#if defined (__TCPL01X__)
#define FLASH_APP_PARAM_SIZE            (0)
#elif defined (__TCPL03X__)
#define FLASH_APP_PARAM_SIZE            (0x00000800UL) /* 1.5k + 0.5k*/
#endif
#else
#define FLASH_BOOT_SIZE                 (0x00002E00UL)  /* 11.5k */
#define FLASH_DFU_INFO_ADDR             (FLASH_BASE_ADDR + FLASH_BOOT_SIZE) /* 11.5k */
#define FLASH_DFU_INFO_SIZE             (FLASH_SECTOR_SIZE) /* 0.5k */
#define FLASH_APP_ADDR                  (FLASH_DFU_INFO_ADDR + FLASH_DFU_INFO_SIZE) /* 12k */
#if defined (__TCPL01X__)
#define FLASH_APP_PARAM_SIZE            (0)
#elif defined (__TCPL03X__)
#define FLASH_APP_PARAM_SIZE            (0x00000800UL) /* 1.5k + 0.5k*/
#endif
#endif
#define FLASH_APP_IMAGE_SIZE            (FLASH_END_ADDR - FLASH_BASE_ADDR - FLASH_APP_ADDR - FLASH_APP_PARAM_SIZE) /* V3-54k(0xDA00) V2-52K(0xD000)*/
#define FLASH_APP_END_ADDR              (FLASH_END_ADDR - FLASH_APP_PARAM_SIZE)

#define  QUEUE_LIN_LEN          (2)

#define LIN_BRUAD_9600          (1)
#define LIN_BRUAD_19200         (2)
#define LIN_BRUAD_115200        (5)

/**
 * @brief dfu msg error code enumeration
 */
typedef enum
{
    DFU_MSG_SUCCESS = 0,
    DFU_MSG_ERROR,
    DFU_MSG_ERASE_ERROR,
    DFU_MSG_SYNC_ERROR,
    DFU_MSG_TRANFER_REQUEST_ERROR,
    DFU_MSG_TRANFER_EXIT_ERROR,
    DFU_MSG_SEQ_ERROR,
    DFU_MSG_PACKET_LEN_ERROR,
    DFU_MSG_INDEX_ERROR,
    DFU_MSG_PROGRA_ERROR,
    DFU_MSG_CRC_ERROR,
    DFU_MSG_TIMEOUT,
    DFU_MSG_MAX,
} dfu_msg_error_code_e;

/**
 * @brief dfu cmd enumeration
 */
typedef enum
{
    DFU_CMD_SYNC_INFO = 0,
    DFU_CMD_FLASH_ERASE,
    DFU_CMD_TRANFER_START,
    DFU_CMD_TRANFER_STOP,
    DFU_CMD_MAX,
} dfu_cmd_e;

/**
 * @brief bootlaoder state enumeration
 */
typedef enum
{
    BOOT_STATE_IDLE = 0,
    BOOT_STATE_USER_APP,
    BOOT_STATE_UPGRADE,
} boot_state_e;

/**
 * @brief packet struct
 */
typedef struct
{
    uint32_t head;
    uint32_t data[DFU_PROGRAM_WORDS];
    uint32_t crc32;
} __attribute__((aligned(4))) packet_unit_t;

/**
 * @brief queue list struct
 */
typedef struct
{
    packet_unit_t packet[QUEUE_LIN_LEN];
    uint8_t head;
    uint8_t tail;
} queue_list_t;

/**
 * @brief service uds struct
 */
typedef struct
{
    uint8_t sid;
    uint8_t sessionMode;
    uint8_t requsetMode;
    uint8_t securityLevel;
} ServiceUDS_TypeDef;

/**
 * @brief lin baudrate config struct
 */
typedef struct
{
    uint8_t update_flag;
    uint32_t baudrate;
} lin_baudrate_config_t;

/**
 * @brief last dfu info struct
 */
typedef struct
{
    uint32_t magic;
    uint32_t image_size;
    uint32_t image_crc;
    uint32_t written_image_length;
    uint32_t written_image_crc;
    uint32_t reason;
    uint32_t version;
    uint32_t image_addr;    /* Waring Don't move*/
    uint32_t time[3];

} last_dfu_info_t;

/**
 * @brief dfu manager struct
 */
typedef struct
{
    uint32_t write_addr;
    uint32_t write_length;
    uint32_t write_index;
    uint32_t write_crc;
    uint32_t receive_length;
    uint32_t recevice_index;
    uint32_t uds_timeout;
    uint8_t op_code;
    uint8_t resp_value;
    uint8_t program_flag;
    uint8_t boot_state;
    lin_baudrate_config_t lin_config;
    last_dfu_info_t dfu_info;
    queue_list_t queue_list;
} dfu_manager_context_t;

/**
 * @brief dfu process struct
 */
typedef void (*dfu_func)(uint8_t *, uint16_t);
typedef struct
{
    uint8_t sid;
    dfu_func func;
} dfu_process_context_t;

void dfu_manager_init(void);
void lin_sci_baudrate_update(void);
void dfu_timeout_handle(void);
void main_loops(void);

#ifdef __cplusplus
}
#endif
#endif /* __DFU_UDS_MANAGER_H__ */
