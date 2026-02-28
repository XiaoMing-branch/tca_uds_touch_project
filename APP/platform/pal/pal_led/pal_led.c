/**
 *****************************************************************************
 * @brief   pal led source file.
 *
 * @file    pal_led.c
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

#include "pal_led.h"
#include "app.h"

/**
* @brief 静态pn结电压检测频率
*/
#define LED_STATIC_SAMPLE_FREQ   0X4FFF
/**
* @brief LED正常驱动频率
*/
#define LED_DRIVER_PWM_FREQ      0XFFFF

extern void  pwm_callback_handle(uint32_t isr);

led_control_instance_t *led_ctrl_instance[LED_CHANNLE_MAX];

__attribute__((weak)) void pwm_callback_handle(uint32_t isr)
{
    //do noting
}

/**
* @brief led0 ctrl instance
*/
led_control_instance_t led0_ctrl_instance =
{
    .channel.rgb = { LED_CH_R, LED_CH_G, LED_CH_B },
    .current =
    {
        .driver = LED_DRIVER_30MA,
#ifdef __TCPL01X__
        .diagnose = LED_DIAG_1000UA,
#endif
    },
    .callback = pwm_callback_handle,
};

/**
* @brief led pwm config
*/
pwm_config_t config =
{
    .clk_cfg = {
        .clk_source = FCLK_SRC_48M,
        .fclk_div = 0,
    },
    .isr_cfg = {
        .isr = PWM_INIT_FLAG,
        .isr_enable = true,
    },
    .out_mode = PWM_MODE_INDEPENDENT,
    .polarity = PWM_POLARITY_HIGH,
    .hvio_mode = HVIO_MODE_LED,
    .period = LED_DRIVER_PWM_FREQ,
};

/********************************************************
** \brief   pal_led_init
**
** \param   led_channel_e               channel
** \param   led_control_instance_t*     instance
**
** \retval  None
*********************************************************/
void pal_led_init(led_channel_e channel, led_control_instance_t *instance)
{

    if (NULL == instance)
    {
        return;
    }

    ll_pwm_init((ll_pwm_bus_e)channel, &config, instance->callback);

    for (uint8_t i = 0; i < 3; i++)
    {
#ifdef __TCPL01X__
        ll_led_diag_current_config((pwm_channel_e)instance->channel.rgb[i], (led_diag_current_e)instance->current.diagnose);
#endif
        ll_led_driver_current_config((pwm_channel_e)instance->channel.rgb[i], (led_driver_current_e)instance->current.driver);
    }

    led_ctrl_instance[channel] = instance;
}

/********************************************************
** \brief   pal_led_current_set
**
** \param   led_channel_e               channel
** \param   uint8_t                     current
**
** \retval  None
*********************************************************/
void pal_led_current_set(led_channel_e channel, uint8_t current)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance)
    {
        return;
    }

    for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
    {
        ll_led_driver_current_config((pwm_channel_e)instance->channel.rgb[rgb], (led_driver_current_e)current);
    }

    instance->current.driver = current;
}

/********************************************************
** \brief   pal_led_current_get
**
** \param   led_channel_e               channel
** \param   uint8_t*                    current
**
** \retval  None
*********************************************************/
void pal_led_current_get(led_channel_e channel, uint8_t *current)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance)
    {
        return;
    }

    *current = instance->current.driver;
}

/********************************************************
** \brief   pal_led_dutcycle_set
**
** \param   led_channel_e               channel
** \param   uint16_t*                   duty_cycle
**
** \retval  None
*********************************************************/
void pal_led_dutcycle_set(led_channel_e channel, uint16_t *duty_cycle)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance || NULL == duty_cycle)
    {
        return;
    }

    for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
    {
        ll_pwm_channel_threshold_config((pwm_channel_e)instance->channel.rgb[rgb], duty_cycle[rgb], 0);
    }
}

/********************************************************
** \brief   pal_led_dutcycle_set
**
** \param   led_channel_e               channel
** \param   uint16_t*                   duty_cycle
**
** \retval  None
*********************************************************/
void pal_led_dutcycle_get(led_channel_e channel, uint16_t *duty_cycle)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance || NULL == duty_cycle)
    {
        return;
    }

    for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
    {
        ll_pwm_high_threshold_get((pwm_channel_e)instance->channel.rgb[rgb], &duty_cycle[rgb]);
    }
}

/********************************************************
** \brief   pal_led_enable
**
** \param   led_channel_e               channel
** \param   bool                        enable
**
** \retval  None
*********************************************************/
void pal_led_enable(led_channel_e channel, bool enable)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance)
    {
        return;
    }

    ll_pwm_enable(HVIO_MODE_LED, enable);
    instance->is_open = enable;
}

/********************************************************
** \brief   pal_led_break
**
** \param   led_channel_e               channel
** \param   bool                        enable
**
** \retval  None
*********************************************************/
void pal_led_break(led_channel_e channel, bool enable)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance)
    {
        return;
    }

    ll_pwm_break_set(enable);
}

/********************************************************
** \brief   pal_led_static_pnvolt_set
**
** \param   led_channel_e               channel
** \param   bool                        enable
**
** \retval  None
*********************************************************/
void pal_led_static_pnvolt_set(led_channel_e channel, bool enable)
{
    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance)
    {
        return;
    }

    if (enable != instance->static_sample.valid)
    {
        instance->static_sample.valid = enable;

        if (enable)
        {
            if (!instance->is_open)
            {

                for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
                {
                    ll_pwm_high_threshold_get((pwm_channel_e)instance->channel.rgb[rgb], &instance->static_sample.duty_cycle[rgb]);
                    ll_pwm_channel_threshold_config((pwm_channel_e)instance->channel.rgb[rgb], 0, 0);
                }
            }

        }
        else
        {
            if (instance->is_open)
            {
                for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
                {
                    ll_pwm_channel_threshold_config((pwm_channel_e)instance->channel.rgb[rgb], instance->static_sample.duty_cycle[rgb], 0);
                }
            }
        }

        uint32_t pwm_freq = (enable && !instance->is_open) ? LED_STATIC_SAMPLE_FREQ : LED_DRIVER_PWM_FREQ;

        for (rgb_type_e rgb = RGB_RED; rgb < RGB_TYPE_MAX; rgb++)
        {
            ll_pwm_channel_period_config((pwm_channel_e)instance->channel.rgb[rgb], pwm_freq);
        }

        if (!instance->is_open)
        {
            ll_pwm_enable(HVIO_MODE_LED, true);
        }
    }
}

/********************************************************
** \brief   pal_led_channel_mux_get
**
** \param   led_channel_e               channel
** \param   uint8_t**                   channel_mux
**
** \retval  None
*********************************************************/
void pal_led_channel_mux_get(led_channel_e channel, uint8_t **channel_mux)
{

    led_control_instance_t *instance = led_ctrl_instance[channel];

    if (NULL == instance)
    {

        return;
    }

    *channel_mux = instance->channel.rgb;
}
