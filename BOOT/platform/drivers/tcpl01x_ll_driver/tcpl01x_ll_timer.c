/**
 *****************************************************************************
 * @brief       timer driver source file.
 *
 * @file        tcpl01x_ll_timer.c
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

#include "tcpl01x_ll_timer.h"
#include "tcpl01x_ll_cortex.h"

static ISR_FUNC_CALLBACK timer_callback = NULL;

/********************************************************
** \brief   ll_timer_init
**
** \param   timer_config_t*     config
** \param   ISR_FUNC_CALLBACK   callback
**
** \retval  None
*********************************************************/
void ll_timer_init(timer_config_t *config, ISR_FUNC_CALLBACK callback)
{
    ll_timer_deinit();

    CLOCK_CONFIG_UNLOCK();

    /* Timer_FCLK = Sourece_CLK / fclk_divider */
    CRG->TIM_CLKRST_CTRL_F.FCLK_SEL_TIM = config->clk_cfg.clk_source;

    if (config->clk_cfg.fclk_div)
    {
        CRG->TIM_CLKRST_CTRL_F.FCLK_DIV_TIM = config->clk_cfg.fclk_div - 1;
        CRG->TIM_CLKRST_CTRL_F.FCLK_EN_TIM = 1;
    }
    else
    {
        CRG->TIM_CLKRST_CTRL_F.FCLK_EN_TIM = 0;
    }

    CLOCK_CONFIG_LOCK();

    TIM_LITE->PRESCALE_F.PRESCALE       = config->prescale - 1;
    TIM_LITE->INIT_VAL_F.CNT_INIT_VAL   = config->initial_value;
    TIM_LITE->CTRL_F.LOOP_DIS           = (config->repeat_disable) ? 1 : 0;
    TIM_LITE->CTRL_F.PRE_AUTO_LD_EN     = (config->prescale_autoload) ? 1 : 0;
    TIM_LITE->CTRL_F.CNT_AUTO_LD_EN     = (config->repeat_count_autoload) ? 1 : 0;
    TIM_LITE->REPEAT_F.REPEAT_NUM       = config->repeat_counts;
    TIM_LITE->CTRL_F.INIT_VALUE_LD      = (config->init_value_autoload) ? 0 : 1;

    TIM_LITE->IMR_F.CNT_UDF_INT_MSK = (config->isr_cfg.isr_enable) ? 0 : 1; //isr mask config

    if (config->isr_cfg.isr_enable)
    {
        if (NULL != callback)
        {
            timer_callback = callback;
        }

        NVIC_ClearPendingIRQ(TIMER_IRQn);
        NVIC_SetPriority(TIMER_IRQn, config->isr_cfg.priority);
    }
}

/********************************************************
** \brief   ll_timer_deinit
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_timer_deinit(void)
{

    NVIC_DisableIRQ(TIMER_IRQn);
    timer_callback = NULL;
    TIM_LITE->PRESCALE_F.PRESCALE       = 0;
    TIM_LITE->INIT_VAL_F.CNT_INIT_VAL   = 0;
    TIM_LITE->CTRL_F.LOOP_DIS           = 0;
    TIM_LITE->CTRL_F.PRE_AUTO_LD_EN     = 0;
    TIM_LITE->CTRL_F.CNT_AUTO_LD_EN     = 0;
    TIM_LITE->REPEAT_F.REPEAT_NUM       = 0;
    TIM_LITE->CTRL_F.INIT_VALUE_LD      = 0;
}

/********************************************************
** \brief   ll_timer_enable
**
** \param   bool        enable
**
** \retval  None
*********************************************************/
void ll_timer_enable(bool enable)
{
    TIM_LITE->CTRL_F.EN = (enable) ? 1 : 0;
}

/********************************************************
** \brief   ll_timer_isr_enable
**
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_timer_isr_enable(bool enable)
{
    if (enable)
    {
        NVIC_EnableIRQ(TIMER_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(TIMER_IRQn);
    }

    return LL_OK;
}

/********************************************************
** \brief   Sets the intial counter value
**
** \param   uint16_    intial counter value
**
** \retval  None
*********************************************************/
void ll_timer_counter_set(uint16_t value)
{
    TIM_LITE->INIT_VAL_F.CNT_INIT_VAL = value;
}

/********************************************************
** \brief   Gets the current counter value
**
** \param   None
**
** \retval  uint16_t    value:current counter value
*********************************************************/
uint16_t ll_timer_counter_get(void)
{
    return TIM_LITE->CNT_VAL_F.CNT_VAL;
}

/********************************************************
** \brief   Sets the repeates number value
**
** \param   uint8_t    intial counter value
**
** \retval  None
*********************************************************/
void ll_timer_repeat_num_set(uint8_t value)
{
    TIM_LITE->REPEAT_F.REPEAT_NUM = value;
}

/********************************************************
** \brief   Gets the current repeaset number value
**
** \param   None
**
** \retval  uint8_t     value:urrent repeaset number value
*********************************************************/
uint8_t ll_timer_repeat_num_get(void)
{
    return TIM_LITE->RPT_CNT_VAL_F.RPT_CNT_VAL;
}

/********************************************************
** \brief   TIMER_IRQHandler
**
** \retval  None
*********************************************************/
void TIMER_IRQHandler(void)
{
    TIM_LITE->ICR_F.CNT_UDF_INT_CLR = 1; //clear underflow interrupt

    if (NULL != timer_callback)
    {
        timer_callback(0);
    }

}
