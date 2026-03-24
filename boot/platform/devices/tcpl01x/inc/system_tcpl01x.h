/**
 *****************************************************************************
 * @brief   system_tcpl01 header file.
 *
 * @file    system_tcpl01x.h
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

#ifndef __SYSTEM_TCPL01X_H__
#define __SYSTEM_TCPL01X_H__

#include "tcpl01x.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
* Definitions
******************************************************************************/
extern uint32_t SystemCoreClock;

/*******************************************************************************
* API
******************************************************************************/

#define CONFIG_SYSTEM_CORE_CLK      HCLK_SRC_RC48M

typedef enum system_hclk_src
{
    HCLK_SRC_RC48M,
    HCLK_SRC_RC32K,
    HCLK_SRC_MAX,
} enumSystemHclkSrc_t;

uint32_t GetFclkVal(void);
void SystemCoreClockUpdate(void);
uint32_t SystemGetHClkFreq(void);
void system_remap_config(uint32_t vetor_offset, bool enable);

#if defined(__cplusplus)
}
#endif
#endif /* __SYSTEM_TCPL01X_H__ */
