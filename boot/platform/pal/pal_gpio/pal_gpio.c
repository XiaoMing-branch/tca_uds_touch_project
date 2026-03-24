/**
 *****************************************************************************
 * @brief   pal gpio source file.
 *
 * @file    pal_gpio.c
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

#include "pal_gpio.h"

#if defined (__TCPL03X__)

/********************************************************
** \brief   pal_gpio_read
**
** \param   gpio_pin_e  gpio_pin
**
** \retval  bool        true for false
*********************************************************/
bool pal_gpio_read(gpio_pin_e gpio_pin)
{
    return ll_gpio_read(gpio_pin);
}

/********************************************************
** \brief   pal_gpio_output
**
** \param   gpio_pin_e  gpio_pin
** \param   bool        state:true-H_LEVEL, false-L_LEVEL
**
** \retval  None
*********************************************************/
void pal_gpio_output(gpio_pin_e gpio_pin, bool state)
{
    ll_gpio_output(gpio_pin, state);
}

/********************************************************
** \brief   pal_gpio_toggle
**
** \param   gpio_pin_e  gpio_pin
**
** \retval  None
*********************************************************/
void pal_gpio_toggle(gpio_pin_e gpio_pin)
{
    ll_gpio_toggle(gpio_pin);
}

/********************************************************
** \brief   pal_gpio_init
**
** \param   gpio_config_t               config
** \param   ISR_FUNC_CALLBACK           callback
**
** \retval  None
*********************************************************/
void pal_gpio_init(gpio_config_t *cfg, ISR_FUNC_CALLBACK callback)
{
    ll_gpio_init(cfg, callback);

    if (cfg->trigger_flag)
    {
        ll_gpio_isr_enable(cfg->gpio_pin, true);
    }
}
#endif
