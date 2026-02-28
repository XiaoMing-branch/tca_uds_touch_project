/**
 *****************************************************************************
 * @brief   register_map header file.
 *
 * @file    register_map.h
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

#ifndef __REGISTER_MAP_H__
#define __REGISTER_MAP_H__

// --------------------------------------------------------
// Memory
#define  EFLASH_BASE_ADDR         0x00FF0000
#define  SRAM_BASE_ADDR           0x10000000

// MCU Peripheral
// -- APB
#define  PMU_BASE_ADDR            0x40000000
#define  WDG_BASE_ADDR            0x40001000
#define  TEST_BASE_ADDR           0x40002000
#define  CRG_BASE_ADDR            0x40003000
#define  SYSCFG_BASE_ADDR         0x40004000
#define  PINMUX_BASE_ADDR         0x40005000
#define  TIM_LITE_BASE_ADDR       0x40006000
#define  PRINT_UART_BASE_ADDR     0x40007000
#define  CRC_BASE_ADDR            0x40008000
#define  AFE_COM_BASE_ADDR        0x40009000

// AFE Peripheral
#define  AFE_SYSCFG_BASE_ADDR     0x4000A000
#define  AFE_PINMUX_BASE_ADDR     0x4000A100
#define  AFE_TEST_BASE_ADDR       0x4000A200
#define  AFE_PMU_BASE_ADDR        0x4000A300
#define  AFE_RTC_BASE_ADDR        0x4000A400
#define  AFE_CRG_BASE_ADDR        0x4000A500
#define  ADC_CTRL_BASE_ADDR       0x4000A600
#define  AFE_PWM_BASE_ADDR        0x4000A700
#define  LIN_SCI_BASE_ADDR        0x4000A800

// --------------------------------------------------------
// Reg MAP
#define  EFLASH           ((EFLASH_REG_TypeDef*)           EFLASH_BASE_ADDR)

#define  PMU              ((PMU_REG_TypeDef*)              PMU_BASE_ADDR)
#define  WDG              ((WDG_REG_TypeDef*)              WDG_BASE_ADDR)
#define  TEST             ((TEST_REG_TypeDef *)            TEST_BASE_ADDR)
#define  CRG              ((CRG_REG_TypeDef *)             CRG_BASE_ADDR)
#define  SYSCFG           ((SYSCFG_REG_TypeDef*)           SYSCFG_BASE_ADDR)
#define  PINMUX           ((PINMUX_REG_TypeDef*)           PINMUX_BASE_ADDR)
#define  TIM_LITE         ((TIM_LITE_REG_TypeDef*)         TIM_LITE_BASE_ADDR)
#define  PRINT_UART       ((PRINT_UART_REG_TypeDef*)       PRINT_UART_BASE_ADDR)
#define  CRC              ((CRC_REG_TypeDef *)             CRC_BASE_ADDR)
#define  AFE_COM          ((AFE_COM_REG_TypeDef *)         AFE_COM_BASE_ADDR)

#define  AFE_SYSCFG       ((AFE_SYSCFG_REG_TypeDef *)      AFE_SYSCFG_BASE_ADDR)
#define  AFE_PINMUX       ((AFE_PINMUX_REG_TypeDef*)       AFE_PINMUX_BASE_ADDR)
#define  AFE_TEST         ((AFE_TEST_REG_TypeDef*)         AFE_TEST_BASE_ADDR)
#define  AFE_PMU          ((AFE_PMU_REG_TypeDef*)          AFE_PMU_BASE_ADDR)
#define  RTC              ((RTC_REG_TypeDef*)              AFE_RTC_BASE_ADDR)
#define  AFE_CRG          ((AFE_CRG_REG_TypeDef*)          AFE_CRG_BASE_ADDR)
#define  ADC              ((ADC_REG_TypeDef*)              ADC_CTRL_BASE_ADDR)
#define  AFE_PWM          ((AFE_PWM_REG_TypeDef*)          AFE_PWM_BASE_ADDR)
#define  LIN_SCI          ((LIN_SCI_REG_TypeDef*)          LIN_SCI_BASE_ADDR)

#endif
