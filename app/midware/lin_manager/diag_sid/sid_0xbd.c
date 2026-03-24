/**
 *****************************************************************************
 * @brief   lin dianosticiii source file.
 *
 * @file    diagnosticiii.c
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

#include "diagnosticIII.h"
#include "utilities.h"
#include "pal_store.h"

/********************************************************
** \brief   soc_reg_write
** \param   uint8_t*                    ptr
** \param   uint16_t                    length
** \retval  None
*********************************************************/
void soc_reg_write(uint8_t *ptr, uint16_t length)
{
    l_u32 addr = 0;
    (void)(&addr);
    l_u32 tt = 0;
    (void)(&tt);

    addr = endian_swap_func((uint8_t *)&ptr[2], sizeof(uint32_t));
    tt   = endian_swap_func((uint8_t *)&ptr[6], sizeof(uint32_t));

    pal_store_reg_rw(true, addr, (uint32_t *)&tt);

    lin_diag_positive_notify(ptr[0], &ptr[2], 8);
}
