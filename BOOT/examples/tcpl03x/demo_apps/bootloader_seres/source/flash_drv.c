/**
 *****************************************************************************
 * @brief   flash driver source file.
 *
 * @file    flash_drv.c
 * @author  AE/FAE team
 * @date    2025.06.05
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2025 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */

#include "stdlib.h"
#include "stdint.h"
#include "tcpl03x_ll_flash.h"

/* #1 this offset should align with scatter file */
#define FLASH_DRV_OFFSET    (0x00000008)
#define CAL_OFFSET(funcPtr) ((uint32_t)(funcPtr) - FLASH_DRV_OFFSET)


typedef uint8_t (*tpfFLASH_DRV_EraseSector) (void);
typedef uint8_t (*tpfFLASH_DRV_Program)     (void);

typedef struct
{
    tpfFLASH_DRV_EraseSector    pfFLASH_DRV_EraseSector;
    tpfFLASH_DRV_Program        pfFLASH_DRV_Program;
} tFlashDriverAPIInfo;




__attribute__((section (".Flash_Driver_Section"))) void ll_flash_erase_reg()
{


    EFLASH->ERASE_TRIG_F.SECTOR_ERASE_TRIG = 1;

    while (EFLASH->STATUS_F.ERASE_BUSY_STATUS == 1)
    {
        ;
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
__attribute__((section (".Flash_Driver_Section"))) void ll_flash_write_reg(uint32_t addr, uint8_t *ptr)
{

    *((volatile uint64_t *)addr) = *((volatile uint64_t *)ptr);
    while (EFLASH->STATUS_F.PROG_BUSY_STATUS == 1)
    {
        ;
    }


}

__attribute__((used)) __attribute__((section (".Flash_Driver_Section_Offset"))) static const tFlashDriverAPIInfo g_FlashDriverAPI = {
    (tpfFLASH_DRV_EraseSector) CAL_OFFSET(ll_flash_erase_reg),
    (tpfFLASH_DRV_Program) CAL_OFFSET(ll_flash_write_reg),
};



