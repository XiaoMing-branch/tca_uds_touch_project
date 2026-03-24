/**
 *****************************************************************************
 * @brief   adc_com_reg_def header file.
 *
 * @file    adc_com_reg_def.h
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

#ifndef   AFE_COM_DEF_H__
#define   AFE_COM_DEF_H__

// Register Offset Macro Definition
#define AFE_COM_ADDR_OFFSET                                     0x0000
#define AFE_COM_WDATA_OFFSET                                    0x0004
#define AFE_COM_RDATA_OFFSET                                    0x0008
#define AFE_COM_CTRL_OFFSET                                     0x000C
#define AFE_COM_IMR_OFFSET                                      0x0010
#define AFE_COM_ICR_OFFSET                                      0x0014
#define AFE_COM_IRSR_OFFSET                                     0x0018
#define AFE_COM_ISR_OFFSET                                      0x001C

// Register Address Macro Definition
#define AFE_COM_ADDR_ADDR                                       ( AFE_COM_BASE_ADDR + AFE_COM_ADDR_OFFSET)
#define AFE_COM_WDATA_ADDR                                      ( AFE_COM_BASE_ADDR + AFE_COM_WDATA_OFFSET)
#define AFE_COM_RDATA_ADDR                                      ( AFE_COM_BASE_ADDR + AFE_COM_RDATA_OFFSET)
#define AFE_COM_CTRL_ADDR                                       ( AFE_COM_BASE_ADDR + AFE_COM_CTRL_OFFSET)
#define AFE_COM_IMR_ADDR                                        ( AFE_COM_BASE_ADDR + AFE_COM_IMR_OFFSET)
#define AFE_COM_ICR_ADDR                                        ( AFE_COM_BASE_ADDR + AFE_COM_ICR_OFFSET)
#define AFE_COM_IRSR_ADDR                                       ( AFE_COM_BASE_ADDR + AFE_COM_IRSR_OFFSET)
#define AFE_COM_ISR_ADDR                                        ( AFE_COM_BASE_ADDR + AFE_COM_ISR_OFFSET)

// Register Field Macro Definition
#define AFE_COM_ADDR_CRC_EN_SHIFT                             16
#define AFE_COM_ADDR_CRC_EN_MASK                              0x00010000
#define AFE_COM_ADDR_CRC_EN_SET(n)                            (((uint32_t)(n) << 16 ) & 0x00010000)
#define AFE_COM_ADDR_CRC_EN_CLR                               0xFFFEFFFF

#define AFE_COM_ADDR_BUSY_SHIFT                               12
#define AFE_COM_ADDR_BUSY_MASK                                0x00001000
#define AFE_COM_ADDR_BUSY_SET(n)                              (((uint32_t)(n) << 12 ) & 0x00001000)
#define AFE_COM_ADDR_BUSY_CLR                                 0xFFFFEFFF

#define AFE_COM_ADDR_COM_ADDR_SHIFT                           0
#define AFE_COM_ADDR_COM_ADDR_MASK                            0x00000FFF
#define AFE_COM_ADDR_COM_ADDR_SET(n)                          (((uint32_t)(n) << 0  ) & 0x00000FFF)
#define AFE_COM_ADDR_COM_ADDR_CLR                             0xFFFFF000

#define AFE_COM_WDATA_COM_WDATA_SHIFT                         0
#define AFE_COM_WDATA_COM_WDATA_MASK                          0xFFFFFFFF
#define AFE_COM_WDATA_COM_WDATA_SET(n)                        (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define AFE_COM_WDATA_COM_WDATA_CLR                           0x00000000

#define AFE_COM_RDATA_COM_RDATA_SHIFT                         0
#define AFE_COM_RDATA_COM_RDATA_MASK                          0xFFFFFFFF
#define AFE_COM_RDATA_COM_RDATA_SET(n)                        (((uint32_t)(n) << 0  ) & 0xFFFFFFFF)
#define AFE_COM_RDATA_COM_RDATA_CLR                           0x00000000

#define AFE_COM_CTRL_CLK_DIV_SHIFT                            0
#define AFE_COM_CTRL_CLK_DIV_MASK                             0x00000003
#define AFE_COM_CTRL_CLK_DIV_SET(n)                           (((uint32_t)(n) << 0  ) & 0x00000003)
#define AFE_COM_CTRL_CLK_DIV_CLR                              0xFFFFFFFC

#define AFE_COM_IMR_IMR_SHIFT                                 0
#define AFE_COM_IMR_IMR_MASK                                  0x00000007
#define AFE_COM_IMR_IMR_SET(n)                                (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_COM_IMR_IMR_CLR                                   0xFFFFFFF8

#define AFE_COM_ICR_ICR_SHIFT                                 0
#define AFE_COM_ICR_ICR_MASK                                  0x00000007
#define AFE_COM_ICR_ICR_SET(n)                                (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_COM_ICR_ICR_CLR                                   0xFFFFFFF8

#define AFE_COM_IRSR_IRSR_SHIFT                               0
#define AFE_COM_IRSR_IRSR_MASK                                0x00000007
#define AFE_COM_IRSR_IRSR_SET(n)                              (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_COM_IRSR_IRSR_CLR                                 0xFFFFFFF8

#define AFE_COM_ISR_ISR_SHIFT                                 0
#define AFE_COM_ISR_ISR_MASK                                  0x00000007
#define AFE_COM_ISR_ISR_SET(n)                                (((uint32_t)(n) << 0  ) & 0x00000007)
#define AFE_COM_ISR_ISR_CLR                                   0xFFFFFFF8

// Register Structure Definition
typedef struct
{
    __IO uint32_t COM_ADDR        : 12 ; // 11 : 0
    __IO uint32_t BUSY            : 1  ; // 12 : 12
    __IO uint32_t RESERVED1       : 3  ; // 15 : 13
    __IO uint32_t CRC_EN          : 1  ; // 16 : 16
    __IO uint32_t RESERVED0       : 15 ; // 31 : 17
} AFE_COM_ADDR_FIELD_T;

typedef struct
{
    __IO uint32_t COM_WDATA       : 32 ; // 31 : 0
} AFE_COM_WDATA_FIELD_T;

typedef struct
{
    __IO uint32_t COM_RDATA       : 32 ; // 31 : 0
} AFE_COM_RDATA_FIELD_T;

typedef struct
{
    __IO uint32_t CLK_DIV         : 2  ; // 1  : 0
    __IO uint32_t RESERVED0       : 19 ; // 31 : 13
} AFE_COM_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t IMR             : 3  ; // 2  : 0
    __IO uint32_t RESERVED0       : 29 ; // 31 : 3
} AFE_COM_IMR_FIELD_T;

typedef struct
{
    __IO uint32_t ICR             : 3  ; // 2  : 0
    __IO uint32_t RESERVED0       : 29 ; // 31 : 3
} AFE_COM_ICR_FIELD_T;

typedef struct
{
    __IO uint32_t IRSR            : 3  ; // 2  : 0
    __IO uint32_t RESERVED0       : 29 ; // 31 : 3
} AFE_COM_IRSR_FIELD_T;

typedef struct
{
    __IO uint32_t ISR             : 3  ; // 2  : 0
    __IO uint32_t RESERVED0       : 29 ; // 31 : 3
} AFE_COM_ISR_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t ADDR          ; // 0x0000
        AFE_COM_ADDR_FIELD_T ADDR_F  ;
    };

    union
    {
        __IO  uint32_t WDATA         ; // 0x0004
        AFE_COM_WDATA_FIELD_T WDATA_F;
    };

    union
    {
        __IO  uint32_t RDATA         ; // 0x0008
        AFE_COM_RDATA_FIELD_T RDATA_F;
    };

    union
    {
        __IO  uint32_t CTRL          ; // 0x000C
        AFE_COM_CTRL_FIELD_T CTRL_F  ;
    };

    union
    {
        __IO  uint32_t IMR           ; // 0x0010
        AFE_COM_IMR_FIELD_T IMR_F    ;
    };

    union
    {
        __IO  uint32_t ICR           ; // 0x0014
        AFE_COM_ICR_FIELD_T ICR_F    ;
    };

    union
    {
        __IO  uint32_t IRSR          ; // 0x0018
        AFE_COM_IRSR_FIELD_T IRSR_F  ;
    };

    union
    {
        __IO  uint32_t ISR           ; // 0x001C
        AFE_COM_ISR_FIELD_T ISR_F    ;
    };

} AFE_COM_REG_TypeDef;

#endif
