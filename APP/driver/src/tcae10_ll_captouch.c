/**
  ******************************************************************************
  * @brief   captouch  driver source file..
  *
  * @file   captouch.c
  * @author AE/FAE team
  * @date
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <b>&copy; Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd.</b>
  *
  ******************************************************************************
  */

#include "tcae10_ll_captouch.h"


/**
  * @brief  This function enables touch interrupt
  * @param  touch_int the interrupt to be enabled, this value can be one or
  *         combination of @ref captouch interrupt Definitions
  * @retval None
  */
void CapTouch_InterruptEnable(uint8_t touch_int)
{
    CAPTOUCH->IMR &= ~(touch_int);
}

/**
  * @brief  This function disable touch interrupt
  * @param  touch_int the interrupt to be enabled, this value can be one or
  *         combination of @ref captouch interrupt Definitions
  * @retval None
  */
void CapTouch_InterruptDisable(uint8_t touch_int)
{
    CAPTOUCH->IMR |= touch_int;
}
/**
  * @brief  This function clear touch interrupt
  * @param  touch_int the interrupt to be enabled, this value can be one or
  *         combination of @ref captouch interrupt Definitions
  * @retval None
  */
void CapTouch_InterruptClear(uint8_t touch_int)
{
    CAPTOUCH->ICR |= touch_int;
}
/**
  * @brief  This function enables or disables touch
  * @param  state specifies the new state of touch, can be ENABLE or DISABLE
  * @retval None
  */
void CapTouch_Enable(FunctionalState state)
{
    CAPTOUCH->CTRL1_F.CAPTOUCH_EN = (state ? 1 : 0);
}
/**
  * @brief  This function touch software trigger
  * @param  None
  * @retval None
  */
void CapTouch_SoftwareTrig(void)
{
    CAPTOUCH->CTRL0_F.SW_TRIG = 1;
}

/**
  * @brief  This function set touch hopping
  * @param  [in]:period:  0 - 7
  * @retval None
  */
void CapTouch_Hopping(uint8_t period)
{
    uint8_t i;
    uint8_t shift_cnt = 0;

    CAPTOUCH->CTRL4 &= ~((uint32_t)0x7U << (period * 3));
    for (i = 0; i <= period; ++i)            //set hop cnt : 0,1,2,3...，修正最高hop_cnt值为0的bug
    {
        CAPTOUCH->CTRL4 &= ~((uint32_t)0x7U << (i * 3));
        shift_cnt = i * 3;
        CAPTOUCH->CTRL4 |= ((uint32_t)i << shift_cnt);
    }
    CAPTOUCH->CTRL4_F.HOP_PERIOD = period;
}

/**
  * @brief  This function gets the status of a specified adc interrupt flag
  * @param  adc_int the interrupt to read status, this value can be one or
  *          combination of @ref ADC_INTERRUPT_Definitions
  * @retval returns the specified flag's status
  */
bool CapTouch_InterruptStatusGet(uint8_t touch_int)
{
    return (ADC->ISR & (touch_int)) ;
}

/**
  * @brief  This function initialize touch
  * @param  config  a pointer to the touch configuration struct
  * @retval None
  */
void CapTouch_Init(CapTouch_InitConfig_t *touch_cfg)
{
    /*CTRL0*/
    CAPTOUCH->CTRL0_F.CAL_SEL = touch_cfg->Calibration_Sel;
    CAPTOUCH->CTRL0_F.SHLD_I = touch_cfg->Shield_Iout;
    CAPTOUCH->CTRL0_F.SHLD_SEL = touch_cfg->Shield_Sel;
    CAPTOUCH->CTRL0_F.CHNL_SEL = touch_cfg->Channel_Sel;
    /*CTRL1*/
    CAPTOUCH->CTRL1_F.SAMP_OVF_TIME = touch_cfg->Sample_Ovf_Time;
    CAPTOUCH->CTRL1_F.SAMP_OVF_EN = touch_cfg->Sample_Ovf_Enable;
    CAPTOUCH->CTRL1_F.TRAN_LOOP = touch_cfg->Transfer_Loop;
    CAPTOUCH->CTRL1_F.TW_TRIG_EN = touch_cfg->Tinywork_Trigger_Enable;
    CAPTOUCH->CTRL1_F.TRIG_ADC_EN = touch_cfg->Trigger_adc_en;
    CAPTOUCH->CTRL1_F.DSTSW_DIS = touch_cfg->dstsw_dis;
    CAPTOUCH->CTRL1_F.CMP_EN = touch_cfg->cmp_en;
    CAPTOUCH->CTRL1_F.SHLD_EN = touch_cfg->shld_en;
    CAPTOUCH->CTRL1_F.CREF_SEL = touch_cfg->cref_sel;
    CAPTOUCH->CTRL1_F.CAPTOUCH_MODE = touch_cfg->Captouch_Mode;
    /*CTRL2*/
    CAPTOUCH->CTRL2_F.INIT_TIME = touch_cfg->Init_time;
    CAPTOUCH->CTRL2_F.TRAN_TIME = touch_cfg->tran_time;
    CAPTOUCH->CTRL2_F.CHG_TIME = touch_cfg->chg_time;
    /*CTRL3*/
    CAPTOUCH->CTRL3_F.IDAC_INP = touch_cfg->idac_inp;
    CAPTOUCH->CTRL3_F.IDAC_INN = touch_cfg->idac_inn;
    CAPTOUCH->CTRL3_F.SW_IDAC_SEL_P = touch_cfg->sw_idac_sel_p;
    CAPTOUCH->CTRL3_F.SW_IDAC_SEL_N = touch_cfg->sw_idac_sel_n;
    CAPTOUCH->CTRL3_F.IDAC_EN = touch_cfg->idac_en;

}



