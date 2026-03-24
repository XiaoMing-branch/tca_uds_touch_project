/**
 *****************************************************************************
 * @brief   spi_reg_def header file.
 *
 * @file    spi_reg_def.h
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

#ifndef   SPI_DEF_H__
#define   SPI_DEF_H__

// Register Offset Macro Definition
#define SPI_CR0_OFFSET                                          0x0000
#define SPI_CR1_OFFSET                                          0x0004
#define SPI_CPSR_OFFSET                                         0x0008
#define SPI_WDR_OFFSET                                          0x000C
#define SPI_RDR_OFFSET                                          0x0010
#define SPI_SR_OFFSET                                           0x0014
#define SPI_IMR_OFFSET                                          0x0018
#define SPI_IRSR_OFFSET                                         0x001C
#define SPI_ISR_OFFSET                                          0x0020
#define SPI_ICR_OFFSET                                          0x0024
#define SPI_CRCR_OFFSET                                         0x0028
#define SPI_DEBUG_OFFSET                                        0x0080

// Register Address Macro Definition
#define SPI_CR0_ADDR                                            ( SPI_BASE_ADDR + SPI_CR0_OFFSET)
#define SPI_CR1_ADDR                                            ( SPI_BASE_ADDR + SPI_CR1_OFFSET)
#define SPI_CPSR_ADDR                                           ( SPI_BASE_ADDR + SPI_CPSR_OFFSET)
#define SPI_WDR_ADDR                                            ( SPI_BASE_ADDR + SPI_WDR_OFFSET)
#define SPI_RDR_ADDR                                            ( SPI_BASE_ADDR + SPI_RDR_OFFSET)
#define SPI_SR_ADDR                                             ( SPI_BASE_ADDR + SPI_SR_OFFSET)
#define SPI_IMR_ADDR                                            ( SPI_BASE_ADDR + SPI_IMR_OFFSET)
#define SPI_IRSR_ADDR                                           ( SPI_BASE_ADDR + SPI_IRSR_OFFSET)
#define SPI_ISR_ADDR                                            ( SPI_BASE_ADDR + SPI_ISR_OFFSET)
#define SPI_ICR_ADDR                                            ( SPI_BASE_ADDR + SPI_ICR_OFFSET)
#define SPI_CRCR_ADDR                                           ( SPI_BASE_ADDR + SPI_CRCR_OFFSET)
#define SPI_DEBUG_ADDR                                          ( SPI_BASE_ADDR + SPI_DEBUG_OFFSET)

// Register Field Macro Definition
#define SPI_CR0_TX_CONF_DET_EN_SHIFT                          15
#define SPI_CR0_TX_CONF_DET_EN_MASK                           0x00008000
#define SPI_CR0_TX_CONF_DET_EN_SET(n)                         (((uint32_t)(n) << 15 ) & 0x00008000)
#define SPI_CR0_TX_CONF_DET_EN_CLR                            0xFFFF7FFF

#define SPI_CR0_L_FRAME_EN_SHIFT                              14
#define SPI_CR0_L_FRAME_EN_MASK                               0x00004000
#define SPI_CR0_L_FRAME_EN_SET(n)                             (((uint32_t)(n) << 14 ) & 0x00004000)
#define SPI_CR0_L_FRAME_EN_CLR                                0xFFFFBFFF

#define SPI_CR0_CSN_POL_SEL_SHIFT                             13
#define SPI_CR0_CSN_POL_SEL_MASK                              0x00002000
#define SPI_CR0_CSN_POL_SEL_SET(n)                            (((uint32_t)(n) << 13 ) & 0x00002000)
#define SPI_CR0_CSN_POL_SEL_CLR                               0xFFFFDFFF

#define SPI_CR0_CRC_EN_SHIFT                                  12
#define SPI_CR0_CRC_EN_MASK                                   0x00001000
#define SPI_CR0_CRC_EN_SET(n)                                 (((uint32_t)(n) << 12 ) & 0x00001000)
#define SPI_CR0_CRC_EN_CLR                                    0xFFFFEFFF

#define SPI_CR0_WIRE_MODE_4_SHIFT                             11
#define SPI_CR0_WIRE_MODE_4_MASK                              0x00000800
#define SPI_CR0_WIRE_MODE_4_SET(n)                            (((uint32_t)(n) << 11 ) & 0x00000800)
#define SPI_CR0_WIRE_MODE_4_CLR                               0xFFFFF7FF

#define SPI_CR0_LSB_FIRST_SHIFT                               10
#define SPI_CR0_LSB_FIRST_MASK                                0x00000400
#define SPI_CR0_LSB_FIRST_SET(n)                              (((uint32_t)(n) << 10 ) & 0x00000400)
#define SPI_CR0_LSB_FIRST_CLR                                 0xFFFFFBFF

#define SPI_CR0_SPH_SHIFT                                     9
#define SPI_CR0_SPH_MASK                                      0x00000200
#define SPI_CR0_SPH_SET(n)                                    (((uint32_t)(n) << 9  ) & 0x00000200)
#define SPI_CR0_SPH_CLR                                       0xFFFFFDFF

#define SPI_CR0_SPO_SHIFT                                     8
#define SPI_CR0_SPO_MASK                                      0x00000100
#define SPI_CR0_SPO_SET(n)                                    (((uint32_t)(n) << 8  ) & 0x00000100)
#define SPI_CR0_SPO_CLR                                       0xFFFFFEFF

#define SPI_CR0_INS_SIZE_SHIFT                                7
#define SPI_CR0_INS_SIZE_MASK                                 0x00000080
#define SPI_CR0_INS_SIZE_SET(n)                               (((uint32_t)(n) << 7  ) & 0x00000080)
#define SPI_CR0_INS_SIZE_CLR                                  0xFFFFFF7F

#define SPI_CR0_DATA_SIZE_DIS_SHIFT                           6
#define SPI_CR0_DATA_SIZE_DIS_MASK                            0x00000040
#define SPI_CR0_DATA_SIZE_DIS_SET(n)                          (((uint32_t)(n) << 6  ) & 0x00000040)
#define SPI_CR0_DATA_SIZE_DIS_CLR                             0xFFFFFFBF

#define SPI_CR0_DATA_SIZE_SHIFT                               4
#define SPI_CR0_DATA_SIZE_MASK                                0x00000030
#define SPI_CR0_DATA_SIZE_SET(n)                              (((uint32_t)(n) << 4  ) & 0x00000030)
#define SPI_CR0_DATA_SIZE_CLR                                 0xFFFFFFCF

#define SPI_CR0_IO_DIS_SHIFT                                  3
#define SPI_CR0_IO_DIS_MASK                                   0x00000008
#define SPI_CR0_IO_DIS_SET(n)                                 (((uint32_t)(n) << 3  ) & 0x00000008)
#define SPI_CR0_IO_DIS_CLR                                    0xFFFFFFF7

#define SPI_CR0_SLV_MODE_SHIFT                                2
#define SPI_CR0_SLV_MODE_MASK                                 0x00000004
#define SPI_CR0_SLV_MODE_SET(n)                               (((uint32_t)(n) << 2  ) & 0x00000004)
#define SPI_CR0_SLV_MODE_CLR                                  0xFFFFFFFB

#define SPI_CR0_LP_BACK_EN_SHIFT                              1
#define SPI_CR0_LP_BACK_EN_MASK                               0x00000002
#define SPI_CR0_LP_BACK_EN_SET(n)                             (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_CR0_LP_BACK_EN_CLR                                0xFFFFFFFD

#define SPI_CR0_SPI_EN_SHIFT                                  0
#define SPI_CR0_SPI_EN_MASK                                   0x00000001
#define SPI_CR0_SPI_EN_SET(n)                                 (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_CR0_SPI_EN_CLR                                    0xFFFFFFFE

#define SPI_CR1_RX_FIFO_CLR_SHIFT                             5
#define SPI_CR1_RX_FIFO_CLR_MASK                              0x00000020
#define SPI_CR1_RX_FIFO_CLR_SET(n)                            (((uint32_t)(n) << 5  ) & 0x00000020)
#define SPI_CR1_RX_FIFO_CLR_CLR                               0xFFFFFFDF

#define SPI_CR1_TX_FIFO_CLR_SHIFT                             4
#define SPI_CR1_TX_FIFO_CLR_MASK                              0x00000010
#define SPI_CR1_TX_FIFO_CLR_SET(n)                            (((uint32_t)(n) << 4  ) & 0x00000010)
#define SPI_CR1_TX_FIFO_CLR_CLR                               0xFFFFFFEF

#define SPI_CR1_RX_FIFO_INT_TH_SHIFT                          2
#define SPI_CR1_RX_FIFO_INT_TH_MASK                           0x0000000C
#define SPI_CR1_RX_FIFO_INT_TH_SET(n)                         (((uint32_t)(n) << 2  ) & 0x0000000C)
#define SPI_CR1_RX_FIFO_INT_TH_CLR                            0xFFFFFFF3

#define SPI_CR1_TX_FIFO_INT_TH_SHIFT                          0
#define SPI_CR1_TX_FIFO_INT_TH_MASK                           0x00000003
#define SPI_CR1_TX_FIFO_INT_TH_SET(n)                         (((uint32_t)(n) << 0  ) & 0x00000003)
#define SPI_CR1_TX_FIFO_INT_TH_CLR                            0xFFFFFFFC

#define SPI_CPSR_FCLK_DIV_SHIFT                               0
#define SPI_CPSR_FCLK_DIV_MASK                                0x0000000F
#define SPI_CPSR_FCLK_DIV_SET(n)                              (((uint32_t)(n) << 0  ) & 0x0000000F)
#define SPI_CPSR_FCLK_DIV_CLR                                 0xFFFFFFF0

#define SPI_WDR_TX_DATA_SHIFT                                 0
#define SPI_WDR_TX_DATA_MASK                                  0xFFFFFFFF
#define SPI_WDR_TX_DATA_SET(n)                                (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define SPI_WDR_TX_DATA_CLR                                   0x00000000

#define SPI_RDR_RX_DATA_SHIFT                                 0
#define SPI_RDR_RX_DATA_MASK                                  0xFFFFFFFF
#define SPI_RDR_RX_DATA_SET(n)                                (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define SPI_RDR_RX_DATA_CLR                                   0x00000000

#define SPI_SR_BSY_FLG_SHIFT                                  4
#define SPI_SR_BSY_FLG_MASK                                   0x00000010
#define SPI_SR_BSY_FLG_SET(n)                                 (((uint32_t)(n) << 4  ) & 0x00000010)
#define SPI_SR_BSY_FLG_CLR                                    0xFFFFFFEF

#define SPI_SR_RX_FIFO_FULL_FLG_SHIFT                         3
#define SPI_SR_RX_FIFO_FULL_FLG_MASK                          0x00000008
#define SPI_SR_RX_FIFO_FULL_FLG_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define SPI_SR_RX_FIFO_FULL_FLG_CLR                           0xFFFFFFF7

#define SPI_SR_RX_FIFO_EMPTY_FLG_SHIFT                        2
#define SPI_SR_RX_FIFO_EMPTY_FLG_MASK                         0x00000004
#define SPI_SR_RX_FIFO_EMPTY_FLG_SET(n)                       (((uint32_t)(n) << 2  ) & 0x00000004)
#define SPI_SR_RX_FIFO_EMPTY_FLG_CLR                          0xFFFFFFFB

#define SPI_SR_TX_FIFO_FULL_FLG_SHIFT                         1
#define SPI_SR_TX_FIFO_FULL_FLG_MASK                          0x00000002
#define SPI_SR_TX_FIFO_FULL_FLG_SET(n)                        (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_SR_TX_FIFO_FULL_FLG_CLR                           0xFFFFFFFD

#define SPI_SR_TX_FIFO_EMPTY_FLG_SHIFT                        0
#define SPI_SR_TX_FIFO_EMPTY_FLG_MASK                         0x00000001
#define SPI_SR_TX_FIFO_EMPTY_FLG_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_SR_TX_FIFO_EMPTY_FLG_CLR                          0xFFFFFFFE

#define SPI_IMR_TX_CONF_ERR_INT_MSK_SHIFT                     5
#define SPI_IMR_TX_CONF_ERR_INT_MSK_MASK                      0x00000020
#define SPI_IMR_TX_CONF_ERR_INT_MSK_SET(n)                    (((uint32_t)(n) << 5  ) & 0x00000020)
#define SPI_IMR_TX_CONF_ERR_INT_MSK_CLR                       0xFFFFFFDF

#define SPI_IMR_CRC_ERR_INT_MSK_SHIFT                         4
#define SPI_IMR_CRC_ERR_INT_MSK_MASK                          0x00000010
#define SPI_IMR_CRC_ERR_INT_MSK_SET(n)                        (((uint32_t)(n) << 4  ) & 0x00000010)
#define SPI_IMR_CRC_ERR_INT_MSK_CLR                           0xFFFFFFEF

#define SPI_IMR_INS_RX_FIN_INT_MSK_SHIFT                      3
#define SPI_IMR_INS_RX_FIN_INT_MSK_MASK                       0x00000008
#define SPI_IMR_INS_RX_FIN_INT_MSK_SET(n)                     (((uint32_t)(n) << 3  ) & 0x00000008)
#define SPI_IMR_INS_RX_FIN_INT_MSK_CLR                        0xFFFFFFF7

#define SPI_IMR_TX_FIFO_INT_MSK_SHIFT                         2
#define SPI_IMR_TX_FIFO_INT_MSK_MASK                          0x00000004
#define SPI_IMR_TX_FIFO_INT_MSK_SET(n)                        (((uint32_t)(n) << 2  ) & 0x00000004)
#define SPI_IMR_TX_FIFO_INT_MSK_CLR                           0xFFFFFFFB

#define SPI_IMR_RX_FIFO_INT_MSK_SHIFT                         1
#define SPI_IMR_RX_FIFO_INT_MSK_MASK                          0x00000002
#define SPI_IMR_RX_FIFO_INT_MSK_SET(n)                        (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_IMR_RX_FIFO_INT_MSK_CLR                           0xFFFFFFFD

#define SPI_IMR_RX_FIFO_OR_INT_MSK_SHIFT                      0
#define SPI_IMR_RX_FIFO_OR_INT_MSK_MASK                       0x00000001
#define SPI_IMR_RX_FIFO_OR_INT_MSK_SET(n)                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_IMR_RX_FIFO_OR_INT_MSK_CLR                        0xFFFFFFFE

#define SPI_IRSR_TX_CONF_ERR_INT_RST_SHIFT                    5
#define SPI_IRSR_TX_CONF_ERR_INT_RST_MASK                     0x00000020
#define SPI_IRSR_TX_CONF_ERR_INT_RST_SET(n)                   (((uint32_t)(n) << 5  ) & 0x00000020)
#define SPI_IRSR_TX_CONF_ERR_INT_RST_CLR                      0xFFFFFFDF

#define SPI_IRSR_CRC_ERR_INT_RST_SHIFT                        4
#define SPI_IRSR_CRC_ERR_INT_RST_MASK                         0x00000010
#define SPI_IRSR_CRC_ERR_INT_RST_SET(n)                       (((uint32_t)(n) << 4  ) & 0x00000010)
#define SPI_IRSR_CRC_ERR_INT_RST_CLR                          0xFFFFFFEF

#define SPI_IRSR_INS_RX_FIN_INT_RST_SHIFT                     3
#define SPI_IRSR_INS_RX_FIN_INT_RST_MASK                      0x00000008
#define SPI_IRSR_INS_RX_FIN_INT_RST_SET(n)                    (((uint32_t)(n) << 3  ) & 0x00000008)
#define SPI_IRSR_INS_RX_FIN_INT_RST_CLR                       0xFFFFFFF7

#define SPI_IRSR_TX_FIFO_INT_RST_SHIFT                        2
#define SPI_IRSR_TX_FIFO_INT_RST_MASK                         0x00000004
#define SPI_IRSR_TX_FIFO_INT_RST_SET(n)                       (((uint32_t)(n) << 2  ) & 0x00000004)
#define SPI_IRSR_TX_FIFO_INT_RST_CLR                          0xFFFFFFFB

#define SPI_IRSR_RX_FIFO_INT_RST_SHIFT                        1
#define SPI_IRSR_RX_FIFO_INT_RST_MASK                         0x00000002
#define SPI_IRSR_RX_FIFO_INT_RST_SET(n)                       (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_IRSR_RX_FIFO_INT_RST_CLR                          0xFFFFFFFD

#define SPI_IRSR_RX_FIFO_OR_INT_RST_SHIFT                     0
#define SPI_IRSR_RX_FIFO_OR_INT_RST_MASK                      0x00000001
#define SPI_IRSR_RX_FIFO_OR_INT_RST_SET(n)                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_IRSR_RX_FIFO_OR_INT_RST_CLR                       0xFFFFFFFE

#define SPI_ISR_TX_CONF_ERR_INT_ST_SHIFT                      5
#define SPI_ISR_TX_CONF_ERR_INT_ST_MASK                       0x00000020
#define SPI_ISR_TX_CONF_ERR_INT_ST_SET(n)                     (((uint32_t)(n) << 5  ) & 0x00000020)
#define SPI_ISR_TX_CONF_ERR_INT_ST_CLR                        0xFFFFFFDF

#define SPI_ISR_CRC_ERR_INT_ST_SHIFT                          4
#define SPI_ISR_CRC_ERR_INT_ST_MASK                           0x00000010
#define SPI_ISR_CRC_ERR_INT_ST_SET(n)                         (((uint32_t)(n) << 4  ) & 0x00000010)
#define SPI_ISR_CRC_ERR_INT_ST_CLR                            0xFFFFFFEF

#define SPI_ISR_INS_RX_FIN_INT_ST_SHIFT                       3
#define SPI_ISR_INS_RX_FIN_INT_ST_MASK                        0x00000008
#define SPI_ISR_INS_RX_FIN_INT_ST_SET(n)                      (((uint32_t)(n) << 3  ) & 0x00000008)
#define SPI_ISR_INS_RX_FIN_INT_ST_CLR                         0xFFFFFFF7

#define SPI_ISR_TX_FIFO_INT_ST_SHIFT                          2
#define SPI_ISR_TX_FIFO_INT_ST_MASK                           0x00000004
#define SPI_ISR_TX_FIFO_INT_ST_SET(n)                         (((uint32_t)(n) << 2  ) & 0x00000004)
#define SPI_ISR_TX_FIFO_INT_ST_CLR                            0xFFFFFFFB

#define SPI_ISR_RX_FIFO_INT_ST_SHIFT                          1
#define SPI_ISR_RX_FIFO_INT_ST_MASK                           0x00000002
#define SPI_ISR_RX_FIFO_INT_ST_SET(n)                         (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_ISR_RX_FIFO_INT_ST_CLR                            0xFFFFFFFD

#define SPI_ISR_RX_FIFO_OR_INT_ST_SHIFT                       0
#define SPI_ISR_RX_FIFO_OR_INT_ST_MASK                        0x00000001
#define SPI_ISR_RX_FIFO_OR_INT_ST_SET(n)                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_ISR_RX_FIFO_OR_INT_ST_CLR                         0xFFFFFFFE

#define SPI_ICR_TX_CONF_ERR_INT_CLR_SHIFT                     5
#define SPI_ICR_TX_CONF_ERR_INT_CLR_MASK                      0x00000020
#define SPI_ICR_TX_CONF_ERR_INT_CLR_SET(n)                    (((uint32_t)(n) << 5  ) & 0x00000020)
#define SPI_ICR_TX_CONF_ERR_INT_CLR_CLR                       0xFFFFFFDF

#define SPI_ICR_CRC_ERR_INT_CLR_SHIFT                         4
#define SPI_ICR_CRC_ERR_INT_CLR_MASK                          0x00000010
#define SPI_ICR_CRC_ERR_INT_CLR_SET(n)                        (((uint32_t)(n) << 4  ) & 0x00000010)
#define SPI_ICR_CRC_ERR_INT_CLR_CLR                           0xFFFFFFEF

#define SPI_ICR_INS_RX_FIN_INT_CLR_SHIFT                      3
#define SPI_ICR_INS_RX_FIN_INT_CLR_MASK                       0x00000008
#define SPI_ICR_INS_RX_FIN_INT_CLR_SET(n)                     (((uint32_t)(n) << 3  ) & 0x00000008)
#define SPI_ICR_INS_RX_FIN_INT_CLR_CLR                        0xFFFFFFF7

#define SPI_ICR_TX_FIFO_INT_CLR_SHIFT                         2
#define SPI_ICR_TX_FIFO_INT_CLR_MASK                          0x00000004
#define SPI_ICR_TX_FIFO_INT_CLR_SET(n)                        (((uint32_t)(n) << 2  ) & 0x00000004)
#define SPI_ICR_TX_FIFO_INT_CLR_CLR                           0xFFFFFFFB

#define SPI_ICR_RX_FIFO_INT_CLR_SHIFT                         1
#define SPI_ICR_RX_FIFO_INT_CLR_MASK                          0x00000002
#define SPI_ICR_RX_FIFO_INT_CLR_SET(n)                        (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_ICR_RX_FIFO_INT_CLR_CLR                           0xFFFFFFFD

#define SPI_ICR_RX_FIFO_OR_INT_CLR_SHIFT                      0
#define SPI_ICR_RX_FIFO_OR_INT_CLR_MASK                       0x00000001
#define SPI_ICR_RX_FIFO_OR_INT_CLR_SET(n)                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_ICR_RX_FIFO_OR_INT_CLR_CLR                        0xFFFFFFFE

#define SPI_CRCR_SFT_CRC_DOUT_SHIFT                           24
#define SPI_CRCR_SFT_CRC_DOUT_MASK                            0xFF000000
#define SPI_CRCR_SFT_CRC_DOUT_SET(n)                          (((uint32_t)(n) << 24 ) & 0xFF000000)
#define SPI_CRCR_SFT_CRC_DOUT_CLR                             0x00FFFFFF

#define SPI_CRCR_SFT_DIN_SHIFT                                16
#define SPI_CRCR_SFT_DIN_MASK                                 0x00FF0000
#define SPI_CRCR_SFT_DIN_SET(n)                               (((uint32_t)(n) << 16 ) & 0x00FF0000)
#define SPI_CRCR_SFT_DIN_CLR                                  0xFF00FFFF

#define SPI_CRCR_SFT_CRC_INI_VALUE_SHIFT                      8
#define SPI_CRCR_SFT_CRC_INI_VALUE_MASK                       0x0000FF00
#define SPI_CRCR_SFT_CRC_INI_VALUE_SET(n)                     (((uint32_t)(n) << 8  ) & 0x0000FF00)
#define SPI_CRCR_SFT_CRC_INI_VALUE_CLR                        0xFFFF00FF

#define SPI_CRCR_CRC8_POLY_SEL_SHIFT                          1
#define SPI_CRCR_CRC8_POLY_SEL_MASK                           0x00000002
#define SPI_CRCR_CRC8_POLY_SEL_SET(n)                         (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_CRCR_CRC8_POLY_SEL_CLR                            0xFFFFFFFD

#define SPI_CRCR_SFT_CRC_UNIT_EN_SHIFT                        0
#define SPI_CRCR_SFT_CRC_UNIT_EN_MASK                         0x00000001
#define SPI_CRCR_SFT_CRC_UNIT_EN_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_CRCR_SFT_CRC_UNIT_EN_CLR                          0xFFFFFFFE

#define SPI_DEBUG_SCLK_SYNC_MODE_SHIFT                        1
#define SPI_DEBUG_SCLK_SYNC_MODE_MASK                         0x00000002
#define SPI_DEBUG_SCLK_SYNC_MODE_SET(n)                       (((uint32_t)(n) << 1  ) & 0x00000002)
#define SPI_DEBUG_SCLK_SYNC_MODE_CLR                          0xFFFFFFFD

#define SPI_DEBUG_RXD_SYNC_EN_SHIFT                           0
#define SPI_DEBUG_RXD_SYNC_EN_MASK                            0x00000001
#define SPI_DEBUG_RXD_SYNC_EN_SET(n)                          (((uint32_t)(n) << 0  ) & 0x00000001)
#define SPI_DEBUG_RXD_SYNC_EN_CLR                             0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t SPI_EN              : 1  ; // 0  : 0
    __IO uint32_t LP_BACK_EN          : 1  ; // 1  : 1
    __IO uint32_t SLV_MODE            : 1  ; // 2  : 2
    __IO uint32_t IO_DIS              : 1  ; // 3  : 3
    __IO uint32_t DATA_SIZE           : 2  ; // 5  : 4
    __IO uint32_t DATA_SIZE_DIS       : 1  ; // 6  : 6
    __IO uint32_t INS_SIZE            : 1  ; // 7  : 7
    __IO uint32_t SPO                 : 1  ; // 8  : 8
    __IO uint32_t SPH                 : 1  ; // 9  : 9
    __IO uint32_t LSB_FIRST           : 1  ; // 10 : 10
    __IO uint32_t WIRE_MODE_4         : 1  ; // 11 : 11
    __IO uint32_t CRC_EN              : 1  ; // 12 : 12
    __IO uint32_t CSN_POL_SEL         : 1  ; // 13 : 13
    __IO uint32_t L_FRAME_EN          : 1  ; // 14 : 14
    __IO uint32_t TX_CONF_DET_EN      : 1  ; // 15 : 15
    __IO uint32_t RESERVED0           : 16 ; // 31 : 16
} SPI_CR0_FIELD_T;

typedef struct
{
    __IO uint32_t TX_FIFO_INT_TH      : 2  ; // 1  : 0
    __IO uint32_t RX_FIFO_INT_TH      : 2  ; // 3  : 2
    __IO uint32_t TX_FIFO_CLR         : 1  ; // 4  : 4
    __IO uint32_t RX_FIFO_CLR         : 1  ; // 5  : 5
    __IO uint32_t RESERVED0           : 26 ; // 31 : 6
} SPI_CR1_FIELD_T;

typedef struct
{
    __IO uint32_t FCLK_DIV            : 4  ; // 3  : 0
    __IO uint32_t RESERVED0           : 28 ; // 31 : 4
} SPI_CPSR_FIELD_T;

typedef struct
{
    __IO uint32_t TX_DATA             : 32 ; // 31 : 0
} SPI_WDR_FIELD_T;

typedef struct
{
    __IO uint32_t RX_DATA             : 32 ; // 31 : 0
} SPI_RDR_FIELD_T;

typedef struct
{
    __IO uint32_t TX_FIFO_EMPTY_FLG   : 1  ; // 0  : 0
    __IO uint32_t TX_FIFO_FULL_FLG    : 1  ; // 1  : 1
    __IO uint32_t RX_FIFO_EMPTY_FLG   : 1  ; // 2  : 2
    __IO uint32_t RX_FIFO_FULL_FLG    : 1  ; // 3  : 3
    __IO uint32_t BSY_FLG             : 1  ; // 4  : 4
    __IO uint32_t RESERVED0           : 27 ; // 31 : 5
} SPI_SR_FIELD_T;

typedef struct
{
    __IO uint32_t RX_FIFO_OR_INT_MSK  : 1  ; // 0  : 0
    __IO uint32_t RX_FIFO_INT_MSK     : 1  ; // 1  : 1
    __IO uint32_t TX_FIFO_INT_MSK     : 1  ; // 2  : 2
    __IO uint32_t INS_RX_FIN_INT_MSK  : 1  ; // 3  : 3
    __IO uint32_t CRC_ERR_INT_MSK     : 1  ; // 4  : 4
    __IO uint32_t TX_CONF_ERR_INT_MSK : 1  ; // 5  : 5
    __IO uint32_t RESERVED0           : 26 ; // 31 : 6
} SPI_IMR_FIELD_T;

typedef struct
{
    __IO uint32_t RX_FIFO_OR_INT_RST  : 1  ; // 0  : 0
    __IO uint32_t RX_FIFO_INT_RST     : 1  ; // 1  : 1
    __IO uint32_t TX_FIFO_INT_RST     : 1  ; // 2  : 2
    __IO uint32_t INS_RX_FIN_INT_RST  : 1  ; // 3  : 3
    __IO uint32_t CRC_ERR_INT_RST     : 1  ; // 4  : 4
    __IO uint32_t TX_CONF_ERR_INT_RST : 1  ; // 5  : 5
    __IO uint32_t RESERVED0           : 26 ; // 31 : 6
} SPI_IRSR_FIELD_T;

typedef struct
{
    __IO uint32_t RX_FIFO_OR_INT_ST   : 1  ; // 0  : 0
    __IO uint32_t RX_FIFO_INT_ST      : 1  ; // 1  : 1
    __IO uint32_t TX_FIFO_INT_ST      : 1  ; // 2  : 2
    __IO uint32_t INS_RX_FIN_INT_ST   : 1  ; // 3  : 3
    __IO uint32_t CRC_ERR_INT_ST      : 1  ; // 4  : 4
    __IO uint32_t TX_CONF_ERR_INT_ST  : 1  ; // 5  : 5
    __IO uint32_t RESERVED0           : 26 ; // 31 : 6
} SPI_ISR_FIELD_T;

typedef struct
{
    __IO uint32_t RX_FIFO_OR_INT_CLR  : 1  ; // 0  : 0
    __IO uint32_t RX_FIFO_INT_CLR     : 1  ; // 1  : 1
    __IO uint32_t TX_FIFO_INT_CLR     : 1  ; // 2  : 2
    __IO uint32_t INS_RX_FIN_INT_CLR  : 1  ; // 3  : 3
    __IO uint32_t CRC_ERR_INT_CLR     : 1  ; // 4  : 4
    __IO uint32_t TX_CONF_ERR_INT_CLR : 1  ; // 5  : 5
    __IO uint32_t RESERVED0           : 26 ; // 31 : 6
} SPI_ICR_FIELD_T;

typedef struct
{
    __IO uint32_t SFT_CRC_UNIT_EN     : 1  ; // 0  : 0
    __IO uint32_t CRC8_POLY_SEL       : 1  ; // 1  : 1
    __IO uint32_t RESERVED0           : 6  ; // 7  : 2
    __IO uint32_t SFT_CRC_INI_VALUE   : 8  ; // 15 : 8
    __IO uint32_t SFT_DIN             : 8  ; // 23 : 16
    __IO uint32_t SFT_CRC_DOUT        : 8  ; // 31 : 24
} SPI_CRCR_FIELD_T;

typedef struct
{
    __IO uint32_t RXD_SYNC_EN         : 1  ; // 0  : 0
    __IO uint32_t SCLK_SYNC_MODE      : 1  ; // 1  : 1
    __IO uint32_t RESERVED0           : 30 ; // 31 : 2
} SPI_DEBUG_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t CR0           ; // 0x0000
        SPI_CR0_FIELD_T CR0_F        ;
    };

    union
    {
        __IO  uint32_t CR1           ; // 0x0004
        SPI_CR1_FIELD_T CR1_F        ;
    };

    union
    {
        __IO  uint32_t CPSR          ; // 0x0008
        SPI_CPSR_FIELD_T CPSR_F      ;
    };

    union
    {
        __IO  uint32_t WDR           ; // 0x000C
        SPI_WDR_FIELD_T WDR_F        ;
    };

    union
    {
        __IO  uint32_t RDR           ; // 0x0010
        SPI_RDR_FIELD_T RDR_F        ;
    };

    union
    {
        __IO  uint32_t SR            ; // 0x0014
        SPI_SR_FIELD_T SR_F          ;
    };

    union
    {
        __IO  uint32_t IMR           ; // 0x0018
        SPI_IMR_FIELD_T IMR_F        ;
    };

    union
    {
        __IO  uint32_t IRSR          ; // 0x001C
        SPI_IRSR_FIELD_T IRSR_F      ;
    };

    union
    {
        __IO  uint32_t ISR           ; // 0x0020
        SPI_ISR_FIELD_T ISR_F        ;
    };

    union
    {
        __IO  uint32_t ICR           ; // 0x0024
        SPI_ICR_FIELD_T ICR_F        ;
    };

    union
    {
        __IO  uint32_t CRCR          ; // 0x0028
        SPI_CRCR_FIELD_T CRCR_F      ;
    };

    uint32_t RESERVED0[21]            ;

    union
    {
        __IO  uint32_t DEBUG         ; // 0x0080
        SPI_DEBUG_FIELD_T DEBUG_F    ;
    };

} SPI_REG_TypeDef;

#endif
