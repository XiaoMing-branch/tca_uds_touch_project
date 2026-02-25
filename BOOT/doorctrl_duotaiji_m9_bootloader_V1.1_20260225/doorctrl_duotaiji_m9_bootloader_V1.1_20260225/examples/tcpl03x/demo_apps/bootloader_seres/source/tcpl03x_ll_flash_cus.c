/**
 *****************************************************************************
 * @brief   flash Source file.
 *
 * @file    tcpl03x_ll_flash.c
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

#include "tcpl03x.h"
#include "system_tcpl03x.h"
#include "tcpl03x_ll_flash.h"

#define FLASH_WR_BYTE_ALIGN (8)
#define FLASH_DRV_CIPER_SIZE (56)

#if 8 == FLASH_WR_BYTE_ALIGN
typedef uint64_t flash_size_t;
#else
typedef uint32_t flash_size_t;
#endif

extern uint8_t flash_driver[];
typedef uint8_t (*tpfFLASH_DRV_EraseSector)(void);
typedef uint8_t (*tpfFLASH_DRV_Program)(uint32_t addr, uint8_t *ptr);

uint8_t flash_driver_ciper[FLASH_DRV_CIPER_SIZE] =
    {
        0x02, 0x01, 0x01, 0x01, 0x1A, 0x01, 0x01, 0x01,
        0x05, 0x49, 0x02, 0x69, 0x02, 0x23, 0x0B, 0x44,
        0x03, 0x61, 0xC2, 0x6B, 0x8A, 0x08, 0xFD, 0xD5,
        0x71, 0x48, 0xC1, 0x47, 0x21, 0x01, 0xFF, 0x01,
        0x0B, 0x69, 0x4A, 0x69, 0x42, 0x61, 0x03, 0x61,
        0x03, 0x49, 0x02, 0x69, 0x4A, 0x08, 0xFD, 0xD5,
        0x71, 0x48, 0xC1, 0x47, 0x4D, 0x01, 0xFF, 0x01};

tpfFLASH_DRV_EraseSector g_pfFLASH_DRV_EraseSector = (tpfFLASH_DRV_EraseSector)(0x10000009u);
tpfFLASH_DRV_Program g_tpfFLASH_DRV_Program = (tpfFLASH_DRV_Program)(0x10000021u);
/********************************************************
** \brief   This function initializes flash
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_flash_init(void)
{
    FLASH_UNLOCK_CONFIG();

    /*Read Timing configuration*/
    EFLASH->RD_TIME_CFG = 0X00003033;
    /*Recovery Timing configuration*/
    EFLASH->RCV_TIME_CFG = 0x00035CDC;
    /*Erase or program to WE setup timing configuration*/
    EFLASH->NVS_TIME_CFG = 0x00016058;
    /*Program timing configuration*/
    EFLASH->PROG_TIME_CFG = 0x00161ADC;
    /*Erase timing configuration*/
    EFLASH->ERASE_TIME_CFG = 0x00000809;
    /*Latency timing configuration*/
    EFLASH->LATENCY_TIME_CFG = 0x0000301A;

    FLASH_LOCK_CONFIG();
}

/********************************************************
** \brief   ll_flash_sector_get
**
** \param   flash_type_e    type
** \param   uint32_t        addr
**
** \retval  uint16_t sector index
*********************************************************/
static uint16_t ll_flash_sector_get(flash_type_e type, uint32_t addr)
{
    return ((addr - NVM_FLASH_BASE_ADDR) >> 9);
}

/********************************************************
** \brief   ll_flash_addr_valid_check
**
** \param   flash_type_e    type
** \param   uint32_t        addr
** \param   uint32_t        length
**
** \retval  uint8_t         sector index
*********************************************************/
static uint8_t ll_flash_addr_valid_check(flash_type_e type, uint32_t addr, uint32_t length)
{
    return (!((addr + length) > NVM_FLASH_SIZE));
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

    EFLASH->OP_CTRL_F.RDONLY_EN = false;

    for (uint32_t index = sector_start; index < sector_end; index++)
    {
        /* erase sector */
        EFLASH->ERASE_CFG_F.SECTOR_INDEX = index;
        // g_pfFLASH_DRV_EraseSector();
        EFLASH->ERASE_TRIG_F.SECTOR_ERASE_TRIG = 1;

        while (EFLASH->STATUS_F.ERASE_BUSY_STATUS == 1)
        {
            ;
        }
    }

    EFLASH->OP_CTRL_F.RDONLY_EN = true;
}

