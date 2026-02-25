/**
*****************************************************************************
* @brief  demo example source file.
* @file   lin_frame.c
* @author AE/FAE team
* @date   28/JUL/2023
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <b>&copy; Copyright (c) 2023 Tinychip Microelectronics Co.,Ltd.</b>
*
*****************************************************************************
*/
#include "lin_frame.h"
#include "lin_cfg.h"
#include "lin.h"
#include "app.h"
#include "custom_diagnosticIII.h"
#include "tc_log.h"

static const char *TAG = "LIN FRAME";

DoorSt_T door_st = {0};       // 门把手状态反馈信号，初始化为0
DoorCmd_T door_cmd = {0};     // ECU对门把手控制信号，初始化为0
extern user_cfg_t g_user_info;

/**
* @description: 通过LIN向主机发送信号
 * @return [void]
 */
void App_LinSendDoorState(void)
{
    if (l_flg_tst_LI0_EHIS_FL_State_flag())
    {
        l_flg_clr_LI0_EHIS_FL_State_flag();
        l_bool_wr_LI0_EHIS_FL_FltSt(door_st.FltSt);
        l_u8_wr_LI0_EHIS_FL_SwtSt(door_st.SwtSt);
        l_u8_wr_LI0_EHIS_FL_SW_MinorVersA(door_st.SW_MinorVersA);
        l_u8_wr_LI0_EHIS_FL_SW_MajorVersA(door_st.SW_MajorVersA);
        l_u8_wr_LI0_EHIS_FL_HW_PhaVers(door_st.HW_PhaVers);
        l_u8_wr_LI0_EHIS_FL_HW_MajorVersB(door_st.HW_MajorVersB);
        l_u8_wr_LI0_EHIS_FL_HW_MinorVersB(door_st.HW_MinorVersB);
        l_u8_wr_LI0_EHIS_FL_SN_MajorVersB(door_st.SN_MajorVersB);
        l_u8_wr_LI0_EHIS_FL_SN_MinorVersB(door_st.SN_MinorVersB);
        l_u8_wr_LI0_EHIS_FL_SN_SupplierCod(door_st.SN_SupplierCod);
        if (LEFT_FRONT_DOOR != g_user_info.config_word)
        {
            g_user_info.config_word = LEFT_FRONT_DOOR; // 左前门把手
            uds_diagnostic_configword_remap_nad();
        }
    }
    if (l_flg_tst_LI0_EHIS_RL_State_flag())
    {
        l_flg_clr_LI0_EHIS_RL_State_flag();
        l_bool_wr_LI0_EHIS_RL_FltSt(door_st.FltSt);
        l_u8_wr_LI0_EHIS_RL_SwtSt(door_st.SwtSt);
        l_u8_wr_LI0_EHIS_RL_SW_MinorVersA(door_st.SW_MinorVersA);
        l_u8_wr_LI0_EHIS_RL_SW_MajorVersA(door_st.SW_MajorVersA);
        l_u8_wr_LI0_EHIS_RL_HW_PhaVers(door_st.HW_PhaVers);
        l_u8_wr_LI0_EHIS_RL_HW_MajorVersB(door_st.HW_MajorVersB);
        l_u8_wr_LI0_EHIS_RL_HW_MinorVersB(door_st.HW_MinorVersB);
        l_u8_wr_LI0_EHIS_RL_SN_MajorVersB(door_st.SN_MajorVersB);
        l_u8_wr_LI0_EHIS_RL_SN_MinorVersB(door_st.SN_MinorVersB);
        l_u8_wr_LI0_EHIS_RL_SN_SupplierCod(door_st.SN_SupplierCod);
        if (LEFT_REAR_DOOR != g_user_info.config_word)
        {
            g_user_info.config_word = LEFT_REAR_DOOR; // 左后门把手
            uds_diagnostic_configword_remap_nad();
        }
    }
    if (l_flg_tst_LI0_EHIS_FR_State_flag())
    {
        l_flg_clr_LI0_EHIS_FR_State_flag();
        l_bool_wr_LI0_EHIS_FR_FRtSt(door_st.FltSt);
        l_u8_wr_LI0_EHIS_FR_SwtSt(door_st.SwtSt);
        l_u8_wr_LI0_EHIS_FR_SW_MinorVersA(door_st.SW_MinorVersA);
        l_u8_wr_LI0_EHIS_FR_SW_MajorVersA(door_st.SW_MajorVersA);
        l_u8_wr_LI0_EHIS_FR_HW_PhaVers(door_st.HW_PhaVers);
        l_u8_wr_LI0_EHIS_FR_HW_MajorVersB(door_st.HW_MajorVersB);
        l_u8_wr_LI0_EHIS_FR_HW_MinorVersB(door_st.HW_MinorVersB);
        l_u8_wr_LI0_EHIS_FR_SN_MajorVersB(door_st.SN_MajorVersB);
        l_u8_wr_LI0_EHIS_FR_SN_MinorVersB(door_st.SN_MinorVersB);
        l_u8_wr_LI0_EHIS_FR_SN_SupplierCod(door_st.SN_SupplierCod);
        if (RIGHT_FRONT_DOOR != g_user_info.config_word)
        {
            g_user_info.config_word = RIGHT_FRONT_DOOR; // 右前门把手
            uds_diagnostic_configword_remap_nad();
        }
    }
    if (l_flg_tst_LI0_EHIS_RR_State_flag())
    {
        l_flg_clr_LI0_EHIS_RR_State_flag();
        l_bool_wr_LI0_EHIS_RR_FltSt(door_st.FltSt);
        l_u8_wr_LI0_EHIS_RR_SwtSt(door_st.SwtSt);
        l_u8_wr_LI0_EHIS_RR_SW_MinorVersA(door_st.SW_MinorVersA);
        l_u8_wr_LI0_EHIS_RR_SW_MajorVersA(door_st.SW_MajorVersA);
        l_u8_wr_LI0_EHIS_RR_HW_PhaVers(door_st.HW_PhaVers);
        l_u8_wr_LI0_EHIS_RR_HW_MajorVersB(door_st.HW_MajorVersB);
        l_u8_wr_LI0_EHIS_RR_HW_MinorVersB(door_st.HW_MinorVersB);
        l_u8_wr_LI0_EHIS_RR_SN_MajorVersB(door_st.SN_MajorVersB);
        l_u8_wr_LI0_EHIS_RR_SN_MinorVersB(door_st.SN_MinorVersB);
        l_u8_wr_LI0_EHIS_RR_SN_SupplierCod(door_st.SN_SupplierCod);
        if (RIGHT_REAR_DOOR != g_user_info.config_word)
        {
            g_user_info.config_word = RIGHT_REAR_DOOR; // 右后门把手
            uds_diagnostic_configword_remap_nad();
        }
    }
}

