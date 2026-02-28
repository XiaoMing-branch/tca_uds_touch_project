/**
 *****************************************************************************
 * @brief   timer driver source file.
 *
 * @file    tcae10_ll_timer.c
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

#include "tcae10_ll_timer.h"
#include "tcae10_ll_cortex.h"

static ISR_FUNC_CALLBACK timer_callback = NULL;

/********************************************************
** \brief   ll_time_clk_config
**
** \param   ll_clk_config_t*    config
**
** \retval  None
*********************************************************/
static void ll_time_clk_config(ll_clk_config_t *config)
{
    CRG_CONFIG_UNLOCK();

    CRG->TIM_LITE_CLKRST_CTRL_F.PCLK_EN_TIM_LITE = 1;                       /* enable pwm pclk */
    CRG->TIM_LITE_CLKRST_CTRL_F.FCLK_EN_TIM_LITE = 1;                       /* enable pwm fclk */
    CRG->TIM_LITE_CLKRST_CTRL_F.FCLK_SEL_TIM_LITE = config->clk_source;     /* pwm fclk source sel */
    CRG->TIM_LITE_CLKRST_CTRL_F.FCLK_DIV_TIM_LITE = config->fclk_div;       /* pwm fclk div */

    CRG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_timer_init
**
** \param   timer_config_t*   config
** \param   FUNC_CALLBACK   callback
**
** \retval  None
*********************************************************/
void ll_timer_init(timer_config_t *config, ISR_FUNC_CALLBACK callback)
{
    //to do assert_param
    ll_timer_deinit();

    ll_time_clk_config(&config->clk_cfg);

    TIM_LITE->CTRL_F.TRIG_EN = config->trigger_mode;
    TIM_LITE->CTRL_F.LOOP_DIS = config->repeat_disable;
    TIM_LITE->INIT_VAL_F.CNT_INIT_VAL = config->initial_value;

    TIM_LITE->IMR_F.CNT_UDF_INT_MSK = (config->isr_cfg.isr_enable) ? 0 : 1; //isr mask config

    // if (config->isr_cfg.isr_enable)
    // {
    //     if (NULL != callback)
    //     {
    //         timer_callback = callback;
    //     }

    //     NVIC_ClearPendingIRQ(TIMER_IRQn);
    //     NVIC_SetPriority(TIMER_IRQn, config->isr_cfg.priority);
    // }
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
    CRG_CONFIG_UNLOCK();
    CRG->TIM_LITE_CLKRST_CTRL_F.RST_TIM_LITE = 1;
    __NOP();
    __NOP();
    CRG->TIM_LITE_CLKRST_CTRL_F.RST_TIM_LITE = 0;
    __NOP();
    __NOP();
    CRG_CONFIG_LOCK();
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
** \brief   ll_timer_trig_enable
**
** \param   bool        enable
**
** \retval  None
*********************************************************/
void ll_timer_trig_enable(bool enable)
{
    TIM_LITE->CTRL_F.CNT_TRIG = (enable) ? 1 : 0;
}

/********************************************************
** \brief   ll_timer_isr_enable
**
** \param   ll_sci_bus_e    bus
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_timer_isr_enable(bool enable)
{
    NVIC_ClearPendingIRQ(TIMER_IRQn);

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
** \brief   ll_timer_isr_get
**
** \param   None
**
** \retval  bool
*********************************************************/
bool ll_timer_isr_get(void)
{
    return (TIM_LITE->ISR_F.CNT_UDF_INT_STATUS);
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
    TIM_LITE->CTRL_F.INIT_VALUE_LD = 1;
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
** \brief   TIMER_IRQHandler
**
** \retval  None
*********************************************************/
//void TIMER_IRQHandler(void)
//{
//   TIM_LITE->ICR_F.CNT_UDF_INT_CLR = TRUE; //clear underflow interrupt

//   if (NULL != timer_callback)
//   {
//       timer_callback(0);
//   }
//}