static void ll_flash_erase_reg_drv(flash_type_e type, uint32_t addr, uint32_t length)
{
    uint16_t sector_start = ll_flash_sector_get(type, addr);
    uint16_t sector_end = ll_flash_sector_get(type, (addr + length - 1)) + 1;

    EFLASH->OP_CTRL_F.RDONLY_EN = false;

    for (uint32_t index = sector_start; index < sector_end; index++)
    {
        /* erase sector */
        EFLASH->ERASE_CFG_F.SECTOR_INDEX = index;
        __disable_irq();
        g_pfFLASH_DRV_EraseSector();
        __enable_irq();
    }

    EFLASH->OP_CTRL_F.RDONLY_EN = true;
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
    uint32_t remain_length, reseverd_length;
    flash_size_t temp_data;
    uint32_t offset = 0;
    uint8_t *ptr = (uint8_t *)&temp_data;

#if 8 == FLASH_WR_BYTE_ALIGN
    temp_data = 0xFFFFFFFFFFFFFFFF;
#else
    temp_data = 0xFFFFFFFF;
#endif

    EFLASH->OP_CTRL_F.RDONLY_EN = false;

    remain_length = length;
    reseverd_length = remain_length % FLASH_WR_BYTE_ALIGN;

    if (remain_length > reseverd_length)
    {
        for (uint32_t i = 0; i < remain_length - reseverd_length; i += FLASH_WR_BYTE_ALIGN)
        {
            memcpy((uint8_t *)ptr, (uint8_t *)(buffer + offset), sizeof(flash_size_t));
            // g_tpfFLASH_DRV_Program(addr + offset, ptr);
            *((volatile flash_size_t *)(addr + offset)) = *((volatile flash_size_t *)ptr);
            while (EFLASH->STATUS_F.PROG_BUSY_STATUS == 1)
            {
                ;
            }
            offset += FLASH_WR_BYTE_ALIGN;
        }
    }

    if (reseverd_length)
    {
#if 8 == FLASH_WR_BYTE_ALIGN
        temp_data = 0xFFFFFFFFFFFFFFFF;
#else
        temp_data = 0xFFFFFFFF;
#endif
        memcpy((uint8_t *)ptr, (uint8_t *)&buffer[length - reseverd_length], reseverd_length);
        *((volatile flash_size_t *)(addr + offset)) = *((volatile flash_size_t *)ptr);

        while (EFLASH->STATUS_F.PROG_BUSY_STATUS == 1)
        {
            ;
        }
    }

    EFLASH->OP_CTRL_F.RDONLY_EN = true;
}

static void ll_flash_write_reg_drv(uint32_t addr, uint8_t *buffer, uint32_t length)
{
    uint32_t remain_length, reseverd_length;
    flash_size_t temp_data;
    uint32_t offset = 0;
    uint8_t *ptr = (uint8_t *)&temp_data;

#if 8 == FLASH_WR_BYTE_ALIGN
    temp_data = 0xFFFFFFFFFFFFFFFF;
#else
    temp_data = 0xFFFFFFFF;
#endif

    EFLASH->OP_CTRL_F.RDONLY_EN = false;

    remain_length = length;
    reseverd_length = remain_length % FLASH_WR_BYTE_ALIGN;

    if (remain_length > reseverd_length)
    {
        for (uint32_t i = 0; i < remain_length - reseverd_length; i += FLASH_WR_BYTE_ALIGN)
        {
            memcpy((uint8_t *)ptr, (uint8_t *)(buffer + offset), sizeof(flash_size_t));
            __disable_irq();
            g_tpfFLASH_DRV_Program(addr + offset, ptr);
            __enable_irq();
            offset += FLASH_WR_BYTE_ALIGN;
        }
    }

    if (reseverd_length)
    {
#if 8 == FLASH_WR_BYTE_ALIGN
        temp_data = 0xFFFFFFFFFFFFFFFF;
#else
        temp_data = 0xFFFFFFFF;
#endif
        memcpy((uint8_t *)ptr, (uint8_t *)&buffer[length - reseverd_length], reseverd_length);
        __disable_irq();
        g_tpfFLASH_DRV_Program(addr + offset, ptr);
        __enable_irq();

    }

    EFLASH->OP_CTRL_F.RDONLY_EN = true;
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
    uint32_t remain_length, reseverd_length;
    flash_size_t temp_data;

    uint32_t offset = addr % FLASH_BYTE_ALIGN;
    uint8_t *ptr = (uint8_t *)&temp_data;
    uint32_t read_len __attribute__((unused));

    if (offset)
    {
        *((volatile flash_size_t *)ptr) = *((volatile flash_size_t *)(addr - offset));
        read_len = (length > (FLASH_WR_BYTE_ALIGN - offset)) ? FLASH_WR_BYTE_ALIGN - offset : length;
        memcpy((uint8_t *)(buffer), (uint8_t *)(ptr + offset), read_len);
        offset = read_len;
    }

    remain_length = length - offset;
    reseverd_length = remain_length % FLASH_WR_BYTE_ALIGN;

    if (remain_length > reseverd_length)
    {
        for (uint32_t i = 0; i < remain_length - reseverd_length; i += FLASH_WR_BYTE_ALIGN)
        {

            *((volatile flash_size_t *)ptr) = *((volatile flash_size_t *)(addr + offset));
            memcpy((uint8_t *)(buffer + offset), (uint8_t *)ptr, sizeof(flash_size_t));
            offset += FLASH_WR_BYTE_ALIGN;
        }
    }

    if (reseverd_length)
    {
        *((volatile flash_size_t *)ptr) = *((volatile flash_size_t *)(addr + offset));

        memcpy((uint8_t *)(buffer + offset), (uint8_t *)ptr, reseverd_length);
    }
}

