/**
 *****************************************************************************
 * @brief   crg_reg_def header file.
 *
 * @file    crg_reg_def.h
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

#ifndef   CRG_DEF_H__
#define   CRG_DEF_H__

// Register Offset Macro Definition
#define CRG_HCLK_CTRL_OFFSET                                    0x0000
#define CRG_PCLK_CTRL_OFFSET                                    0x0004
#define CRG_M0_CLKRST_CTRL_OFFSET                               0x0008
#define CRG_TIM_CLKRST_CTRL_OFFSET                              0x000C
#define CRG_AFE_CLKRST_CTRL_OFFSET                              0x0010
#define CRG_CRC_CLKRST_CTRL_OFFSET                              0x0014
#define CRG_PINMUX_CLKRST_CTRL_OFFSET                           0x0018
#define CRG_PRINT_UART_CLKRST_CTRL_OFFSET                       0x001C
#define CRG_RCCLK_CTRL_OFFSET                                   0x0020
#define CRG_WDG_CLKRST_CTRL_OFFSET                              0x0024
#define CRG_RST_CTRL_OFFSET                                     0x0028
#define CRG_CRG_LOCK_OFFSET                                     0x00FC

// Register Address Macro Definition
#define CRG_HCLK_CTRL_ADDR                                      ( CRG_BASE_ADDR + CRG_HCLK_CTRL_OFFSET)
#define CRG_PCLK_CTRL_ADDR                                      ( CRG_BASE_ADDR + CRG_PCLK_CTRL_OFFSET)
#define CRG_M0_CLKRST_CTRL_ADDR                                 ( CRG_BASE_ADDR + CRG_M0_CLKRST_CTRL_OFFSET)
#define CRG_TIM_CLKRST_CTRL_ADDR                                ( CRG_BASE_ADDR + CRG_TIM_CLKRST_CTRL_OFFSET)
#define CRG_AFE_CLKRST_CTRL_ADDR                                ( CRG_BASE_ADDR + CRG_AFE_CLKRST_CTRL_OFFSET)
#define CRG_CRC_CLKRST_CTRL_ADDR                                ( CRG_BASE_ADDR + CRG_CRC_CLKRST_CTRL_OFFSET)
#define CRG_PINMUX_CLKRST_CTRL_ADDR                             ( CRG_BASE_ADDR + CRG_PINMUX_CLKRST_CTRL_OFFSET)
#define CRG_PRINT_UART_CLKRST_CTRL_ADDR                         ( CRG_BASE_ADDR + CRG_PRINT_UART_CLKRST_CTRL_OFFSET)
#define CRG_RCCLK_CTRL_ADDR                                     ( CRG_BASE_ADDR + CRG_RCCLK_CTRL_OFFSET)
#define CRG_WDG_CLKRST_CTRL_ADDR                                ( CRG_BASE_ADDR + CRG_WDG_CLKRST_CTRL_OFFSET)
#define CRG_RST_CTRL_ADDR                                       ( CRG_BASE_ADDR + CRG_RST_CTRL_OFFSET)
#define CRG_CRG_LOCK_ADDR                                       ( CRG_BASE_ADDR + CRG_CRG_LOCK_OFFSET)

// Register Field Macro Definition
#define CRG_HCLK_CTRL_AUTO_HCLK_FORCE_EN_SHIFT                                8
#define CRG_HCLK_CTRL_AUTO_HCLK_FORCE_EN_MASK                                 0x00000100
#define CRG_HCLK_CTRL_AUTO_HCLK_FORCE_EN_SET(n)                               (((uint32_t)(n) << 8  ) & 0x00000100)
#define CRG_HCLK_CTRL_AUTO_HCLK_FORCE_EN_CLR                                  0xFFFFFEFF

#define CRG_HCLK_CTRL_HCLK_DIV_SHIFT                                          4
#define CRG_HCLK_CTRL_HCLK_DIV_MASK                                           0x000000F0
#define CRG_HCLK_CTRL_HCLK_DIV_SET(n)                                         (((uint32_t)(n) << 4  ) & 0x000000F0)
#define CRG_HCLK_CTRL_HCLK_DIV_CLR                                            0xFFFFFF0F

#define CRG_HCLK_CTRL_HCLK_DIV_LOAD_SHIFT                                     3
#define CRG_HCLK_CTRL_HCLK_DIV_LOAD_MASK                                      0x00000008
#define CRG_HCLK_CTRL_HCLK_DIV_LOAD_SET(n)                                    (((uint32_t)(n) << 3  ) & 0x00000008)
#define CRG_HCLK_CTRL_HCLK_DIV_LOAD_CLR                                       0xFFFFFFF7

#define CRG_HCLK_CTRL_HCLK_SEL_SHIFT                                          0
#define CRG_HCLK_CTRL_HCLK_SEL_MASK                                           0x00000001
#define CRG_HCLK_CTRL_HCLK_SEL_SET(n)                                         (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_HCLK_CTRL_HCLK_SEL_CLR                                            0xFFFFFFFE

#define CRG_PCLK_CTRL_PCLK_EN_TEST_SHIFT                                      9
#define CRG_PCLK_CTRL_PCLK_EN_TEST_MASK                                       0x00000200
#define CRG_PCLK_CTRL_PCLK_EN_TEST_SET(n)                                     (((uint32_t)(n) << 9  ) & 0x00000200)
#define CRG_PCLK_CTRL_PCLK_EN_TEST_CLR                                        0xFFFFFDFF

#define CRG_PCLK_CTRL_PCLK_EN_PMU_SHIFT                                       8
#define CRG_PCLK_CTRL_PCLK_EN_PMU_MASK                                        0x00000100
#define CRG_PCLK_CTRL_PCLK_EN_PMU_SET(n)                                      (((uint32_t)(n) << 8  ) & 0x00000100)
#define CRG_PCLK_CTRL_PCLK_EN_PMU_CLR                                         0xFFFFFEFF

#define CRG_PCLK_CTRL_PCLK_DIV_LOAD_SHIFT                                     3
#define CRG_PCLK_CTRL_PCLK_DIV_LOAD_MASK                                      0x00000008
#define CRG_PCLK_CTRL_PCLK_DIV_LOAD_SET(n)                                    (((uint32_t)(n) << 3  ) & 0x00000008)
#define CRG_PCLK_CTRL_PCLK_DIV_LOAD_CLR                                       0xFFFFFFF7

#define CRG_PCLK_CTRL_PCLK_DIV_SHIFT                                          0
#define CRG_PCLK_CTRL_PCLK_DIV_MASK                                           0x00000007
#define CRG_PCLK_CTRL_PCLK_DIV_SET(n)                                         (((uint32_t)(n) << 0  ) & 0x00000007)
#define CRG_PCLK_CTRL_PCLK_DIV_CLR                                            0xFFFFFFF8

#define CRG_M0_CLKRST_CTRL_FCLK_DIV_SYSTICK_SHIFT                             4
#define CRG_M0_CLKRST_CTRL_FCLK_DIV_SYSTICK_MASK                              0x000000F0
#define CRG_M0_CLKRST_CTRL_FCLK_DIV_SYSTICK_SET(n)                            (((uint32_t)(n) << 4  ) & 0x000000F0)
#define CRG_M0_CLKRST_CTRL_FCLK_DIV_SYSTICK_CLR                               0xFFFFFF0F

#define CRG_M0_CLKRST_CTRL_FCLK_EN_SYSTICK_SHIFT                              2
#define CRG_M0_CLKRST_CTRL_FCLK_EN_SYSTICK_MASK                               0x00000004
#define CRG_M0_CLKRST_CTRL_FCLK_EN_SYSTICK_SET(n)                             (((uint32_t)(n) << 2  ) & 0x00000004)
#define CRG_M0_CLKRST_CTRL_FCLK_EN_SYSTICK_CLR                                0xFFFFFFFB

#define CRG_M0_CLKRST_CTRL_M0_LOCKUP_EN_SHIFT                                 1
#define CRG_M0_CLKRST_CTRL_M0_LOCKUP_EN_MASK                                  0x00000002
#define CRG_M0_CLKRST_CTRL_M0_LOCKUP_EN_SET(n)                                (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_M0_CLKRST_CTRL_M0_LOCKUP_EN_CLR                                   0xFFFFFFFD

#define CRG_M0_CLKRST_CTRL_RST_M0_SHIFT                                       0
#define CRG_M0_CLKRST_CTRL_RST_M0_MASK                                        0x00000001
#define CRG_M0_CLKRST_CTRL_RST_M0_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_M0_CLKRST_CTRL_RST_M0_CLR                                         0xFFFFFFFE

#define CRG_TIM_CLKRST_CTRL_FCLK_DIV_TIM_SHIFT                                4
#define CRG_TIM_CLKRST_CTRL_FCLK_DIV_TIM_MASK                                 0x000000F0
#define CRG_TIM_CLKRST_CTRL_FCLK_DIV_TIM_SET(n)                               (((uint32_t)(n) << 4  ) & 0x000000F0)
#define CRG_TIM_CLKRST_CTRL_FCLK_DIV_TIM_CLR                                  0xFFFFFF0F

#define CRG_TIM_CLKRST_CTRL_FCLK_SEL_TIM_SHIFT                                3
#define CRG_TIM_CLKRST_CTRL_FCLK_SEL_TIM_MASK                                 0x00000008
#define CRG_TIM_CLKRST_CTRL_FCLK_SEL_TIM_SET(n)                               (((uint32_t)(n) << 3  ) & 0x00000008)
#define CRG_TIM_CLKRST_CTRL_FCLK_SEL_TIM_CLR                                  0xFFFFFFF7

#define CRG_TIM_CLKRST_CTRL_FCLK_EN_TIM_SHIFT                                 2
#define CRG_TIM_CLKRST_CTRL_FCLK_EN_TIM_MASK                                  0x00000004
#define CRG_TIM_CLKRST_CTRL_FCLK_EN_TIM_SET(n)                                (((uint32_t)(n) << 2  ) & 0x00000004)
#define CRG_TIM_CLKRST_CTRL_FCLK_EN_TIM_CLR                                   0xFFFFFFFB

#define CRG_TIM_CLKRST_CTRL_PCLK_EN_TIM_SHIFT                                 1
#define CRG_TIM_CLKRST_CTRL_PCLK_EN_TIM_MASK                                  0x00000002
#define CRG_TIM_CLKRST_CTRL_PCLK_EN_TIM_SET(n)                                (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_TIM_CLKRST_CTRL_PCLK_EN_TIM_CLR                                   0xFFFFFFFD

#define CRG_TIM_CLKRST_CTRL_RST_TIM_SHIFT                                     0
#define CRG_TIM_CLKRST_CTRL_RST_TIM_MASK                                      0x00000001
#define CRG_TIM_CLKRST_CTRL_RST_TIM_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_TIM_CLKRST_CTRL_RST_TIM_CLR                                       0xFFFFFFFE

#define CRG_AFE_CLKRST_CTRL_PCLK_EN_AFE_SHIFT                                 1
#define CRG_AFE_CLKRST_CTRL_PCLK_EN_AFE_MASK                                  0x00000002
#define CRG_AFE_CLKRST_CTRL_PCLK_EN_AFE_SET(n)                                (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_AFE_CLKRST_CTRL_PCLK_EN_AFE_CLR                                   0xFFFFFFFD

#define CRG_AFE_CLKRST_CTRL_RST_AFE_SHIFT                                     0
#define CRG_AFE_CLKRST_CTRL_RST_AFE_MASK                                      0x00000001
#define CRG_AFE_CLKRST_CTRL_RST_AFE_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_AFE_CLKRST_CTRL_RST_AFE_CLR                                       0xFFFFFFFE

#define CRG_CRC_CLKRST_CTRL_PCLK_EN_CRC_SHIFT                                 1
#define CRG_CRC_CLKRST_CTRL_PCLK_EN_CRC_MASK                                  0x00000002
#define CRG_CRC_CLKRST_CTRL_PCLK_EN_CRC_SET(n)                                (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_CRC_CLKRST_CTRL_PCLK_EN_CRC_CLR                                   0xFFFFFFFD

#define CRG_CRC_CLKRST_CTRL_RST_CRC_SHIFT                                     0
#define CRG_CRC_CLKRST_CTRL_RST_CRC_MASK                                      0x00000001
#define CRG_CRC_CLKRST_CTRL_RST_CRC_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_CRC_CLKRST_CTRL_RST_CRC_CLR                                       0xFFFFFFFE

#define CRG_PINMUX_CLKRST_CTRL_PCLK_EN_PINMUX_SHIFT                           1
#define CRG_PINMUX_CLKRST_CTRL_PCLK_EN_PINMUX_MASK                            0x00000002
#define CRG_PINMUX_CLKRST_CTRL_PCLK_EN_PINMUX_SET(n)                          (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_PINMUX_CLKRST_CTRL_PCLK_EN_PINMUX_CLR                             0xFFFFFFFD

#define CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_SHIFT                               0
#define CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_MASK                                0x00000001
#define CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_CLR                                 0xFFFFFFFE

#define CRG_PRINT_UART_CLKRST_CTRL_PCLK_EN_PRINT_UART_SHIFT                   1
#define CRG_PRINT_UART_CLKRST_CTRL_PCLK_EN_PRINT_UART_MASK                    0x00000002
#define CRG_PRINT_UART_CLKRST_CTRL_PCLK_EN_PRINT_UART_SET(n)                  (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_PRINT_UART_CLKRST_CTRL_PCLK_EN_PRINT_UART_CLR                     0xFFFFFFFD

#define CRG_PRINT_UART_CLKRST_CTRL_RST_PRINT_UART_SHIFT                       0
#define CRG_PRINT_UART_CLKRST_CTRL_RST_PRINT_UART_MASK                        0x00000001
#define CRG_PRINT_UART_CLKRST_CTRL_RST_PRINT_UART_SET(n)                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_PRINT_UART_CLKRST_CTRL_RST_PRINT_UART_CLR                         0xFFFFFFFE

#define CRG_RCCLK_CTRL_HRC_READY_SHIFT                                        1
#define CRG_RCCLK_CTRL_HRC_READY_MASK                                         0x00000002
#define CRG_RCCLK_CTRL_HRC_READY_SET(n)                                       (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_RCCLK_CTRL_HRC_READY_CLR                                          0xFFFFFFFD

#define CRG_RCCLK_CTRL_SW_HRC_EN_SHIFT                                        0
#define CRG_RCCLK_CTRL_SW_HRC_EN_MASK                                         0x00000001
#define CRG_RCCLK_CTRL_SW_HRC_EN_SET(n)                                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_RCCLK_CTRL_SW_HRC_EN_CLR                                          0xFFFFFFFE

#define CRG_WDG_CLKRST_CTRL_FCLK_DIV_WDG_SHIFT                                4
#define CRG_WDG_CLKRST_CTRL_FCLK_DIV_WDG_MASK                                 0x0000FFF0
#define CRG_WDG_CLKRST_CTRL_FCLK_DIV_WDG_SET(n)                               (((uint32_t)(n) << 4  ) & 0x0000FFF0)
#define CRG_WDG_CLKRST_CTRL_FCLK_DIV_WDG_CLR                                  0xFFFF000F

#define CRG_WDG_CLKRST_CTRL_PCLK_EN_WDG_SHIFT                                 1
#define CRG_WDG_CLKRST_CTRL_PCLK_EN_WDG_MASK                                  0x00000002
#define CRG_WDG_CLKRST_CTRL_PCLK_EN_WDG_SET(n)                                (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRG_WDG_CLKRST_CTRL_PCLK_EN_WDG_CLR                                   0xFFFFFFFD

#define CRG_RST_CTRL_SW_POR_REQ_SHIFT                                         8
#define CRG_RST_CTRL_SW_POR_REQ_MASK                                          0x00000100
#define CRG_RST_CTRL_SW_POR_REQ_SET(n)                                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define CRG_RST_CTRL_SW_POR_REQ_CLR                                           0xFFFFFEFF

#define CRG_RST_CTRL_CLR_RST_SHIFT                                            6
#define CRG_RST_CTRL_CLR_RST_MASK                                             0x00000040
#define CRG_RST_CTRL_CLR_RST_SET(n)                                           (((uint32_t)(n) << 6  ) & 0x00000040)
#define CRG_RST_CTRL_CLR_RST_CLR                                              0xFFFFFFBF

#define CRG_RST_CTRL_RST_FLAG_SHIFT                                           0
#define CRG_RST_CTRL_RST_FLAG_MASK                                            0x0000003F
#define CRG_RST_CTRL_RST_FLAG_SET(n)                                          (((uint32_t)(n) << 0  ) & 0x0000003F)
#define CRG_RST_CTRL_RST_FLAG_CLR                                             0xFFFFFFC0

#define CRG_CRG_LOCK_CRG_LOCK_SHIFT                                           0
#define CRG_CRG_LOCK_CRG_LOCK_MASK                                            0x00000001
#define CRG_CRG_LOCK_CRG_LOCK_SET(n)                                          (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRG_CRG_LOCK_CRG_LOCK_CLR                                             0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t HCLK_SEL           : 1  ; // 0  : 0
    __IO uint32_t RESERVED1          : 2  ; // 2  : 1
    __IO uint32_t HCLK_DIV_LOAD      : 1  ; // 3  : 3
    __IO uint32_t HCLK_DIV           : 4  ; // 7  : 4
    __IO uint32_t AUTO_HCLK_FORCE_EN : 1  ; // 8  : 8
    __IO uint32_t RESERVED0          : 23 ; // 31 : 9
} CRG_HCLK_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t PCLK_DIV           : 3  ; // 2  : 0
    __IO uint32_t PCLK_DIV_LOAD      : 1  ; // 3  : 3
    __IO uint32_t RESERVED1          : 4  ; // 7  : 4
    __IO uint32_t PCLK_EN_PMU        : 1  ; // 8  : 8
    __IO uint32_t PCLK_EN_TEST       : 1  ; // 9  : 9
    __IO uint32_t RESERVED0          : 22 ; // 31 : 10
} CRG_PCLK_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_M0             : 1  ; // 0  : 0
    __IO uint32_t M0_LOCKUP_EN       : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_SYSTICK    : 1  ; // 2  : 2
    __IO uint32_t RESERVED1          : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_SYSTICK   : 4  ; // 7  : 4
    __IO uint32_t RESERVED0          : 24 ; // 31 : 8
} CRG_M0_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_TIM            : 1  ; // 0  : 0
    __IO uint32_t PCLK_EN_TIM        : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_TIM        : 1  ; // 2  : 2
    __IO uint32_t FCLK_SEL_TIM       : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_TIM       : 4  ; // 7  : 4
    __IO uint32_t RESERVED0          : 24 ; // 31 : 8
} CRG_TIM_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_AFE            : 1  ; // 0  : 0
    __IO uint32_t PCLK_EN_AFE        : 1  ; // 1  : 1
    __IO uint32_t RESERVED0          : 30 ; // 31 : 2
} CRG_AFE_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_CRC            : 1  ; // 0  : 0
    __IO uint32_t PCLK_EN_CRC        : 1  ; // 1  : 1
    __IO uint32_t RESERVED0          : 30 ; // 31 : 2
} CRG_CRC_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_PINMUX         : 1  ; // 0  : 0
    __IO uint32_t PCLK_EN_PINMUX     : 1  ; // 1  : 1
    __IO uint32_t RESERVED0          : 30 ; // 31 : 2
} CRG_PINMUX_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_PRINT_UART     : 1  ; // 0  : 0
    __IO uint32_t PCLK_EN_PRINT_UART : 1  ; // 1  : 1
    __IO uint32_t RESERVED0          : 30 ; // 31 : 2
} CRG_PRINT_UART_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t SW_HRC_EN          : 1  ; // 0  : 0
    __IO uint32_t HRC_READY          : 1  ; // 1  : 1
    __IO uint32_t RESERVED0          : 30 ; // 31 : 2
} CRG_RCCLK_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RESERVED2          : 1  ; // 0  : 0
    __IO uint32_t PCLK_EN_WDG        : 1  ; // 1  : 1
    __IO uint32_t RESERVED1          : 2  ; // 3  : 2
    __IO uint32_t FCLK_DIV_WDG       : 12 ; // 15 : 4
    __IO uint32_t RESERVED0          : 16 ; // 31 : 16
} CRG_WDG_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_FLAG           : 6  ; // 5  : 0
    __IO uint32_t CLR_RST            : 1  ; // 6  : 6
    __IO uint32_t RESERVED1          : 1  ; // 7  : 7
    __IO uint32_t SW_POR_REQ         : 1  ; // 8  : 8
    __IO uint32_t RESERVED0          : 23 ; // 31 : 9
} CRG_RST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t CRG_LOCK           : 1  ; // 0  : 0
    __IO uint32_t RESERVED0          : 31 ; // 31 : 1
} CRG_CRG_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t HCLK_CTRL                                       ; // 0x0000
        CRG_HCLK_CTRL_FIELD_T HCLK_CTRL_F                              ;
    };

    union
    {
        __IO  uint32_t PCLK_CTRL                                       ; // 0x0004
        CRG_PCLK_CTRL_FIELD_T PCLK_CTRL_F                              ;
    };

    union
    {
        __IO  uint32_t M0_CLKRST_CTRL                                  ; // 0x0008
        CRG_M0_CLKRST_CTRL_FIELD_T M0_CLKRST_CTRL_F                    ;
    };

    union
    {
        __IO  uint32_t TIM_CLKRST_CTRL                                 ; // 0x000C
        CRG_TIM_CLKRST_CTRL_FIELD_T TIM_CLKRST_CTRL_F                  ;
    };

    union
    {
        __IO  uint32_t AFE_CLKRST_CTRL                                 ; // 0x0010
        CRG_AFE_CLKRST_CTRL_FIELD_T AFE_CLKRST_CTRL_F                  ;
    };

    union
    {
        __IO  uint32_t CRC_CLKRST_CTRL                                 ; // 0x0014
        CRG_CRC_CLKRST_CTRL_FIELD_T CRC_CLKRST_CTRL_F                  ;
    };

    union
    {
        __IO  uint32_t PINMUX_CLKRST_CTRL                              ; // 0x0018
        CRG_PINMUX_CLKRST_CTRL_FIELD_T PINMUX_CLKRST_CTRL_F            ;
    };

    union
    {
        __IO  uint32_t PRINT_UART_CLKRST_CTRL                          ; // 0x001C
        CRG_PRINT_UART_CLKRST_CTRL_FIELD_T PRINT_UART_CLKRST_CTRL_F    ;
    };

    union
    {
        __IO  uint32_t RCCLK_CTRL                                      ; // 0x0020
        CRG_RCCLK_CTRL_FIELD_T RCCLK_CTRL_F                            ;
    };

    union
    {
        __IO  uint32_t WDG_CLKRST_CTRL                                 ; // 0x0024
        CRG_WDG_CLKRST_CTRL_FIELD_T WDG_CLKRST_CTRL_F                  ;
    };

    union
    {
        __IO  uint32_t RST_CTRL                                        ; // 0x0028
        CRG_RST_CTRL_FIELD_T RST_CTRL_F                                ;
    };

    uint32_t RESERVED0[52]                                              ;

    union
    {
        __IO  uint32_t CRG_LOCK                                        ; // 0x00FC
        CRG_CRG_LOCK_FIELD_T CRG_LOCK_F                                ;
    };

} CRG_REG_TypeDef;

#endif
