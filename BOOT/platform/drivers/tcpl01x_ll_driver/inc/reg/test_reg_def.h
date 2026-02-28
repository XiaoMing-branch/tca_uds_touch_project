/**
 *****************************************************************************
 * @brief   test_reg_def header file.
 *
 * @file    test_reg_def.h
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

#ifndef   TEST_DEF_H__
#define   TEST_DEF_H__

// Register Offset Macro Definition
#define TEST_TEST_MODE_CTRL_OFFSET                              0x0000
#define TEST_TEST_IO_CTRL_OFFSET                                0x0004
#define TEST_TEST_SWD_CTRL_OFFSET                               0x0008
#define TEST_TEST_PMU_CTRL_OFFSET                               0x000C
#define TEST_TEST_HRC48M_CTRL_OFFSET                            0x0010
#define TEST_TEST_BUS_CTRL_OFFSET                               0x0014
#define TEST_TEST_LOCK_OFFSET                                   0x00FC

// Register Address Macro Definition
#define TEST_TEST_MODE_CTRL_ADDR                                ( TEST_BASE_ADDR + TEST_TEST_MODE_CTRL_OFFSET)
#define TEST_TEST_IO_CTRL_ADDR                                  ( TEST_BASE_ADDR + TEST_TEST_IO_CTRL_OFFSET)
#define TEST_TEST_SWD_CTRL_ADDR                                 ( TEST_BASE_ADDR + TEST_TEST_SWD_CTRL_OFFSET)
#define TEST_TEST_PMU_CTRL_ADDR                                 ( TEST_BASE_ADDR + TEST_TEST_PMU_CTRL_OFFSET)
#define TEST_TEST_HRC48M_CTRL_ADDR                              ( TEST_BASE_ADDR + TEST_TEST_HRC48M_CTRL_OFFSET)
#define TEST_TEST_BUS_CTRL_ADDR                                 ( TEST_BASE_ADDR + TEST_TEST_BUS_CTRL_OFFSET)
#define TEST_TEST_LOCK_ADDR                                     ( TEST_BASE_ADDR + TEST_TEST_LOCK_OFFSET)

// Register Field Macro Definition
#define TEST_TEST_MODE_CTRL_TM_DET_EN_SHIFT                            0
#define TEST_TEST_MODE_CTRL_TM_DET_EN_MASK                             0x00000001
#define TEST_TEST_MODE_CTRL_TM_DET_EN_SET(n)                           (((uint32_t)(n) << 0  ) & 0x00000001)
#define TEST_TEST_MODE_CTRL_TM_DET_EN_CLR                              0xFFFFFFFE

#define TEST_TEST_IO_CTRL_TEST_RD_AFE_INT_SHIFT                        5
#define TEST_TEST_IO_CTRL_TEST_RD_AFE_INT_MASK                         0x00000020
#define TEST_TEST_IO_CTRL_TEST_RD_AFE_INT_SET(n)                       (((uint32_t)(n) << 5  ) & 0x00000020)
#define TEST_TEST_IO_CTRL_TEST_RD_AFE_INT_CLR                          0xFFFFFFDF

#define TEST_TEST_IO_CTRL_TEST_RD_SWD_CLK_SHIFT                        4
#define TEST_TEST_IO_CTRL_TEST_RD_SWD_CLK_MASK                         0x00000010
#define TEST_TEST_IO_CTRL_TEST_RD_SWD_CLK_SET(n)                       (((uint32_t)(n) << 4  ) & 0x00000010)
#define TEST_TEST_IO_CTRL_TEST_RD_SWD_CLK_CLR                          0xFFFFFFEF

#define TEST_TEST_IO_CTRL_TEST_RD_SWD_DI_SHIFT                         3
#define TEST_TEST_IO_CTRL_TEST_RD_SWD_DI_MASK                          0x00000008
#define TEST_TEST_IO_CTRL_TEST_RD_SWD_DI_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define TEST_TEST_IO_CTRL_TEST_RD_SWD_DI_CLR                           0xFFFFFFF7

#define TEST_TEST_IO_CTRL_TEST_WR_SWD_DO_SHIFT                         2
#define TEST_TEST_IO_CTRL_TEST_WR_SWD_DO_MASK                          0x00000004
#define TEST_TEST_IO_CTRL_TEST_WR_SWD_DO_SET(n)                        (((uint32_t)(n) << 2  ) & 0x00000004)
#define TEST_TEST_IO_CTRL_TEST_WR_SWD_DO_CLR                           0xFFFFFFFB

#define TEST_TEST_IO_CTRL_TEST_WR_SWD_OE_SHIFT                         1
#define TEST_TEST_IO_CTRL_TEST_WR_SWD_OE_MASK                          0x00000002
#define TEST_TEST_IO_CTRL_TEST_WR_SWD_OE_SET(n)                        (((uint32_t)(n) << 1  ) & 0x00000002)
#define TEST_TEST_IO_CTRL_TEST_WR_SWD_OE_CLR                           0xFFFFFFFD

#define TEST_TEST_IO_CTRL_TEST_PIN_LPBK_EN_SHIFT                       0
#define TEST_TEST_IO_CTRL_TEST_PIN_LPBK_EN_MASK                        0x00000001
#define TEST_TEST_IO_CTRL_TEST_PIN_LPBK_EN_SET(n)                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define TEST_TEST_IO_CTRL_TEST_PIN_LPBK_EN_CLR                         0xFFFFFFFE

#define TEST_TEST_SWD_CTRL_FUSE_DISABLE_SWD_SHIFT                      0
#define TEST_TEST_SWD_CTRL_FUSE_DISABLE_SWD_MASK                       0x00000001
#define TEST_TEST_SWD_CTRL_FUSE_DISABLE_SWD_SET(n)                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define TEST_TEST_SWD_CTRL_FUSE_DISABLE_SWD_CLR                        0xFFFFFFFE

#define TEST_TEST_PMU_CTRL_SW_SLP_REQ_SHIFT                            0
#define TEST_TEST_PMU_CTRL_SW_SLP_REQ_MASK                             0x00000001
#define TEST_TEST_PMU_CTRL_SW_SLP_REQ_SET(n)                           (((uint32_t)(n) << 0  ) & 0x00000001)
#define TEST_TEST_PMU_CTRL_SW_SLP_REQ_CLR                              0xFFFFFFFE

#define TEST_TEST_HRC48M_CTRL_RC48M_TEMP_SHIFT                         20
#define TEST_TEST_HRC48M_CTRL_RC48M_TEMP_MASK                          0x00700000
#define TEST_TEST_HRC48M_CTRL_RC48M_TEMP_SET(n)                        (((uint32_t)(n) << 20 ) & 0x00700000)
#define TEST_TEST_HRC48M_CTRL_RC48M_TEMP_CLR                           0xFF8FFFFF

#define TEST_TEST_HRC48M_CTRL_RC48M_FINE_SHIFT                         12
#define TEST_TEST_HRC48M_CTRL_RC48M_FINE_MASK                          0x0001F000
#define TEST_TEST_HRC48M_CTRL_RC48M_FINE_SET(n)                        (((uint32_t)(n) << 12 ) & 0x0001F000)
#define TEST_TEST_HRC48M_CTRL_RC48M_FINE_CLR                           0xFFFE0FFF

#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_TD_SHIFT                    4
#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_TD_MASK                     0x000007F0
#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_TD_SET(n)                   (((uint32_t)(n) << 4  ) & 0x000007F0)
#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_TD_CLR                      0xFFFFF80F

#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_SHIFT                       0
#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_MASK                        0x00000003
#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_SET(n)                      (((uint32_t)(n) << 0  ) & 0x00000003)
#define TEST_TEST_HRC48M_CTRL_RC48M_COARSE_CLR                         0xFFFFFFFC

#define TEST_TEST_BUS_CTRL_EFLASH_TP_SEL_SHIFT                         21
#define TEST_TEST_BUS_CTRL_EFLASH_TP_SEL_MASK                          0x00600000
#define TEST_TEST_BUS_CTRL_EFLASH_TP_SEL_SET(n)                        (((uint32_t)(n) << 21 ) & 0x00600000)
#define TEST_TEST_BUS_CTRL_EFLASH_TP_SEL_CLR                           0xFF9FFFFF

#define TEST_TEST_BUS_CTRL_EFLASH_TP_EN_SHIFT                          20
#define TEST_TEST_BUS_CTRL_EFLASH_TP_EN_MASK                           0x00100000
#define TEST_TEST_BUS_CTRL_EFLASH_TP_EN_SET(n)                         (((uint32_t)(n) << 20 ) & 0x00100000)
#define TEST_TEST_BUS_CTRL_EFLASH_TP_EN_CLR                            0xFFEFFFFF

#define TEST_TEST_BUS_CTRL_CM0_TP_SEL_SHIFT                            17
#define TEST_TEST_BUS_CTRL_CM0_TP_SEL_MASK                             0x00060000
#define TEST_TEST_BUS_CTRL_CM0_TP_SEL_SET(n)                           (((uint32_t)(n) << 17 ) & 0x00060000)
#define TEST_TEST_BUS_CTRL_CM0_TP_SEL_CLR                              0xFFF9FFFF

#define TEST_TEST_BUS_CTRL_CM0_TP_EN_SHIFT                             16
#define TEST_TEST_BUS_CTRL_CM0_TP_EN_MASK                              0x00010000
#define TEST_TEST_BUS_CTRL_CM0_TP_EN_SET(n)                            (((uint32_t)(n) << 16 ) & 0x00010000)
#define TEST_TEST_BUS_CTRL_CM0_TP_EN_CLR                               0xFFFEFFFF

#define TEST_TEST_BUS_CTRL_PMU_TP_SEL_SHIFT                            13
#define TEST_TEST_BUS_CTRL_PMU_TP_SEL_MASK                             0x00006000
#define TEST_TEST_BUS_CTRL_PMU_TP_SEL_SET(n)                           (((uint32_t)(n) << 13 ) & 0x00006000)
#define TEST_TEST_BUS_CTRL_PMU_TP_SEL_CLR                              0xFFFF9FFF

#define TEST_TEST_BUS_CTRL_PMU_TP_EN_SHIFT                             12
#define TEST_TEST_BUS_CTRL_PMU_TP_EN_MASK                              0x00001000
#define TEST_TEST_BUS_CTRL_PMU_TP_EN_SET(n)                            (((uint32_t)(n) << 12 ) & 0x00001000)
#define TEST_TEST_BUS_CTRL_PMU_TP_EN_CLR                               0xFFFFEFFF

#define TEST_TEST_BUS_CTRL_CRG_TP_SEL_SHIFT                            9
#define TEST_TEST_BUS_CTRL_CRG_TP_SEL_MASK                             0x00000600
#define TEST_TEST_BUS_CTRL_CRG_TP_SEL_SET(n)                           (((uint32_t)(n) << 9  ) & 0x00000600)
#define TEST_TEST_BUS_CTRL_CRG_TP_SEL_CLR                              0xFFFFF9FF

#define TEST_TEST_BUS_CTRL_CRG_TP_EN_SHIFT                             8
#define TEST_TEST_BUS_CTRL_CRG_TP_EN_MASK                              0x00000100
#define TEST_TEST_BUS_CTRL_CRG_TP_EN_SET(n)                            (((uint32_t)(n) << 8  ) & 0x00000100)
#define TEST_TEST_BUS_CTRL_CRG_TP_EN_CLR                               0xFFFFFEFF

#define TEST_TEST_BUS_CTRL_TOP_TP_BIT_SEL_SHIFT                        4
#define TEST_TEST_BUS_CTRL_TOP_TP_BIT_SEL_MASK                         0x000000F0
#define TEST_TEST_BUS_CTRL_TOP_TP_BIT_SEL_SET(n)                       (((uint32_t)(n) << 4  ) & 0x000000F0)
#define TEST_TEST_BUS_CTRL_TOP_TP_BIT_SEL_CLR                          0xFFFFFF0F

#define TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_SHIFT                         1
#define TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_MASK                          0x0000000E
#define TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_SET(n)                        (((uint32_t)(n) << 1  ) & 0x0000000E)
#define TEST_TEST_BUS_CTRL_TOP_TP_IP_SEL_CLR                           0xFFFFFFF1

#define TEST_TEST_BUS_CTRL_TOP_TP_EN_SHIFT                             0
#define TEST_TEST_BUS_CTRL_TOP_TP_EN_MASK                              0x00000001
#define TEST_TEST_BUS_CTRL_TOP_TP_EN_SET(n)                            (((uint32_t)(n) << 0  ) & 0x00000001)
#define TEST_TEST_BUS_CTRL_TOP_TP_EN_CLR                               0xFFFFFFFE

#define TEST_TEST_LOCK_TEST_LOCK_SHIFT                                 0
#define TEST_TEST_LOCK_TEST_LOCK_MASK                                  0x00000001
#define TEST_TEST_LOCK_TEST_LOCK_SET(n)                                (((uint32_t)(n) << 0  ) & 0x00000001)
#define TEST_TEST_LOCK_TEST_LOCK_CLR                                   0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t TM_DET_EN        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} TEST_TEST_MODE_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TEST_PIN_LPBK_EN : 1  ; // 0  : 0
    __IO uint32_t TEST_WR_SWD_OE   : 1  ; // 1  : 1
    __IO uint32_t TEST_WR_SWD_DO   : 1  ; // 2  : 2
    __IO uint32_t TEST_RD_SWD_DI   : 1  ; // 3  : 3
    __IO uint32_t TEST_RD_SWD_CLK  : 1  ; // 4  : 4
    __IO uint32_t TEST_RD_AFE_INT  : 1  ; // 5  : 5
    __IO uint32_t RESERVED0        : 26 ; // 31 : 6
} TEST_TEST_IO_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t FUSE_DISABLE_SWD : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} TEST_TEST_SWD_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t SW_SLP_REQ       : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} TEST_TEST_PMU_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RC48M_COARSE     : 2  ; // 1  : 0
    __IO uint32_t RESERVED3        : 2  ; // 3  : 2
    __IO uint32_t RC48M_COARSE_TD  : 7  ; // 10 : 4
    __IO uint32_t RESERVED2        : 1  ; // 11 : 11
    __IO uint32_t RC48M_FINE       : 5  ; // 16 : 12
    __IO uint32_t RESERVED1        : 3  ; // 19 : 17
    __IO uint32_t RC48M_TEMP       : 3  ; // 22 : 20
    __IO uint32_t RESERVED0        : 9  ; // 31 : 23
} TEST_TEST_HRC48M_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TOP_TP_EN        : 1  ; // 0  : 0
    __IO uint32_t TOP_TP_IP_SEL    : 3  ; // 3  : 1
    __IO uint32_t TOP_TP_BIT_SEL   : 4  ; // 7  : 4
    __IO uint32_t CRG_TP_EN        : 1  ; // 8  : 8
    __IO uint32_t CRG_TP_SEL       : 2  ; // 10 : 9
    __IO uint32_t RESERVED4        : 1  ; // 11 : 11
    __IO uint32_t PMU_TP_EN        : 1  ; // 12 : 12
    __IO uint32_t PMU_TP_SEL       : 2  ; // 14 : 13
    __IO uint32_t RESERVED3        : 1  ; // 15 : 15
    __IO uint32_t CM0_TP_EN        : 1  ; // 16 : 16
    __IO uint32_t CM0_TP_SEL       : 2  ; // 18 : 17
    __IO uint32_t RESERVED2        : 1  ; // 19 : 19
    __IO uint32_t EFLASH_TP_EN     : 1  ; // 20 : 20
    __IO uint32_t EFLASH_TP_SEL    : 2  ; // 22 : 21
    __IO uint32_t RESERVED1        : 1  ; // 23 : 23
    __IO uint32_t RESERVED0        : 8  ; // 31 : 24
} TEST_TEST_BUS_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TEST_LOCK        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} TEST_TEST_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t TEST_MODE_CTRL                      ; // 0x0000
        TEST_TEST_MODE_CTRL_FIELD_T TEST_MODE_CTRL_F       ;
    };

    union
    {
        __IO  uint32_t TEST_IO_CTRL                        ; // 0x0004
        TEST_TEST_IO_CTRL_FIELD_T TEST_IO_CTRL_F           ;
    };

    union
    {
        __IO  uint32_t TEST_SWD_CTRL                       ; // 0x0008
        TEST_TEST_SWD_CTRL_FIELD_T TEST_SWD_CTRL_F         ;
    };

    union
    {
        __IO  uint32_t TEST_PMU_CTRL                       ; // 0x000C
        TEST_TEST_PMU_CTRL_FIELD_T TEST_PMU_CTRL_F         ;
    };

    union
    {
        __IO  uint32_t TEST_HRC48M_CTRL                    ; // 0x0010
        TEST_TEST_HRC48M_CTRL_FIELD_T TEST_HRC48M_CTRL_F   ;
    };

    union
    {
        __IO  uint32_t TEST_BUS_CTRL                       ; // 0x0014
        TEST_TEST_BUS_CTRL_FIELD_T TEST_BUS_CTRL_F         ;
    };

    uint32_t RESERVED0[57]                                  ;

    union
    {
        __IO  uint32_t TEST_LOCK                           ; // 0x00FC
        TEST_TEST_LOCK_FIELD_T TEST_LOCK_F                 ;
    };

} TEST_REG_TypeDef;

#endif
