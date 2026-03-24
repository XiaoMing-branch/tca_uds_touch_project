/**
 *****************************************************************************
 * @brief   interrupt header file.
 *
 * @file    tcpl01x_ll_cortex.h
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

#ifndef __TCPL01X_LL_CORTEX_H__
#define __TCPL01X_LL_CORTEX_H__

#include "tcpl01x.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define AFE_ADDR_STATUS_CRC_ENABLE      0x00000010u
#define AFE_ADDR_STATUS_COM_BUSY        0x0000000Cu

#define AFE_COM_SPI_CLK_DIV_2       0x00000000u
#define AFE_COM_SPI_CLK_DIV_4       0x00000001u
#define AFE_COM_SPI_CLK_DIV_8       0x00000002u
#define AFE_COM_SPI_CLK_DIV_16      0x00000003u

#define AFE_COM_IMR_POS_WRITE_FAIL      0X0
#define AFE_COM_IMR_POS_READ_FAIL       0X1
#define AFE_COM_IMR_POS_FINISH          0X2

#define AFE_COM_INTERRUPT_WRITE_FAIL    (1 << AFE_COM_IMR_POS_WRITE_FAIL)
#define AFE_COM_INTERRUPT_READ_FAIL     (1 << AFE_COM_IMR_POS_READ_FAIL)
#define AFE_COM_INTERRUPT_FINISH        (1 << AFE_COM_IMR_POS_FINISH)

void EnableNvic(uint32_t irq, uint8_t level, bool en);
void AFE_INT_IRQHandler(void);
void afe_isr_mask_get(uint32_t *Imr0, uint32_t *Imr1);
void afe_isr_mask_set(uint32_t Imr0, uint32_t Imr1);
void afe_isr_all_clear(void);
void afe_syscfg_int_enable(uint32_t int0, uint32_t int1);
void afe_syscfg_int_disable(uint32_t int0, uint32_t int1);
void afe_syscfg_int_flag_clear(uint32_t int0, uint32_t int1);
bool afe_syscfg_event_status_get(uint32_t int0, uint32_t int1);

void afe_com_init(uint8_t clk_div);
uint16_t afe_com_address_get(void);
void afe_com_isr_enable(uint8_t it_bit, bool enbale);
void afe_com_isr_flag_clear(uint8_t it_bit);
uint8_t afe_com_isr_flag_get(void);
void afe_com_crc_enable(bool enable);
uint8_t afe_reg_write(volatile uint32_t *reg, uint32_t val);
uint8_t afe_reg_read(volatile uint32_t *reg, uint32_t *val);
void afe_bit_set(volatile uint32_t *reg, uint32_t pos);
void afe_bit_clear(volatile uint32_t *reg, uint32_t pos);

#ifdef __cplusplus
}
#endif
#endif /* __TCPL01X_LL_CORTEX_H__ */
