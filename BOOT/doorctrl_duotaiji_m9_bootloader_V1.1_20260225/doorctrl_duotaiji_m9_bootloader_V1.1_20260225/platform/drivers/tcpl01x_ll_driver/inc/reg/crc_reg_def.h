/**
 *****************************************************************************
 * @brief   crc_reg_def header file.
 *
 * @file    crc_reg_def.h
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

#ifndef   CRC_DEF_H__
#define   CRC_DEF_H__

// Register Offset Macro Definition
#define CRC_CRC_DIN_OFFSET                                      0x0000
#define CRC_CRC_RESULT_OFFSET                                   0x0004
#define CRC_CTRL_OFFSET                                         0x0008
#define CRC_CRC_INIT_VALUE_OFFSET                               0x000C
#define CRC_CRC_POLY_OFFSET                                     0x0010
#define CRC_CRC_VLDBIT_OFFSET                                   0x0014
#define CRC_STATUS_OFFSET                                       0x0018

// Register Address Macro Definition
#define CRC_CRC_DIN_ADDR                                        ( CRC_BASE_ADDR + CRC_CRC_DIN_OFFSET)
#define CRC_CRC_RESULT_ADDR                                     ( CRC_BASE_ADDR + CRC_CRC_RESULT_OFFSET)
#define CRC_CTRL_ADDR                                           ( CRC_BASE_ADDR + CRC_CTRL_OFFSET)
#define CRC_CRC_INIT_VALUE_ADDR                                 ( CRC_BASE_ADDR + CRC_CRC_INIT_VALUE_OFFSET)
#define CRC_CRC_POLY_ADDR                                       ( CRC_BASE_ADDR + CRC_CRC_POLY_OFFSET)
#define CRC_CRC_VLDBIT_ADDR                                     ( CRC_BASE_ADDR + CRC_CRC_VLDBIT_OFFSET)
#define CRC_STATUS_ADDR                                         ( CRC_BASE_ADDR + CRC_STATUS_OFFSET)

// Register Field Macro Definition
#define CRC_CRC_DIN_CRC_DIN_SHIFT                                  0
#define CRC_CRC_DIN_CRC_DIN_MASK                                   0xFFFFFFFF
#define CRC_CRC_DIN_CRC_DIN_SET(n)                                 (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define CRC_CRC_DIN_CRC_DIN_CLR                                    0x00000000

#define CRC_CRC_RESULT_CRC_RESULT_SHIFT                            0
#define CRC_CRC_RESULT_CRC_RESULT_MASK                             0xFFFFFFFF
#define CRC_CRC_RESULT_CRC_RESULT_SET(n)                           (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define CRC_CRC_RESULT_CRC_RESULT_CLR                              0x00000000

#define CRC_CTRL_REV_IN_SHIFT                                      12
#define CRC_CTRL_REV_IN_MASK                                       0x00003000
#define CRC_CTRL_REV_IN_SET(n)                                     (((uint32_t)(n) << 12 ) & 0x00003000)
#define CRC_CTRL_REV_IN_CLR                                        0xFFFFCFFF

#define CRC_CTRL_REV_OUT_SHIFT                                     8
#define CRC_CTRL_REV_OUT_MASK                                      0x00000100
#define CRC_CTRL_REV_OUT_SET(n)                                    (((uint32_t)(n) << 8  ) & 0x00000100)
#define CRC_CTRL_REV_OUT_CLR                                       0xFFFFFEFF

#define CRC_CTRL_CRC_MODE_SHIFT                                    4
#define CRC_CTRL_CRC_MODE_MASK                                     0x00000030
#define CRC_CTRL_CRC_MODE_SET(n)                                   (((uint32_t)(n) << 4  ) & 0x00000030)
#define CRC_CTRL_CRC_MODE_CLR                                      0xFFFFFFCF

#define CRC_CTRL_INIT_SHIFT                                        1
#define CRC_CTRL_INIT_MASK                                         0x00000002
#define CRC_CTRL_INIT_SET(n)                                       (((uint32_t)(n) << 1  ) & 0x00000002)
#define CRC_CTRL_INIT_CLR                                          0xFFFFFFFD

#define CRC_CTRL_EN_SHIFT                                          0
#define CRC_CTRL_EN_MASK                                           0x00000001
#define CRC_CTRL_EN_SET(n)                                         (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRC_CTRL_EN_CLR                                            0xFFFFFFFE

#define CRC_CRC_INIT_VALUE_CRC_INIT_VALUE_SHIFT                    0
#define CRC_CRC_INIT_VALUE_CRC_INIT_VALUE_MASK                     0xFFFFFFFF
#define CRC_CRC_INIT_VALUE_CRC_INIT_VALUE_SET(n)                   (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define CRC_CRC_INIT_VALUE_CRC_INIT_VALUE_CLR                      0x00000000

#define CRC_CRC_POLY_CRC_POLY_SHIFT                                0
#define CRC_CRC_POLY_CRC_POLY_MASK                                 0xFFFFFFFF
#define CRC_CRC_POLY_CRC_POLY_SET(n)                               (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define CRC_CRC_POLY_CRC_POLY_CLR                                  0x00000000

#define CRC_CRC_VLDBIT_CRC_VLDBIT_SHIFT                            0
#define CRC_CRC_VLDBIT_CRC_VLDBIT_MASK                             0xFFFFFFFF
#define CRC_CRC_VLDBIT_CRC_VLDBIT_SET(n)                           (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define CRC_CRC_VLDBIT_CRC_VLDBIT_CLR                              0x00000000

#define CRC_STATUS_CRC_BUSY_SHIFT                                  0
#define CRC_STATUS_CRC_BUSY_MASK                                   0x00000001
#define CRC_STATUS_CRC_BUSY_SET(n)                                 (((uint32_t)(n) << 0  ) & 0x00000001)
#define CRC_STATUS_CRC_BUSY_CLR                                    0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t CRC_DIN         : 32 ; // 31 : 0
} CRC_CRC_DIN_FIELD_T;

typedef struct
{
    __IO uint32_t CRC_RESULT      : 32 ; // 31 : 0
} CRC_CRC_RESULT_FIELD_T;

typedef struct
{
    __IO uint32_t EN              : 1  ; // 0  : 0
    __IO uint32_t INIT            : 1  ; // 1  : 1
    __IO uint32_t RESERVED3       : 2  ; // 3  : 2
    __IO uint32_t CRC_MODE        : 2  ; // 5  : 4
    __IO uint32_t RESERVED2       : 2  ; // 7  : 6
    __IO uint32_t REV_OUT         : 1  ; // 8  : 8
    __IO uint32_t RESERVED1       : 3  ; // 11 : 9
    __IO uint32_t REV_IN          : 2  ; // 13 : 12
    __IO uint32_t RESERVED0       : 18 ; // 31 : 14
} CRC_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t CRC_INIT_VALUE  : 32 ; // 31 : 0
} CRC_CRC_INIT_VALUE_FIELD_T;

typedef struct
{
    __IO uint32_t CRC_POLY        : 32 ; // 31 : 0
} CRC_CRC_POLY_FIELD_T;

typedef struct
{
    __IO uint32_t CRC_VLDBIT      : 32 ; // 31 : 0
} CRC_CRC_VLDBIT_FIELD_T;

typedef struct
{
    __IO uint32_t CRC_BUSY        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0       : 31 ; // 31 : 1
} CRC_STATUS_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t CRC_DIN                         ; // 0x0000
        CRC_CRC_DIN_FIELD_T CRC_DIN_F                  ;
    };

    union
    {
        __IO  uint32_t CRC_RESULT                      ; // 0x0004
        CRC_CRC_RESULT_FIELD_T CRC_RESULT_F            ;
    };

    union
    {
        __IO  uint32_t CTRL                            ; // 0x0008
        CRC_CTRL_FIELD_T CTRL_F                        ;
    };

    union
    {
        __IO  uint32_t CRC_INIT_VALUE                  ; // 0x000C
        CRC_CRC_INIT_VALUE_FIELD_T CRC_INIT_VALUE_F    ;
    };

    union
    {
        __IO  uint32_t CRC_POLY                        ; // 0x0010
        CRC_CRC_POLY_FIELD_T CRC_POLY_F                ;
    };

    union
    {
        __IO  uint32_t CRC_VLDBIT                      ; // 0x0014
        CRC_CRC_VLDBIT_FIELD_T CRC_VLDBIT_F            ;
    };

    union
    {
        __IO  uint32_t STATUS                          ; // 0x0018
        CRC_STATUS_FIELD_T STATUS_F                    ;
    };

} CRC_REG_TypeDef;

#endif
