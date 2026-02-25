/**
 *****************************************************************************
 * @brief   pal store source file.
 *
 * @file    pal_store.c
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

#include "pal_store.h"
#include "utilities.h"

/********************************************************
** \brief   pal_store_data_set
**
** \param   uint32_t                    addr
** \param   uint8_t*                    data
** \param   uint16_t                    length
**
** \retval  None
*********************************************************/
void pal_store_data_set(uint32_t addr, uint8_t *data, uint16_t length)
{
    uint8_t nvrdata[STORE_SECTOR_SIZE] __attribute((aligned(4)));
    uint32_t offset = addr % STORE_SECTOR_SIZE;
    uint32_t crc __attribute__((unused));

    ll_flash_read(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);

    if (memcmp((uint8_t *)&nvrdata[offset], data, length))
    {
        memcpy((uint8_t *)&nvrdata[offset], data, length);
        crc = crc16_calculate_func(0xFFFF, (uint8_t *)&nvrdata[offset], length);
        memcpy(&nvrdata[offset + length], &crc, sizeof(uint32_t));
        ll_flash_smart_write(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);
    }
}

/********************************************************
** \brief   pal_store_data_get
**
** \param   uint32_t                    addr
** \param   uint8_t*                    data
** \param   uint16_t                    length
**
** \retval  bool
*********************************************************/
bool pal_store_data_get(uint32_t addr, uint8_t *data, uint16_t length)
{
    uint8_t nvrdata[STORE_SECTOR_SIZE] __attribute((aligned(4)));
    uint32_t offset = addr % STORE_SECTOR_SIZE;
    uint32_t crc;

    ll_flash_read(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);

    memcpy((uint8_t *)&crc, (uint8_t *)&nvrdata[offset + length], sizeof(uint32_t));

    if (crc == crc16_calculate_func(0xFFFF, (uint8_t *)&nvrdata[offset], length))
    {
        memcpy((uint8_t *)data, (uint8_t *)&nvrdata[offset], length);
        return true;
    }

    return false;
}

/********************************************************
** \brief   pal_store_data_init
**
** \param   uint32_t                    addr
** \param   uint8_t*                    data
** \param   uint16_t                    length
**
** \retval  bool
*********************************************************/
bool pal_store_data_init(uint32_t addr, uint8_t *data, uint16_t length)
{
    uint8_t nvrdata[STORE_SECTOR_SIZE] __attribute((aligned(4)));
    uint32_t offset = addr % STORE_SECTOR_SIZE;
    uint32_t crc;

    ll_flash_read(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);

    memcpy((uint8_t *)&crc, (uint8_t *)&nvrdata[offset + length], sizeof(uint32_t));

    if (crc != crc16_calculate_func(0xFFFF, (uint8_t *)&nvrdata[offset], length))
    {
        memcpy((uint8_t *)&nvrdata[offset], (uint8_t *)data, length);
        crc = crc16_calculate_func(0xFFFF, (uint8_t *)&nvrdata[offset], length);
        memcpy(&nvrdata[offset + length], (uint8_t *)&crc, sizeof(uint32_t));
        ll_flash_smart_write(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);
        return false;
    }

    memcpy(data, &nvrdata[offset], length);

    return true;
}

/********************************************************
** \brief   pal_store_data_clear
**
** \param   uint32_t                    addr
** \param   uint16_t                    length
**
** \retval  bool
*********************************************************/
bool pal_store_data_clear(uint32_t addr, uint16_t length)
{
    uint32_t offset = addr % STORE_SECTOR_SIZE;

    if (!offset && !(length % STORE_SECTOR_SIZE))
    {
        ll_flash_erase(STORE_TYPE_SEL, addr, length);
    }
    else
    {
        uint8_t nvrdata[STORE_SECTOR_SIZE] __attribute((aligned(4)));
        ll_flash_read(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);
        memset((uint8_t *)&nvrdata[offset], 0xFF, length);
        ll_flash_smart_write(STORE_TYPE_SEL, addr - offset, (uint8_t *)nvrdata, STORE_SECTOR_SIZE);
    }

    return true;
}

