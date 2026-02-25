/**
 *****************************************************************************
 * @brief   pinmux_reg_def header file.
 *
 * @file    pinmux_reg_def.h
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

#ifndef   PINMUX_DEF_H__
#define   PINMUX_DEF_H__

// Register Offset Macro Definition
#define PINMUX_INT_IO0_CFG_OFFSET                               0x0000
#define PINMUX_INT_IO1_CFG_OFFSET                               0x0004
#define PINMUX_INT_IO2_CFG_OFFSET                               0x0008
#define PINMUX_INT_IO3_CFG_OFFSET                               0x000C
#define PINMUX_LED_DIS_CFG_OFFSET                               0x0010
#define PINMUX_PIN_LP_CTRL_OFFSET                               0x0014

// Register Address Macro Definition
#define PINMUX_INT_IO0_CFG_ADDR                                 ( PINMUX_BASE_ADDR + PINMUX_INT_IO0_CFG_OFFSET)
#define PINMUX_INT_IO1_CFG_ADDR                                 ( PINMUX_BASE_ADDR + PINMUX_INT_IO1_CFG_OFFSET)
#define PINMUX_INT_IO2_CFG_ADDR                                 ( PINMUX_BASE_ADDR + PINMUX_INT_IO2_CFG_OFFSET)
#define PINMUX_INT_IO3_CFG_ADDR                                 ( PINMUX_BASE_ADDR + PINMUX_INT_IO3_CFG_OFFSET)
#define PINMUX_LED_DIS_CFG_ADDR                                 ( PINMUX_BASE_ADDR + PINMUX_LED_DIS_CFG_OFFSET)
#define PINMUX_PIN_LP_CTRL_ADDR                                 ( PINMUX_BASE_ADDR + PINMUX_PIN_LP_CTRL_OFFSET)

// Register Field Macro Definition
#define PINMUX_INT_IO0_CFG_INT_IO0_SR_SHIFT                         12
#define PINMUX_INT_IO0_CFG_INT_IO0_SR_MASK                          0x00001000
#define PINMUX_INT_IO0_CFG_INT_IO0_SR_SET(n)                        (((uint32_t)(n) << 12 ) & 0x00001000)
#define PINMUX_INT_IO0_CFG_INT_IO0_SR_CLR                           0xFFFFEFFF

#define PINMUX_INT_IO0_CFG_INT_IO0_OS_SHIFT                         11
#define PINMUX_INT_IO0_CFG_INT_IO0_OS_MASK                          0x00000800
#define PINMUX_INT_IO0_CFG_INT_IO0_OS_SET(n)                        (((uint32_t)(n) << 11 ) & 0x00000800)
#define PINMUX_INT_IO0_CFG_INT_IO0_OS_CLR                           0xFFFFF7FF

#define PINMUX_INT_IO0_CFG_INT_IO0_OD_SHIFT                         10
#define PINMUX_INT_IO0_CFG_INT_IO0_OD_MASK                          0x00000400
#define PINMUX_INT_IO0_CFG_INT_IO0_OD_SET(n)                        (((uint32_t)(n) << 10 ) & 0x00000400)
#define PINMUX_INT_IO0_CFG_INT_IO0_OD_CLR                           0xFFFFFBFF

#define PINMUX_INT_IO0_CFG_INT_IO0_DR_SHIFT                         9
#define PINMUX_INT_IO0_CFG_INT_IO0_DR_MASK                          0x00000200
#define PINMUX_INT_IO0_CFG_INT_IO0_DR_SET(n)                        (((uint32_t)(n) << 9  ) & 0x00000200)
#define PINMUX_INT_IO0_CFG_INT_IO0_DR_CLR                           0xFFFFFDFF

#define PINMUX_INT_IO0_CFG_INT_IO0_CS_SHIFT                         8
#define PINMUX_INT_IO0_CFG_INT_IO0_CS_MASK                          0x00000100
#define PINMUX_INT_IO0_CFG_INT_IO0_CS_SET(n)                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define PINMUX_INT_IO0_CFG_INT_IO0_CS_CLR                           0xFFFFFEFF

#define PINMUX_INT_IO0_CFG_INT_IO0_PD_SHIFT                         6
#define PINMUX_INT_IO0_CFG_INT_IO0_PD_MASK                          0x00000040
#define PINMUX_INT_IO0_CFG_INT_IO0_PD_SET(n)                        (((uint32_t)(n) << 6  ) & 0x00000040)
#define PINMUX_INT_IO0_CFG_INT_IO0_PD_CLR                           0xFFFFFFBF

#define PINMUX_INT_IO0_CFG_INT_IO0_PU_SHIFT                         5
#define PINMUX_INT_IO0_CFG_INT_IO0_PU_MASK                          0x00000020
#define PINMUX_INT_IO0_CFG_INT_IO0_PU_SET(n)                        (((uint32_t)(n) << 5  ) & 0x00000020)
#define PINMUX_INT_IO0_CFG_INT_IO0_PU_CLR                           0xFFFFFFDF

#define PINMUX_INT_IO0_CFG_INT_IO0_PULL_SEL_SHIFT                   4
#define PINMUX_INT_IO0_CFG_INT_IO0_PULL_SEL_MASK                    0x00000010
#define PINMUX_INT_IO0_CFG_INT_IO0_PULL_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000010)
#define PINMUX_INT_IO0_CFG_INT_IO0_PULL_SEL_CLR                     0xFFFFFFEF

#define PINMUX_INT_IO0_CFG_INT_IO0_IE_SHIFT                         3
#define PINMUX_INT_IO0_CFG_INT_IO0_IE_MASK                          0x00000008
#define PINMUX_INT_IO0_CFG_INT_IO0_IE_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define PINMUX_INT_IO0_CFG_INT_IO0_IE_CLR                           0xFFFFFFF7

#define PINMUX_INT_IO0_CFG_INT_IO0_SRC_SEL_SHIFT                    0
#define PINMUX_INT_IO0_CFG_INT_IO0_SRC_SEL_MASK                     0x00000001
#define PINMUX_INT_IO0_CFG_INT_IO0_SRC_SEL_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define PINMUX_INT_IO0_CFG_INT_IO0_SRC_SEL_CLR                      0xFFFFFFFE

#define PINMUX_INT_IO1_CFG_INT_IO1_SR_SHIFT                         12
#define PINMUX_INT_IO1_CFG_INT_IO1_SR_MASK                          0x00001000
#define PINMUX_INT_IO1_CFG_INT_IO1_SR_SET(n)                        (((uint32_t)(n) << 12 ) & 0x00001000)
#define PINMUX_INT_IO1_CFG_INT_IO1_SR_CLR                           0xFFFFEFFF

#define PINMUX_INT_IO1_CFG_INT_IO1_OS_SHIFT                         11
#define PINMUX_INT_IO1_CFG_INT_IO1_OS_MASK                          0x00000800
#define PINMUX_INT_IO1_CFG_INT_IO1_OS_SET(n)                        (((uint32_t)(n) << 11 ) & 0x00000800)
#define PINMUX_INT_IO1_CFG_INT_IO1_OS_CLR                           0xFFFFF7FF

#define PINMUX_INT_IO1_CFG_INT_IO1_OD_SHIFT                         10
#define PINMUX_INT_IO1_CFG_INT_IO1_OD_MASK                          0x00000400
#define PINMUX_INT_IO1_CFG_INT_IO1_OD_SET(n)                        (((uint32_t)(n) << 10 ) & 0x00000400)
#define PINMUX_INT_IO1_CFG_INT_IO1_OD_CLR                           0xFFFFFBFF

#define PINMUX_INT_IO1_CFG_INT_IO1_DR_SHIFT                         9
#define PINMUX_INT_IO1_CFG_INT_IO1_DR_MASK                          0x00000200
#define PINMUX_INT_IO1_CFG_INT_IO1_DR_SET(n)                        (((uint32_t)(n) << 9  ) & 0x00000200)
#define PINMUX_INT_IO1_CFG_INT_IO1_DR_CLR                           0xFFFFFDFF

#define PINMUX_INT_IO1_CFG_INT_IO1_CS_SHIFT                         8
#define PINMUX_INT_IO1_CFG_INT_IO1_CS_MASK                          0x00000100
#define PINMUX_INT_IO1_CFG_INT_IO1_CS_SET(n)                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define PINMUX_INT_IO1_CFG_INT_IO1_CS_CLR                           0xFFFFFEFF

#define PINMUX_INT_IO1_CFG_INT_IO1_PD_SHIFT                         6
#define PINMUX_INT_IO1_CFG_INT_IO1_PD_MASK                          0x00000040
#define PINMUX_INT_IO1_CFG_INT_IO1_PD_SET(n)                        (((uint32_t)(n) << 6  ) & 0x00000040)
#define PINMUX_INT_IO1_CFG_INT_IO1_PD_CLR                           0xFFFFFFBF

#define PINMUX_INT_IO1_CFG_INT_IO1_PU_SHIFT                         5
#define PINMUX_INT_IO1_CFG_INT_IO1_PU_MASK                          0x00000020
#define PINMUX_INT_IO1_CFG_INT_IO1_PU_SET(n)                        (((uint32_t)(n) << 5  ) & 0x00000020)
#define PINMUX_INT_IO1_CFG_INT_IO1_PU_CLR                           0xFFFFFFDF

#define PINMUX_INT_IO1_CFG_INT_IO1_PULL_SEL_SHIFT                   4
#define PINMUX_INT_IO1_CFG_INT_IO1_PULL_SEL_MASK                    0x00000010
#define PINMUX_INT_IO1_CFG_INT_IO1_PULL_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000010)
#define PINMUX_INT_IO1_CFG_INT_IO1_PULL_SEL_CLR                     0xFFFFFFEF

#define PINMUX_INT_IO1_CFG_INT_IO1_IE_SHIFT                         3
#define PINMUX_INT_IO1_CFG_INT_IO1_IE_MASK                          0x00000008
#define PINMUX_INT_IO1_CFG_INT_IO1_IE_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define PINMUX_INT_IO1_CFG_INT_IO1_IE_CLR                           0xFFFFFFF7

#define PINMUX_INT_IO1_CFG_INT_IO1_SRC_SEL_SHIFT                    0
#define PINMUX_INT_IO1_CFG_INT_IO1_SRC_SEL_MASK                     0x00000001
#define PINMUX_INT_IO1_CFG_INT_IO1_SRC_SEL_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define PINMUX_INT_IO1_CFG_INT_IO1_SRC_SEL_CLR                      0xFFFFFFFE

#define PINMUX_INT_IO2_CFG_INT_IO2_SR_SHIFT                         12
#define PINMUX_INT_IO2_CFG_INT_IO2_SR_MASK                          0x00001000
#define PINMUX_INT_IO2_CFG_INT_IO2_SR_SET(n)                        (((uint32_t)(n) << 12 ) & 0x00001000)
#define PINMUX_INT_IO2_CFG_INT_IO2_SR_CLR                           0xFFFFEFFF

#define PINMUX_INT_IO2_CFG_INT_IO2_OS_SHIFT                         11
#define PINMUX_INT_IO2_CFG_INT_IO2_OS_MASK                          0x00000800
#define PINMUX_INT_IO2_CFG_INT_IO2_OS_SET(n)                        (((uint32_t)(n) << 11 ) & 0x00000800)
#define PINMUX_INT_IO2_CFG_INT_IO2_OS_CLR                           0xFFFFF7FF

#define PINMUX_INT_IO2_CFG_INT_IO2_OD_SHIFT                         10
#define PINMUX_INT_IO2_CFG_INT_IO2_OD_MASK                          0x00000400
#define PINMUX_INT_IO2_CFG_INT_IO2_OD_SET(n)                        (((uint32_t)(n) << 10 ) & 0x00000400)
#define PINMUX_INT_IO2_CFG_INT_IO2_OD_CLR                           0xFFFFFBFF

#define PINMUX_INT_IO2_CFG_INT_IO2_DR_SHIFT                         9
#define PINMUX_INT_IO2_CFG_INT_IO2_DR_MASK                          0x00000200
#define PINMUX_INT_IO2_CFG_INT_IO2_DR_SET(n)                        (((uint32_t)(n) << 9  ) & 0x00000200)
#define PINMUX_INT_IO2_CFG_INT_IO2_DR_CLR                           0xFFFFFDFF

#define PINMUX_INT_IO2_CFG_INT_IO2_CS_SHIFT                         8
#define PINMUX_INT_IO2_CFG_INT_IO2_CS_MASK                          0x00000100
#define PINMUX_INT_IO2_CFG_INT_IO2_CS_SET(n)                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define PINMUX_INT_IO2_CFG_INT_IO2_CS_CLR                           0xFFFFFEFF

#define PINMUX_INT_IO2_CFG_INT_IO2_PD_SHIFT                         6
#define PINMUX_INT_IO2_CFG_INT_IO2_PD_MASK                          0x00000040
#define PINMUX_INT_IO2_CFG_INT_IO2_PD_SET(n)                        (((uint32_t)(n) << 6  ) & 0x00000040)
#define PINMUX_INT_IO2_CFG_INT_IO2_PD_CLR                           0xFFFFFFBF

#define PINMUX_INT_IO2_CFG_INT_IO2_PU_SHIFT                         5
#define PINMUX_INT_IO2_CFG_INT_IO2_PU_MASK                          0x00000020
#define PINMUX_INT_IO2_CFG_INT_IO2_PU_SET(n)                        (((uint32_t)(n) << 5  ) & 0x00000020)
#define PINMUX_INT_IO2_CFG_INT_IO2_PU_CLR                           0xFFFFFFDF

#define PINMUX_INT_IO2_CFG_INT_IO2_PULL_SEL_SHIFT                   4
#define PINMUX_INT_IO2_CFG_INT_IO2_PULL_SEL_MASK                    0x00000010
#define PINMUX_INT_IO2_CFG_INT_IO2_PULL_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000010)
#define PINMUX_INT_IO2_CFG_INT_IO2_PULL_SEL_CLR                     0xFFFFFFEF

#define PINMUX_INT_IO2_CFG_INT_IO2_IE_SHIFT                         3
#define PINMUX_INT_IO2_CFG_INT_IO2_IE_MASK                          0x00000008
#define PINMUX_INT_IO2_CFG_INT_IO2_IE_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define PINMUX_INT_IO2_CFG_INT_IO2_IE_CLR                           0xFFFFFFF7

#define PINMUX_INT_IO2_CFG_INT_IO2_SRC_SEL_SHIFT                    0
#define PINMUX_INT_IO2_CFG_INT_IO2_SRC_SEL_MASK                     0x00000001
#define PINMUX_INT_IO2_CFG_INT_IO2_SRC_SEL_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define PINMUX_INT_IO2_CFG_INT_IO2_SRC_SEL_CLR                      0xFFFFFFFE

#define PINMUX_INT_IO3_CFG_INT_IO3_SR_SHIFT                         12
#define PINMUX_INT_IO3_CFG_INT_IO3_SR_MASK                          0x00001000
#define PINMUX_INT_IO3_CFG_INT_IO3_SR_SET(n)                        (((uint32_t)(n) << 12 ) & 0x00001000)
#define PINMUX_INT_IO3_CFG_INT_IO3_SR_CLR                           0xFFFFEFFF

#define PINMUX_INT_IO3_CFG_INT_IO3_OS_SHIFT                         11
#define PINMUX_INT_IO3_CFG_INT_IO3_OS_MASK                          0x00000800
#define PINMUX_INT_IO3_CFG_INT_IO3_OS_SET(n)                        (((uint32_t)(n) << 11 ) & 0x00000800)
#define PINMUX_INT_IO3_CFG_INT_IO3_OS_CLR                           0xFFFFF7FF

#define PINMUX_INT_IO3_CFG_INT_IO3_OD_SHIFT                         10
#define PINMUX_INT_IO3_CFG_INT_IO3_OD_MASK                          0x00000400
#define PINMUX_INT_IO3_CFG_INT_IO3_OD_SET(n)                        (((uint32_t)(n) << 10 ) & 0x00000400)
#define PINMUX_INT_IO3_CFG_INT_IO3_OD_CLR                           0xFFFFFBFF

#define PINMUX_INT_IO3_CFG_INT_IO3_DR_SHIFT                         9
#define PINMUX_INT_IO3_CFG_INT_IO3_DR_MASK                          0x00000200
#define PINMUX_INT_IO3_CFG_INT_IO3_DR_SET(n)                        (((uint32_t)(n) << 9  ) & 0x00000200)
#define PINMUX_INT_IO3_CFG_INT_IO3_DR_CLR                           0xFFFFFDFF

#define PINMUX_INT_IO3_CFG_INT_IO3_CS_SHIFT                         8
#define PINMUX_INT_IO3_CFG_INT_IO3_CS_MASK                          0x00000100
#define PINMUX_INT_IO3_CFG_INT_IO3_CS_SET(n)                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define PINMUX_INT_IO3_CFG_INT_IO3_CS_CLR                           0xFFFFFEFF

#define PINMUX_INT_IO3_CFG_INT_IO3_PD_SHIFT                         6
#define PINMUX_INT_IO3_CFG_INT_IO3_PD_MASK                          0x00000040
#define PINMUX_INT_IO3_CFG_INT_IO3_PD_SET(n)                        (((uint32_t)(n) << 6  ) & 0x00000040)
#define PINMUX_INT_IO3_CFG_INT_IO3_PD_CLR                           0xFFFFFFBF

#define PINMUX_INT_IO3_CFG_INT_IO3_PU_SHIFT                         5
#define PINMUX_INT_IO3_CFG_INT_IO3_PU_MASK                          0x00000020
#define PINMUX_INT_IO3_CFG_INT_IO3_PU_SET(n)                        (((uint32_t)(n) << 5  ) & 0x00000020)
#define PINMUX_INT_IO3_CFG_INT_IO3_PU_CLR                           0xFFFFFFDF

#define PINMUX_INT_IO3_CFG_INT_IO3_PULL_SEL_SHIFT                   4
#define PINMUX_INT_IO3_CFG_INT_IO3_PULL_SEL_MASK                    0x00000010
#define PINMUX_INT_IO3_CFG_INT_IO3_PULL_SEL_SET(n)                  (((uint32_t)(n) << 4  ) & 0x00000010)
#define PINMUX_INT_IO3_CFG_INT_IO3_PULL_SEL_CLR                     0xFFFFFFEF

#define PINMUX_INT_IO3_CFG_INT_IO3_IE_SHIFT                         3
#define PINMUX_INT_IO3_CFG_INT_IO3_IE_MASK                          0x00000008
#define PINMUX_INT_IO3_CFG_INT_IO3_IE_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define PINMUX_INT_IO3_CFG_INT_IO3_IE_CLR                           0xFFFFFFF7

#define PINMUX_INT_IO3_CFG_INT_IO3_SRC_SEL_SHIFT                    0
#define PINMUX_INT_IO3_CFG_INT_IO3_SRC_SEL_MASK                     0x00000001
#define PINMUX_INT_IO3_CFG_INT_IO3_SRC_SEL_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define PINMUX_INT_IO3_CFG_INT_IO3_SRC_SEL_CLR                      0xFFFFFFFE

#define PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_SHIFT                    0
#define PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_MASK                     0x00000003
#define PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_SET(n)                   (((uint32_t)(n) << 0  ) & 0x00000003)
#define PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_CLR                      0xFFFFFFFC

#define PINMUX_PIN_LP_CTRL_SWD_CLK_PD_DIS_SHIFT                     6
#define PINMUX_PIN_LP_CTRL_SWD_CLK_PD_DIS_MASK                      0x00000040
#define PINMUX_PIN_LP_CTRL_SWD_CLK_PD_DIS_SET(n)                    (((uint32_t)(n) << 6  ) & 0x00000040)
#define PINMUX_PIN_LP_CTRL_SWD_CLK_PD_DIS_CLR                       0xFFFFFFBF

#define PINMUX_PIN_LP_CTRL_SWD_CLK_IE_DIS_SHIFT                     5
#define PINMUX_PIN_LP_CTRL_SWD_CLK_IE_DIS_MASK                      0x00000020
#define PINMUX_PIN_LP_CTRL_SWD_CLK_IE_DIS_SET(n)                    (((uint32_t)(n) << 5  ) & 0x00000020)
#define PINMUX_PIN_LP_CTRL_SWD_CLK_IE_DIS_CLR                       0xFFFFFFDF

#define PINMUX_PIN_LP_CTRL_SWD_DI_PU_DIS_SHIFT                      4
#define PINMUX_PIN_LP_CTRL_SWD_DI_PU_DIS_MASK                       0x00000010
#define PINMUX_PIN_LP_CTRL_SWD_DI_PU_DIS_SET(n)                     (((uint32_t)(n) << 4  ) & 0x00000010)
#define PINMUX_PIN_LP_CTRL_SWD_DI_PU_DIS_CLR                        0xFFFFFFEF

#define PINMUX_PIN_LP_CTRL_SWD_DI_IE_DIS_SHIFT                      3
#define PINMUX_PIN_LP_CTRL_SWD_DI_IE_DIS_MASK                       0x00000008
#define PINMUX_PIN_LP_CTRL_SWD_DI_IE_DIS_SET(n)                     (((uint32_t)(n) << 3  ) & 0x00000008)
#define PINMUX_PIN_LP_CTRL_SWD_DI_IE_DIS_CLR                        0xFFFFFFF7

#define PINMUX_PIN_LP_CTRL_VS_PORB_PU_DIS_SHIFT                     2
#define PINMUX_PIN_LP_CTRL_VS_PORB_PU_DIS_MASK                      0x00000004
#define PINMUX_PIN_LP_CTRL_VS_PORB_PU_DIS_SET(n)                    (((uint32_t)(n) << 2  ) & 0x00000004)
#define PINMUX_PIN_LP_CTRL_VS_PORB_PU_DIS_CLR                       0xFFFFFFFB

#define PINMUX_PIN_LP_CTRL_AFE_INT_PD_DIS_SHIFT                     1
#define PINMUX_PIN_LP_CTRL_AFE_INT_PD_DIS_MASK                      0x00000002
#define PINMUX_PIN_LP_CTRL_AFE_INT_PD_DIS_SET(n)                    (((uint32_t)(n) << 1  ) & 0x00000002)
#define PINMUX_PIN_LP_CTRL_AFE_INT_PD_DIS_CLR                       0xFFFFFFFD

#define PINMUX_PIN_LP_CTRL_AFE_INT_IE_DIS_SHIFT                     0
#define PINMUX_PIN_LP_CTRL_AFE_INT_IE_DIS_MASK                      0x00000001
#define PINMUX_PIN_LP_CTRL_AFE_INT_IE_DIS_SET(n)                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define PINMUX_PIN_LP_CTRL_AFE_INT_IE_DIS_CLR                       0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t INT_IO0_SRC_SEL  : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 2  ; // 2  : 1
    __IO uint32_t INT_IO0_IE       : 1  ; // 3  : 3
    __IO uint32_t INT_IO0_PULL_SEL : 1  ; // 4  : 4
    __IO uint32_t INT_IO0_PU       : 1  ; // 5  : 5
    __IO uint32_t INT_IO0_PD       : 1  ; // 6  : 6
    __IO uint32_t RESERVED1        : 1  ; // 7  : 7
    __IO uint32_t INT_IO0_CS       : 1  ; // 8  : 8
    __IO uint32_t INT_IO0_DR       : 1  ; // 9  : 9
    __IO uint32_t INT_IO0_OD       : 1  ; // 10 : 10
    __IO uint32_t INT_IO0_OS       : 1  ; // 11 : 11
    __IO uint32_t INT_IO0_SR       : 1  ; // 12 : 12
    __IO uint32_t RESERVED0        : 19 ; // 31 : 13
} PINMUX_INT_IO0_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INT_IO1_SRC_SEL  : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 2  ; // 2  : 1
    __IO uint32_t INT_IO1_IE       : 1  ; // 3  : 3
    __IO uint32_t INT_IO1_PULL_SEL : 1  ; // 4  : 4
    __IO uint32_t INT_IO1_PU       : 1  ; // 5  : 5
    __IO uint32_t INT_IO1_PD       : 1  ; // 6  : 6
    __IO uint32_t RESERVED1        : 1  ; // 7  : 7
    __IO uint32_t INT_IO1_CS       : 1  ; // 8  : 8
    __IO uint32_t INT_IO1_DR       : 1  ; // 9  : 9
    __IO uint32_t INT_IO1_OD       : 1  ; // 10 : 10
    __IO uint32_t INT_IO1_OS       : 1  ; // 11 : 11
    __IO uint32_t INT_IO1_SR       : 1  ; // 12 : 12
    __IO uint32_t RESERVED0        : 19 ; // 31 : 13
} PINMUX_INT_IO1_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INT_IO2_SRC_SEL  : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 2  ; // 2  : 1
    __IO uint32_t INT_IO2_IE       : 1  ; // 3  : 3
    __IO uint32_t INT_IO2_PULL_SEL : 1  ; // 4  : 4
    __IO uint32_t INT_IO2_PU       : 1  ; // 5  : 5
    __IO uint32_t INT_IO2_PD       : 1  ; // 6  : 6
    __IO uint32_t RESERVED1        : 1  ; // 7  : 7
    __IO uint32_t INT_IO2_CS       : 1  ; // 8  : 8
    __IO uint32_t INT_IO2_DR       : 1  ; // 9  : 9
    __IO uint32_t INT_IO2_OD       : 1  ; // 10 : 10
    __IO uint32_t INT_IO2_OS       : 1  ; // 11 : 11
    __IO uint32_t INT_IO2_SR       : 1  ; // 12 : 12
    __IO uint32_t RESERVED0        : 19 ; // 31 : 13
} PINMUX_INT_IO2_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INT_IO3_SRC_SEL  : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 2  ; // 2  : 1
    __IO uint32_t INT_IO3_IE       : 1  ; // 3  : 3
    __IO uint32_t INT_IO3_PULL_SEL : 1  ; // 4  : 4
    __IO uint32_t INT_IO3_PU       : 1  ; // 5  : 5
    __IO uint32_t INT_IO3_PD       : 1  ; // 6  : 6
    __IO uint32_t RESERVED1        : 1  ; // 7  : 7
    __IO uint32_t INT_IO3_CS       : 1  ; // 8  : 8
    __IO uint32_t INT_IO3_DR       : 1  ; // 9  : 9
    __IO uint32_t INT_IO3_OD       : 1  ; // 10 : 10
    __IO uint32_t INT_IO3_OS       : 1  ; // 11 : 11
    __IO uint32_t INT_IO3_SR       : 1  ; // 12 : 12
    __IO uint32_t RESERVED0        : 19 ; // 31 : 13
} PINMUX_INT_IO3_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t LED_DIS_SRC_SEL  : 2  ; // 1  : 0
    __IO uint32_t RESERVED0        : 30 ; // 31 : 2
} PINMUX_LED_DIS_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t AFE_INT_IE_DIS   : 1  ; // 0  : 0
    __IO uint32_t AFE_INT_PD_DIS   : 1  ; // 1  : 1
    __IO uint32_t VS_PORB_PU_DIS   : 1  ; // 2  : 2
    __IO uint32_t SWD_DI_IE_DIS    : 1  ; // 3  : 3
    __IO uint32_t SWD_DI_PU_DIS    : 1  ; // 4  : 4
    __IO uint32_t SWD_CLK_IE_DIS   : 1  ; // 5  : 5
    __IO uint32_t SWD_CLK_PD_DIS   : 1  ; // 6  : 6
    __IO uint32_t RESERVED0        : 25 ; // 31 : 7
} PINMUX_PIN_LP_CTRL_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t INT_IO0_CFG               ; // 0x0000
        PINMUX_INT_IO0_CFG_FIELD_T INT_IO0_CFG_F ;
    };

    union
    {
        __IO  uint32_t INT_IO1_CFG               ; // 0x0004
        PINMUX_INT_IO1_CFG_FIELD_T INT_IO1_CFG_F ;
    };

    union
    {
        __IO  uint32_t INT_IO2_CFG               ; // 0x0008
        PINMUX_INT_IO2_CFG_FIELD_T INT_IO2_CFG_F ;
    };

    union
    {
        __IO  uint32_t INT_IO3_CFG               ; // 0x000C
        PINMUX_INT_IO3_CFG_FIELD_T INT_IO3_CFG_F ;
    };

    union
    {
        __IO  uint32_t LED_DIS_CFG               ; // 0x0010
        PINMUX_LED_DIS_CFG_FIELD_T LED_DIS_CFG_F ;
    };

    union
    {
        __IO  uint32_t PIN_LP_CTRL               ; // 0x0014
        PINMUX_PIN_LP_CTRL_FIELD_T PIN_LP_CTRL_F ;
    };

} PINMUX_REG_TypeDef;

#endif
