/**
 *****************************************************************************
 * @brief   rtc_reg_def header file.
 *
 * @file    rtc_reg_def.h
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

#ifndef   RTC_DEF_H__
#define   RTC_DEF_H__

// Register Offset Macro Definition
#define RTC_RTC_CTRL_OFFSET                                     0x0000
#define RTC_RTC_TRIG_0_OFFSET                                   0x0004
#define RTC_RTC_CNT_OFFSET                                      0x0008
#define RTC_RTC_ALARM_OFFSET                                    0x000C
#define RTC_RTC_SEC_OFFSET                                      0x0010
#define RTC_RTC_MIN_OFFSET                                      0x0014
#define RTC_RTC_HOUR_OFFSET                                     0x0018
#define RTC_RTC_DAY_OFFSET                                      0x001C
#define RTC_RTC_MON_OFFSET                                      0x0020
#define RTC_RTC_YEAR_OFFSET                                     0x0024
#define RTC_RTC_CALENDAR_0_OFFSET                               0x0028
#define RTC_RTC_CALENDAR_1_OFFSET                               0x002C
#define RTC_LOCK_OFFSET                                         0x00FC

// Register Address Macro Definition
#define RTC_RTC_CTRL_ADDR                                       ( RTC_BASE_ADDR + RTC_RTC_CTRL_OFFSET)
#define RTC_RTC_TRIG_0_ADDR                                     ( RTC_BASE_ADDR + RTC_RTC_TRIG_0_OFFSET)
#define RTC_RTC_CNT_ADDR                                        ( RTC_BASE_ADDR + RTC_RTC_CNT_OFFSET)
#define RTC_RTC_ALARM_ADDR                                      ( RTC_BASE_ADDR + RTC_RTC_ALARM_OFFSET)
#define RTC_RTC_SEC_ADDR                                        ( RTC_BASE_ADDR + RTC_RTC_SEC_OFFSET)
#define RTC_RTC_MIN_ADDR                                        ( RTC_BASE_ADDR + RTC_RTC_MIN_OFFSET)
#define RTC_RTC_HOUR_ADDR                                       ( RTC_BASE_ADDR + RTC_RTC_HOUR_OFFSET)
#define RTC_RTC_DAY_ADDR                                        ( RTC_BASE_ADDR + RTC_RTC_DAY_OFFSET)
#define RTC_RTC_MON_ADDR                                        ( RTC_BASE_ADDR + RTC_RTC_MON_OFFSET)
#define RTC_RTC_YEAR_ADDR                                       ( RTC_BASE_ADDR + RTC_RTC_YEAR_OFFSET)
#define RTC_RTC_CALENDAR_0_ADDR                                 ( RTC_BASE_ADDR + RTC_RTC_CALENDAR_0_OFFSET)
#define RTC_RTC_CALENDAR_1_ADDR                                 ( RTC_BASE_ADDR + RTC_RTC_CALENDAR_1_OFFSET)
#define RTC_LOCK_ADDR                                           ( RTC_BASE_ADDR + RTC_LOCK_OFFSET)

// Register Field Macro Definition
#define RTC_RTC_CTRL_CALENDAR_EN_SHIFT                             18
#define RTC_RTC_CTRL_CALENDAR_EN_MASK                              0x00040000
#define RTC_RTC_CTRL_CALENDAR_EN_SET(n)                            (((uint32_t)(n) << 18 ) & 0x00040000)
#define RTC_RTC_CTRL_CALENDAR_EN_CLR                               0xFFFBFFFF

#define RTC_RTC_CTRL_CALENDAR_LOAD_SHIFT                           17
#define RTC_RTC_CTRL_CALENDAR_LOAD_MASK                            0x00020000
#define RTC_RTC_CTRL_CALENDAR_LOAD_SET(n)                          (((uint32_t)(n) << 17 ) & 0x00020000)
#define RTC_RTC_CTRL_CALENDAR_LOAD_CLR                             0xFFFDFFFF

#define RTC_RTC_CTRL_CALENDAR_CLR_SHIFT                            16
#define RTC_RTC_CTRL_CALENDAR_CLR_MASK                             0x00010000
#define RTC_RTC_CTRL_CALENDAR_CLR_SET(n)                           (((uint32_t)(n) << 16 ) & 0x00010000)
#define RTC_RTC_CTRL_CALENDAR_CLR_CLR                              0xFFFEFFFF

#define RTC_RTC_CTRL_TRIG_GADC_EN_SHIFT                            10
#define RTC_RTC_CTRL_TRIG_GADC_EN_MASK                             0x00000400
#define RTC_RTC_CTRL_TRIG_GADC_EN_SET(n)                           (((uint32_t)(n) << 10 ) & 0x00000400)
#define RTC_RTC_CTRL_TRIG_GADC_EN_CLR                              0xFFFFFBFF

#define RTC_RTC_CTRL_TRIG_LOAD_0_SHIFT                             9
#define RTC_RTC_CTRL_TRIG_LOAD_0_MASK                              0x00000200
#define RTC_RTC_CTRL_TRIG_LOAD_0_SET(n)                            (((uint32_t)(n) << 9  ) & 0x00000200)
#define RTC_RTC_CTRL_TRIG_LOAD_0_CLR                               0xFFFFFDFF

#define RTC_RTC_CTRL_TRIG_EN_0_SHIFT                               8
#define RTC_RTC_CTRL_TRIG_EN_0_MASK                                0x00000100
#define RTC_RTC_CTRL_TRIG_EN_0_SET(n)                              (((uint32_t)(n) << 8  ) & 0x00000100)
#define RTC_RTC_CTRL_TRIG_EN_0_CLR                                 0xFFFFFEFF

#define RTC_RTC_CTRL_CNT_LOAD_SHIFT                                5
#define RTC_RTC_CTRL_CNT_LOAD_MASK                                 0x00000020
#define RTC_RTC_CTRL_CNT_LOAD_SET(n)                               (((uint32_t)(n) << 5  ) & 0x00000020)
#define RTC_RTC_CTRL_CNT_LOAD_CLR                                  0xFFFFFFDF

#define RTC_RTC_CTRL_CNT_EN_SHIFT                                  4
#define RTC_RTC_CTRL_CNT_EN_MASK                                   0x00000010
#define RTC_RTC_CTRL_CNT_EN_SET(n)                                 (((uint32_t)(n) << 4  ) & 0x00000010)
#define RTC_RTC_CTRL_CNT_EN_CLR                                    0xFFFFFFEF

#define RTC_RTC_CTRL_RTC_LOAD_SHIFT                                2
#define RTC_RTC_CTRL_RTC_LOAD_MASK                                 0x00000004
#define RTC_RTC_CTRL_RTC_LOAD_SET(n)                               (((uint32_t)(n) << 2  ) & 0x00000004)
#define RTC_RTC_CTRL_RTC_LOAD_CLR                                  0xFFFFFFFB

#define RTC_RTC_CTRL_RTC_CLR_SHIFT                                 1
#define RTC_RTC_CTRL_RTC_CLR_MASK                                  0x00000002
#define RTC_RTC_CTRL_RTC_CLR_SET(n)                                (((uint32_t)(n) << 1  ) & 0x00000002)
#define RTC_RTC_CTRL_RTC_CLR_CLR                                   0xFFFFFFFD

#define RTC_RTC_CTRL_RTC_HOLD_SHIFT                                0
#define RTC_RTC_CTRL_RTC_HOLD_MASK                                 0x00000001
#define RTC_RTC_CTRL_RTC_HOLD_SET(n)                               (((uint32_t)(n) << 0  ) & 0x00000001)
#define RTC_RTC_CTRL_RTC_HOLD_CLR                                  0xFFFFFFFE

#define RTC_RTC_TRIG_0_TRIG_PHASE_0_SHIFT                          16
#define RTC_RTC_TRIG_0_TRIG_PHASE_0_MASK                           0xFFFF0000
#define RTC_RTC_TRIG_0_TRIG_PHASE_0_SET(n)                         (((uint32_t)(n) << 16 ) & 0xFFFF0000)
#define RTC_RTC_TRIG_0_TRIG_PHASE_0_CLR                            0x0000FFFF

#define RTC_RTC_TRIG_0_TRIG_NUM_0_SHIFT                            0
#define RTC_RTC_TRIG_0_TRIG_NUM_0_MASK                             0x0000FFFF
#define RTC_RTC_TRIG_0_TRIG_NUM_0_SET(n)                           (((uint32_t)(n) << 0  ) & 0x0000FFFF)
#define RTC_RTC_TRIG_0_TRIG_NUM_0_CLR                              0xFFFF0000

#define RTC_RTC_CNT_CNT_NUM_SHIFT                                  0
#define RTC_RTC_CNT_CNT_NUM_MASK                                   0x00FFFFFF
#define RTC_RTC_CNT_CNT_NUM_SET(n)                                 (((uint32_t)(n) << 0  ) & 0x00FFFFFF)
#define RTC_RTC_CNT_CNT_NUM_CLR                                    0xFF000000

#define RTC_RTC_ALARM_ALARM_HOUR_SHIFT                             16
#define RTC_RTC_ALARM_ALARM_HOUR_MASK                              0x001F0000
#define RTC_RTC_ALARM_ALARM_HOUR_SET(n)                            (((uint32_t)(n) << 16 ) & 0x001F0000)
#define RTC_RTC_ALARM_ALARM_HOUR_CLR                               0xFFE0FFFF

#define RTC_RTC_ALARM_ALARM_MIN_SHIFT                              8
#define RTC_RTC_ALARM_ALARM_MIN_MASK                               0x00003F00
#define RTC_RTC_ALARM_ALARM_MIN_SET(n)                             (((uint32_t)(n) << 8  ) & 0x00003F00)
#define RTC_RTC_ALARM_ALARM_MIN_CLR                                0xFFFFC0FF

#define RTC_RTC_ALARM_ALARM_SEC_SHIFT                              0
#define RTC_RTC_ALARM_ALARM_SEC_MASK                               0x0000003F
#define RTC_RTC_ALARM_ALARM_SEC_SET(n)                             (((uint32_t)(n) << 0  ) & 0x0000003F)
#define RTC_RTC_ALARM_ALARM_SEC_CLR                                0xFFFFFFC0

#define RTC_RTC_SEC_SEC_SHIFT                                      0
#define RTC_RTC_SEC_SEC_MASK                                       0x0000003F
#define RTC_RTC_SEC_SEC_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x0000003F)
#define RTC_RTC_SEC_SEC_CLR                                        0xFFFFFFC0

#define RTC_RTC_MIN_MIN_SHIFT                                      0
#define RTC_RTC_MIN_MIN_MASK                                       0x0000003F
#define RTC_RTC_MIN_MIN_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x0000003F)
#define RTC_RTC_MIN_MIN_CLR                                        0xFFFFFFC0

#define RTC_RTC_HOUR_HOUR_SHIFT                                    0
#define RTC_RTC_HOUR_HOUR_MASK                                     0x0000001F
#define RTC_RTC_HOUR_HOUR_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x0000001F)
#define RTC_RTC_HOUR_HOUR_CLR                                      0xFFFFFFE0

#define RTC_RTC_DAY_DAY_SHIFT                                      0
#define RTC_RTC_DAY_DAY_MASK                                       0x0000001F
#define RTC_RTC_DAY_DAY_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x0000001F)
#define RTC_RTC_DAY_DAY_CLR                                        0xFFFFFFE0

#define RTC_RTC_MON_MON_SHIFT                                      0
#define RTC_RTC_MON_MON_MASK                                       0x0000000F
#define RTC_RTC_MON_MON_SET(n)                                     (((uint32_t)(n) << 0  ) & 0x0000000F)
#define RTC_RTC_MON_MON_CLR                                        0xFFFFFFF0

#define RTC_RTC_YEAR_YEAR_SHIFT                                    0
#define RTC_RTC_YEAR_YEAR_MASK                                     0x0000007F
#define RTC_RTC_YEAR_YEAR_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x0000007F)
#define RTC_RTC_YEAR_YEAR_CLR                                      0xFFFFFF80

#define RTC_RTC_CALENDAR_0_CALENDAR_HOUR_SHIFT                     16
#define RTC_RTC_CALENDAR_0_CALENDAR_HOUR_MASK                      0x001F0000
#define RTC_RTC_CALENDAR_0_CALENDAR_HOUR_SET(n)                    (((uint32_t)(n) << 16 ) & 0x001F0000)
#define RTC_RTC_CALENDAR_0_CALENDAR_HOUR_CLR                       0xFFE0FFFF

#define RTC_RTC_CALENDAR_0_CALENDAR_MIN_SHIFT                      8
#define RTC_RTC_CALENDAR_0_CALENDAR_MIN_MASK                       0x00003F00
#define RTC_RTC_CALENDAR_0_CALENDAR_MIN_SET(n)                     (((uint32_t)(n) << 8  ) & 0x00003F00)
#define RTC_RTC_CALENDAR_0_CALENDAR_MIN_CLR                        0xFFFFC0FF

#define RTC_RTC_CALENDAR_0_CALENDAR_SEC_SHIFT                      0
#define RTC_RTC_CALENDAR_0_CALENDAR_SEC_MASK                       0x0000003F
#define RTC_RTC_CALENDAR_0_CALENDAR_SEC_SET(n)                     (((uint32_t)(n) << 0  ) & 0x0000003F)
#define RTC_RTC_CALENDAR_0_CALENDAR_SEC_CLR                        0xFFFFFFC0

#define RTC_RTC_CALENDAR_1_CALENDAR_YEAR_SHIFT                     16
#define RTC_RTC_CALENDAR_1_CALENDAR_YEAR_MASK                      0x007F0000
#define RTC_RTC_CALENDAR_1_CALENDAR_YEAR_SET(n)                    (((uint32_t)(n) << 16 ) & 0x007F0000)
#define RTC_RTC_CALENDAR_1_CALENDAR_YEAR_CLR                       0xFF80FFFF

#define RTC_RTC_CALENDAR_1_CALENDAR_MON_SHIFT                      8
#define RTC_RTC_CALENDAR_1_CALENDAR_MON_MASK                       0x00000F00
#define RTC_RTC_CALENDAR_1_CALENDAR_MON_SET(n)                     (((uint32_t)(n) << 8  ) & 0x00000F00)
#define RTC_RTC_CALENDAR_1_CALENDAR_MON_CLR                        0xFFFFF0FF

#define RTC_RTC_CALENDAR_1_CALENDAR_DAY_SHIFT                      0
#define RTC_RTC_CALENDAR_1_CALENDAR_DAY_MASK                       0x0000001F
#define RTC_RTC_CALENDAR_1_CALENDAR_DAY_SET(n)                     (((uint32_t)(n) << 0  ) & 0x0000001F)
#define RTC_RTC_CALENDAR_1_CALENDAR_DAY_CLR                        0xFFFFFFE0

#define RTC_LOCK_RTC_LOCK_SHIFT                                    0
#define RTC_LOCK_RTC_LOCK_MASK                                     0x00000001
#define RTC_LOCK_RTC_LOCK_SET(n)                                   (((uint32_t)(n) << 0  ) & 0x00000001)
#define RTC_LOCK_RTC_LOCK_CLR                                      0xFFFFFFFE

// Register Structure Definition
typedef struct
{
    __IO uint32_t RTC_HOLD        : 1  ; // 0  : 0
    __IO uint32_t RTC_CLR         : 1  ; // 1  : 1
    __IO uint32_t RTC_LOAD        : 1  ; // 2  : 2
    __IO uint32_t RESERVED3       : 1  ; // 3  : 3
    __IO uint32_t CNT_EN          : 1  ; // 4  : 4
    __IO uint32_t CNT_LOAD        : 1  ; // 5  : 5
    __IO uint32_t RESERVED2       : 2  ; // 7  : 6
    __IO uint32_t TRIG_EN_0       : 1  ; // 8  : 8
    __IO uint32_t TRIG_LOAD_0     : 1  ; // 9  : 9
    __IO uint32_t TRIG_GADC_EN    : 1  ; // 10 : 10
    __IO uint32_t RESERVED1       : 5  ; // 15 : 11
    __IO uint32_t CALENDAR_CLR    : 1  ; // 16 : 16
    __IO uint32_t CALENDAR_LOAD   : 1  ; // 17 : 17
    __IO uint32_t CALENDAR_EN     : 1  ; // 18 : 18
    __IO uint32_t RESERVED0       : 13 ; // 31 : 19
} RTC_RTC_CTRL_FIELD_T;

typedef struct
{
    __IO uint32_t TRIG_NUM_0      : 16 ; // 15 : 0
    __IO uint32_t TRIG_PHASE_0    : 16 ; // 31 : 16
} RTC_RTC_TRIG_0_FIELD_T;

typedef struct
{
    __IO uint32_t CNT_NUM         : 24 ; // 23 : 0
    __IO uint32_t RESERVED0       : 8  ; // 31 : 24
} RTC_RTC_CNT_FIELD_T;

typedef struct
{
    __IO uint32_t ALARM_SEC       : 6  ; // 5  : 0
    __IO uint32_t RESERVED2       : 2  ; // 7  : 6
    __IO uint32_t ALARM_MIN       : 6  ; // 13 : 8
    __IO uint32_t RESERVED1       : 2  ; // 15 : 14
    __IO uint32_t ALARM_HOUR      : 5  ; // 20 : 16
    __IO uint32_t RESERVED0       : 11 ; // 31 : 21
} RTC_RTC_ALARM_FIELD_T;

typedef struct
{
    __IO uint32_t SEC             : 6  ; // 5  : 0
    __IO uint32_t RESERVED0       : 26 ; // 31 : 6
} RTC_RTC_SEC_FIELD_T;

typedef struct
{
    __IO uint32_t MIN             : 6  ; // 5  : 0
    __IO uint32_t RESERVED0       : 26 ; // 31 : 6
} RTC_RTC_MIN_FIELD_T;

typedef struct
{
    __IO uint32_t HOUR            : 5  ; // 4  : 0
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} RTC_RTC_HOUR_FIELD_T;

typedef struct
{
    __IO uint32_t DAY             : 5  ; // 4  : 0
    __IO uint32_t RESERVED0       : 27 ; // 31 : 5
} RTC_RTC_DAY_FIELD_T;

typedef struct
{
    __IO uint32_t MON             : 4  ; // 3  : 0
    __IO uint32_t RESERVED0       : 28 ; // 31 : 4
} RTC_RTC_MON_FIELD_T;

typedef struct
{
    __IO uint32_t YEAR            : 7  ; // 6  : 0
    __IO uint32_t RESERVED0       : 25 ; // 31 : 7
} RTC_RTC_YEAR_FIELD_T;

typedef struct
{
    __IO uint32_t CALENDAR_SEC    : 6  ; // 5  : 0
    __IO uint32_t RESERVED2       : 2  ; // 7  : 6
    __IO uint32_t CALENDAR_MIN    : 6  ; // 13 : 8
    __IO uint32_t RESERVED1       : 2  ; // 15 : 14
    __IO uint32_t CALENDAR_HOUR   : 5  ; // 20 : 16
    __IO uint32_t RESERVED0       : 11 ; // 31 : 21
} RTC_RTC_CALENDAR_0_FIELD_T;

typedef struct
{
    __IO uint32_t CALENDAR_DAY    : 5  ; // 4  : 0
    __IO uint32_t RESERVED2       : 3  ; // 7  : 5
    __IO uint32_t CALENDAR_MON    : 4  ; // 11 : 8
    __IO uint32_t RESERVED1       : 4  ; // 15 : 12
    __IO uint32_t CALENDAR_YEAR   : 7  ; // 22 : 16
    __IO uint32_t RESERVED0       : 9  ; // 31 : 23
} RTC_RTC_CALENDAR_1_FIELD_T;

typedef struct
{
    __IO uint32_t RTC_LOCK        : 1  ; // 0  : 0
    __IO uint32_t RESERVED0       : 31 ; // 31 : 1
} RTC_LOCK_FIELD_T;

// Register Map Structure Definition
typedef struct
{
    union
    {
        __IO  uint32_t RTC_CTRL                        ; // 0x0000
        RTC_RTC_CTRL_FIELD_T RTC_CTRL_F                ;
    };

    union
    {
        __IO  uint32_t RTC_TRIG_0                      ; // 0x0004
        RTC_RTC_TRIG_0_FIELD_T RTC_TRIG_0_F            ;
    };

    union
    {
        __IO  uint32_t RTC_CNT                         ; // 0x0008
        RTC_RTC_CNT_FIELD_T RTC_CNT_F                  ;
    };

    union
    {
        __IO  uint32_t RTC_ALARM                       ; // 0x000C
        RTC_RTC_ALARM_FIELD_T RTC_ALARM_F              ;
    };

    union
    {
        __IO  uint32_t RTC_SEC                         ; // 0x0010
        RTC_RTC_SEC_FIELD_T RTC_SEC_F                  ;
    };

    union
    {
        __IO  uint32_t RTC_MIN                         ; // 0x0014
        RTC_RTC_MIN_FIELD_T RTC_MIN_F                  ;
    };

    union
    {
        __IO  uint32_t RTC_HOUR                        ; // 0x0018
        RTC_RTC_HOUR_FIELD_T RTC_HOUR_F                ;
    };

    union
    {
        __IO  uint32_t RTC_DAY                         ; // 0x001C
        RTC_RTC_DAY_FIELD_T RTC_DAY_F                  ;
    };

    union
    {
        __IO  uint32_t RTC_MON                         ; // 0x0020
        RTC_RTC_MON_FIELD_T RTC_MON_F                  ;
    };

    union
    {
        __IO  uint32_t RTC_YEAR                        ; // 0x0024
        RTC_RTC_YEAR_FIELD_T RTC_YEAR_F                ;
    };

    union
    {
        __IO  uint32_t RTC_CALENDAR_0                  ; // 0x0028
        RTC_RTC_CALENDAR_0_FIELD_T RTC_CALENDAR_0_F    ;
    };

    union
    {
        __IO  uint32_t RTC_CALENDAR_1                  ; // 0x002C
        RTC_RTC_CALENDAR_1_FIELD_T RTC_CALENDAR_1_F    ;
    };

    uint32_t RESERVED0[51]                              ;

    union
    {
        __IO  uint32_t LOCK                            ; // 0x00FC
        RTC_LOCK_FIELD_T LOCK_F                        ;
    };

} RTC_REG_TypeDef;

#endif
