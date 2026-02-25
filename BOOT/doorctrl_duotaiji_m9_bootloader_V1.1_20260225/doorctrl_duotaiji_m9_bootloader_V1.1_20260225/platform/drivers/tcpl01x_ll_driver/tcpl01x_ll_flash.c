/**
 *****************************************************************************
 * @brief   flash Source file.
 *
 * @file    tcpl01x_ll_flash.c
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

#include "tcpl01x.h"
#include "system_tcpl01x.h"
#include "tcpl01x_ll_flash.h"

/********************************************************
** \brief   ll_flash_configrctc
**
** \param   uint8_t      rcTime
**
** \retval  void
*********************************************************/
void ll_flash_configrctc(uint8_t rcTime)
{
    FLASH_UNLOCK_CONFIG();
    EFLASH->RD_TIME_CFG_F.RC_CYC = rcTime;      /** Read time (HCLK) ,  reset:1*/
    FLASH_LOCK_CONFIG();
}

/********************************************************
** \brief   HAL_Flash_Erase
**
** \param   FLASH_TYPE_E    flash_type
** \param   uint32_t        addr
**
** \retval  uint16_t        sector index
*********************************************************/
static uint16_t ll_flash_sector_get(flash_type_e type, uint32_t addr)
{
    uint32_t base_addr = FLASH_TYPE_NVM == type ? NVM_FLASH_BASE_ADDR : NVR_FLASH_BASE_ADDR;
    uint32_t sector = (addr - base_addr) >> 9;

    return sector;
}

/********************************************************
** \brief   HAL_Flash_Erase
**
** \param   FLASH_TYPE_E    flash_type
** \param   uint32_t        addr
** \param   uint32_t        length
**
** \retval  uint8_t         sector index
*********************************************************/
static uint8_t ll_flash_addr_valid_check(flash_type_e type, uint32_t addr, uint32_t length)
{
    uint8_t res = true;

    if (type >= FLASH_TYPE_MAX)
    {
        return false;
    }

    if (FLASH_TYPE_NVM == type)
    {
        res = !((addr + length) > NVM_FLASH_SIZE);
    }
    else
    {
        res = !((addr + length) > NVR_FLASH_END_ADDR || addr < NVR_FLASH_BASE_ADDR);
    }

    return res;
}

/********************************************************
** \brief   ll_flash_erase_reg
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint32_t        length
**
** \retval  None
*********************************************************/
static void ll_flash_erase_reg(flash_type_e type, uint32_t addr, uint32_t length)
{
    uint16_t sector_start = ll_flash_sector_get(type, addr);
    uint16_t sector_end = ll_flash_sector_get(type, (addr + length - 1)) + 1;

    for (uint32_t index = sector_start; index < sector_end; index++)
    {
        /* erase sector */
        EFLASH->ERASE_CFG_F.SECTOR_INDEX = index;
        EFLASH->ERASE_TRIG_F.SECTOR_ERASE_TRIG = 1;

        while (EFLASH->STATUS_F.ERASE_BUSY_STATUS == 1)
        {
            ;
        }
    }
}

/********************************************************
** \brief   ll_flash_write_reg
**
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  None
*********************************************************/
static void ll_flash_write_reg(uint32_t addr, uint8_t *buffer, uint32_t length)
{
    uint32_t temp_data, remain_length, reseverd_length;

    uint32_t offset = addr % FLASH_BYTE_ALIGN;
    uint8_t *ptr = (uint8_t *)&temp_data;
    uint32_t write_len __attribute__((unused));

    if (offset)
    {
        temp_data = 0xFFFFFFFF;
        *((volatile uint32_t *)ptr) = *((volatile uint32_t *)(addr - offset)); //读出
        write_len = (length > (FLASH_BYTE_ALIGN - offset)) ? FLASH_BYTE_ALIGN - offset : length;
        memcpy((uint8_t *)(ptr + offset), (uint8_t *)buffer, write_len); //补齐赋值
        *((volatile uint32_t *)(addr - offset)) = *((volatile uint32_t *)ptr); //回写
        offset = write_len;
    }

    remain_length = length - offset;
    reseverd_length = remain_length % FLASH_BYTE_ALIGN;

    if (remain_length > reseverd_length)
    {
        for (uint32_t i = 0; i < remain_length - reseverd_length; i += 4)
        {

            memcpy((uint8_t *)ptr, (uint8_t *)(buffer + offset), sizeof(uint32_t));
            *((volatile uint32_t *)(addr + offset)) = *((volatile uint32_t *)ptr);

            while (EFLASH->STATUS_F.PROG_BUSY_STATUS == 1)
            {
                ;
            }

            offset += 4;
        }
    }

    if (reseverd_length)
    {
        temp_data = 0xFFFFFFFF;

        memcpy((uint8_t *)ptr, (uint8_t *)&buffer[length - reseverd_length], reseverd_length);

        *((volatile uint32_t *)(addr + offset)) = *((volatile uint32_t *)ptr) ;

        while (EFLASH->STATUS_F.PROG_BUSY_STATUS == 1)
        {
            ;
        }
    }
}

