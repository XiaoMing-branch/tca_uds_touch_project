/**
 *****************************************************************************
 * @brief   uart driver header.
 *
 * @file    tcpl01x_ll_uart.h
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

#ifndef __TCPL01X_LL_ADC_H__
#define __TCPL01X_LL_ADC_H__

#include "tcpl01x_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* ADC int0 */
#define ADC_INT_DONE_FLAG            AFE_SYSCFG_IMR0_ADC_DONE_INT_MSK_MASK                   //Mask ADC done interrupt
/* ADC int1 */
#define ADC_INT_CMP_FLAG             AFE_SYSCFG_IMR1_ADC_CMP_INT_MSK_MASK                    //Mask ADC compare interrupt
#define ADC_INT_FIFO_OVF_FLAG        AFE_SYSCFG_IMR1_ADC_FIFO_OVF_INT_MSK_MASK               //Mask ADC fifo overflow interrupt
#define ADC_INT_FIFO_RDY_FLAG        AFE_SYSCFG_IMR1_ADC_RX_RDY_INT_MSK_MASK                 //Mask ADC fifo data ready interrupt
#define ADC_INT_FIFO_UNF_FLAG        AFE_SYSCFG_IMR1_ADC_FIFO_UNF_INT_MSK_MASK               //Mask ADC fifo underflow interrupt

/* power check int0*/
#define OTP_INT_FLAG                 AFE_SYSCFG_IMR0_OTP_INT_MSK_MASK                        //Mask OTP interrupt
#define VS_LVD_INT_FLAG              AFE_SYSCFG_IMR0_VS_LVD_INT_MSK_MASK                     //Mask VS LVD interrupt

typedef enum
{
    ADC_CHANNEL_TEMP = 0U,
    ADC_CHANNEL_VBAT,
    ADC_CHANNEL_VC0,
    ADC_CHANNEL_VC1,
    ADC_CHANNEL_VC2,
    ADC_CHANNEL_VPN0,
    ADC_CHANNEL_VPN1,
    ADC_CHANNEL_VPN2,
    ADC_CHANNEL_LIN,
    ADC_CHANNEL_MAX,
} adc_channel_e;

/**
  * @brief  ll adc  trigger mode enumeration
  */
typedef enum
{
    TRIG_SOFTWARE        = 0U,
    TRIG_PWM0_RISEEDGE   = 0x01U,
    TRIG_PWM0_FALLEDGE   = 0x02U,
    TRIG_PWM1_RISEEDGE   = 0x04U,
    TRIG_PWM1_FALLEDGE   = 0x08U,
    TRIG_PWM2_RISEEDGE   = 0x10U,
    TRIG_PWM2_FALLEDGE   = 0x20U,
    TRIG_RTC         = 0x40U,
    TRIG_LIN         = 0x80U,
} adc_trig_mode_e;

typedef enum
{
    ADC_VREF_2035 =  0,
    ADC_VREF_1528,
    ADC_VREF_769,
    ADC_VREF_MAX,
} adc_vref_e;

typedef enum
{
    ADC_GAIN1_X2  = 0,
    ADC_GAIN1_X5,
    ADC_GAIN1_X7,
    ADC_GAIN1_X10,
    ADC_GAIN1_X12,
    ADC_GAIN1_X15,
    ADC_GAIN1_X17,
    ADC_GAIN1_X20,
    ADC_GAIN1_MAX,
} adc_gain1_e;

typedef enum
{
    ADC_GAIN2_X1 = 0,
    ADC_GAIN2_X2,
    ADC_GAIN2_X3,
    ADC_GAIN2_X4,
    ADC_GAIN2_X5,
    ADC_GAIN2_X6,
    ADC_GAIN2_X7,
    ADC_GAIN2_X8,
    ADC_GAIN2_MAX,
} adc_gain2_e;

typedef enum
{
    ADC_VCR_365 = 0,
    ADC_VCR_415,
    ADC_VCR_466,
    ADC_VCR_516,
    ADC_VCR_567,
    ADC_VCR_617,
    ADC_VCR_668,
    ADC_VCR_719,
    ADC_VCR_769,
    ADC_VCR_820,
    ADC_VCR_871,
    ADC_VCR_921,
    ADC_VCR_971,
    ADC_VCR_1022,
    ADC_VCR_1073,
    ADC_VCR_1123,
    ADC_VCR_MAX,
} adc_vcr_e;

typedef enum
{
    ADC_VCA_0 = 0,
    ADC_VCA_1V2,
    ADC_VCA_MAX,
} adc_vca_e;

typedef enum
{
    ADC_OP_GAIN0_1 = 0,
    ADC_OP_GAIN0,
    ADC_OP_SEL_MAX,
} adc_op_sel_e;

typedef struct
{
    adc_gain1_e gain1;
    adc_gain2_e gain2;
    adc_vcr_e vcr;
    adc_vca_e vca;
    adc_vref_e vref;
    adc_op_sel_e op_sel;
} adc_cfg_t;

/**
  * @brief  ll adc enumeration
  */
typedef struct
{
    ll_clk_config_t clk_cfg;
    ll_isr_config_t isr_cfg;
    uint8_t trig_num;
    adc_trig_mode_e trig_mode;
} adc_config_t;

void ll_adc_deinit(void);
ll_status_e ll_adc_init(adc_config_t *config, ISR_FUNC_CALLBACK callback);
ll_status_e ll_adc_vref_config(adc_vref_e vref);
ll_status_e ll_adc_gain_config(adc_channel_e channel, adc_cfg_t *config);
ll_status_e ll_adc_isr_enable(bool enable);
ll_status_e ll_adc_lin_aa_enable(lin_aa_type_e type, bool enable);
ll_status_e ll_adc_select_channel(adc_channel_e channel, adc_cfg_t *cfg);
uint8_t ll_adc_fifo_length_get(void);
uint16_t ll_adc_fifo_get(uint16_t *buffer, uint16_t length);
uint16_t ll_adc_fifo_clear(void);
ll_status_e ll_adc_crtl_config(uint32_t *value, bool is_write);
void ll_adc_softwart_start(bool enable);
ll_status_e ll_adc_it_start(bool enable);
ll_status_e ll_adc_volt_calculate_func(int16_t code, adc_cfg_t *cfg, uint16_t *value);
ll_status_e ll_adc_vbat_calculate_func(int16_t code, uint16_t *value);
ll_status_e ll_adc_temp_calculate_func(int16_t code, adc_cfg_t *cfg,  uint16_t *value);
ll_status_e ll_adc_channnel_start(adc_channel_e channel, adc_cfg_t *cfg, uint16_t *buffer, uint8_t trig_num);
ll_status_e ll_adc_tsensor_enable(bool enable);
ll_status_e ll_bias_control_enable(bool enable);

#if defined(__cplusplus)
}
#endif

#endif /* __TCPL01X_LL_ADC_H__ */
