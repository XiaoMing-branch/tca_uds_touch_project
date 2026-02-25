/**
 *****************************************************************************
 * @brief   afe_syscfg_reg_def header file.
 *
 * @file    afe_syscfg_reg_def.h
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

#ifndef   AFE_SYSCFG_DEF_H__
#define   AFE_SYSCFG_DEF_H__

// Register Offset Macro Definition
#define AFE_SYSCFG_REVISION_OFFSET                              0x0000
#define AFE_SYSCFG_IMR0_OFFSET                                  0x0004
#define AFE_SYSCFG_ICR0_OFFSET                                  0x0008
#define AFE_SYSCFG_ISR0_OFFSET                                  0x000C
#define AFE_SYSCFG_IRSR0_OFFSET                                 0x0010
#define AFE_SYSCFG_IMR1_OFFSET                                  0x0014
#define AFE_SYSCFG_ICR1_OFFSET                                  0x0018
#define AFE_SYSCFG_ISR1_OFFSET                                  0x001C
#define AFE_SYSCFG_IRSR1_OFFSET                                 0x0020
#define AFE_SYSCFG_GPIO_CTRL_OFFSET                             0x0024
#define AFE_SYSCFG_INT_SNS_CTRL_OFFSET                          0x0028
#define AFE_SYSCFG_BIAS_CTRL_OFFSET                             0x002C
#define AFE_SYSCFG_OTP_STATUS_OFFSET                            0x0030
#define AFE_SYSCFG_LIN_WU_CTRL_OFFSET                           0x0034
#define AFE_SYSCFG_SYSCFG_LOCK_OFFSET                           0x00FC

// Register Address Macro Definition
#define AFE_SYSCFG_REVISION_ADDR                                ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_REVISION_OFFSET)
#define AFE_SYSCFG_IMR0_ADDR                                    ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_IMR0_OFFSET)
#define AFE_SYSCFG_ICR0_ADDR                                    ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_ICR0_OFFSET)
#define AFE_SYSCFG_ISR0_ADDR                                    ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_ISR0_OFFSET)
#define AFE_SYSCFG_IRSR0_ADDR                                   ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_IRSR0_OFFSET)
#define AFE_SYSCFG_IMR1_ADDR                                    ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_IMR1_OFFSET)
#define AFE_SYSCFG_ICR1_ADDR                                    ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_ICR1_OFFSET)
#define AFE_SYSCFG_ISR1_ADDR                                    ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_ISR1_OFFSET)
#define AFE_SYSCFG_IRSR1_ADDR                                   ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_IRSR1_OFFSET)
#define AFE_SYSCFG_GPIO_CTRL_ADDR                               ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_GPIO_CTRL_OFFSET)
#define AFE_SYSCFG_INT_SNS_CTRL_ADDR                            ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_INT_SNS_CTRL_OFFSET)
#define AFE_SYSCFG_BIAS_CTRL_ADDR                               ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_BIAS_CTRL_OFFSET)
#define AFE_SYSCFG_OTP_STATUS_ADDR                              ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_OTP_STATUS_OFFSET)
#define AFE_SYSCFG_LIN_WU_CTRL_ADDR                             ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_LIN_WU_CTRL_OFFSET)
#define AFE_SYSCFG_SYSCFG_LOCK_ADDR                             ( AFE_SYSCFG_BASE_ADDR + AFE_SYSCFG_SYSCFG_LOCK_OFFSET)

// Register Field Macro Definition
#define AFE_SYSCFG_REVISION_REV_ID_SHIFT                                               16
#define AFE_SYSCFG_REVISION_REV_ID_MASK                                                0x007F0000
#define AFE_SYSCFG_REVISION_REV_ID_SET(n)                                              (((uint32_t)(n) << 16 ) & 0x007F0000)
#define AFE_SYSCFG_REVISION_REV_ID_CLR                                                 0xFF80FFFF

#define AFE_SYSCFG_REVISION_CHIP_ID_SHIFT                                              0
#define AFE_SYSCFG_REVISION_CHIP_ID_MASK                                               0x0000FFFF
#define AFE_SYSCFG_REVISION_CHIP_ID_SET(n)                                             (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define AFE_SYSCFG_REVISION_CHIP_ID_CLR                                                0xFFFF0000

#define AFE_SYSCFG_IMR0_INT_MSK                                                        0xFFFFFFFF
#define AFE_SYSCFG_IMR1_INT_MSK                                                        0x3FFF

#define AFE_SYSCFG_IMR0_VS_LVD_INT_MSK_SHIFT                                           31
#define AFE_SYSCFG_IMR0_VS_LVD_INT_MSK_MASK                                            0x80000000
#define AFE_SYSCFG_IMR0_VS_LVD_INT_MSK_SET(n)                                          (((uint32_t)(n) << 31 ) & 0x80000000)
#define AFE_SYSCFG_IMR0_VS_LVD_INT_MSK_CLR                                             0x7FFFFFFF

#define AFE_SYSCFG_IMR0_OTP_INT_MSK_SHIFT                                              30
#define AFE_SYSCFG_IMR0_OTP_INT_MSK_MASK                                               0x40000000
#define AFE_SYSCFG_IMR0_OTP_INT_MSK_SET(n)                                             (((uint32_t)(n) << 30 ) & 0x40000000)
#define AFE_SYSCFG_IMR0_OTP_INT_MSK_CLR                                                0xBFFFFFFF

#define AFE_SYSCFG_IMR0_ADC_DONE_INT_MSK_SHIFT                                         29
#define AFE_SYSCFG_IMR0_ADC_DONE_INT_MSK_MASK                                          0x20000000
#define AFE_SYSCFG_IMR0_ADC_DONE_INT_MSK_SET(n)                                        (((uint32_t)(n) << 29 ) & 0x20000000)
#define AFE_SYSCFG_IMR0_ADC_DONE_INT_MSK_CLR                                           0xDFFFFFFF

#define AFE_SYSCFG_IMR0_TX_1BYTE_DONE_INT_MSK_SHIFT                                    28
#define AFE_SYSCFG_IMR0_TX_1BYTE_DONE_INT_MSK_MASK                                     0x10000000
#define AFE_SYSCFG_IMR0_TX_1BYTE_DONE_INT_MSK_SET(n)                                   (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_SYSCFG_IMR0_TX_1BYTE_DONE_INT_MSK_CLR                                      0xEFFFFFFF

#define AFE_SYSCFG_IMR0_AUTO_ADDR_DONE_INT_MSK_SHIFT                                   27
#define AFE_SYSCFG_IMR0_AUTO_ADDR_DONE_INT_MSK_MASK                                    0x08000000
#define AFE_SYSCFG_IMR0_AUTO_ADDR_DONE_INT_MSK_SET(n)                                  (((uint32_t)(n) << 27 ) & 0x08000000)
#define AFE_SYSCFG_IMR0_AUTO_ADDR_DONE_INT_MSK_CLR                                     0xF7FFFFFF

#define AFE_SYSCFG_IMR0_SLV_SELECTED_INT_MSK_SHIFT                                     26
#define AFE_SYSCFG_IMR0_SLV_SELECTED_INT_MSK_MASK                                      0x04000000
#define AFE_SYSCFG_IMR0_SLV_SELECTED_INT_MSK_SET(n)                                    (((uint32_t)(n) << 26 ) & 0x04000000)
#define AFE_SYSCFG_IMR0_SLV_SELECTED_INT_MSK_CLR                                       0xFBFFFFFF

#define AFE_SYSCFG_IMR0_TX_RX_CONF_INT_MSK_SHIFT                                       25
#define AFE_SYSCFG_IMR0_TX_RX_CONF_INT_MSK_MASK                                        0x02000000
#define AFE_SYSCFG_IMR0_TX_RX_CONF_INT_MSK_SET(n)                                      (((uint32_t)(n) << 25 ) & 0x02000000)
#define AFE_SYSCFG_IMR0_TX_RX_CONF_INT_MSK_CLR                                         0xFDFFFFFF

#define AFE_SYSCFG_IMR0_TX_PID_DONE_INT_MSK_SHIFT                                      24
#define AFE_SYSCFG_IMR0_TX_PID_DONE_INT_MSK_MASK                                       0x01000000
#define AFE_SYSCFG_IMR0_TX_PID_DONE_INT_MSK_SET(n)                                     (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_SYSCFG_IMR0_TX_PID_DONE_INT_MSK_CLR                                        0xFEFFFFFF

#define AFE_SYSCFG_IMR0_RX_TIMEOUT_INT_MSK_SHIFT                                       23
#define AFE_SYSCFG_IMR0_RX_TIMEOUT_INT_MSK_MASK                                        0x00800000
#define AFE_SYSCFG_IMR0_RX_TIMEOUT_INT_MSK_SET(n)                                      (((uint32_t)(n) << 23 ) & 0x00800000)
#define AFE_SYSCFG_IMR0_RX_TIMEOUT_INT_MSK_CLR                                         0xFF7FFFFF

#define AFE_SYSCFG_IMR0_SYNC_VAL_ERR_INT_MSK_SHIFT                                     22
#define AFE_SYSCFG_IMR0_SYNC_VAL_ERR_INT_MSK_MASK                                      0x00400000
#define AFE_SYSCFG_IMR0_SYNC_VAL_ERR_INT_MSK_SET(n)                                    (((uint32_t)(n) << 22 ) & 0x00400000)
#define AFE_SYSCFG_IMR0_SYNC_VAL_ERR_INT_MSK_CLR                                       0xFFBFFFFF

#define AFE_SYSCFG_IMR0_SYNC_DET_INT_MSK_SHIFT                                         21
#define AFE_SYSCFG_IMR0_SYNC_DET_INT_MSK_MASK                                          0x00200000
#define AFE_SYSCFG_IMR0_SYNC_DET_INT_MSK_SET(n)                                        (((uint32_t)(n) << 21 ) & 0x00200000)
#define AFE_SYSCFG_IMR0_SYNC_DET_INT_MSK_CLR                                           0xFFDFFFFF

#define AFE_SYSCFG_IMR0_BRK_DET_INT_MSK_SHIFT                                          20
#define AFE_SYSCFG_IMR0_BRK_DET_INT_MSK_MASK                                           0x00100000
#define AFE_SYSCFG_IMR0_BRK_DET_INT_MSK_SET(n)                                         (((uint32_t)(n) << 20 ) & 0x00100000)
#define AFE_SYSCFG_IMR0_BRK_DET_INT_MSK_CLR                                            0xFFEFFFFF

#define AFE_SYSCFG_IMR0_TX_COL_DET_ERR_INT_MSK_SHIFT                                   19
#define AFE_SYSCFG_IMR0_TX_COL_DET_ERR_INT_MSK_MASK                                    0x00080000
#define AFE_SYSCFG_IMR0_TX_COL_DET_ERR_INT_MSK_SET(n)                                  (((uint32_t)(n) << 19 ) & 0x00080000)
#define AFE_SYSCFG_IMR0_TX_COL_DET_ERR_INT_MSK_CLR                                     0xFFF7FFFF

#define AFE_SYSCFG_IMR0_TX_FIFO_EMPTY_INT_MSK_SHIFT                                    18
#define AFE_SYSCFG_IMR0_TX_FIFO_EMPTY_INT_MSK_MASK                                     0x00040000
#define AFE_SYSCFG_IMR0_TX_FIFO_EMPTY_INT_MSK_SET(n)                                   (((uint32_t)(n) << 18 ) & 0x00040000)
#define AFE_SYSCFG_IMR0_TX_FIFO_EMPTY_INT_MSK_CLR                                      0xFFFBFFFF

#define AFE_SYSCFG_IMR0_TX_DONE_INT_MSK_SHIFT                                          17
#define AFE_SYSCFG_IMR0_TX_DONE_INT_MSK_MASK                                           0x00020000
#define AFE_SYSCFG_IMR0_TX_DONE_INT_MSK_SET(n)                                         (((uint32_t)(n) << 17 ) & 0x00020000)
#define AFE_SYSCFG_IMR0_TX_DONE_INT_MSK_CLR                                            0xFFFDFFFF

#define AFE_SYSCFG_IMR0_RX_FIFO_OVF_ERR_INT_MSK_SHIFT                                  16
#define AFE_SYSCFG_IMR0_RX_FIFO_OVF_ERR_INT_MSK_MASK                                   0x00010000
#define AFE_SYSCFG_IMR0_RX_FIFO_OVF_ERR_INT_MSK_SET(n)                                 (((uint32_t)(n) << 16 ) & 0x00010000)
#define AFE_SYSCFG_IMR0_RX_FIFO_OVF_ERR_INT_MSK_CLR                                    0xFFFEFFFF

#define AFE_SYSCFG_IMR0_RX_FIFO_FULL_INT_MSK_SHIFT                                     15
#define AFE_SYSCFG_IMR0_RX_FIFO_FULL_INT_MSK_MASK                                      0x00008000
#define AFE_SYSCFG_IMR0_RX_FIFO_FULL_INT_MSK_SET(n)                                    (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_SYSCFG_IMR0_RX_FIFO_FULL_INT_MSK_CLR                                       0xFFFF7FFF

#define AFE_SYSCFG_IMR0_RX_STP_ERR_INT_MSK_SHIFT                                       14
#define AFE_SYSCFG_IMR0_RX_STP_ERR_INT_MSK_MASK                                        0x00004000
#define AFE_SYSCFG_IMR0_RX_STP_ERR_INT_MSK_SET(n)                                      (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_SYSCFG_IMR0_RX_STP_ERR_INT_MSK_CLR                                         0xFFFFBFFF

#define AFE_SYSCFG_IMR0_RX_CHKSUM_ERR_INT_MSK_SHIFT                                    13
#define AFE_SYSCFG_IMR0_RX_CHKSUM_ERR_INT_MSK_MASK                                     0x00002000
#define AFE_SYSCFG_IMR0_RX_CHKSUM_ERR_INT_MSK_SET(n)                                   (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_IMR0_RX_CHKSUM_ERR_INT_MSK_CLR                                      0xFFFFDFFF

#define AFE_SYSCFG_IMR0_RX_PTY_CHK_ERR_INT_MSK_SHIFT                                   12
#define AFE_SYSCFG_IMR0_RX_PTY_CHK_ERR_INT_MSK_MASK                                    0x00001000
#define AFE_SYSCFG_IMR0_RX_PTY_CHK_ERR_INT_MSK_SET(n)                                  (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_IMR0_RX_PTY_CHK_ERR_INT_MSK_CLR                                     0xFFFFEFFF

#define AFE_SYSCFG_IMR0_RX_PID_DONE_INT_MSK_SHIFT                                      11
#define AFE_SYSCFG_IMR0_RX_PID_DONE_INT_MSK_MASK                                       0x00000800
#define AFE_SYSCFG_IMR0_RX_PID_DONE_INT_MSK_SET(n)                                     (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_IMR0_RX_PID_DONE_INT_MSK_CLR                                        0xFFFFF7FF

#define AFE_SYSCFG_IMR0_RX_DONE_INT_MSK_SHIFT                                          10
#define AFE_SYSCFG_IMR0_RX_DONE_INT_MSK_MASK                                           0x00000400
#define AFE_SYSCFG_IMR0_RX_DONE_INT_MSK_SET(n)                                         (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_IMR0_RX_DONE_INT_MSK_CLR                                            0xFFFFFBFF

#define AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_SHIFT                                    9
#define AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_MASK                                     0x00000200
#define AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_SET(n)                                   (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_CLR                                      0xFFFFFDFF

#define AFE_SYSCFG_IMR0_CH2_PWM_CLR_INT_MSK_SHIFT                                      8
#define AFE_SYSCFG_IMR0_CH2_PWM_CLR_INT_MSK_MASK                                       0x00000100
#define AFE_SYSCFG_IMR0_CH2_PWM_CLR_INT_MSK_SET(n)                                     (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_IMR0_CH2_PWM_CLR_INT_MSK_CLR                                        0xFFFFFEFF

#define AFE_SYSCFG_IMR0_CH2_PWM_SET_INT_MSK_SHIFT                                      7
#define AFE_SYSCFG_IMR0_CH2_PWM_SET_INT_MSK_MASK                                       0x00000080
#define AFE_SYSCFG_IMR0_CH2_PWM_SET_INT_MSK_SET(n)                                     (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_IMR0_CH2_PWM_SET_INT_MSK_CLR                                        0xFFFFFF7F

#define AFE_SYSCFG_IMR0_CH2_CNT_MAX_INT_MSK_SHIFT                                      6
#define AFE_SYSCFG_IMR0_CH2_CNT_MAX_INT_MSK_MASK                                       0x00000040
#define AFE_SYSCFG_IMR0_CH2_CNT_MAX_INT_MSK_SET(n)                                     (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_IMR0_CH2_CNT_MAX_INT_MSK_CLR                                        0xFFFFFFBF

#define AFE_SYSCFG_IMR0_CH1_PWM_CLR_INT_MSK_SHIFT                                      5
#define AFE_SYSCFG_IMR0_CH1_PWM_CLR_INT_MSK_MASK                                       0x00000020
#define AFE_SYSCFG_IMR0_CH1_PWM_CLR_INT_MSK_SET(n)                                     (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_IMR0_CH1_PWM_CLR_INT_MSK_CLR                                        0xFFFFFFDF

#define AFE_SYSCFG_IMR0_CH1_PWM_SET_INT_MSK_SHIFT                                      4
#define AFE_SYSCFG_IMR0_CH1_PWM_SET_INT_MSK_MASK                                       0x00000010
#define AFE_SYSCFG_IMR0_CH1_PWM_SET_INT_MSK_SET(n)                                     (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_IMR0_CH1_PWM_SET_INT_MSK_CLR                                        0xFFFFFFEF

#define AFE_SYSCFG_IMR0_CH1_CNT_MAX_INT_MSK_SHIFT                                      3
#define AFE_SYSCFG_IMR0_CH1_CNT_MAX_INT_MSK_MASK                                       0x00000008
#define AFE_SYSCFG_IMR0_CH1_CNT_MAX_INT_MSK_SET(n)                                     (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_IMR0_CH1_CNT_MAX_INT_MSK_CLR                                        0xFFFFFFF7

#define AFE_SYSCFG_IMR0_CH0_PWM_CLR_INT_MSK_SHIFT                                      2
#define AFE_SYSCFG_IMR0_CH0_PWM_CLR_INT_MSK_MASK                                       0x00000004
#define AFE_SYSCFG_IMR0_CH0_PWM_CLR_INT_MSK_SET(n)                                     (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_IMR0_CH0_PWM_CLR_INT_MSK_CLR                                        0xFFFFFFFB

#define AFE_SYSCFG_IMR0_CH0_PWM_SET_INT_MSK_SHIFT                                      1
#define AFE_SYSCFG_IMR0_CH0_PWM_SET_INT_MSK_MASK                                       0x00000002
#define AFE_SYSCFG_IMR0_CH0_PWM_SET_INT_MSK_SET(n)                                     (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_IMR0_CH0_PWM_SET_INT_MSK_CLR                                        0xFFFFFFFD

#define AFE_SYSCFG_IMR0_CH0_CNT_MAX_INT_MSK_SHIFT                                      0
#define AFE_SYSCFG_IMR0_CH0_CNT_MAX_INT_MSK_MASK                                       0x00000001
#define AFE_SYSCFG_IMR0_CH0_CNT_MAX_INT_MSK_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_IMR0_CH0_CNT_MAX_INT_MSK_CLR                                        0xFFFFFFFE

#define AFE_SYSCFG_ICR0_VS_LVD_INT_CLR_SHIFT                                           31
#define AFE_SYSCFG_ICR0_VS_LVD_INT_CLR_MASK                                            0x80000000
#define AFE_SYSCFG_ICR0_VS_LVD_INT_CLR_SET(n)                                          (((uint32_t)(n) << 31 ) & 0x80000000)
#define AFE_SYSCFG_ICR0_VS_LVD_INT_CLR_CLR                                             0x7FFFFFFF

#define AFE_SYSCFG_ICR0_OTP_INT_CLR_SHIFT                                              30
#define AFE_SYSCFG_ICR0_OTP_INT_CLR_MASK                                               0x40000000
#define AFE_SYSCFG_ICR0_OTP_INT_CLR_SET(n)                                             (((uint32_t)(n) << 30 ) & 0x40000000)
#define AFE_SYSCFG_ICR0_OTP_INT_CLR_CLR                                                0xBFFFFFFF

#define AFE_SYSCFG_ICR0_ADC_DONE_INT_CLR_SHIFT                                         29
#define AFE_SYSCFG_ICR0_ADC_DONE_INT_CLR_MASK                                          0x20000000
#define AFE_SYSCFG_ICR0_ADC_DONE_INT_CLR_SET(n)                                        (((uint32_t)(n) << 29 ) & 0x20000000)
#define AFE_SYSCFG_ICR0_ADC_DONE_INT_CLR_CLR                                           0xDFFFFFFF

#define AFE_SYSCFG_ICR0_TX_1BYTE_DONE_INT_CLR_SHIFT                                    28
#define AFE_SYSCFG_ICR0_TX_1BYTE_DONE_INT_CLR_MASK                                     0x10000000
#define AFE_SYSCFG_ICR0_TX_1BYTE_DONE_INT_CLR_SET(n)                                   (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_SYSCFG_ICR0_TX_1BYTE_DONE_INT_CLR_CLR                                      0xEFFFFFFF

#define AFE_SYSCFG_ICR0_AUTO_ADDR_DONE_INT_CLR_SHIFT                                   27
#define AFE_SYSCFG_ICR0_AUTO_ADDR_DONE_INT_CLR_MASK                                    0x08000000
#define AFE_SYSCFG_ICR0_AUTO_ADDR_DONE_INT_CLR_SET(n)                                  (((uint32_t)(n) << 27 ) & 0x08000000)
#define AFE_SYSCFG_ICR0_AUTO_ADDR_DONE_INT_CLR_CLR                                     0xF7FFFFFF

#define AFE_SYSCFG_ICR0_SLV_SELECTED_INT_CLR_SHIFT                                     26
#define AFE_SYSCFG_ICR0_SLV_SELECTED_INT_CLR_MASK                                      0x04000000
#define AFE_SYSCFG_ICR0_SLV_SELECTED_INT_CLR_SET(n)                                    (((uint32_t)(n) << 26 ) & 0x04000000)
#define AFE_SYSCFG_ICR0_SLV_SELECTED_INT_CLR_CLR                                       0xFBFFFFFF

#define AFE_SYSCFG_ICR0_TX_RX_CONF_INT_CLR_SHIFT                                       25
#define AFE_SYSCFG_ICR0_TX_RX_CONF_INT_CLR_MASK                                        0x02000000
#define AFE_SYSCFG_ICR0_TX_RX_CONF_INT_CLR_SET(n)                                      (((uint32_t)(n) << 25 ) & 0x02000000)
#define AFE_SYSCFG_ICR0_TX_RX_CONF_INT_CLR_CLR                                         0xFDFFFFFF

#define AFE_SYSCFG_ICR0_TX_PID_DONE_INT_CLR_SHIFT                                      24
#define AFE_SYSCFG_ICR0_TX_PID_DONE_INT_CLR_MASK                                       0x01000000
#define AFE_SYSCFG_ICR0_TX_PID_DONE_INT_CLR_SET(n)                                     (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_SYSCFG_ICR0_TX_PID_DONE_INT_CLR_CLR                                        0xFEFFFFFF

#define AFE_SYSCFG_ICR0_RX_TIMEOUT_INT_CLR_SHIFT                                       23
#define AFE_SYSCFG_ICR0_RX_TIMEOUT_INT_CLR_MASK                                        0x00800000
#define AFE_SYSCFG_ICR0_RX_TIMEOUT_INT_CLR_SET(n)                                      (((uint32_t)(n) << 23 ) & 0x00800000)
#define AFE_SYSCFG_ICR0_RX_TIMEOUT_INT_CLR_CLR                                         0xFF7FFFFF

#define AFE_SYSCFG_ICR0_SYNC_VAL_ERR_INT_CLR_SHIFT                                     22
#define AFE_SYSCFG_ICR0_SYNC_VAL_ERR_INT_CLR_MASK                                      0x00400000
#define AFE_SYSCFG_ICR0_SYNC_VAL_ERR_INT_CLR_SET(n)                                    (((uint32_t)(n) << 22 ) & 0x00400000)
#define AFE_SYSCFG_ICR0_SYNC_VAL_ERR_INT_CLR_CLR                                       0xFFBFFFFF

#define AFE_SYSCFG_ICR0_SYNC_DET_INT_CLR_SHIFT                                         21
#define AFE_SYSCFG_ICR0_SYNC_DET_INT_CLR_MASK                                          0x00200000
#define AFE_SYSCFG_ICR0_SYNC_DET_INT_CLR_SET(n)                                        (((uint32_t)(n) << 21 ) & 0x00200000)
#define AFE_SYSCFG_ICR0_SYNC_DET_INT_CLR_CLR                                           0xFFDFFFFF

#define AFE_SYSCFG_ICR0_BRK_DET_INT_CLR_SHIFT                                          20
#define AFE_SYSCFG_ICR0_BRK_DET_INT_CLR_MASK                                           0x00100000
#define AFE_SYSCFG_ICR0_BRK_DET_INT_CLR_SET(n)                                         (((uint32_t)(n) << 20 ) & 0x00100000)
#define AFE_SYSCFG_ICR0_BRK_DET_INT_CLR_CLR                                            0xFFEFFFFF

#define AFE_SYSCFG_ICR0_TX_COL_DET_ERR_INT_CLR_SHIFT                                   19
#define AFE_SYSCFG_ICR0_TX_COL_DET_ERR_INT_CLR_MASK                                    0x00080000
#define AFE_SYSCFG_ICR0_TX_COL_DET_ERR_INT_CLR_SET(n)                                  (((uint32_t)(n) << 19 ) & 0x00080000)
#define AFE_SYSCFG_ICR0_TX_COL_DET_ERR_INT_CLR_CLR                                     0xFFF7FFFF

#define AFE_SYSCFG_ICR0_TX_FIFO_EMPTY_INT_CLR_SHIFT                                    18
#define AFE_SYSCFG_ICR0_TX_FIFO_EMPTY_INT_CLR_MASK                                     0x00040000
#define AFE_SYSCFG_ICR0_TX_FIFO_EMPTY_INT_CLR_SET(n)                                   (((uint32_t)(n) << 18 ) & 0x00040000)
#define AFE_SYSCFG_ICR0_TX_FIFO_EMPTY_INT_CLR_CLR                                      0xFFFBFFFF

#define AFE_SYSCFG_ICR0_TX_DONE_INT_CLR_SHIFT                                          17
#define AFE_SYSCFG_ICR0_TX_DONE_INT_CLR_MASK                                           0x00020000
#define AFE_SYSCFG_ICR0_TX_DONE_INT_CLR_SET(n)                                         (((uint32_t)(n) << 17 ) & 0x00020000)
#define AFE_SYSCFG_ICR0_TX_DONE_INT_CLR_CLR                                            0xFFFDFFFF

#define AFE_SYSCFG_ICR0_RX_FIFO_OVF_ERR_INT_CLR_SHIFT                                  16
#define AFE_SYSCFG_ICR0_RX_FIFO_OVF_ERR_INT_CLR_MASK                                   0x00010000
#define AFE_SYSCFG_ICR0_RX_FIFO_OVF_ERR_INT_CLR_SET(n)                                 (((uint32_t)(n) << 16 ) & 0x00010000)
#define AFE_SYSCFG_ICR0_RX_FIFO_OVF_ERR_INT_CLR_CLR                                    0xFFFEFFFF

#define AFE_SYSCFG_ICR0_RX_FIFO_FULL_INT_CLR_SHIFT                                     15
#define AFE_SYSCFG_ICR0_RX_FIFO_FULL_INT_CLR_MASK                                      0x00008000
#define AFE_SYSCFG_ICR0_RX_FIFO_FULL_INT_CLR_SET(n)                                    (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_SYSCFG_ICR0_RX_FIFO_FULL_INT_CLR_CLR                                       0xFFFF7FFF

#define AFE_SYSCFG_ICR0_RX_STP_ERR_INT_CLR_SHIFT                                       14
#define AFE_SYSCFG_ICR0_RX_STP_ERR_INT_CLR_MASK                                        0x00004000
#define AFE_SYSCFG_ICR0_RX_STP_ERR_INT_CLR_SET(n)                                      (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_SYSCFG_ICR0_RX_STP_ERR_INT_CLR_CLR                                         0xFFFFBFFF

#define AFE_SYSCFG_ICR0_RX_CHKSUM_ERR_INT_CLR_SHIFT                                    13
#define AFE_SYSCFG_ICR0_RX_CHKSUM_ERR_INT_CLR_MASK                                     0x00002000
#define AFE_SYSCFG_ICR0_RX_CHKSUM_ERR_INT_CLR_SET(n)                                   (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_ICR0_RX_CHKSUM_ERR_INT_CLR_CLR                                      0xFFFFDFFF

#define AFE_SYSCFG_ICR0_RX_PTY_CHK_ERR_INT_CLR_SHIFT                                   12
#define AFE_SYSCFG_ICR0_RX_PTY_CHK_ERR_INT_CLR_MASK                                    0x00001000
#define AFE_SYSCFG_ICR0_RX_PTY_CHK_ERR_INT_CLR_SET(n)                                  (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_ICR0_RX_PTY_CHK_ERR_INT_CLR_CLR                                     0xFFFFEFFF

#define AFE_SYSCFG_ICR0_RX_PID_DONE_INT_CLR_SHIFT                                      11
#define AFE_SYSCFG_ICR0_RX_PID_DONE_INT_CLR_MASK                                       0x00000800
#define AFE_SYSCFG_ICR0_RX_PID_DONE_INT_CLR_SET(n)                                     (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_ICR0_RX_PID_DONE_INT_CLR_CLR                                        0xFFFFF7FF

#define AFE_SYSCFG_ICR0_RX_DONE_INT_CLR_SHIFT                                          10
#define AFE_SYSCFG_ICR0_RX_DONE_INT_CLR_MASK                                           0x00000400
#define AFE_SYSCFG_ICR0_RX_DONE_INT_CLR_SET(n)                                         (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_ICR0_RX_DONE_INT_CLR_CLR                                            0xFFFFFBFF

#define AFE_SYSCFG_ICR0_RX_1BYTE_DONE_INT_CLR_SHIFT                                    9
#define AFE_SYSCFG_ICR0_RX_1BYTE_DONE_INT_CLR_MASK                                     0x00000200
#define AFE_SYSCFG_ICR0_RX_1BYTE_DONE_INT_CLR_SET(n)                                   (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_ICR0_RX_1BYTE_DONE_INT_CLR_CLR                                      0xFFFFFDFF

#define AFE_SYSCFG_ICR0_CH2_PWM_CLR_INT_CLR_SHIFT                                      8
#define AFE_SYSCFG_ICR0_CH2_PWM_CLR_INT_CLR_MASK                                       0x00000100
#define AFE_SYSCFG_ICR0_CH2_PWM_CLR_INT_CLR_SET(n)                                     (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_ICR0_CH2_PWM_CLR_INT_CLR_CLR                                        0xFFFFFEFF

#define AFE_SYSCFG_ICR0_CH2_PWM_SET_INT_CLR_SHIFT                                      7
#define AFE_SYSCFG_ICR0_CH2_PWM_SET_INT_CLR_MASK                                       0x00000080
#define AFE_SYSCFG_ICR0_CH2_PWM_SET_INT_CLR_SET(n)                                     (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_ICR0_CH2_PWM_SET_INT_CLR_CLR                                        0xFFFFFF7F

#define AFE_SYSCFG_ICR0_CH2_CNT_MAX_INT_CLR_SHIFT                                      6
#define AFE_SYSCFG_ICR0_CH2_CNT_MAX_INT_CLR_MASK                                       0x00000040
#define AFE_SYSCFG_ICR0_CH2_CNT_MAX_INT_CLR_SET(n)                                     (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_ICR0_CH2_CNT_MAX_INT_CLR_CLR                                        0xFFFFFFBF

#define AFE_SYSCFG_ICR0_CH1_PWM_CLR_INT_CLR_SHIFT                                      5
#define AFE_SYSCFG_ICR0_CH1_PWM_CLR_INT_CLR_MASK                                       0x00000020
#define AFE_SYSCFG_ICR0_CH1_PWM_CLR_INT_CLR_SET(n)                                     (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_ICR0_CH1_PWM_CLR_INT_CLR_CLR                                        0xFFFFFFDF

#define AFE_SYSCFG_ICR0_CH1_PWM_SET_INT_CLR_SHIFT                                      4
#define AFE_SYSCFG_ICR0_CH1_PWM_SET_INT_CLR_MASK                                       0x00000010
#define AFE_SYSCFG_ICR0_CH1_PWM_SET_INT_CLR_SET(n)                                     (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_ICR0_CH1_PWM_SET_INT_CLR_CLR                                        0xFFFFFFEF

#define AFE_SYSCFG_ICR0_CH1_CNT_MAX_INT_CLR_SHIFT                                      3
#define AFE_SYSCFG_ICR0_CH1_CNT_MAX_INT_CLR_MASK                                       0x00000008
#define AFE_SYSCFG_ICR0_CH1_CNT_MAX_INT_CLR_SET(n)                                     (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_ICR0_CH1_CNT_MAX_INT_CLR_CLR                                        0xFFFFFFF7

#define AFE_SYSCFG_ICR0_CH0_PWM_CLR_INT_CLR_SHIFT                                      2
#define AFE_SYSCFG_ICR0_CH0_PWM_CLR_INT_CLR_MASK                                       0x00000004
#define AFE_SYSCFG_ICR0_CH0_PWM_CLR_INT_CLR_SET(n)                                     (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_ICR0_CH0_PWM_CLR_INT_CLR_CLR                                        0xFFFFFFFB

#define AFE_SYSCFG_ICR0_CH0_PWM_SET_INT_CLR_SHIFT                                      1
#define AFE_SYSCFG_ICR0_CH0_PWM_SET_INT_CLR_MASK                                       0x00000002
#define AFE_SYSCFG_ICR0_CH0_PWM_SET_INT_CLR_SET(n)                                     (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_ICR0_CH0_PWM_SET_INT_CLR_CLR                                        0xFFFFFFFD

#define AFE_SYSCFG_ICR0_CH0_CNT_MAX_INT_CLR_SHIFT                                      0
#define AFE_SYSCFG_ICR0_CH0_CNT_MAX_INT_CLR_MASK                                       0x00000001
#define AFE_SYSCFG_ICR0_CH0_CNT_MAX_INT_CLR_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_ICR0_CH0_CNT_MAX_INT_CLR_CLR                                        0xFFFFFFFE

#define AFE_SYSCFG_ISR0_VS_LVD_INT_STATUS_SHIFT                                        31
#define AFE_SYSCFG_ISR0_VS_LVD_INT_STATUS_MASK                                         0x80000000
#define AFE_SYSCFG_ISR0_VS_LVD_INT_STATUS_SET(n)                                       (((uint32_t)(n) << 31 ) & 0x80000000)
#define AFE_SYSCFG_ISR0_VS_LVD_INT_STATUS_CLR                                          0x7FFFFFFF

#define AFE_SYSCFG_ISR0_OTP_INT_STATUS_SHIFT                                           30
#define AFE_SYSCFG_ISR0_OTP_INT_STATUS_MASK                                            0x40000000
#define AFE_SYSCFG_ISR0_OTP_INT_STATUS_SET(n)                                          (((uint32_t)(n) << 30 ) & 0x40000000)
#define AFE_SYSCFG_ISR0_OTP_INT_STATUS_CLR                                             0xBFFFFFFF

#define AFE_SYSCFG_ISR0_ADC_DONE_INT_STATUS_SHIFT                                      29
#define AFE_SYSCFG_ISR0_ADC_DONE_INT_STATUS_MASK                                       0x20000000
#define AFE_SYSCFG_ISR0_ADC_DONE_INT_STATUS_SET(n)                                     (((uint32_t)(n) << 29 ) & 0x20000000)
#define AFE_SYSCFG_ISR0_ADC_DONE_INT_STATUS_CLR                                        0xDFFFFFFF

#define AFE_SYSCFG_ISR0_TX_1BYTE_DONE_INT_STATUS_SHIFT                                 28
#define AFE_SYSCFG_ISR0_TX_1BYTE_DONE_INT_STATUS_MASK                                  0x10000000
#define AFE_SYSCFG_ISR0_TX_1BYTE_DONE_INT_STATUS_SET(n)                                (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_SYSCFG_ISR0_TX_1BYTE_DONE_INT_STATUS_CLR                                   0xEFFFFFFF

#define AFE_SYSCFG_ISR0_AUTO_ADDR_DONE_INT_STATUS_SHIFT                                27
#define AFE_SYSCFG_ISR0_AUTO_ADDR_DONE_INT_STATUS_MASK                                 0x08000000
#define AFE_SYSCFG_ISR0_AUTO_ADDR_DONE_INT_STATUS_SET(n)                               (((uint32_t)(n) << 27 ) & 0x08000000)
#define AFE_SYSCFG_ISR0_AUTO_ADDR_DONE_INT_STATUS_CLR                                  0xF7FFFFFF

#define AFE_SYSCFG_ISR0_SLV_SELECTED_INT_STATUS_SHIFT                                  26
#define AFE_SYSCFG_ISR0_SLV_SELECTED_INT_STATUS_MASK                                   0x04000000
#define AFE_SYSCFG_ISR0_SLV_SELECTED_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 26 ) & 0x04000000)
#define AFE_SYSCFG_ISR0_SLV_SELECTED_INT_STATUS_CLR                                    0xFBFFFFFF

#define AFE_SYSCFG_ISR0_TX_RX_CONF_INT_STATUS_SHIFT                                    25
#define AFE_SYSCFG_ISR0_TX_RX_CONF_INT_STATUS_MASK                                     0x02000000
#define AFE_SYSCFG_ISR0_TX_RX_CONF_INT_STATUS_SET(n)                                   (((uint32_t)(n) << 25 ) & 0x02000000)
#define AFE_SYSCFG_ISR0_TX_RX_CONF_INT_STATUS_CLR                                      0xFDFFFFFF

#define AFE_SYSCFG_ISR0_TX_PID_DONE_INT_STATUS_SHIFT                                   24
#define AFE_SYSCFG_ISR0_TX_PID_DONE_INT_STATUS_MASK                                    0x01000000
#define AFE_SYSCFG_ISR0_TX_PID_DONE_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_SYSCFG_ISR0_TX_PID_DONE_INT_STATUS_CLR                                     0xFEFFFFFF

#define AFE_SYSCFG_ISR0_RX_TIMEOUT_INT_STATUS_SHIFT                                    23
#define AFE_SYSCFG_ISR0_RX_TIMEOUT_INT_STATUS_MASK                                     0x00800000
#define AFE_SYSCFG_ISR0_RX_TIMEOUT_INT_STATUS_SET(n)                                   (((uint32_t)(n) << 23 ) & 0x00800000)
#define AFE_SYSCFG_ISR0_RX_TIMEOUT_INT_STATUS_CLR                                      0xFF7FFFFF

#define AFE_SYSCFG_ISR0_SYNC_VAL_ERR_INT_STATUS_SHIFT                                  22
#define AFE_SYSCFG_ISR0_SYNC_VAL_ERR_INT_STATUS_MASK                                   0x00400000
#define AFE_SYSCFG_ISR0_SYNC_VAL_ERR_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 22 ) & 0x00400000)
#define AFE_SYSCFG_ISR0_SYNC_VAL_ERR_INT_STATUS_CLR                                    0xFFBFFFFF

#define AFE_SYSCFG_ISR0_SYNC_DET_INT_STATUS_SHIFT                                      21
#define AFE_SYSCFG_ISR0_SYNC_DET_INT_STATUS_MASK                                       0x00200000
#define AFE_SYSCFG_ISR0_SYNC_DET_INT_STATUS_SET(n)                                     (((uint32_t)(n) << 21 ) & 0x00200000)
#define AFE_SYSCFG_ISR0_SYNC_DET_INT_STATUS_CLR                                        0xFFDFFFFF

#define AFE_SYSCFG_ISR0_BRK_DET_INT_STATUS_SHIFT                                       20
#define AFE_SYSCFG_ISR0_BRK_DET_INT_STATUS_MASK                                        0x00100000
#define AFE_SYSCFG_ISR0_BRK_DET_INT_STATUS_SET(n)                                      (((uint32_t)(n) << 20 ) & 0x00100000)
#define AFE_SYSCFG_ISR0_BRK_DET_INT_STATUS_CLR                                         0xFFEFFFFF

#define AFE_SYSCFG_ISR0_TX_COL_DET_ERR_INT_STATUS_SHIFT                                19
#define AFE_SYSCFG_ISR0_TX_COL_DET_ERR_INT_STATUS_MASK                                 0x00080000
#define AFE_SYSCFG_ISR0_TX_COL_DET_ERR_INT_STATUS_SET(n)                               (((uint32_t)(n) << 19 ) & 0x00080000)
#define AFE_SYSCFG_ISR0_TX_COL_DET_ERR_INT_STATUS_CLR                                  0xFFF7FFFF

#define AFE_SYSCFG_ISR0_TX_FIFO_EMPTY_INT_STATUS_SHIFT                                 18
#define AFE_SYSCFG_ISR0_TX_FIFO_EMPTY_INT_STATUS_MASK                                  0x00040000
#define AFE_SYSCFG_ISR0_TX_FIFO_EMPTY_INT_STATUS_SET(n)                                (((uint32_t)(n) << 18 ) & 0x00040000)
#define AFE_SYSCFG_ISR0_TX_FIFO_EMPTY_INT_STATUS_CLR                                   0xFFFBFFFF

#define AFE_SYSCFG_ISR0_TX_DONE_INT_STATUS_SHIFT                                       17
#define AFE_SYSCFG_ISR0_TX_DONE_INT_STATUS_MASK                                        0x00020000
#define AFE_SYSCFG_ISR0_TX_DONE_INT_STATUS_SET(n)                                      (((uint32_t)(n) << 17 ) & 0x00020000)
#define AFE_SYSCFG_ISR0_TX_DONE_INT_STATUS_CLR                                         0xFFFDFFFF

#define AFE_SYSCFG_ISR0_RX_FIFO_OVF_ERR_INT_STATUS_SHIFT                               16
#define AFE_SYSCFG_ISR0_RX_FIFO_OVF_ERR_INT_STATUS_MASK                                0x00010000
#define AFE_SYSCFG_ISR0_RX_FIFO_OVF_ERR_INT_STATUS_SET(n)                              (((uint32_t)(n) << 16 ) & 0x00010000)
#define AFE_SYSCFG_ISR0_RX_FIFO_OVF_ERR_INT_STATUS_CLR                                 0xFFFEFFFF

#define AFE_SYSCFG_ISR0_RX_FIFO_FULL_INT_STATUS_SHIFT                                  15
#define AFE_SYSCFG_ISR0_RX_FIFO_FULL_INT_STATUS_MASK                                   0x00008000
#define AFE_SYSCFG_ISR0_RX_FIFO_FULL_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_SYSCFG_ISR0_RX_FIFO_FULL_INT_STATUS_CLR                                    0xFFFF7FFF

#define AFE_SYSCFG_ISR0_RX_STP_ERR_INT_STATUS_SHIFT                                    14
#define AFE_SYSCFG_ISR0_RX_STP_ERR_INT_STATUS_MASK                                     0x00004000
#define AFE_SYSCFG_ISR0_RX_STP_ERR_INT_STATUS_SET(n)                                   (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_SYSCFG_ISR0_RX_STP_ERR_INT_STATUS_CLR                                      0xFFFFBFFF

#define AFE_SYSCFG_ISR0_RX_CHKSUM_ERR_INT_STATUS_SHIFT                                 13
#define AFE_SYSCFG_ISR0_RX_CHKSUM_ERR_INT_STATUS_MASK                                  0x00002000
#define AFE_SYSCFG_ISR0_RX_CHKSUM_ERR_INT_STATUS_SET(n)                                (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_ISR0_RX_CHKSUM_ERR_INT_STATUS_CLR                                   0xFFFFDFFF

#define AFE_SYSCFG_ISR0_RX_PTY_CHK_ERR_INT_STATUS_SHIFT                                12
#define AFE_SYSCFG_ISR0_RX_PTY_CHK_ERR_INT_STATUS_MASK                                 0x00001000
#define AFE_SYSCFG_ISR0_RX_PTY_CHK_ERR_INT_STATUS_SET(n)                               (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_ISR0_RX_PTY_CHK_ERR_INT_STATUS_CLR                                  0xFFFFEFFF

#define AFE_SYSCFG_ISR0_RX_PID_DONE_INT_STATUS_SHIFT                                   11
#define AFE_SYSCFG_ISR0_RX_PID_DONE_INT_STATUS_MASK                                    0x00000800
#define AFE_SYSCFG_ISR0_RX_PID_DONE_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_ISR0_RX_PID_DONE_INT_STATUS_CLR                                     0xFFFFF7FF

#define AFE_SYSCFG_ISR0_RX_DONE_INT_STATUS_SHIFT                                       10
#define AFE_SYSCFG_ISR0_RX_DONE_INT_STATUS_MASK                                        0x00000400
#define AFE_SYSCFG_ISR0_RX_DONE_INT_STATUS_SET(n)                                      (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_ISR0_RX_DONE_INT_STATUS_CLR                                         0xFFFFFBFF

#define AFE_SYSCFG_ISR0_RX_1BYTE_DONE_INT_STATUS_SHIFT                                 9
#define AFE_SYSCFG_ISR0_RX_1BYTE_DONE_INT_STATUS_MASK                                  0x00000200
#define AFE_SYSCFG_ISR0_RX_1BYTE_DONE_INT_STATUS_SET(n)                                (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_ISR0_RX_1BYTE_DONE_INT_STATUS_CLR                                   0xFFFFFDFF

#define AFE_SYSCFG_ISR0_CH2_PWM_CLR_INT_STATUS_SHIFT                                   8
#define AFE_SYSCFG_ISR0_CH2_PWM_CLR_INT_STATUS_MASK                                    0x00000100
#define AFE_SYSCFG_ISR0_CH2_PWM_CLR_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_ISR0_CH2_PWM_CLR_INT_STATUS_CLR                                     0xFFFFFEFF

#define AFE_SYSCFG_ISR0_CH2_PWM_SET_INT_STATUS_SHIFT                                   7
#define AFE_SYSCFG_ISR0_CH2_PWM_SET_INT_STATUS_MASK                                    0x00000080
#define AFE_SYSCFG_ISR0_CH2_PWM_SET_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_ISR0_CH2_PWM_SET_INT_STATUS_CLR                                     0xFFFFFF7F

#define AFE_SYSCFG_ISR0_CH2_CNT_MAX_INT_STATUS_SHIFT                                   6
#define AFE_SYSCFG_ISR0_CH2_CNT_MAX_INT_STATUS_MASK                                    0x00000040
#define AFE_SYSCFG_ISR0_CH2_CNT_MAX_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_ISR0_CH2_CNT_MAX_INT_STATUS_CLR                                     0xFFFFFFBF

#define AFE_SYSCFG_ISR0_CH1_PWM_CLR_INT_STATUS_SHIFT                                   5
#define AFE_SYSCFG_ISR0_CH1_PWM_CLR_INT_STATUS_MASK                                    0x00000020
#define AFE_SYSCFG_ISR0_CH1_PWM_CLR_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_ISR0_CH1_PWM_CLR_INT_STATUS_CLR                                     0xFFFFFFDF

#define AFE_SYSCFG_ISR0_CH1_PWM_SET_INT_STATUS_SHIFT                                   4
#define AFE_SYSCFG_ISR0_CH1_PWM_SET_INT_STATUS_MASK                                    0x00000010
#define AFE_SYSCFG_ISR0_CH1_PWM_SET_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_ISR0_CH1_PWM_SET_INT_STATUS_CLR                                     0xFFFFFFEF

#define AFE_SYSCFG_ISR0_CH1_CNT_MAX_INT_STATUS_SHIFT                                   3
#define AFE_SYSCFG_ISR0_CH1_CNT_MAX_INT_STATUS_MASK                                    0x00000008
#define AFE_SYSCFG_ISR0_CH1_CNT_MAX_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_ISR0_CH1_CNT_MAX_INT_STATUS_CLR                                     0xFFFFFFF7

#define AFE_SYSCFG_ISR0_CH0_PWM_CLR_INT_STATUS_SHIFT                                   2
#define AFE_SYSCFG_ISR0_CH0_PWM_CLR_INT_STATUS_MASK                                    0x00000004
#define AFE_SYSCFG_ISR0_CH0_PWM_CLR_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_ISR0_CH0_PWM_CLR_INT_STATUS_CLR                                     0xFFFFFFFB

#define AFE_SYSCFG_ISR0_CH0_PWM_SET_INT_STATUS_SHIFT                                   1
#define AFE_SYSCFG_ISR0_CH0_PWM_SET_INT_STATUS_MASK                                    0x00000002
#define AFE_SYSCFG_ISR0_CH0_PWM_SET_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_ISR0_CH0_PWM_SET_INT_STATUS_CLR                                     0xFFFFFFFD

#define AFE_SYSCFG_ISR0_CH0_CNT_MAX_INT_STATUS_SHIFT                                   0
#define AFE_SYSCFG_ISR0_CH0_CNT_MAX_INT_STATUS_MASK                                    0x00000001
#define AFE_SYSCFG_ISR0_CH0_CNT_MAX_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_ISR0_CH0_CNT_MAX_INT_STATUS_CLR                                     0xFFFFFFFE

#define AFE_SYSCFG_IRSR0_VS_LVD_INT_RAW_STATUS_SHIFT                                   31
#define AFE_SYSCFG_IRSR0_VS_LVD_INT_RAW_STATUS_MASK                                    0x80000000
#define AFE_SYSCFG_IRSR0_VS_LVD_INT_RAW_STATUS_SET(n)                                  (((uint32_t)(n) << 31 ) & 0x80000000)
#define AFE_SYSCFG_IRSR0_VS_LVD_INT_RAW_STATUS_CLR                                     0x7FFFFFFF

#define AFE_SYSCFG_IRSR0_OTP_INT_RAW_STATUS_SHIFT                                      30
#define AFE_SYSCFG_IRSR0_OTP_INT_RAW_STATUS_MASK                                       0x40000000
#define AFE_SYSCFG_IRSR0_OTP_INT_RAW_STATUS_SET(n)                                     (((uint32_t)(n) << 30 ) & 0x40000000)
#define AFE_SYSCFG_IRSR0_OTP_INT_RAW_STATUS_CLR                                        0xBFFFFFFF

#define AFE_SYSCFG_IRSR0_ADC_DONE_INT_RAW_STATUS_SHIFT                                 29
#define AFE_SYSCFG_IRSR0_ADC_DONE_INT_RAW_STATUS_MASK                                  0x20000000
#define AFE_SYSCFG_IRSR0_ADC_DONE_INT_RAW_STATUS_SET(n)                                (((uint32_t)(n) << 29 ) & 0x20000000)
#define AFE_SYSCFG_IRSR0_ADC_DONE_INT_RAW_STATUS_CLR                                   0xDFFFFFFF

#define AFE_SYSCFG_IRSR0_TX_1BYTE_DONE_INT_RAW_STATUS_SHIFT                            28
#define AFE_SYSCFG_IRSR0_TX_1BYTE_DONE_INT_RAW_STATUS_MASK                             0x10000000
#define AFE_SYSCFG_IRSR0_TX_1BYTE_DONE_INT_RAW_STATUS_SET(n)                           (((uint32_t)(n) << 28 ) & 0x10000000)
#define AFE_SYSCFG_IRSR0_TX_1BYTE_DONE_INT_RAW_STATUS_CLR                              0xEFFFFFFF

#define AFE_SYSCFG_IRSR0_AUTO_ADDR_DONE_INT_RAW_STATUS_SHIFT                           27
#define AFE_SYSCFG_IRSR0_AUTO_ADDR_DONE_INT_RAW_STATUS_MASK                            0x08000000
#define AFE_SYSCFG_IRSR0_AUTO_ADDR_DONE_INT_RAW_STATUS_SET(n)                          (((uint32_t)(n) << 27 ) & 0x08000000)
#define AFE_SYSCFG_IRSR0_AUTO_ADDR_DONE_INT_RAW_STATUS_CLR                             0xF7FFFFFF

#define AFE_SYSCFG_IRSR0_SLV_SELECTED_INT_RAW_STATUS_SHIFT                             26
#define AFE_SYSCFG_IRSR0_SLV_SELECTED_INT_RAW_STATUS_MASK                              0x04000000
#define AFE_SYSCFG_IRSR0_SLV_SELECTED_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 26 ) & 0x04000000)
#define AFE_SYSCFG_IRSR0_SLV_SELECTED_INT_RAW_STATUS_CLR                               0xFBFFFFFF

#define AFE_SYSCFG_IRSR0_TX_RX_CONF_INT_RAW_STATUS_SHIFT                               25
#define AFE_SYSCFG_IRSR0_TX_RX_CONF_INT_RAW_STATUS_MASK                                0x02000000
#define AFE_SYSCFG_IRSR0_TX_RX_CONF_INT_RAW_STATUS_SET(n)                              (((uint32_t)(n) << 25 ) & 0x02000000)
#define AFE_SYSCFG_IRSR0_TX_RX_CONF_INT_RAW_STATUS_CLR                                 0xFDFFFFFF

#define AFE_SYSCFG_IRSR0_TX_PID_DONE_INT_RAW_STATUS_SHIFT                              24
#define AFE_SYSCFG_IRSR0_TX_PID_DONE_INT_RAW_STATUS_MASK                               0x01000000
#define AFE_SYSCFG_IRSR0_TX_PID_DONE_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 24 ) & 0x01000000)
#define AFE_SYSCFG_IRSR0_TX_PID_DONE_INT_RAW_STATUS_CLR                                0xFEFFFFFF

#define AFE_SYSCFG_IRSR0_RX_TIMEOUT_INT_RAW_STATUS_SHIFT                               23
#define AFE_SYSCFG_IRSR0_RX_TIMEOUT_INT_RAW_STATUS_MASK                                0x00800000
#define AFE_SYSCFG_IRSR0_RX_TIMEOUT_INT_RAW_STATUS_SET(n)                              (((uint32_t)(n) << 23 ) & 0x00800000)
#define AFE_SYSCFG_IRSR0_RX_TIMEOUT_INT_RAW_STATUS_CLR                                 0xFF7FFFFF

#define AFE_SYSCFG_IRSR0_SYNC_VAL_ERR_INT_RAW_STATUS_SHIFT                             22
#define AFE_SYSCFG_IRSR0_SYNC_VAL_ERR_INT_RAW_STATUS_MASK                              0x00400000
#define AFE_SYSCFG_IRSR0_SYNC_VAL_ERR_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 22 ) & 0x00400000)
#define AFE_SYSCFG_IRSR0_SYNC_VAL_ERR_INT_RAW_STATUS_CLR                               0xFFBFFFFF

#define AFE_SYSCFG_IRSR0_SYNC_DET_INT_RAW_STATUS_SHIFT                                 21
#define AFE_SYSCFG_IRSR0_SYNC_DET_INT_RAW_STATUS_MASK                                  0x00200000
#define AFE_SYSCFG_IRSR0_SYNC_DET_INT_RAW_STATUS_SET(n)                                (((uint32_t)(n) << 21 ) & 0x00200000)
#define AFE_SYSCFG_IRSR0_SYNC_DET_INT_RAW_STATUS_CLR                                   0xFFDFFFFF

#define AFE_SYSCFG_IRSR0_BRK_DET_INT_RAW_STATUS_SHIFT                                  20
#define AFE_SYSCFG_IRSR0_BRK_DET_INT_RAW_STATUS_MASK                                   0x00100000
#define AFE_SYSCFG_IRSR0_BRK_DET_INT_RAW_STATUS_SET(n)                                 (((uint32_t)(n) << 20 ) & 0x00100000)
#define AFE_SYSCFG_IRSR0_BRK_DET_INT_RAW_STATUS_CLR                                    0xFFEFFFFF

#define AFE_SYSCFG_IRSR0_TX_COL_DET_ERR_INT_RAW_STATUS_SHIFT                           19
#define AFE_SYSCFG_IRSR0_TX_COL_DET_ERR_INT_RAW_STATUS_MASK                            0x00080000
#define AFE_SYSCFG_IRSR0_TX_COL_DET_ERR_INT_RAW_STATUS_SET(n)                          (((uint32_t)(n) << 19 ) & 0x00080000)
#define AFE_SYSCFG_IRSR0_TX_COL_DET_ERR_INT_RAW_STATUS_CLR                             0xFFF7FFFF

#define AFE_SYSCFG_IRSR0_TX_FIFO_EMPTY_INT_RAW_STATUS_SHIFT                            18
#define AFE_SYSCFG_IRSR0_TX_FIFO_EMPTY_INT_RAW_STATUS_MASK                             0x00040000
#define AFE_SYSCFG_IRSR0_TX_FIFO_EMPTY_INT_RAW_STATUS_SET(n)                           (((uint32_t)(n) << 18 ) & 0x00040000)
#define AFE_SYSCFG_IRSR0_TX_FIFO_EMPTY_INT_RAW_STATUS_CLR                              0xFFFBFFFF

#define AFE_SYSCFG_IRSR0_TX_DONE_INT_RAW_STATUS_SHIFT                                  17
#define AFE_SYSCFG_IRSR0_TX_DONE_INT_RAW_STATUS_MASK                                   0x00020000
#define AFE_SYSCFG_IRSR0_TX_DONE_INT_RAW_STATUS_SET(n)                                 (((uint32_t)(n) << 17 ) & 0x00020000)
#define AFE_SYSCFG_IRSR0_TX_DONE_INT_RAW_STATUS_CLR                                    0xFFFDFFFF

#define AFE_SYSCFG_IRSR0_RX_FIFO_OVF_ERR_INT_RAW_STATUS_SHIFT                          16
#define AFE_SYSCFG_IRSR0_RX_FIFO_OVF_ERR_INT_RAW_STATUS_MASK                           0x00010000
#define AFE_SYSCFG_IRSR0_RX_FIFO_OVF_ERR_INT_RAW_STATUS_SET(n)                         (((uint32_t)(n) << 16 ) & 0x00010000)
#define AFE_SYSCFG_IRSR0_RX_FIFO_OVF_ERR_INT_RAW_STATUS_CLR                            0xFFFEFFFF

#define AFE_SYSCFG_IRSR0_RX_FIFO_FULL_INT_RAW_STATUS_SHIFT                             15
#define AFE_SYSCFG_IRSR0_RX_FIFO_FULL_INT_RAW_STATUS_MASK                              0x00008000
#define AFE_SYSCFG_IRSR0_RX_FIFO_FULL_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 15 ) & 0x00008000)
#define AFE_SYSCFG_IRSR0_RX_FIFO_FULL_INT_RAW_STATUS_CLR                               0xFFFF7FFF

#define AFE_SYSCFG_IRSR0_RX_STP_ERR_INT_RAW_STATUS_SHIFT                               14
#define AFE_SYSCFG_IRSR0_RX_STP_ERR_INT_RAW_STATUS_MASK                                0x00004000
#define AFE_SYSCFG_IRSR0_RX_STP_ERR_INT_RAW_STATUS_SET(n)                              (((uint32_t)(n) << 14 ) & 0x00004000)
#define AFE_SYSCFG_IRSR0_RX_STP_ERR_INT_RAW_STATUS_CLR                                 0xFFFFBFFF

#define AFE_SYSCFG_IRSR0_RX_CHKSUM_ERR_INT_RAW_STATUS_SHIFT                            13
#define AFE_SYSCFG_IRSR0_RX_CHKSUM_ERR_INT_RAW_STATUS_MASK                             0x00002000
#define AFE_SYSCFG_IRSR0_RX_CHKSUM_ERR_INT_RAW_STATUS_SET(n)                           (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_IRSR0_RX_CHKSUM_ERR_INT_RAW_STATUS_CLR                              0xFFFFDFFF

#define AFE_SYSCFG_IRSR0_RX_PTY_CHK_ERR_INT_RAW_STATUS_SHIFT                           12
#define AFE_SYSCFG_IRSR0_RX_PTY_CHK_ERR_INT_RAW_STATUS_MASK                            0x00001000
#define AFE_SYSCFG_IRSR0_RX_PTY_CHK_ERR_INT_RAW_STATUS_SET(n)                          (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_IRSR0_RX_PTY_CHK_ERR_INT_RAW_STATUS_CLR                             0xFFFFEFFF

#define AFE_SYSCFG_IRSR0_RX_PID_DONE_INT_RAW_STATUS_SHIFT                              11
#define AFE_SYSCFG_IRSR0_RX_PID_DONE_INT_RAW_STATUS_MASK                               0x00000800
#define AFE_SYSCFG_IRSR0_RX_PID_DONE_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_IRSR0_RX_PID_DONE_INT_RAW_STATUS_CLR                                0xFFFFF7FF

#define AFE_SYSCFG_IRSR0_RX_DONE_INT_RAW_STATUS_SHIFT                                  10
#define AFE_SYSCFG_IRSR0_RX_DONE_INT_RAW_STATUS_MASK                                   0x00000400
#define AFE_SYSCFG_IRSR0_RX_DONE_INT_RAW_STATUS_SET(n)                                 (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_IRSR0_RX_DONE_INT_RAW_STATUS_CLR                                    0xFFFFFBFF

#define AFE_SYSCFG_IRSR0_RX_1BYTE_DONE_INT_RAW_STATUS_SHIFT                            9
#define AFE_SYSCFG_IRSR0_RX_1BYTE_DONE_INT_RAW_STATUS_MASK                             0x00000200
#define AFE_SYSCFG_IRSR0_RX_1BYTE_DONE_INT_RAW_STATUS_SET(n)                           (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_IRSR0_RX_1BYTE_DONE_INT_RAW_STATUS_CLR                              0xFFFFFDFF

#define AFE_SYSCFG_IRSR0_CH2_PWM_CLR_INT_RAW_STATUS_SHIFT                              8
#define AFE_SYSCFG_IRSR0_CH2_PWM_CLR_INT_RAW_STATUS_MASK                               0x00000100
#define AFE_SYSCFG_IRSR0_CH2_PWM_CLR_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_IRSR0_CH2_PWM_CLR_INT_RAW_STATUS_CLR                                0xFFFFFEFF

#define AFE_SYSCFG_IRSR0_CH2_PWM_SET_INT_RAW_STATUS_SHIFT                              7
#define AFE_SYSCFG_IRSR0_CH2_PWM_SET_INT_RAW_STATUS_MASK                               0x00000080
#define AFE_SYSCFG_IRSR0_CH2_PWM_SET_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_IRSR0_CH2_PWM_SET_INT_RAW_STATUS_CLR                                0xFFFFFF7F

#define AFE_SYSCFG_IRSR0_CH2_CNT_MAX_INT_RAW_STATUS_SHIFT                              6
#define AFE_SYSCFG_IRSR0_CH2_CNT_MAX_INT_RAW_STATUS_MASK                               0x00000040
#define AFE_SYSCFG_IRSR0_CH2_CNT_MAX_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_IRSR0_CH2_CNT_MAX_INT_RAW_STATUS_CLR                                0xFFFFFFBF

#define AFE_SYSCFG_IRSR0_CH1_PWM_CLR_INT_RAW_STATUS_SHIFT                              5
#define AFE_SYSCFG_IRSR0_CH1_PWM_CLR_INT_RAW_STATUS_MASK                               0x00000020
#define AFE_SYSCFG_IRSR0_CH1_PWM_CLR_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_IRSR0_CH1_PWM_CLR_INT_RAW_STATUS_CLR                                0xFFFFFFDF

#define AFE_SYSCFG_IRSR0_CH1_PWM_SET_INT_RAW_STATUS_SHIFT                              4
#define AFE_SYSCFG_IRSR0_CH1_PWM_SET_INT_RAW_STATUS_MASK                               0x00000010
#define AFE_SYSCFG_IRSR0_CH1_PWM_SET_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_IRSR0_CH1_PWM_SET_INT_RAW_STATUS_CLR                                0xFFFFFFEF

#define AFE_SYSCFG_IRSR0_CH1_CNT_MAX_INT_RAW_STATUS_SHIFT                              3
#define AFE_SYSCFG_IRSR0_CH1_CNT_MAX_INT_RAW_STATUS_MASK                               0x00000008
#define AFE_SYSCFG_IRSR0_CH1_CNT_MAX_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_IRSR0_CH1_CNT_MAX_INT_RAW_STATUS_CLR                                0xFFFFFFF7

#define AFE_SYSCFG_IRSR0_CH0_PWM_CLR_INT_RAW_STATUS_SHIFT                              2
#define AFE_SYSCFG_IRSR0_CH0_PWM_CLR_INT_RAW_STATUS_MASK                               0x00000004
#define AFE_SYSCFG_IRSR0_CH0_PWM_CLR_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_IRSR0_CH0_PWM_CLR_INT_RAW_STATUS_CLR                                0xFFFFFFFB

#define AFE_SYSCFG_IRSR0_CH0_PWM_SET_INT_RAW_STATUS_SHIFT                              1
#define AFE_SYSCFG_IRSR0_CH0_PWM_SET_INT_RAW_STATUS_MASK                               0x00000002
#define AFE_SYSCFG_IRSR0_CH0_PWM_SET_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_IRSR0_CH0_PWM_SET_INT_RAW_STATUS_CLR                                0xFFFFFFFD

#define AFE_SYSCFG_IRSR0_CH0_CNT_MAX_INT_RAW_STATUS_SHIFT                              0
#define AFE_SYSCFG_IRSR0_CH0_CNT_MAX_INT_RAW_STATUS_MASK                               0x00000001
#define AFE_SYSCFG_IRSR0_CH0_CNT_MAX_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_IRSR0_CH0_CNT_MAX_INT_RAW_STATUS_CLR                                0xFFFFFFFE

#define AFE_SYSCFG_IMR1_AUTO_ADDR_1BIT_INT_MSK_SHIFT                                   13
#define AFE_SYSCFG_IMR1_AUTO_ADDR_1BIT_INT_MSK_MASK                                    0x00002000
#define AFE_SYSCFG_IMR1_AUTO_ADDR_1BIT_INT_MSK_SET(n)                                  (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_IMR1_AUTO_ADDR_1BIT_INT_MSK_CLR                                     0xFFFFDFFF

#define AFE_SYSCFG_IMR1_AUTO_ADDR_START_INT_MSK_SHIFT                                  12
#define AFE_SYSCFG_IMR1_AUTO_ADDR_START_INT_MSK_MASK                                   0x00001000
#define AFE_SYSCFG_IMR1_AUTO_ADDR_START_INT_MSK_SET(n)                                 (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_IMR1_AUTO_ADDR_START_INT_MSK_CLR                                    0xFFFFEFFF

#define AFE_SYSCFG_IMR1_MP_MODE_ADDR_INT_MSK_SHIFT                                     11
#define AFE_SYSCFG_IMR1_MP_MODE_ADDR_INT_MSK_MASK                                      0x00000800
#define AFE_SYSCFG_IMR1_MP_MODE_ADDR_INT_MSK_SET(n)                                    (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_IMR1_MP_MODE_ADDR_INT_MSK_CLR                                       0xFFFFF7FF

#define AFE_SYSCFG_IMR1_SLV_TX_BRK_DONE_INT_MSK_SHIFT                                  10
#define AFE_SYSCFG_IMR1_SLV_TX_BRK_DONE_INT_MSK_MASK                                   0x00000400
#define AFE_SYSCFG_IMR1_SLV_TX_BRK_DONE_INT_MSK_SET(n)                                 (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_IMR1_SLV_TX_BRK_DONE_INT_MSK_CLR                                    0xFFFFFBFF

#define AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_SHIFT                                      9
#define AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_MASK                                       0x00000200
#define AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_SET(n)                                     (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_CLR                                        0xFFFFFDFF

#define AFE_SYSCFG_IMR1_BUS_IDLE_DET_INT_MSK_SHIFT                                     8
#define AFE_SYSCFG_IMR1_BUS_IDLE_DET_INT_MSK_MASK                                      0x00000100
#define AFE_SYSCFG_IMR1_BUS_IDLE_DET_INT_MSK_SET(n)                                    (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_IMR1_BUS_IDLE_DET_INT_MSK_CLR                                       0xFFFFFEFF

#define AFE_SYSCFG_IMR1_ADC_FIFO_UNF_INT_MSK_SHIFT                                     7
#define AFE_SYSCFG_IMR1_ADC_FIFO_UNF_INT_MSK_MASK                                      0x00000080
#define AFE_SYSCFG_IMR1_ADC_FIFO_UNF_INT_MSK_SET(n)                                    (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_IMR1_ADC_FIFO_UNF_INT_MSK_CLR                                       0xFFFFFF7F

#define AFE_SYSCFG_IMR1_ADC_RX_RDY_INT_MSK_SHIFT                                       6
#define AFE_SYSCFG_IMR1_ADC_RX_RDY_INT_MSK_MASK                                        0x00000040
#define AFE_SYSCFG_IMR1_ADC_RX_RDY_INT_MSK_SET(n)                                      (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_IMR1_ADC_RX_RDY_INT_MSK_CLR                                         0xFFFFFFBF

#define AFE_SYSCFG_IMR1_ADC_FIFO_OVF_INT_MSK_SHIFT                                     5
#define AFE_SYSCFG_IMR1_ADC_FIFO_OVF_INT_MSK_MASK                                      0x00000020
#define AFE_SYSCFG_IMR1_ADC_FIFO_OVF_INT_MSK_SET(n)                                    (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_IMR1_ADC_FIFO_OVF_INT_MSK_CLR                                       0xFFFFFFDF

#define AFE_SYSCFG_IMR1_ADC_CMP_INT_MSK_SHIFT                                          4
#define AFE_SYSCFG_IMR1_ADC_CMP_INT_MSK_MASK                                           0x00000010
#define AFE_SYSCFG_IMR1_ADC_CMP_INT_MSK_SET(n)                                         (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_IMR1_ADC_CMP_INT_MSK_CLR                                            0xFFFFFFEF

#define AFE_SYSCFG_IMR1_GPIO_INT_MSK_SHIFT                                             3
#define AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK                                              0x00000008
#define AFE_SYSCFG_IMR1_GPIO_INT_MSK_SET(n)                                            (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_IMR1_GPIO_INT_MSK_CLR                                               0xFFFFFFF7

#define AFE_SYSCFG_IMR1_RTC_ALARM_INT_MSK_SHIFT                                        2
#define AFE_SYSCFG_IMR1_RTC_ALARM_INT_MSK_MASK                                         0x00000004
#define AFE_SYSCFG_IMR1_RTC_ALARM_INT_MSK_SET(n)                                       (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_IMR1_RTC_ALARM_INT_MSK_CLR                                          0xFFFFFFFB

#define AFE_SYSCFG_IMR1_RTC_CNT_INT_MSK_SHIFT                                          1
#define AFE_SYSCFG_IMR1_RTC_CNT_INT_MSK_MASK                                           0x00000002
#define AFE_SYSCFG_IMR1_RTC_CNT_INT_MSK_SET(n)                                         (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_IMR1_RTC_CNT_INT_MSK_CLR                                            0xFFFFFFFD

#define AFE_SYSCFG_IMR1_RTC_TRIG_0_INT_MSK_SHIFT                                       0
#define AFE_SYSCFG_IMR1_RTC_TRIG_0_INT_MSK_MASK                                        0x00000001
#define AFE_SYSCFG_IMR1_RTC_TRIG_0_INT_MSK_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_IMR1_RTC_TRIG_0_INT_MSK_CLR                                         0xFFFFFFFE

#define AFE_SYSCFG_ICR1_AUTO_ADDR_1BIT_INT_CLR_SHIFT                                   13
#define AFE_SYSCFG_ICR1_AUTO_ADDR_1BIT_INT_CLR_MASK                                    0x00002000
#define AFE_SYSCFG_ICR1_AUTO_ADDR_1BIT_INT_CLR_SET(n)                                  (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_ICR1_AUTO_ADDR_1BIT_INT_CLR_CLR                                     0xFFFFDFFF

#define AFE_SYSCFG_ICR1_AUTO_ADDR_START_INT_CLR_SHIFT                                  12
#define AFE_SYSCFG_ICR1_AUTO_ADDR_START_INT_CLR_MASK                                   0x00001000
#define AFE_SYSCFG_ICR1_AUTO_ADDR_START_INT_CLR_SET(n)                                 (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_ICR1_AUTO_ADDR_START_INT_CLR_CLR                                    0xFFFFEFFF

#define AFE_SYSCFG_ICR1_MP_MODE_ADDR_INT_CLR_SHIFT                                     11
#define AFE_SYSCFG_ICR1_MP_MODE_ADDR_INT_CLR_MASK                                      0x00000800
#define AFE_SYSCFG_ICR1_MP_MODE_ADDR_INT_CLR_SET(n)                                    (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_ICR1_MP_MODE_ADDR_INT_CLR_CLR                                       0xFFFFF7FF

#define AFE_SYSCFG_ICR1_SLV_TX_BRK_DONE_INT_CLR_SHIFT                                  10
#define AFE_SYSCFG_ICR1_SLV_TX_BRK_DONE_INT_CLR_MASK                                   0x00000400
#define AFE_SYSCFG_ICR1_SLV_TX_BRK_DONE_INT_CLR_SET(n)                                 (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_ICR1_SLV_TX_BRK_DONE_INT_CLR_CLR                                    0xFFFFFBFF

#define AFE_SYSCFG_ICR1_WAKE_UP_DET_INT_CLR_SHIFT                                      9
#define AFE_SYSCFG_ICR1_WAKE_UP_DET_INT_CLR_MASK                                       0x00000200
#define AFE_SYSCFG_ICR1_WAKE_UP_DET_INT_CLR_SET(n)                                     (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_ICR1_WAKE_UP_DET_INT_CLR_CLR                                        0xFFFFFDFF

#define AFE_SYSCFG_ICR1_BUS_IDLE_DET_INT_CLR_SHIFT                                     8
#define AFE_SYSCFG_ICR1_BUS_IDLE_DET_INT_CLR_MASK                                      0x00000100
#define AFE_SYSCFG_ICR1_BUS_IDLE_DET_INT_CLR_SET(n)                                    (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_ICR1_BUS_IDLE_DET_INT_CLR_CLR                                       0xFFFFFEFF

#define AFE_SYSCFG_ICR1_ADC_FIFO_UNF_INT_CLR_SHIFT                                     7
#define AFE_SYSCFG_ICR1_ADC_FIFO_UNF_INT_CLR_MASK                                      0x00000080
#define AFE_SYSCFG_ICR1_ADC_FIFO_UNF_INT_CLR_SET(n)                                    (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_ICR1_ADC_FIFO_UNF_INT_CLR_CLR                                       0xFFFFFF7F

#define AFE_SYSCFG_ICR1_ADC_RX_RDY_INT_CLR_SHIFT                                       6
#define AFE_SYSCFG_ICR1_ADC_RX_RDY_INT_CLR_MASK                                        0x00000040
#define AFE_SYSCFG_ICR1_ADC_RX_RDY_INT_CLR_SET(n)                                      (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_ICR1_ADC_RX_RDY_INT_CLR_CLR                                         0xFFFFFFBF

#define AFE_SYSCFG_ICR1_ADC_FIFO_OVF_INT_CLR_SHIFT                                     5
#define AFE_SYSCFG_ICR1_ADC_FIFO_OVF_INT_CLR_MASK                                      0x00000020
#define AFE_SYSCFG_ICR1_ADC_FIFO_OVF_INT_CLR_SET(n)                                    (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_ICR1_ADC_FIFO_OVF_INT_CLR_CLR                                       0xFFFFFFDF

#define AFE_SYSCFG_ICR1_ADC_CMP_INT_CLR_SHIFT                                          4
#define AFE_SYSCFG_ICR1_ADC_CMP_INT_CLR_MASK                                           0x00000010
#define AFE_SYSCFG_ICR1_ADC_CMP_INT_CLR_SET(n)                                         (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_ICR1_ADC_CMP_INT_CLR_CLR                                            0xFFFFFFEF

#define AFE_SYSCFG_ICR1_GPIO_INT_CLR_SHIFT                                             3
#define AFE_SYSCFG_ICR1_GPIO_INT_CLR_MASK                                              0x00000008
#define AFE_SYSCFG_ICR1_GPIO_INT_CLR_SET(n)                                            (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_ICR1_GPIO_INT_CLR_CLR                                               0xFFFFFFF7

#define AFE_SYSCFG_ICR1_RTC_ALARM_INT_CLR_SHIFT                                        2
#define AFE_SYSCFG_ICR1_RTC_ALARM_INT_CLR_MASK                                         0x00000004
#define AFE_SYSCFG_ICR1_RTC_ALARM_INT_CLR_SET(n)                                       (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_ICR1_RTC_ALARM_INT_CLR_CLR                                          0xFFFFFFFB

#define AFE_SYSCFG_ICR1_RTC_CNT_INT_CLR_SHIFT                                          1
#define AFE_SYSCFG_ICR1_RTC_CNT_INT_CLR_MASK                                           0x00000002
#define AFE_SYSCFG_ICR1_RTC_CNT_INT_CLR_SET(n)                                         (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_ICR1_RTC_CNT_INT_CLR_CLR                                            0xFFFFFFFD

#define AFE_SYSCFG_ICR1_RTC_TRIG_0_INT_CLR_SHIFT                                       0
#define AFE_SYSCFG_ICR1_RTC_TRIG_0_INT_CLR_MASK                                        0x00000001
#define AFE_SYSCFG_ICR1_RTC_TRIG_0_INT_CLR_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_ICR1_RTC_TRIG_0_INT_CLR_CLR                                         0xFFFFFFFE

#define AFE_SYSCFG_ISR1_AUTO_ADDR_1BIT_INT_STATUS_SHIFT                                13
#define AFE_SYSCFG_ISR1_AUTO_ADDR_1BIT_INT_STATUS_MASK                                 0x00002000
#define AFE_SYSCFG_ISR1_AUTO_ADDR_1BIT_INT_STATUS_SET(n)                               (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_ISR1_AUTO_ADDR_1BIT_INT_STATUS_CLR                                  0xFFFFDFFF

#define AFE_SYSCFG_ISR1_AUTO_ADDR_START_INT_STATUS_SHIFT                               12
#define AFE_SYSCFG_ISR1_AUTO_ADDR_START_INT_STATUS_MASK                                0x00001000
#define AFE_SYSCFG_ISR1_AUTO_ADDR_START_INT_STATUS_SET(n)                              (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_ISR1_AUTO_ADDR_START_INT_STATUS_CLR                                 0xFFFFEFFF

#define AFE_SYSCFG_ISR1_MP_MODE_ADDR_INT_STATUS_SHIFT                                  11
#define AFE_SYSCFG_ISR1_MP_MODE_ADDR_INT_STATUS_MASK                                   0x00000800
#define AFE_SYSCFG_ISR1_MP_MODE_ADDR_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_ISR1_MP_MODE_ADDR_INT_STATUS_CLR                                    0xFFFFF7FF

#define AFE_SYSCFG_ISR1_SLV_TX_BRK_DONE_INT_STATUS_SHIFT                               10
#define AFE_SYSCFG_ISR1_SLV_TX_BRK_DONE_INT_STATUS_MASK                                0x00000400
#define AFE_SYSCFG_ISR1_SLV_TX_BRK_DONE_INT_STATUS_SET(n)                              (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_ISR1_SLV_TX_BRK_DONE_INT_STATUS_CLR                                 0xFFFFFBFF

#define AFE_SYSCFG_ISR1_WAKE_UP_DET_INT_STATUS_SHIFT                                   9
#define AFE_SYSCFG_ISR1_WAKE_UP_DET_INT_STATUS_MASK                                    0x00000200
#define AFE_SYSCFG_ISR1_WAKE_UP_DET_INT_STATUS_SET(n)                                  (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_ISR1_WAKE_UP_DET_INT_STATUS_CLR                                     0xFFFFFDFF

#define AFE_SYSCFG_ISR1_BUS_IDLE_DET_INT_STATUS_SHIFT                                  8
#define AFE_SYSCFG_ISR1_BUS_IDLE_DET_INT_STATUS_MASK                                   0x00000100
#define AFE_SYSCFG_ISR1_BUS_IDLE_DET_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_ISR1_BUS_IDLE_DET_INT_STATUS_CLR                                    0xFFFFFEFF

#define AFE_SYSCFG_ISR1_ADC_FIFO_UNF_INT_STATUS_SHIFT                                  7
#define AFE_SYSCFG_ISR1_ADC_FIFO_UNF_INT_STATUS_MASK                                   0x00000080
#define AFE_SYSCFG_ISR1_ADC_FIFO_UNF_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_ISR1_ADC_FIFO_UNF_INT_STATUS_CLR                                    0xFFFFFF7F

#define AFE_SYSCFG_ISR1_ADC_RX_RDY_INT_STATUS_SHIFT                                    6
#define AFE_SYSCFG_ISR1_ADC_RX_RDY_INT_STATUS_MASK                                     0x00000040
#define AFE_SYSCFG_ISR1_ADC_RX_RDY_INT_STATUS_SET(n)                                   (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_ISR1_ADC_RX_RDY_INT_STATUS_CLR                                      0xFFFFFFBF

#define AFE_SYSCFG_ISR1_ADC_FIFO_OVF_INT_STATUS_SHIFT                                  5
#define AFE_SYSCFG_ISR1_ADC_FIFO_OVF_INT_STATUS_MASK                                   0x00000020
#define AFE_SYSCFG_ISR1_ADC_FIFO_OVF_INT_STATUS_SET(n)                                 (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_ISR1_ADC_FIFO_OVF_INT_STATUS_CLR                                    0xFFFFFFDF

#define AFE_SYSCFG_ISR1_ADC_CMP_INT_STATUS_SHIFT                                       4
#define AFE_SYSCFG_ISR1_ADC_CMP_INT_STATUS_MASK                                        0x00000010
#define AFE_SYSCFG_ISR1_ADC_CMP_INT_STATUS_SET(n)                                      (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_ISR1_ADC_CMP_INT_STATUS_CLR                                         0xFFFFFFEF

#define AFE_SYSCFG_ISR1_GPIO_INT_STATUS_SHIFT                                          3
#define AFE_SYSCFG_ISR1_GPIO_INT_STATUS_MASK                                           0x00000008
#define AFE_SYSCFG_ISR1_GPIO_INT_STATUS_SET(n)                                         (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_ISR1_GPIO_INT_STATUS_CLR                                            0xFFFFFFF7

#define AFE_SYSCFG_ISR1_RTC_ALARM_INT_STATUS_SHIFT                                     2
#define AFE_SYSCFG_ISR1_RTC_ALARM_INT_STATUS_MASK                                      0x00000004
#define AFE_SYSCFG_ISR1_RTC_ALARM_INT_STATUS_SET(n)                                    (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_ISR1_RTC_ALARM_INT_STATUS_CLR                                       0xFFFFFFFB

#define AFE_SYSCFG_ISR1_RTC_CNT_INT_STATUS_SHIFT                                       1
#define AFE_SYSCFG_ISR1_RTC_CNT_INT_STATUS_MASK                                        0x00000002
#define AFE_SYSCFG_ISR1_RTC_CNT_INT_STATUS_SET(n)                                      (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_ISR1_RTC_CNT_INT_STATUS_CLR                                         0xFFFFFFFD

#define AFE_SYSCFG_ISR1_RTC_TRIG_0_INT_STATUS_SHIFT                                    0
#define AFE_SYSCFG_ISR1_RTC_TRIG_0_INT_STATUS_MASK                                     0x00000001
#define AFE_SYSCFG_ISR1_RTC_TRIG_0_INT_STATUS_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_ISR1_RTC_TRIG_0_INT_STATUS_CLR                                      0xFFFFFFFE

#define AFE_SYSCFG_IRSR1_AUTO_ADDR_1BIT_INT_RAW_STATUS_SHIFT                           13
#define AFE_SYSCFG_IRSR1_AUTO_ADDR_1BIT_INT_RAW_STATUS_MASK                            0x00002000
#define AFE_SYSCFG_IRSR1_AUTO_ADDR_1BIT_INT_RAW_STATUS_SET(n)                          (((uint32_t)(n) << 13 ) & 0x00002000)
#define AFE_SYSCFG_IRSR1_AUTO_ADDR_1BIT_INT_RAW_STATUS_CLR                             0xFFFFDFFF

#define AFE_SYSCFG_IRSR1_AUTO_ADDR_START_INT_RAW_STATUS_SHIFT                          12
#define AFE_SYSCFG_IRSR1_AUTO_ADDR_START_INT_RAW_STATUS_MASK                           0x00001000
#define AFE_SYSCFG_IRSR1_AUTO_ADDR_START_INT_RAW_STATUS_SET(n)                         (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_SYSCFG_IRSR1_AUTO_ADDR_START_INT_RAW_STATUS_CLR                            0xFFFFEFFF

#define AFE_SYSCFG_IRSR1_MP_MODE_ADDR_INT_RAW_STATUS_SHIFT                             11
#define AFE_SYSCFG_IRSR1_MP_MODE_ADDR_INT_RAW_STATUS_MASK                              0x00000800
#define AFE_SYSCFG_IRSR1_MP_MODE_ADDR_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_SYSCFG_IRSR1_MP_MODE_ADDR_INT_RAW_STATUS_CLR                               0xFFFFF7FF

#define AFE_SYSCFG_IRSR1_SLV_TX_BRK_DONE_INT_RAW_STATUS_SHIFT                          10
#define AFE_SYSCFG_IRSR1_SLV_TX_BRK_DONE_INT_RAW_STATUS_MASK                           0x00000400
#define AFE_SYSCFG_IRSR1_SLV_TX_BRK_DONE_INT_RAW_STATUS_SET(n)                         (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_SYSCFG_IRSR1_SLV_TX_BRK_DONE_INT_RAW_STATUS_CLR                            0xFFFFFBFF

#define AFE_SYSCFG_IRSR1_WAKE_UP_DET_INT_RAW_STATUS_SHIFT                              9
#define AFE_SYSCFG_IRSR1_WAKE_UP_DET_INT_RAW_STATUS_MASK                               0x00000200
#define AFE_SYSCFG_IRSR1_WAKE_UP_DET_INT_RAW_STATUS_SET(n)                             (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_SYSCFG_IRSR1_WAKE_UP_DET_INT_RAW_STATUS_CLR                                0xFFFFFDFF

#define AFE_SYSCFG_IRSR1_BUS_IDLE_DET_INT_RAW_STATUS_SHIFT                             8
#define AFE_SYSCFG_IRSR1_BUS_IDLE_DET_INT_RAW_STATUS_MASK                              0x00000100
#define AFE_SYSCFG_IRSR1_BUS_IDLE_DET_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_SYSCFG_IRSR1_BUS_IDLE_DET_INT_RAW_STATUS_CLR                               0xFFFFFEFF

#define AFE_SYSCFG_IRSR1_ADC_FIFO_UNF_INT_RAW_STATUS_SHIFT                             7
#define AFE_SYSCFG_IRSR1_ADC_FIFO_UNF_INT_RAW_STATUS_MASK                              0x00000080
#define AFE_SYSCFG_IRSR1_ADC_FIFO_UNF_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 7  ) & 0x00000080)
#define AFE_SYSCFG_IRSR1_ADC_FIFO_UNF_INT_RAW_STATUS_CLR                               0xFFFFFF7F

#define AFE_SYSCFG_IRSR1_ADC_RX_RDY_INT_RAW_STATUS_SHIFT                               6
#define AFE_SYSCFG_IRSR1_ADC_RX_RDY_INT_RAW_STATUS_MASK                                0x00000040
#define AFE_SYSCFG_IRSR1_ADC_RX_RDY_INT_RAW_STATUS_SET(n)                              (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_IRSR1_ADC_RX_RDY_INT_RAW_STATUS_CLR                                 0xFFFFFFBF

#define AFE_SYSCFG_IRSR1_ADC_FIFO_OVF_INT_RAW_STATUS_SHIFT                             5
#define AFE_SYSCFG_IRSR1_ADC_FIFO_OVF_INT_RAW_STATUS_MASK                              0x00000020
#define AFE_SYSCFG_IRSR1_ADC_FIFO_OVF_INT_RAW_STATUS_SET(n)                            (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_IRSR1_ADC_FIFO_OVF_INT_RAW_STATUS_CLR                               0xFFFFFFDF

#define AFE_SYSCFG_IRSR1_ADC_CMP_INT_RAW_STATUS_SHIFT                                  4
#define AFE_SYSCFG_IRSR1_ADC_CMP_INT_RAW_STATUS_MASK                                   0x00000010
#define AFE_SYSCFG_IRSR1_ADC_CMP_INT_RAW_STATUS_SET(n)                                 (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_IRSR1_ADC_CMP_INT_RAW_STATUS_CLR                                    0xFFFFFFEF

#define AFE_SYSCFG_IRSR1_GPIO_INT_RAW_STATUS_SHIFT                                     3
#define AFE_SYSCFG_IRSR1_GPIO_INT_RAW_STATUS_MASK                                      0x00000008
#define AFE_SYSCFG_IRSR1_GPIO_INT_RAW_STATUS_SET(n)                                    (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_SYSCFG_IRSR1_GPIO_INT_RAW_STATUS_CLR                                       0xFFFFFFF7

#define AFE_SYSCFG_IRSR1_RTC_ALARM_INT_RAW_STATUS_SHIFT                                2
#define AFE_SYSCFG_IRSR1_RTC_ALARM_INT_RAW_STATUS_MASK                                 0x00000004
#define AFE_SYSCFG_IRSR1_RTC_ALARM_INT_RAW_STATUS_SET(n)                               (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_IRSR1_RTC_ALARM_INT_RAW_STATUS_CLR                                  0xFFFFFFFB

#define AFE_SYSCFG_IRSR1_RTC_CNT_INT_RAW_STATUS_SHIFT                                  1
#define AFE_SYSCFG_IRSR1_RTC_CNT_INT_RAW_STATUS_MASK                                   0x00000002
#define AFE_SYSCFG_IRSR1_RTC_CNT_INT_RAW_STATUS_SET(n)                                 (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_IRSR1_RTC_CNT_INT_RAW_STATUS_CLR                                    0xFFFFFFFD

#define AFE_SYSCFG_IRSR1_RTC_TRIG_0_INT_RAW_STATUS_SHIFT                               0
#define AFE_SYSCFG_IRSR1_RTC_TRIG_0_INT_RAW_STATUS_MASK                                0x00000001
#define AFE_SYSCFG_IRSR1_RTC_TRIG_0_INT_RAW_STATUS_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_IRSR1_RTC_TRIG_0_INT_RAW_STATUS_CLR                                 0xFFFFFFFE

#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAIN_SHIFT                                         6
#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAIN_MASK                                          0x00000040
#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAIN_SET(n)                                        (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAIN_CLR                                           0xFFFFFFBF

#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_TYP_SEL_SHIFT                                    5
#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_TYP_SEL_MASK                                     0x00000020
#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_TYP_SEL_SET(n)                                   (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_TYP_SEL_CLR                                      0xFFFFFFDF

#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_SHIFT                                    4
#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_MASK                                     0x00000010
#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_SET(n)                                   (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_CLR                                      0xFFFFFFEF

#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_CLR_SHIFT                                      2
#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_CLR_MASK                                       0x00000004
#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_CLR_SET(n)                                     (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_CLR_CLR                                        0xFFFFFFFB

#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_SET_SHIFT                                      1
#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_SET_MASK                                       0x00000002
#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_SET_SET(n)                                     (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_SET_CLR                                        0xFFFFFFFD

#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_SHIFT                                        0
#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_MASK                                         0x00000001
#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_SET(n)                                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_CLR                                          0xFFFFFFFE

#define AFE_SYSCFG_INT_SNS_CTRL_INT_SNS_EN_SHIFT                                       0
#define AFE_SYSCFG_INT_SNS_CTRL_INT_SNS_EN_MASK                                        0x00000001
#define AFE_SYSCFG_INT_SNS_CTRL_INT_SNS_EN_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_INT_SNS_CTRL_INT_SNS_EN_CLR                                         0xFFFFFFFE

#define AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_SHIFT                                      0
#define AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_MASK                                       0x00000001
#define AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_BIAS_CTRL_ACTIVE_BIAS_EN_CLR                                        0xFFFFFFFE

#define AFE_SYSCFG_OTP_STATUS_OTP_OUT_SHIFT                                            0
#define AFE_SYSCFG_OTP_STATUS_OTP_OUT_MASK                                             0x00000001
#define AFE_SYSCFG_OTP_STATUS_OTP_OUT_SET(n)                                           (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_OTP_STATUS_OTP_OUT_CLR                                              0xFFFFFFFE

#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_TIM_SHIFT                                       4
#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_TIM_MASK                                        0x000000F0
#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_TIM_SET(n)                                      (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_TIM_CLR                                         0xFFFFFF0F

#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_DET_EN_SHIFT                                    0
#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_DET_EN_MASK                                     0x00000001
#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_DET_EN_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_LIN_WU_CTRL_WAKE_UP_DET_EN_CLR                                      0xFFFFFFFE

#define AFE_SYSCFG_SYSCFG_LOCK_SYSCFG_LOCK_SHIFT                                       0
#define AFE_SYSCFG_SYSCFG_LOCK_SYSCFG_LOCK_MASK                                        0x00000001
#define AFE_SYSCFG_SYSCFG_LOCK_SYSCFG_LOCK_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_SYSCFG_SYSCFG_LOCK_SYSCFG_LOCK_CLR                                         0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t CHIP_ID                        : 16 ; // 15 : 0
    __IO uint32_t REV_ID                         : 7  ; // 22 : 16
    __IO uint32_t RESERVED0                      : 9  ; // 31 : 23
} AFE_SYSCFG_REVISION_FIELD_T;

typedef struct
{
    __IO uint32_t CH0_CNT_MAX_INT_MSK            : 1  ; // 0  : 0
    __IO uint32_t CH0_PWM_SET_INT_MSK            : 1  ; // 1  : 1
    __IO uint32_t CH0_PWM_CLR_INT_MSK            : 1  ; // 2  : 2
    __IO uint32_t CH1_CNT_MAX_INT_MSK            : 1  ; // 3  : 3
    __IO uint32_t CH1_PWM_SET_INT_MSK            : 1  ; // 4  : 4
    __IO uint32_t CH1_PWM_CLR_INT_MSK            : 1  ; // 5  : 5
    __IO uint32_t CH2_CNT_MAX_INT_MSK            : 1  ; // 6  : 6
    __IO uint32_t CH2_PWM_SET_INT_MSK            : 1  ; // 7  : 7
    __IO uint32_t CH2_PWM_CLR_INT_MSK            : 1  ; // 8  : 8
    __IO uint32_t RX_1BYTE_DONE_INT_MSK          : 1  ; // 9  : 9
    __IO uint32_t RX_DONE_INT_MSK                : 1  ; // 10 : 10
    __IO uint32_t RX_PID_DONE_INT_MSK            : 1  ; // 11 : 11
    __IO uint32_t RX_PTY_CHK_ERR_INT_MSK         : 1  ; // 12 : 12
    __IO uint32_t RX_CHKSUM_ERR_INT_MSK          : 1  ; // 13 : 13
    __IO uint32_t RX_STP_ERR_INT_MSK             : 1  ; // 14 : 14
    __IO uint32_t RX_FIFO_FULL_INT_MSK           : 1  ; // 15 : 15
    __IO uint32_t RX_FIFO_OVF_ERR_INT_MSK        : 1  ; // 16 : 16
    __IO uint32_t TX_DONE_INT_MSK                : 1  ; // 17 : 17
    __IO uint32_t TX_FIFO_EMPTY_INT_MSK          : 1  ; // 18 : 18
    __IO uint32_t TX_COL_DET_ERR_INT_MSK         : 1  ; // 19 : 19
    __IO uint32_t BRK_DET_INT_MSK                : 1  ; // 20 : 20
    __IO uint32_t SYNC_DET_INT_MSK               : 1  ; // 21 : 21
    __IO uint32_t SYNC_VAL_ERR_INT_MSK           : 1  ; // 22 : 22
    __IO uint32_t RX_TIMEOUT_INT_MSK             : 1  ; // 23 : 23
    __IO uint32_t TX_PID_DONE_INT_MSK            : 1  ; // 24 : 24
    __IO uint32_t TX_RX_CONF_INT_MSK             : 1  ; // 25 : 25
    __IO uint32_t SLV_SELECTED_INT_MSK           : 1  ; // 26 : 26
    __IO uint32_t AUTO_ADDR_DONE_INT_MSK         : 1  ; // 27 : 27
    __IO uint32_t TX_1BYTE_DONE_INT_MSK          : 1  ; // 28 : 28
    __IO uint32_t ADC_DONE_INT_MSK               : 1  ; // 29 : 29
    __IO uint32_t OTP_INT_MSK                    : 1  ; // 30 : 30
    __IO uint32_t VS_LVD_INT_MSK                 : 1  ; // 31 : 31
} AFE_SYSCFG_IMR0_FIELD_T;

typedef struct
{
    __IO uint32_t CH0_CNT_MAX_INT_CLR            : 1  ; // 0  : 0
    __IO uint32_t CH0_PWM_SET_INT_CLR            : 1  ; // 1  : 1
    __IO uint32_t CH0_PWM_CLR_INT_CLR            : 1  ; // 2  : 2
    __IO uint32_t CH1_CNT_MAX_INT_CLR            : 1  ; // 3  : 3
    __IO uint32_t CH1_PWM_SET_INT_CLR            : 1  ; // 4  : 4
    __IO uint32_t CH1_PWM_CLR_INT_CLR            : 1  ; // 5  : 5
    __IO uint32_t CH2_CNT_MAX_INT_CLR            : 1  ; // 6  : 6
    __IO uint32_t CH2_PWM_SET_INT_CLR            : 1  ; // 7  : 7
    __IO uint32_t CH2_PWM_CLR_INT_CLR            : 1  ; // 8  : 8
    __IO uint32_t RX_1BYTE_DONE_INT_CLR          : 1  ; // 9  : 9
    __IO uint32_t RX_DONE_INT_CLR                : 1  ; // 10 : 10
    __IO uint32_t RX_PID_DONE_INT_CLR            : 1  ; // 11 : 11
    __IO uint32_t RX_PTY_CHK_ERR_INT_CLR         : 1  ; // 12 : 12
    __IO uint32_t RX_CHKSUM_ERR_INT_CLR          : 1  ; // 13 : 13
    __IO uint32_t RX_STP_ERR_INT_CLR             : 1  ; // 14 : 14
    __IO uint32_t RX_FIFO_FULL_INT_CLR           : 1  ; // 15 : 15
    __IO uint32_t RX_FIFO_OVF_ERR_INT_CLR        : 1  ; // 16 : 16
    __IO uint32_t TX_DONE_INT_CLR                : 1  ; // 17 : 17
    __IO uint32_t TX_FIFO_EMPTY_INT_CLR          : 1  ; // 18 : 18
    __IO uint32_t TX_COL_DET_ERR_INT_CLR         : 1  ; // 19 : 19
    __IO uint32_t BRK_DET_INT_CLR                : 1  ; // 20 : 20
    __IO uint32_t SYNC_DET_INT_CLR               : 1  ; // 21 : 21
    __IO uint32_t SYNC_VAL_ERR_INT_CLR           : 1  ; // 22 : 22
    __IO uint32_t RX_TIMEOUT_INT_CLR             : 1  ; // 23 : 23
    __IO uint32_t TX_PID_DONE_INT_CLR            : 1  ; // 24 : 24
    __IO uint32_t TX_RX_CONF_INT_CLR             : 1  ; // 25 : 25
    __IO uint32_t SLV_SELECTED_INT_CLR           : 1  ; // 26 : 26
    __IO uint32_t AUTO_ADDR_DONE_INT_CLR         : 1  ; // 27 : 27
    __IO uint32_t TX_1BYTE_DONE_INT_CLR          : 1  ; // 28 : 28
    __IO uint32_t ADC_DONE_INT_CLR               : 1  ; // 29 : 29
    __IO uint32_t OTP_INT_CLR                    : 1  ; // 30 : 30
    __IO uint32_t VS_LVD_INT_CLR                 : 1  ; // 31 : 31
} AFE_SYSCFG_ICR0_FIELD_T;

typedef struct
{
    __IO uint32_t CH0_CNT_MAX_INT_STATUS         : 1  ; // 0  : 0
    __IO uint32_t CH0_PWM_SET_INT_STATUS         : 1  ; // 1  : 1
    __IO uint32_t CH0_PWM_CLR_INT_STATUS         : 1  ; // 2  : 2
    __IO uint32_t CH1_CNT_MAX_INT_STATUS         : 1  ; // 3  : 3
    __IO uint32_t CH1_PWM_SET_INT_STATUS         : 1  ; // 4  : 4
    __IO uint32_t CH1_PWM_CLR_INT_STATUS         : 1  ; // 5  : 5
    __IO uint32_t CH2_CNT_MAX_INT_STATUS         : 1  ; // 6  : 6
    __IO uint32_t CH2_PWM_SET_INT_STATUS         : 1  ; // 7  : 7
    __IO uint32_t CH2_PWM_CLR_INT_STATUS         : 1  ; // 8  : 8
    __IO uint32_t RX_1BYTE_DONE_INT_STATUS       : 1  ; // 9  : 9
    __IO uint32_t RX_DONE_INT_STATUS             : 1  ; // 10 : 10
    __IO uint32_t RX_PID_DONE_INT_STATUS         : 1  ; // 11 : 11
    __IO uint32_t RX_PTY_CHK_ERR_INT_STATUS      : 1  ; // 12 : 12
    __IO uint32_t RX_CHKSUM_ERR_INT_STATUS       : 1  ; // 13 : 13
    __IO uint32_t RX_STP_ERR_INT_STATUS          : 1  ; // 14 : 14
    __IO uint32_t RX_FIFO_FULL_INT_STATUS        : 1  ; // 15 : 15
    __IO uint32_t RX_FIFO_OVF_ERR_INT_STATUS     : 1  ; // 16 : 16
    __IO uint32_t TX_DONE_INT_STATUS             : 1  ; // 17 : 17
    __IO uint32_t TX_FIFO_EMPTY_INT_STATUS       : 1  ; // 18 : 18
    __IO uint32_t TX_COL_DET_ERR_INT_STATUS      : 1  ; // 19 : 19
    __IO uint32_t BRK_DET_INT_STATUS             : 1  ; // 20 : 20
    __IO uint32_t SYNC_DET_INT_STATUS            : 1  ; // 21 : 21
    __IO uint32_t SYNC_VAL_ERR_INT_STATUS        : 1  ; // 22 : 22
    __IO uint32_t RX_TIMEOUT_INT_STATUS          : 1  ; // 23 : 23
    __IO uint32_t TX_PID_DONE_INT_STATUS         : 1  ; // 24 : 24
    __IO uint32_t TX_RX_CONF_INT_STATUS          : 1  ; // 25 : 25
    __IO uint32_t SLV_SELECTED_INT_STATUS        : 1  ; // 26 : 26
    __IO uint32_t AUTO_ADDR_DONE_INT_STATUS      : 1  ; // 27 : 27
    __IO uint32_t TX_1BYTE_DONE_INT_STATUS       : 1  ; // 28 : 28
    __IO uint32_t ADC_DONE_INT_STATUS            : 1  ; // 29 : 29
    __IO uint32_t OTP_INT_STATUS                 : 1  ; // 30 : 30
    __IO uint32_t VS_LVD_INT_STATUS              : 1  ; // 31 : 31
} AFE_SYSCFG_ISR0_FIELD_T;

typedef struct
{
    __IO uint32_t CH0_CNT_MAX_INT_RAW_STATUS     : 1  ; // 0  : 0
    __IO uint32_t CH0_PWM_SET_INT_RAW_STATUS     : 1  ; // 1  : 1
    __IO uint32_t CH0_PWM_CLR_INT_RAW_STATUS     : 1  ; // 2  : 2
    __IO uint32_t CH1_CNT_MAX_INT_RAW_STATUS     : 1  ; // 3  : 3
    __IO uint32_t CH1_PWM_SET_INT_RAW_STATUS     : 1  ; // 4  : 4
    __IO uint32_t CH1_PWM_CLR_INT_RAW_STATUS     : 1  ; // 5  : 5
    __IO uint32_t CH2_CNT_MAX_INT_RAW_STATUS     : 1  ; // 6  : 6
    __IO uint32_t CH2_PWM_SET_INT_RAW_STATUS     : 1  ; // 7  : 7
    __IO uint32_t CH2_PWM_CLR_INT_RAW_STATUS     : 1  ; // 8  : 8
    __IO uint32_t RX_1BYTE_DONE_INT_RAW_STATUS   : 1  ; // 9  : 9
    __IO uint32_t RX_DONE_INT_RAW_STATUS         : 1  ; // 10 : 10
    __IO uint32_t RX_PID_DONE_INT_RAW_STATUS     : 1  ; // 11 : 11
    __IO uint32_t RX_PTY_CHK_ERR_INT_RAW_STATUS  : 1  ; // 12 : 12
    __IO uint32_t RX_CHKSUM_ERR_INT_RAW_STATUS   : 1  ; // 13 : 13
    __IO uint32_t RX_STP_ERR_INT_RAW_STATUS      : 1  ; // 14 : 14
    __IO uint32_t RX_FIFO_FULL_INT_RAW_STATUS    : 1  ; // 15 : 15
    __IO uint32_t RX_FIFO_OVF_ERR_INT_RAW_STATUS : 1  ; // 16 : 16
    __IO uint32_t TX_DONE_INT_RAW_STATUS         : 1  ; // 17 : 17
    __IO uint32_t TX_FIFO_EMPTY_INT_RAW_STATUS   : 1  ; // 18 : 18
    __IO uint32_t TX_COL_DET_ERR_INT_RAW_STATUS  : 1  ; // 19 : 19
    __IO uint32_t BRK_DET_INT_RAW_STATUS         : 1  ; // 20 : 20
    __IO uint32_t SYNC_DET_INT_RAW_STATUS        : 1  ; // 21 : 21
    __IO uint32_t SYNC_VAL_ERR_INT_RAW_STATUS    : 1  ; // 22 : 22
    __IO uint32_t RX_TIMEOUT_INT_RAW_STATUS      : 1  ; // 23 : 23
    __IO uint32_t TX_PID_DONE_INT_RAW_STATUS     : 1  ; // 24 : 24
    __IO uint32_t TX_RX_CONF_INT_RAW_STATUS      : 1  ; // 25 : 25
    __IO uint32_t SLV_SELECTED_INT_RAW_STATUS    : 1  ; // 26 : 26
    __IO uint32_t AUTO_ADDR_DONE_INT_RAW_STATUS  : 1  ; // 27 : 27
    __IO uint32_t TX_1BYTE_DONE_INT_RAW_STATUS   : 1  ; // 28 : 28
    __IO uint32_t ADC_DONE_INT_RAW_STATUS        : 1  ; // 29 : 29
    __IO uint32_t OTP_INT_RAW_STATUS             : 1  ; // 30 : 30
    __IO uint32_t VS_LVD_INT_RAW_STATUS          : 1  ; // 31 : 31
} AFE_SYSCFG_IRSR0_FIELD_T;

typedef struct
{
    __IO uint32_t RTC_TRIG_0_INT_MSK             : 1  ; // 0  : 0
    __IO uint32_t RTC_CNT_INT_MSK                : 1  ; // 1  : 1
    __IO uint32_t RTC_ALARM_INT_MSK              : 1  ; // 2  : 2
    __IO uint32_t GPIO_INT_MSK                   : 1  ; // 3  : 3
    __IO uint32_t ADC_CMP_INT_MSK                : 1  ; // 4  : 4
    __IO uint32_t ADC_FIFO_OVF_INT_MSK           : 1  ; // 5  : 5
    __IO uint32_t ADC_RX_RDY_INT_MSK             : 1  ; // 6  : 6
    __IO uint32_t ADC_FIFO_UNF_INT_MSK           : 1  ; // 7  : 7
    __IO uint32_t BUS_IDLE_DET_INT_MSK           : 1  ; // 8  : 8
    __IO uint32_t WAKE_UP_DET_INT_MSK            : 1  ; // 9  : 9
    __IO uint32_t SLV_TX_BRK_DONE_INT_MSK        : 1  ; // 10 : 10
    __IO uint32_t MP_MODE_ADDR_INT_MSK           : 1  ; // 11 : 11
    __IO uint32_t AUTO_ADDR_START_INT_MSK        : 1  ; // 12 : 12
    __IO uint32_t AUTO_ADDR_1BIT_INT_MSK         : 1  ; // 13 : 13
    __IO uint32_t RESERVED0                      : 18 ; // 31 : 14
} AFE_SYSCFG_IMR1_FIELD_T;

typedef struct
{
    __IO uint32_t RTC_TRIG_0_INT_CLR             : 1  ; // 0  : 0
    __IO uint32_t RTC_CNT_INT_CLR                : 1  ; // 1  : 1
    __IO uint32_t RTC_ALARM_INT_CLR              : 1  ; // 2  : 2
    __IO uint32_t GPIO_INT_CLR                   : 1  ; // 3  : 3
    __IO uint32_t ADC_CMP_INT_CLR                : 1  ; // 4  : 4
    __IO uint32_t ADC_FIFO_OVF_INT_CLR           : 1  ; // 5  : 5
    __IO uint32_t ADC_RX_RDY_INT_CLR             : 1  ; // 6  : 6
    __IO uint32_t ADC_FIFO_UNF_INT_CLR           : 1  ; // 7  : 7
    __IO uint32_t BUS_IDLE_DET_INT_CLR           : 1  ; // 8  : 8
    __IO uint32_t WAKE_UP_DET_INT_CLR            : 1  ; // 9  : 9
    __IO uint32_t SLV_TX_BRK_DONE_INT_CLR        : 1  ; // 10 : 10
    __IO uint32_t MP_MODE_ADDR_INT_CLR           : 1  ; // 11 : 11
    __IO uint32_t AUTO_ADDR_START_INT_CLR        : 1  ; // 12 : 12
    __IO uint32_t AUTO_ADDR_1BIT_INT_CLR         : 1  ; // 13 : 13
    __IO uint32_t RESERVED0                      : 18 ; // 31 : 14
} AFE_SYSCFG_ICR1_FIELD_T;

typedef struct
{
    __IO uint32_t RTC_TRIG_0_INT_STATUS          : 1  ; // 0  : 0
    __IO uint32_t RTC_CNT_INT_STATUS             : 1  ; // 1  : 1
    __IO uint32_t RTC_ALARM_INT_STATUS           : 1  ; // 2  : 2
    __IO uint32_t GPIO_INT_STATUS                : 1  ; // 3  : 3
    __IO uint32_t ADC_CMP_INT_STATUS             : 1  ; // 4  : 4
    __IO uint32_t ADC_FIFO_OVF_INT_STATUS        : 1  ; // 5  : 5
    __IO uint32_t ADC_RX_RDY_INT_STATUS          : 1  ; // 6  : 6
    __IO uint32_t ADC_FIFO_UNF_INT_STATUS        : 1  ; // 7  : 7
    __IO uint32_t BUS_IDLE_DET_INT_STATUS        : 1  ; // 8  : 8
    __IO uint32_t WAKE_UP_DET_INT_STATUS         : 1  ; // 9  : 9
    __IO uint32_t SLV_TX_BRK_DONE_INT_STATUS     : 1  ; // 10 : 10
    __IO uint32_t MP_MODE_ADDR_INT_STATUS        : 1  ; // 11 : 11
    __IO uint32_t AUTO_ADDR_START_INT_STATUS     : 1  ; // 12 : 12
    __IO uint32_t AUTO_ADDR_1BIT_INT_STATUS      : 1  ; // 13 : 13
    __IO uint32_t RESERVED0                      : 18 ; // 31 : 14
} AFE_SYSCFG_ISR1_FIELD_T;

typedef struct
{
    __IO uint32_t RTC_TRIG_0_INT_RAW_STATUS      : 1  ; // 0  : 0
    __IO uint32_t RTC_CNT_INT_RAW_STATUS         : 1  ; // 1  : 1
    __IO uint32_t RTC_ALARM_INT_RAW_STATUS       : 1  ; // 2  : 2
    __IO uint32_t GPIO_INT_RAW_STATUS            : 1  ; // 3  : 3
    __IO uint32_t ADC_CMP_INT_RAW_STATUS         : 1  ; // 4  : 4
    __IO uint32_t ADC_FIFO_OVF_INT_RAW_STATUS    : 1  ; // 5  : 5
    __IO uint32_t ADC_RX_RDY_INT_RAW_STATUS      : 1  ; // 6  : 6
    __IO uint32_t ADC_FIFO_UNF_INT_RAW_STATUS    : 1  ; // 7  : 7
    __IO uint32_t BUS_IDLE_DET_INT_RAW_STATUS    : 1  ; // 8  : 8
    __IO uint32_t WAKE_UP_DET_INT_RAW_STATUS     : 1  ; // 9  : 9
    __IO uint32_t SLV_TX_BRK_DONE_INT_RAW_STATUS : 1  ; // 10 : 10
    __IO uint32_t MP_MODE_ADDR_INT_RAW_STATUS    : 1  ; // 11 : 11
    __IO uint32_t AUTO_ADDR_START_INT_RAW_STATUS : 1  ; // 12 : 12
    __IO uint32_t AUTO_ADDR_1BIT_INT_RAW_STATUS  : 1  ; // 13 : 13
    __IO uint32_t RESERVED0                      : 18 ; // 31 : 14
} AFE_SYSCFG_IRSR1_FIELD_T;

typedef struct
{
    __IO uint32_t GPIO_DATAOUT                   : 1  ; // 0  : 0
    __IO uint32_t GPIO_OUTEN_SET                 : 1  ; // 1  : 1
    __IO uint32_t GPIO_OUTEN_CLR                 : 1  ; // 2  : 2
    __IO uint32_t RESERVED1                      : 1  ; // 3  : 3
    __IO uint32_t GPIO_INT_POL_SEL               : 1  ; // 4  : 4
    __IO uint32_t GPIO_INT_TYP_SEL               : 1  ; // 5  : 5
    __IO uint32_t GPIO_DATAIN                    : 1  ; // 6  : 6
    __IO uint32_t RESERVED0                      : 25 ; // 31 : 7
} AFE_SYSCFG_GPIO_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t INT_SNS_EN                     : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                      : 31 ; // 31 : 1
} AFE_SYSCFG_INT_SNS_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t ACTIVE_BIAS_EN                 : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                      : 31 ; // 31 : 1
} AFE_SYSCFG_BIAS_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t OTP_OUT                        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                      : 31 ; // 31 : 1
} AFE_SYSCFG_OTP_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t WAKE_UP_DET_EN                 : 1  ; // 0  : 0
    __IO uint32_t RESERVED1                      : 3  ; // 3  : 1
    __IO uint32_t WAKE_UP_TIM                    : 4  ; // 7  : 4
    __IO uint32_t RESERVED0                      : 24 ; // 31 : 8
} AFE_SYSCFG_LIN_WU_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t SYSCFG_LOCK                    : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                      : 31 ; // 31 : 1
} AFE_SYSCFG_SYSCFG_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t REVISION                    ; // 0x0000
        AFE_SYSCFG_REVISION_FIELD_T REVISION_F     ;
    };

    union
    {
        __IO  uint32_t IMR0                        ; // 0x0004
        AFE_SYSCFG_IMR0_FIELD_T IMR0_F             ;
    };

    union
    {
        __IO  uint32_t ICR0                        ; // 0x0008
        AFE_SYSCFG_ICR0_FIELD_T ICR0_F             ;
    };

    union
    {
        __IO  uint32_t ISR0                        ; // 0x000C
        AFE_SYSCFG_ISR0_FIELD_T ISR0_F             ;
    };

    union
    {
        __IO  uint32_t IRSR0                       ; // 0x0010
        AFE_SYSCFG_IRSR0_FIELD_T IRSR0_F           ;
    };

    union
    {
        __IO  uint32_t IMR1                        ; // 0x0014
        AFE_SYSCFG_IMR1_FIELD_T IMR1_F             ;
    };

    union
    {
        __IO  uint32_t ICR1                        ; // 0x0018
        AFE_SYSCFG_ICR1_FIELD_T ICR1_F             ;
    };

    union
    {
        __IO  uint32_t ISR1                        ; // 0x001C
        AFE_SYSCFG_ISR1_FIELD_T ISR1_F             ;
    };

    union
    {
        __IO  uint32_t IRSR1                       ; // 0x0020
        AFE_SYSCFG_IRSR1_FIELD_T IRSR1_F           ;
    };

    union
    {
        __IO  uint32_t GPIO_CTRL                   ; // 0x0024
        AFE_SYSCFG_GPIO_CTRL_FIELD_T GPIO_CTRL_F   ;
    };

    union
    {
        __IO  uint32_t INT_SNS_CTRL                ; // 0x0028
        AFE_SYSCFG_INT_SNS_CTRL_FIELD_T INT_SNS_CTRL_F;
    };

    union
    {
        __IO  uint32_t BIAS_CTRL                   ; // 0x002C
        AFE_SYSCFG_BIAS_CTRL_FIELD_T BIAS_CTRL_F   ;
    };

    union
    {
        __IO  uint32_t OTP_STATUS                  ; // 0x0030
        AFE_SYSCFG_OTP_STATUS_FIELD_T OTP_STATUS_F ;
    };

    union
    {
        __IO  uint32_t LIN_WU_CTRL                 ; // 0x0034
        AFE_SYSCFG_LIN_WU_CTRL_FIELD_T LIN_WU_CTRL_F;
    };

    uint32_t RESERVED0[49]                          ;

    union
    {
        __IO  uint32_t SYSCFG_LOCK                 ; // 0x00FC
        AFE_SYSCFG_SYSCFG_LOCK_FIELD_T SYSCFG_LOCK_F;
    };

} AFE_SYSCFG_REG_TypeDef;

#endif
