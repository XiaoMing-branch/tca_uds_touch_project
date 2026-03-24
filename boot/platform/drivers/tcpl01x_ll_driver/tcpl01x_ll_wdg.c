/**
 *****************************************************************************
 * @brief   wdg driver source file.
 *
 * @file    tcpl01x_ll_wdg.c
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

#include "tcpl01x_ll_wdg.h"
#include "tcpl01x_ll_cortex.h"

#if 0
#define WDG_UNLCOK()          WDG->LOCK = 0xAAAA5555
#define WDG_LCOK()            WDG->LOCK = 0x12345678
#else
#define WDG_UNLCOK()
#define WDG_LCOK()
#endif

static ISR_FUNC_CALLBACK wdg_callback = NULL;

/********************************************************
** \brief   ll_wdg_init
**
** \param   wdg_config_t*       config
** \param   ISR_FUNC_CALLBACK   callback
**
** \retval  None
*********************************************************/
void ll_wdg_init(wdg_config_t *config, ISR_FUNC_CALLBACK callback)
{
    ll_wdg_deinit();

    CLOCK_CONFIG_UNLOCK();

    CRG->WDG_CLKRST_CTRL = (CRG_WDG_CLKRST_CTRL_PCLK_EN_WDG_SET(1) | CRG_WDG_CLKRST_CTRL_FCLK_DIV_WDG_SET(config->clk_cfg.fclk_div - 1));

    CLOCK_CONFIG_LOCK();

    WDG_UNLCOK();

    WDG->CTRL_F.DBG_STOP = 1;
    WDG->CTRL_F.REO = (config->reset_on_overflow) ? 1 : 0;
    WDG->CNT_MAX_F.MAX_CNT = (config->max_count & 0xFFF);

    WDG_LCOK();

    if (config->isr_cfg.isr_enable)
    {
        if (NULL != callback)
        {
            wdg_callback = callback;
        }

        NVIC_ClearPendingIRQ(IWDG_IRQn);
        NVIC_SetPriority(IWDG_IRQn, config->isr_cfg.priority);
    }
}

/********************************************************
** \brief   ll_wdg_deinit
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_wdg_deinit(void)
{
    NVIC_DisableIRQ(IWDG_IRQn);
    wdg_callback = NULL;

    WDG_UNLCOK();

    WDG->CTRL = 0;
    WDG->CNT_MAX_F.MAX_CNT = 0;

    WDG_LCOK();

    CLOCK_CONFIG_UNLOCK();

    CRG->WDG_CLKRST_CTRL_F.PCLK_EN_WDG = 0;

    CLOCK_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_wdg_isr_enable
**
** \param   bool        enable
**
** \retval  None
*********************************************************/
void ll_wdg_isr_enable(bool enable)
{
    if (enable)
    {
        NVIC_EnableIRQ(IWDG_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(IWDG_IRQn);
    }
}

/********************************************************
** \brief   ll_wdg_enable
**
** \param   bool        enable
**
** \retval  None
*********************************************************/
void ll_wdg_enable(bool enable)
{
    WDG_UNLCOK();

    WDG->CTRL_F.WE = (enable) ? 1 : 0;

    WDG_LCOK();
}

/********************************************************
** \brief   ll_wdg_reload
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_wdg_reload(void)
{
    WDG_UNLCOK();

    WDG->CCR_F.CCR = 1;

    WDG_LCOK();
}

/********************************************************
** \brief   ll_wdg_interrupt_clear
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_wdg_interrupt_clear(void)
{
    WDG_UNLCOK();

    WDG->ICR_F.COI = 1;

    WDG_LCOK();
}

/********************************************************
** \brief   IWDG_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
void IWDG_IRQHandler(void)
{
    ll_wdg_interrupt_clear();
    ll_wdg_reload();

    if (NULL != wdg_callback)
    {
        wdg_callback(0);
    }
}