/********************************************************
** \brief   ll_flash_read_reg
**
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  None
*********************************************************/
static void ll_flash_read_reg(uint32_t addr, uint8_t *buffer, uint32_t length)
{
    uint32_t temp_data, remain_length, reseverd_length;

    uint32_t offset = addr % FLASH_BYTE_ALIGN;
    uint8_t *ptr = (uint8_t *)&temp_data;
    uint32_t read_len __attribute__((unused));

    if (offset)
    {
        *((volatile uint32_t *)ptr) = *((volatile uint32_t *)(addr - offset));
        read_len = (length > (FLASH_BYTE_ALIGN - offset)) ? FLASH_BYTE_ALIGN - offset : length;
        memcpy((uint8_t *)(buffer), (uint8_t *)(ptr + offset), read_len);
        offset = read_len;
    }

    remain_length = length - offset;
    reseverd_length = remain_length % FLASH_BYTE_ALIGN;

    if (remain_length > reseverd_length)
    {
        for (uint32_t i = 0; i < remain_length - reseverd_length; i += 4)
        {

            *((volatile uint32_t *)ptr) = *((volatile uint32_t *)(addr + offset));
            memcpy((uint8_t *)(buffer + offset), (uint8_t *)ptr, sizeof(uint32_t));
            offset += 4;
        }
    }

    if (reseverd_length)
    {
        *((volatile uint32_t *)ptr) = *((volatile uint32_t *)(addr + offset));

        memcpy((uint8_t *)(buffer + offset), (uint8_t *)ptr, reseverd_length);
    }
}

/********************************************************
** \brief   ll_flash_erase_chip
**
** \param   None
**
** \retval  int             0-success
*********************************************************/
#if defined   (__ICCARM__)     /* iar */
#pragma location = "RAMUSERCODE"
#elif defined (__ARMCC_VERSION)       /* keil */
__attribute__((section("RAMCODE")))
#endif
int ll_flash_erase_chip(void)
{
    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 1; //?1????????
    EFLASH->ERASE_TRIG_F.CHIP_ERASE_TRIG = 1;

    while (EFLASH->STATUS_F.ERASE_BUSY_STATUS == 1)
    {
        ;
    }

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();

    return 0;
}

/********************************************************
** \brief   ll_flash_erase     flash erase func
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
#if defined   (__ICCARM__)     /* iar */
#pragma location = "RAMUSERCODE"
#elif defined (__ARMCC_VERSION)       /* keil */
__attribute__((section("RAMCODE")))
#endif
int ll_flash_erase(flash_type_e type, uint32_t addr, uint32_t length)
{
    int res = 0;

    if (false == ll_flash_addr_valid_check(type, addr, length))
    {
        return -1;
    }

    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_UNLOCK_NVR_ACCESS();
        EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 1;
    }
    else if (FLASH_TYPE_NVM == type)
    {
        EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;
    }

    ll_flash_erase_reg(type, addr, length);

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_LOCK_NVR_ACCESS();
    }

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();

    return res;
}

/********************************************************
** \brief   ll_flash_read      flash read func
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
int ll_flash_read(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length)
{
    if (false == ll_flash_addr_valid_check(type, addr, length))
    {
        return -1;
    }

    FLASH_UNLOCK_CONFIG();

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_UNLOCK_NVR_ACCESS();
    }

    ll_flash_read_reg(addr, buffer, length);

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_LOCK_NVR_ACCESS();
    }

    FLASH_LOCK_CONFIG();

    return 0;
}

/********************************************************
** \brief   ll_flash_write FLASH write
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
#if defined   (__ICCARM__)     /* iar */
#pragma location = "RAMUSERCODE"
#elif defined (__ARMCC_VERSION)       /* keil */
__attribute__((section("RAMCODE")))
#endif
int ll_flash_write(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length)
{
    if (false == ll_flash_addr_valid_check(type, addr, length))
    {
        return -1;
    }

    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_UNLOCK_NVR_ACCESS();
    }

    ll_flash_write_reg(addr, buffer, length);

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_LOCK_NVR_ACCESS();
    }

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();
    return 0;
}

/********************************************************
** \brief   ll_flash_smart_write FLASH smart write
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
#if defined   (__ICCARM__)     /* iar */
#pragma location = "RAMUSERCODE"
#elif defined (__ARMCC_VERSION)       /* keil */
__attribute__((section("RAMCODE")))
#endif
int ll_flash_smart_write(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length)
{
    if (false == ll_flash_addr_valid_check(type, addr, length))
    {
        return -1;
    }

    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_UNLOCK_NVR_ACCESS();
        EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 1;
    }
    else if (FLASH_TYPE_NVM == type)
    {
        EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;
    }

    ll_flash_erase_reg(type, addr, length);
    ll_flash_write_reg(addr, buffer, length);

    if (FLASH_TYPE_NVR == type)
    {
        FLASH_LOCK_NVR_ACCESS();
    }

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();

    return 0;
}

/********************************************************
** \brief   ll_flash_reg_wr
**
** \param   boot            is_write
** \param   uint32_t        addr
** \param   uint32_t*       reg_value
**
** \retval  int             0-success
*********************************************************/
int ll_flash_reg_wr(bool is_write, uint32_t addr, uint32_t *reg_value)
{
    if (is_write)
    {
        if (addr < AFE_SYSCFG_BASE_ADDR)
        {
            *(volatile uint32_t *)(addr) = *reg_value;

        }
        else
        {
            afe_reg_write(&(*(volatile uint32_t *)(addr)), *reg_value);
        }
    }
    else
    {
        if (addr < AFE_SYSCFG_BASE_ADDR)
        {
            if ((addr >= NVR_FLASH_BASE_ADDR) && (addr <= 0x00800800))
            {
                ll_flash_read(FLASH_TYPE_NVR, addr, (uint8_t *)reg_value, sizeof(uint32_t));
            }
            else
            {
                *reg_value = *(uint32_t *)(addr);
            }
        }
        else
        {

            afe_reg_read(&(*(volatile uint32_t *)(addr)), reg_value);
        }

    }

    return 0;
}
