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

#include "lin_precfg.h"

#if LIN_PROTOCOL == PROTOCOL_21
/********************************************************
** \brief   lin_diag_assign_frame_id_range
** \param   uint8_t*                    ptr
** \param   uint16_t                    length
** \retval  None
*********************************************************/
void lin_diag_assign_frame_id_range(uint8_t *ptr, uint16_t length)
{
    uint8_t start_index;
    uint8_t i, j;
    uint8_t fid;

    if (length != 6)
    {
        lin_diag_negative_notify(ptr[0], GENERAL_REJECT);
        return;
    }

    start_index = ptr[1];

    for (i = 5, j = start_index + 4; j > start_index; i--, j--)
    {
        if (ptr[i] != 0xFF && j > lin_cfg.lin_cfg_frame_num)
        {
            //lin_diag_negative_notify(ptr[0], GENERAL_REJECT);
            return;
        }
    }

    /* Store PIDs */
    for (i = 2, j = start_index + 1; i < length; i++, j++)
    {
        switch (ptr[i])
        {
            case 0x00:
                /* Unassign frame */
                lin_configuration_RAM[j] = 0xFF;
                break;

            case 0xFF:
                /* keep the previous assigned value of this frame */
                break;

            default:
                /* Calculate frame ID & Assign ID to frame */
                fid = lin_process_parity(ptr[i], CHECK_PARITY);
                if (0xFF == fid)
                {
                    lin_diag_negative_notify(ptr[0], GENERAL_REJECT);
                    return;
                }
                else
                {
                    lin_configuration_RAM[j] = fid;
                }
                break;
        }
    } /* End of for statement */

    lin_diag_positive_notify(ptr[0], NULL, 0);
}
#endif
