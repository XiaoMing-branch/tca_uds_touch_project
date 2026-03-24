/**
 *****************************************************************************
 * @brief   tcpl01 header file.
 *
 * @file    tcpl01x.h
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

#ifndef __TCPL01X_H__
#define __TCPL01X_H__

#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @brief 32 bits memory read macro.
*/
#if !defined(REG_READ32)
#define REG_READ32(address)               (*(volatile uint32_t*)(address))
#endif

/**
* @brief 32 bits memory write macro.
*/
#if !defined(REG_WRITE32)
#define REG_WRITE32(address, value)       ((*(volatile uint32_t*)(address))= (uint32_t)(value))
#endif

/**
* @brief 32 bits bits setting macro.
*/
#if !defined(REG_BIT_SET32)
#define REG_BIT_SET32(address, mask)      ((*(volatile uint32_t*)(address))|= (uint32_t)(mask))
#endif

/**
* @brief 32 bits bits clearing macro.
*/
#if !defined(REG_BIT_CLEAR32)
#define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32_t*)(address))&= ((uint32_t)~((uint32_t)(mask))))
#endif

/**
* @brief 32 bit clear bits and set with new value
* @note It is user's responsability to make sure that value has only "mask" bits set - (value&~mask)==0
*/
#if !defined(REG_RMW32)
#define REG_RMW32(address, mask, value)   (REG_WRITE32((address), ((REG_READ32(address)& ((uint32_t)~((uint32_t)(mask))))| ((uint32_t)(value)))))
#endif

typedef enum IRQn
{
    /******  Cortex-M# Processor Exceptions Numbers ***************************************************/

    /* ToDo: use this Cortex interrupt numbers if your device is a CORTEX-M4 device                   */
    NonMaskableInt_IRQn           = -14,      /*!<  2 Non Maskable Interrupt                        */
    HardFault_IRQn                = -13,      /*!<  3 Hard Fault Interrupt                          */
    SVCall_IRQn                   = -5,       /*!< 11 SV Call Interrupt                             */
    PendSV_IRQn                   = -2,       /*!< 14 Pend SV Interrupt                             */
    SysTick_IRQn                  = -1,       /*!< 15 System Tick Interrupt                         */

    /******  Device Specific Interrupt Numbers ********************************************************/
    /* ToDo: add here your device specific external interrupt numbers
             according the interrupt handlers defined in startup_Device.s
             eg.: Interrupt for Timer#1       TIM1_IRQHandler   ->   TIM1_IRQn                        */

    AFE_INT_IRQn    = 0,
    TIMER_IRQn      = 1,
    IWDG_IRQn        = 2,
    FLASH_IRQn     = 3,
    AFE_COM_IRQn    = 4,
} IRQn_Type;

#define ADC_IRQn    (AFE_INT_IRQn)

/************************************************************************/
/*  Processor and Core Peripheral Section                               */
/************************************************************************/
/* -------  Start of section using anonymous unions and disabling warnings  ------- */
#if   defined (__CC_ARM)
#pragma push
#pragma anon_unions
#elif defined (__ICCARM__)
#pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc11-extensions"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning 586
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif
/* --------  Configuration of Core Peripherals  ----------------------------------- */
#define __CM0_REV                 0x0000U   /* Core revision r0p0 */
#define __MPU_PRESENT             0U        /* no MPU present */
#define __VTOR_PRESENT            0U        /* no VTOR present */
#define __NVIC_PRIO_BITS          2U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */

#include <core_cm0.h>

#define DEFAULT_SYSTEM_CLOCK    (48000000UL)
#define DEFAULT_AFE_CLOCK       (48000000UL)
#define DEFAULT_RC32K_CLOCK     (32000UL)
/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR TCPL01X */
/* ************************************************************************** */
/** \defgroup TCPL01X_api Peripheral Software API */
#include "tcpl01x_ll_cortex.h"
#include "tcpl01x_ll_sys.h"
// Register Structure Definition
#include "./reg/register.h"

/* --------  End of section using anonymous unions and disabling warnings  -------- */
#if   defined (__CC_ARM)
#pragma pop
#elif defined (__ICCARM__)
/* leave anonymous unions enabled */
#elif (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
#pragma clang diagnostic pop
#elif defined (__GNUC__)
/* anonymous unions are enabled by default */
#elif defined (__TMS470__)
/* anonymous unions are enabled by default */
#elif defined (__TASKING__)
#pragma warning restore
#elif defined (__CSMC__)
/* anonymous unions are enabled by default */
#else
#warning Not supported compiler type
#endif

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#ifdef __cplusplus
}
#endif
#endif /* __TCPL01X_H__ */