/********************************************************
** \brief   ll_flash_erase_chip
**
** \param   None
**
** \retval  uint8_t         0-success
*********************************************************/
int ll_flash_erase_chip(void)
{
    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;
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
** \brief   ll_flash_erase  flash erase func
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
int ll_flash_erase(flash_type_e type, uint32_t addr, uint32_t length)
{
    int res = 0;

    if ((FLASH_TYPE_NVM != type) || (false == ll_flash_addr_valid_check(type, addr, length)))
    {
        return -1;
    }

    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;

    ll_flash_erase_reg(type, addr, length);

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();

    return res;
}

int ll_flash_erase_drv(flash_type_e type, uint32_t addr, uint32_t length)
{
    int res = 0;

    if ((FLASH_TYPE_NVM != type) || (false == ll_flash_addr_valid_check(type, addr, length)))
    {
        return -1;
    }

    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;

    ll_flash_erase_reg_drv(type, addr, length);

    FLASH_LOCK_CONFIG();

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

    ll_flash_read_reg(addr, buffer, length);

    return 0;
}

/********************************************************
** \brief   ll_flash_write
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
int ll_flash_write(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length)
{
    if ((FLASH_TYPE_NVM != type) || (false == ll_flash_addr_valid_check(type, addr, length)))
    {
        return -1;
    }

    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;

    ll_flash_write_reg(addr, buffer, length);

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();

    return 0;
}

int ll_flash_write_drv(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length)
{
    if ((FLASH_TYPE_NVM != type) || (false == ll_flash_addr_valid_check(type, addr, length)))
    {
        return -1;
    }

    /*mask all interupt but NMI and HardFault*/
    __disable_irq();

    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;

    ll_flash_write_reg_drv(addr, buffer, length);

    FLASH_LOCK_CONFIG();

    /*resume all interupt enabled*/
    __enable_irq();

    return 0;
}

/********************************************************
** \brief   ll_flash_smart_write
**
** \param   flash_type_e    type:0-NVM 1-NVR
** \param   uint32_t        addr
** \param   uint8_t*        buffer
** \param   uint32_t        length
**
** \retval  int             0-success
*********************************************************/
int ll_flash_smart_write(flash_type_e type, uint32_t addr, uint8_t *buffer, uint32_t length)
{
    if ((FLASH_TYPE_NVM != type) || (false == ll_flash_addr_valid_check(type, addr, length)))
    {
        return -1;
    }
    /* remap flash driver */
    for (int i = 0; i < FLASH_DRV_CIPER_SIZE; i++)
    {
        flash_driver[i] = flash_driver_ciper[i] - 1;
    }
    flash_driver[30] = 0xFF;
    flash_driver[54] = 0xFF;


    FLASH_UNLOCK_CONFIG();

    EFLASH->ERASE_CFG_F.NVR_SECTOR_SEL = 0;

    ll_flash_erase_reg_drv(type, addr, length);
    ll_flash_write_reg_drv(addr, buffer, length);

    FLASH_LOCK_CONFIG();

    /* destroy flash driver */
    memset(flash_driver, 0, FLASH_DRV_CIPER_SIZE);
    return 0;
}

/********************************************************
** \brief   ll_flash_reg_wr
**
** \param   bool            is_write:write read
** \param   uint32_t        addr
** \param   uint32_t        *reg_value
**
** \retval  int             0-success
*********************************************************/
int ll_flash_reg_wr(bool is_write, uint32_t addr, uint32_t *reg_value)
{
    /* APB_SLV address */
    if (addr > APB_BASE_ADDRESS)
    {
        if (is_write)
        {
            REG_WRITE32(addr, *reg_value);
        }
        else
        {
            *reg_value = REG_READ32(addr);
        }
    }

    {
        *reg_value = REG_READ32(addr);
    }

    return 0;
}

/********************************************************
** \brief   ll_flash_isr_enable
**
** \param   uint32_t        isr_flag
** \param   bool            enable
**
** \retval  int             0-success
*********************************************************/
int ll_flash_isr_enable(uint32_t isr_flag, bool enable)
{
    FLASH_UNLOCK_CONFIG();

    if (enable)
    {
        EFLASH->IMR &= ~(isr_flag);
    }
    else
    {
        EFLASH->IMR |= isr_flag;
    }

    FLASH_LOCK_CONFIG();

    return 0;
}

/********************************************************
** \brief   FLASH_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
void FLASH_IRQHandler(void)
{
    uint32_t isr = EFLASH->ISR;

    FLASH_UNLOCK_CONFIG();

    EFLASH->ICR = isr;

    FLASH_LOCK_CONFIG();
}
