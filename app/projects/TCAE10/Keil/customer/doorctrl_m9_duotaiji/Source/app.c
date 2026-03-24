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

static void HandleDoorPwm(void);      //处理pwm输出
static void DoorPwmStart(void);
static void DoorPwmStop(void);
static struct
{
    uint8_t keymask;
    uint8_t changed;
    uint8_t fsm;
    uint32_t begin_t;
} pwmCtrl = {0};

extern const char g_seres_app_software_version[21];
extern const char g_lin_sequence_num_version[24];

void SetHwSwVersion(void)
{
    uint8_t hard_version[8] = {0};

    ll_flash_read(FLASH_TYPE_NVM, 0x00003908u, (uint8_t *)hard_version, sizeof(hard_version));

    door_st.SW_MajorVersA = (g_seres_app_software_version[10] - 0x30); // 软件主版本号
    door_st.SW_MinorVersA = ((g_seres_app_software_version[15] - 0x30) * 10 + (g_seres_app_software_version[16] - 0x30)) & 0x7F; // 软件次版本号

    door_st.HW_MajorVersB = (hard_version[5] - 0x30);    // 硬件主版本号
    door_st.HW_MinorVersB = (hard_version[7] - 0x30);    // 硬件次版本号
    // 硬件阶段版本号
    if (hard_version[3] == 'A')
    {
        door_st.HW_PhaVers = 0x1;
    }
    else if (hard_version[3] == 'B')
    {
        door_st.HW_PhaVers = 0x2;
    }
    else if (hard_version[3] == 'C')
    {
        door_st.HW_PhaVers = 0x3;
    }
    else
    {
        door_st.HW_PhaVers = 0x0;
    }
    // LIN节点：主序列号A/B/C
    if (g_lin_sequence_num_version[8] == 'A')
    {
        door_st.SN_MajorVersB = 0x1;
    }
    else if (g_lin_sequence_num_version[8] == 'B')
    {
        door_st.SN_MajorVersB = 0x2;
    }
    else if (g_lin_sequence_num_version[8] == 'C')
    {
        door_st.SN_MajorVersB = 0x3;
    }
    else
    {
        door_st.SN_MajorVersB = 0x0;
    }
    // LIN节点：次序列号(1~9)
    door_st.SN_MinorVersB = (g_lin_sequence_num_version[3] - 0x30) & 0xF;
    // LIN节点：供应商代码
    if ((g_lin_sequence_num_version[17] == '3') && (g_lin_sequence_num_version[18] == '1') &&
        (g_lin_sequence_num_version[19] == '9') && (g_lin_sequence_num_version[20] == '7'))
    {
        door_st.SN_SupplierCod = 0x0;
    }
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
        HandleDoorPwm();
    }

    if (msg == MSG_TASK_ENTER_HALT)
    {
        session_mode = SESSION_MODE_DEFAULT;
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
        pwmCtrl.keymask = 1;
    }
    else if (status == SI_KEY_RELEASE)
    {
        pwmCtrl.keymask = 0;
    }
    else
    {
        return;
    }

    pwmCtrl.changed = 1;
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

static void HandleDoorPwm(void)   //处理pwm输出
{
    switch (pwmCtrl.fsm)
    {
    case 0:
        if (pwmCtrl.changed)
        {
            pwmCtrl.changed = 0;
            if (pwmCtrl.keymask)
            {
                DoorPwmStart();     //开
                door_st.SwtSt = 1;

                pwmCtrl.begin_t = TcTimeGet();
                pwmCtrl.fsm = 1;
            }
            else
            {
                //关pwm
                DoorPwmStop();
                pwmCtrl.begin_t = TcTimeGet();              //用于LinCanEnterSleep
                door_st.SwtSt = 2;
            }
        }
        break;
    case 1:             //等待最小信号时间
        if (TcTimeGet() - pwmCtrl.begin_t >= OPEN_DOOR_MIN_TIMEMS)
        {
            pwmCtrl.fsm = 2;
        }
        break;
    case 2:     //正常响应
        if (TcTimeGet() - pwmCtrl.begin_t >= OPEN_DOOR_MAX_TIMEMS || pwmCtrl.changed)
        {
            //关pwm
            DoorPwmStop();
            pwmCtrl.begin_t = TcTimeGet();              //用于LinCanEnterSleep
            door_st.SwtSt = 2;
            pwmCtrl.fsm = 0;
            return;
        }
        break;
    }
}

static void DoorPwmStart(void)
{
    PWM->LED_CTRL_F.LED_LDO5V_EN = ENABLE;
    ll_gpio_output(UNLOCK_PIN, true);
}

static void DoorPwmStop(void)
{
//        PWM->LED_CTRL_F.LED_LDO5V_EN = DISABLE;
    ll_gpio_output(UNLOCK_PIN, false);
}

//返回1表示收到lin sleep命令后可以进入低功耗，0表示不可以
int LinCanEnterSleep(void)
{
    return (TcTimeGet() - pwmCtrl.begin_t >= 5000);
}
