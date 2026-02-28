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

l_u8 slave_resp_dat[MAX_QUEUE_SIZE * 6 - 1];
l_u16 slave_resp_length;

/********************************************************
** \brief   lin_diag_service_handle
**
** \param   None
**
** \retval  None
*********************************************************/
void lin_diag_service_handle(void)
{
    uint16_t length;
    uint8_t data[MAX_QUEUE_SIZE * 6 - 1];

    for (uint8_t i = 0; i < _DIAG_NUMBER_OF_SERVICES_; i++)
    {
        if (lin_diag_services_flag[i])
        {
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
            /* get pdu from rx queue */
            ld_receive_message(&length, data);
#else /* Single frame support */

            for (uint8_t index = 2; i < 8; i++)
            {
                data[data_index++] = (*tl_current_rx_pdu_ptr)[2];
            }

            length = (*tl_current_rx_pdu_ptr)[1] & 0x0F
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */

            switch (lin_diag_services_supported[i])
            {
                case SERVICE_READ_BY_IDENTIFY:/* Mandatory for TL LIN 2.1 & 2.0, Optional for J2602 */
                    lin_diag_read_by_identifier(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_SAVE_CONFIGURATION:
                    lin_diag_save_configuration(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_ASSIGN_NAD:
#if LIN_PROTOCOL == PROTOCOL_J2602
                    lin_assign_nad_j2602(data, length);
#else
                    lin_diag_assign_nad(data, length);
#endif
                    lin_diag_services_flag[i] = 0;
                    break;

#if LIN_PROTOCOL == PROTOCOL_21

                case SERVICE_ASSIGN_FRAME_ID_RANGE:    /* Mandatory for TL LIN 2.1 */
                    lin_diag_assign_frame_id_range(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;
#endif

#if LIN_PROTOCOL != PROTOCOL_J2602

                case SERVICE_CONDITIONAL_CHANGE_NAD:
                    lin_diag_conditional_change_nad(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;
#endif

#if ((LIN_PROTOCOL == PROTOCOL_20) || (LIN_PROTOCOL == PROTOCOL_J2602))

                case SERVICE_ASSIGN_FRAME_ID:
                    lin_diag_assign_frame_identifier(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;
#endif

                case SERVICE_ECU_RESET:
                    lin_diag_ecu_reset(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_LED_GET_CONFIG:
                    lin_diag_led_config_get(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_LED_SET_CONFIG:
                    lin_diag_led_config_set(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

#if LIN_PROTOCOL == PROTOCOL_J2602

                case SERVICE_TARGET_RESET:
                    lin_diag_target_reset(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;
#else

                case SERVICE_ASSIGN_NAD_VIA_SNPD:
                    lin_diag_snpd(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;
#endif

                case SERVICE_IO_CONTROL_BY_IDENTIFY:
                    lin_diag_io_control_by_identifier(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_DATA_DUMP:
                    lin_diag_data_dump_control(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_WRITE_DATA_BY_IDENTIFY:
                    lin_diag_write_by_identifier(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_TESTER_PRESENT:
                    lin_diag_tester_present(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case SERVICE_GET_TRACEABILITY_MSG:
                    lin_diag_get_traceability_msg(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

#ifdef CFG_LIN_CONFORM_TEST

                case 0xad:
                    diag_0xad_command(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case 0xae:
                    diag_0xae_command(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;

                case 0xaf:
                    diag_0xaf_command(data, length);
                    lin_diag_services_flag[i] = 0;
                    break;
#endif

                default:
                    break;
            }
        }
    }
}

/********************************************************
** \brief   dfu_do_notify_cp        数据返回
**
** \param   uint8_t                 sid:service_id
** \param   uint8_t                 *data
** \param   uint16_t                length
**
** \retval  None
*********************************************************/
void lin_diag_positive_notify(uint8_t sid, uint8_t *data, uint16_t length)
{
    slave_resp_dat[0] = sid + 0x40;

    for (uint16_t i = 0; i < length; i++)
    {
        slave_resp_dat[1 + i] = data[i];
    }

    ld_send_message((l_u16)(1 + length), (l_u8 *)slave_resp_dat);
}

/********************************************************
** \brief   lin_diag_notify_response    response返回
**
** \param   uint8_t                     sid:service_id
** \param   uint8_t                     resp_value：返回值
**
** \retval  None
*********************************************************/
void lin_diag_negative_notify(uint8_t sid, uint8_t resp_value)
{
    slave_resp_dat[0] = RES_NEGATIVE;
    slave_resp_dat[1] = sid;
    slave_resp_dat[2] = resp_value;

    ld_send_message(3, (l_u8 *)slave_resp_dat);
}
