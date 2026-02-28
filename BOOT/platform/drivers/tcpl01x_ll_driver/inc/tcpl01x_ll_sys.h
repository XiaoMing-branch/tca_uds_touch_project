/**
 *****************************************************************************
 * @brief   syscfg header file.
 *
 * @file    tcpl01x_ll_tcpl01x_ll_sys
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

#ifndef __TCPL01X_LL_SYS_H__
#define __TCPL01X_LL_SYS_H__

#include <stdint.h>
#include <stdbool.h>
#include "tcpl01x.h"

#if defined(__cplusplus)
extern "C" {
#endif

void ll_syscfg_info_get(uint8_t *revision_id, uint16_t *chip_id);
void ll_syscfg_afeinfo_get(uint8_t *revision_id, uint16_t *chip_id);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_SYS_H__ */
