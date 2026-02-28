/**
 *****************************************************************************
 * @brief   adc_reg_def header file.
 *
 * @file    adc_reg_def.h
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

#ifndef   ADC_DEF_H__
#define   ADC_DEF_H__

// Register Offset Macro Definition
#define ADC_FIFO_DATA_OFFSET                                    0x0000
#define ADC_FIFO_STATE_OFFSET                                   0x0004
#define ADC_CTRL0_OFFSET                                        0x0008
#define ADC_CTRL1_OFFSET                                        0x000C
#define ADC_CTRL2_OFFSET                                        0x0010
#define ADC_CTRL3_OFFSET                                        0x0014
#define ADC_CTRL4_OFFSET                                        0x0018
#define ADC_ADC_OUT_OFFSET                                      0x001C
#define ADC_CHNL_STATUS_OFFSET                                  0x0020
#define ADC_CTRL_GAIN_0_OFFSET                                  0x0024
#define ADC_CTRL_GAIN_1_OFFSET                                  0x0028
#define ADC_CTRL_GAIN_2_OFFSET                                  0x002C
#define ADC_CTRL_GAIN_3_OFFSET                                  0x0030
#define ADC_CTRL_ANA_OFFSET                                     0x0034
#define ADC_CTRL_CAL_0_OFFSET                                   0x0038
#define ADC_CTRL_CAL_1_OFFSET                                   0x003C
#define ADC_CTRL_CAL_2_OFFSET                                   0x0040
#define ADC_CTRL_CAL_3_OFFSET                                   0x0044
#define ADC_CTRL_CAL_4_OFFSET                                   0x0048
#define ADC_CTRL_CAL_5_OFFSET                                   0x004C
#define ADC_CTRL_CAL_6_OFFSET                                   0x0050
#define ADC_CTRL_CAL_7_OFFSET                                   0x0054
#define ADC_CTRL_CAL_8_OFFSET                                   0x0058
#define ADC_CTRL_CAL_9_OFFSET                                   0x005C
#define ADC_CTRL_CAL_10_OFFSET                                  0x0060
#define ADC_CTRL_CAL_11_OFFSET                                  0x0064
#define ADC_TRIM_ADSAR_VALUE0_OFFSET                            0x0080
#define ADC_TRIM_ADSAR_VALUE1_OFFSET                            0x0084
#define ADC_TRIM_ADSAR_VALUE2_OFFSET                            0x0088
#define ADC_TRIM_ADSAR_VALUE3_OFFSET                            0x008C
#define ADC_TRIM_ADSAR_VALUE4_OFFSET                            0x0090
#define ADC_TRIM_ADSAR_VALUE5_OFFSET                            0x0094
#define ADC_TRIM_ADSAR_VALUE6_OFFSET                            0x0098
#define ADC_TRIM_ADSAR_VALUE7_OFFSET                            0x009C
#define ADC_TRIM_ADSAR_VALUE8_OFFSET                            0x00A0

// Register Address Macro Definition
#define ADC_FIFO_DATA_ADDR                                      ( ADC_BASE_ADDR + ADC_FIFO_DATA_OFFSET)
#define ADC_FIFO_STATE_ADDR                                     ( ADC_BASE_ADDR + ADC_FIFO_STATE_OFFSET)
#define ADC_CTRL0_ADDR                                          ( ADC_BASE_ADDR + ADC_CTRL0_OFFSET)
#define ADC_CTRL1_ADDR                                          ( ADC_BASE_ADDR + ADC_CTRL1_OFFSET)
#define ADC_CTRL2_ADDR                                          ( ADC_BASE_ADDR + ADC_CTRL2_OFFSET)
#define ADC_CTRL3_ADDR                                          ( ADC_BASE_ADDR + ADC_CTRL3_OFFSET)
#define ADC_CTRL4_ADDR                                          ( ADC_BASE_ADDR + ADC_CTRL4_OFFSET)
#define ADC_ADC_OUT_ADDR                                        ( ADC_BASE_ADDR + ADC_ADC_OUT_OFFSET)
#define ADC_CHNL_STATUS_ADDR                                    ( ADC_BASE_ADDR + ADC_CHNL_STATUS_OFFSET)
#define ADC_CTRL_GAIN_0_ADDR                                    ( ADC_BASE_ADDR + ADC_CTRL_GAIN_0_OFFSET)
#define ADC_CTRL_GAIN_1_ADDR                                    ( ADC_BASE_ADDR + ADC_CTRL_GAIN_1_OFFSET)
#define ADC_CTRL_GAIN_2_ADDR                                    ( ADC_BASE_ADDR + ADC_CTRL_GAIN_2_OFFSET)
#define ADC_CTRL_GAIN_3_ADDR                                    ( ADC_BASE_ADDR + ADC_CTRL_GAIN_3_OFFSET)
#define ADC_CTRL_ANA_ADDR                                       ( ADC_BASE_ADDR + ADC_CTRL_ANA_OFFSET)
#define ADC_CTRL_CAL_0_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_0_OFFSET)
#define ADC_CTRL_CAL_1_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_1_OFFSET)
#define ADC_CTRL_CAL_2_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_2_OFFSET)
#define ADC_CTRL_CAL_3_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_3_OFFSET)
#define ADC_CTRL_CAL_4_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_4_OFFSET)
#define ADC_CTRL_CAL_5_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_5_OFFSET)
#define ADC_CTRL_CAL_6_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_6_OFFSET)
#define ADC_CTRL_CAL_7_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_7_OFFSET)
#define ADC_CTRL_CAL_8_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_8_OFFSET)
#define ADC_CTRL_CAL_9_ADDR                                     ( ADC_BASE_ADDR + ADC_CTRL_CAL_9_OFFSET)
#define ADC_CTRL_CAL_10_ADDR                                    ( ADC_BASE_ADDR + ADC_CTRL_CAL_10_OFFSET)
#define ADC_CTRL_CAL_11_ADDR                                    ( ADC_BASE_ADDR + ADC_CTRL_CAL_11_OFFSET)
#define ADC_TRIM_ADSAR_VALUE0_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE0_OFFSET)
#define ADC_TRIM_ADSAR_VALUE1_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE1_OFFSET)
#define ADC_TRIM_ADSAR_VALUE2_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE2_OFFSET)
#define ADC_TRIM_ADSAR_VALUE3_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE3_OFFSET)
#define ADC_TRIM_ADSAR_VALUE4_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE4_OFFSET)
#define ADC_TRIM_ADSAR_VALUE5_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE5_OFFSET)
#define ADC_TRIM_ADSAR_VALUE6_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE6_OFFSET)
#define ADC_TRIM_ADSAR_VALUE7_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE7_OFFSET)
#define ADC_TRIM_ADSAR_VALUE8_ADDR                              ( ADC_BASE_ADDR + ADC_TRIM_ADSAR_VALUE8_OFFSET)

// Register Field Macro Definition
#define ADC_FIFO_DATA_FIFO_RDATA_SHIFT                                  0
#define ADC_FIFO_DATA_FIFO_RDATA_MASK                                   0xFFFFFFFF
#define ADC_FIFO_DATA_FIFO_RDATA_SET(n)                                 (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define ADC_FIFO_DATA_FIFO_RDATA_CLR                                    0x00000000

#define ADC_FIFO_STATE_ENTRY_VALID_SHIFT                                0
#define ADC_FIFO_STATE_ENTRY_VALID_MASK                                 0x0000000F
#define ADC_FIFO_STATE_ENTRY_VALID_SET(n)                               (((uint32_t)(n) << 0  ) & 0x0000000F)
#define ADC_FIFO_STATE_ENTRY_VALID_CLR                                  0xFFFFFFF0

#define ADC_CTRL0_TRIG_EN_SHIFT                                         16
#define ADC_CTRL0_TRIG_EN_MASK                                          0x00FF0000
#define ADC_CTRL0_TRIG_EN_SET(n)                                        (((uint32_t)(n) << 16 ) & 0x00FF0000)
#define ADC_CTRL0_TRIG_EN_CLR                                           0xFF00FFFF

#define ADC_CTRL0_FIFO_FORMAT_SHIFT                                     15
#define ADC_CTRL0_FIFO_FORMAT_MASK                                      0x00008000
#define ADC_CTRL0_FIFO_FORMAT_SET(n)                                    (((uint32_t)(n) << 15 ) & 0x00008000)
#define ADC_CTRL0_FIFO_FORMAT_CLR                                       0xFFFF7FFF

#define ADC_CTRL0_FIFO_THRHLD_SHIFT                                     12
#define ADC_CTRL0_FIFO_THRHLD_MASK                                      0x00007000
#define ADC_CTRL0_FIFO_THRHLD_SET(n)                                    (((uint32_t)(n) << 12 ) & 0x00007000)
#define ADC_CTRL0_FIFO_THRHLD_CLR                                       0xFFFF8FFF

#define ADC_CTRL0_IRQ_MODE_SHIFT                                        8
#define ADC_CTRL0_IRQ_MODE_MASK                                         0x00000700
#define ADC_CTRL0_IRQ_MODE_SET(n)                                       (((uint32_t)(n) << 8  ) & 0x00000700)
#define ADC_CTRL0_IRQ_MODE_CLR                                          0xFFFFF8FF

#define ADC_CTRL0_AUTO_ADC_EN_SHIFT                                     2
#define ADC_CTRL0_AUTO_ADC_EN_MASK                                      0x00000004
#define ADC_CTRL0_AUTO_ADC_EN_SET(n)                                    (((uint32_t)(n) << 2  ) & 0x00000004)
#define ADC_CTRL0_AUTO_ADC_EN_CLR                                       0xFFFFFFFB

#define ADC_CTRL0_SW_ADC_EN_SHIFT                                       1
#define ADC_CTRL0_SW_ADC_EN_MASK                                        0x00000002
#define ADC_CTRL0_SW_ADC_EN_SET(n)                                      (((uint32_t)(n) << 1  ) & 0x00000002)
#define ADC_CTRL0_SW_ADC_EN_CLR                                         0xFFFFFFFD

#define ADC_CTRL0_SW_START_SHIFT                                        0
#define ADC_CTRL0_SW_START_MASK                                         0x00000001
#define ADC_CTRL0_SW_START_SET(n)                                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define ADC_CTRL0_SW_START_CLR                                          0xFFFFFFFE

#define ADC_CTRL1_TRIG_NUM_SHIFT                                        16
#define ADC_CTRL1_TRIG_NUM_MASK                                         0xFFFF0000
#define ADC_CTRL1_TRIG_NUM_SET(n)                                       (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define ADC_CTRL1_TRIG_NUM_CLR                                          0x0000FFFF

#define ADC_CTRL1_SCAN_CHNL_NUM_SHIFT                                   8
#define ADC_CTRL1_SCAN_CHNL_NUM_MASK                                    0x00000700
#define ADC_CTRL1_SCAN_CHNL_NUM_SET(n)                                  (((uint32_t)(n) << 8  ) & 0x00000700)
#define ADC_CTRL1_SCAN_CHNL_NUM_CLR                                     0xFFFFF8FF

#define ADC_CTRL1_CHNL_AVG_EN_SHIFT                                     7
#define ADC_CTRL1_CHNL_AVG_EN_MASK                                      0x00000080
#define ADC_CTRL1_CHNL_AVG_EN_SET(n)                                    (((uint32_t)(n) << 7  ) & 0x00000080)
#define ADC_CTRL1_CHNL_AVG_EN_CLR                                       0xFFFFFF7F

#define ADC_CTRL1_CHNL_SAMP_NUM_SHIFT                                   4
#define ADC_CTRL1_CHNL_SAMP_NUM_MASK                                    0x00000070
#define ADC_CTRL1_CHNL_SAMP_NUM_SET(n)                                  (((uint32_t)(n) << 4  ) & 0x00000070)
#define ADC_CTRL1_CHNL_SAMP_NUM_CLR                                     0xFFFFFF8F

#define ADC_CTRL1_ADC_IN_SEL_SHIFT                                      0
#define ADC_CTRL1_ADC_IN_SEL_MASK                                       0x0000000F
#define ADC_CTRL1_ADC_IN_SEL_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x0000000F)
#define ADC_CTRL1_ADC_IN_SEL_CLR                                        0xFFFFFFF0

#define ADC_CTRL2_SAMP_PRE_CYCLE_SHIFT                                  29
#define ADC_CTRL2_SAMP_PRE_CYCLE_MASK                                   0xE0000000
#define ADC_CTRL2_SAMP_PRE_CYCLE_SET(n)                                 (((uint32_t)(n) << 29 ) & 0xE0000000)
#define ADC_CTRL2_SAMP_PRE_CYCLE_CLR                                    0x1FFFFFFF

#define ADC_CTRL2_SAMP_CYCLE_SHIFT                                      22
#define ADC_CTRL2_SAMP_CYCLE_MASK                                       0x1FC00000
#define ADC_CTRL2_SAMP_CYCLE_SET(n)                                     (((uint32_t)(n) << 22 ) & 0x1FC00000)
#define ADC_CTRL2_SAMP_CYCLE_CLR                                        0xE03FFFFF

#define ADC_CTRL2_SAMP_DLY_CYCLE_SHIFT                                  18
#define ADC_CTRL2_SAMP_DLY_CYCLE_MASK                                   0x003C0000
#define ADC_CTRL2_SAMP_DLY_CYCLE_SET(n)                                 (((uint32_t)(n) << 18 ) & 0x003C0000)
#define ADC_CTRL2_SAMP_DLY_CYCLE_CLR                                    0xFFC3FFFF

#define ADC_CTRL2_CHNL_INIT_CYCLE_SHIFT                                 10
#define ADC_CTRL2_CHNL_INIT_CYCLE_MASK                                  0x0001FC00
#define ADC_CTRL2_CHNL_INIT_CYCLE_SET(n)                                (((uint32_t)(n) << 10 ) & 0x0001FC00)
#define ADC_CTRL2_CHNL_INIT_CYCLE_CLR                                   0xFFFE03FF

#define ADC_CTRL2_INIT_CYCLE_SHIFT                                      0
#define ADC_CTRL2_INIT_CYCLE_MASK                                       0x000003FF
#define ADC_CTRL2_INIT_CYCLE_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x000003FF)
#define ADC_CTRL2_INIT_CYCLE_CLR                                        0xFFFFFC00

#define ADC_CTRL3_SCAN_CHNL_7_SHIFT                                     28
#define ADC_CTRL3_SCAN_CHNL_7_MASK                                      0xF0000000
#define ADC_CTRL3_SCAN_CHNL_7_SET(n)                                    (((uint32_t)(n) << 28 ) & 0xF0000000)
#define ADC_CTRL3_SCAN_CHNL_7_CLR                                       0x0FFFFFFF

#define ADC_CTRL3_SCAN_CHNL_6_SHIFT                                     24
#define ADC_CTRL3_SCAN_CHNL_6_MASK                                      0x0F000000
#define ADC_CTRL3_SCAN_CHNL_6_SET(n)                                    (((uint32_t)(n) << 24 ) & 0x0F000000)
#define ADC_CTRL3_SCAN_CHNL_6_CLR                                       0xF0FFFFFF

#define ADC_CTRL3_SCAN_CHNL_5_SHIFT                                     20
#define ADC_CTRL3_SCAN_CHNL_5_MASK                                      0x00F00000
#define ADC_CTRL3_SCAN_CHNL_5_SET(n)                                    (((uint32_t)(n) << 20 ) & 0x00F00000)
#define ADC_CTRL3_SCAN_CHNL_5_CLR                                       0xFF0FFFFF

#define ADC_CTRL3_SCAN_CHNL_4_SHIFT                                     16
#define ADC_CTRL3_SCAN_CHNL_4_MASK                                      0x000F0000
#define ADC_CTRL3_SCAN_CHNL_4_SET(n)                                    (((uint32_t)(n) << 16 ) & 0x000F0000)
#define ADC_CTRL3_SCAN_CHNL_4_CLR                                       0xFFF0FFFF

#define ADC_CTRL3_SCAN_CHNL_3_SHIFT                                     12
#define ADC_CTRL3_SCAN_CHNL_3_MASK                                      0x0000F000
#define ADC_CTRL3_SCAN_CHNL_3_SET(n)                                    (((uint32_t)(n) << 12 ) & 0x0000F000)
#define ADC_CTRL3_SCAN_CHNL_3_CLR                                       0xFFFF0FFF

#define ADC_CTRL3_SCAN_CHNL_2_SHIFT                                     8
#define ADC_CTRL3_SCAN_CHNL_2_MASK                                      0x00000F00
#define ADC_CTRL3_SCAN_CHNL_2_SET(n)                                    (((uint32_t)(n) << 8  ) & 0x00000F00)
#define ADC_CTRL3_SCAN_CHNL_2_CLR                                       0xFFFFF0FF

#define ADC_CTRL3_SCAN_CHNL_1_SHIFT                                     4
#define ADC_CTRL3_SCAN_CHNL_1_MASK                                      0x000000F0
#define ADC_CTRL3_SCAN_CHNL_1_SET(n)                                    (((uint32_t)(n) << 4  ) & 0x000000F0)
#define ADC_CTRL3_SCAN_CHNL_1_CLR                                       0xFFFFFF0F

#define ADC_CTRL3_SCAN_CHNL_0_SHIFT                                     0
#define ADC_CTRL3_SCAN_CHNL_0_MASK                                      0x0000000F
#define ADC_CTRL3_SCAN_CHNL_0_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x0000000F)
#define ADC_CTRL3_SCAN_CHNL_0_CLR                                       0xFFFFFFF0

#define ADC_CTRL4_CMP_CEILING_SHIFT                                     16
#define ADC_CTRL4_CMP_CEILING_MASK                                      0x07FF0000
#define ADC_CTRL4_CMP_CEILING_SET(n)                                    (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL4_CMP_CEILING_CLR                                       0xF800FFFF

#define ADC_CTRL4_CMP_BOTTOM_SHIFT                                      0
#define ADC_CTRL4_CMP_BOTTOM_MASK                                       0x000007FF
#define ADC_CTRL4_CMP_BOTTOM_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x000007FF)
#define ADC_CTRL4_CMP_BOTTOM_CLR                                        0xFFFFF800

#define ADC_ADC_OUT_RAW_OUT17_SHIFT                                     15
#define ADC_ADC_OUT_RAW_OUT17_MASK                                      0xFFFF8000
#define ADC_ADC_OUT_RAW_OUT17_SET(n)                                    (((uint32_t)(n) << 15 ) & 0xFFFF8000)
#define ADC_ADC_OUT_RAW_OUT17_CLR                                       0x00007FFF

#define ADC_ADC_OUT_ADC_READY_ERR_SHIFT                                 12
#define ADC_ADC_OUT_ADC_READY_ERR_MASK                                  0x00001000
#define ADC_ADC_OUT_ADC_READY_ERR_SET(n)                                (((uint32_t)(n) << 12 ) & 0x00001000)
#define ADC_ADC_OUT_ADC_READY_ERR_CLR                                   0xFFFFEFFF

#define ADC_ADC_OUT_PWM_STATUS_SHIFT                                    11
#define ADC_ADC_OUT_PWM_STATUS_MASK                                     0x00000800
#define ADC_ADC_OUT_PWM_STATUS_SET(n)                                   (((uint32_t)(n) << 11 ) & 0x00000800)
#define ADC_ADC_OUT_PWM_STATUS_CLR                                      0xFFFFF7FF

#define ADC_ADC_OUT_ADC_OUT_SHIFT                                       0
#define ADC_ADC_OUT_ADC_OUT_MASK                                        0x000007FF
#define ADC_ADC_OUT_ADC_OUT_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x000007FF)
#define ADC_ADC_OUT_ADC_OUT_CLR                                         0xFFFFF800

#define ADC_CHNL_STATUS_IRQ_COMP_STATUS_SHIFT                           0
#define ADC_CHNL_STATUS_IRQ_COMP_STATUS_MASK                            0x003FFFFF
#define ADC_CHNL_STATUS_IRQ_COMP_STATUS_SET(n)                          (((uint32_t)(n) << 0  ) & 0x003FFFFF)
#define ADC_CHNL_STATUS_IRQ_COMP_STATUS_CLR                             0xFFC00000

#define ADC_CTRL_GAIN_0_OP_SEL_1_SHIFT                                  27
#define ADC_CTRL_GAIN_0_OP_SEL_1_MASK                                   0x08000000
#define ADC_CTRL_GAIN_0_OP_SEL_1_SET(n)                                 (((uint32_t)(n) << 27 ) & 0x08000000)
#define ADC_CTRL_GAIN_0_OP_SEL_1_CLR                                    0xF7FFFFFF

#define ADC_CTRL_GAIN_0_VCA_SEL_1_SHIFT                                 26
#define ADC_CTRL_GAIN_0_VCA_SEL_1_MASK                                  0x04000000
#define ADC_CTRL_GAIN_0_VCA_SEL_1_SET(n)                                (((uint32_t)(n) << 26 ) & 0x04000000)
#define ADC_CTRL_GAIN_0_VCA_SEL_1_CLR                                   0xFBFFFFFF

#define ADC_CTRL_GAIN_0_VCR_SEL_1_SHIFT                                 22
#define ADC_CTRL_GAIN_0_VCR_SEL_1_MASK                                  0x03C00000
#define ADC_CTRL_GAIN_0_VCR_SEL_1_SET(n)                                (((uint32_t)(n) << 22 ) & 0x03C00000)
#define ADC_CTRL_GAIN_0_VCR_SEL_1_CLR                                   0xFC3FFFFF

#define ADC_CTRL_GAIN_0_GAIN2_SEL_1_SHIFT                               19
#define ADC_CTRL_GAIN_0_GAIN2_SEL_1_MASK                                0x00380000
#define ADC_CTRL_GAIN_0_GAIN2_SEL_1_SET(n)                              (((uint32_t)(n) << 19 ) & 0x00380000)
#define ADC_CTRL_GAIN_0_GAIN2_SEL_1_CLR                                 0xFFC7FFFF

#define ADC_CTRL_GAIN_0_GAIN1_SEL_1_SHIFT                               16
#define ADC_CTRL_GAIN_0_GAIN1_SEL_1_MASK                                0x00070000
#define ADC_CTRL_GAIN_0_GAIN1_SEL_1_SET(n)                              (((uint32_t)(n) << 16 ) & 0x00070000)
#define ADC_CTRL_GAIN_0_GAIN1_SEL_1_CLR                                 0xFFF8FFFF

#define ADC_CTRL_GAIN_0_OP_SEL_0_SHIFT                                  11
#define ADC_CTRL_GAIN_0_OP_SEL_0_MASK                                   0x00000800
#define ADC_CTRL_GAIN_0_OP_SEL_0_SET(n)                                 (((uint32_t)(n) << 11 ) & 0x00000800)
#define ADC_CTRL_GAIN_0_OP_SEL_0_CLR                                    0xFFFFF7FF

#define ADC_CTRL_GAIN_0_VCA_SEL_0_SHIFT                                 10
#define ADC_CTRL_GAIN_0_VCA_SEL_0_MASK                                  0x00000400
#define ADC_CTRL_GAIN_0_VCA_SEL_0_SET(n)                                (((uint32_t)(n) << 10 ) & 0x00000400)
#define ADC_CTRL_GAIN_0_VCA_SEL_0_CLR                                   0xFFFFFBFF

#define ADC_CTRL_GAIN_0_VCR_SEL_0_SHIFT                                 6
#define ADC_CTRL_GAIN_0_VCR_SEL_0_MASK                                  0x000003C0
#define ADC_CTRL_GAIN_0_VCR_SEL_0_SET(n)                                (((uint32_t)(n) << 6  ) & 0x000003C0)
#define ADC_CTRL_GAIN_0_VCR_SEL_0_CLR                                   0xFFFFFC3F

#define ADC_CTRL_GAIN_0_GAIN2_SEL_0_SHIFT                               3
#define ADC_CTRL_GAIN_0_GAIN2_SEL_0_MASK                                0x00000038
#define ADC_CTRL_GAIN_0_GAIN2_SEL_0_SET(n)                              (((uint32_t)(n) << 3  ) & 0x00000038)
#define ADC_CTRL_GAIN_0_GAIN2_SEL_0_CLR                                 0xFFFFFFC7

#define ADC_CTRL_GAIN_0_GAIN1_SEL_0_SHIFT                               0
#define ADC_CTRL_GAIN_0_GAIN1_SEL_0_MASK                                0x00000007
#define ADC_CTRL_GAIN_0_GAIN1_SEL_0_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000007)
#define ADC_CTRL_GAIN_0_GAIN1_SEL_0_CLR                                 0xFFFFFFF8

#define ADC_CTRL_GAIN_1_OP_SEL_3_SHIFT                                  27
#define ADC_CTRL_GAIN_1_OP_SEL_3_MASK                                   0x08000000
#define ADC_CTRL_GAIN_1_OP_SEL_3_SET(n)                                 (((uint32_t)(n) << 27 ) & 0x08000000)
#define ADC_CTRL_GAIN_1_OP_SEL_3_CLR                                    0xF7FFFFFF

#define ADC_CTRL_GAIN_1_VCA_SEL_3_SHIFT                                 26
#define ADC_CTRL_GAIN_1_VCA_SEL_3_MASK                                  0x04000000
#define ADC_CTRL_GAIN_1_VCA_SEL_3_SET(n)                                (((uint32_t)(n) << 26 ) & 0x04000000)
#define ADC_CTRL_GAIN_1_VCA_SEL_3_CLR                                   0xFBFFFFFF

#define ADC_CTRL_GAIN_1_VCR_SEL_3_SHIFT                                 22
#define ADC_CTRL_GAIN_1_VCR_SEL_3_MASK                                  0x03C00000
#define ADC_CTRL_GAIN_1_VCR_SEL_3_SET(n)                                (((uint32_t)(n) << 22 ) & 0x03C00000)
#define ADC_CTRL_GAIN_1_VCR_SEL_3_CLR                                   0xFC3FFFFF

#define ADC_CTRL_GAIN_1_GAIN2_SEL_3_SHIFT                               19
#define ADC_CTRL_GAIN_1_GAIN2_SEL_3_MASK                                0x00380000
#define ADC_CTRL_GAIN_1_GAIN2_SEL_3_SET(n)                              (((uint32_t)(n) << 19 ) & 0x00380000)
#define ADC_CTRL_GAIN_1_GAIN2_SEL_3_CLR                                 0xFFC7FFFF

#define ADC_CTRL_GAIN_1_GAIN1_SEL_3_SHIFT                               16
#define ADC_CTRL_GAIN_1_GAIN1_SEL_3_MASK                                0x00070000
#define ADC_CTRL_GAIN_1_GAIN1_SEL_3_SET(n)                              (((uint32_t)(n) << 16 ) & 0x00070000)
#define ADC_CTRL_GAIN_1_GAIN1_SEL_3_CLR                                 0xFFF8FFFF

#define ADC_CTRL_GAIN_1_OP_SEL_2_SHIFT                                  11
#define ADC_CTRL_GAIN_1_OP_SEL_2_MASK                                   0x00000800
#define ADC_CTRL_GAIN_1_OP_SEL_2_SET(n)                                 (((uint32_t)(n) << 11 ) & 0x00000800)
#define ADC_CTRL_GAIN_1_OP_SEL_2_CLR                                    0xFFFFF7FF

#define ADC_CTRL_GAIN_1_VCA_SEL_2_SHIFT                                 10
#define ADC_CTRL_GAIN_1_VCA_SEL_2_MASK                                  0x00000400
#define ADC_CTRL_GAIN_1_VCA_SEL_2_SET(n)                                (((uint32_t)(n) << 10 ) & 0x00000400)
#define ADC_CTRL_GAIN_1_VCA_SEL_2_CLR                                   0xFFFFFBFF

#define ADC_CTRL_GAIN_1_VCR_SEL_2_SHIFT                                 6
#define ADC_CTRL_GAIN_1_VCR_SEL_2_MASK                                  0x000003C0
#define ADC_CTRL_GAIN_1_VCR_SEL_2_SET(n)                                (((uint32_t)(n) << 6  ) & 0x000003C0)
#define ADC_CTRL_GAIN_1_VCR_SEL_2_CLR                                   0xFFFFFC3F

#define ADC_CTRL_GAIN_1_GAIN2_SEL_2_SHIFT                               3
#define ADC_CTRL_GAIN_1_GAIN2_SEL_2_MASK                                0x00000038
#define ADC_CTRL_GAIN_1_GAIN2_SEL_2_SET(n)                              (((uint32_t)(n) << 3  ) & 0x00000038)
#define ADC_CTRL_GAIN_1_GAIN2_SEL_2_CLR                                 0xFFFFFFC7

#define ADC_CTRL_GAIN_1_GAIN1_SEL_2_SHIFT                               0
#define ADC_CTRL_GAIN_1_GAIN1_SEL_2_MASK                                0x00000007
#define ADC_CTRL_GAIN_1_GAIN1_SEL_2_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000007)
#define ADC_CTRL_GAIN_1_GAIN1_SEL_2_CLR                                 0xFFFFFFF8

#define ADC_CTRL_GAIN_2_OP_SEL_5_SHIFT                                  27
#define ADC_CTRL_GAIN_2_OP_SEL_5_MASK                                   0x08000000
#define ADC_CTRL_GAIN_2_OP_SEL_5_SET(n)                                 (((uint32_t)(n) << 27 ) & 0x08000000)
#define ADC_CTRL_GAIN_2_OP_SEL_5_CLR                                    0xF7FFFFFF

#define ADC_CTRL_GAIN_2_VCA_SEL_5_SHIFT                                 26
#define ADC_CTRL_GAIN_2_VCA_SEL_5_MASK                                  0x04000000
#define ADC_CTRL_GAIN_2_VCA_SEL_5_SET(n)                                (((uint32_t)(n) << 26 ) & 0x04000000)
#define ADC_CTRL_GAIN_2_VCA_SEL_5_CLR                                   0xFBFFFFFF

#define ADC_CTRL_GAIN_2_VCR_SEL_5_SHIFT                                 22
#define ADC_CTRL_GAIN_2_VCR_SEL_5_MASK                                  0x03C00000
#define ADC_CTRL_GAIN_2_VCR_SEL_5_SET(n)                                (((uint32_t)(n) << 22 ) & 0x03C00000)
#define ADC_CTRL_GAIN_2_VCR_SEL_5_CLR                                   0xFC3FFFFF

#define ADC_CTRL_GAIN_2_GAIN2_SEL_5_SHIFT                               19
#define ADC_CTRL_GAIN_2_GAIN2_SEL_5_MASK                                0x00380000
#define ADC_CTRL_GAIN_2_GAIN2_SEL_5_SET(n)                              (((uint32_t)(n) << 19 ) & 0x00380000)
#define ADC_CTRL_GAIN_2_GAIN2_SEL_5_CLR                                 0xFFC7FFFF

#define ADC_CTRL_GAIN_2_GAIN1_SEL_5_SHIFT                               16
#define ADC_CTRL_GAIN_2_GAIN1_SEL_5_MASK                                0x00070000
#define ADC_CTRL_GAIN_2_GAIN1_SEL_5_SET(n)                              (((uint32_t)(n) << 16 ) & 0x00070000)
#define ADC_CTRL_GAIN_2_GAIN1_SEL_5_CLR                                 0xFFF8FFFF

#define ADC_CTRL_GAIN_2_OP_SEL_4_SHIFT                                  11
#define ADC_CTRL_GAIN_2_OP_SEL_4_MASK                                   0x00000800
#define ADC_CTRL_GAIN_2_OP_SEL_4_SET(n)                                 (((uint32_t)(n) << 11 ) & 0x00000800)
#define ADC_CTRL_GAIN_2_OP_SEL_4_CLR                                    0xFFFFF7FF

#define ADC_CTRL_GAIN_2_VCA_SEL_4_SHIFT                                 10
#define ADC_CTRL_GAIN_2_VCA_SEL_4_MASK                                  0x00000400
#define ADC_CTRL_GAIN_2_VCA_SEL_4_SET(n)                                (((uint32_t)(n) << 10 ) & 0x00000400)
#define ADC_CTRL_GAIN_2_VCA_SEL_4_CLR                                   0xFFFFFBFF

#define ADC_CTRL_GAIN_2_VCR_SEL_4_SHIFT                                 6
#define ADC_CTRL_GAIN_2_VCR_SEL_4_MASK                                  0x000003C0
#define ADC_CTRL_GAIN_2_VCR_SEL_4_SET(n)                                (((uint32_t)(n) << 6  ) & 0x000003C0)
#define ADC_CTRL_GAIN_2_VCR_SEL_4_CLR                                   0xFFFFFC3F

#define ADC_CTRL_GAIN_2_GAIN2_SEL_4_SHIFT                               3
#define ADC_CTRL_GAIN_2_GAIN2_SEL_4_MASK                                0x00000038
#define ADC_CTRL_GAIN_2_GAIN2_SEL_4_SET(n)                              (((uint32_t)(n) << 3  ) & 0x00000038)
#define ADC_CTRL_GAIN_2_GAIN2_SEL_4_CLR                                 0xFFFFFFC7

#define ADC_CTRL_GAIN_2_GAIN1_SEL_4_SHIFT                               0
#define ADC_CTRL_GAIN_2_GAIN1_SEL_4_MASK                                0x00000007
#define ADC_CTRL_GAIN_2_GAIN1_SEL_4_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000007)
#define ADC_CTRL_GAIN_2_GAIN1_SEL_4_CLR                                 0xFFFFFFF8

#define ADC_CTRL_GAIN_3_OP_SEL_7_SHIFT                                  27
#define ADC_CTRL_GAIN_3_OP_SEL_7_MASK                                   0x08000000
#define ADC_CTRL_GAIN_3_OP_SEL_7_SET(n)                                 (((uint32_t)(n) << 27 ) & 0x08000000)
#define ADC_CTRL_GAIN_3_OP_SEL_7_CLR                                    0xF7FFFFFF

#define ADC_CTRL_GAIN_3_VCA_SEL_7_SHIFT                                 26
#define ADC_CTRL_GAIN_3_VCA_SEL_7_MASK                                  0x04000000
#define ADC_CTRL_GAIN_3_VCA_SEL_7_SET(n)                                (((uint32_t)(n) << 26 ) & 0x04000000)
#define ADC_CTRL_GAIN_3_VCA_SEL_7_CLR                                   0xFBFFFFFF

#define ADC_CTRL_GAIN_3_VCR_SEL_7_SHIFT                                 22
#define ADC_CTRL_GAIN_3_VCR_SEL_7_MASK                                  0x03C00000
#define ADC_CTRL_GAIN_3_VCR_SEL_7_SET(n)                                (((uint32_t)(n) << 22 ) & 0x03C00000)
#define ADC_CTRL_GAIN_3_VCR_SEL_7_CLR                                   0xFC3FFFFF

#define ADC_CTRL_GAIN_3_GAIN2_SEL_7_SHIFT                               19
#define ADC_CTRL_GAIN_3_GAIN2_SEL_7_MASK                                0x00380000
#define ADC_CTRL_GAIN_3_GAIN2_SEL_7_SET(n)                              (((uint32_t)(n) << 19 ) & 0x00380000)
#define ADC_CTRL_GAIN_3_GAIN2_SEL_7_CLR                                 0xFFC7FFFF

#define ADC_CTRL_GAIN_3_GAIN1_SEL_7_SHIFT                               16
#define ADC_CTRL_GAIN_3_GAIN1_SEL_7_MASK                                0x00070000
#define ADC_CTRL_GAIN_3_GAIN1_SEL_7_SET(n)                              (((uint32_t)(n) << 16 ) & 0x00070000)
#define ADC_CTRL_GAIN_3_GAIN1_SEL_7_CLR                                 0xFFF8FFFF

#define ADC_CTRL_GAIN_3_OP_SEL_6_SHIFT                                  11
#define ADC_CTRL_GAIN_3_OP_SEL_6_MASK                                   0x00000800
#define ADC_CTRL_GAIN_3_OP_SEL_6_SET(n)                                 (((uint32_t)(n) << 11 ) & 0x00000800)
#define ADC_CTRL_GAIN_3_OP_SEL_6_CLR                                    0xFFFFF7FF

#define ADC_CTRL_GAIN_3_VCA_SEL_6_SHIFT                                 10
#define ADC_CTRL_GAIN_3_VCA_SEL_6_MASK                                  0x00000400
#define ADC_CTRL_GAIN_3_VCA_SEL_6_SET(n)                                (((uint32_t)(n) << 10 ) & 0x00000400)
#define ADC_CTRL_GAIN_3_VCA_SEL_6_CLR                                   0xFFFFFBFF

#define ADC_CTRL_GAIN_3_VCR_SEL_6_SHIFT                                 6
#define ADC_CTRL_GAIN_3_VCR_SEL_6_MASK                                  0x000003C0
#define ADC_CTRL_GAIN_3_VCR_SEL_6_SET(n)                                (((uint32_t)(n) << 6  ) & 0x000003C0)
#define ADC_CTRL_GAIN_3_VCR_SEL_6_CLR                                   0xFFFFFC3F

#define ADC_CTRL_GAIN_3_GAIN2_SEL_6_SHIFT                               3
#define ADC_CTRL_GAIN_3_GAIN2_SEL_6_MASK                                0x00000038
#define ADC_CTRL_GAIN_3_GAIN2_SEL_6_SET(n)                              (((uint32_t)(n) << 3  ) & 0x00000038)
#define ADC_CTRL_GAIN_3_GAIN2_SEL_6_CLR                                 0xFFFFFFC7

#define ADC_CTRL_GAIN_3_GAIN1_SEL_6_SHIFT                               0
#define ADC_CTRL_GAIN_3_GAIN1_SEL_6_MASK                                0x00000007
#define ADC_CTRL_GAIN_3_GAIN1_SEL_6_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000007)
#define ADC_CTRL_GAIN_3_GAIN1_SEL_6_CLR                                 0xFFFFFFF8

#define ADC_CTRL_ANA_ADC_REG_SHIFT                                      0
#define ADC_CTRL_ANA_ADC_REG_MASK                                       0x000000FF
#define ADC_CTRL_ANA_ADC_REG_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x000000FF)
#define ADC_CTRL_ANA_ADC_REG_CLR                                        0xFFFFFF00

#define ADC_CTRL_CAL_0_ADC_OUT_OFFSET_0_SHIFT                           16
#define ADC_CTRL_CAL_0_ADC_OUT_OFFSET_0_MASK                            0x07FF0000
#define ADC_CTRL_CAL_0_ADC_OUT_OFFSET_0_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_0_ADC_OUT_OFFSET_0_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_0_ADC_OUT_CAL_0_SHIFT                              0
#define ADC_CTRL_CAL_0_ADC_OUT_CAL_0_MASK                               0x00000FFF
#define ADC_CTRL_CAL_0_ADC_OUT_CAL_0_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_0_ADC_OUT_CAL_0_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_1_ADC_OUT_OFFSET_1_SHIFT                           16
#define ADC_CTRL_CAL_1_ADC_OUT_OFFSET_1_MASK                            0x07FF0000
#define ADC_CTRL_CAL_1_ADC_OUT_OFFSET_1_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_1_ADC_OUT_OFFSET_1_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_1_ADC_OUT_CAL_1_SHIFT                              0
#define ADC_CTRL_CAL_1_ADC_OUT_CAL_1_MASK                               0x00000FFF
#define ADC_CTRL_CAL_1_ADC_OUT_CAL_1_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_1_ADC_OUT_CAL_1_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_2_ADC_OUT_OFFSET_2_SHIFT                           16
#define ADC_CTRL_CAL_2_ADC_OUT_OFFSET_2_MASK                            0x07FF0000
#define ADC_CTRL_CAL_2_ADC_OUT_OFFSET_2_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_2_ADC_OUT_OFFSET_2_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_2_ADC_OUT_CAL_2_SHIFT                              0
#define ADC_CTRL_CAL_2_ADC_OUT_CAL_2_MASK                               0x00000FFF
#define ADC_CTRL_CAL_2_ADC_OUT_CAL_2_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_2_ADC_OUT_CAL_2_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_3_ADC_OUT_OFFSET_3_SHIFT                           16
#define ADC_CTRL_CAL_3_ADC_OUT_OFFSET_3_MASK                            0x07FF0000
#define ADC_CTRL_CAL_3_ADC_OUT_OFFSET_3_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_3_ADC_OUT_OFFSET_3_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_3_ADC_OUT_CAL_3_SHIFT                              0
#define ADC_CTRL_CAL_3_ADC_OUT_CAL_3_MASK                               0x00000FFF
#define ADC_CTRL_CAL_3_ADC_OUT_CAL_3_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_3_ADC_OUT_CAL_3_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_4_ADC_OUT_OFFSET_4_SHIFT                           16
#define ADC_CTRL_CAL_4_ADC_OUT_OFFSET_4_MASK                            0x07FF0000
#define ADC_CTRL_CAL_4_ADC_OUT_OFFSET_4_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_4_ADC_OUT_OFFSET_4_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_4_ADC_OUT_CAL_4_SHIFT                              0
#define ADC_CTRL_CAL_4_ADC_OUT_CAL_4_MASK                               0x00000FFF
#define ADC_CTRL_CAL_4_ADC_OUT_CAL_4_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_4_ADC_OUT_CAL_4_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_5_ADC_OUT_OFFSET_5_SHIFT                           16
#define ADC_CTRL_CAL_5_ADC_OUT_OFFSET_5_MASK                            0x07FF0000
#define ADC_CTRL_CAL_5_ADC_OUT_OFFSET_5_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_5_ADC_OUT_OFFSET_5_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_5_ADC_OUT_CAL_5_SHIFT                              0
#define ADC_CTRL_CAL_5_ADC_OUT_CAL_5_MASK                               0x00000FFF
#define ADC_CTRL_CAL_5_ADC_OUT_CAL_5_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_5_ADC_OUT_CAL_5_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_6_ADC_OUT_OFFSET_6_SHIFT                           16
#define ADC_CTRL_CAL_6_ADC_OUT_OFFSET_6_MASK                            0x07FF0000
#define ADC_CTRL_CAL_6_ADC_OUT_OFFSET_6_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_6_ADC_OUT_OFFSET_6_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_6_ADC_OUT_CAL_6_SHIFT                              0
#define ADC_CTRL_CAL_6_ADC_OUT_CAL_6_MASK                               0x00000FFF
#define ADC_CTRL_CAL_6_ADC_OUT_CAL_6_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_6_ADC_OUT_CAL_6_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_7_ADC_OUT_OFFSET_7_SHIFT                           16
#define ADC_CTRL_CAL_7_ADC_OUT_OFFSET_7_MASK                            0x07FF0000
#define ADC_CTRL_CAL_7_ADC_OUT_OFFSET_7_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_7_ADC_OUT_OFFSET_7_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_7_ADC_OUT_CAL_7_SHIFT                              0
#define ADC_CTRL_CAL_7_ADC_OUT_CAL_7_MASK                               0x00000FFF
#define ADC_CTRL_CAL_7_ADC_OUT_CAL_7_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_7_ADC_OUT_CAL_7_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_8_ADC_OUT_OFFSET_8_SHIFT                           16
#define ADC_CTRL_CAL_8_ADC_OUT_OFFSET_8_MASK                            0x07FF0000
#define ADC_CTRL_CAL_8_ADC_OUT_OFFSET_8_SET(n)                          (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_8_ADC_OUT_OFFSET_8_CLR                             0xF800FFFF

#define ADC_CTRL_CAL_8_ADC_OUT_CAL_8_SHIFT                              0
#define ADC_CTRL_CAL_8_ADC_OUT_CAL_8_MASK                               0x00000FFF
#define ADC_CTRL_CAL_8_ADC_OUT_CAL_8_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_8_ADC_OUT_CAL_8_CLR                                0xFFFFF000

#define ADC_CTRL_CAL_9_ADC_OUT_D0_SHIFT                                 16
#define ADC_CTRL_CAL_9_ADC_OUT_D0_MASK                                  0x07FF0000
#define ADC_CTRL_CAL_9_ADC_OUT_D0_SET(n)                                (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_9_ADC_OUT_D0_CLR                                   0xF800FFFF

#define ADC_CTRL_CAL_9_ADC_OUT_C0_SHIFT                                 0
#define ADC_CTRL_CAL_9_ADC_OUT_C0_MASK                                  0x00000FFF
#define ADC_CTRL_CAL_9_ADC_OUT_C0_SET(n)                                (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_9_ADC_OUT_C0_CLR                                   0xFFFFF000

#define ADC_CTRL_CAL_10_ADC_OUT_D1_SHIFT                                16
#define ADC_CTRL_CAL_10_ADC_OUT_D1_MASK                                 0x07FF0000
#define ADC_CTRL_CAL_10_ADC_OUT_D1_SET(n)                               (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_10_ADC_OUT_D1_CLR                                  0xF800FFFF

#define ADC_CTRL_CAL_10_ADC_OUT_C1_SHIFT                                0
#define ADC_CTRL_CAL_10_ADC_OUT_C1_MASK                                 0x00000FFF
#define ADC_CTRL_CAL_10_ADC_OUT_C1_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_10_ADC_OUT_C1_CLR                                  0xFFFFF000

#define ADC_CTRL_CAL_11_ADC_OUT_D2_SHIFT                                16
#define ADC_CTRL_CAL_11_ADC_OUT_D2_MASK                                 0x07FF0000
#define ADC_CTRL_CAL_11_ADC_OUT_D2_SET(n)                               (((uint32_t)(n) << 16 ) & 0x07FF0000)
#define ADC_CTRL_CAL_11_ADC_OUT_D2_CLR                                  0xF800FFFF

#define ADC_CTRL_CAL_11_ADC_OUT_C2_SHIFT                                0
#define ADC_CTRL_CAL_11_ADC_OUT_C2_MASK                                 0x00000FFF
#define ADC_CTRL_CAL_11_ADC_OUT_C2_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_CTRL_CAL_11_ADC_OUT_C2_CLR                                  0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL1_SHIFT                    16
#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL1_MASK                     0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL1_SET(n)                   (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL1_CLR                      0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL0_SHIFT                    0
#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL0_MASK                     0x00000FFF
#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL0_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE0_SARADC_TRIM_VAL0_CLR                      0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL3_SHIFT                    16
#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL3_MASK                     0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL3_SET(n)                   (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL3_CLR                      0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL2_SHIFT                    0
#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL2_MASK                     0x00000FFF
#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL2_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE1_SARADC_TRIM_VAL2_CLR                      0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL5_SHIFT                    16
#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL5_MASK                     0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL5_SET(n)                   (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL5_CLR                      0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL4_SHIFT                    0
#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL4_MASK                     0x00000FFF
#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL4_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE2_SARADC_TRIM_VAL4_CLR                      0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL7_SHIFT                    16
#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL7_MASK                     0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL7_SET(n)                   (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL7_CLR                      0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL6_SHIFT                    0
#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL6_MASK                     0x00000FFF
#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL6_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE3_SARADC_TRIM_VAL6_CLR                      0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL9_SHIFT                    16
#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL9_MASK                     0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL9_SET(n)                   (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL9_CLR                      0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL8_SHIFT                    0
#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL8_MASK                     0x00000FFF
#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL8_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE4_SARADC_TRIM_VAL8_CLR                      0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL11_SHIFT                   16
#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL11_MASK                    0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL11_SET(n)                  (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL11_CLR                     0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL10_SHIFT                   0
#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL10_MASK                    0x00000FFF
#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL10_SET(n)                  (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE5_SARADC_TRIM_VAL10_CLR                     0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL13_SHIFT                   16
#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL13_MASK                    0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL13_SET(n)                  (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL13_CLR                     0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL12_SHIFT                   0
#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL12_MASK                    0x00000FFF
#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL12_SET(n)                  (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE6_SARADC_TRIM_VAL12_CLR                     0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL15_SHIFT                   16
#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL15_MASK                    0x0FFF0000
#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL15_SET(n)                  (((uint32_t)(n) << 16 ) & 0x0FFF0000)
#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL15_CLR                     0xF000FFFF

#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL14_SHIFT                   0
#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL14_MASK                    0x00000FFF
#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL14_SET(n)                  (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define ADC_TRIM_ADSAR_VALUE7_SARADC_TRIM_VAL14_CLR                     0xFFFFF000

#define ADC_TRIM_ADSAR_VALUE8_SARADC_TRIM_VAL16_SHIFT                   0
#define ADC_TRIM_ADSAR_VALUE8_SARADC_TRIM_VAL16_MASK                    0x00001FFF
#define ADC_TRIM_ADSAR_VALUE8_SARADC_TRIM_VAL16_SET(n)                  (((uint32_t)(n) << 0  ) & 0x00001FFF)
#define ADC_TRIM_ADSAR_VALUE8_SARADC_TRIM_VAL16_CLR                     0xFFFFE000

// Register Structure Definition
typedef struct
{
    __IO uint32_t FIFO_RDATA        : 32 ; // 31 : 0
} ADC_FIFO_DATA_FIELD_T;

typedef struct
{
    __IO uint32_t ENTRY_VALID       : 4  ; // 3  : 0
    __IO uint32_t RESERVED0         : 28 ; // 31 : 4
} ADC_FIFO_STATE_FIELD_T;

typedef struct
{
    __IO uint32_t SW_START          : 1  ; // 0  : 0
    __IO uint32_t SW_ADC_EN         : 1  ; // 1  : 1
    __IO uint32_t AUTO_ADC_EN       : 1  ; // 2  : 2
    __IO uint32_t RESERVED2         : 5  ; // 7  : 3
    __IO uint32_t IRQ_MODE          : 3  ; // 10 : 8
    __IO uint32_t RESERVED1         : 1  ; // 11 : 11
    __IO uint32_t FIFO_THRHLD       : 3  ; // 14 : 12
    __IO uint32_t FIFO_FORMAT       : 1  ; // 15 : 15
    __IO uint32_t TRIG_EN           : 8  ; // 23 : 16
    __IO uint32_t RESERVED0         : 8  ; // 31 : 24
} ADC_CTRL0_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_IN_SEL        : 4  ; // 3  : 0
    __IO uint32_t CHNL_SAMP_NUM     : 3  ; // 6  : 4
    __IO uint32_t CHNL_AVG_EN       : 1  ; // 7  : 7
    __IO uint32_t SCAN_CHNL_NUM     : 3  ; // 10 : 8
    __IO uint32_t RESERVED0         : 5  ; // 15 : 11
    __IO uint32_t TRIG_NUM          : 16 ; // 31 : 16
} ADC_CTRL1_FIELD_T;

typedef struct
{
    __IO uint32_t INIT_CYCLE        : 10 ; // 9  : 0
    __IO uint32_t CHNL_INIT_CYCLE   : 7  ; // 16 : 10
    __IO uint32_t RESERVED0         : 1  ; // 17 : 17
    __IO uint32_t SAMP_DLY_CYCLE    : 4  ; // 21 : 18
    __IO uint32_t SAMP_CYCLE        : 7  ; // 28 : 22
    __IO uint32_t SAMP_PRE_CYCLE    : 3  ; // 31 : 29
} ADC_CTRL2_FIELD_T;

typedef struct
{
    __IO uint32_t SCAN_CHNL_0       : 4  ; // 3  : 0
    __IO uint32_t SCAN_CHNL_1       : 4  ; // 7  : 4
    __IO uint32_t SCAN_CHNL_2       : 4  ; // 11 : 8
    __IO uint32_t SCAN_CHNL_3       : 4  ; // 15 : 12
    __IO uint32_t SCAN_CHNL_4       : 4  ; // 19 : 16
    __IO uint32_t SCAN_CHNL_5       : 4  ; // 23 : 20
    __IO uint32_t SCAN_CHNL_6       : 4  ; // 27 : 24
    __IO uint32_t SCAN_CHNL_7       : 4  ; // 31 : 28
} ADC_CTRL3_FIELD_T;

typedef struct
{
    __IO uint32_t CMP_BOTTOM        : 11 ; // 10 : 0
    __IO uint32_t RESERVED1         : 5  ; // 15 : 11
    __IO uint32_t CMP_CEILING       : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL4_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT           : 11 ; // 10 : 0
    __IO uint32_t PWM_STATUS        : 1  ; // 11 : 11
    __IO uint32_t ADC_READY_ERR     : 1  ; // 12 : 12
    __IO uint32_t RESERVED0         : 2  ; // 14 : 13
    __IO uint32_t RAW_OUT17         : 17 ; // 31 : 15
} ADC_ADC_OUT_FIELD_T;

typedef struct
{
    __IO uint32_t IRQ_COMP_STATUS   : 22 ; // 21 : 0
    __IO uint32_t RESERVED0         : 10 ; // 31 : 22
} ADC_CHNL_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t GAIN1_SEL_0       : 3  ; // 2  : 0
    __IO uint32_t GAIN2_SEL_0       : 3  ; // 5  : 3
    __IO uint32_t VCR_SEL_0         : 4  ; // 9  : 6
    __IO uint32_t VCA_SEL_0         : 1  ; // 10 : 10
    __IO uint32_t OP_SEL_0          : 1  ; // 11 : 11
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t GAIN1_SEL_1       : 3  ; // 18 : 16
    __IO uint32_t GAIN2_SEL_1       : 3  ; // 21 : 19
    __IO uint32_t VCR_SEL_1         : 4  ; // 25 : 22
    __IO uint32_t VCA_SEL_1         : 1  ; // 26 : 26
    __IO uint32_t OP_SEL_1          : 1  ; // 27 : 27
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_CTRL_GAIN_0_FIELD_T;

typedef struct
{
    __IO uint32_t GAIN1_SEL_2       : 3  ; // 2  : 0
    __IO uint32_t GAIN2_SEL_2       : 3  ; // 5  : 3
    __IO uint32_t VCR_SEL_2         : 4  ; // 9  : 6
    __IO uint32_t VCA_SEL_2         : 1  ; // 10 : 10
    __IO uint32_t OP_SEL_2          : 1  ; // 11 : 11
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t GAIN1_SEL_3       : 3  ; // 18 : 16
    __IO uint32_t GAIN2_SEL_3       : 3  ; // 21 : 19
    __IO uint32_t VCR_SEL_3         : 4  ; // 25 : 22
    __IO uint32_t VCA_SEL_3         : 1  ; // 26 : 26
    __IO uint32_t OP_SEL_3          : 1  ; // 27 : 27
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_CTRL_GAIN_1_FIELD_T;

typedef struct
{
    __IO uint32_t GAIN1_SEL_4       : 3  ; // 2  : 0
    __IO uint32_t GAIN2_SEL_4       : 3  ; // 5  : 3
    __IO uint32_t VCR_SEL_4         : 4  ; // 9  : 6
    __IO uint32_t VCA_SEL_4         : 1  ; // 10 : 10
    __IO uint32_t OP_SEL_4          : 1  ; // 11 : 11
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t GAIN1_SEL_5       : 3  ; // 18 : 16
    __IO uint32_t GAIN2_SEL_5       : 3  ; // 21 : 19
    __IO uint32_t VCR_SEL_5         : 4  ; // 25 : 22
    __IO uint32_t VCA_SEL_5         : 1  ; // 26 : 26
    __IO uint32_t OP_SEL_5          : 1  ; // 27 : 27
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_CTRL_GAIN_2_FIELD_T;

typedef struct
{
    __IO uint32_t GAIN1_SEL_6       : 3  ; // 2  : 0
    __IO uint32_t GAIN2_SEL_6       : 3  ; // 5  : 3
    __IO uint32_t VCR_SEL_6         : 4  ; // 9  : 6
    __IO uint32_t VCA_SEL_6         : 1  ; // 10 : 10
    __IO uint32_t OP_SEL_6          : 1  ; // 11 : 11
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t GAIN1_SEL_7       : 3  ; // 18 : 16
    __IO uint32_t GAIN2_SEL_7       : 3  ; // 21 : 19
    __IO uint32_t VCR_SEL_7         : 4  ; // 25 : 22
    __IO uint32_t VCA_SEL_7         : 1  ; // 26 : 26
    __IO uint32_t OP_SEL_7          : 1  ; // 27 : 27
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_CTRL_GAIN_3_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_REG           : 8  ; // 7  : 0
    __IO uint32_t RESERVED0         : 24 ; // 31 : 8
} ADC_CTRL_ANA_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_0     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_0  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_0_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_1     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_1  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_1_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_2     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_2  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_2_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_3     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_3  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_3_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_4     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_4  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_4_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_5     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_5  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_5_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_6     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_6  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_6_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_7     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_7  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_7_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_CAL_8     : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_OFFSET_8  : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_8_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_C0        : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_D0        : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_9_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_C1        : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_D1        : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_10_FIELD_T;

typedef struct
{
    __IO uint32_t ADC_OUT_C2        : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t ADC_OUT_D2        : 11 ; // 26 : 16
    __IO uint32_t RESERVED0         : 5  ; // 31 : 27
} ADC_CTRL_CAL_11_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL0  : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL1  : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE0_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL2  : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL3  : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE1_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL4  : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL5  : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE2_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL6  : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL7  : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE3_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL8  : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL9  : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE4_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL10 : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL11 : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE5_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL12 : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL13 : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE6_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL14 : 12 ; // 11 : 0
    __IO uint32_t RESERVED1         : 4  ; // 15 : 12
    __IO uint32_t SARADC_TRIM_VAL15 : 12 ; // 27 : 16
    __IO uint32_t RESERVED0         : 4  ; // 31 : 28
} ADC_TRIM_ADSAR_VALUE7_FIELD_T;

typedef struct
{
    __IO uint32_t SARADC_TRIM_VAL16 : 13 ; // 12 : 0
    __IO uint32_t RESERVED0         : 19 ; // 31 : 13
} ADC_TRIM_ADSAR_VALUE8_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t FIFO_DATA                             ; // 0x0000
        ADC_FIFO_DATA_FIELD_T FIFO_DATA_F                    ;
    };

    union
    {
        __IO  uint32_t FIFO_STATE                            ; // 0x0004
        ADC_FIFO_STATE_FIELD_T FIFO_STATE_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL0                                 ; // 0x0008
        ADC_CTRL0_FIELD_T CTRL0_F                            ;
    };

    union
    {
        __IO  uint32_t CTRL1                                 ; // 0x000C
        ADC_CTRL1_FIELD_T CTRL1_F                            ;
    };

    union
    {
        __IO  uint32_t CTRL2                                 ; // 0x0010
        ADC_CTRL2_FIELD_T CTRL2_F                            ;
    };

    union
    {
        __IO  uint32_t CTRL3                                 ; // 0x0014
        ADC_CTRL3_FIELD_T CTRL3_F                            ;
    };

    union
    {
        __IO  uint32_t CTRL4                                 ; // 0x0018
        ADC_CTRL4_FIELD_T CTRL4_F                            ;
    };

    union
    {
        __IO  uint32_t ADC_OUT                               ; // 0x001C
        ADC_ADC_OUT_FIELD_T ADC_OUT_F                        ;
    };

    union
    {
        __IO  uint32_t CHNL_STATUS                           ; // 0x0020
        ADC_CHNL_STATUS_FIELD_T CHNL_STATUS_F                ;
    };

    union
    {
        __IO  uint32_t CTRL_GAIN_0                           ; // 0x0024
        ADC_CTRL_GAIN_0_FIELD_T CTRL_GAIN_0_F                ;
    };

    union
    {
        __IO  uint32_t CTRL_GAIN_1                           ; // 0x0028
        ADC_CTRL_GAIN_1_FIELD_T CTRL_GAIN_1_F                ;
    };

    union
    {
        __IO  uint32_t CTRL_GAIN_2                           ; // 0x002C
        ADC_CTRL_GAIN_2_FIELD_T CTRL_GAIN_2_F                ;
    };

    union
    {
        __IO  uint32_t CTRL_GAIN_3                           ; // 0x0030
        ADC_CTRL_GAIN_3_FIELD_T CTRL_GAIN_3_F                ;
    };

    union
    {
        __IO  uint32_t CTRL_ANA                              ; // 0x0034
        ADC_CTRL_ANA_FIELD_T CTRL_ANA_F                      ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_0                            ; // 0x0038
        ADC_CTRL_CAL_0_FIELD_T CTRL_CAL_0_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_1                            ; // 0x003C
        ADC_CTRL_CAL_1_FIELD_T CTRL_CAL_1_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_2                            ; // 0x0040
        ADC_CTRL_CAL_2_FIELD_T CTRL_CAL_2_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_3                            ; // 0x0044
        ADC_CTRL_CAL_3_FIELD_T CTRL_CAL_3_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_4                            ; // 0x0048
        ADC_CTRL_CAL_4_FIELD_T CTRL_CAL_4_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_5                            ; // 0x004C
        ADC_CTRL_CAL_5_FIELD_T CTRL_CAL_5_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_6                            ; // 0x0050
        ADC_CTRL_CAL_6_FIELD_T CTRL_CAL_6_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_7                            ; // 0x0054
        ADC_CTRL_CAL_7_FIELD_T CTRL_CAL_7_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_8                            ; // 0x0058
        ADC_CTRL_CAL_8_FIELD_T CTRL_CAL_8_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_9                            ; // 0x005C
        ADC_CTRL_CAL_9_FIELD_T CTRL_CAL_9_F                  ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_10                           ; // 0x0060
        ADC_CTRL_CAL_10_FIELD_T CTRL_CAL_10_F                ;
    };

    union
    {
        __IO  uint32_t CTRL_CAL_11                           ; // 0x0064
        ADC_CTRL_CAL_11_FIELD_T CTRL_CAL_11_F                ;
    };

    uint32_t RESERVED0[6]                                    ;

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE0                     ; // 0x0080
        ADC_TRIM_ADSAR_VALUE0_FIELD_T TRIM_ADSAR_VALUE0_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE1                     ; // 0x0084
        ADC_TRIM_ADSAR_VALUE1_FIELD_T TRIM_ADSAR_VALUE1_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE2                     ; // 0x0088
        ADC_TRIM_ADSAR_VALUE2_FIELD_T TRIM_ADSAR_VALUE2_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE3                     ; // 0x008C
        ADC_TRIM_ADSAR_VALUE3_FIELD_T TRIM_ADSAR_VALUE3_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE4                     ; // 0x0090
        ADC_TRIM_ADSAR_VALUE4_FIELD_T TRIM_ADSAR_VALUE4_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE5                     ; // 0x0094
        ADC_TRIM_ADSAR_VALUE5_FIELD_T TRIM_ADSAR_VALUE5_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE6                     ; // 0x0098
        ADC_TRIM_ADSAR_VALUE6_FIELD_T TRIM_ADSAR_VALUE6_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE7                     ; // 0x009C
        ADC_TRIM_ADSAR_VALUE7_FIELD_T TRIM_ADSAR_VALUE7_F    ;
    };

    union
    {
        __IO  uint32_t TRIM_ADSAR_VALUE8                     ; // 0x00A0
        ADC_TRIM_ADSAR_VALUE8_FIELD_T TRIM_ADSAR_VALUE8_F    ;
    };

} ADC_REG_TypeDef;

#endif
