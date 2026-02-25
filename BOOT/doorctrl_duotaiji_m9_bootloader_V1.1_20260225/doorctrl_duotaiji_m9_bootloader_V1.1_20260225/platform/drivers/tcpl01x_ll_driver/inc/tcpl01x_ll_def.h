/**
*****************************************************************************
* @brief   driver def header.
*
* @file    ll_def.h
* @author
* @date    2024.04.20
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <b>&copy; Copyright (c) 2022 Tinychip Microelectronics Co.,Ltd.</b>
*
*****************************************************************************
*/

#ifndef __TCPL01X_LL_DEF_H__
#define __TCPL01X_LL_DEF_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "tcpl01x.h"

#if defined(__cplusplus)
extern "C" {
#endif

#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif

#if 0
#define CLOCK_CONFIG_LOCK()     (CRG->CRG_LOCK = 0x12345678)
#define CLOCK_CONFIG_UNLOCK()   (CRG->CRG_LOCK = 0x5a5a5a5a)
#else
#define CLOCK_CONFIG_LOCK()
#define CLOCK_CONFIG_UNLOCK()
#endif

#if 0
#define AFE_CLOCK_CONFIG_LOCK()     (AFE_CRG->CRG_LOCK = 0xfedcba98)
#define AFE_CLOCK_CONFIG_UNLOCK()   (AFE_CRG->CRG_LOCK = 0x76543210)
#else
#define AFE_CLOCK_CONFIG_LOCK()
#define AFE_CLOCK_CONFIG_UNLOCK()
#endif

#if 0
#define SYSCFG_LOCK()           SYSCFG->SYSCFG_LOCK = 0x12345678
#define SYSCFG_UNLOCK()         SYSCFG->SYSCFG_LOCK = 0xaa55aa55
#else
#define SYSCFG_LOCK()
#define SYSCFG_UNLOCK()
#endif

#if 0
#define AFE_SYSCFG_LOCK()                                               \
   do {                                                                \                                         \
       afe_reg_write(AFE_SYSCFG->SYSCFG_LOCK, 0x12345678);     \
       } while (0)

#define AFE_SYSCFG_UNLOCK()                                             \
   do {                                                                \                                         \
       afe_reg_write(AFE_SYSCFG->SYSCFG_LOCK, 0xaa55aa55);     \
       } while (0)
#else
#define AFE_SYSCFG_LOCK()
#define AFE_SYSCFG_UNLOCK()
#endif

/*!
   \brief Performes a software reset
*/
#define LL_SOFTWARE_RESET()                              \
        do{                                           \
            CLOCK_CONFIG_UNLOCK(); \
            CRG->M0_CLKRST_CTRL_F.RST_M0=1;        \
            CLOCK_CONFIG_LOCK();    \
        }while(0)

/*!
   \brief Performes a software reset
*/
#define LL_SOFTWARE_RESET_FLAG_CLEAR()                              \
        do{                                           \
            CLOCK_CONFIG_UNLOCK(); \
            CRG->RST_CTRL_F.CLR_RST = 1;      \
            CLOCK_CONFIG_LOCK();    \
        }while(0)

/**
  * @brief  fclk_src_e enumeration
  */
typedef enum
{
    FCLK_SRC_48M,
    FCLK_SRC_32K,
    FCLK_SRC_MAX,
} fclk_src_e;

typedef enum
{
    LIN_AA_STYPE_STEPS_4 = 0,
    LIN_AA_STYPE_STEPS_3,
    LIN_AA_STYPE_STEPS_2,
} lin_aa_type_e;

/**
  * @brief  ll status enumeration
  */
typedef enum
{
    LL_OK       = 0x00U,
    LL_ERROR    = 0x01U,
    LL_BUSY     = 0x02U,
    LL_TIMEOUT  = 0x03U,
    LL_COMM_ERROR  = 0x04U,
    LL_PARAM_INVALID  = 0x05U
} ll_status_e;

/**
 * @brief CALLBACK FUNC
 */
typedef void (*ISR_FUNC_CALLBACK)(uint32_t);

/**
  * @brief  ll clk struct
  */
typedef struct
{
    fclk_src_e clk_source;
    uint8_t  fclk_div;
} ll_clk_config_t;

/**
  * @brief  ll clk struct
  */
typedef struct
{
    uint32_t isr;
    uint32_t isr1;
    uint8_t priority;
    bool isr_enable;
} ll_isr_config_t;

#include "tcpl01x_ll_cortex.h"
#include "tcpl01x_ll_sys.h"
#include "tcpl01x_ll_adc.h"
#include "tcpl01x_ll_crc.h"
#include "tcpl01x_ll_flash.h"
#include "tcpl01x_ll_gpio.h"
#include "tcpl01x_ll_lpm.h"
#include "tcpl01x_ll_pwm.h"
#include "tcpl01x_ll_rtc.h"
#include "tcpl01x_ll_sci.h"
#include "tcpl01x_ll_rtc.h"
#include "tcpl01x_ll_timer.h"
#include "tcpl01x_ll_wdg.h"

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_DEF_H__ */
