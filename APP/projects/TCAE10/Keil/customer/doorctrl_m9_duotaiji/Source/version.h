/**
 *****************************************************************************
 * @brief   version header file.
 *
 * @file    version.h
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

#ifndef __VERSION_H__
#define __VERSION_H__

#define TC_VERSION      0       /* major version number     */
#define TC_SUBVERSION   1       /* minor version number     */
#define TC_REVISION     0       /* revise version number    */

#define APP_VER         VERSION_CHECK(TC_VERSION, TC_SUBVERSION, TC_REVISION)

#define VERSION_CHECK(major, minor, revise)     ((major * 10000) +          \
                                                 (minor * 100) + revise)

#define DATE_YEAR_VAL                   \
         (((__DATE__[9] - '0')  * 10    \
         + (__DATE__[10] - '0')))

#define DATE_MONTH_VAL                                      \
        (__DATE__[2] == 'n' ? (__DATE__[1] == 'a' ? 1 : 6 ) \
       : __DATE__[2] == 'b' ? 2                             \
       : __DATE__[2] == 'r' ? (__DATE__[0] == 'M' ? 3 : 4)  \
       : __DATE__[2] == 'y' ? 5                             \
       : __DATE__[2] == 'l' ? 7                             \
       : __DATE__[2] == 'g' ? 8                             \
       : __DATE__[2] == 'p' ? 9                             \
       : __DATE__[2] == 't' ? 10                            \
       : __DATE__[2] == 'v' ? 11 : 12 )

#define DATE_DAY_VAL                    \
        ((__DATE__[4] == ' ' ? 0 : __DATE__[4] - '0') * 10 + (__DATE__[5] - '0'))

#define YEAR_MONTH_DAY                  \
        ((DATE_YEAR_VAL * 10000) + (DATE_MONTH_VAL * 100) + DATE_DAY_VAL)

#define TIME_HOUR_VAL                   \
        ((__TIME__[0] - '0') * 10       \
       + (__TIME__[1] - '0'))

#define TIME_MIN_VAL                    \
        ((__TIME__[3] - '0') * 10       \
       + (__TIME__[4] - '0'))

#define TIME_SEC_VAL                    \
        ((__TIME__[6] - '0') * 10       \
       + (__TIME__[7] - '0'))

#define HOUR_MIN_SEC                    \
        ((TIME_HOUR_VAL * 10000) + (TIME_MIN_VAL * 100) + TIME_SEC_VAL)

#define BCD_DIGIT(digit) "0123456789"[(digit )]

#define DATE_MONTH_HI_VAL         (DATE_MONTH_VAL / 10)
#define DATE_MONTH_LO_VAL         (DATE_MONTH_VAL % 10)

#define DATE_DAY_HI_VAL           (DATE_DAY_VAL / 10)
#define DATE_DAY_LO_VAL           (DATE_DAY_VAL % 10)

#define DATE_YEAR_0_VAL           (DATE_YEAR_VAL / 1000)
#define DATE_YEAR_1_VAL           (DATE_YEAR_VAL / 100)
#define DATE_YEAR_2_VAL           (DATE_YEAR_VAL / 10)
#define DATE_YEAR_3_VAL           (DATE_YEAR_VAL % 10)

#define DATE_YEAR_CH0             BCD_DIGIT((__DATE__[ 7] - 0x30))
#define DATE_YEAR_CH1             BCD_DIGIT((__DATE__[ 8] - 0x30))
#define DATE_YEAR_CH2             BCD_DIGIT((__DATE__[ 9] - 0x30))
#define DATE_YEAR_CH3             BCD_DIGIT((__DATE__[10] - 0x30))

#define DATE_YEAR_STR               \
        DATE_YEAR_CH0, DATE_YEAR_CH1, DATE_YEAR_CH2, DATE_YEAR_CH3

#define DATE_MONTH_CH0            BCD_DIGIT(DATE_MONTH_HI_VAL)
#define DATE_MONTH_CH1            BCD_DIGIT(DATE_MONTH_LO_VAL)

#define DATE_MONTH_STR              \
        DATE_MONTH_CH0, DATE_MONTH_CH1

#define DATE_DAY_CH0              BCD_DIGIT(DATE_DAY_HI_VAL)
#define DATE_DAY_CH1              BCD_DIGIT(DATE_DAY_LO_VAL)

#define DATE_DAY_STR                \
        DATE_DAY_CH0, DATE_DAY_CH1

#define DATE_YEAR_MONTH_DAY_STR     \
        DATE_YEAR_STR, DATE_MONTH_STR, DATE_DAY_STR

#define TIME_HOUR_CH0             BCD_DIGIT(TIME_HOUR_VAL / 10)
#define TIME_HOUR_CH1             BCD_DIGIT(TIME_HOUR_VAL % 10)

#define TIME_HOUR_STR               \
        TIME_HOUR_CH0, TIME_HOUR_CH1

#define TIME_MIN_CH0              BCD_DIGIT(TIME_MIN_VAL / 10)
#define TIME_MIN_CH1              BCD_DIGIT(TIME_MIN_VAL % 10)

#define TIME_MIN_STR                \
        TIME_MIN_CH0, TIME_MIN_CH1

#define TIME_SEC_CH0              BCD_DIGIT(TIME_SEC_VAL / 10)
#define TIME_SEC_CH1              BCD_DIGIT(TIME_SEC_VAL % 10)

#define TIME_SEC_STR                \
        TIME_SEC_CH0, TIME_SEC_CH1

#define TIEM_HOUR_MIN_SEC_STR       \
        TIME_HOUR_STR, TIME_MIN_STR, TIME_SEC_STR

#define DATE_TIME_STR               \
        DATE_YEAR_MONTH_DAY_STR, TIEM_HOUR_MIN_SEC_STR

#endif
