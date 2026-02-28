/**
 *****************************************************************************
 * @brief   afe_pinmux_reg_def header file.
 *
 * @file    afe_pinmux_reg_def.h
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

#ifndef   AFE_PINMUX_DEF_H__
#define   AFE_PINMUX_DEF_H__

// Register Offset Macro Definition
#define AFE_PINMUX_OUT0_CFG_OFFSET                              0x0000
#define AFE_PINMUX_OUT1_CFG_OFFSET                              0x0004
#define AFE_PINMUX_OUT2_CFG_OFFSET                              0x0008
#define AFE_PINMUX_IO3_CFG_OFFSET                               0x000C
#define AFE_PINMUX_TEST_CFG_OFFSET                              0x0010
#define AFE_PINMUX_LED_DIS_CFG_OFFSET                           0x0014
#define AFE_PINMUX_INT_IO2_CFG_OFFSET                           0x0018

// Register Address Macro Definition
#define AFE_PINMUX_OUT0_CFG_ADDR                                ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_OUT0_CFG_OFFSET)
#define AFE_PINMUX_OUT1_CFG_ADDR                                ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_OUT1_CFG_OFFSET)
#define AFE_PINMUX_OUT2_CFG_ADDR                                ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_OUT2_CFG_OFFSET)
#define AFE_PINMUX_IO3_CFG_ADDR                                 ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_IO3_CFG_OFFSET)
#define AFE_PINMUX_TEST_CFG_ADDR                                ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_TEST_CFG_OFFSET)
#define AFE_PINMUX_LED_DIS_CFG_ADDR                             ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_LED_DIS_CFG_OFFSET)
#define AFE_PINMUX_INT_IO2_CFG_ADDR                             ( AFE_PINMUX_BASE_ADDR + AFE_PINMUX_INT_IO2_CFG_OFFSET)

// Register Field Macro Definition
#define AFE_PINMUX_OUT0_CFG_OUT0_CS_SHIFT                              4
#define AFE_PINMUX_OUT0_CFG_OUT0_CS_MASK                               0x00000010
#define AFE_PINMUX_OUT0_CFG_OUT0_CS_SET(n)                             (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PINMUX_OUT0_CFG_OUT0_CS_CLR                                0xFFFFFFEF

#define AFE_PINMUX_OUT0_CFG_OUT0_IE_SHIFT                              3
#define AFE_PINMUX_OUT0_CFG_OUT0_IE_MASK                               0x00000008
#define AFE_PINMUX_OUT0_CFG_OUT0_IE_SET(n)                             (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_PINMUX_OUT0_CFG_OUT0_IE_CLR                                0xFFFFFFF7

#define AFE_PINMUX_OUT0_CFG_OUT0_SRC_SEL_SHIFT                         0
#define AFE_PINMUX_OUT0_CFG_OUT0_SRC_SEL_MASK                          0x00000007
#define AFE_PINMUX_OUT0_CFG_OUT0_SRC_SEL_SET(n)                        (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PINMUX_OUT0_CFG_OUT0_SRC_SEL_CLR                           0xFFFFFFF8

#define AFE_PINMUX_OUT1_CFG_OUT1_CS_SHIFT                              4
#define AFE_PINMUX_OUT1_CFG_OUT1_CS_MASK                               0x00000010
#define AFE_PINMUX_OUT1_CFG_OUT1_CS_SET(n)                             (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PINMUX_OUT1_CFG_OUT1_CS_CLR                                0xFFFFFFEF

#define AFE_PINMUX_OUT1_CFG_OUT1_IE_SHIFT                              3
#define AFE_PINMUX_OUT1_CFG_OUT1_IE_MASK                               0x00000008
#define AFE_PINMUX_OUT1_CFG_OUT1_IE_SET(n)                             (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_PINMUX_OUT1_CFG_OUT1_IE_CLR                                0xFFFFFFF7

#define AFE_PINMUX_OUT1_CFG_OUT1_SRC_SEL_SHIFT                         0
#define AFE_PINMUX_OUT1_CFG_OUT1_SRC_SEL_MASK                          0x00000007
#define AFE_PINMUX_OUT1_CFG_OUT1_SRC_SEL_SET(n)                        (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PINMUX_OUT1_CFG_OUT1_SRC_SEL_CLR                           0xFFFFFFF8

#define AFE_PINMUX_OUT2_CFG_OUT2_CS_SHIFT                              4
#define AFE_PINMUX_OUT2_CFG_OUT2_CS_MASK                               0x00000010
#define AFE_PINMUX_OUT2_CFG_OUT2_CS_SET(n)                             (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PINMUX_OUT2_CFG_OUT2_CS_CLR                                0xFFFFFFEF

#define AFE_PINMUX_OUT2_CFG_OUT2_IE_SHIFT                              3
#define AFE_PINMUX_OUT2_CFG_OUT2_IE_MASK                               0x00000008
#define AFE_PINMUX_OUT2_CFG_OUT2_IE_SET(n)                             (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_PINMUX_OUT2_CFG_OUT2_IE_CLR                                0xFFFFFFF7

#define AFE_PINMUX_OUT2_CFG_OUT2_SRC_SEL_SHIFT                         0
#define AFE_PINMUX_OUT2_CFG_OUT2_SRC_SEL_MASK                          0x00000007
#define AFE_PINMUX_OUT2_CFG_OUT2_SRC_SEL_SET(n)                        (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PINMUX_OUT2_CFG_OUT2_SRC_SEL_CLR                           0xFFFFFFF8

#define AFE_PINMUX_IO3_CFG_IO3_SR_SHIFT                                12
#define AFE_PINMUX_IO3_CFG_IO3_SR_MASK                                 0x00001000
#define AFE_PINMUX_IO3_CFG_IO3_SR_SET(n)                               (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_PINMUX_IO3_CFG_IO3_SR_CLR                                  0xFFFFEFFF

#define AFE_PINMUX_IO3_CFG_IO3_OS_SHIFT                                11
#define AFE_PINMUX_IO3_CFG_IO3_OS_MASK                                 0x00000800
#define AFE_PINMUX_IO3_CFG_IO3_OS_SET(n)                               (((uint32_t)(n) << 11 ) & 0x00000800)
#define AFE_PINMUX_IO3_CFG_IO3_OS_CLR                                  0xFFFFF7FF

#define AFE_PINMUX_IO3_CFG_IO3_OD_SHIFT                                10
#define AFE_PINMUX_IO3_CFG_IO3_OD_MASK                                 0x00000400
#define AFE_PINMUX_IO3_CFG_IO3_OD_SET(n)                               (((uint32_t)(n) << 10 ) & 0x00000400)
#define AFE_PINMUX_IO3_CFG_IO3_OD_CLR                                  0xFFFFFBFF

#define AFE_PINMUX_IO3_CFG_IO3_DR_SHIFT                                9
#define AFE_PINMUX_IO3_CFG_IO3_DR_MASK                                 0x00000200
#define AFE_PINMUX_IO3_CFG_IO3_DR_SET(n)                               (((uint32_t)(n) << 9  ) & 0x00000200)
#define AFE_PINMUX_IO3_CFG_IO3_DR_CLR                                  0xFFFFFDFF

#define AFE_PINMUX_IO3_CFG_IO3_CS_SHIFT                                8
#define AFE_PINMUX_IO3_CFG_IO3_CS_MASK                                 0x00000100
#define AFE_PINMUX_IO3_CFG_IO3_CS_SET(n)                               (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PINMUX_IO3_CFG_IO3_CS_CLR                                  0xFFFFFEFF

#define AFE_PINMUX_IO3_CFG_IO3_PD_SHIFT                                6
#define AFE_PINMUX_IO3_CFG_IO3_PD_MASK                                 0x00000040
#define AFE_PINMUX_IO3_CFG_IO3_PD_SET(n)                               (((uint32_t)(n) << 6  ) & 0x00000040)
#define AFE_PINMUX_IO3_CFG_IO3_PD_CLR                                  0xFFFFFFBF

#define AFE_PINMUX_IO3_CFG_IO3_PU_SHIFT                                5
#define AFE_PINMUX_IO3_CFG_IO3_PU_MASK                                 0x00000020
#define AFE_PINMUX_IO3_CFG_IO3_PU_SET(n)                               (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_PINMUX_IO3_CFG_IO3_PU_CLR                                  0xFFFFFFDF

#define AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_SHIFT                          4
#define AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_MASK                           0x00000010
#define AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_SET(n)                         (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_CLR                            0xFFFFFFEF

#define AFE_PINMUX_IO3_CFG_IO3_IE_SHIFT                                3
#define AFE_PINMUX_IO3_CFG_IO3_IE_MASK                                 0x00000008
#define AFE_PINMUX_IO3_CFG_IO3_IE_SET(n)                               (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_PINMUX_IO3_CFG_IO3_IE_CLR                                  0xFFFFFFF7

#define AFE_PINMUX_IO3_CFG_IO3_SRC_SEL_SHIFT                           0
#define AFE_PINMUX_IO3_CFG_IO3_SRC_SEL_MASK                            0x00000007
#define AFE_PINMUX_IO3_CFG_IO3_SRC_SEL_SET(n)                          (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PINMUX_IO3_CFG_IO3_SRC_SEL_CLR                             0xFFFFFFF8

#define AFE_PINMUX_TEST_CFG_TEST_CS_SHIFT                              4
#define AFE_PINMUX_TEST_CFG_TEST_CS_MASK                               0x00000010
#define AFE_PINMUX_TEST_CFG_TEST_CS_SET(n)                             (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PINMUX_TEST_CFG_TEST_CS_CLR                                0xFFFFFFEF

#define AFE_PINMUX_TEST_CFG_TEST_IE_SHIFT                              3
#define AFE_PINMUX_TEST_CFG_TEST_IE_MASK                               0x00000008
#define AFE_PINMUX_TEST_CFG_TEST_IE_SET(n)                             (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_PINMUX_TEST_CFG_TEST_IE_CLR                                0xFFFFFFF7

#define AFE_PINMUX_TEST_CFG_TEST_SRC_SEL_SHIFT                         0
#define AFE_PINMUX_TEST_CFG_TEST_SRC_SEL_MASK                          0x00000007
#define AFE_PINMUX_TEST_CFG_TEST_SRC_SEL_SET(n)                        (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PINMUX_TEST_CFG_TEST_SRC_SEL_CLR                           0xFFFFFFF8

#define AFE_PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_SHIFT                   0
#define AFE_PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_MASK                    0x00000003
#define AFE_PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_SET(n)                  (((uint32_t)(n) << 0  ) & 0x00000003)
#define AFE_PINMUX_LED_DIS_CFG_LED_DIS_SRC_SEL_CLR                     0xFFFFFFFC

#define AFE_PINMUX_INT_IO2_CFG_INT_IO2_PD_SHIFT                        0
#define AFE_PINMUX_INT_IO2_CFG_INT_IO2_PD_MASK                         0x00000001
#define AFE_PINMUX_INT_IO2_CFG_INT_IO2_PD_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PINMUX_INT_IO2_CFG_INT_IO2_PD_CLR                          0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t OUT0_SRC_SEL    : 3  ; // 2  : 0
    __IO uint32_t OUT0_IE         : 1  ; // 3  : 3
    __IO uint32_t OUT0_CS         : 1  ; // 4  : 4
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} AFE_PINMUX_OUT0_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t OUT1_SRC_SEL    : 3  ; // 2  : 0
    __IO uint32_t OUT1_IE         : 1  ; // 3  : 3
    __IO uint32_t OUT1_CS         : 1  ; // 4  : 4
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} AFE_PINMUX_OUT1_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t OUT2_SRC_SEL    : 3  ; // 2  : 0
    __IO uint32_t OUT2_IE         : 1  ; // 3  : 3
    __IO uint32_t OUT2_CS         : 1  ; // 4  : 4
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} AFE_PINMUX_OUT2_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t IO3_SRC_SEL     : 3  ; // 2  : 0
    __IO uint32_t IO3_IE          : 1  ; // 3  : 3
    __IO uint32_t IO3_PULL_SEL    : 1  ; // 4  : 4
    __IO uint32_t IO3_PU          : 1  ; // 5  : 5
    __IO uint32_t IO3_PD          : 1  ; // 6  : 6
    __IO uint32_t RESERVED1       : 1  ; // 7  : 7
    __IO uint32_t IO3_CS          : 1  ; // 8  : 8
    __IO uint32_t IO3_DR          : 1  ; // 9  : 9
    __IO uint32_t IO3_OD          : 1  ; // 10 : 10
    __IO uint32_t IO3_OS          : 1  ; // 11 : 11
    __IO uint32_t IO3_SR          : 1  ; // 12 : 12
    __IO uint32_t RESERVED0       : 19 ; // 31 : 13
} AFE_PINMUX_IO3_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t TEST_SRC_SEL    : 3  ; // 2  : 0
    __IO uint32_t TEST_IE         : 1  ; // 3  : 3
    __IO uint32_t TEST_CS         : 1  ; // 4  : 4
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} AFE_PINMUX_TEST_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t LED_DIS_SRC_SEL : 2  ; // 1  : 0
    __IO uint32_t RESERVED0       : 30 ; // 31 : 2
} AFE_PINMUX_LED_DIS_CFG_FIELD_T;

typedef struct
{
    __IO uint32_t INT_IO2_PD      : 1  ; // 0  : 0
    __IO uint32_t RESERVED0       : 31 ; // 31 : 1
} AFE_PINMUX_INT_IO2_CFG_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t OUT0_CFG                  ; // 0x0000
        AFE_PINMUX_OUT0_CFG_FIELD_T OUT0_CFG_F   ;
    };

    union
    {
        __IO  uint32_t OUT1_CFG                  ; // 0x0004
        AFE_PINMUX_OUT1_CFG_FIELD_T OUT1_CFG_F   ;
    };

    union
    {
        __IO  uint32_t OUT2_CFG                  ; // 0x0008
        AFE_PINMUX_OUT2_CFG_FIELD_T OUT2_CFG_F   ;
    };

    union
    {
        __IO  uint32_t IO3_CFG                   ; // 0x000C
        AFE_PINMUX_IO3_CFG_FIELD_T IO3_CFG_F     ;
    };

    union
    {
        __IO  uint32_t TEST_CFG                  ; // 0x0010
        AFE_PINMUX_TEST_CFG_FIELD_T TEST_CFG_F   ;
    };

    union
    {
        __IO  uint32_t LED_DIS_CFG               ; // 0x0014
        AFE_PINMUX_LED_DIS_CFG_FIELD_T LED_DIS_CFG_F;
    };

    union
    {
        __IO  uint32_t INT_IO2_CFG               ; // 0x0018
        AFE_PINMUX_INT_IO2_CFG_FIELD_T INT_IO2_CFG_F;
    };

} AFE_PINMUX_REG_TypeDef;

#endif
