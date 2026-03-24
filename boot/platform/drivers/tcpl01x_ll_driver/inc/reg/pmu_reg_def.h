/**
 *****************************************************************************
 * @brief   pmu_reg_def header file.
 *
 * @file    pmu_reg_def.h
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

#ifndef   PMU_DEF_H__
#define   PMU_DEF_H__

// Register Offset Macro Definition
#define PMU_SLEEP_MODE_OFFSET                                   0x0000
#define PMU_WAIT_CYCLE_OFFSET                                   0x0004
#define PMU_PMU_CTRL_OFFSET                                     0x0008
#define PMU_PMU_LOCK_OFFSET                                     0x00FC

// Register Address Macro Definition
#define PMU_SLEEP_MODE_ADDR                                     ( PMU_BASE_ADDR + PMU_SLEEP_MODE_OFFSET)
#define PMU_WAIT_CYCLE_ADDR                                     ( PMU_BASE_ADDR + PMU_WAIT_CYCLE_OFFSET)
#define PMU_PMU_CTRL_ADDR                                       ( PMU_BASE_ADDR + PMU_PMU_CTRL_OFFSET)
#define PMU_PMU_LOCK_ADDR                                       ( PMU_BASE_ADDR + PMU_PMU_LOCK_OFFSET)

// Register Field Macro Definition
#define PMU_SLEEP_MODE_SLP_MODE_SHIFT                          0
#define PMU_SLEEP_MODE_SLP_MODE_MASK                           0x00000003
#define PMU_SLEEP_MODE_SLP_MODE_SET(n)                         (((uint32_t)(n) << 0  ) & 0x00000003)
#define PMU_SLEEP_MODE_SLP_MODE_CLR                            0xFFFFFFFC

#define PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_SHIFT                   0
#define PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_MASK                    0x00000007
#define PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_SET(n)                  (((uint32_t)(n) << 0  ) & 0x00000007)
#define PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_CLR                     0xFFFFFFF8

#define PMU_PMU_CTRL_SLWK_PCLK_SW_SHIFT                        0
#define PMU_PMU_CTRL_SLWK_PCLK_SW_MASK                         0x00000001
#define PMU_PMU_CTRL_SLWK_PCLK_SW_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define PMU_PMU_CTRL_SLWK_PCLK_SW_CLR                          0xFFFFFFFE

#define PMU_PMU_LOCK_PMU_LOCK_SHIFT                            0
#define PMU_PMU_LOCK_PMU_LOCK_MASK                             0x00000001
#define PMU_PMU_LOCK_PMU_LOCK_SET(n)                           (((uint32_t)(n) << 0  ) & 0x00000001)
#define PMU_PMU_LOCK_PMU_LOCK_CLR                              0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t SLP_MODE        : 2  ; // 1  : 0
    __IO uint32_t RESERVED0       : 30 ; // 31 : 2
} PMU_SLEEP_MODE_FIELD_T;

typedef struct
{
    __IO uint32_t PUP_CYCLE_HFCLK : 3  ; // 2  : 0
    __IO uint32_t RESERVED0       : 29 ; // 31 : 3
} PMU_WAIT_CYCLE_FIELD_T;

typedef struct
{
    __IO uint32_t SLWK_PCLK_SW    : 1  ; // 0  : 0
    __IO uint32_t RESERVED0       : 31 ; // 31 : 1
} PMU_PMU_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t PMU_LOCK        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0       : 31 ; // 31 : 1
} PMU_PMU_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t SLEEPMODE               ; // 0x0000
        PMU_SLEEP_MODE_FIELD_T SLEEP_MODE_F    ;
    };

    union
    {
        __IO  uint32_t WAIT_CYCLE              ; // 0x0004
        PMU_WAIT_CYCLE_FIELD_T WAIT_CYCLE_F    ;
    };

    union
    {
        __IO  uint32_t PMU_CTRL                ; // 0x0008
        PMU_PMU_CTRL_FIELD_T PMU_CTRL_F        ;
    };

    uint32_t RESERVED0[60]                      ;

    union
    {
        __IO  uint32_t PMU_LOCK                ; // 0x00FC
        PMU_PMU_LOCK_FIELD_T PMU_LOCK_F        ;
    };

} PMU_REG_TypeDef;

#endif
