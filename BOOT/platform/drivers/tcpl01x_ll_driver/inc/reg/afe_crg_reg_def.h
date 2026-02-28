/**
 *****************************************************************************
 * @brief   adc_crg_reg_def header file.
 *
 * @file    adc_crg_reg_def.h
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

#ifndef   AFE_CRG_DEF_H__
#define   AFE_CRG_DEF_H__

// Register Offset Macro Definition
#define AFE_CRG_RTC_CLKRST_CTRL_OFFSET                          0x0000
#define AFE_CRG_ADC_CLKRST_CTRL_OFFSET                          0x0004
#define AFE_CRG_PWM_CLKRST_CTRL_OFFSET                          0x0008
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_OFFSET                      0x000C
#define AFE_CRG_GPIO_CLKRST_CTRL_OFFSET                         0x0010
#define AFE_CRG_PINMUX_CLKRST_CTRL_OFFSET                       0x0014
#define AFE_CRG_RCCLK_CTRL_OFFSET                               0x0018
#define AFE_CRG_OTP_RST_CTRL_OFFSET                             0x001C
#define AFE_CRG_RST_CTRL_OFFSET                                 0x0020
#define AFE_CRG_CRG_LOCK_OFFSET                                 0x00FC

// Register Address Macro Definition
#define AFE_CRG_RTC_CLKRST_CTRL_ADDR                            ( AFE_CRG_BASE_ADDR + AFE_CRG_RTC_CLKRST_CTRL_OFFSET)
#define AFE_CRG_ADC_CLKRST_CTRL_ADDR                            ( AFE_CRG_BASE_ADDR + AFE_CRG_ADC_CLKRST_CTRL_OFFSET)
#define AFE_CRG_PWM_CLKRST_CTRL_ADDR                            ( AFE_CRG_BASE_ADDR + AFE_CRG_PWM_CLKRST_CTRL_OFFSET)
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_ADDR                        ( AFE_CRG_BASE_ADDR + AFE_CRG_LIN_SCI_CLKRST_CTRL_OFFSET)
#define AFE_CRG_GPIO_CLKRST_CTRL_ADDR                           ( AFE_CRG_BASE_ADDR + AFE_CRG_GPIO_CLKRST_CTRL_OFFSET)
#define AFE_CRG_PINMUX_CLKRST_CTRL_ADDR                         ( AFE_CRG_BASE_ADDR + AFE_CRG_PINMUX_CLKRST_CTRL_OFFSET)
#define AFE_CRG_RCCLK_CTRL_ADDR                                 ( AFE_CRG_BASE_ADDR + AFE_CRG_RCCLK_CTRL_OFFSET)
#define AFE_CRG_OTP_RST_CTRL_ADDR                               ( AFE_CRG_BASE_ADDR + AFE_CRG_OTP_RST_CTRL_OFFSET)
#define AFE_CRG_RST_CTRL_ADDR                                   ( AFE_CRG_BASE_ADDR + AFE_CRG_RST_CTRL_OFFSET)
#define AFE_CRG_CRG_LOCK_ADDR                                   ( AFE_CRG_BASE_ADDR + AFE_CRG_CRG_LOCK_OFFSET)

// Register Field Macro Definition
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_DIV_RTC_SHIFT                           4
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_DIV_RTC_MASK                            0x000000F0
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_DIV_RTC_SET(n)                          (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_DIV_RTC_CLR                             0xFFFFFF0F

#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_EN_RTC_SHIFT                            2
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_EN_RTC_MASK                             0x00000004
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_EN_RTC_SET(n)                           (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_CRG_RTC_CLKRST_CTRL_FCLK_EN_RTC_CLR                              0xFFFFFFFB

#define AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_SHIFT                                0
#define AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_MASK                                 0x00000001
#define AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_CLR                                  0xFFFFFFFE

#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_DIV_ADC_SHIFT                           4
#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_DIV_ADC_MASK                            0x000000F0
#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_DIV_ADC_SET(n)                          (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_DIV_ADC_CLR                             0xFFFFFF0F

#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_EN_ADC_SHIFT                            2
#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_EN_ADC_MASK                             0x00000004
#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_EN_ADC_SET(n)                           (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_CRG_ADC_CLKRST_CTRL_FCLK_EN_ADC_CLR                              0xFFFFFFFB

#define AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_SHIFT                                0
#define AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_MASK                                 0x00000001
#define AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_ADC_CLKRST_CTRL_RST_ADC_CLR                                  0xFFFFFFFE

#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_DIV_PWM_SHIFT                           4
#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_DIV_PWM_MASK                            0x000000F0
#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_DIV_PWM_SET(n)                          (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_DIV_PWM_CLR                             0xFFFFFF0F

#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_EN_PWM_SHIFT                            2
#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_EN_PWM_MASK                             0x00000004
#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_EN_PWM_SET(n)                           (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_CRG_PWM_CLKRST_CTRL_FCLK_EN_PWM_CLR                              0xFFFFFFFB

#define AFE_CRG_PWM_CLKRST_CTRL_RST_PWM_SHIFT                                0
#define AFE_CRG_PWM_CLKRST_CTRL_RST_PWM_MASK                                 0x00000001
#define AFE_CRG_PWM_CLKRST_CTRL_RST_PWM_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_PWM_CLKRST_CTRL_RST_PWM_CLR                                  0xFFFFFFFE

#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_SHIFT                   4
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_MASK                    0x000000F0
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_SET(n)                  (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_CLR                     0xFFFFFF0F

#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_SEL_LIN_SCI_SHIFT                   3
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_SEL_LIN_SCI_MASK                    0x00000008
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_SEL_LIN_SCI_SET(n)                  (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_SEL_LIN_SCI_CLR                     0xFFFFFFF7

#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_EN_LIN_SCI_SHIFT                    2
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_EN_LIN_SCI_MASK                     0x00000004
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_EN_LIN_SCI_SET(n)                   (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_EN_LIN_SCI_CLR                      0xFFFFFFFB

#define AFE_CRG_LIN_SCI_CLKRST_CTRL_RST_LIN_SCI_SHIFT                        0
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_RST_LIN_SCI_MASK                         0x00000001
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_RST_LIN_SCI_SET(n)                       (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_LIN_SCI_CLKRST_CTRL_RST_LIN_SCI_CLR                          0xFFFFFFFE

#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_DIV_GPIO_SHIFT                         4
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_DIV_GPIO_MASK                          0x000000F0
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_DIV_GPIO_SET(n)                        (((uint32_t)(n) << 4  ) & 0x000000F0)
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_DIV_GPIO_CLR                           0xFFFFFF0F

#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_SEL_GPIO_SHIFT                         3
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_SEL_GPIO_MASK                          0x00000008
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_SEL_GPIO_SET(n)                        (((uint32_t)(n) << 3  ) & 0x00000008)
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_SEL_GPIO_CLR                           0xFFFFFFF7

#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_EN_GPIO_SHIFT                          2
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_EN_GPIO_MASK                           0x00000004
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_EN_GPIO_SET(n)                         (((uint32_t)(n) << 2  ) & 0x00000004)
#define AFE_CRG_GPIO_CLKRST_CTRL_FCLK_EN_GPIO_CLR                            0xFFFFFFFB

#define AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT                              0
#define AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_MASK                               0x00000001
#define AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SET(n)                             (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_CLR                                0xFFFFFFFE

#define AFE_CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_SHIFT                          0
#define AFE_CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_MASK                           0x00000001
#define AFE_CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_SET(n)                         (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_PINMUX_CLKRST_CTRL_RST_PINMUX_CLR                            0xFFFFFFFE

#define AFE_CRG_RCCLK_CTRL_HRC_READY_SHIFT                                   1
#define AFE_CRG_RCCLK_CTRL_HRC_READY_MASK                                    0x00000002
#define AFE_CRG_RCCLK_CTRL_HRC_READY_SET(n)                                  (((uint32_t)(n) << 1  ) & 0x00000002)
#define AFE_CRG_RCCLK_CTRL_HRC_READY_CLR                                     0xFFFFFFFD

#define AFE_CRG_RCCLK_CTRL_SW_HRC_EN_SHIFT                                   0
#define AFE_CRG_RCCLK_CTRL_SW_HRC_EN_MASK                                    0x00000001
#define AFE_CRG_RCCLK_CTRL_SW_HRC_EN_SET(n)                                  (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_RCCLK_CTRL_SW_HRC_EN_CLR                                     0xFFFFFFFE

#define AFE_CRG_OTP_RST_CTRL_OTP_RST_EN_SHIFT                                0
#define AFE_CRG_OTP_RST_CTRL_OTP_RST_EN_MASK                                 0x00000001
#define AFE_CRG_OTP_RST_CTRL_OTP_RST_EN_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_OTP_RST_CTRL_OTP_RST_EN_CLR                                  0xFFFFFFFE

#define AFE_CRG_RST_CTRL_SW_POR_REQ_SHIFT                                    8
#define AFE_CRG_RST_CTRL_SW_POR_REQ_MASK                                     0x00000100
#define AFE_CRG_RST_CTRL_SW_POR_REQ_SET(n)                                   (((uint32_t)(n) << 8  ) & 0x00000100)
#define AFE_CRG_RST_CTRL_SW_POR_REQ_CLR                                      0xFFFFFEFF

#define AFE_CRG_RST_CTRL_CLR_RST_SHIFT                                       5
#define AFE_CRG_RST_CTRL_CLR_RST_MASK                                        0x00000020
#define AFE_CRG_RST_CTRL_CLR_RST_SET(n)                                      (((uint32_t)(n) << 5  ) & 0x00000020)
#define AFE_CRG_RST_CTRL_CLR_RST_CLR                                         0xFFFFFFDF

#define AFE_CRG_RST_CTRL_RST_FLAG_SHIFT                                      0
#define AFE_CRG_RST_CTRL_RST_FLAG_MASK                                       0x0000000F
#define AFE_CRG_RST_CTRL_RST_FLAG_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x0000000F)
#define AFE_CRG_RST_CTRL_RST_FLAG_CLR                                        0xFFFFFFF0

#define AFE_CRG_CRG_LOCK_CRG_LOCK_SHIFT                                      0
#define AFE_CRG_CRG_LOCK_CRG_LOCK_MASK                                       0x00000001
#define AFE_CRG_CRG_LOCK_CRG_LOCK_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x00000001)
#define AFE_CRG_CRG_LOCK_CRG_LOCK_CLR                                        0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t RST_RTC          : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_RTC      : 1  ; // 2  : 2
    __IO uint32_t RESERVED1        : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_RTC     : 4  ; // 7  : 4
    __IO uint32_t RESERVED0        : 24 ; // 31 : 8
} AFE_CRG_RTC_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_ADC          : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_ADC      : 1  ; // 2  : 2
    __IO uint32_t RESERVED1        : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_ADC     : 4  ; // 7  : 4
    __IO uint32_t RESERVED0        : 24 ; // 31 : 8
} AFE_CRG_ADC_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_PWM          : 1  ; // 0  : 0
    __IO uint32_t RESERVED2        : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_PWM      : 1  ; // 2  : 2
    __IO uint32_t RESERVED1        : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_PWM     : 4  ; // 7  : 4
    __IO uint32_t RESERVED0        : 24 ; // 31 : 8
} AFE_CRG_PWM_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_LIN_SCI      : 1  ; // 0  : 0
    __IO uint32_t RESERVED1        : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_LIN_SCI  : 1  ; // 2  : 2
    __IO uint32_t FCLK_SEL_LIN_SCI : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_LIN_SCI : 4  ; // 7  : 4
    __IO uint32_t RESERVED0        : 24 ; // 31 : 8
} AFE_CRG_LIN_SCI_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_GPIO         : 1  ; // 0  : 0
    __IO uint32_t RESERVED1        : 1  ; // 1  : 1
    __IO uint32_t FCLK_EN_GPIO     : 1  ; // 2  : 2
    __IO uint32_t FCLK_SEL_GPIO    : 1  ; // 3  : 3
    __IO uint32_t FCLK_DIV_GPIO    : 4  ; // 7  : 4
    __IO uint32_t RESERVED0        : 24 ; // 31 : 8
} AFE_CRG_GPIO_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_PINMUX       : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} AFE_CRG_PINMUX_CLKRST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t SW_HRC_EN        : 1  ; // 0  : 0
    __IO uint32_t HRC_READY        : 1  ; // 1  : 1
    __IO uint32_t RESERVED0        : 30 ; // 31 : 2
} AFE_CRG_RCCLK_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t OTP_RST_EN       : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} AFE_CRG_OTP_RST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t RST_FLAG         : 4  ; // 3  : 0
    __IO uint32_t RESERVED2        : 1  ; // 4  : 4
    __IO uint32_t CLR_RST          : 1  ; // 5  : 5
    __IO uint32_t RESERVED1        : 2  ; // 7  : 6
    __IO uint32_t SW_POR_REQ       : 1  ; // 8  : 8
    __IO uint32_t RESERVED0        : 23 ; // 31 : 9
} AFE_CRG_RST_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t CRG_LOCK         : 1  ; // 0  : 0
    __IO uint32_t RESERVED0        : 31 ; // 31 : 1
} AFE_CRG_CRG_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t RTC_CLKRST_CTRL                           ; // 0x0000
        AFE_CRG_RTC_CLKRST_CTRL_FIELD_T RTC_CLKRST_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t ADC_CLKRST_CTRL                           ; // 0x0004
        AFE_CRG_ADC_CLKRST_CTRL_FIELD_T ADC_CLKRST_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t PWM_CLKRST_CTRL                           ; // 0x0008
        AFE_CRG_PWM_CLKRST_CTRL_FIELD_T PWM_CLKRST_CTRL_F        ;
    };

    union
    {
        __IO  uint32_t LIN_SCI_CLKRST_CTRL                       ; // 0x000C
        AFE_CRG_LIN_SCI_CLKRST_CTRL_FIELD_T LIN_SCI_CLKRST_CTRL_F;
    };

    union
    {
        __IO  uint32_t GPIO_CLKRST_CTRL                          ; // 0x0010
        AFE_CRG_GPIO_CLKRST_CTRL_FIELD_T GPIO_CLKRST_CTRL_F      ;
    };

    union
    {
        __IO  uint32_t PINMUX_CLKRST_CTRL                        ; // 0x0014
        AFE_CRG_PINMUX_CLKRST_CTRL_FIELD_T PINMUX_CLKRST_CTRL_F  ;
    };

    union
    {
        __IO  uint32_t RCCLK_CTRL                                ; // 0x0018
        AFE_CRG_RCCLK_CTRL_FIELD_T RCCLK_CTRL_F                  ;
    };

    union
    {
        __IO  uint32_t OTP_RST_CTRL                              ; // 0x001C
        AFE_CRG_OTP_RST_CTRL_FIELD_T OTP_RST_CTRL_F              ;
    };

    union
    {
        __IO  uint32_t RST_CTRL                                  ; // 0x0020
        AFE_CRG_RST_CTRL_FIELD_T RST_CTRL_F                      ;
    };

    uint32_t RESERVED0[54]                                        ;

    union
    {
        __IO  uint32_t CRG_LOCK                                  ; // 0x00FC
        AFE_CRG_CRG_LOCK_FIELD_T CRG_LOCK_F                      ;
    };

} AFE_CRG_REG_TypeDef;

#endif
