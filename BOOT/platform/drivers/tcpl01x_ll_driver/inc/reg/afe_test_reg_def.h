/**
 *****************************************************************************
 * @brief   afe_test_reg_def header file.
 *
 * @file    afe_test_reg_def.h
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

#ifndef   AFE_TEST_DEF_H__
#define   AFE_TEST_DEF_H__

// Register Offset Macro Definition
#define AFE_TEST_TEST_MODE_CTRL_OFFSET                          0x0000
#define AFE_TEST_TEST_RSTN_CTRL_OFFSET                          0x0004
#define AFE_TEST_TEST_IO_CTRL_OFFSET                            0x0008
#define AFE_TEST_TEST_HRC48M_TRIM_OFFSET                        0x000C
#define AFE_TEST_TEST_LRC32K_TRIM_OFFSET                        0x0010
#define AFE_TEST_TEST_LED_TRIM_OFFSET                           0x0014
#define AFE_TEST_TEST_ANA_CTRL_OFFSET                           0x0018
#define AFE_TEST_TEST_TPREF_TRIM_OFFSET                         0x001C
#define AFE_TEST_TEST_LDO35V_TRIM_OFFSET                        0x0020
#define AFE_TEST_TEST_OTP_TRIM_OFFSET                           0x0024
#define AFE_TEST_TEST_LIN_TRIM_OFFSET                           0x0028
#define AFE_TEST_TEST_LIN_CTRL_OFFSET                           0x002C
#define AFE_TEST_TEST_LIN_STATUS_OFFSET                         0x0030
#define AFE_TEST_TEST_ADC_CTRL_OFFSET                           0x0034
#define AFE_TEST_TEST_BUS_CTRL_OFFSET                           0x0038
#define AFE_TEST_TEST_LDO15_TRIM_OFFSET                         0x003C
#define AFE_TEST_TEST_RSTN_IO_CTRL_OFFSET                       0x0040
#define AFE_TEST_TEST_LDO15_CTRL_OFFSET                         0x0044
#define AFE_TEST_TEST_LOCK_OFFSET                               0x00FC

// Register Address Macro Definition
#define AFE_TEST_TEST_MODE_CTRL_ADDR                            ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_MODE_CTRL_OFFSET)
#define AFE_TEST_TEST_RSTN_CTRL_ADDR                            ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_RSTN_CTRL_OFFSET)
#define AFE_TEST_TEST_IO_CTRL_ADDR                              ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_IO_CTRL_OFFSET)
#define AFE_TEST_TEST_HRC48M_TRIM_ADDR                          ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_HRC48M_TRIM_OFFSET)
#define AFE_TEST_TEST_LRC32K_TRIM_ADDR                          ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LRC32K_TRIM_OFFSET)
#define AFE_TEST_TEST_LED_TRIM_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LED_TRIM_OFFSET)
#define AFE_TEST_TEST_ANA_CTRL_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_ANA_CTRL_OFFSET)
#define AFE_TEST_TEST_TPREF_TRIM_ADDR                           ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_TPREF_TRIM_OFFSET)
#define AFE_TEST_TEST_LDO35V_TRIM_ADDR                          ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LDO35V_TRIM_OFFSET)
#define AFE_TEST_TEST_OTP_TRIM_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_OTP_TRIM_OFFSET)
#define AFE_TEST_TEST_LIN_TRIM_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LIN_TRIM_OFFSET)
#define AFE_TEST_TEST_LIN_CTRL_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LIN_CTRL_OFFSET)
#define AFE_TEST_TEST_LIN_STATUS_ADDR                           ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LIN_STATUS_OFFSET)
#define AFE_TEST_TEST_ADC_CTRL_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_ADC_CTRL_OFFSET)
#define AFE_TEST_TEST_BUS_CTRL_ADDR                             ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_BUS_CTRL_OFFSET)
#define AFE_TEST_TEST_LDO15_TRIM_ADDR                           ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LDO15_TRIM_OFFSET)
#define AFE_TEST_TEST_RSTN_IO_CTRL_ADDR                         ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_RSTN_IO_CTRL_OFFSET)
#define AFE_TEST_TEST_LDO15_CTRL_ADDR                           ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LDO15_CTRL_OFFSET)
#define AFE_TEST_TEST_LOCK_ADDR                                 ( AFE_TEST_BASE_ADDR + AFE_TEST_TEST_LOCK_OFFSET)

// Register Field Macro Definition
#define AFE_TEST_TEST_MODE_CTRL_TM_DET_EN_SHIFT                                   0
#define AFE_TEST_TEST_MODE_CTRL_TM_DET_EN_MASK                                    0x00000001
#define AFE_TEST_TEST_MODE_CTRL_TM_DET_EN_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_MODE_CTRL_TM_DET_EN_CLR                                     0xFFFFFFFE

#define AFE_TEST_TEST_RSTN_CTRL_TEST_RSTN_EN_SHIFT                                0
#define AFE_TEST_TEST_RSTN_CTRL_TEST_RSTN_EN_MASK                                 0x00000001
#define AFE_TEST_TEST_RSTN_CTRL_TEST_RSTN_EN_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_RSTN_CTRL_TEST_RSTN_EN_CLR                                  0xFFFFFFFE

#define AFE_TEST_TEST_IO_CTRL_TEST_IO_LPBK_EN_SHIFT                               1
#define AFE_TEST_TEST_IO_CTRL_TEST_IO_LPBK_EN_MASK                                0x00000002
#define AFE_TEST_TEST_IO_CTRL_TEST_IO_LPBK_EN_SET(n)                              (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_TEST_TEST_IO_CTRL_TEST_IO_LPBK_EN_CLR                                 0xFFFFFFFD

#define AFE_TEST_TEST_IO_CTRL_IO3_TEST_FLAG_EN_SHIFT                              0
#define AFE_TEST_TEST_IO_CTRL_IO3_TEST_FLAG_EN_MASK                               0x00000001
#define AFE_TEST_TEST_IO_CTRL_IO3_TEST_FLAG_EN_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_IO_CTRL_IO3_TEST_FLAG_EN_CLR                                0xFFFFFFFE

#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_LDO_TRIM_SHIFT                           16
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_LDO_TRIM_MASK                            0x00030000
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_LDO_TRIM_SET(n)                          (((uint32_t)(n) << 16 ) & 0x00030000)
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_LDO_TRIM_CLR                             0xFFFCFFFF

#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_RES_TRIM_SHIFT                           12
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_RES_TRIM_MASK                            0x00007000
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_RES_TRIM_SET(n)                          (((uint32_t)(n) << 12 ) & 0x00007000)
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_RES_TRIM_CLR                             0xFFFF8FFF

#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_MAX_TRIM_SHIFT                           8
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_MAX_TRIM_MASK                            0x00000300
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_MAX_TRIM_SET(n)                          (((uint32_t)(n) << 8  ) & 0x00000300)
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_MAX_TRIM_CLR                             0xFFFFFCFF

#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_CAP_TRIM_SHIFT                           0
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_CAP_TRIM_MASK                            0x000000FF
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_CAP_TRIM_SET(n)                          (((uint32_t)(n) << 0  ) & 0x000000FF)
#define AFE_TEST_TEST_HRC48M_TRIM_HRC48M_CAP_TRIM_CLR                             0xFFFFFF00

#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_RES_TRIM_SHIFT                           4
#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_RES_TRIM_MASK                            0x000000F0
#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_RES_TRIM_SET(n)                          (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_RES_TRIM_CLR                             0xFFFFFF0F

#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_CAP_TRIM_SHIFT                           0
#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_CAP_TRIM_MASK                            0x00000003
#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_CAP_TRIM_SET(n)                          (((uint32_t)(n) << 0  ) & 0x00000003)
#define AFE_TEST_TEST_LRC32K_TRIM_LRC32K_CAP_TRIM_CLR                             0xFFFFFFFC

#define AFE_TEST_TEST_LED_TRIM_LED_LC2_IOUT_TRIM_SHIFT                            24
#define AFE_TEST_TEST_LED_TRIM_LED_LC2_IOUT_TRIM_MASK                             0xFF000000
#define AFE_TEST_TEST_LED_TRIM_LED_LC2_IOUT_TRIM_SET(n)                           (((uint32_t)(n) << 24 ) & 0xFF000000)
#define AFE_TEST_TEST_LED_TRIM_LED_LC2_IOUT_TRIM_CLR                              0x00FFFFFF

#define AFE_TEST_TEST_LED_TRIM_LED_LC1_IOUT_TRIM_SHIFT                            16
#define AFE_TEST_TEST_LED_TRIM_LED_LC1_IOUT_TRIM_MASK                             0x00FF0000
#define AFE_TEST_TEST_LED_TRIM_LED_LC1_IOUT_TRIM_SET(n)                           (((uint32_t)(n) << 16 ) & 0x00FF0000)
#define AFE_TEST_TEST_LED_TRIM_LED_LC1_IOUT_TRIM_CLR                              0xFF00FFFF

#define AFE_TEST_TEST_LED_TRIM_LED_LC0_IOUT_TRIM_SHIFT                            8
#define AFE_TEST_TEST_LED_TRIM_LED_LC0_IOUT_TRIM_MASK                             0x0000FF00
#define AFE_TEST_TEST_LED_TRIM_LED_LC0_IOUT_TRIM_SET(n)                           (((uint32_t)(n) << 8  ) & 0x0000FF00)
#define AFE_TEST_TEST_LED_TRIM_LED_LC0_IOUT_TRIM_CLR                              0xFFFF00FF

#define AFE_TEST_TEST_LED_TRIM_ACTIVE_IBIAS_TRIM_SHIFT                            0
#define AFE_TEST_TEST_LED_TRIM_ACTIVE_IBIAS_TRIM_MASK                             0x0000003F
#define AFE_TEST_TEST_LED_TRIM_ACTIVE_IBIAS_TRIM_SET(n)                           (((uint32_t)(n) << 0  ) & 0x0000003F)
#define AFE_TEST_TEST_LED_TRIM_ACTIVE_IBIAS_TRIM_CLR                              0xFFFFFFC0

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_SEL_BUF_SHIFT                              12
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_SEL_BUF_MASK                               0x00001000
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_SEL_BUF_SET(n)                             (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_SEL_BUF_CLR                                0xFFFFEFFF

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_SEL_SHIFT                              8
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_SEL_MASK                               0x00000F00
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_SEL_SET(n)                             (((uint32_t)(n) << 8  ) & 0x00000F00)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_SEL_CLR                                0xFFFFF0FF

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_SEL_SHIFT                              4
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_SEL_MASK                               0x000000F0
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_SEL_SET(n)                             (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_SEL_CLR                                0xFFFFFF0F

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TO_ADC_EN_SHIFT                            3
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TO_ADC_EN_MASK                             0x00000008
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TO_ADC_EN_SET(n)                           (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TO_ADC_EN_CLR                              0xFFFFFFF7

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_EN_SHIFT                               2
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_EN_MASK                                0x00000004
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_EN_SET(n)                              (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAO_EN_CLR                                 0xFFFFFFFB

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_EN_SHIFT                               1
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_EN_MASK                                0x00000002
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_EN_SET(n)                              (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_TAI_EN_CLR                                 0xFFFFFFFD

#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_BUF_EN_SHIFT                               0
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_BUF_EN_MASK                                0x00000001
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_BUF_EN_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_ANA_CTRL_TESTMUX_BUF_EN_CLR                                 0xFFFFFFFE

#define AFE_TEST_TEST_TPREF_TRIM_TPREF_TRIM_SHIFT                                 0
#define AFE_TEST_TEST_TPREF_TRIM_TPREF_TRIM_MASK                                  0x0000007F
#define AFE_TEST_TEST_TPREF_TRIM_TPREF_TRIM_SET(n)                                (((uint32_t)(n) << 0  ) & 0x0000007F)
#define AFE_TEST_TEST_TPREF_TRIM_TPREF_TRIM_CLR                                   0xFFFFFF80

#define AFE_TEST_TEST_LDO35V_TRIM_LDO35V_TRIM_SHIFT                               0
#define AFE_TEST_TEST_LDO35V_TRIM_LDO35V_TRIM_MASK                                0x0000000F
#define AFE_TEST_TEST_LDO35V_TRIM_LDO35V_TRIM_SET(n)                              (((uint32_t)(n) << 0  ) & 0x0000000F)
#define AFE_TEST_TEST_LDO35V_TRIM_LDO35V_TRIM_CLR                                 0xFFFFFFF0

#define AFE_TEST_TEST_OTP_TRIM_OTP_TRIM_SHIFT                                     0
#define AFE_TEST_TEST_OTP_TRIM_OTP_TRIM_MASK                                      0x0000001F
#define AFE_TEST_TEST_OTP_TRIM_OTP_TRIM_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x0000001F)
#define AFE_TEST_TEST_OTP_TRIM_OTP_TRIM_CLR                                       0xFFFFFFE0

#define AFE_TEST_TEST_LIN_TRIM_LIN_TRIM_BUSLIM_SHIFT                              4
#define AFE_TEST_TEST_LIN_TRIM_LIN_TRIM_BUSLIM_MASK                               0x000000F0
#define AFE_TEST_TEST_LIN_TRIM_LIN_TRIM_BUSLIM_SET(n)                             (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_TEST_TEST_LIN_TRIM_LIN_TRIM_BUSLIM_CLR                                0xFFFFFF0F

#define AFE_TEST_TEST_LIN_TRIM_LIN_ITRIM_SHIFT                                    0
#define AFE_TEST_TEST_LIN_TRIM_LIN_ITRIM_MASK                                     0x0000000F
#define AFE_TEST_TEST_LIN_TRIM_LIN_ITRIM_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x0000000F)
#define AFE_TEST_TEST_LIN_TRIM_LIN_ITRIM_CLR                                      0xFFFFFFF0

#define AFE_TEST_TEST_LIN_CTRL_LIN_TESTSEL_SHIFT                                  28
#define AFE_TEST_TEST_LIN_CTRL_LIN_TESTSEL_MASK                                   0x70000000
#define AFE_TEST_TEST_LIN_CTRL_LIN_TESTSEL_SET(n)                                 (((uint32_t)(n) << 28 ) & 0x70000000)
#define AFE_TEST_TEST_LIN_CTRL_LIN_TESTSEL_CLR                                    0x8FFFFFFF

#define AFE_TEST_TEST_LIN_CTRL_LIN_PDSSOK_EN_SHIFT                                24
#define AFE_TEST_TEST_LIN_CTRL_LIN_PDSSOK_EN_MASK                                 0x01000000
#define AFE_TEST_TEST_LIN_CTRL_LIN_PDSSOK_EN_SET(n)                               (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_TEST_TEST_LIN_CTRL_LIN_PDSSOK_EN_CLR                                  0xFEFFFFFF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_CUR_SHIFT                               20
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_CUR_MASK                                0x00700000
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_CUR_SET(n)                              (((uint32_t)(n) << 20 ) & 0x00700000)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_CUR_CLR                                 0xFF8FFFFF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_CUR_SHIFT                               16
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_CUR_MASK                                0x00070000
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_CUR_SET(n)                              (((uint32_t)(n) << 16 ) & 0x00070000)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_CUR_CLR                                 0xFFF8FFFF

#define AFE_TEST_TEST_LIN_CTRL_LIN_RX_DELAY_SHIFT                                 12
#define AFE_TEST_TEST_LIN_CTRL_LIN_RX_DELAY_MASK                                  0x00007000
#define AFE_TEST_TEST_LIN_CTRL_LIN_RX_DELAY_SET(n)                                (((uint32_t)(n) << 12 ) & 0x00007000)
#define AFE_TEST_TEST_LIN_CTRL_LIN_RX_DELAY_CLR                                   0xFFFF8FFF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_LEVEL_SHIFT                                8
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_LEVEL_MASK                                 0x00000F00
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_LEVEL_SET(n)                               (((uint32_t)(n) << 8  ) & 0x00000F00)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_LEVEL_CLR                                  0xFFFFF0FF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_FBNEG_EN_SHIFT                             6
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_FBNEG_EN_MASK                              0x00000040
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_FBNEG_EN_SET(n)                            (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_FBNEG_EN_CLR                               0xFFFFFFBF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PU_EN_SHIFT                       5
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PU_EN_MASK                        0x00000020
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PU_EN_SET(n)                      (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PU_EN_CLR                         0xFFFFFFDF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PD_EN_SHIFT                       4
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PD_EN_MASK                        0x00000010
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PD_EN_SET(n)                      (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_SLOPEDIS_PD_EN_CLR                         0xFFFFFFEF

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_EN_SHIFT                                3
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_EN_MASK                                 0x00000008
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_EN_SET(n)                               (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PU_EN_CLR                                  0xFFFFFFF7

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_EN_SHIFT                                2
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_EN_MASK                                 0x00000004
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_EN_SET(n)                               (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_PD_EN_CLR                                  0xFFFFFFFB

#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_EN_SHIFT                                   1
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_EN_MASK                                    0x00000002
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_EN_SET(n)                                  (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_TEST_TEST_LIN_CTRL_LIN_EMC_EN_CLR                                     0xFFFFFFFD

#define AFE_TEST_TEST_LIN_CTRL_LIN_TM_RX_SHIFT                                    0
#define AFE_TEST_TEST_LIN_CTRL_LIN_TM_RX_MASK                                     0x00000001
#define AFE_TEST_TEST_LIN_CTRL_LIN_TM_RX_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_LIN_CTRL_LIN_TM_RX_CLR                                      0xFFFFFFFE

#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPE_OK_SHIFT                               2
#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPE_OK_MASK                                0x00000004
#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPE_OK_SET(n)                              (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPE_OK_CLR                                 0xFFFFFFFB

#define AFE_TEST_TEST_LIN_STATUS_LIN_COMPOUT_SHIFT                                1
#define AFE_TEST_TEST_LIN_STATUS_LIN_COMPOUT_MASK                                 0x00000002
#define AFE_TEST_TEST_LIN_STATUS_LIN_COMPOUT_SET(n)                               (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_TEST_TEST_LIN_STATUS_LIN_COMPOUT_CLR                                  0xFFFFFFFD

#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPEDIS_SHIFT                               0
#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPEDIS_MASK                                0x00000001
#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPEDIS_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_LIN_STATUS_LIN_SLOPEDIS_CLR                                 0xFFFFFFFE

#define AFE_TEST_TEST_ADC_CTRL_ADC_TEST_SEL_SHIFT                                 4
#define AFE_TEST_TEST_ADC_CTRL_ADC_TEST_SEL_MASK                                  0x00000070
#define AFE_TEST_TEST_ADC_CTRL_ADC_TEST_SEL_SET(n)                                (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_TEST_TEST_ADC_CTRL_ADC_TEST_SEL_CLR                                   0xFFFFFF8F

#define AFE_TEST_TEST_ADC_CTRL_ADC_TESTBS_EN_SHIFT                                0
#define AFE_TEST_TEST_ADC_CTRL_ADC_TESTBS_EN_MASK                                 0x00000001
#define AFE_TEST_TEST_ADC_CTRL_ADC_TESTBS_EN_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_ADC_CTRL_ADC_TESTBS_EN_CLR                                  0xFFFFFFFE

#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_SEL_SHIFT                                   29
#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_SEL_MASK                                    0x60000000
#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_SEL_SET(n)                                  (((uint32_t)(n) << 29 ) & 0x60000000)
#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_SEL_CLR                                     0x9FFFFFFF

#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_EN_SHIFT                                    28
#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_EN_MASK                                     0x10000000
#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_EN_SET(n)                                   (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_TEST_TEST_BUS_CTRL_ADC_TP_EN_CLR                                      0xEFFFFFFF

#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_SEL_SHIFT                                   25
#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_SEL_MASK                                    0x06000000
#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_SEL_SET(n)                                  (((uint32_t)(n) << 25 ) & 0x06000000)
#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_SEL_CLR                                     0xF9FFFFFF

#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_EN_SHIFT                                    24
#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_EN_MASK                                     0x01000000
#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_EN_SET(n)                                   (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_TEST_TEST_BUS_CTRL_RTC_TP_EN_CLR                                      0xFEFFFFFF

#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_SEL_SHIFT                                   21
#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_SEL_MASK                                    0x00600000
#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_SEL_SET(n)                                  (((uint32_t)(n) << 21 ) & 0x00600000)
#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_SEL_CLR                                     0xFF9FFFFF

#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_EN_SHIFT                                    20
#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_EN_MASK                                     0x00100000
#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_EN_SET(n)                                   (((uint32_t)(n) << 20 ) & 0x00100000)
#define AFE_TEST_TEST_BUS_CTRL_LIN_TP_EN_CLR                                      0xFFEFFFFF

#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_SEL_SHIFT                                   17
#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_SEL_MASK                                    0x00060000
#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_SEL_SET(n)                                  (((uint32_t)(n) << 17 ) & 0x00060000)
#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_SEL_CLR                                     0xFFF9FFFF

#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_EN_SHIFT                                    16
#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_EN_MASK                                     0x00010000
#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_EN_SET(n)                                   (((uint32_t)(n) << 16 ) & 0x00010000)
#define AFE_TEST_TEST_BUS_CTRL_PWM_TP_EN_CLR                                      0xFFFEFFFF

#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_SEL_SHIFT                                   13
#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_SEL_MASK                                    0x00006000
#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_SEL_SET(n)                                  (((uint32_t)(n) << 13 ) & 0x00006000)
#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_SEL_CLR                                     0xFFFF9FFF

#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_EN_SHIFT                                    12
#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_EN_MASK                                     0x00001000
#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_EN_SET(n)                                   (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_TEST_TEST_BUS_CTRL_PMU_TP_EN_CLR                                      0xFFFFEFFF

#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_SEL_SHIFT                                   9
#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_SEL_MASK                                    0x00000600
#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_SEL_SET(n)                                  (((uint32_t)(n) << 9  ) & 0x00000600)
#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_SEL_CLR                                     0xFFFFF9FF

#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_EN_SHIFT                                    8
#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_EN_MASK                                     0x00000100
#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_EN_SET(n)                                   (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_TEST_TEST_BUS_CTRL_CRG_TP_EN_CLR                                      0xFFFFFEFF

#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_OUT_SEL_SHIFT                               6
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_OUT_SEL_MASK                                0x000000C0
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_OUT_SEL_SET(n)                              (((uint32_t)(n) << 6  ) & 0x000000C0)
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_OUT_SEL_CLR                                 0xFFFFFF3F

#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HNIBBLE_SEL_SHIFT                           5
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HNIBBLE_SEL_MASK                            0x00000020
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HNIBBLE_SEL_SET(n)                          (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HNIBBLE_SEL_CLR                             0xFFFFFFDF

#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HBYTE_SEL_SHIFT                             4
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HBYTE_SEL_MASK                              0x00000010
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HBYTE_SEL_SET(n)                            (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_HBYTE_SEL_CLR                               0xFFFFFFEF

#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_SHIFT                                1
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_MASK                                 0x0000000E
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_SET(n)                               (((uint32_t)(n) << 1  ) & 0x0000000E)
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_CLR                                  0xFFFFFFF1

#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_EN_SHIFT                                    0
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_EN_MASK                                     0x00000001
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_EN_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_BUS_CTRL_TOP_TP_EN_CLR                                      0xFFFFFFFE

#define AFE_TEST_TEST_LDO15_TRIM_LDO15_TRIM_SHIFT                                 0
#define AFE_TEST_TEST_LDO15_TRIM_LDO15_TRIM_MASK                                  0x00000001
#define AFE_TEST_TEST_LDO15_TRIM_LDO15_TRIM_SET(n)                                (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_LDO15_TRIM_LDO15_TRIM_CLR                                   0xFFFFFFFE

#define AFE_TEST_TEST_RSTN_IO_CTRL_TEST_RSTN_IO_EN_SHIFT                          0
#define AFE_TEST_TEST_RSTN_IO_CTRL_TEST_RSTN_IO_EN_MASK                           0x00000001
#define AFE_TEST_TEST_RSTN_IO_CTRL_TEST_RSTN_IO_EN_SET(n)                         (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_RSTN_IO_CTRL_TEST_RSTN_IO_EN_CLR                            0xFFFFFFFE

#define AFE_TEST_TEST_LDO15_CTRL_LDO15_SCAN_BYPASS_SHIFT                          0
#define AFE_TEST_TEST_LDO15_CTRL_LDO15_SCAN_BYPASS_MASK                           0x00000001
#define AFE_TEST_TEST_LDO15_CTRL_LDO15_SCAN_BYPASS_SET(n)                         (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_LDO15_CTRL_LDO15_SCAN_BYPASS_CLR                            0xFFFFFFFE

#define AFE_TEST_TEST_LOCK_TEST_LOCK_SHIFT                                        0
#define AFE_TEST_TEST_LOCK_TEST_LOCK_MASK                                         0x00000001
#define AFE_TEST_TEST_LOCK_TEST_LOCK_SET(n)                                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_TEST_TEST_LOCK_TEST_LOCK_CLR                                          0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t TM_DET_EN              : 1  ; // 0  : 0
    __IO uint32_t RESERVED0              : 31 ; // 31 : 1
} AFE_TEST_TEST_MODE_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TEST_RSTN_EN           : 1  ; // 0  : 0
    __IO uint32_t RESERVED0              : 31 ; // 31 : 1
} AFE_TEST_TEST_RSTN_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t IO3_TEST_FLAG_EN       : 1  ; // 0  : 0
    __IO uint32_t TEST_IO_LPBK_EN        : 1  ; // 1  : 1
    __IO uint32_t RESERVED0              : 30 ; // 31 : 2
} AFE_TEST_TEST_IO_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t HRC48M_CAP_TRIM        : 8  ; // 7  : 0
    __IO uint32_t HRC48M_MAX_TRIM        : 2  ; // 9  : 8
    __IO uint32_t RESERVED2              : 2  ; // 11 : 10
    __IO uint32_t HRC48M_RES_TRIM        : 3  ; // 14 : 12
    __IO uint32_t RESERVED1              : 1  ; // 15 : 15
    __IO uint32_t HRC48M_LDO_TRIM        : 2  ; // 17 : 16
    __IO uint32_t RESERVED0              : 14 ; // 31 : 18
} AFE_TEST_TEST_HRC48M_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t LRC32K_CAP_TRIM        : 2  ; // 1  : 0
    __IO uint32_t RESERVED1              : 2  ; // 3  : 2
    __IO uint32_t LRC32K_RES_TRIM        : 4  ; // 7  : 4
    __IO uint32_t RESERVED0              : 24 ; // 31 : 8
} AFE_TEST_TEST_LRC32K_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t ACTIVE_IBIAS_TRIM      : 6  ; // 5  : 0
    __IO uint32_t RESERVED0              : 2  ; // 7  : 6
    __IO uint32_t LED_LC0_IOUT_TRIM      : 8  ; // 15 : 8
    __IO uint32_t LED_LC1_IOUT_TRIM      : 8  ; // 23 : 16
    __IO uint32_t LED_LC2_IOUT_TRIM      : 8  ; // 31 : 24
} AFE_TEST_TEST_LED_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t TESTMUX_BUF_EN         : 1  ; // 0  : 0
    __IO uint32_t TESTMUX_TAI_EN         : 1  ; // 1  : 1
    __IO uint32_t TESTMUX_TAO_EN         : 1  ; // 2  : 2
    __IO uint32_t TESTMUX_TO_ADC_EN      : 1  ; // 3  : 3
    __IO uint32_t TESTMUX_TAI_SEL        : 4  ; // 7  : 4
    __IO uint32_t TESTMUX_TAO_SEL        : 4  ; // 11 : 8
    __IO uint32_t TESTMUX_SEL_BUF        : 1  ; // 12 : 12
    __IO uint32_t RESERVED0              : 19 ; // 31 : 13
} AFE_TEST_TEST_ANA_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TPREF_TRIM             : 7  ; // 6  : 0
    __IO uint32_t RESERVED0              : 25 ; // 31 : 7
} AFE_TEST_TEST_TPREF_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t LDO35V_TRIM            : 4  ; // 3  : 0
    __IO uint32_t RESERVED0              : 28 ; // 31 : 4
} AFE_TEST_TEST_LDO35V_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t OTP_TRIM               : 5  ; // 4  : 0
    __IO uint32_t RESERVED0              : 27 ; // 31 : 5
} AFE_TEST_TEST_OTP_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t LIN_ITRIM              : 4  ; // 3  : 0
    __IO uint32_t LIN_TRIM_BUSLIM        : 4  ; // 7  : 4
    __IO uint32_t RESERVED0              : 24 ; // 31 : 8
} AFE_TEST_TEST_LIN_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t LIN_TM_RX              : 1  ; // 0  : 0
    __IO uint32_t LIN_EMC_EN             : 1  ; // 1  : 1
    __IO uint32_t LIN_EMC_PD_EN          : 1  ; // 2  : 2
    __IO uint32_t LIN_EMC_PU_EN          : 1  ; // 3  : 3
    __IO uint32_t LIN_EMC_SLOPEDIS_PD_EN : 1  ; // 4  : 4
    __IO uint32_t LIN_EMC_SLOPEDIS_PU_EN : 1  ; // 5  : 5
    __IO uint32_t LIN_EMC_FBNEG_EN       : 1  ; // 6  : 6
    __IO uint32_t RESERVED5              : 1  ; // 7  : 7
    __IO uint32_t LIN_EMC_LEVEL          : 4  ; // 11 : 8
    __IO uint32_t LIN_RX_DELAY           : 3  ; // 14 : 12
    __IO uint32_t RESERVED4              : 1  ; // 15 : 15
    __IO uint32_t LIN_EMC_PD_CUR         : 3  ; // 18 : 16
    __IO uint32_t RESERVED3              : 1  ; // 19 : 19
    __IO uint32_t LIN_EMC_PU_CUR         : 3  ; // 22 : 20
    __IO uint32_t RESERVED2              : 1  ; // 23 : 23
    __IO uint32_t LIN_PDSSOK_EN          : 1  ; // 24 : 24
    __IO uint32_t RESERVED1              : 3  ; // 27 : 25
    __IO uint32_t LIN_TESTSEL            : 3  ; // 30 : 28
    __IO uint32_t RESERVED0              : 1  ; // 31 : 31
} AFE_TEST_TEST_LIN_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LIN_SLOPEDIS           : 1  ; // 0  : 0
    __IO uint32_t LIN_COMPOUT            : 1  ; // 1  : 1
    __IO uint32_t LIN_SLOPE_OK           : 1  ; // 2  : 2
    __IO uint32_t RESERVED0              : 29 ; // 31 : 3
} AFE_TEST_TEST_LIN_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_TESTBS_EN          : 1  ; // 0  : 0
    __IO uint32_t RESERVED1              : 3  ; // 3  : 1
    __IO uint32_t ADC_TEST_SEL           : 3  ; // 6  : 4
    __IO uint32_t RESERVED0              : 25 ; // 31 : 7
} AFE_TEST_TEST_ADC_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TOP_TP_EN              : 1  ; // 0  : 0
    __IO uint32_t TOP_TP_IP_SEL          : 3  ; // 3  : 1
    __IO uint32_t TOP_TP_HBYTE_SEL       : 1  ; // 4  : 4
    __IO uint32_t TOP_TP_HNIBBLE_SEL     : 1  ; // 5  : 5
    __IO uint32_t TOP_TP_OUT_SEL         : 2  ; // 7  : 6
    __IO uint32_t CRG_TP_EN              : 1  ; // 8  : 8
    __IO uint32_t CRG_TP_SEL             : 2  ; // 10 : 9
    __IO uint32_t RESERVED5              : 1  ; // 11 : 11
    __IO uint32_t PMU_TP_EN              : 1  ; // 12 : 12
    __IO uint32_t PMU_TP_SEL             : 2  ; // 14 : 13
    __IO uint32_t RESERVED4              : 1  ; // 15 : 15
    __IO uint32_t PWM_TP_EN              : 1  ; // 16 : 16
    __IO uint32_t PWM_TP_SEL             : 2  ; // 18 : 17
    __IO uint32_t RESERVED3              : 1  ; // 19 : 19
    __IO uint32_t LIN_TP_EN              : 1  ; // 20 : 20
    __IO uint32_t LIN_TP_SEL             : 2  ; // 22 : 21
    __IO uint32_t RESERVED2              : 1  ; // 23 : 23
    __IO uint32_t RTC_TP_EN              : 1  ; // 24 : 24
    __IO uint32_t RTC_TP_SEL             : 2  ; // 26 : 25
    __IO uint32_t RESERVED1              : 1  ; // 27 : 27
    __IO uint32_t ADC_TP_EN              : 1  ; // 28 : 28
    __IO uint32_t ADC_TP_SEL             : 2  ; // 30 : 29
    __IO uint32_t RESERVED0              : 1  ; // 31 : 31
} AFE_TEST_TEST_BUS_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LDO15_TRIM             : 1  ; // 0  : 0
    __IO uint32_t RESERVED0              : 31 ; // 31 : 1
} AFE_TEST_TEST_LDO15_TRIM_FIELD_T;

typedef struct
{
    __IO uint32_t TEST_RSTN_IO_EN        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0              : 31 ; // 31 : 1
} AFE_TEST_TEST_RSTN_IO_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LDO15_SCAN_BYPASS      : 1  ; // 0  : 0
    __IO uint32_t RESERVED0              : 31 ; // 31 : 1
} AFE_TEST_TEST_LDO15_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TEST_LOCK              : 1  ; // 0  : 0
    __IO uint32_t RESERVED0              : 31 ; // 31 : 1
} AFE_TEST_TEST_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t TEST_MODE_CTRL                        ; // 0x0000
        AFE_TEST_TEST_MODE_CTRL_FIELD_T TEST_MODE_CTRL_F     ;
    };

    union
    {
        __IO  uint32_t TEST_RSTN_CTRL                        ; // 0x0004
        AFE_TEST_TEST_RSTN_CTRL_FIELD_T TEST_RSTN_CTRL_F     ;
    };

    union
    {
        __IO  uint32_t TEST_IO_CTRL                          ; // 0x0008
        AFE_TEST_TEST_IO_CTRL_FIELD_T TEST_IO_CTRL_F         ;
    };

    union
    {
        __IO  uint32_t TEST_HRC48M_TRIM                      ; // 0x000C
        AFE_TEST_TEST_HRC48M_TRIM_FIELD_T TEST_HRC48M_TRIM_F ;
    };

    union
    {
        __IO  uint32_t TEST_LRC32K_TRIM                      ; // 0x0010
        AFE_TEST_TEST_LRC32K_TRIM_FIELD_T TEST_LRC32K_TRIM_F ;
    };

    union
    {
        __IO  uint32_t TEST_LED_TRIM                         ; // 0x0014
        AFE_TEST_TEST_LED_TRIM_FIELD_T TEST_LED_TRIM_F       ;
    };

    union
    {
        __IO  uint32_t TEST_ANA_CTRL                         ; // 0x0018
        AFE_TEST_TEST_ANA_CTRL_FIELD_T TEST_ANA_CTRL_F       ;
    };

    union
    {
        __IO  uint32_t TEST_TPREF_TRIM                       ; // 0x001C
        AFE_TEST_TEST_TPREF_TRIM_FIELD_T TEST_TPREF_TRIM_F   ;
    };

    union
    {
        __IO  uint32_t TEST_LDO35V_TRIM                      ; // 0x0020
        AFE_TEST_TEST_LDO35V_TRIM_FIELD_T TEST_LDO35V_TRIM_F ;
    };

    union
    {
        __IO  uint32_t TEST_OTP_TRIM                         ; // 0x0024
        AFE_TEST_TEST_OTP_TRIM_FIELD_T TEST_OTP_TRIM_F       ;
    };

    union
    {
        __IO  uint32_t TEST_LIN_TRIM                         ; // 0x0028
        AFE_TEST_TEST_LIN_TRIM_FIELD_T TEST_LIN_TRIM_F       ;
    };

    union
    {
        __IO  uint32_t TEST_LIN_CTRL                         ; // 0x002C
        AFE_TEST_TEST_LIN_CTRL_FIELD_T TEST_LIN_CTRL_F       ;
    };

    union
    {
        __IO  uint32_t TEST_LIN_STATUS                       ; // 0x0030
        AFE_TEST_TEST_LIN_STATUS_FIELD_T TEST_LIN_STATUS_F   ;
    };

    union
    {
        __IO  uint32_t TEST_ADC_CTRL                         ; // 0x0034
        AFE_TEST_TEST_ADC_CTRL_FIELD_T TEST_ADC_CTRL_F       ;
    };

    union
    {
        __IO  uint32_t TEST_BUS_CTRL                         ; // 0x0038
        AFE_TEST_TEST_BUS_CTRL_FIELD_T TEST_BUS_CTRL_F       ;
    };

    union
    {
        __IO  uint32_t TEST_LDO15_TRIM                       ; // 0x003C
        AFE_TEST_TEST_LDO15_TRIM_FIELD_T TEST_LDO15_TRIM_F   ;
    };

    union
    {
        __IO  uint32_t TEST_RSTN_IO_CTRL                     ; // 0x0040
        AFE_TEST_TEST_RSTN_IO_CTRL_FIELD_T TEST_RSTN_IO_CTRL_F;
    };

    union
    {
        __IO  uint32_t TEST_LDO15_CTRL                       ; // 0x0044
        AFE_TEST_TEST_LDO15_CTRL_FIELD_T TEST_LDO15_CTRL_F   ;
    };

    uint32_t RESERVED0[45]                                    ;

    union
    {
        __IO  uint32_t TEST_LOCK                             ; // 0x00FC
        AFE_TEST_TEST_LOCK_FIELD_T TEST_LOCK_F               ;
    };

} AFE_TEST_REG_TypeDef;

#endif
