/**
*****************************************************************************
* @brief  touch tool source
* @file   touch_tool.c
* @author AE/FAE team
* @date   28/JUL/2023
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <b>&copy; Copyright (c) 2023 Tinychip Microelectronics Co.,Ltd.</b>
*
*****************************************************************************
*/

#include "string.h"
#include "touch_tool.h"
#include "tcae10_ll_def.h"
#include "tc_log.h"
#include "tc.h"
#include "si_touch_port.h"
#include "touch_haldispatch.h"

//const static char *TAG = "TOUCH_TOOL";

#define TOUCH_CHANNEL_NUM       5

/**
 ******************************************************************************
 ** \brief Touch_IOConfig
 **
 ** \param [in]:channel:        CAPTOUCH_CHANNEL_0
                                CAPTOUCH_CHANNEL_1
                                CAPTOUCH_CHANNEL_2
                                CAPTOUCH_CHANNEL_3
                                CAPTOUCH_CHANNEL_4
 ** \retval void
 **
 ******************************************************************************/
void Touch_IOConfig(uint8_t channel)
{
    static const struct
    {
        gpio_pin_e pin;
        uint8_t mux;
    } touchPins[TOUCH_CHANNEL_NUM] =
    {
        {GPIO_PIN_1, GPIO1_SOFTWARE_INPUT_FUNCTION_CAP0}, {GPIO_PIN_0, GPIO0_SOFTWARE_INPUT_FUNCTION_CAP1}, {GPIO_PIN_2, GPIO2_SOFTWARE_INPUT_FUNCTION_CAP2},
        {GPIO_PIN_4, GPIO4_SOFTWARE_INPUT_FUNCTION_CAP3}, {GPIO_PIN_5, GPIO5_SOFTWARE_INPUT_FUNCTION_CAP4}
    };

    if (channel >= TOUCH_CHANNEL_NUM)
    {
        return;
    }

    ll_gpio_afio_config(GPIO_PIN_3, (gpio_afio_mux_e)GPIO3_SOFTWARE_INPUT_FUNCTION_CAP_REF);

    ll_gpio_afio_config(touchPins[channel].pin, (gpio_afio_mux_e)touchPins[channel].mux);
    GPIO->OUTEN_SET_F.OUTEN_SET |= 1 << touchPins[channel].pin;
    GPIO->DATAOUT_F.DATAOUT &= ~(1 << touchPins[channel].pin);
}

void Touch_IOEnable(uint8_t channel, uint8_t enable)
{
    static const struct
    {
        gpio_pin_e pin;
        uint8_t mux;
        uint8_t mux_gpio;
    } touchPins[TOUCH_CHANNEL_NUM] =
    {
        {GPIO_PIN_1, GPIO1_SOFTWARE_INPUT_FUNCTION_CAP0, GPIO1_SOFTWARE_INPUT_FUNCTION_GPIO}, {GPIO_PIN_0, GPIO0_SOFTWARE_INPUT_FUNCTION_CAP1, GPIO0_SOFTWARE_INPUT_FUNCTION_GPIO},
        {GPIO_PIN_2, GPIO2_SOFTWARE_INPUT_FUNCTION_CAP2, GPIO2_SOFTWARE_INPUT_FUNCTION_GPIO}, {GPIO_PIN_4, GPIO4_SOFTWARE_INPUT_FUNCTION_CAP3, GPIO4_SOFTWARE_INPUT_FUNCTION_GPIO},
        {GPIO_PIN_5, GPIO5_SOFTWARE_INPUT_FUNCTION_CAP4, GPIO5_SOFTWARE_INPUT_FUNCTION_GPIO}
    };

    if (channel >= TOUCH_CHANNEL_NUM)
    {
        return;
    }

    if (enable)
    {
        ll_gpio_afio_config(touchPins[channel].pin, (gpio_afio_mux_e)touchPins[channel].mux);
    }
    else
    {
        ll_gpio_afio_config(touchPins[channel].pin, (gpio_afio_mux_e)touchPins[channel].mux_gpio);
    }
}

void Touch_Reset(void)
{
    CRG_CONFIG_UNLOCK();
    CRG->CAPTOUCH_CLKRST_CTRL_F.RST_CAPTOUCH = 1;
    __NOP();
    __NOP();
    CRG->CAPTOUCH_CLKRST_CTRL_F.RST_CAPTOUCH = 0;
    __NOP();
    __NOP();
    CRG_CONFIG_LOCK();
}

//RTC触发touch配置，sw:1开0关
void TouchRtcTrigConfig(uint8_t freq, uint8_t sw)
{
    ll_timer_deinit();

    CRG_CONFIG_UNLOCK();
    CRG->TIM_LITE_CLKRST_CTRL_F.PCLK_EN_TIM_LITE = 1;
    CRG->TIM_LITE_CLKRST_CTRL_F.FCLK_SEL_TIM_LITE = FCLK_SRC_32K;
    CRG->TIM_LITE_CLKRST_CTRL_F.FCLK_DIV_TIM_LITE = 0;
    CRG->TIM_LITE_CLKRST_CTRL_F.FCLK_EN_TIM_LITE = 0x1;
    CRG_CONFIG_LOCK();

    TIM_LITE->CTRL_F.TRIG_EN = 0;
    TIM_LITE->CTRL_F.PAUSE = 0;
    TIM_LITE->CTRL_F.STP = 0;
    TIM_LITE->CTRL_F.LOOP_DIS = 0;

    TIM_LITE->INIT_VAL = (32768 / freq);

    if (sw)
    {
        TIM_LITE->ICR = 0xFFFFFFFF;
        TIM_LITE->IMR_F.CNT_UDF_INT_MSK = 0;    //TIMERLITE_INTERRUPT_ENABLE();
        EnableNvic(TIMER_IRQn, TCAE10_DEFAULT_IRQ_LEVEL, ENABLE);
        TIM_LITE->CTRL_F.EN = 1; //TIMERLITE_ENABLE();
    }
    else
    {
        TIM_LITE->IMR_F.CNT_UDF_INT_MSK = 1;    //TIMERLITE_INTERRUPT_DISABLE();
        EnableNvic(TIMER_IRQn, TCAE10_DEFAULT_IRQ_LEVEL, DISABLE);
        TIM_LITE->CTRL_F.EN = 0;        //TIMERLITE_DISABLE();
    }
}

//获取当前时间，单位ms
uint32_t TouchGetTime(void)
{
    uint32_t curTick = TcTimeGet();
#if (TC_SYSTICK_HZ==1000)
    return curTick;
#else
    return (uint64_t)curTick * 1000 / TC_SYSTICK_HZ;
#endif
}

uint32_t lpParaAdjusterSelectCallback(void)    //低功耗参数调节选择器回调接口，非低功耗返回0，低功耗返回1
{
    if (Touch_HalDispatch_GetInSleep(touchDispatch))            //处在低功耗模式
    {
        return 1;
    }
    return 0;
}
