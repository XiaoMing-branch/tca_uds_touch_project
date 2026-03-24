/**
 *****************************************************************************
 * @brief   crc header file.
 *
 * @file    tcpl01x_ll_crc.h
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

#ifndef __TCPL01X_LL_CRC_H__
#define __TCPL01X_LL_CRC_H__

#include <stdint.h>
#include "tcpl01x_ll_cortex.h"
#include "tcpl01x.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define CRC_MODE_CRC32      0X00000000u
#define CRC_MODE_CRC16      0X00000001u
#define CRC_MODE_CRC8       0X00000002u

#define CRC_IN_DATA_REVERS_NONE              0X00u
#define CRC_IN_DATA_REVERS_BY_BYTE           0X01u
#define CRC_IN_DATA_REVERS_BY_HALF_WORLD     0X10u
#define CRC_IN_DATA_REVERS_BY_WORLD          0X11u

void CRC_Enable(bool enable);
void CRC_Init(uint8_t crc_mode, uint8_t in_data_reverse_type, bool out_data_reverse_enable);
uint8_t ll_crc_calculate8(uint8_t *in_data, uint8_t init_value, uint8_t poly, uint32_t data_length);
uint16_t ll_crc_calculate16(uint8_t *in_data, uint16_t init_value, uint16_t poly, uint32_t data_length);
uint32_t ll_crc_calculate32(uint8_t *in_data, uint32_t init_value, uint32_t poly, uint32_t data_length);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_CRC_H__ */
