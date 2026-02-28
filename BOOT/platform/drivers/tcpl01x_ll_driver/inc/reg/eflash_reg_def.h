/**
 *****************************************************************************
 * @brief   eflash_reg_def header file.
 *
 * @file    eflash_reg_def.h
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

#ifndef   EFLASH_DEF_H__
#define   EFLASH_DEF_H__

// Register Offset Macro Definition
#define EFLASH_REVISION_ID_OFFSET                               0x0000
#define EFLASH_RD_TIME_CFG_OFFSET                               0x0004
#define EFLASH_PROG_ERASE_TIME_CFG0_OFFSET                      0x0008
#define EFLASH_PROG_ERASE_TIME_CFG1_OFFSET                      0x000C
#define EFLASH_ERASE_CFG_OFFSET                                 0x0010
#define EFLASH_ERASE_TRIG_OFFSET                                0x0014
#define EFLASH_MISC_CTRL_OFFSET                                 0x0018
#define EFLASH_OP_CTRL_OFFSET                                   0x001C
#define EFLASH_PROG_ADDR_PROT0_OFFSET                           0x0020
#define EFLASH_PROG_ADDR_PROT1_OFFSET                           0x0024
#define EFLASH_ICR_OFFSET                                       0x0028
#define EFLASH_IMR_OFFSET                                       0x002C
#define EFLASH_ISR_OFFSET                                       0x0030
#define EFLASH_IRSR_OFFSET                                      0x0034
#define EFLASH_ERR_ADDR_OFFSET                                  0x0038
#define EFLASH_ERR_WDATA_OFFSET                                 0x003C
#define EFLASH_ERR_RDATA_OFFSET                                 0x0040
#define EFLASH_STATUS_OFFSET                                    0x0044
#define EFLASH_WR_LOCK_OFFSET                                   0x00F8
#define EFLASH_NVR_PROT_OFFSET                                  0x00FC

// Register Address Macro Definition
#define EFLASH_REVISION_ID_ADDR                                 ( EFLASH_BASE_ADDR + EFLASH_REVISION_ID_OFFSET)
#define EFLASH_RD_TIME_CFG_ADDR                                 ( EFLASH_BASE_ADDR + EFLASH_RD_TIME_CFG_OFFSET)
#define EFLASH_PROG_ERASE_TIME_CFG0_ADDR                        ( EFLASH_BASE_ADDR + EFLASH_PROG_ERASE_TIME_CFG0_OFFSET)
#define EFLASH_PROG_ERASE_TIME_CFG1_ADDR                        ( EFLASH_BASE_ADDR + EFLASH_PROG_ERASE_TIME_CFG1_OFFSET)
#define EFLASH_ERASE_CFG_ADDR                                   ( EFLASH_BASE_ADDR + EFLASH_ERASE_CFG_OFFSET)
#define EFLASH_ERASE_TRIG_ADDR                                  ( EFLASH_BASE_ADDR + EFLASH_ERASE_TRIG_OFFSET)
#define EFLASH_MISC_CTRL_ADDR                                   ( EFLASH_BASE_ADDR + EFLASH_MISC_CTRL_OFFSET)
#define EFLASH_OP_CTRL_ADDR                                     ( EFLASH_BASE_ADDR + EFLASH_OP_CTRL_OFFSET)
#define EFLASH_PROG_ADDR_PROT0_ADDR                             ( EFLASH_BASE_ADDR + EFLASH_PROG_ADDR_PROT0_OFFSET)
#define EFLASH_PROG_ADDR_PROT1_ADDR                             ( EFLASH_BASE_ADDR + EFLASH_PROG_ADDR_PROT1_OFFSET)
#define EFLASH_ICR_ADDR                                         ( EFLASH_BASE_ADDR + EFLASH_ICR_OFFSET)
#define EFLASH_IMR_ADDR                                         ( EFLASH_BASE_ADDR + EFLASH_IMR_OFFSET)
#define EFLASH_ISR_ADDR                                         ( EFLASH_BASE_ADDR + EFLASH_ISR_OFFSET)
#define EFLASH_IRSR_ADDR                                        ( EFLASH_BASE_ADDR + EFLASH_IRSR_OFFSET)
#define EFLASH_ERR_ADDR_ADDR                                    ( EFLASH_BASE_ADDR + EFLASH_ERR_ADDR_OFFSET)
#define EFLASH_ERR_WDATA_ADDR                                   ( EFLASH_BASE_ADDR + EFLASH_ERR_WDATA_OFFSET)
#define EFLASH_ERR_RDATA_ADDR                                   ( EFLASH_BASE_ADDR + EFLASH_ERR_RDATA_OFFSET)
#define EFLASH_STATUS_ADDR                                      ( EFLASH_BASE_ADDR + EFLASH_STATUS_OFFSET)
#define EFLASH_WR_LOCK_ADDR                                     ( EFLASH_BASE_ADDR + EFLASH_WR_LOCK_OFFSET)
#define EFLASH_NVR_PROT_ADDR                                    ( EFLASH_BASE_ADDR + EFLASH_NVR_PROT_OFFSET)

// Register Field Macro Definition
#define EFLASH_REVISION_ID_REVISION_ID_SHIFT                                                     0
#define EFLASH_REVISION_ID_REVISION_ID_MASK                                                      0x000000FF
#define EFLASH_REVISION_ID_REVISION_ID_SET(n)                                                    (((uint32_t)(n) << 0  ) & 0x000000FF)
#define EFLASH_REVISION_ID_REVISION_ID_CLR                                                       0xFFFFFF00

#define EFLASH_RD_TIME_CFG_RC_CYC_SHIFT                                                          0
#define EFLASH_RD_TIME_CFG_RC_CYC_MASK                                                           0x0000000F
#define EFLASH_RD_TIME_CFG_RC_CYC_SET(n)                                                         (((uint32_t)(n) << 0  ) & 0x0000000F)
#define EFLASH_RD_TIME_CFG_RC_CYC_CLR                                                            0xFFFFFFF0

#define EFLASH_PROG_ERASE_TIME_CFG0_ECHIP_RCV_CYC_SHIFT                                          22
#define EFLASH_PROG_ERASE_TIME_CFG0_ECHIP_RCV_CYC_MASK                                           0xFFC00000
#define EFLASH_PROG_ERASE_TIME_CFG0_ECHIP_RCV_CYC_SET(n)                                         (((uint32_t)(n) << 22 ) & 0xFFC00000)
#define EFLASH_PROG_ERASE_TIME_CFG0_ECHIP_RCV_CYC_CLR                                            0x003FFFFF

#define EFLASH_PROG_ERASE_TIME_CFG0_ESECT_RCV_CYC_SHIFT                                          12
#define EFLASH_PROG_ERASE_TIME_CFG0_ESECT_RCV_CYC_MASK                                           0x003FF000
#define EFLASH_PROG_ERASE_TIME_CFG0_ESECT_RCV_CYC_SET(n)                                         (((uint32_t)(n) << 12 ) & 0x003FF000)
#define EFLASH_PROG_ERASE_TIME_CFG0_ESECT_RCV_CYC_CLR                                            0xFFC00FFF

#define EFLASH_PROG_ERASE_TIME_CFG0_PROG_RCV_CYC_SHIFT                                           6
#define EFLASH_PROG_ERASE_TIME_CFG0_PROG_RCV_CYC_MASK                                            0x00000FC0
#define EFLASH_PROG_ERASE_TIME_CFG0_PROG_RCV_CYC_SET(n)                                          (((uint32_t)(n) << 6  ) & 0x00000FC0)
#define EFLASH_PROG_ERASE_TIME_CFG0_PROG_RCV_CYC_CLR                                             0xFFFFF03F

#define EFLASH_PROG_ERASE_TIME_CFG0_NVS_CYC_SHIFT                                                0
#define EFLASH_PROG_ERASE_TIME_CFG0_NVS_CYC_MASK                                                 0x0000003F
#define EFLASH_PROG_ERASE_TIME_CFG0_NVS_CYC_SET(n)                                               (((uint32_t)(n) << 0  ) & 0x0000003F)
#define EFLASH_PROG_ERASE_TIME_CFG0_NVS_CYC_CLR                                                  0xFFFFFFC0

#define EFLASH_PROG_ERASE_TIME_CFG1_LATENCY_CYC_SHIFT                                            29
#define EFLASH_PROG_ERASE_TIME_CFG1_LATENCY_CYC_MASK                                             0xE0000000
#define EFLASH_PROG_ERASE_TIME_CFG1_LATENCY_CYC_SET(n)                                           (((uint32_t)(n) << 29 ) & 0xE0000000)
#define EFLASH_PROG_ERASE_TIME_CFG1_LATENCY_CYC_CLR                                              0x1FFFFFFF

#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_CHIP_CYC_SHIFT                                         21
#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_CHIP_CYC_MASK                                          0x1FE00000
#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_CHIP_CYC_SET(n)                                        (((uint32_t)(n) << 21 ) & 0x1FE00000)
#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_CHIP_CYC_CLR                                           0xE01FFFFF

#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_SECT_CYC_SHIFT                                         16
#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_SECT_CYC_MASK                                          0x001F0000
#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_SECT_CYC_SET(n)                                        (((uint32_t)(n) << 16 ) & 0x001F0000)
#define EFLASH_PROG_ERASE_TIME_CFG1_ERASE_SECT_CYC_CLR                                           0xFFE0FFFF

#define EFLASH_PROG_ERASE_TIME_CFG1_PROG_CYC_SHIFT                                               11
#define EFLASH_PROG_ERASE_TIME_CFG1_PROG_CYC_MASK                                                0x0000F800
#define EFLASH_PROG_ERASE_TIME_CFG1_PROG_CYC_SET(n)                                              (((uint32_t)(n) << 11 ) & 0x0000F800)
#define EFLASH_PROG_ERASE_TIME_CFG1_PROG_CYC_CLR                                                 0xFFFF07FF

#define EFLASH_PROG_ERASE_TIME_CFG1_ADH_CYC_SHIFT                                                9
#define EFLASH_PROG_ERASE_TIME_CFG1_ADH_CYC_MASK                                                 0x00000600
#define EFLASH_PROG_ERASE_TIME_CFG1_ADH_CYC_SET(n)                                               (((uint32_t)(n) << 9  ) & 0x00000600)
#define EFLASH_PROG_ERASE_TIME_CFG1_ADH_CYC_CLR                                                  0xFFFFF9FF

#define EFLASH_PROG_ERASE_TIME_CFG1_ADS_CYC_SHIFT                                                7
#define EFLASH_PROG_ERASE_TIME_CFG1_ADS_CYC_MASK                                                 0x00000180
#define EFLASH_PROG_ERASE_TIME_CFG1_ADS_CYC_SET(n)                                               (((uint32_t)(n) << 7  ) & 0x00000180)
#define EFLASH_PROG_ERASE_TIME_CFG1_ADS_CYC_CLR                                                  0xFFFFFE7F

#define EFLASH_PROG_ERASE_TIME_CFG1_PGH_CYC_SHIFT                                                5
#define EFLASH_PROG_ERASE_TIME_CFG1_PGH_CYC_MASK                                                 0x00000060
#define EFLASH_PROG_ERASE_TIME_CFG1_PGH_CYC_SET(n)                                               (((uint32_t)(n) << 5  ) & 0x00000060)
#define EFLASH_PROG_ERASE_TIME_CFG1_PGH_CYC_CLR                                                  0xFFFFFF9F

#define EFLASH_PROG_ERASE_TIME_CFG1_PGS_CYC_SHIFT                                                0
#define EFLASH_PROG_ERASE_TIME_CFG1_PGS_CYC_MASK                                                 0x0000001F
#define EFLASH_PROG_ERASE_TIME_CFG1_PGS_CYC_SET(n)                                               (((uint32_t)(n) << 0  ) & 0x0000001F)
#define EFLASH_PROG_ERASE_TIME_CFG1_PGS_CYC_CLR                                                  0xFFFFFFE0

#define EFLASH_ERASE_CFG_NVR_SECTOR_SEL_SHIFT                                                    24
#define EFLASH_ERASE_CFG_NVR_SECTOR_SEL_MASK                                                     0x01000000
#define EFLASH_ERASE_CFG_NVR_SECTOR_SEL_SET(n)                                                   (((uint32_t)(n) << 24 ) & 0x01000000)
#define EFLASH_ERASE_CFG_NVR_SECTOR_SEL_CLR                                                      0xFEFFFFFF

#define EFLASH_ERASE_CFG_SECTOR_INDEX_SHIFT                                                      0
#define EFLASH_ERASE_CFG_SECTOR_INDEX_MASK                                                       0x0000007F
#define EFLASH_ERASE_CFG_SECTOR_INDEX_SET(n)                                                     (((uint32_t)(n) << 0  ) & 0x0000007F)
#define EFLASH_ERASE_CFG_SECTOR_INDEX_CLR                                                        0xFFFFFF80

#define EFLASH_ERASE_TRIG_CHIP_ERASE_TRIG_SHIFT                                                  16
#define EFLASH_ERASE_TRIG_CHIP_ERASE_TRIG_MASK                                                   0x00010000
#define EFLASH_ERASE_TRIG_CHIP_ERASE_TRIG_SET(n)                                                 (((uint32_t)(n) << 16 ) & 0x00010000)
#define EFLASH_ERASE_TRIG_CHIP_ERASE_TRIG_CLR                                                    0xFFFEFFFF

#define EFLASH_ERASE_TRIG_SECTOR_ERASE_TRIG_SHIFT                                                0
#define EFLASH_ERASE_TRIG_SECTOR_ERASE_TRIG_MASK                                                 0x00000001
#define EFLASH_ERASE_TRIG_SECTOR_ERASE_TRIG_SET(n)                                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_ERASE_TRIG_SECTOR_ERASE_TRIG_CLR                                                  0xFFFFFFFE

#define EFLASH_MISC_CTRL_CLK1K_DIVISOR_SHIFT                                                     8
#define EFLASH_MISC_CTRL_CLK1K_DIVISOR_MASK                                                      0x00001F00
#define EFLASH_MISC_CTRL_CLK1K_DIVISOR_SET(n)                                                    (((uint32_t)(n) << 8  ) & 0x00001F00)
#define EFLASH_MISC_CTRL_CLK1K_DIVISOR_CLR                                                       0xFFFFE0FF

#define EFLASH_MISC_CTRL_CLK1M_DIVISOR_SHIFT                                                     4
#define EFLASH_MISC_CTRL_CLK1M_DIVISOR_MASK                                                      0x000000F0
#define EFLASH_MISC_CTRL_CLK1M_DIVISOR_SET(n)                                                    (((uint32_t)(n) << 4  ) & 0x000000F0)
#define EFLASH_MISC_CTRL_CLK1M_DIVISOR_CLR                                                       0xFFFFFF0F

#define EFLASH_MISC_CTRL_DEEP_STANDBY_SHIFT                                                      0
#define EFLASH_MISC_CTRL_DEEP_STANDBY_MASK                                                       0x00000001
#define EFLASH_MISC_CTRL_DEEP_STANDBY_SET(n)                                                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_MISC_CTRL_DEEP_STANDBY_CLR                                                        0xFFFFFFFE

#define EFLASH_OP_CTRL_RDONLY_EN_SHIFT                                                           4
#define EFLASH_OP_CTRL_RDONLY_EN_MASK                                                            0x00000010
#define EFLASH_OP_CTRL_RDONLY_EN_SET(n)                                                          (((uint32_t)(n) << 4  ) & 0x00000010)
#define EFLASH_OP_CTRL_RDONLY_EN_CLR                                                             0xFFFFFFEF

#define EFLASH_OP_CTRL_PROG_RD_CHK_EN_SHIFT                                                      2
#define EFLASH_OP_CTRL_PROG_RD_CHK_EN_MASK                                                       0x00000004
#define EFLASH_OP_CTRL_PROG_RD_CHK_EN_SET(n)                                                     (((uint32_t)(n) << 2  ) & 0x00000004)
#define EFLASH_OP_CTRL_PROG_RD_CHK_EN_CLR                                                        0xFFFFFFFB

#define EFLASH_OP_CTRL_PROG_ADDR_CHK_EN_SHIFT                                                    1
#define EFLASH_OP_CTRL_PROG_ADDR_CHK_EN_MASK                                                     0x00000002
#define EFLASH_OP_CTRL_PROG_ADDR_CHK_EN_SET(n)                                                   (((uint32_t)(n) << 1  ) & 0x00000002)
#define EFLASH_OP_CTRL_PROG_ADDR_CHK_EN_CLR                                                      0xFFFFFFFD

#define EFLASH_OP_CTRL_FAST_RD_EN_SHIFT                                                          0
#define EFLASH_OP_CTRL_FAST_RD_EN_MASK                                                           0x00000001
#define EFLASH_OP_CTRL_FAST_RD_EN_SET(n)                                                         (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_OP_CTRL_FAST_RD_EN_CLR                                                            0xFFFFFFFE

#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_END0_SHIFT                                         16
#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_END0_MASK                                          0x3FFF0000
#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_END0_SET(n)                                        (((uint32_t)(n) << 16 ) & 0x3FFF0000)
#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_END0_CLR                                           0xC000FFFF

#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_START0_SHIFT                                       0
#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_START0_MASK                                        0x00003FFF
#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_START0_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00003FFF)
#define EFLASH_PROG_ADDR_PROT0_PROG_ADDR_PROT_START0_CLR                                         0xFFFFC000

#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_END1_SHIFT                                         16
#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_END1_MASK                                          0x3FFF0000
#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_END1_SET(n)                                        (((uint32_t)(n) << 16 ) & 0x3FFF0000)
#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_END1_CLR                                           0xC000FFFF

#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_START1_SHIFT                                       0
#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_START1_MASK                                        0x00003FFF
#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_START1_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00003FFF)
#define EFLASH_PROG_ADDR_PROT1_PROG_ADDR_PROT_START1_CLR                                         0xFFFFC000

#define EFLASH_ICR_ERASE_DONE_INT_CLR_SHIFT                                                      4
#define EFLASH_ICR_ERASE_DONE_INT_CLR_MASK                                                       0x00000010
#define EFLASH_ICR_ERASE_DONE_INT_CLR_SET(n)                                                     (((uint32_t)(n) << 4  ) & 0x00000010)
#define EFLASH_ICR_ERASE_DONE_INT_CLR_CLR                                                        0xFFFFFFEF

#define EFLASH_ICR_PROG_DONE_INT_CLR_SHIFT                                                       3
#define EFLASH_ICR_PROG_DONE_INT_CLR_MASK                                                        0x00000008
#define EFLASH_ICR_PROG_DONE_INT_CLR_SET(n)                                                      (((uint32_t)(n) << 3  ) & 0x00000008)
#define EFLASH_ICR_PROG_DONE_INT_CLR_CLR                                                         0xFFFFFFF7

#define EFLASH_ICR_PROG_RD_CHK_ERR_INT_CLR_SHIFT                                                 2
#define EFLASH_ICR_PROG_RD_CHK_ERR_INT_CLR_MASK                                                  0x00000004
#define EFLASH_ICR_PROG_RD_CHK_ERR_INT_CLR_SET(n)                                                (((uint32_t)(n) << 2  ) & 0x00000004)
#define EFLASH_ICR_PROG_RD_CHK_ERR_INT_CLR_CLR                                                   0xFFFFFFFB

#define EFLASH_ICR_NVR_ACCESS_ERR_INT_CLR_SHIFT                                                  1
#define EFLASH_ICR_NVR_ACCESS_ERR_INT_CLR_MASK                                                   0x00000002
#define EFLASH_ICR_NVR_ACCESS_ERR_INT_CLR_SET(n)                                                 (((uint32_t)(n) << 1  ) & 0x00000002)
#define EFLASH_ICR_NVR_ACCESS_ERR_INT_CLR_CLR                                                    0xFFFFFFFD

#define EFLASH_ICR_NVM_PROG_ADDR_CHK_ERR_INT_CLR_SHIFT                                           0
#define EFLASH_ICR_NVM_PROG_ADDR_CHK_ERR_INT_CLR_MASK                                            0x00000001
#define EFLASH_ICR_NVM_PROG_ADDR_CHK_ERR_INT_CLR_SET(n)                                          (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_ICR_NVM_PROG_ADDR_CHK_ERR_INT_CLR_CLR                                             0xFFFFFFFE

#define EFLASH_IMR_ERASE_DONE_INT_MSK_SHIFT                                                      4
#define EFLASH_IMR_ERASE_DONE_INT_MSK_MASK                                                       0x00000010
#define EFLASH_IMR_ERASE_DONE_INT_MSK_SET(n)                                                     (((uint32_t)(n) << 4  ) & 0x00000010)
#define EFLASH_IMR_ERASE_DONE_INT_MSK_CLR                                                        0xFFFFFFEF

#define EFLASH_IMR_PROG_DONE_INT_MSK_SHIFT                                                       3
#define EFLASH_IMR_PROG_DONE_INT_MSK_MASK                                                        0x00000008
#define EFLASH_IMR_PROG_DONE_INT_MSK_SET(n)                                                      (((uint32_t)(n) << 3  ) & 0x00000008)
#define EFLASH_IMR_PROG_DONE_INT_MSK_CLR                                                         0xFFFFFFF7

#define EFLASH_IMR_PROG_RD_CHK_ERR_INT_MSK_SHIFT                                                 2
#define EFLASH_IMR_PROG_RD_CHK_ERR_INT_MSK_MASK                                                  0x00000004
#define EFLASH_IMR_PROG_RD_CHK_ERR_INT_MSK_SET(n)                                                (((uint32_t)(n) << 2  ) & 0x00000004)
#define EFLASH_IMR_PROG_RD_CHK_ERR_INT_MSK_CLR                                                   0xFFFFFFFB

#define EFLASH_IMR_NVR_ACCESS_ERR_INT_MSK_SHIFT                                                  1
#define EFLASH_IMR_NVR_ACCESS_ERR_INT_MSK_MASK                                                   0x00000002
#define EFLASH_IMR_NVR_ACCESS_ERR_INT_MSK_SET(n)                                                 (((uint32_t)(n) << 1  ) & 0x00000002)
#define EFLASH_IMR_NVR_ACCESS_ERR_INT_MSK_CLR                                                    0xFFFFFFFD

#define EFLASH_IMR_NVM_PROG_ADDR_CHK_ERR_INT_MSK_SHIFT                                           0
#define EFLASH_IMR_NVM_PROG_ADDR_CHK_ERR_INT_MSK_MASK                                            0x00000001
#define EFLASH_IMR_NVM_PROG_ADDR_CHK_ERR_INT_MSK_SET(n)                                          (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_IMR_NVM_PROG_ADDR_CHK_ERR_INT_MSK_CLR                                             0xFFFFFFFE

#define EFLASH_ISR_ERASE_DONE_INT_STATUS_SHIFT                                                   4
#define EFLASH_ISR_ERASE_DONE_INT_STATUS_MASK                                                    0x00000010
#define EFLASH_ISR_ERASE_DONE_INT_STATUS_SET(n)                                                  (((uint32_t)(n) << 4  ) & 0x00000010)
#define EFLASH_ISR_ERASE_DONE_INT_STATUS_CLR                                                     0xFFFFFFEF

#define EFLASH_ISR_PROG_DONE_INT_STATUS_SHIFT                                                    3
#define EFLASH_ISR_PROG_DONE_INT_STATUS_MASK                                                     0x00000008
#define EFLASH_ISR_PROG_DONE_INT_STATUS_SET(n)                                                   (((uint32_t)(n) << 3  ) & 0x00000008)
#define EFLASH_ISR_PROG_DONE_INT_STATUS_CLR                                                      0xFFFFFFF7

#define EFLASH_ISR_PROG_RD_CHK_ERR_INT_STATUS_SHIFT                                              2
#define EFLASH_ISR_PROG_RD_CHK_ERR_INT_STATUS_MASK                                               0x00000004
#define EFLASH_ISR_PROG_RD_CHK_ERR_INT_STATUS_SET(n)                                             (((uint32_t)(n) << 2  ) & 0x00000004)
#define EFLASH_ISR_PROG_RD_CHK_ERR_INT_STATUS_CLR                                                0xFFFFFFFB

#define EFLASH_ISR_NVR_ACCESS_ERR_INT_STATUS_SHIFT                                               1
#define EFLASH_ISR_NVR_ACCESS_ERR_INT_STATUS_MASK                                                0x00000002
#define EFLASH_ISR_NVR_ACCESS_ERR_INT_STATUS_SET(n)                                              (((uint32_t)(n) << 1  ) & 0x00000002)
#define EFLASH_ISR_NVR_ACCESS_ERR_INT_STATUS_CLR                                                 0xFFFFFFFD

#define EFLASH_ISR_NVM_PROG_ADDR_CHK_ERR_INT_STATUS_SHIFT                                        0
#define EFLASH_ISR_NVM_PROG_ADDR_CHK_ERR_INT_STATUS_MASK                                         0x00000001
#define EFLASH_ISR_NVM_PROG_ADDR_CHK_ERR_INT_STATUS_SET(n)                                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_ISR_NVM_PROG_ADDR_CHK_ERR_INT_STATUS_CLR                                          0xFFFFFFFE

#define EFLASH_IRSR_ERASE_DONE_INT_RAW_STATUS_SHIFT                                              4
#define EFLASH_IRSR_ERASE_DONE_INT_RAW_STATUS_MASK                                               0x00000010
#define EFLASH_IRSR_ERASE_DONE_INT_RAW_STATUS_SET(n)                                             (((uint32_t)(n) << 4  ) & 0x00000010)
#define EFLASH_IRSR_ERASE_DONE_INT_RAW_STATUS_CLR                                                0xFFFFFFEF

#define EFLASH_IRSR_PROG_DONE_INT_RAW_STATUS_SHIFT                                               3
#define EFLASH_IRSR_PROG_DONE_INT_RAW_STATUS_MASK                                                0x00000008
#define EFLASH_IRSR_PROG_DONE_INT_RAW_STATUS_SET(n)                                              (((uint32_t)(n) << 3  ) & 0x00000008)
#define EFLASH_IRSR_PROG_DONE_INT_RAW_STATUS_CLR                                                 0xFFFFFFF7

#define EFLASH_IRSR_PROG_RD_CHK_ERR_INT_RAW_STATUS_SHIFT                                         2
#define EFLASH_IRSR_PROG_RD_CHK_ERR_INT_RAW_STATUS_MASK                                          0x00000004
#define EFLASH_IRSR_PROG_RD_CHK_ERR_INT_RAW_STATUS_SET(n)                                        (((uint32_t)(n) << 2  ) & 0x00000004)
#define EFLASH_IRSR_PROG_RD_CHK_ERR_INT_RAW_STATUS_CLR                                           0xFFFFFFFB

#define EFLASH_IRSR_NVR_ACCESS_ERR_INT_RAW_STATUS_SHIFT                                          1
#define EFLASH_IRSR_NVR_ACCESS_ERR_INT_RAW_STATUS_MASK                                           0x00000002
#define EFLASH_IRSR_NVR_ACCESS_ERR_INT_RAW_STATUS_SET(n)                                         (((uint32_t)(n) << 1  ) & 0x00000002)
#define EFLASH_IRSR_NVR_ACCESS_ERR_INT_RAW_STATUS_CLR                                            0xFFFFFFFD

#define EFLASH_IRSR_NVM_PROG_ADDR_CHK_ERR_INT_RAW_STATUS_SHIFT                                   0
#define EFLASH_IRSR_NVM_PROG_ADDR_CHK_ERR_INT_RAW_STATUS_MASK                                    0x00000001
#define EFLASH_IRSR_NVM_PROG_ADDR_CHK_ERR_INT_RAW_STATUS_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_IRSR_NVM_PROG_ADDR_CHK_ERR_INT_RAW_STATUS_CLR                                     0xFFFFFFFE

#define EFLASH_ERR_ADDR_ERR_ADDR_SHIFT                                                           0
#define EFLASH_ERR_ADDR_ERR_ADDR_MASK                                                            0xFFFFFFFF
#define EFLASH_ERR_ADDR_ERR_ADDR_SET(n)                                                          (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define EFLASH_ERR_ADDR_ERR_ADDR_CLR                                                             0x00000000

#define EFLASH_ERR_WDATA_ERR_WDATA_SHIFT                                                         0
#define EFLASH_ERR_WDATA_ERR_WDATA_MASK                                                          0xFFFFFFFF
#define EFLASH_ERR_WDATA_ERR_WDATA_SET(n)                                                        (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define EFLASH_ERR_WDATA_ERR_WDATA_CLR                                                           0x00000000

#define EFLASH_ERR_RDATA_ERR_RDATA_SHIFT                                                         0
#define EFLASH_ERR_RDATA_ERR_RDATA_MASK                                                          0xFFFFFFFF
#define EFLASH_ERR_RDATA_ERR_RDATA_SET(n)                                                        (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define EFLASH_ERR_RDATA_ERR_RDATA_CLR                                                           0x00000000

#define EFLASH_STATUS_PROG_BUSY_STATUS_SHIFT                                                     1
#define EFLASH_STATUS_PROG_BUSY_STATUS_MASK                                                      0x00000002
#define EFLASH_STATUS_PROG_BUSY_STATUS_SET(n)                                                    (((uint32_t)(n) << 1  ) & 0x00000002)
#define EFLASH_STATUS_PROG_BUSY_STATUS_CLR                                                       0xFFFFFFFD

#define EFLASH_STATUS_ERASE_BUSY_STATUS_SHIFT                                                    0
#define EFLASH_STATUS_ERASE_BUSY_STATUS_MASK                                                     0x00000001
#define EFLASH_STATUS_ERASE_BUSY_STATUS_SET(n)                                                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_STATUS_ERASE_BUSY_STATUS_CLR                                                      0xFFFFFFFE

#define EFLASH_WR_LOCK_WR_LOCK_SHIFT                                                             0
#define EFLASH_WR_LOCK_WR_LOCK_MASK                                                              0x00000001
#define EFLASH_WR_LOCK_WR_LOCK_SET(n)                                                            (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_WR_LOCK_WR_LOCK_CLR                                                               0xFFFFFFFE

#define EFLASH_NVR_PROT_NVR_PROT_SHIFT                                                           0
#define EFLASH_NVR_PROT_NVR_PROT_MASK                                                            0x00000001
#define EFLASH_NVR_PROT_NVR_PROT_SET(n)                                                          (((uint32_t)(n) << 0  ) & 0x00000001)
#define EFLASH_NVR_PROT_NVR_PROT_CLR                                                             0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t REVISION_ID                          : 8  ; // 7  : 0
    __IO uint32_t RESERVED0                            : 24 ; // 31 : 8
} EFLASH_REVISION_ID_FIELD_T;

typedef struct
{
    __IO uint32_t RC_CYC                               : 4  ; // 3  : 0
    __IO uint32_t RESERVED0                            : 28 ; // 31 : 4
} EFLASH_RD_TIME_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t NVS_CYC                              : 6  ; // 5  : 0
    __IO uint32_t PROG_RCV_CYC                         : 6  ; // 11 : 6
    __IO uint32_t ESECT_RCV_CYC                        : 10 ; // 21 : 12
    __IO uint32_t ECHIP_RCV_CYC                        : 10 ; // 31 : 22
} EFLASH_PROG_ERASE_TIME_CFG0_FIELD_T;

typedef struct
{
    __IO uint32_t PGS_CYC                              : 5  ; // 4  : 0
    __IO uint32_t PGH_CYC                              : 2  ; // 6  : 5
    __IO uint32_t ADS_CYC                              : 2  ; // 8  : 7
    __IO uint32_t ADH_CYC                              : 2  ; // 10 : 9
    __IO uint32_t PROG_CYC                             : 5  ; // 15 : 11
    __IO uint32_t ERASE_SECT_CYC                       : 5  ; // 20 : 16
    __IO uint32_t ERASE_CHIP_CYC                       : 8  ; // 28 : 21
    __IO uint32_t LATENCY_CYC                          : 3  ; // 31 : 29
} EFLASH_PROG_ERASE_TIME_CFG1_FIELD_T;

typedef struct
{
    __IO uint32_t SECTOR_INDEX                         : 7  ; // 6  : 0
    __IO uint32_t RESERVED1                            : 17 ; // 23 : 7
    __IO uint32_t NVR_SECTOR_SEL                       : 1  ; // 24 : 24
    __IO uint32_t RESERVED0                            : 7  ; // 31 : 25
} EFLASH_ERASE_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t SECTOR_ERASE_TRIG                    : 1  ; // 0  : 0
    __IO uint32_t RESERVED1                            : 15 ; // 15 : 1
    __IO uint32_t CHIP_ERASE_TRIG                      : 1  ; // 16 : 16
    __IO uint32_t RESERVED0                            : 15 ; // 31 : 17
} EFLASH_ERASE_TRIG_FIELD_T;

typedef struct
{
    __IO uint32_t DEEP_STANDBY                         : 1  ; // 0  : 0
    __IO uint32_t RESERVED1                            : 3  ; // 3  : 1
    __IO uint32_t CLK1M_DIVISOR                        : 4  ; // 7  : 4
    __IO uint32_t CLK1K_DIVISOR                        : 5  ; // 12 : 8
    __IO uint32_t RESERVED0                            : 19 ; // 31 : 13
} EFLASH_MISC_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t FAST_RD_EN                           : 1  ; // 0  : 0
    __IO uint32_t PROG_ADDR_CHK_EN                     : 1  ; // 1  : 1
    __IO uint32_t PROG_RD_CHK_EN                       : 1  ; // 2  : 2
    __IO uint32_t RESERVED1                            : 1  ; // 3  : 3
    __IO uint32_t RDONLY_EN                            : 1  ; // 4  : 4
    __IO uint32_t RESERVED0                            : 27 ; // 31 : 5
} EFLASH_OP_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t PROG_ADDR_PROT_START0                : 14 ; // 13 : 0
    __IO uint32_t RESERVED1                            : 2  ; // 15 : 14
    __IO uint32_t PROG_ADDR_PROT_END0                  : 14 ; // 29 : 16
    __IO uint32_t RESERVED0                            : 2  ; // 31 : 30
} EFLASH_PROG_ADDR_PROT0_FIELD_T;

typedef struct
{
    __IO uint32_t PROG_ADDR_PROT_START1                : 14 ; // 13 : 0
    __IO uint32_t RESERVED1                            : 2  ; // 15 : 14
    __IO uint32_t PROG_ADDR_PROT_END1                  : 14 ; // 29 : 16
    __IO uint32_t RESERVED0                            : 2  ; // 31 : 30
} EFLASH_PROG_ADDR_PROT1_FIELD_T;

typedef struct
{
    __IO uint32_t NVM_PROG_ADDR_CHK_ERR_INT_CLR        : 1  ; // 0  : 0
    __IO uint32_t NVR_ACCESS_ERR_INT_CLR               : 1  ; // 1  : 1
    __IO uint32_t PROG_RD_CHK_ERR_INT_CLR              : 1  ; // 2  : 2
    __IO uint32_t PROG_DONE_INT_CLR                    : 1  ; // 3  : 3
    __IO uint32_t ERASE_DONE_INT_CLR                   : 1  ; // 4  : 4
    __IO uint32_t RESERVED0                            : 27 ; // 31 : 5
} EFLASH_ICR_FIELD_T;

typedef struct
{
    __IO uint32_t NVM_PROG_ADDR_CHK_ERR_INT_MSK        : 1  ; // 0  : 0
    __IO uint32_t NVR_ACCESS_ERR_INT_MSK               : 1  ; // 1  : 1
    __IO uint32_t PROG_RD_CHK_ERR_INT_MSK              : 1  ; // 2  : 2
    __IO uint32_t PROG_DONE_INT_MSK                    : 1  ; // 3  : 3
    __IO uint32_t ERASE_DONE_INT_MSK                   : 1  ; // 4  : 4
    __IO uint32_t RESERVED0                            : 27 ; // 31 : 5
} EFLASH_IMR_FIELD_T;

typedef struct
{
    __IO uint32_t NVM_PROG_ADDR_CHK_ERR_INT_STATUS     : 1  ; // 0  : 0
    __IO uint32_t NVR_ACCESS_ERR_INT_STATUS            : 1  ; // 1  : 1
    __IO uint32_t PROG_RD_CHK_ERR_INT_STATUS           : 1  ; // 2  : 2
    __IO uint32_t PROG_DONE_INT_STATUS                 : 1  ; // 3  : 3
    __IO uint32_t ERASE_DONE_INT_STATUS                : 1  ; // 4  : 4
    __IO uint32_t RESERVED0                            : 27 ; // 31 : 5
} EFLASH_ISR_FIELD_T;

typedef struct
{
    __IO uint32_t NVM_PROG_ADDR_CHK_ERR_INT_RAW_STATUS : 1  ; // 0  : 0
    __IO uint32_t NVR_ACCESS_ERR_INT_RAW_STATUS        : 1  ; // 1  : 1
    __IO uint32_t PROG_RD_CHK_ERR_INT_RAW_STATUS       : 1  ; // 2  : 2
    __IO uint32_t PROG_DONE_INT_RAW_STATUS             : 1  ; // 3  : 3
    __IO uint32_t ERASE_DONE_INT_RAW_STATUS            : 1  ; // 4  : 4
    __IO uint32_t RESERVED0                            : 27 ; // 31 : 5
} EFLASH_IRSR_FIELD_T;

typedef struct
{
    __IO uint32_t ERR_ADDR                             : 32 ; // 31 : 0
} EFLASH_ERR_ADDR_FIELD_T;

typedef struct
{
    __IO uint32_t ERR_WDATA                            : 32 ; // 31 : 0
} EFLASH_ERR_WDATA_FIELD_T;

typedef struct
{
    __IO uint32_t ERR_RDATA                            : 32 ; // 31 : 0
} EFLASH_ERR_RDATA_FIELD_T;

typedef struct
{
    __IO uint32_t ERASE_BUSY_STATUS                    : 1  ; // 0  : 0
    __IO uint32_t PROG_BUSY_STATUS                     : 1  ; // 1  : 1
    __IO uint32_t RESERVED0                            : 30 ; // 31 : 2
} EFLASH_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t WR_LOCK                              : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                            : 31 ; // 31 : 1
} EFLASH_WR_LOCK_FIELD_T;

typedef struct
{
    __IO uint32_t NVR_PROT                             : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                            : 31 ; // 31 : 1
} EFLASH_NVR_PROT_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t REVISION_ID                                 ; // 0x0000
        EFLASH_REVISION_ID_FIELD_T REVISION_ID_F                   ;
    };

    union
    {
        __IO  uint32_t RD_TIME_CFG                                 ; // 0x0004
        EFLASH_RD_TIME_CFG_FIELD_T RD_TIME_CFG_F                   ;
    };

    union
    {
        __IO  uint32_t PROG_ERASE_TIME_CFG0                        ; // 0x0008
        EFLASH_PROG_ERASE_TIME_CFG0_FIELD_T PROG_ERASE_TIME_CFG0_F ;
    };

    union
    {
        __IO  uint32_t PROG_ERASE_TIME_CFG1                        ; // 0x000C
        EFLASH_PROG_ERASE_TIME_CFG1_FIELD_T PROG_ERASE_TIME_CFG1_F ;
    };

    union
    {
        __IO  uint32_t ERASE_CFG                                   ; // 0x0010
        EFLASH_ERASE_CFG_FIELD_T ERASE_CFG_F                       ;
    };

    union
    {
        __IO  uint32_t ERASE_TRIG                                  ; // 0x0014
        EFLASH_ERASE_TRIG_FIELD_T ERASE_TRIG_F                     ;
    };

    union
    {
        __IO  uint32_t MISC_CTRL                                   ; // 0x0018
        EFLASH_MISC_CTRL_FIELD_T MISC_CTRL_F                       ;
    };

    union
    {
        __IO  uint32_t OP_CTRL                                     ; // 0x001C
        EFLASH_OP_CTRL_FIELD_T OP_CTRL_F                           ;
    };

    union
    {
        __IO  uint32_t PROG_ADDR_PROT0                             ; // 0x0020
        EFLASH_PROG_ADDR_PROT0_FIELD_T PROG_ADDR_PROT0_F           ;
    };

    union
    {
        __IO  uint32_t PROG_ADDR_PROT1                             ; // 0x0024
        EFLASH_PROG_ADDR_PROT1_FIELD_T PROG_ADDR_PROT1_F           ;
    };

    union
    {
        __IO  uint32_t ICR                                         ; // 0x0028
        EFLASH_ICR_FIELD_T ICR_F                                   ;
    };

    union
    {
        __IO  uint32_t IMR                                         ; // 0x002C
        EFLASH_IMR_FIELD_T IMR_F                                   ;
    };

    union
    {
        __IO  uint32_t ISR                                         ; // 0x0030
        EFLASH_ISR_FIELD_T ISR_F                                   ;
    };

    union
    {
        __IO  uint32_t IRSR                                        ; // 0x0034
        EFLASH_IRSR_FIELD_T IRSR_F                                 ;
    };

    union
    {
        __IO  uint32_t ERR_ADDR                                    ; // 0x0038
        EFLASH_ERR_ADDR_FIELD_T ERR_ADDR_F                         ;
    };

    union
    {
        __IO  uint32_t ERR_WDATA                                   ; // 0x003C
        EFLASH_ERR_WDATA_FIELD_T ERR_WDATA_F                       ;
    };

    union
    {
        __IO  uint32_t ERR_RDATA                                   ; // 0x0040
        EFLASH_ERR_RDATA_FIELD_T ERR_RDATA_F                       ;
    };

    union
    {
        __IO  uint32_t STATUS                                      ; // 0x0044
        EFLASH_STATUS_FIELD_T STATUS_F                             ;
    };

    uint32_t RESERVED0[44]                                          ;

    union
    {
        __IO  uint32_t WR_LOCK                                     ; // 0x00F8
        EFLASH_WR_LOCK_FIELD_T WR_LOCK_F                           ;
    };

    union
    {
        __IO  uint32_t NVR_PROT                                    ; // 0x00FC
        EFLASH_NVR_PROT_FIELD_T NVR_PROT_F                         ;
    };

} EFLASH_REG_TypeDef;

#endif
