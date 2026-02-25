/**
 *****************************************************************************
 * @brief   afe_pmu_reg_def header file.
 *
 * @file    afe_pmu_reg_def.h
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

#ifndef   AFE_PMU_DEF_H__
#define   AFE_PMU_DEF_H__

// Register Offset Macro Definition
#define AFE_PMU_SLEEP_MODE_OFFSET                               0x0000
#define AFE_PMU_PMU_CTRL_OFFSET                                 0x0004
#define AFE_PMU_WAIT_CYCLE_OFFSET                               0x0008
#define AFE_PMU_PMU_STATUS_OFFSET                               0x000C
#define AFE_PMU_LVD_CTRL_OFFSET                                 0x0010
#define AFE_PMU_LDO35V_CTRL_OFFSET                              0x0014
#define AFE_PMU_POR_CTRL_OFFSET                                 0x0018
#define AFE_PMU_LDO15_CTRL_OFFSET                               0x001C
#define AFE_PMU_VS_PORB_CTRL_OFFSET                             0x0020
#define AFE_PMU_PMU_LOCK_OFFSET                                 0x00FC

// Register Address Macro Definition
#define AFE_PMU_SLEEP_MODE_ADDR                                 ( AFE_PMU_BASE_ADDR + AFE_PMU_SLEEP_MODE_OFFSET)
#define AFE_PMU_PMU_CTRL_ADDR                                   ( AFE_PMU_BASE_ADDR + AFE_PMU_PMU_CTRL_OFFSET)
#define AFE_PMU_WAIT_CYCLE_ADDR                                 ( AFE_PMU_BASE_ADDR + AFE_PMU_WAIT_CYCLE_OFFSET)
#define AFE_PMU_PMU_STATUS_ADDR                                 ( AFE_PMU_BASE_ADDR + AFE_PMU_PMU_STATUS_OFFSET)
#define AFE_PMU_LVD_CTRL_ADDR                                   ( AFE_PMU_BASE_ADDR + AFE_PMU_LVD_CTRL_OFFSET)
#define AFE_PMU_LDO35V_CTRL_ADDR                                ( AFE_PMU_BASE_ADDR + AFE_PMU_LDO35V_CTRL_OFFSET)
#define AFE_PMU_POR_CTRL_ADDR                                   ( AFE_PMU_BASE_ADDR + AFE_PMU_POR_CTRL_OFFSET)
#define AFE_PMU_LDO15_CTRL_ADDR                                 ( AFE_PMU_BASE_ADDR + AFE_PMU_LDO15_CTRL_OFFSET)
#define AFE_PMU_VS_PORB_CTRL_ADDR                               ( AFE_PMU_BASE_ADDR + AFE_PMU_VS_PORB_CTRL_OFFSET)
#define AFE_PMU_PMU_LOCK_ADDR                                   ( AFE_PMU_BASE_ADDR + AFE_PMU_PMU_LOCK_OFFSET)

// Register Field Macro Definition
#define AFE_PMU_SLEEP_MODE_SLP_MODE_SHIFT                                     0
#define AFE_PMU_SLEEP_MODE_SLP_MODE_MASK                                      0x00000003
#define AFE_PMU_SLEEP_MODE_SLP_MODE_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x00000003)
#define AFE_PMU_SLEEP_MODE_SLP_MODE_CLR                                       0xFFFFFFFC

#define AFE_PMU_PMU_CTRL_SW_SLWK_WKUP_SHIFT                                   8
#define AFE_PMU_PMU_CTRL_SW_SLWK_WKUP_MASK                                    0x00000100
#define AFE_PMU_PMU_CTRL_SW_SLWK_WKUP_SET(n)                                  (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PMU_PMU_CTRL_SW_SLWK_WKUP_CLR                                     0xFFFFFEFF

#define AFE_PMU_PMU_CTRL_SLWK_HRC_EN_SHIFT                                    4
#define AFE_PMU_PMU_CTRL_SLWK_HRC_EN_MASK                                     0x00000010
#define AFE_PMU_PMU_CTRL_SLWK_HRC_EN_SET(n)                                   (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PMU_PMU_CTRL_SLWK_HRC_EN_CLR                                      0xFFFFFFEF

#define AFE_PMU_PMU_CTRL_SW_SLP_REQ_SHIFT                                     0
#define AFE_PMU_PMU_CTRL_SW_SLP_REQ_MASK                                      0x00000001
#define AFE_PMU_PMU_CTRL_SW_SLP_REQ_SET(n)                                    (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PMU_PMU_CTRL_SW_SLP_REQ_CLR                                       0xFFFFFFFE

#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO15_HW_EN_DL_SHIFT                     16
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO15_HW_EN_DL_MASK                      0x003F0000
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO15_HW_EN_DL_SET(n)                    (((uint32_t)(n) << 16 ) & 0x003F0000)
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO15_HW_EN_DL_CLR                       0xFFC0FFFF

#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO35V_EN_RL_SHIFT                       12
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO35V_EN_RL_MASK                        0x00007000
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO35V_EN_RL_SET(n)                      (((uint32_t)(n) << 12 ) & 0x00007000)
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_LDO35V_EN_RL_CLR                         0xFFFF8FFF

#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_PSW15_SHIFT                              8
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_PSW15_MASK                               0x00000700
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_PSW15_SET(n)                             (((uint32_t)(n) << 8  ) & 0x00000700)
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_PSW15_CLR                                0xFFFFF8FF

#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_SHIFT                              0
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_MASK                               0x0000003F
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_SET(n)                             (((uint32_t)(n) << 0  ) & 0x0000003F)
#define AFE_PMU_WAIT_CYCLE_PUP_CYCLE_HFCLK_CLR                                0xFFFFFFC0

#define AFE_PMU_PMU_STATUS_PMU_STATE_SHIFT                                    0
#define AFE_PMU_PMU_STATUS_PMU_STATE_MASK                                     0x00000007
#define AFE_PMU_PMU_STATUS_PMU_STATE_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PMU_PMU_STATUS_PMU_STATE_CLR                                      0xFFFFFFF8

#define AFE_PMU_LVD_CTRL_HW_LVD_DIS_LED_EN_SHIFT                              12
#define AFE_PMU_LVD_CTRL_HW_LVD_DIS_LED_EN_MASK                               0x00001000
#define AFE_PMU_LVD_CTRL_HW_LVD_DIS_LED_EN_SET(n)                             (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_PMU_LVD_CTRL_HW_LVD_DIS_LED_EN_CLR                                0xFFFFEFFF

#define AFE_PMU_LVD_CTRL_VS_LVD_SHIFT                                         8
#define AFE_PMU_LVD_CTRL_VS_LVD_MASK                                          0x00000100
#define AFE_PMU_LVD_CTRL_VS_LVD_SET(n)                                        (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PMU_LVD_CTRL_VS_LVD_CLR                                           0xFFFFFEFF

#define AFE_PMU_LVD_CTRL_VS_LVD_SEL_SHIFT                                     4
#define AFE_PMU_LVD_CTRL_VS_LVD_SEL_MASK                                      0x00000070
#define AFE_PMU_LVD_CTRL_VS_LVD_SEL_SET(n)                                    (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PMU_LVD_CTRL_VS_LVD_SEL_CLR                                       0xFFFFFF8F

#define AFE_PMU_LVD_CTRL_VS_LVD_EN_SHIFT                                      0
#define AFE_PMU_LVD_CTRL_VS_LVD_EN_MASK                                       0x00000001
#define AFE_PMU_LVD_CTRL_VS_LVD_EN_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PMU_LVD_CTRL_VS_LVD_EN_CLR                                        0xFFFFFFFE

#define AFE_PMU_LDO35V_CTRL_LDO35V_RL_RDY_SHIFT                               4
#define AFE_PMU_LDO35V_CTRL_LDO35V_RL_RDY_MASK                                0x00000010
#define AFE_PMU_LDO35V_CTRL_LDO35V_RL_RDY_SET(n)                              (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PMU_LDO35V_CTRL_LDO35V_RL_RDY_CLR                                 0xFFFFFFEF

#define AFE_PMU_LDO35V_CTRL_LDO35V_SEL_RL_SHIFT                               0
#define AFE_PMU_LDO35V_CTRL_LDO35V_SEL_RL_MASK                                0x0000000F
#define AFE_PMU_LDO35V_CTRL_LDO35V_SEL_RL_SET(n)                              (((uint32_t)(n) << 0  ) & 0x0000000F)
#define AFE_PMU_LDO35V_CTRL_LDO35V_SEL_RL_CLR                                 0xFFFFFFF0

#define AFE_PMU_POR_CTRL_LDO15_PORB_FALLEDGE_SEL_SHIFT                        4
#define AFE_PMU_POR_CTRL_LDO15_PORB_FALLEDGE_SEL_MASK                         0x00000030
#define AFE_PMU_POR_CTRL_LDO15_PORB_FALLEDGE_SEL_SET(n)                       (((uint32_t)(n) << 4  ) & 0x00000030)
#define AFE_PMU_POR_CTRL_LDO15_PORB_FALLEDGE_SEL_CLR                          0xFFFFFFCF

#define AFE_PMU_POR_CTRL_VDD4_PORB_FALLEDGE_SEL_SHIFT                         0
#define AFE_PMU_POR_CTRL_VDD4_PORB_FALLEDGE_SEL_MASK                          0x00000003
#define AFE_PMU_POR_CTRL_VDD4_PORB_FALLEDGE_SEL_SET(n)                        (((uint32_t)(n) << 0  ) & 0x00000003)
#define AFE_PMU_POR_CTRL_VDD4_PORB_FALLEDGE_SEL_CLR                           0xFFFFFFFC

#define AFE_PMU_LDO15_CTRL_LDO15_DL_IBASE_SEL_SHIFT                           4
#define AFE_PMU_LDO15_CTRL_LDO15_DL_IBASE_SEL_MASK                            0x00000070
#define AFE_PMU_LDO15_CTRL_LDO15_DL_IBASE_SEL_SET(n)                          (((uint32_t)(n) << 4  ) & 0x00000070)
#define AFE_PMU_LDO15_CTRL_LDO15_DL_IBASE_SEL_CLR                             0xFFFFFF8F

#define AFE_PMU_LDO15_CTRL_LDO15_SW_ENB_DL_SHIFT                              0
#define AFE_PMU_LDO15_CTRL_LDO15_SW_ENB_DL_MASK                               0x00000001
#define AFE_PMU_LDO15_CTRL_LDO15_SW_ENB_DL_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PMU_LDO15_CTRL_LDO15_SW_ENB_DL_CLR                                0xFFFFFFFE

#define AFE_PMU_VS_PORB_CTRL_VS_PORB_FOREWARN_SHIFT                           8
#define AFE_PMU_VS_PORB_CTRL_VS_PORB_FOREWARN_MASK                            0x00000100
#define AFE_PMU_VS_PORB_CTRL_VS_PORB_FOREWARN_SET(n)                          (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_PMU_VS_PORB_CTRL_VS_PORB_FOREWARN_CLR                             0xFFFFFEFF

#define AFE_PMU_VS_PORB_CTRL_HW_VS_PORB_DIS_LED_EN_SHIFT                      4
#define AFE_PMU_VS_PORB_CTRL_HW_VS_PORB_DIS_LED_EN_MASK                       0x00000010
#define AFE_PMU_VS_PORB_CTRL_HW_VS_PORB_DIS_LED_EN_SET(n)                     (((uint32_t)(n) << 4  ) & 0x00000010)
#define AFE_PMU_VS_PORB_CTRL_HW_VS_PORB_DIS_LED_EN_CLR                        0xFFFFFFEF

#define AFE_PMU_VS_PORB_CTRL_VS_PORB_SEL_SHIFT                                0
#define AFE_PMU_VS_PORB_CTRL_VS_PORB_SEL_MASK                                 0x00000007
#define AFE_PMU_VS_PORB_CTRL_VS_PORB_SEL_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_PMU_VS_PORB_CTRL_VS_PORB_SEL_CLR                                  0xFFFFFFF8

#define AFE_PMU_PMU_LOCK_PMU_LOCK_SHIFT                                       0
#define AFE_PMU_PMU_LOCK_PMU_LOCK_MASK                                        0x00000001
#define AFE_PMU_PMU_LOCK_PMU_LOCK_SET(n)                                      (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_PMU_PMU_LOCK_PMU_LOCK_CLR                                         0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t SLP_MODE                 : 2  ; // 1  : 0
    __IO uint32_t RESERVED0                : 30 ; // 31 : 2
} AFE_PMU_SLEEP_MODE_FIELD_T;

typedef struct
{
    __IO uint32_t SW_SLP_REQ               : 1  ; // 0  : 0
    __IO uint32_t RESERVED2                : 3  ; // 3  : 1
    __IO uint32_t SLWK_HRC_EN              : 1  ; // 4  : 4
    __IO uint32_t RESERVED1                : 3  ; // 7  : 5
    __IO uint32_t SW_SLWK_WKUP             : 1  ; // 8  : 8
    __IO uint32_t RESERVED0                : 23 ; // 31 : 9
} AFE_PMU_PMU_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t PUP_CYCLE_HFCLK          : 6  ; // 5  : 0
    __IO uint32_t RESERVED3                : 2  ; // 7  : 6
    __IO uint32_t PUP_CYCLE_PSW15          : 3  ; // 10 : 8
    __IO uint32_t RESERVED2                : 1  ; // 11 : 11
    __IO uint32_t PUP_CYCLE_LDO35V_EN_RL   : 3  ; // 14 : 12
    __IO uint32_t RESERVED1                : 1  ; // 15 : 15
    __IO uint32_t PUP_CYCLE_LDO15_HW_EN_DL : 6  ; // 21 : 16
    __IO uint32_t RESERVED0                : 10 ; // 31 : 22
} AFE_PMU_WAIT_CYCLE_FIELD_T;

typedef struct
{
    __IO uint32_t PMU_STATE                : 3  ; // 2  : 0
    __IO uint32_t RESERVED0                : 29 ; // 31 : 3
} AFE_PMU_PMU_STATUS_FIELD_T;

typedef struct
{
    __IO uint32_t VS_LVD_EN                : 1  ; // 0  : 0
    __IO uint32_t RESERVED3                : 3  ; // 3  : 1
    __IO uint32_t VS_LVD_SEL               : 3  ; // 6  : 4
    __IO uint32_t RESERVED2                : 1  ; // 7  : 7
    __IO uint32_t VS_LVD                   : 1  ; // 8  : 8
    __IO uint32_t RESERVED1                : 3  ; // 11 : 9
    __IO uint32_t HW_LVD_DIS_LED_EN        : 1  ; // 12 : 12
    __IO uint32_t RESERVED0                : 19 ; // 31 : 13
} AFE_PMU_LVD_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LDO35V_SEL_RL            : 4  ; // 3  : 0
    __IO uint32_t LDO35V_RL_RDY            : 1  ; // 4  : 4
    __IO uint32_t RESERVED0                : 27 ; // 31 : 5
} AFE_PMU_LDO35V_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t VDD4_PORB_FALLEDGE_SEL   : 2  ; // 1  : 0
    __IO uint32_t RESERVED1                : 2  ; // 3  : 2
    __IO uint32_t LDO15_PORB_FALLEDGE_SEL  : 2  ; // 5  : 4
    __IO uint32_t RESERVED0                : 26 ; // 31 : 6
} AFE_PMU_POR_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t LDO15_SW_ENB_DL          : 1  ; // 0  : 0
    __IO uint32_t RESERVED1                : 3  ; // 3  : 1
    __IO uint32_t LDO15_DL_IBASE_SEL       : 3  ; // 6  : 4
    __IO uint32_t RESERVED0                : 25 ; // 31 : 7
} AFE_PMU_LDO15_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t VS_PORB_SEL              : 3  ; // 2  : 0
    __IO uint32_t RESERVED2                : 1  ; // 3  : 3
    __IO uint32_t HW_VS_PORB_DIS_LED_EN    : 1  ; // 4  : 4
    __IO uint32_t RESERVED1                : 3  ; // 7  : 5
    __IO uint32_t VS_PORB_FOREWARN         : 1  ; // 8  : 8
    __IO uint32_t RESERVED0                : 23 ; // 31 : 9
} AFE_PMU_VS_PORB_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t PMU_LOCK                 : 1  ; // 0  : 0
    __IO uint32_t RESERVED0                : 31 ; // 31 : 1
} AFE_PMU_PMU_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t SLEEPMODE                   ; // 0x0000
        AFE_PMU_SLEEP_MODE_FIELD_T SLEEP_MODE_F    ;
    };

    union
    {
        __IO  uint32_t PMU_CTRL                    ; // 0x0004
        AFE_PMU_PMU_CTRL_FIELD_T PMU_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t WAIT_CYCLE                  ; // 0x0008
        AFE_PMU_WAIT_CYCLE_FIELD_T WAIT_CYCLE_F    ;
    };

    union
    {
        __IO  uint32_t PMU_STATUS                  ; // 0x000C
        AFE_PMU_PMU_STATUS_FIELD_T PMU_STATUS_F    ;
    };

    union
    {
        __IO  uint32_t LVD_CTRL                    ; // 0x0010
        AFE_PMU_LVD_CTRL_FIELD_T LVD_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t LDO35V_CTRL                 ; // 0x0014
        AFE_PMU_LDO35V_CTRL_FIELD_T LDO35V_CTRL_F  ;
    };

    union
    {
        __IO  uint32_t POR_CTRL                    ; // 0x0018
        AFE_PMU_POR_CTRL_FIELD_T POR_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t LDO15_CTRL                  ; // 0x001C
        AFE_PMU_LDO15_CTRL_FIELD_T LDO15_CTRL_F    ;
    };

    union
    {
        __IO  uint32_t VS_PORB_CTRL                ; // 0x0020
        AFE_PMU_VS_PORB_CTRL_FIELD_T VS_PORB_CTRL_F;
    };

    uint32_t RESERVED0[54]                          ;

    union
    {
        __IO  uint32_t PMU_LOCK                    ; // 0x00FC
        AFE_PMU_PMU_LOCK_FIELD_T PMU_LOCK_F        ;
    };

} AFE_PMU_REG_TypeDef;

#endif
