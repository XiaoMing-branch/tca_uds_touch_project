/**
 *****************************************************************************
 * @brief   flash header file.
 *
 * @file    tcpl01x_ll_flash.h
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

#ifndef __TCPL01X_LL_FLASH_H__
#define __TCPL01X_LL_FLASH_H__

#include "tcpl01x.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define  FLASH_BYTE_ALIGN                   (4)

#define FLASH_LOCK_CONFIG()                 (EFLASH->WR_LOCK = 0xFEDCBA98)
#define FLASH_UNLOCK_CONFIG()               (EFLASH->WR_LOCK = 0x76543210)

#define FLASH_LOCK_NVR_ACCESS()              (EFLASH->NVR_PROT = 0xFEDCBA98)
#define FLASH_UNLOCK_NVR_ACCESS()           (EFLASH->NVR_PROT = 0x76543210)

// Main memory (NVM) define
#define  NVM_FLASH_BASE_ADDR                (0x00000000UL)
#define  NVM_FLASH_SIZE                     (0x00010000UL)    //64k
#define  NVM_FLASH_END                      (NVM_FLASH_BASE_ADDR + NVM_FLASH_SIZE)    //64k
#define  FLASH_SECTOR_SIZE                  (512)

// NVR memory define
#define  NVR_FLASH_BASE_ADDR                (0x00800000UL)
#define  NVR_FLASH_SIZE                     (0x00000A00UL)// 2.5k
#define  NVR_FLASH_END_ADDR                 (NVR_FLASH_BASE_ADDR + NVR_FLASH_SIZE)
#define  NVR_FLASH_SECTOR_SIZE              (FLASH_SECTOR_SIZE)

#define  UID_BASE_ADDR_BAK                  (0x0080084CUL)
#define  UID_BASE_ADDR                      (0x00800700UL)

typedef enum
{
    FLASH_TYPE_NVM,
    FLASH_TYPE_NVR,
    FLASH_TYPE_MAX,
} flash_type_e;

void ll_flash_configrctc(uint8_t rcTime);
int ll_flash_erase(flash_type_e type, uint32_t addr, uint32_t length);
int ll_flash_read(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length);
int ll_flash_write(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length);
int ll_flash_smart_write(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length);
int ll_flash_reg_wr(bool is_write, uint32_t addr, uint32_t *reg_value);

#ifdef __cplusplus
}
#endif
#endif /* __TCPL01X_LL_FLASH_H__ */