/********************************************************
** \brief   pal_store_erase
**
** \param   flash_type_e    type
** \param   uint32_t        addr
** \param   uint16_t        length
**
** \retval  bool
*********************************************************/
bool pal_store_erase(flash_type_e type, uint32_t addr, uint16_t length)
{
    if (0 != ll_flash_erase(type, addr, length))
    {
        return false;
    }

    return true;
}

/********************************************************
** \brief   pal_store_write
**
** \param   flash_type_e    type
** \param   uint32_t        addr
** \param   uint8_t*        value
** \param   uint16_t        length
**
** \retval  bool
*********************************************************/
bool pal_store_write(flash_type_e type, uint32_t addr, uint8_t *value, uint16_t length)
{
    if (0 != ll_flash_write(type, addr, value, length))
    {
        return false;
    }

    return true;
}

/********************************************************
** \brief   pal_store_read
**
** \param   flash_type_e    type
** \param   uint32_t        addr
** \param   uint8_t*        value
** \param   uint16_t        length
**
** \retval  bool
*********************************************************/
bool pal_store_read(flash_type_e type, uint32_t addr, uint8_t *value, uint16_t length)
{
    if (0 != ll_flash_read(type, addr, value, length))
    {
        return false;
    }

    return true;
}

/********************************************************
** \brief   Return the unique device identifier (UID based on 96 bits)
**
** \param   uint32_t        *uid
**
** \retval  None
*********************************************************/
void pal_store_uid_get(uint32_t *uid)
{
#if defined (__TCPL01X__)
    uint32_t buffer[5];

    ll_flash_read(STORE_TYPE_SEL, UID_BASE_ADDR, (uint8_t *)&buffer[0], 3 * sizeof(uint32_t));

    if (buffer[0] == 0xFFFFFFFF && buffer[1] == 0xFFFFFFFF && buffer[2] == 0xFFFFFFFF)
    {
        ll_flash_read(STORE_TYPE_SEL, UID_BASE_ADDR_BAK, (uint8_t *)&buffer[0], 5 * sizeof(uint32_t));

        buffer[2] = ((buffer[2] & 0xFF) << 24) | ((buffer[3] & 0xFF) << 16) | ((buffer[4] & 0xFF)  << 8) | 0xFF;
    }

    memcpy((uint8_t *)uid, (uint8_t *)&buffer[0], 3 * sizeof(uint32_t));
#endif
}

/********************************************************
** \brief   Return the unique device identifier (UID based on 96 bits)
**
** \param   uint32_t        *boot_ver
**
** \retval  None
*********************************************************/
void pal_store_boot_ver_get(uint32_t *boot_ver)
{
    uint32_t ver;
    ll_flash_read(FLASH_TYPE_NVM, BOOT_VERSION_ADDR, (uint8_t *)&ver, sizeof(uint32_t));
    ver = (ver & 0xFF) * 10000 + ((ver & 0xFF00) >> 8)  * 100 + ((ver & 0xFF0000) >> 16) ;
    memcpy((uint8_t *)boot_ver, (uint8_t *)&ver, sizeof(ver));
}

/********************************************************
** \brief   pal_store_chip_ver_id_get
**
** \param   uint8_t*        chip_ver
** \param   uint16_t*       chip_id
**
** \retval  None
*********************************************************/
void pal_store_chip_ver_id_get(uint8_t *chip_ver, uint16_t *chip_id)
{
    ll_syscfg_info_get(chip_ver, chip_id);
}

/********************************************************
** \brief   pal_store_reg_rw
**
** \param   bool            is_write
** \param   uint32_t        addr
** \param   uint32_t        *value
**
** \retval  None
*********************************************************/
void pal_store_reg_rw(bool is_write, uint32_t addr, uint32_t *value)
{
    ll_flash_reg_wr(is_write, addr, value);
}
