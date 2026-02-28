/**
 *****************************************************************************
 * @brief   gpio driver header file.
 *
 * @file    gpio.h
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
#ifndef __TCPL01X_LL_GPIO_H__
#define __TCPL01X_LL_GPIO_H__

#include "tcpl01x_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
 * @brief  gpio pin enumeration
 */
typedef enum
{
    GPIO_PIN_0 = 0,
    GPIO_PIN_MAX,
} gpio_pin_e;

/**
 * @brief  gpio mode enumeration
 */
typedef enum
{
    GPIO_MODE_IN_PP = 0,
    GPIO_MODE_OUT_PP,
    GPIO_MODE_OUT_OD = GPIO_MODE_IN_PP,
    GPIO_MODE_IN_OD = GPIO_MODE_OUT_PP,
} gpio_mode_e;

/**
 * @brief  gpio pull mode enumeration
 */
typedef enum
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_DOWN,
    GPIO_PULL_UP,
} gpio_pull_mode_e;

/**
 * @brief  gpio pull down type enumeration
 */
typedef enum
{
    GPIO_PULLDOWN_SWANDHW = 0,  /*!< GPIO Pull down is controlled by Outx_pd and hardware together*/
    GPIO_PULLDOWN_SW_ONLY,          /*!< GPIO Pull down is controlled by Outx_pd only*/
} gpio_pull_down_type;

typedef enum
{
    GPIO_TRIGGER_NULL = 0,
    GPIO_TRIGGER_FALLING_EDGE,        /*interrupt is active only on the falling edge*/
    GPIO_TRIGGER_RISING_EDGE,         /*interrupt is active only on the rising edge*/
} gpio_trigger_flag_e;

/**
 * @brief  gpio afio type enumeration
 *
 */
typedef enum
{
    AFIO_MUX_0 = 0,
    AFIO_MUX_1,
} gpio_afio_mux_e;


/**
  * @defgroup GPIO_Configuration struct
  */
typedef struct
{
    gpio_pin_e gpio_pin;                                    /*!< Specifies GPIO PIN it can be any value of @ref gpio_pin_e */
    gpio_mode_e mode;                           /*!< Specifies GPIO mode  it can be any value of @ref gpio_mode_e */
    gpio_pull_mode_e pull_mode;                     /*!< Specifies GPIO Pull mode it can be any value of @ref gpio_pull_mode_e */
    gpio_pull_down_type pull_down_type;   /*!< Specifies the pull-down type for the GPIO it can be any value of @ref gpio_pull_down_type */
    gpio_afio_mux_e afio;                 /*!< Specifies the alternate function for the gpio it can be any value of @ref gpio_afio_mux_e */
    gpio_trigger_flag_e trigger_flag;
} gpio_config_t;


void ll_gpio_deinit(void);
void ll_gpio_init(gpio_config_t *config, ISR_FUNC_CALLBACK callback);
bool ll_gpio_read(gpio_pin_e gpio_pin);
void ll_gpio_output(gpio_pin_e gpio_pin, bool state);
void ll_gpio_toggle(gpio_pin_e gpio_pin);
void ll_gpio_isr_enable(gpio_pin_e gpio_pin, bool enable);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_GPIO_H__ */
