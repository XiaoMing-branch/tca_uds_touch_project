/**
 *****************************************************************************
 * @brief   bootloader example source file.
 *
 * @file    app.c
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

#include "system_tcpl03x.h"
#include "tcpl03x.h"
#include "pal_systick.h"
#include "pal_func_def.h"
#include "dfu_uds_manager.h"

static void DoorGpioInit(void)
{
    ll_gpio_output(GPIO_PIN_1, false);

    gpio_config_t cfg;
    cfg.gpio_pin = GPIO_PIN_1;
    cfg.mode = GPIO_MODE_OUT_PP;
    cfg.afio = AFIO_MUX_1;
    ll_gpio_init(&cfg, NULL);
    ll_gpio_output(GPIO_PIN_1, false);
}

int TcMain(void)
{
    interrupt_disable();
    //DoorGpioInit();
    dfu_manager_init();
    interrupt_enable();

    while (1)
    {
        main_loops();
    }
}
