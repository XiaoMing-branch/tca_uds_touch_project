/**
  ******************************************************************************
  * @brief  application main file.
  *
  * @file   app.c
  * @author AE/FAE team
  * @date
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <b>&copy; Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd.</b>
  *
  ******************************************************************************
  */

#include "tcae10.h"
#include "tcae10_ll_def.h"
#include "tc_log.h"
#include "tc_halt.h"
#include "misc.h"
#include "tc.h"
#include "app.h"
#include "lin_task.h"
#include "si_touch_port.h"
#include "touch_config.h"
#include "lin_frame.h"
#include "store_manager.h"
#include "diagnosticIII.h"

static const char *TAG = "APP";

static void AppTask(uint32_t msg, void *param);    //App任务
static void FreeIoSet(void);        //不用io设置，防止低功耗漏电
static void FreePerSet(void);       //关闭不用外设，降低功耗

static void DoorGpioInit(void);
extern void SysDoFlashRoutine27Service(void);

extern DoorSt_T door_st;

void SetHwSwVersion(void)
{
    door_st.SW_MajorVersA = 0x1;    // 软件主版本号
    door_st.SW_MinorVersA = 0x1;    // 软件次版本号
    door_st.HW_MajorVersB = 0x1;    // 硬件主版本号
    door_st.HW_MinorVersB = 0x0;    // 硬件次版本号
    door_st.HW_PhaVers = 0x1;       // 硬件阶段版本号
    door_st.SN_MajorVersB = 0x1;    // 主序列号
    door_st.SN_MinorVersB = 0x1;    // 次序列号
    door_st.SN_SupplierCod = 0x0;   // 供应商代码
}

void TcMain(void)
{
#if defined APP_MATCH_BOOT
    ll_syscfg_remap_config(FLASH_APP_ADDR, true);
#else
    delay1ms(5000);
#endif

    FreePerSet();
    FreeIoSet();

    DoorGpioInit();

#if WATCH_DOG_EN
    WdgInit();
#endif

#if ((DEBUG_PRINT_EN == 1) && (LOG_INTERFACE_TYPE == LOG_INTERFACE_UART))
    TC_LOG_Init(1000000);
    TC_LOG_SetPin(PRINT_GPIO6);
#endif

    TcPortInit();      //little os port初始化

    __enable_irq();

#if LOW_POWER_EN
    HaltInit();                             //低功耗任务初始化
#endif

#if TOUCH_FUNC_EN
    TouchInit();
#endif
    store_manager_init();
#if LIN_FUNC_EN
    LinInit();          //Lin初始化
#endif

    TC_LOGI(TAG, "duotaiji m9 door ctrl project");

    if (!TcTaskCreate("app", AppTask, NULL, TC_TASK_PRIO_MID))   //创建APP任务
    {
        TC_LOGE(TAG, "AppTask create fail");
    }
    else
    {
        TC_LOGI(TAG, "AppTask create ok");
    }

    while (1)
    {
        TcTaskExec();
    }
}

static void AppTask(uint32_t msg, void *param)    //App任务
{
    static T_TcTimer *appTimer = NULL;            //定时器

    if (msg == MSG_TASK_INIT)
    {
        if ((appTimer = TcTimerCreate(TC_TIMER_TYPE_CIRCLE, 2, NULL, currentTask, NULL)) == NULL)
        {
            TC_LOGE(TAG, "appTimer create fail");
        }
        else
        {
            TcTimerStart(appTimer);
        }

        SetHwSwVersion();
        DoorGpioInit();

#if DEBUG_PRINT_EN && LOG_INTERFACE_TYPE==LOG_INTERFACE_UART
        PWM->LED_CTRL_F.LED_LDO5V_EN = 1;
#endif
    }

    if (msg == MSG_TASK_TIMER)
    {
#if WATCH_DOG_EN
        ll_wdg_reload();
#endif

//        TC_LOGD(TAG, "vbat:%d", GetVbatMv(ADC_VREF_2500, 4));
//        int32_t vbat = GetVbatMv(ADC_VREF_2500, 4);
//        TC_LOG_SYMBOL_I32("vbat", &vbat, sizeof(vbat));

#if LIN_FUNC_EN
        App_LinControlMsg();
#endif
        LinDiagnosticSessionCheck();
        SysDoFlashRoutine27Service();
    }

    if (msg == MSG_TASK_ENTER_HALT)
    {
        PWM->LED_CTRL_F.LED_LDO5V_EN = DISABLE;     //确保ldo5关闭
    }

    if (msg == MSG_TASK_WAKE_UP)
    {
        PWM->LED_CTRL_F.LED_LDO5V_EN = ENABLE;     //确保ldo5关闭

#if LOW_POWER_EN
        HaltTimeoutChgPeriod(5000);
#endif
    }
}

void TouchKeyCallback(uint8_t keyNo, T_SiKeyStatus status)
{
    if (status == SI_KEY_PRESS)
    {
        PWM->LED_CTRL_F.LED_LDO5V_EN = ENABLE;
        ll_gpio_output(UNLOCK_PIN, true);
    }
    else if (status == SI_KEY_RELEASE)
    {
//        PWM->LED_CTRL_F.LED_LDO5V_EN = DISABLE;
        ll_gpio_output(UNLOCK_PIN, false);
    }
    else
    {
        return;
    }
}

static void FreePerSet(void)       //关闭不用外设，降低功耗
{

}

static void FreeIoSet(void)     //不用io设置，防止低功耗漏电
{

}

static void DoorGpioInit(void)
{
    //PWM CLK CFG
    CRG_CONFIG_UNLOCK();
    CRG->PWM_CLKRST_CTRL_F.PCLK_EN_PWM = ENABLE;
    CRG_CONFIG_LOCK();

    PWM->LED_CTRL_F.LED_LDO5V_EN = ENABLE;        //需要发波时候再开启
//    ADC->CTRL0_F.VREFBUF_EN = ENABLE;

    ll_gpio_output(UNLOCK_PIN, false);
    gpio_config_t cfg =
    {
        .gpio_pin = UNLOCK_PIN,
        .mode = GPIO_MODE_OUT_PP,
        .pull_mode = GPIO_PULL_NONE,
        .afio = AFIO_MUX_3,
        .trigger_flag = GPIO_TRIGGER_NULL
    };
    ll_gpio_init(&cfg, NULL);
    ll_gpio_output(UNLOCK_PIN, false);
}
