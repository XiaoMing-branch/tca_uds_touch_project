/**
 *****************************************************************************
 * @brief   afe_pmm_reg_def header file.
 *
 * @file    afe_pmm_reg_def.h
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

#ifndef   AFE_PWM_DEF_H__
#define   AFE_PWM_DEF_H__

// Register Offset Macro Definition
#define AFE_PWM_CTRL_OFFSET                                     0x0000
#define AFE_PWM_CH0_CTRL_OFFSET                                 0x0004
#define AFE_PWM_CH0_CNT_CFG_OFFSET                              0x0008
#define AFE_PWM_CH0_PWM_CFG_OFFSET                              0x000C
#define AFE_PWM_CH0_PHS_CFG_OFFSET                              0x0010
#define AFE_PWM_CH0_CNT_VAL_OFFSET                              0x0014
#define AFE_PWM_CH1_CTRL_OFFSET                                 0x0018
#define AFE_PWM_CH1_CNT_CFG_OFFSET                              0x001C
#define AFE_PWM_CH1_PWM_CFG_OFFSET                              0x0020
#define AFE_PWM_CH1_PHS_CFG_OFFSET                              0x0024
#define AFE_PWM_CH1_CNT_VAL_OFFSET                              0x0028
#define AFE_PWM_CH2_CTRL_OFFSET                                 0x002C
#define AFE_PWM_CH2_CNT_CFG_OFFSET                              0x0030
#define AFE_PWM_CH2_PWM_CFG_OFFSET                              0x0034
#define AFE_PWM_CH2_PHS_CFG_OFFSET                              0x0038
#define AFE_PWM_CH2_CNT_VAL_OFFSET                              0x003C
#define AFE_PWM_PWM_STATUS_OFFSET                               0x0040
#define AFE_PWM_LED_CTRL_OFFSET                                 0x0044
#define AFE_PWM_LED_LC0_CTRL_OFFSET                             0x0048
#define AFE_PWM_LED_LC1_CTRL_OFFSET                             0x004C
#define AFE_PWM_LED_LC2_CTRL_OFFSET                             0x0050
#define AFE_PWM_WR_LOCK_OFFSET                                  0x00FC

// Register Address Macro Definition
#define AFE_PWM_CTRL_ADDR                                       ( AFE_PWM_BASE_ADDR + AFE_PWM_CTRL_OFFSET)
#define AFE_PWM_CH0_CTRL_ADDR                                   ( AFE_PWM_BASE_ADDR + AFE_PWM_CH0_CTRL_OFFSET)
#define AFE_PWM_CH0_CNT_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH0_CNT_CFG_OFFSET)
#define AFE_PWM_CH0_PWM_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH0_PWM_CFG_OFFSET)
#define AFE_PWM_CH0_PHS_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH0_PHS_CFG_OFFSET)
#define AFE_PWM_CH0_CNT_VAL_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH0_CNT_VAL_OFFSET)
#define AFE_PWM_CH1_CTRL_ADDR                                   ( AFE_PWM_BASE_ADDR + AFE_PWM_CH1_CTRL_OFFSET)
#define AFE_PWM_CH1_CNT_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH1_CNT_CFG_OFFSET)
#define AFE_PWM_CH1_PWM_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH1_PWM_CFG_OFFSET)
#define AFE_PWM_CH1_PHS_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH1_PHS_CFG_OFFSET)
#define AFE_PWM_CH1_CNT_VAL_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH1_CNT_VAL_OFFSET)
#define AFE_PWM_CH2_CTRL_ADDR                                   ( AFE_PWM_BASE_ADDR + AFE_PWM_CH2_CTRL_OFFSET)
#define AFE_PWM_CH2_CNT_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH2_CNT_CFG_OFFSET)
#define AFE_PWM_CH2_PWM_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH2_PWM_CFG_OFFSET)
#define AFE_PWM_CH2_PHS_CFG_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH2_PHS_CFG_OFFSET)
#define AFE_PWM_CH2_CNT_VAL_ADDR                                ( AFE_PWM_BASE_ADDR + AFE_PWM_CH2_CNT_VAL_OFFSET)
#define AFE_PWM_PWM_STATUS_ADDR                                 ( AFE_PWM_BASE_ADDR + AFE_PWM_PWM_STATUS_OFFSET)
#define AFE_PWM_LED_CTRL_ADDR                                   ( AFE_PWM_BASE_ADDR + AFE_PWM_LED_CTRL_OFFSET)
#define AFE_PWM_LED_LC0_CTRL_ADDR                               ( AFE_PWM_BASE_ADDR + AFE_PWM_LED_LC0_CTRL_OFFSET)
#define AFE_PWM_LED_LC1_CTRL_ADDR                               ( AFE_PWM_BASE_ADDR + AFE_PWM_LED_LC1_CTRL_OFFSET)
#define AFE_PWM_LED_LC2_CTRL_ADDR                               ( AFE_PWM_BASE_ADDR + AFE_PWM_LED_LC2_CTRL_OFFSET)
#define AFE_PWM_WR_LOCK_ADDR                                    ( AFE_PWM_BASE_ADDR + AFE_PWM_WR_LOCK_OFFSET)

// Register Field Macro Definition
#define AFE_PWM_CTRL_GLB_LD_EN_STATUS_SHIFT                             8
#define AFE_PWM_CTRL_GLB_LD_EN_STATUS_MASK                              0x00000100
#define AFE_PWM_CTRL_GLB_LD_EN_STATUS_SET(n)                            (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PWM_CTRL_GLB_LD_EN_STATUS_CLR                               0xFFFFFEFF

#define AFE_PWM_CTRL_GLB_LD_EN_SET_SHIFT                                4
#define AFE_PWM_CTRL_GLB_LD_EN_SET_MASK                                 0x00000010
#define AFE_PWM_CTRL_GLB_LD_EN_SET_SET(n)                               (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PWM_CTRL_GLB_LD_EN_SET_CLR                                  0xFFFFFFEF

#define AFE_PWM_CTRL_PWM_SW_EN_SHIFT                                    2
#define AFE_PWM_CTRL_PWM_SW_EN_MASK                                     0x00000004
#define AFE_PWM_CTRL_PWM_SW_EN_SET(n)                                   (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_PWM_CTRL_PWM_SW_EN_CLR                                      0xFFFFFFFB

#define AFE_PWM_CTRL_SYNC_EN_SHIFT                                      1
#define AFE_PWM_CTRL_SYNC_EN_MASK                                       0x00000002
#define AFE_PWM_CTRL_SYNC_EN_SET(n)                                     (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_PWM_CTRL_SYNC_EN_CLR                                        0xFFFFFFFD

#define AFE_PWM_CTRL_GLB_EN_SHIFT                                       0
#define AFE_PWM_CTRL_GLB_EN_MASK                                        0x00000001
#define AFE_PWM_CTRL_GLB_EN_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_CTRL_GLB_EN_CLR                                         0xFFFFFFFE

#define AFE_PWM_CH0_CTRL_CH0_AUTO_LD_EN_SHIFT                           28
#define AFE_PWM_CH0_CTRL_CH0_AUTO_LD_EN_MASK                            0x10000000
#define AFE_PWM_CH0_CTRL_CH0_AUTO_LD_EN_SET(n)                          (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_PWM_CH0_CTRL_CH0_AUTO_LD_EN_CLR                             0xEFFFFFFF

#define AFE_PWM_CH0_CTRL_CH0_SW_OUT_SHIFT                               24
#define AFE_PWM_CH0_CTRL_CH0_SW_OUT_MASK                                0x01000000
#define AFE_PWM_CH0_CTRL_CH0_SW_OUT_SET(n)                              (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_PWM_CH0_CTRL_CH0_SW_OUT_CLR                                 0xFEFFFFFF

#define AFE_PWM_CH0_CTRL_CH0_PHS_LD_SHIFT                               15
#define AFE_PWM_CH0_CTRL_CH0_PHS_LD_MASK                                0x00008000
#define AFE_PWM_CH0_CTRL_CH0_PHS_LD_SET(n)                              (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_PWM_CH0_CTRL_CH0_PHS_LD_CLR                                 0xFFFF7FFF

#define AFE_PWM_CH0_CTRL_CH0_PHS_EN_SHIFT                               14
#define AFE_PWM_CH0_CTRL_CH0_PHS_EN_MASK                                0x00004000
#define AFE_PWM_CH0_CTRL_CH0_PHS_EN_SET(n)                              (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_PWM_CH0_CTRL_CH0_PHS_EN_CLR                                 0xFFFFBFFF

#define AFE_PWM_CH0_CTRL_CH0_BRK_EN_SHIFT                               13
#define AFE_PWM_CH0_CTRL_CH0_BRK_EN_MASK                                0x00002000
#define AFE_PWM_CH0_CTRL_CH0_BRK_EN_SET(n)                              (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_PWM_CH0_CTRL_CH0_BRK_EN_CLR                                 0xFFFFDFFF

#define AFE_PWM_CH0_CTRL_CH0_ONE_SHOT_TRIG_SHIFT                        8
#define AFE_PWM_CH0_CTRL_CH0_ONE_SHOT_TRIG_MASK                         0x00000100
#define AFE_PWM_CH0_CTRL_CH0_ONE_SHOT_TRIG_SET(n)                       (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PWM_CH0_CTRL_CH0_ONE_SHOT_TRIG_CLR                          0xFFFFFEFF

#define AFE_PWM_CH0_CTRL_CH0_MODE_SHIFT                                 4
#define AFE_PWM_CH0_CTRL_CH0_MODE_MASK                                  0x00000070
#define AFE_PWM_CH0_CTRL_CH0_MODE_SET(n)                                (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PWM_CH0_CTRL_CH0_MODE_CLR                                   0xFFFFFF8F

#define AFE_PWM_CH0_CTRL_CH0_PTY_SHIFT                                  2
#define AFE_PWM_CH0_CTRL_CH0_PTY_MASK                                   0x00000004
#define AFE_PWM_CH0_CTRL_CH0_PTY_SET(n)                                 (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_PWM_CH0_CTRL_CH0_PTY_CLR                                    0xFFFFFFFB

#define AFE_PWM_CH0_CTRL_CH0_EN_SHIFT                                   0
#define AFE_PWM_CH0_CTRL_CH0_EN_MASK                                    0x00000001
#define AFE_PWM_CH0_CTRL_CH0_EN_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_CH0_CTRL_CH0_EN_CLR                                     0xFFFFFFFE

#define AFE_PWM_CH0_CNT_CFG_PERIOD0_SHIFT                               16
#define AFE_PWM_CH0_CNT_CFG_PERIOD0_MASK                                0xFFFF0000
#define AFE_PWM_CH0_CNT_CFG_PERIOD0_SET(n)                              (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define AFE_PWM_CH0_CNT_CFG_PERIOD0_CLR                                 0x0000FFFF

#define AFE_PWM_CH0_PWM_CFG_HT0_SHIFT                                   16
#define AFE_PWM_CH0_PWM_CFG_HT0_MASK                                    0xFFFF0000
#define AFE_PWM_CH0_PWM_CFG_HT0_SET(n)                                  (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define AFE_PWM_CH0_PWM_CFG_HT0_CLR                                     0x0000FFFF

#define AFE_PWM_CH0_PWM_CFG_LT0_SHIFT                                   0
#define AFE_PWM_CH0_PWM_CFG_LT0_MASK                                    0x0000FFFF
#define AFE_PWM_CH0_PWM_CFG_LT0_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH0_PWM_CFG_LT0_CLR                                     0xFFFF0000

#define AFE_PWM_CH0_PHS_CFG_INIT_PHS0_SHIFT                             0
#define AFE_PWM_CH0_PHS_CFG_INIT_PHS0_MASK                              0x0000FFFF
#define AFE_PWM_CH0_PHS_CFG_INIT_PHS0_SET(n)                            (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH0_PHS_CFG_INIT_PHS0_CLR                               0xFFFF0000

#define AFE_PWM_CH0_CNT_VAL_CNT0_VAL_SHIFT                              0
#define AFE_PWM_CH0_CNT_VAL_CNT0_VAL_MASK                               0x0000FFFF
#define AFE_PWM_CH0_CNT_VAL_CNT0_VAL_SET(n)                             (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH0_CNT_VAL_CNT0_VAL_CLR                                0xFFFF0000

#define AFE_PWM_CH1_CTRL_CH1_AUTO_LD_EN_SHIFT                           28
#define AFE_PWM_CH1_CTRL_CH1_AUTO_LD_EN_MASK                            0x10000000
#define AFE_PWM_CH1_CTRL_CH1_AUTO_LD_EN_SET(n)                          (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_PWM_CH1_CTRL_CH1_AUTO_LD_EN_CLR                             0xEFFFFFFF

#define AFE_PWM_CH1_CTRL_CH1_SW_OUT_SHIFT                               24
#define AFE_PWM_CH1_CTRL_CH1_SW_OUT_MASK                                0x01000000
#define AFE_PWM_CH1_CTRL_CH1_SW_OUT_SET(n)                              (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_PWM_CH1_CTRL_CH1_SW_OUT_CLR                                 0xFEFFFFFF

#define AFE_PWM_CH1_CTRL_CH1_PHS_LD_SHIFT                               15
#define AFE_PWM_CH1_CTRL_CH1_PHS_LD_MASK                                0x00008000
#define AFE_PWM_CH1_CTRL_CH1_PHS_LD_SET(n)                              (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_PWM_CH1_CTRL_CH1_PHS_LD_CLR                                 0xFFFF7FFF

#define AFE_PWM_CH1_CTRL_CH1_PHS_EN_SHIFT                               14
#define AFE_PWM_CH1_CTRL_CH1_PHS_EN_MASK                                0x00004000
#define AFE_PWM_CH1_CTRL_CH1_PHS_EN_SET(n)                              (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_PWM_CH1_CTRL_CH1_PHS_EN_CLR                                 0xFFFFBFFF

#define AFE_PWM_CH1_CTRL_CH1_BRK_EN_SHIFT                               13
#define AFE_PWM_CH1_CTRL_CH1_BRK_EN_MASK                                0x00002000
#define AFE_PWM_CH1_CTRL_CH1_BRK_EN_SET(n)                              (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_PWM_CH1_CTRL_CH1_BRK_EN_CLR                                 0xFFFFDFFF

#define AFE_PWM_CH1_CTRL_CH1_ONE_SHOT_TRIG_SHIFT                        8
#define AFE_PWM_CH1_CTRL_CH1_ONE_SHOT_TRIG_MASK                         0x00000100
#define AFE_PWM_CH1_CTRL_CH1_ONE_SHOT_TRIG_SET(n)                       (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PWM_CH1_CTRL_CH1_ONE_SHOT_TRIG_CLR                          0xFFFFFEFF

#define AFE_PWM_CH1_CTRL_CH1_MODE_SHIFT                                 4
#define AFE_PWM_CH1_CTRL_CH1_MODE_MASK                                  0x00000070
#define AFE_PWM_CH1_CTRL_CH1_MODE_SET(n)                                (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PWM_CH1_CTRL_CH1_MODE_CLR                                   0xFFFFFF8F

#define AFE_PWM_CH1_CTRL_CH1_PTY_SHIFT                                  2
#define AFE_PWM_CH1_CTRL_CH1_PTY_MASK                                   0x00000004
#define AFE_PWM_CH1_CTRL_CH1_PTY_SET(n)                                 (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_PWM_CH1_CTRL_CH1_PTY_CLR                                    0xFFFFFFFB

#define AFE_PWM_CH1_CTRL_CH1_EN_SHIFT                                   0
#define AFE_PWM_CH1_CTRL_CH1_EN_MASK                                    0x00000001
#define AFE_PWM_CH1_CTRL_CH1_EN_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_CH1_CTRL_CH1_EN_CLR                                     0xFFFFFFFE

#define AFE_PWM_CH1_CNT_CFG_PERIOD1_SHIFT                               16
#define AFE_PWM_CH1_CNT_CFG_PERIOD1_MASK                                0xFFFF0000
#define AFE_PWM_CH1_CNT_CFG_PERIOD1_SET(n)                              (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define AFE_PWM_CH1_CNT_CFG_PERIOD1_CLR                                 0x0000FFFF

#define AFE_PWM_CH1_PWM_CFG_HT1_SHIFT                                   16
#define AFE_PWM_CH1_PWM_CFG_HT1_MASK                                    0xFFFF0000
#define AFE_PWM_CH1_PWM_CFG_HT1_SET(n)                                  (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define AFE_PWM_CH1_PWM_CFG_HT1_CLR                                     0x0000FFFF

#define AFE_PWM_CH1_PWM_CFG_LT1_SHIFT                                   0
#define AFE_PWM_CH1_PWM_CFG_LT1_MASK                                    0x0000FFFF
#define AFE_PWM_CH1_PWM_CFG_LT1_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH1_PWM_CFG_LT1_CLR                                     0xFFFF0000

#define AFE_PWM_CH1_PHS_CFG_INIT_PHS1_SHIFT                             0
#define AFE_PWM_CH1_PHS_CFG_INIT_PHS1_MASK                              0x0000FFFF
#define AFE_PWM_CH1_PHS_CFG_INIT_PHS1_SET(n)                            (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH1_PHS_CFG_INIT_PHS1_CLR                               0xFFFF0000

#define AFE_PWM_CH1_CNT_VAL_CNT1_VAL_SHIFT                              0
#define AFE_PWM_CH1_CNT_VAL_CNT1_VAL_MASK                               0x0000FFFF
#define AFE_PWM_CH1_CNT_VAL_CNT1_VAL_SET(n)                             (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH1_CNT_VAL_CNT1_VAL_CLR                                0xFFFF0000

#define AFE_PWM_CH2_CTRL_CH2_AUTO_LD_EN_SHIFT                           28
#define AFE_PWM_CH2_CTRL_CH2_AUTO_LD_EN_MASK                            0x10000000
#define AFE_PWM_CH2_CTRL_CH2_AUTO_LD_EN_SET(n)                          (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_PWM_CH2_CTRL_CH2_AUTO_LD_EN_CLR                             0xEFFFFFFF

#define AFE_PWM_CH2_CTRL_CH2_SW_OUT_SHIFT                               24
#define AFE_PWM_CH2_CTRL_CH2_SW_OUT_MASK                                0x01000000
#define AFE_PWM_CH2_CTRL_CH2_SW_OUT_SET(n)                              (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_PWM_CH2_CTRL_CH2_SW_OUT_CLR                                 0xFEFFFFFF

#define AFE_PWM_CH2_CTRL_CH2_PHS_LD_SHIFT                               15
#define AFE_PWM_CH2_CTRL_CH2_PHS_LD_MASK                                0x00008000
#define AFE_PWM_CH2_CTRL_CH2_PHS_LD_SET(n)                              (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_PWM_CH2_CTRL_CH2_PHS_LD_CLR                                 0xFFFF7FFF

#define AFE_PWM_CH2_CTRL_CH2_PHS_EN_SHIFT                               14
#define AFE_PWM_CH2_CTRL_CH2_PHS_EN_MASK                                0x00004000
#define AFE_PWM_CH2_CTRL_CH2_PHS_EN_SET(n)                              (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_PWM_CH2_CTRL_CH2_PHS_EN_CLR                                 0xFFFFBFFF

#define AFE_PWM_CH2_CTRL_CH2_BRK_EN_SHIFT                               13
#define AFE_PWM_CH2_CTRL_CH2_BRK_EN_MASK                                0x00002000
#define AFE_PWM_CH2_CTRL_CH2_BRK_EN_SET(n)                              (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_PWM_CH2_CTRL_CH2_BRK_EN_CLR                                 0xFFFFDFFF

#define AFE_PWM_CH2_CTRL_CH2_ONE_SHOT_TRIG_SHIFT                        8
#define AFE_PWM_CH2_CTRL_CH2_ONE_SHOT_TRIG_MASK                         0x00000100
#define AFE_PWM_CH2_CTRL_CH2_ONE_SHOT_TRIG_SET(n)                       (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PWM_CH2_CTRL_CH2_ONE_SHOT_TRIG_CLR                          0xFFFFFEFF

#define AFE_PWM_CH2_CTRL_CH2_MODE_SHIFT                                 4
#define AFE_PWM_CH2_CTRL_CH2_MODE_MASK                                  0x00000070
#define AFE_PWM_CH2_CTRL_CH2_MODE_SET(n)                                (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PWM_CH2_CTRL_CH2_MODE_CLR                                   0xFFFFFF8F

#define AFE_PWM_CH2_CTRL_CH2_PTY_SHIFT                                  2
#define AFE_PWM_CH2_CTRL_CH2_PTY_MASK                                   0x00000004
#define AFE_PWM_CH2_CTRL_CH2_PTY_SET(n)                                 (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_PWM_CH2_CTRL_CH2_PTY_CLR                                    0xFFFFFFFB

#define AFE_PWM_CH2_CTRL_CH2_EN_SHIFT                                   0
#define AFE_PWM_CH2_CTRL_CH2_EN_MASK                                    0x00000001
#define AFE_PWM_CH2_CTRL_CH2_EN_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_CH2_CTRL_CH2_EN_CLR                                     0xFFFFFFFE

#define AFE_PWM_CH2_CNT_CFG_PERIOD2_SHIFT                               16
#define AFE_PWM_CH2_CNT_CFG_PERIOD2_MASK                                0xFFFF0000
#define AFE_PWM_CH2_CNT_CFG_PERIOD2_SET(n)                              (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define AFE_PWM_CH2_CNT_CFG_PERIOD2_CLR                                 0x0000FFFF

#define AFE_PWM_CH2_PWM_CFG_HT2_SHIFT                                   16
#define AFE_PWM_CH2_PWM_CFG_HT2_MASK                                    0xFFFF0000
#define AFE_PWM_CH2_PWM_CFG_HT2_SET(n)                                  (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define AFE_PWM_CH2_PWM_CFG_HT2_CLR                                     0x0000FFFF

#define AFE_PWM_CH2_PWM_CFG_LT2_SHIFT                                   0
#define AFE_PWM_CH2_PWM_CFG_LT2_MASK                                    0x0000FFFF
#define AFE_PWM_CH2_PWM_CFG_LT2_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH2_PWM_CFG_LT2_CLR                                     0xFFFF0000

#define AFE_PWM_CH2_PHS_CFG_INIT_PHS2_SHIFT                             0
#define AFE_PWM_CH2_PHS_CFG_INIT_PHS2_MASK                              0x0000FFFF
#define AFE_PWM_CH2_PHS_CFG_INIT_PHS2_SET(n)                            (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH2_PHS_CFG_INIT_PHS2_CLR                               0xFFFF0000

#define AFE_PWM_CH2_CNT_VAL_CNT2_VAL_SHIFT                              0
#define AFE_PWM_CH2_CNT_VAL_CNT2_VAL_MASK                               0x0000FFFF
#define AFE_PWM_CH2_CNT_VAL_CNT2_VAL_SET(n)                             (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_PWM_CH2_CNT_VAL_CNT2_VAL_CLR                                0xFFFF0000

#define AFE_PWM_PWM_STATUS_CH2_OUT_SHIFT                                3
#define AFE_PWM_PWM_STATUS_CH2_OUT_MASK                                 0x00000008
#define AFE_PWM_PWM_STATUS_CH2_OUT_SET(n)                               (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_PWM_PWM_STATUS_CH2_OUT_CLR                                  0xFFFFFFF7

#define AFE_PWM_PWM_STATUS_CH1_OUT_SHIFT                                2
#define AFE_PWM_PWM_STATUS_CH1_OUT_MASK                                 0x00000004
#define AFE_PWM_PWM_STATUS_CH1_OUT_SET(n)                               (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_PWM_PWM_STATUS_CH1_OUT_CLR                                  0xFFFFFFFB

#define AFE_PWM_PWM_STATUS_CH0_OUT_SHIFT                                1
#define AFE_PWM_PWM_STATUS_CH0_OUT_MASK                                 0x00000002
#define AFE_PWM_PWM_STATUS_CH0_OUT_SET(n)                               (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_PWM_PWM_STATUS_CH0_OUT_CLR                                  0xFFFFFFFD

#define AFE_PWM_PWM_STATUS_BRK_IN_VAL_SHIFT                             0
#define AFE_PWM_PWM_STATUS_BRK_IN_VAL_MASK                              0x00000001
#define AFE_PWM_PWM_STATUS_BRK_IN_VAL_SET(n)                            (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_PWM_STATUS_BRK_IN_VAL_CLR                               0xFFFFFFFE

#define AFE_PWM_LED_CTRL_LED_RESERVE_SHIFT                              8
#define AFE_PWM_LED_CTRL_LED_RESERVE_MASK                               0x000FFF00
#define AFE_PWM_LED_CTRL_LED_RESERVE_SET(n)                             (((uint32_t)(n) << 8  ) & 0x000FFF00)
#define AFE_PWM_LED_CTRL_LED_RESERVE_CLR                                0xFFF000FF

#define AFE_PWM_LED_CTRL_LED_EN_SHIFT                                   0
#define AFE_PWM_LED_CTRL_LED_EN_MASK                                    0x00000001
#define AFE_PWM_LED_CTRL_LED_EN_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_LED_CTRL_LED_EN_CLR                                     0xFFFFFFFE

#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TF_SHIFT                       14
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TF_MASK                        0x0000C000
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TF_SET(n)                      (((uint32_t)(n) << 14 ) & 0x0000C000)
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TF_CLR                         0xFFFF3FFF

#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TR_SHIFT                       12
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TR_MASK                        0x00003000
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TR_SET(n)                      (((uint32_t)(n) << 12 ) & 0x00003000)
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_SEL_TR_CLR                         0xFFFFCFFF

#define AFE_PWM_LED_LC0_CTRL_LED_LC0_IOUT_SEL_SHIFT                     8
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_IOUT_SEL_MASK                      0x00000F00
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_IOUT_SEL_SET(n)                    (((uint32_t)(n) << 8  ) & 0x00000F00)
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_IOUT_SEL_CLR                       0xFFFFF0FF

#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_I_SEL_SHIFT                   4
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_I_SEL_MASK                    0x00000070
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_I_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_I_SEL_CLR                     0xFFFFFF8F

#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DISPU_EN_SHIFT                     1
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DISPU_EN_MASK                      0x00000002
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DISPU_EN_SET(n)                    (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DISPU_EN_CLR                       0xFFFFFFFD

#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_EN_SHIFT                      0
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_EN_MASK                       0x00000001
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_EN_SET(n)                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_LED_LC0_CTRL_LED_LC0_DIAG_EN_CLR                        0xFFFFFFFE

#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TF_SHIFT                       14
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TF_MASK                        0x0000C000
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TF_SET(n)                      (((uint32_t)(n) << 14 ) & 0x0000C000)
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TF_CLR                         0xFFFF3FFF

#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TR_SHIFT                       12
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TR_MASK                        0x00003000
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TR_SET(n)                      (((uint32_t)(n) << 12 ) & 0x00003000)
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_SEL_TR_CLR                         0xFFFFCFFF

#define AFE_PWM_LED_LC1_CTRL_LED_LC1_IOUT_SEL_SHIFT                     8
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_IOUT_SEL_MASK                      0x00000F00
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_IOUT_SEL_SET(n)                    (((uint32_t)(n) << 8  ) & 0x00000F00)
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_IOUT_SEL_CLR                       0xFFFFF0FF

#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_I_SEL_SHIFT                   4
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_I_SEL_MASK                    0x00000070
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_I_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_I_SEL_CLR                     0xFFFFFF8F

#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DISPU_EN_SHIFT                     1
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DISPU_EN_MASK                      0x00000002
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DISPU_EN_SET(n)                    (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DISPU_EN_CLR                       0xFFFFFFFD

#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_EN_SHIFT                      0
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_EN_MASK                       0x00000001
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_EN_SET(n)                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_LED_LC1_CTRL_LED_LC1_DIAG_EN_CLR                        0xFFFFFFFE

#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TF_SHIFT                       14
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TF_MASK                        0x0000C000
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TF_SET(n)                      (((uint32_t)(n) << 14 ) & 0x0000C000)
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TF_CLR                         0xFFFF3FFF

#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TR_SHIFT                       12
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TR_MASK                        0x00003000
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TR_SET(n)                      (((uint32_t)(n) << 12 ) & 0x00003000)
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_SEL_TR_CLR                         0xFFFFCFFF

#define AFE_PWM_LED_LC2_CTRL_LED_LC2_IOUT_SEL_SHIFT                     8
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_IOUT_SEL_MASK                      0x00000F00
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_IOUT_SEL_SET(n)                    (((uint32_t)(n) << 8  ) & 0x00000F00)
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_IOUT_SEL_CLR                       0xFFFFF0FF

#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_I_SEL_SHIFT                   4
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_I_SEL_MASK                    0x00000070
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_I_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_I_SEL_CLR                     0xFFFFFF8F

#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DISPU_EN_SHIFT                     1
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DISPU_EN_MASK                      0x00000002
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DISPU_EN_SET(n)                    (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DISPU_EN_CLR                       0xFFFFFFFD

#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_EN_SHIFT                      0
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_EN_MASK                       0x00000001
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_EN_SET(n)                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_LED_LC2_CTRL_LED_LC2_DIAG_EN_CLR                        0xFFFFFFFE

#define AFE_PWM_WR_LOCK_WR_LOCK_SHIFT                                   0
#define AFE_PWM_WR_LOCK_WR_LOCK_MASK                                    0x00000001
#define AFE_PWM_WR_LOCK_WR_LOCK_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PWM_WR_LOCK_WR_LOCK_CLR                                     0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t GLB_EN             : 1  ; // 0  : 0
    __IO uint32_t SYNC_EN            : 1  ; // 1  : 1
    __IO uint32_t PWM_SW_EN          : 1  ; // 2  : 2
    __IO uint32_t RESERVED2          : 1  ; // 3  : 3
    __IO uint32_t GLB_LD_EN_SET      : 1  ; // 4  : 4
    __IO uint32_t RESERVED1          : 3  ; // 7  : 5
    __IO uint32_t GLB_LD_EN_STATUS   : 1  ; // 8  : 8
    __IO uint32_t RESERVED0          : 23 ; // 31 : 9
} AFE_PWM_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t CH0_EN             : 1  ; // 0  : 0
    __IO uint32_t RESERVED6          : 1  ; // 1  : 1
    __IO uint32_t CH0_PTY            : 1  ; // 2  : 2
    __IO uint32_t RESERVED5          : 1  ; // 3  : 3
    __IO uint32_t CH0_MODE           : 3  ; // 6  : 4
    __IO uint32_t RESERVED4          : 1  ; // 7  : 7
    __IO uint32_t CH0_ONE_SHOT_TRIG  : 1  ; // 8  : 8
    __IO uint32_t RESERVED3          : 4  ; // 12 : 9
    __IO uint32_t CH0_BRK_EN         : 1  ; // 13 : 13
    __IO uint32_t CH0_PHS_EN         : 1  ; // 14 : 14
    __IO uint32_t CH0_PHS_LD         : 1  ; // 15 : 15
    __IO uint32_t RESERVED2          : 8  ; // 23 : 16
    __IO uint32_t CH0_SW_OUT         : 1  ; // 24 : 24
    __IO uint32_t RESERVED1          : 3  ; // 27 : 25
    __IO uint32_t CH0_AUTO_LD_EN     : 1  ; // 28 : 28
    __IO uint32_t RESERVED0          : 3  ; // 31 : 29
} AFE_PWM_CH0_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RESERVED           : 16 ; // 15 : 0
    __IO uint32_t PERIOD0            : 16 ; // 31 : 16
} AFE_PWM_CH0_CNT_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t LT0                : 16 ; // 15 : 0
    __IO uint32_t HT0                : 16 ; // 31 : 16
} AFE_PWM_CH0_PWM_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INIT_PHS0          : 16 ; // 15 : 0
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_CH0_PHS_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t CNT0_VAL           : 16 ; // 15 : 0
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_CH0_CNT_VAL_FIELD_T;

typedef struct
{
    __IO uint32_t CH1_EN             : 1  ; // 0  : 0
    __IO uint32_t RESERVED6          : 1  ; // 1  : 1
    __IO uint32_t CH1_PTY            : 1  ; // 2  : 2
    __IO uint32_t RESERVED5          : 1  ; // 3  : 3
    __IO uint32_t CH1_MODE           : 3  ; // 6  : 4
    __IO uint32_t RESERVED4          : 1  ; // 7  : 7
    __IO uint32_t CH1_ONE_SHOT_TRIG  : 1  ; // 8  : 8
    __IO uint32_t RESERVED3          : 4  ; // 12 : 9
    __IO uint32_t CH1_BRK_EN         : 1  ; // 13 : 13
    __IO uint32_t CH1_PHS_EN         : 1  ; // 14 : 14
    __IO uint32_t CH1_PHS_LD         : 1  ; // 15 : 15
    __IO uint32_t RESERVED2          : 8  ; // 23 : 16
    __IO uint32_t CH1_SW_OUT         : 1  ; // 24 : 24
    __IO uint32_t RESERVED1          : 3  ; // 27 : 25
    __IO uint32_t CH1_AUTO_LD_EN     : 1  ; // 28 : 28
    __IO uint32_t RESERVED0          : 3  ; // 31 : 29
} AFE_PWM_CH1_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RESERVED           : 16 ; // 15 : 0
    __IO uint32_t PERIOD1            : 16 ; // 31 : 16
} AFE_PWM_CH1_CNT_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t LT1                : 16 ; // 15 : 0
    __IO uint32_t HT1                : 16 ; // 31 : 16
} AFE_PWM_CH1_PWM_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INIT_PHS1          : 16 ; // 15 : 0
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_CH1_PHS_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t CNT1_VAL           : 16 ; // 15 : 0
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_CH1_CNT_VAL_FIELD_T;

typedef struct
{
    __IO uint32_t CH2_EN             : 1  ; // 0  : 0
    __IO uint32_t RESERVED7          : 1  ; // 1  : 1
    __IO uint32_t CH2_PTY            : 1  ; // 2  : 2
    __IO uint32_t RESERVED6          : 1  ; // 3  : 3
    __IO uint32_t CH2_MODE           : 3  ; // 6  : 4
    __IO uint32_t RESERVED5          : 1  ; // 7  : 7
    __IO uint32_t CH2_ONE_SHOT_TRIG  : 1  ; // 8  : 8
    __IO uint32_t RESERVED4          : 4  ; // 12 : 9
    __IO uint32_t CH2_BRK_EN         : 1  ; // 13 : 13
    __IO uint32_t CH2_PHS_EN         : 1  ; // 14 : 14
    __IO uint32_t CH2_PHS_LD         : 1  ; // 15 : 15
    __IO uint32_t RESERVED3          : 8  ; // 23 : 16
    __IO uint32_t CH2_SW_OUT         : 1  ; // 24 : 24
    __IO uint32_t RESERVED2          : 1  ; // 25 : 25
    __IO uint32_t RESERVED1          : 2  ; // 27 : 26
    __IO uint32_t CH2_AUTO_LD_EN     : 1  ; // 28 : 28
    __IO uint32_t RESERVED0          : 3  ; // 31 : 29
} AFE_PWM_CH2_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RESERVED           : 16 ; // 15 : 0
    __IO uint32_t PERIOD2            : 16 ; // 31 : 16
} AFE_PWM_CH2_CNT_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t LT2                : 16 ; // 15 : 0
    __IO uint32_t HT2                : 16 ; // 31 : 16
} AFE_PWM_CH2_PWM_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INIT_PHS2          : 16 ; // 15 : 0
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_CH2_PHS_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t CNT2_VAL           : 16 ; // 15 : 0
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_CH2_CNT_VAL_FIELD_T;

typedef struct
{
    __IO uint32_t BRK_IN_VAL         : 1  ; // 0  : 0
    __IO uint32_t CH0_OUT            : 1  ; // 1  : 1
    __IO uint32_t CH1_OUT            : 1  ; // 2  : 2
    __IO uint32_t CH2_OUT            : 1  ; // 3  : 3
    __IO uint32_t RESERVED0          : 28 ; // 31 : 4
} AFE_PWM_PWM_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t LED_EN             : 1  ; // 0  : 0
    __IO uint32_t RESERVED1          : 7  ; // 7  : 1
    __IO uint32_t LED_RESERVE        : 12 ; // 19 : 8
    __IO uint32_t RESERVED0          : 12 ; // 31 : 20
} AFE_PWM_LED_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LED_LC0_DIAG_EN    : 1  ; // 0  : 0
    __IO uint32_t LED_LC0_DISPU_EN   : 1  ; // 1  : 1
    __IO uint32_t RESERVED2          : 2  ; // 3  : 2
    __IO uint32_t LED_LC0_DIAG_I_SEL : 3  ; // 6  : 4
    __IO uint32_t RESERVED1          : 1  ; // 7  : 7
    __IO uint32_t LED_LC0_IOUT_SEL   : 4  ; // 11 : 8
    __IO uint32_t LED_LC0_SEL_TR     : 2  ; // 13 : 12
    __IO uint32_t LED_LC0_SEL_TF     : 2  ; // 15 : 14
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_LED_LC0_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LED_LC1_DIAG_EN    : 1  ; // 0  : 0
    __IO uint32_t LED_LC1_DISPU_EN   : 1  ; // 1  : 1
    __IO uint32_t RESERVED2          : 2  ; // 3  : 2
    __IO uint32_t LED_LC1_DIAG_I_SEL : 3  ; // 6  : 4
    __IO uint32_t RESERVED1          : 1  ; // 7  : 7
    __IO uint32_t LED_LC1_IOUT_SEL   : 4  ; // 11 : 8
    __IO uint32_t LED_LC1_SEL_TR     : 2  ; // 13 : 12
    __IO uint32_t LED_LC1_SEL_TF     : 2  ; // 15 : 14
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_LED_LC1_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LED_LC2_DIAG_EN    : 1  ; // 0  : 0
    __IO uint32_t LED_LC2_DISPU_EN   : 1  ; // 1  : 1
    __IO uint32_t RESERVED2          : 2  ; // 3  : 2
    __IO uint32_t LED_LC2_DIAG_I_SEL : 3  ; // 6  : 4
    __IO uint32_t RESERVED1          : 1  ; // 7  : 7
    __IO uint32_t LED_LC2_IOUT_SEL   : 4  ; // 11 : 8
    __IO uint32_t LED_LC2_SEL_TR     : 2  ; // 13 : 12
    __IO uint32_t LED_LC2_SEL_TF     : 2  ; // 15 : 14
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} AFE_PWM_LED_LC2_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t WR_LOCK            : 1  ; // 0  : 0
    __IO uint32_t RESERVED0          : 31 ; // 31 : 1
} AFE_PWM_WR_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t CTRL                        ; // 0x0000
        AFE_PWM_CTRL_FIELD_T CTRL_F                ;
    };

    union
    {
        __IO  uint32_t CH0_CTRL                    ; // 0x0004
        AFE_PWM_CH0_CTRL_FIELD_T CH0_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t CH0_CNT_CFG                 ; // 0x0008
        AFE_PWM_CH0_CNT_CFG_FIELD_T CH0_CNT_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH0_PWM_CFG                 ; // 0x000C
        AFE_PWM_CH0_PWM_CFG_FIELD_T CH0_PWM_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH0_PHS_CFG                 ; // 0x0010
        AFE_PWM_CH0_PHS_CFG_FIELD_T CH0_PHS_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH0_CNT_VAL                 ; // 0x0014
        AFE_PWM_CH0_CNT_VAL_FIELD_T CH0_CNT_VAL_F  ;
    };

    union
    {
        __IO  uint32_t CH1_CTRL                    ; // 0x0018
        AFE_PWM_CH1_CTRL_FIELD_T CH1_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t CH1_CNT_CFG                 ; // 0x001C
        AFE_PWM_CH1_CNT_CFG_FIELD_T CH1_CNT_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH1_PWM_CFG                 ; // 0x0020
        AFE_PWM_CH1_PWM_CFG_FIELD_T CH1_PWM_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH1_PHS_CFG                 ; // 0x0024
        AFE_PWM_CH1_PHS_CFG_FIELD_T CH1_PHS_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH1_CNT_VAL                 ; // 0x0028
        AFE_PWM_CH1_CNT_VAL_FIELD_T CH1_CNT_VAL_F  ;
    };

    union
    {
        __IO  uint32_t CH2_CTRL                    ; // 0x002C
        AFE_PWM_CH2_CTRL_FIELD_T CH2_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t CH2_CNT_CFG                 ; // 0x0030
        AFE_PWM_CH2_CNT_CFG_FIELD_T CH2_CNT_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH2_PWM_CFG                 ; // 0x0034
        AFE_PWM_CH2_PWM_CFG_FIELD_T CH2_PWM_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH2_PHS_CFG                 ; // 0x0038
        AFE_PWM_CH2_PHS_CFG_FIELD_T CH2_PHS_CFG_F  ;
    };

    union
    {
        __IO  uint32_t CH2_CNT_VAL                 ; // 0x003C
        AFE_PWM_CH2_CNT_VAL_FIELD_T CH2_CNT_VAL_F  ;
    };

    union
    {
        __IO  uint32_t PWM_STATUS                  ; // 0x0040
        AFE_PWM_PWM_STATUS_FIELD_T PWM_STATUS_F    ;
    };

    union
    {
        __IO  uint32_t LED_CTRL                    ; // 0x0044
        AFE_PWM_LED_CTRL_FIELD_T LED_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t LED_LC0_CTRL                ; // 0x0048
        AFE_PWM_LED_LC0_CTRL_FIELD_T LED_LC0_CTRL_F;
    };

    union
    {
        __IO  uint32_t LED_LC1_CTRL                ; // 0x004C
        AFE_PWM_LED_LC1_CTRL_FIELD_T LED_LC1_CTRL_F;
    };

    union
    {
        __IO  uint32_t LED_LC2_CTRL                ; // 0x0050
        AFE_PWM_LED_LC2_CTRL_FIELD_T LED_LC2_CTRL_F;
    };

    uint32_t RESERVED0[42]                          ;

    union
    {
        __IO  uint32_t WR_LOCK                     ; // 0x00FC
        AFE_PWM_WR_LOCK_FIELD_T WR_LOCK_F          ;
    };

} AFE_PWM_REG_TypeDef;

#endif
