/**
 *****************************************************************************
 * @brief   gpio driver source file.
 *
 * @file    tcpl01x_ll_gpio.c
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

#include "tcpl01x_ll_gpio.h"

static ISR_FUNC_CALLBACK gpio_isr_callback = NULL;

/********************************************************
** \brief   ll_gpio_init
**
** \param   gpio_mode_e     config
** \param   gpio_pull_e     pull_mode
**
** \retval  None
*********************************************************/
void ll_gpio_init(gpio_config_t *config, ISR_FUNC_CALLBACK callback)
{
    uint32_t reg_val = 0;

    AFE_CLOCK_CONFIG_UNLOCK();

    afe_bit_set(&AFE_CRG->GPIO_CLKRST_CTRL, AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT);
    afe_bit_clear(&AFE_CRG->GPIO_CLKRST_CTRL, AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT);

    reg_val = (AFE_CRG_GPIO_CLKRST_CTRL_FCLK_EN_GPIO_SET(1) | AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_SET(0));
    afe_reg_write(&AFE_CRG->GPIO_CLKRST_CTRL, reg_val);

    AFE_CLOCK_CONFIG_LOCK();

    reg_val = config->afio;

    if (GPIO_MODE_IN_PP == config->mode)
    {
        reg_val |= AFE_PINMUX_IO3_CFG_IO3_IE_SET(1);
    }
    else
    {
        reg_val &= AFE_PINMUX_IO3_CFG_IO3_IE_CLR;
    }

    if (GPIO_PULLDOWN_SWANDHW == config->pull_down_type)
    {
        reg_val &= AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_CLR;
    }
    else
    {
        reg_val |= AFE_PINMUX_IO3_CFG_IO3_PULL_SEL_SET(1);       //bit 4 : (1 pull dir control by software)
    }


    if (GPIO_PULL_DOWN == config->pull_mode) //pull down
    {
        reg_val &= AFE_PINMUX_IO3_CFG_IO3_PU_CLR;            //pull up disable
        reg_val |= AFE_PINMUX_IO3_CFG_IO3_PD_SET(1);         //bit 6 :software pull down

    }
    else if (GPIO_PULL_UP == config->pull_mode) //pull up
    {
        reg_val &= AFE_PINMUX_IO3_CFG_IO3_PD_CLR;
        reg_val |= AFE_PINMUX_IO3_CFG_IO3_PU_SET(1);
    }
    else//none
    {
        reg_val &= AFE_PINMUX_IO3_CFG_IO3_PU_CLR;            //bit 5 : pull up disable
        reg_val &= AFE_PINMUX_IO3_CFG_IO3_PD_CLR;            //bit 6 : pull down disable
    }

    afe_reg_write(&AFE_PINMUX->IO3_CFG, reg_val);

    AFE_SYSCFG_UNLOCK();

    afe_reg_read(&AFE_SYSCFG->GPIO_CTRL, &reg_val);

    if (GPIO_MODE_IN_PP == config->mode)
    {
        reg_val |= AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_CLR_SET(1);    // bit 2 : 1
        reg_val &= AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_SET_CLR;       // bit 1 : 0

        if (GPIO_TRIGGER_NULL != config->trigger_flag)
        {
            if (GPIO_TRIGGER_FALLING_EDGE == config->trigger_flag)  //falling edge
            {
                reg_val |= AFE_SYSCFG_GPIO_CTRL_GPIO_INT_TYP_SEL_SET(1);//bit 5 : (0 : rising edge , 1 : falling edge)
                reg_val &= AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_CLR;
            }
            else
            {
                reg_val &= AFE_SYSCFG_GPIO_CTRL_GPIO_INT_TYP_SEL_CLR;    //bit 5 : (0 : rising edge , 1 : falling edge)
                reg_val |= AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_SET(1);    //bit 4 : 1 : reverse gpio in  0: use gpio in
            }

            afe_syscfg_int_flag_clear(0, AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK);
            gpio_isr_callback = callback;
        }
        else
        {
            reg_val |= AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_SET(1);  /* reverse gpio_in */
        }
    }
    else
    {

        reg_val &= AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_CLR_CLR;
        reg_val |= AFE_SYSCFG_GPIO_CTRL_GPIO_OUTEN_SET_SET(1);

        /* Output mode, Interrupt set default value */
        reg_val &= AFE_SYSCFG_GPIO_CTRL_GPIO_INT_POL_SEL_CLR;
    }

    afe_reg_write(&AFE_SYSCFG->GPIO_CTRL, reg_val);

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   ll_gpio_deinit
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_gpio_deinit(void)
{
    AFE_CLOCK_CONFIG_UNLOCK();

    afe_bit_set(&AFE_CRG->GPIO_CLKRST_CTRL, AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT);
    afe_bit_clear(&AFE_CRG->GPIO_CLKRST_CTRL, AFE_CRG_GPIO_CLKRST_CTRL_RST_GPIO_SHIFT);
    afe_reg_write(&AFE_CRG->GPIO_CLKRST_CTRL, 0);

    AFE_CLOCK_CONFIG_LOCK();

    afe_reg_write(&AFE_PINMUX->IO3_CFG, 0);

}

/********************************************************
** \brief   ll_gpio_read
**
** \param   gpio_pin_e  gpio_pin
**
** \retval  bool        true for false
*********************************************************/
bool ll_gpio_read(gpio_pin_e gpio_pin)
{
    uint32_t reg_val;

    if (gpio_pin >= GPIO_PIN_MAX)
    {
        return false;
    }

    afe_reg_read(&AFE_SYSCFG->GPIO_CTRL, &reg_val);

    return (!!(reg_val & AFE_SYSCFG_GPIO_CTRL_GPIO_DATAIN_MASK));
}

/********************************************************
** \brief   ll_gpio_output
**
** \param   gpio_pin_e  gpio_pin
** \param   bool        state:true-H_LEVEL, false-L_LEVEL
**
** \retval  None
*********************************************************/
void ll_gpio_output(gpio_pin_e gpio_pin, bool state)
{
    if (gpio_pin >= GPIO_PIN_MAX)
    {
        return;
    }

    AFE_SYSCFG_UNLOCK();

    if (state)
    {
        afe_bit_set(&AFE_SYSCFG->GPIO_CTRL, AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_SHIFT);
    }
    else
    {
        afe_bit_clear(&AFE_SYSCFG->GPIO_CTRL, AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_SHIFT);
    }

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   ll_gpio_toggle
**
** \param   gpio_pin_e  gpio_pin
**
** \retval  None
*********************************************************/
void ll_gpio_toggle(gpio_pin_e gpio_pin)
{

    uint32_t reg_val = 0;

    if (gpio_pin >= GPIO_PIN_MAX)
    {
        return;
    }

    AFE_SYSCFG_UNLOCK();

    afe_reg_read(&AFE_SYSCFG->GPIO_CTRL, &reg_val);

    if (reg_val & AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_MASK)
    {
        reg_val &= AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_CLR;
    }
    else
    {
        reg_val |= AFE_SYSCFG_GPIO_CTRL_GPIO_DATAOUT_SET(1);
    }

    afe_reg_write(&AFE_SYSCFG->GPIO_CTRL, reg_val);

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   ll_gpio_isr_enable
**
** \param   gpio_pin_e  gpio_pin
** \param   bool        enable
**
** \retval  None
*********************************************************/
void ll_gpio_isr_enable(gpio_pin_e gpio_pin, bool enable)
{
    afe_syscfg_int_flag_clear(0, AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK);

    if (enable)
    {
        afe_syscfg_int_enable(0, AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK); //enable isr_falg
    }
    else
    {
        afe_syscfg_int_disable(0, AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK); //disable isr_falg
    }
}

/********************************************************
** \brief   GPIO_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
__attribute__((section("RAMCODE")))
void GPIO_IRQHandler(uint32_t isr0, uint32_t isr1)
{
    if (0 != (isr1 & AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK))
    {
        afe_syscfg_int_flag_clear(0, AFE_SYSCFG_IMR1_GPIO_INT_MSK_MASK);

        if (gpio_isr_callback)
        {
            gpio_isr_callback(isr1 >> AFE_SYSCFG_IMR1_GPIO_INT_MSK_SHIFT);
        }
    }
}
