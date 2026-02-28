/**
 *****************************************************************************
 * @brief   lpm Source file.
 *
 * @file    tcpl03x_ll_lpm.c
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

#include "tcpl03x_ll_lpm.h"
#include "tcpl03x_ll_cortex.h"

/********************************************************
** \brief   Enter Deep Sleep mode
**
** \param   bool    on_exit：When set to 1, enter sleep mode (Wait-for-Interrupt)
**                            automatically when exiting an exception handler and
**                            returning to thread level.
**                            When set to 0, this feature is disabled.
**
** \retval  None
*********************************************************/
static void ll_lpm_deep_sleep_enter(bool on_exit)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    if (on_exit)
    {
        SCB->SCR |= (0x01 << 1);
    }
    else
    {
        SCB->SCR &= ~(0x01 << 1);
    }

    __WFI();
}

/********************************************************
** \brief   Enter Normal Sleep mode
**
** \param   bool    on_exit：When set to 1, enter sleep mode (Wait-for-Interrupt)
**                            automatically when exiting an exception handler and
**                            returning to thread level.
**                            When set to 0, this feature is disabled.
**
** \retval  None
*********************************************************/
static void ll_lpm_normal_sleep_enter(bool on_exit)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    if (on_exit)
    {
        SCB->SCR |= (0x01 << 1);
    }
    else
    {
        SCB->SCR &= ~(0x01 << 1);
    }

    __WFI();
}

/********************************************************
** \brief   ll_sleep_mode_get
**
** \param   None
**
** \retval  uint8_t
*********************************************************/
uint8_t ll_sleep_mode_get(void)
{
    return (ASYSCFG->SLEEP_MODE & 0x3);
}

/********************************************************
** \brief   Enter Sleep mode
**
** \param   bool    on_exit：When set to 1, enter sleep mode (Wait-for-Interrupt)
**                            automatically when exiting an exception handler and
**                            returning to thread level.
**                            When set to 0, this feature is disabled.
**
** \retval  None
*********************************************************/
void ll_lpm_mcu_enter(sleep_mode_e state, bool on_exit)
{
    ASYSCFG_CONFIG_UNLOCK();

    switch (state)
    {
        case SLEEP_MODE_MAX:
            break;

        case IDLE_MODE:
            ASYSCFG->SLEEP_MODE = SLPMODE_IDLE;
            ll_lpm_normal_sleep_enter(on_exit);
            break;

        case SLEEPWALK_MODE:
            ASYSCFG->SLEEP_MODE = SLPMODE_SLEEPWALK;
            ll_lpm_deep_sleep_enter(on_exit);
            break;

        case SLEEP_MODE:
            ASYSCFG->SLEEP_MODE = SLPMODE_SLEEP;
            ll_lpm_deep_sleep_enter(on_exit);
            break;

        case DEEPSLEEP_MODE:
            ASYSCFG->SLEEP_MODE_F.SLP_MODE = SLPMODE_DEEPSLEEP;
            ll_lpm_deep_sleep_enter(on_exit);
            break;

        default:
            break;
    }

    ASYSCFG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_lpm_afe_enter
**
** \param   sleep_mode_e    mode
**
** \retval  None
*********************************************************/
void ll_lpm_afe_enter(sleep_mode_e mode)
{
    TEST_CONFIG_UNLOCK();

    TEST->TEST_ANA_CTRL_F.TESTMUX_TAO_SEL = 2;
    TEST->TEST_ANA_CTRL_F.TEST_AON = 0;
    TEST->TEST_ANA_CTRL_F.TESTMUX_TO_ADC_EN = 0;
    TEST->TEST_ANA_CTRL_F.TESTMUX_SEL_BUF = 0;
    TEST->TEST_ANA_CTRL_F.TESTMUX_BUF_EN = 0;
    TEST->TEST_ANA_CTRL_F.TESTMUX_TAO_EN = 0;

    TEST_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_pmu_gpio_lowpower
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_pmu_gpio_lowpower(void)
{
    // /* config LED as led */
    PINMUX->LED0_CFG_F.LED0_SRC_SEL = 0;
    PINMUX->LED1_CFG_F.LED1_SRC_SEL = 0;
    PINMUX->LED2_CFG_F.LED2_SRC_SEL = 0;

    /* config gpio */
    // PINMUX->IO2_CFG_F.IO2_SRC_SEL = 0;
}

/********************************************************
** \brief   ll_pmu_ldo_dummy_enable
**
** \param   bool    enable
**
** \retval  None
*********************************************************/
void ll_pmu_ldo_dummy_enable(bool enable)
{
    ASYSCFG->LDO15_CTRL_F.LDO15_DL_SW_ENB = !enable;

    ASYSCFG->LDO15_CTRL_F.LDO15_DL_IBASE_SEL = 0;
    ASYSCFG->LDO33_CTRL_F.LDO33_DL_SW_ENB = !enable;
    ASYSCFG->LDO33_CTRL_F.LDO33_DL_IBASE_SEL = 0;
}
