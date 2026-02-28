/**
 *****************************************************************************
 * @brief   captouch_reg_def header file.
 *
 * @file    captouch_reg_def.h
 * @author  AE/FAE team
 * @date    2024.09.01
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

#ifndef   CAPTOUCH_DEF_H__
#define   CAPTOUCH_DEF_H__

// Register Offset Macro Definition
#define CAPTOUCH_IMR_OFFSET                                     0x0000
#define CAPTOUCH_ICR_OFFSET                                     0x0004
#define CAPTOUCH_ISR_OFFSET                                     0x0008
#define CAPTOUCH_IRSR_OFFSET                                    0x000C
#define CAPTOUCH_CTRL0_OFFSET                                   0x0010
#define CAPTOUCH_CTRL1_OFFSET                                   0x0014
#define CAPTOUCH_CTRL2_OFFSET                                   0x0018
#define CAPTOUCH_CTRL3_OFFSET                                   0x001C
#define CAPTOUCH_CTRL4_OFFSET                                   0x0020
#define CAPTOUCH_STATUS_OFFSET                                  0x0024
#define CAPTOUCH_CTRL5_OFFSET                                   0x0028
#define CAPTOUCH_CTRL6_OFFSET                                   0x002C

// Register Address Macro Definition
#define CAPTOUCH_IMR_ADDR                                       ( CAPTOUCH_BASE_ADDR + CAPTOUCH_IMR_OFFSET)
#define CAPTOUCH_ICR_ADDR                                       ( CAPTOUCH_BASE_ADDR + CAPTOUCH_ICR_OFFSET)
#define CAPTOUCH_ISR_ADDR                                       ( CAPTOUCH_BASE_ADDR + CAPTOUCH_ISR_OFFSET)
#define CAPTOUCH_IRSR_ADDR                                      ( CAPTOUCH_BASE_ADDR + CAPTOUCH_IRSR_OFFSET)
#define CAPTOUCH_CTRL0_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL0_OFFSET)
#define CAPTOUCH_CTRL1_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL1_OFFSET)
#define CAPTOUCH_CTRL2_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL2_OFFSET)
#define CAPTOUCH_CTRL3_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL3_OFFSET)
#define CAPTOUCH_CTRL4_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL4_OFFSET)
#define CAPTOUCH_STATUS_ADDR                                    ( CAPTOUCH_BASE_ADDR + CAPTOUCH_STATUS_OFFSET)
#define CAPTOUCH_CTRL5_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL5_OFFSET)
#define CAPTOUCH_CTRL6_ADDR                                     ( CAPTOUCH_BASE_ADDR + CAPTOUCH_CTRL6_OFFSET)

// Register Field Macro Definition
#define CAPTOUCH_IMR_IMR_SHIFT                                  0
#define CAPTOUCH_IMR_IMR_MASK                                   0x0000000F
#define CAPTOUCH_IMR_IMR_SET(n)                                 (((uint32_t)(n) << 0  ) & 0x0000000F)
#define CAPTOUCH_IMR_IMR_CLR                                    0xFFFFFFF0

#define CAPTOUCH_ICR_ICR_SHIFT                                  0
#define CAPTOUCH_ICR_ICR_MASK                                   0x0000000F
#define CAPTOUCH_ICR_ICR_SET(n)                                 (((uint32_t)(n) << 0  ) & 0x0000000F)
#define CAPTOUCH_ICR_ICR_CLR                                    0xFFFFFFF0

#define CAPTOUCH_ISR_ISR_SHIFT                                  0
#define CAPTOUCH_ISR_ISR_MASK                                   0x0000000F
#define CAPTOUCH_ISR_ISR_SET(n)                                 (((uint32_t)(n) << 0  ) & 0x0000000F)
#define CAPTOUCH_ISR_ISR_CLR                                    0xFFFFFFF0

#define CAPTOUCH_IRSR_IRSR_SHIFT                                0
#define CAPTOUCH_IRSR_IRSR_MASK                                 0x0000000F
#define CAPTOUCH_IRSR_IRSR_SET(n)                               (((uint32_t)(n) << 0  ) & 0x0000000F)
#define CAPTOUCH_IRSR_IRSR_CLR                                  0xFFFFFFF0

#define CAPTOUCH_CTRL0_CAL_SEL_SHIFT                            16
#define CAPTOUCH_CTRL0_CAL_SEL_MASK                             0x00030000
#define CAPTOUCH_CTRL0_CAL_SEL_SET(n)                           (((uint32_t)(n) << 16 ) & 0x00030000)
#define CAPTOUCH_CTRL0_CAL_SEL_CLR                              0xFFFCFFFF

#define CAPTOUCH_CTRL0_SHLD_I_SHIFT                             12
#define CAPTOUCH_CTRL0_SHLD_I_MASK                              0x00007000
#define CAPTOUCH_CTRL0_SHLD_I_SET(n)                            (((uint32_t)(n) << 12 ) & 0x00007000)
#define CAPTOUCH_CTRL0_SHLD_I_CLR                               0xFFFF8FFF

#define CAPTOUCH_CTRL0_SHLD_SEL_SHIFT                           8
#define CAPTOUCH_CTRL0_SHLD_SEL_MASK                            0x00000700
#define CAPTOUCH_CTRL0_SHLD_SEL_SET(n)                          (((uint32_t)(n) << 8  ) & 0x00000700)
#define CAPTOUCH_CTRL0_SHLD_SEL_CLR                             0xFFFFF8FF

#define CAPTOUCH_CTRL0_CHNL_SEL_SHIFT                           4
#define CAPTOUCH_CTRL0_CHNL_SEL_MASK                            0x00000070
#define CAPTOUCH_CTRL0_CHNL_SEL_SET(n)                          (((uint32_t)(n) << 4  ) & 0x00000070)
#define CAPTOUCH_CTRL0_CHNL_SEL_CLR                             0xFFFFFF8F

#define CAPTOUCH_CTRL0_SW_TRIG_SHIFT                            0
#define CAPTOUCH_CTRL0_SW_TRIG_MASK                             0x00000001
#define CAPTOUCH_CTRL0_SW_TRIG_SET(n)                           (((uint32_t)(n) << 0  ) & 0x00000001)
#define CAPTOUCH_CTRL0_SW_TRIG_CLR                              0xFFFFFFFE

#define CAPTOUCH_CTRL1_SAMP_OVF_TIME_SHIFT                      20
#define CAPTOUCH_CTRL1_SAMP_OVF_TIME_MASK                       0xFFF00000
#define CAPTOUCH_CTRL1_SAMP_OVF_TIME_SET(n)                     (((uint32_t)(n) << 20 ) & 0xFFF00000)
#define CAPTOUCH_CTRL1_SAMP_OVF_TIME_CLR                        0x000FFFFF

#define CAPTOUCH_CTRL1_TRAN_LOOP_SHIFT                          12
#define CAPTOUCH_CTRL1_TRAN_LOOP_MASK                           0x000FF000
#define CAPTOUCH_CTRL1_TRAN_LOOP_SET(n)                         (((uint32_t)(n) << 12 ) & 0x000FF000)
#define CAPTOUCH_CTRL1_TRAN_LOOP_CLR                            0xFFF00FFF

#define CAPTOUCH_CTRL1_SAMP_OVF_EN_SHIFT                        9
#define CAPTOUCH_CTRL1_SAMP_OVF_EN_MASK                         0x00000200
#define CAPTOUCH_CTRL1_SAMP_OVF_EN_SET(n)                       (((uint32_t)(n) << 9  ) & 0x00000200)
#define CAPTOUCH_CTRL1_SAMP_OVF_EN_CLR                          0xFFFFFDFF

#define CAPTOUCH_CTRL1_TW_TRIG_EN_SHIFT                         8
#define CAPTOUCH_CTRL1_TW_TRIG_EN_MASK                          0x00000100
#define CAPTOUCH_CTRL1_TW_TRIG_EN_SET(n)                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define CAPTOUCH_CTRL1_TW_TRIG_EN_CLR                           0xFFFFFEFF

#define CAPTOUCH_CTRL1_TRIG_ADC_EN_SHIFT                        7
#define CAPTOUCH_CTRL1_TRIG_ADC_EN_MASK                         0x00000080
#define CAPTOUCH_CTRL1_TRIG_ADC_EN_SET(n)                       (((uint32_t)(n) << 7  ) & 0x00000080)
#define CAPTOUCH_CTRL1_TRIG_ADC_EN_CLR                          0xFFFFFF7F

#define CAPTOUCH_CTRL1_DSTSW_DIS_SHIFT                          6
#define CAPTOUCH_CTRL1_DSTSW_DIS_MASK                           0x00000040
#define CAPTOUCH_CTRL1_DSTSW_DIS_SET(n)                         (((uint32_t)(n) << 6  ) & 0x00000040)
#define CAPTOUCH_CTRL1_DSTSW_DIS_CLR                            0xFFFFFFBF

#define CAPTOUCH_CTRL1_CMP_EN_SHIFT                             5
#define CAPTOUCH_CTRL1_CMP_EN_MASK                              0x00000020
#define CAPTOUCH_CTRL1_CMP_EN_SET(n)                            (((uint32_t)(n) << 5  ) & 0x00000020)
#define CAPTOUCH_CTRL1_CMP_EN_CLR                               0xFFFFFFDF

#define CAPTOUCH_CTRL1_SHLD_EN_SHIFT                            4
#define CAPTOUCH_CTRL1_SHLD_EN_MASK                             0x00000010
#define CAPTOUCH_CTRL1_SHLD_EN_SET(n)                           (((uint32_t)(n) << 4  ) & 0x00000010)
#define CAPTOUCH_CTRL1_SHLD_EN_CLR                              0xFFFFFFEF

#define CAPTOUCH_CTRL1_CREF_SEL_SHIFT                           3
#define CAPTOUCH_CTRL1_CREF_SEL_MASK                            0x00000008
#define CAPTOUCH_CTRL1_CREF_SEL_SET(n)                          (((uint32_t)(n) << 3  ) & 0x00000008)
#define CAPTOUCH_CTRL1_CREF_SEL_CLR                             0xFFFFFFF7

#define CAPTOUCH_CTRL1_CAPTOUCH_MODE_SHIFT                      1
#define CAPTOUCH_CTRL1_CAPTOUCH_MODE_MASK                       0x00000006
#define CAPTOUCH_CTRL1_CAPTOUCH_MODE_SET(n)                     (((uint32_t)(n) << 1  ) & 0x00000006)
#define CAPTOUCH_CTRL1_CAPTOUCH_MODE_CLR                        0xFFFFFFF9

#define CAPTOUCH_CTRL1_CAPTOUCH_EN_SHIFT                        0
#define CAPTOUCH_CTRL1_CAPTOUCH_EN_MASK                         0x00000001
#define CAPTOUCH_CTRL1_CAPTOUCH_EN_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define CAPTOUCH_CTRL1_CAPTOUCH_EN_CLR                          0xFFFFFFFE

#define CAPTOUCH_CTRL2_INIT_TIME_SHIFT                          16
#define CAPTOUCH_CTRL2_INIT_TIME_MASK                           0x0FFF0000
#define CAPTOUCH_CTRL2_INIT_TIME_SET(n)                         (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define CAPTOUCH_CTRL2_INIT_TIME_CLR                            0xF000FFFF

#define CAPTOUCH_CTRL2_TRAN_TIME_SHIFT                          8
#define CAPTOUCH_CTRL2_TRAN_TIME_MASK                           0x0000FF00
#define CAPTOUCH_CTRL2_TRAN_TIME_SET(n)                         (((uint32_t)(n) << 8  ) & 0x0000FF00)
#define CAPTOUCH_CTRL2_TRAN_TIME_CLR                            0xFFFF00FF

#define CAPTOUCH_CTRL2_CHG_TIME_SHIFT                           0
#define CAPTOUCH_CTRL2_CHG_TIME_MASK                            0x000000FF
#define CAPTOUCH_CTRL2_CHG_TIME_SET(n)                          (((uint32_t)(n) << 0  ) & 0x000000FF)
#define CAPTOUCH_CTRL2_CHG_TIME_CLR                             0xFFFFFF00

#define CAPTOUCH_CTRL3_IDAC_INP_SHIFT                           24
#define CAPTOUCH_CTRL3_IDAC_INP_MASK                            0xFF000000
#define CAPTOUCH_CTRL3_IDAC_INP_SET(n)                          (((uint32_t)(n) << 24 ) & 0xFF000000)
#define CAPTOUCH_CTRL3_IDAC_INP_CLR                             0x00FFFFFF

#define CAPTOUCH_CTRL3_IDAC_INN_SHIFT                           16
#define CAPTOUCH_CTRL3_IDAC_INN_MASK                            0x00FF0000
#define CAPTOUCH_CTRL3_IDAC_INN_SET(n)                          (((uint32_t)(n) << 16 ) & 0x00FF0000)
#define CAPTOUCH_CTRL3_IDAC_INN_CLR                             0xFF00FFFF

#define CAPTOUCH_CTRL3_IDAC_TIME_SHIFT                          8
#define CAPTOUCH_CTRL3_IDAC_TIME_MASK                           0x0000FF00
#define CAPTOUCH_CTRL3_IDAC_TIME_SET(n)                         (((uint32_t)(n) << 8  ) & 0x0000FF00)
#define CAPTOUCH_CTRL3_IDAC_TIME_CLR                            0xFFFF00FF

#define CAPTOUCH_CTRL3_SW_IDAC_SEL_P_SHIFT                      3
#define CAPTOUCH_CTRL3_SW_IDAC_SEL_P_MASK                       0x00000008
#define CAPTOUCH_CTRL3_SW_IDAC_SEL_P_SET(n)                     (((uint32_t)(n) << 3  ) & 0x00000008)
#define CAPTOUCH_CTRL3_SW_IDAC_SEL_P_CLR                        0xFFFFFFF7

#define CAPTOUCH_CTRL3_SW_IDAC_SEL_N_SHIFT                      2
#define CAPTOUCH_CTRL3_SW_IDAC_SEL_N_MASK                       0x00000004
#define CAPTOUCH_CTRL3_SW_IDAC_SEL_N_SET(n)                     (((uint32_t)(n) << 2  ) & 0x00000004)
#define CAPTOUCH_CTRL3_SW_IDAC_SEL_N_CLR                        0xFFFFFFFB

#define CAPTOUCH_CTRL3_SW_IDAC_MODE_SHIFT                       1
#define CAPTOUCH_CTRL3_SW_IDAC_MODE_MASK                        0x00000002
#define CAPTOUCH_CTRL3_SW_IDAC_MODE_SET(n)                      (((uint32_t)(n) << 1  ) & 0x00000002)
#define CAPTOUCH_CTRL3_SW_IDAC_MODE_CLR                         0xFFFFFFFD

#define CAPTOUCH_CTRL3_IDAC_EN_SHIFT                            0
#define CAPTOUCH_CTRL3_IDAC_EN_MASK                             0x00000001
#define CAPTOUCH_CTRL3_IDAC_EN_SET(n)                           (((uint32_t)(n) << 0  ) & 0x00000001)
#define CAPTOUCH_CTRL3_IDAC_EN_CLR                              0xFFFFFFFE

#define CAPTOUCH_CTRL4_HOP_PERIOD_SHIFT                         24
#define CAPTOUCH_CTRL4_HOP_PERIOD_MASK                          0x07000000
#define CAPTOUCH_CTRL4_HOP_PERIOD_SET(n)                        (((uint32_t)(n) << 24 ) & 0x07000000)
#define CAPTOUCH_CTRL4_HOP_PERIOD_CLR                           0xF8FFFFFF

#define CAPTOUCH_CTRL4_HOP_CNT_7_SHIFT                          21
#define CAPTOUCH_CTRL4_HOP_CNT_7_MASK                           0x00E00000
#define CAPTOUCH_CTRL4_HOP_CNT_7_SET(n)                         (((uint32_t)(n) << 21 ) & 0x00E00000)
#define CAPTOUCH_CTRL4_HOP_CNT_7_CLR                            0xFF1FFFFF

#define CAPTOUCH_CTRL4_HOP_CNT_6_SHIFT                          18
#define CAPTOUCH_CTRL4_HOP_CNT_6_MASK                           0x001C0000
#define CAPTOUCH_CTRL4_HOP_CNT_6_SET(n)                         (((uint32_t)(n) << 18 ) & 0x001C0000)
#define CAPTOUCH_CTRL4_HOP_CNT_6_CLR                            0xFFE3FFFF

#define CAPTOUCH_CTRL4_HOP_CNT_5_SHIFT                          15
#define CAPTOUCH_CTRL4_HOP_CNT_5_MASK                           0x00038000
#define CAPTOUCH_CTRL4_HOP_CNT_5_SET(n)                         (((uint32_t)(n) << 15 ) & 0x00038000)
#define CAPTOUCH_CTRL4_HOP_CNT_5_CLR                            0xFFFC7FFF

#define CAPTOUCH_CTRL4_HOP_CNT_4_SHIFT                          12
#define CAPTOUCH_CTRL4_HOP_CNT_4_MASK                           0x00007000
#define CAPTOUCH_CTRL4_HOP_CNT_4_SET(n)                         (((uint32_t)(n) << 12 ) & 0x00007000)
#define CAPTOUCH_CTRL4_HOP_CNT_4_CLR                            0xFFFF8FFF

#define CAPTOUCH_CTRL4_HOP_CNT_3_SHIFT                          9
#define CAPTOUCH_CTRL4_HOP_CNT_3_MASK                           0x00000E00
#define CAPTOUCH_CTRL4_HOP_CNT_3_SET(n)                         (((uint32_t)(n) << 9  ) & 0x00000E00)
#define CAPTOUCH_CTRL4_HOP_CNT_3_CLR                            0xFFFFF1FF

#define CAPTOUCH_CTRL4_HOP_CNT_2_SHIFT                          6
#define CAPTOUCH_CTRL4_HOP_CNT_2_MASK                           0x000001C0
#define CAPTOUCH_CTRL4_HOP_CNT_2_SET(n)                         (((uint32_t)(n) << 6  ) & 0x000001C0)
#define CAPTOUCH_CTRL4_HOP_CNT_2_CLR                            0xFFFFFE3F

#define CAPTOUCH_CTRL4_HOP_CNT_1_SHIFT                          3
#define CAPTOUCH_CTRL4_HOP_CNT_1_MASK                           0x00000038
#define CAPTOUCH_CTRL4_HOP_CNT_1_SET(n)                         (((uint32_t)(n) << 3  ) & 0x00000038)
#define CAPTOUCH_CTRL4_HOP_CNT_1_CLR                            0xFFFFFFC7

#define CAPTOUCH_CTRL4_HOP_CNT_0_SHIFT                          0
#define CAPTOUCH_CTRL4_HOP_CNT_0_MASK                           0x00000007
#define CAPTOUCH_CTRL4_HOP_CNT_0_SET(n)                         (((uint32_t)(n) << 0  ) & 0x00000007)
#define CAPTOUCH_CTRL4_HOP_CNT_0_CLR                            0xFFFFFFF8

#define CAPTOUCH_STATUS_IDAC_VLD_SHIFT                          4
#define CAPTOUCH_STATUS_IDAC_VLD_MASK                           0x00000010
#define CAPTOUCH_STATUS_IDAC_VLD_SET(n)                         (((uint32_t)(n) << 4  ) & 0x00000010)
#define CAPTOUCH_STATUS_IDAC_VLD_CLR                            0xFFFFFFEF

#define CAPTOUCH_STATUS_SHLD_VLD_SHIFT                          3
#define CAPTOUCH_STATUS_SHLD_VLD_MASK                           0x00000008
#define CAPTOUCH_STATUS_SHLD_VLD_SET(n)                         (((uint32_t)(n) << 3  ) & 0x00000008)
#define CAPTOUCH_STATUS_SHLD_VLD_CLR                            0xFFFFFFF7

#define CAPTOUCH_STATUS_CREF_VLD_SHIFT                          2
#define CAPTOUCH_STATUS_CREF_VLD_MASK                           0x00000004
#define CAPTOUCH_STATUS_CREF_VLD_SET(n)                         (((uint32_t)(n) << 2  ) & 0x00000004)
#define CAPTOUCH_STATUS_CREF_VLD_CLR                            0xFFFFFFFB

#define CAPTOUCH_STATUS_CHNL_VLD_SHIFT                          1
#define CAPTOUCH_STATUS_CHNL_VLD_MASK                           0x00000002
#define CAPTOUCH_STATUS_CHNL_VLD_SET(n)                         (((uint32_t)(n) << 1  ) & 0x00000002)
#define CAPTOUCH_STATUS_CHNL_VLD_CLR                            0xFFFFFFFD

#define CAPTOUCH_STATUS_CAPTOUCH_BUSY_SHIFT                     0
#define CAPTOUCH_STATUS_CAPTOUCH_BUSY_MASK                      0x00000001
#define CAPTOUCH_STATUS_CAPTOUCH_BUSY_SET(n)                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define CAPTOUCH_STATUS_CAPTOUCH_BUSY_CLR                       0xFFFFFFFE

#define CAPTOUCH_CTRL5_SW_CHNL_MODE_SHIFT                       2
#define CAPTOUCH_CTRL5_SW_CHNL_MODE_MASK                        0x0000007C
#define CAPTOUCH_CTRL5_SW_CHNL_MODE_SET(n)                      (((uint32_t)(n) << 2  ) & 0x0000007C)
#define CAPTOUCH_CTRL5_SW_CHNL_MODE_CLR                         0xFFFFFF83

#define CAPTOUCH_CTRL5_SW_SHLD_MODE_SHIFT                       1
#define CAPTOUCH_CTRL5_SW_SHLD_MODE_MASK                        0x00000002
#define CAPTOUCH_CTRL5_SW_SHLD_MODE_SET(n)                      (((uint32_t)(n) << 1  ) & 0x00000002)
#define CAPTOUCH_CTRL5_SW_SHLD_MODE_CLR                         0xFFFFFFFD

#define CAPTOUCH_CTRL5_SW_CREF_MODE_SHIFT                       0
#define CAPTOUCH_CTRL5_SW_CREF_MODE_MASK                        0x00000001
#define CAPTOUCH_CTRL5_SW_CREF_MODE_SET(n)                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define CAPTOUCH_CTRL5_SW_CREF_MODE_CLR                         0xFFFFFFFE

#define CAPTOUCH_CTRL6_SW_CHNL_SHLD_SHIFT                       23
#define CAPTOUCH_CTRL6_SW_CHNL_SHLD_MASK                        0x0F800000
#define CAPTOUCH_CTRL6_SW_CHNL_SHLD_SET(n)                      (((uint32_t)(n) << 23 ) & 0x0F800000)
#define CAPTOUCH_CTRL6_SW_CHNL_SHLD_CLR                         0xF07FFFFF

#define CAPTOUCH_CTRL6_SW_CHNL_TRAN_SHIFT                       18
#define CAPTOUCH_CTRL6_SW_CHNL_TRAN_MASK                        0x007C0000
#define CAPTOUCH_CTRL6_SW_CHNL_TRAN_SET(n)                      (((uint32_t)(n) << 18 ) & 0x007C0000)
#define CAPTOUCH_CTRL6_SW_CHNL_TRAN_CLR                         0xFF83FFFF

#define CAPTOUCH_CTRL6_SW_CHNL_DSG_SHIFT                        13
#define CAPTOUCH_CTRL6_SW_CHNL_DSG_MASK                         0x0003E000
#define CAPTOUCH_CTRL6_SW_CHNL_DSG_SET(n)                       (((uint32_t)(n) << 13 ) & 0x0003E000)
#define CAPTOUCH_CTRL6_SW_CHNL_DSG_CLR                          0xFFFC1FFF

#define CAPTOUCH_CTRL6_SW_CHNL_CHG_SHIFT                        8
#define CAPTOUCH_CTRL6_SW_CHNL_CHG_MASK                         0x00001F00
#define CAPTOUCH_CTRL6_SW_CHNL_CHG_SET(n)                       (((uint32_t)(n) << 8  ) & 0x00001F00)
#define CAPTOUCH_CTRL6_SW_CHNL_CHG_CLR                          0xFFFFE0FF

#define CAPTOUCH_CTRL6_SW_SHLD_SHLD_SHIFT                       7
#define CAPTOUCH_CTRL6_SW_SHLD_SHLD_MASK                        0x00000080
#define CAPTOUCH_CTRL6_SW_SHLD_SHLD_SET(n)                      (((uint32_t)(n) << 7  ) & 0x00000080)
#define CAPTOUCH_CTRL6_SW_SHLD_SHLD_CLR                         0xFFFFFF7F

#define CAPTOUCH_CTRL6_SW_SHLD_DSG_SHIFT                        5
#define CAPTOUCH_CTRL6_SW_SHLD_DSG_MASK                         0x00000020
#define CAPTOUCH_CTRL6_SW_SHLD_DSG_SET(n)                       (((uint32_t)(n) << 5  ) & 0x00000020)
#define CAPTOUCH_CTRL6_SW_SHLD_DSG_CLR                          0xFFFFFFDF

#define CAPTOUCH_CTRL6_SW_SHLD_CHG_SHIFT                        4
#define CAPTOUCH_CTRL6_SW_SHLD_CHG_MASK                         0x00000010
#define CAPTOUCH_CTRL6_SW_SHLD_CHG_SET(n)                       (((uint32_t)(n) << 4  ) & 0x00000010)
#define CAPTOUCH_CTRL6_SW_SHLD_CHG_CLR                          0xFFFFFFEF

#define CAPTOUCH_CTRL6_SW_CREF_SHLD_SHIFT                       3
#define CAPTOUCH_CTRL6_SW_CREF_SHLD_MASK                        0x00000008
#define CAPTOUCH_CTRL6_SW_CREF_SHLD_SET(n)                      (((uint32_t)(n) << 3  ) & 0x00000008)
#define CAPTOUCH_CTRL6_SW_CREF_SHLD_CLR                         0xFFFFFFF7

#define CAPTOUCH_CTRL6_SW_CREF_TRAN_SHIFT                       2
#define CAPTOUCH_CTRL6_SW_CREF_TRAN_MASK                        0x00000004
#define CAPTOUCH_CTRL6_SW_CREF_TRAN_SET(n)                      (((uint32_t)(n) << 2  ) & 0x00000004)
#define CAPTOUCH_CTRL6_SW_CREF_TRAN_CLR                         0xFFFFFFFB

#define CAPTOUCH_CTRL6_SW_CREF_DSG_SHIFT                        1
#define CAPTOUCH_CTRL6_SW_CREF_DSG_MASK                         0x00000002
#define CAPTOUCH_CTRL6_SW_CREF_DSG_SET(n)                       (((uint32_t)(n) << 1  ) & 0x00000002)
#define CAPTOUCH_CTRL6_SW_CREF_DSG_CLR                          0xFFFFFFFD

#define CAPTOUCH_CTRL6_SW_CREF_CHG_SHIFT                        0
#define CAPTOUCH_CTRL6_SW_CREF_CHG_MASK                         0x00000001
#define CAPTOUCH_CTRL6_SW_CREF_CHG_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define CAPTOUCH_CTRL6_SW_CREF_CHG_CLR                          0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t IMR             : 4  ; // 3  : 0
    __IO uint32_t RESERVED0       : 28 ; // 31 : 4
} CAPTOUCH_IMR_FIELD_T;

typedef struct
{
    __IO uint32_t ICR             : 4  ; // 3  : 0
    __IO uint32_t RESERVED0       : 28 ; // 31 : 4
} CAPTOUCH_ICR_FIELD_T;

typedef struct
{
    __IO uint32_t ISR             : 4  ; // 3  : 0
    __IO uint32_t RESERVED0       : 28 ; // 31 : 4
} CAPTOUCH_ISR_FIELD_T;

typedef struct
{
    __IO uint32_t IRSR            : 4  ; // 3  : 0
    __IO uint32_t RESERVED0       : 28 ; // 31 : 4
} CAPTOUCH_IRSR_FIELD_T;

typedef struct
{
    __IO uint32_t SW_TRIG         : 1  ; // 0  : 0
    __IO uint32_t RESERVED4       : 3  ; // 3  : 1
    __IO uint32_t CHNL_SEL        : 3  ; // 6  : 4
    __IO uint32_t RESERVED3       : 1  ; // 7  : 7
    __IO uint32_t SHLD_SEL        : 3  ; // 10 : 8
    __IO uint32_t RESERVED2       : 1  ; // 11 : 11
    __IO uint32_t SHLD_I          : 3  ; // 14 : 12
    __IO uint32_t RESERVED1       : 1  ; // 15 : 15
    __IO uint32_t CAL_SEL         : 2  ; // 17 : 16
    __IO uint32_t RESERVED0       : 14 ; // 31 : 18
} CAPTOUCH_CTRL0_FIELD_T;

typedef struct
{
    __IO uint32_t CAPTOUCH_EN     : 1  ; // 0  : 0
    __IO uint32_t CAPTOUCH_MODE   : 2  ; // 2  : 1
    __IO uint32_t CREF_SEL        : 1  ; // 3  : 3
    __IO uint32_t SHLD_EN         : 1  ; // 4  : 4
    __IO uint32_t CMP_EN          : 1  ; // 5  : 5
    __IO uint32_t DSTSW_DIS       : 1  ; // 6  : 6
    __IO uint32_t TRIG_ADC_EN     : 1  ; // 7  : 7
    __IO uint32_t TW_TRIG_EN      : 1  ; // 8  : 8
    __IO uint32_t SAMP_OVF_EN     : 1  ; // 9  : 9
    __IO uint32_t RESERVED0       : 2  ; // 11 : 10
    __IO uint32_t TRAN_LOOP       : 8  ; // 19 : 12
    __IO uint32_t SAMP_OVF_TIME   : 12 ; // 31 : 20
} CAPTOUCH_CTRL1_FIELD_T;

typedef struct
{
    __IO uint32_t CHG_TIME        : 8  ; // 7  : 0
    __IO uint32_t TRAN_TIME       : 8  ; // 15 : 8
    __IO uint32_t INIT_TIME       : 12 ; // 27 : 16
    __IO uint32_t RESERVED0       : 4  ; // 31 : 28
} CAPTOUCH_CTRL2_FIELD_T;

typedef struct
{
    __IO uint32_t IDAC_EN         : 1  ; // 0  : 0
    __IO uint32_t SW_IDAC_MODE    : 1  ; // 1  : 1
    __IO uint32_t SW_IDAC_SEL_N   : 1  ; // 2  : 2
    __IO uint32_t SW_IDAC_SEL_P   : 1  ; // 3  : 3
    __IO uint32_t RESERVED0       : 4  ; // 7  : 4
    __IO uint32_t IDAC_TIME       : 8  ; // 15 : 8
    __IO uint32_t IDAC_INN        : 8  ; // 23 : 16
    __IO uint32_t IDAC_INP        : 8  ; // 31 : 24
} CAPTOUCH_CTRL3_FIELD_T;

typedef struct
{
    __IO uint32_t HOP_CNT_0       : 3  ; // 2  : 0
    __IO uint32_t HOP_CNT_1       : 3  ; // 5  : 3
    __IO uint32_t HOP_CNT_2       : 3  ; // 8  : 6
    __IO uint32_t HOP_CNT_3       : 3  ; // 11 : 9
    __IO uint32_t HOP_CNT_4       : 3  ; // 14 : 12
    __IO uint32_t HOP_CNT_5       : 3  ; // 17 : 15
    __IO uint32_t HOP_CNT_6       : 3  ; // 20 : 18
    __IO uint32_t HOP_CNT_7       : 3  ; // 23 : 21
    __IO uint32_t HOP_PERIOD      : 3  ; // 26 : 24
    __IO uint32_t RESERVED0       : 5  ; // 31 : 27
} CAPTOUCH_CTRL4_FIELD_T;

typedef struct
{
    __IO uint32_t CAPTOUCH_BUSY   : 1  ; // 0  : 0
    __IO uint32_t CHNL_VLD        : 1  ; // 1  : 1
    __IO uint32_t CREF_VLD        : 1  ; // 2  : 2
    __IO uint32_t SHLD_VLD        : 1  ; // 3  : 3
    __IO uint32_t IDAC_VLD        : 1  ; // 4  : 4
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} CAPTOUCH_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t SW_CREF_MODE    : 1  ; // 0  : 0
    __IO uint32_t SW_SHLD_MODE    : 1  ; // 1  : 1
    __IO uint32_t SW_CHNL_MODE    : 5  ; // 6  : 2
    __IO uint32_t RESERVED0       : 25 ; // 31 : 7
} CAPTOUCH_CTRL5_FIELD_T;

typedef struct
{
    __IO uint32_t SW_CREF_CHG     : 1  ; // 0  : 0
    __IO uint32_t SW_CREF_DSG     : 1  ; // 1  : 1
    __IO uint32_t SW_CREF_TRAN    : 1  ; // 2  : 2
    __IO uint32_t SW_CREF_SHLD    : 1  ; // 3  : 3
    __IO uint32_t SW_SHLD_CHG     : 1  ; // 4  : 4
    __IO uint32_t SW_SHLD_DSG     : 1  ; // 5  : 5
    __IO uint32_t RESERVED1       : 1  ; // 6  : 6
    __IO uint32_t SW_SHLD_SHLD    : 1  ; // 7  : 7
    __IO uint32_t SW_CHNL_CHG     : 5  ; // 12 : 8
    __IO uint32_t SW_CHNL_DSG     : 5  ; // 17 : 13
    __IO uint32_t SW_CHNL_TRAN    : 5  ; // 22 : 18
    __IO uint32_t SW_CHNL_SHLD    : 5  ; // 27 : 23
    __IO uint32_t RESERVED0       : 4  ; // 31 : 28
} CAPTOUCH_CTRL6_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t IMR             ; // 0x0000
        CAPTOUCH_IMR_FIELD_T IMR_F     ;
    };

    union
    {
        __IO  uint32_t ICR             ; // 0x0004
        CAPTOUCH_ICR_FIELD_T ICR_F     ;
    };

    union
    {
        __IO  uint32_t ISR             ; // 0x0008
        CAPTOUCH_ISR_FIELD_T ISR_F     ;
    };

    union
    {
        __IO  uint32_t IRSR            ; // 0x000C
        CAPTOUCH_IRSR_FIELD_T IRSR_F   ;
    };

    union
    {
        __IO  uint32_t CTRL0           ; // 0x0010
        CAPTOUCH_CTRL0_FIELD_T CTRL0_F ;
    };

    union
    {
        __IO  uint32_t CTRL1           ; // 0x0014
        CAPTOUCH_CTRL1_FIELD_T CTRL1_F ;
    };

    union
    {
        __IO  uint32_t CTRL2           ; // 0x0018
        CAPTOUCH_CTRL2_FIELD_T CTRL2_F ;
    };

    union
    {
        __IO  uint32_t CTRL3           ; // 0x001C
        CAPTOUCH_CTRL3_FIELD_T CTRL3_F ;
    };

    union
    {
        __IO  uint32_t CTRL4           ; // 0x0020
        CAPTOUCH_CTRL4_FIELD_T CTRL4_F ;
    };

    union
    {
        __IO  uint32_t STATUS          ; // 0x0024
        CAPTOUCH_STATUS_FIELD_T STATUS_F;
    };

    union
    {
        __IO  uint32_t CTRL5           ; // 0x0028
        CAPTOUCH_CTRL5_FIELD_T CTRL5_F ;
    };

    union
    {
        __IO  uint32_t CTRL6           ; // 0x002C
        CAPTOUCH_CTRL6_FIELD_T CTRL6_F ;
    };

} CAPTOUCH_REG_TypeDef;

#endif
