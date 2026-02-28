/**
 *****************************************************************************
 * @brief   syscfg Source file.
 *
 * @file    tcpl01x_ll_sys.c
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

#include "tcpl01x_ll_sys.h"
#include "tcpl01x_ll_def.h"
#include "tcpl01x_ll_cortex.h"

/********************************************************
** \brief   ll_syscfg_info_get
**
** \param   uint8_t   *revision_id : a pointer to hold revision ID when it being read
** \param   uint16_t  *chip_id : a pointer to hold chip ID when it being read
**
** \retval  None
*********************************************************/
void ll_syscfg_info_get(uint8_t *revision_id, uint16_t *chip_id)
{
    SYSCFG_UNLOCK();

    if (NULL != chip_id)
    {
        *chip_id = (uint16_t)(SYSCFG->REVISION_F.CHIP_ID);
    }

    if (NULL != revision_id)
    {
        *revision_id = (uint8_t)(SYSCFG->REVISION_F.REV_ID);
    }

    SYSCFG_LOCK();
}

/********************************************************
** \brief   ll_syscfg_afeinfo_get
**
** \param   uint8_t   *revision_id : a pointer to hold revision ID when it being read
** \param   uint16_t  *chip_id : a pointer to hold chip ID when it being read
**
** \retval  None
*********************************************************/
void ll_syscfg_afeinfo_get(uint8_t *revision_id, uint16_t *chip_id)
{
    uint32_t val = 0;

    afe_reg_read(&AFE_SYSCFG->REVISION, &val);

    if (NULL != chip_id)
    {
        *chip_id = (uint16_t) val ;
    }

    if (NULL != revision_id)
    {
        *revision_id = (uint8_t)(val >> 16);
    }
}
