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

extern void wdg_enable(bool enable);

/********************************************************
** \brief   lin_diag_ecu_reset
** \param   uint8_t*                    ptr
** \param   uint16_t                    length
** \retval  None
*********************************************************/
void lin_diag_ecu_reset(uint8_t *ptr, uint16_t length)
{
    switch (ptr[1])
    {
        /* ISO14429 还支持好几种复位 to do */
        case 0x01:
            /* hardware reset  to do*/
            lin_diag_positive_notify(ptr[0], &ptr[1], 1);
            wdg_enable(false);
            NVIC_SystemReset();
            break;

        default :
            lin_diag_negative_notify(ptr[0], SFNS);
            break;
    }
}
