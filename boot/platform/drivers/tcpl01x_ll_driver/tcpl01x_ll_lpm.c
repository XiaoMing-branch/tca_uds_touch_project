/**
 *****************************************************************************
 * @brief   lpm Source file.
 *
 * @file    tcpl01x_ll_lpm.c
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

#include "tcpl01x.h"
#include "tcpl01x_ll_lpm.h"
#include "tcpl01x_ll_cortex.h"

#if 0
#define AFE_TEST_LOCK()                                       \
   do {                                                       \
       afe_reg_write(&AFE_TEST->TEST_LOCK, 0x76543210);       \
       } while (0)

#define AFE_TEST_UNLOCK()                                     \
   do {                                                       \
       afe_reg_write(&AFE_TEST->TEST_LOCK, 0xFEDCBA98);       \
       } while (0)
#else
#define AFE_TEST_LOCK()
#define AFE_TEST_UNLOCK()
#endif

#if 0
#define PMU_LOCK_CONFIG()                 (PMU->PMU_LOCK = 0x12345678)
#define PMU_UNLOCK_CONFIG()               (PMU->PMU_LOCK = 0xAAAA5555)
#else
#define PMU_LOCK_CONFIG()
#define PMU_UNLOCK_CONFIG()
#endif

#if 0
#define AFE_PMU_LOCK_CONFIG()                                  \
    do {                                                       \
        afe_reg_write(AFE_PMU->PMU_LOCK, 0x12345678);          \
        } while (0)
#define AFE_PMU_UNLOCK_CONFIG()                                \
    do {                                                       \
        afe_reg_write(AFE_PMU->PMU_LOCK, 0xAAAA5555);          \
        } while (0)
#else
#define AFE_PMU_LOCK_CONFIG()
#define AFE_PMU_UNLOCK_CONFIG()
#endif

/********************************************************
** \brief   ll_lpm_deep_sleep_enter
**
** \param   bool    bOnExit
**
** \retval  None
*********************************************************/
#if defined   ( __ICCARM__   ) /* iar */
#pragma location = "RAMUSERCODE"
#elif defined ( __ARMCC_VERSION )     /* keil */
__attribute__((section("RAMCODE")))
#endif
static void ll_lpm_deep_sleep_enter(bool bOnExit)
{
    //#define SCB_SCR_SLEEPDEEP_Msk              (1UL <<2)
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    if (bOnExit)
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
** \brief   ll_lpm_normal_sleep_enter
**
** \param   bool    bOnExit
**
** \retval  None
*********************************************************/
#if defined   ( __ICCARM__   ) /* iar */
#pragma location = "RAMUSERCODE"
#elif defined ( __ARMCC_VERSION )     /* keil */
__attribute__((section("RAMCODE")))
#endif
static void ll_lpm_normal_sleep_enter(bool bOnExit)
{
    //#define SCB_SCR_SLEEPDEEP_Msk              (1UL <<2)
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

    if (bOnExit)
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
** \brief   ll_sleep_nop_us
**
** \param   uint16_t            us
**
** \retval  None
*********************************************************/
static void ll_sleep_nop_us(uint16_t us)
{
    while (us--)
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
    }
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
    return (PMU->SLEEPMODE & 0x3);
}

/********************************************************
** \brief   ll_lpm_mcu_enter
**
** \param   sleep_mode_e        state
** \param   bool                bOnExit
**
** \retval  None
*********************************************************/
void ll_lpm_mcu_enter(sleep_mode_e state, bool bOnExit)
{
    PMU_UNLOCK_CONFIG();

    switch (state)
    {
        case SLEEP_MODE_MAX:
            break;

        case IDLE_MODE:
            PMU->SLEEPMODE = SLPMODE_IDLE;
            ll_lpm_normal_sleep_enter(bOnExit);
            break;

        case SLEEPWALK_MODE:
            PMU->SLEEPMODE = SLPMODE_SLEEPWALK;
            ll_lpm_deep_sleep_enter(bOnExit);
            break;

        case SLEEP_MODE:
            PMU->SLEEPMODE = SLPMODE_SLEEP;
            ll_lpm_deep_sleep_enter(bOnExit);
            break;

        case DEEPSLEEP_MODE:
            PMU->SLEEPMODE = SLPMODE_DEEPSLEEP;
            ll_lpm_deep_sleep_enter(bOnExit);
            break;

        default:
            break;
    }

    PMU_LOCK_CONFIG();
}

/********************************************************
** \brief   ll_lpm_afe_enter
**
** \param   sleep_mode_e        mode
**
** \retval  None
*********************************************************/
void ll_lpm_afe_enter(sleep_mode_e mode)
{
    AFE_PMU_UNLOCK_CONFIG();

    /* afe sleepwalk 0x02 deepsleep 0x03 */
    afe_reg_write(&AFE_PMU->SLEEPMODE, mode);

    /* software request for sleep, Rising edge:200us */
    afe_reg_write(&AFE_PMU->PMU_CTRL, 0x00);
    ll_sleep_nop_us(200);
    afe_reg_write(&AFE_PMU->PMU_CTRL, 0x01);
    ll_sleep_nop_us(100);

    AFE_PMU_LOCK_CONFIG();
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
    uint32_t reg_val;

    /*LDO15 trim config*/
    AFE_TEST_UNLOCK();
    reg_val = 0x00;
    afe_reg_write(&AFE_TEST->TEST_LDO15_TRIM, reg_val);
    AFE_TEST_LOCK();

    // /* config AFE pinmux as led */
    // reg_val = 0x01;
    // afe_reg_write(&AFE_PINMUX->OUT0_CFG, reg_val);
    // afe_reg_write(&AFE_PINMUX->OUT1_CFG, reg_val);
    // afe_reg_write(&AFE_PINMUX->OUT2_CFG, reg_val);

    /* config gpio */
    // reg_val = AFE_PINMUX_IO3_CFG_IO3_SRC_SEL_SET(1);

    // reg_val |= (AFE_PINMUX_IO3_CFG_IO3_IE_SET(1)        |
    //             AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_SET(1)  |
    //             AFE_PINMUX_IO3_CFG_IO3_PD_SET(1));
    // afe_reg_write(&AFE_PINMUX->IO3_CFG, reg_val);

    /* config auto adress fuction */
    reg_val = 0x00;
    afe_reg_write(&LIN_SCI->AUTO_ADDR_CTRL, reg_val);

    /* config LP_ctrl register */
    PINMUX->PIN_LP_CTRL |= (PINMUX_PIN_LP_CTRL_SWD_CLK_PD_DIS_SET(1) |
                            PINMUX_PIN_LP_CTRL_SWD_DI_PU_DIS_SET(1)  |
                            PINMUX_PIN_LP_CTRL_VS_PORB_PU_DIS_SET(1) |
                            PINMUX_PIN_LP_CTRL_AFE_INT_PD_DIS_SET(1));
}