void App_LinReceiveDoorState(void)
{
    uint16_t data[5] = {0};

    if (l_flg_tst_LI0_VIU_DWS_flag())
    {
        l_flg_clr_LI0_VIU_DWS_flag();

        if (LEFT_FRONT_DOOR == g_user_info.config_word) // left front door
        {
            door_cmd.UsageMode = l_u8_rd_LI0_bit2_5();
            door_cmd.VehicleSpeedValid = l_bool_rd_LI0_bit6();

            data[0] = l_u8_rd_LI0_bit8_9();
            data[1] = l_bool_rd_LI0_bit10();
            data[2] = l_bool_rd_LI0_bit11();
            data[3] = l_bool_rd_LI0_bit12();
            data[4] = l_u8_rd_LI0_bit13_20();

            door_cmd.VehicleSpeed = ((data[0] & 0x3) |
                                    ((data[1] & 0x1) << 2) |
                                    ((data[2] & 0x1) << 3) |
                                    ((data[3] & 0x1) << 4) |
                                    ((data[4] & 0xFF) << 5));
        }
        else if (LEFT_REAR_DOOR == g_user_info.config_word) // left rear door
        {
            data[0] = l_bool_rd_LI0_bit6();
            data[1] = l_bool_rd_LI0_bit7();
            data[2] = l_u8_rd_LI0_bit8_9();

            door_cmd.UsageMode = ((data[0] & 0x1) |
                                 ((data[1] & 0x1) << 1) |
                                 ((data[2] & 0x3) << 2));
            door_cmd.VehicleSpeedValid = l_bool_rd_LI0_bit10();
            data[0] = l_bool_rd_LI0_bit11();
            data[1] = l_bool_rd_LI0_bit12();
            data[2] = l_u8_rd_LI0_bit13_20();
            data[3] = l_u8_rd_LI0_bit21_23();
            door_cmd.VehicleSpeed = ((data[0] & 0x1) |
                                    ((data[1] & 0x1) << 1) |
                                    ((data[2] & 0x1) << 2) |
                                    ((data[3] & 0x7) << 10));
        }
        else if ((RIGHT_FRONT_DOOR == g_user_info.config_word) || (RIGHT_REAR_DOOR == g_user_info.config_word)) // right front or rear door
        {
            data[0] = l_u8_rd_LI0_bit8_9();
            data[1] = l_bool_rd_LI0_bit10();
            data[2] = l_bool_rd_LI0_bit11();
            door_cmd.UsageMode = ((data[0] & 0x3) |
                                 ((data[1] & 0x1) << 2) |
                                 ((data[2] & 0x1) << 3));
            door_cmd.VehicleSpeedValid = l_bool_rd_LI0_bit12();
            data[0] = l_u8_rd_LI0_bit13_20();
            data[1] = l_u8_rd_LI0_bit21_23();
            data[2] = l_u8_rd_LI0_bit24_25();
            door_cmd.VehicleSpeed = ((data[0] & 0xFF) |
                                    ((data[1] & 0x7) << 8) |
                                    ((data[2] & 0x2) << 11));
        }
    }
}

/**
 * @description: 获取主机发送的信号，并向主机发送信号
 * @return [void]
 */
void App_LinControlMsg(void)
{
    App_LinSendDoorState();

    App_LinReceiveDoorState();
}
