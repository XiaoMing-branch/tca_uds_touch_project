/**
 *****************************************************************************
 * @brief   rtc driver source file.
 *
 * @file    tcpl01x_ll_rtc.c
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

#include "tcpl01x_ll_rtc.h"
#include "system_tcpl01x.h"
#include "tcpl01x_ll_cortex.h"

#if 0
#define AFE_RTC_CONFIG_LOCK()                                   \
    do {                                                        \
        afe_reg_write(RTC->LOCK, 0x12345678);                   \
        } while (0)

#define AFE_RTC_CONFIG_UNLOCK()                                 \
    do {                                                        \
        afe_reg_write(RTC->LOCK, 0x5A5A5A5A);                   \
        } while (0)
#else
#define AFE_RTC_CONFIG_LOCK()
#define AFE_RTC_CONFIG_UNLOCK()
#endif

typedef enum
{
    RTC_LOAD_TRIG,
    RTC_LOAD_CNT,
    RTC_LOAD_CALENDAR,
} rtc_load_type_e;

#define RTC_ISR1_FLAG       (0x07UL)

#define RTC_CNT_MS_TO_NUM(period)   ((period/30.5)-1)

static ISR_FUNC_CALLBACK rtc_isr_callback = NULL;

static uint32_t rtc_isr1_flag = 0 ;

/********************************************************
** \brief   ll_rtc_clk_config
**
** \param   uint8_t     fclk_div
**
** \retval  None
*********************************************************/
static void ll_rtc_clk_config(uint8_t fclk_div)
{
    uint32_t reg_val = 0;
    AFE_CLOCK_CONFIG_UNLOCK();
    //clk rtst
    afe_bit_set(&AFE_CRG->RTC_CLKRST_CTRL, AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_SHIFT);
    afe_bit_clear(&AFE_CRG->RTC_CLKRST_CTRL, AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_SHIFT);
    //fclk div config
    reg_val = AFE_CRG_RTC_CLKRST_CTRL_FCLK_DIV_RTC_SET(fclk_div) | AFE_CRG_RTC_CLKRST_CTRL_FCLK_EN_RTC_SET(1);
    afe_reg_write(&AFE_CRG->RTC_CLKRST_CTRL, reg_val);
    AFE_CLOCK_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_rtc_init
**
** \param   rtc_config_t*       config
** \param   ISR_FUNC_CALLBACK   callback
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_rtc_init(rtc_config_t *config, ISR_FUNC_CALLBACK callback)
{
    uint32_t reg_val;

    AFE_RTC_CONFIG_UNLOCK();

    afe_bit_set(&RTC->RTC_CTRL, RTC_RTC_CTRL_RTC_HOLD_SHIFT);

    ll_rtc_clk_config(0);

    // rtc  cnt  config & enable
    afe_reg_write(&RTC->RTC_CNT, config->period_cnt);
    afe_reg_read(&RTC->RTC_CTRL, &reg_val);
    reg_val |= RTC_RTC_CTRL_CNT_LOAD_SET(1);
    afe_reg_write(&RTC->RTC_CTRL, reg_val);

    reg_val |= RTC_RTC_CTRL_CNT_EN_SET(1) | RTC_RTC_CTRL_CALENDAR_EN_SET(1); //enable rtc counter and  calendar
    afe_reg_write(&RTC->RTC_CTRL, reg_val);

    afe_syscfg_int_flag_clear(0, RTC_ISR1_FLAG);

    // isr config
    if (config->isr_cfg.isr_enable)
    {
        rtc_isr_callback = callback;
        rtc_isr1_flag = config->isr_cfg.isr & RTC_ISR1_FLAG;  /* int0 use backup flag*/
    }
    else
    {
        rtc_isr_callback = NULL;
        rtc_isr1_flag = 0;
    }

    afe_bit_clear(&RTC->RTC_CTRL, RTC_RTC_CTRL_RTC_HOLD_SHIFT);

    AFE_RTC_CONFIG_LOCK();

    return LL_OK;
}

/********************************************************
** \brief   ll_rtc_deinit
**
** \param   None
**
** \retval  None
*********************************************************/
void ll_rtc_deinit(void)
{
    AFE_CLOCK_CONFIG_UNLOCK();

    //clk rtst
    afe_bit_set(&AFE_CRG->RTC_CLKRST_CTRL, AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_SHIFT);
    afe_bit_clear(&AFE_CRG->RTC_CLKRST_CTRL, AFE_CRG_RTC_CLKRST_CTRL_RST_RTC_SHIFT);

    AFE_CLOCK_CONFIG_LOCK();

    afe_syscfg_int_flag_clear(0, RTC_ISR1_FLAG);
    afe_syscfg_int_disable(0,  RTC_ISR1_FLAG);
    rtc_isr_callback = NULL;
    rtc_isr1_flag = 0;
}

/********************************************************
** \brief   ll_rtc_isr_enable
**
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_rtc_isr_enable(bool enable)
{
    afe_syscfg_int_flag_clear(0, RTC_ISR1_FLAG);

    if (enable)
    {
        afe_syscfg_int_enable(0,  rtc_isr1_flag); //enable isr_falg
    }
    else
    {
        afe_syscfg_int_disable(0,  rtc_isr1_flag); //enable isr_falg
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_rtc_time_set
**
** \param   rtc_time_t*     time
**
** \retval  None
*********************************************************/
void ll_rtc_time_set(rtc_time_t *time)
{
    uint32_t reg_val;

    AFE_RTC_CONFIG_UNLOCK();

    //afe_bit_set(&RTC->RTC_CTRL, RTC_RTC_CTRL_RTC_HOLD_SHIFT);

    afe_reg_write(&RTC->RTC_YEAR, (time->year & 0x3F));
    afe_reg_write(&RTC->RTC_MON, (time->month & 0xF));
    afe_reg_write(&RTC->RTC_DAY, (time->day & 0x1F));

    afe_reg_write(&RTC->RTC_HOUR, (time->hour & 0x1F));
    afe_reg_write(&RTC->RTC_MIN, (time->min & 0x3F));
    afe_reg_write(&RTC->RTC_SEC, (time->sec & 0x3F));

    afe_reg_read(&RTC->RTC_CTRL, &reg_val);
    reg_val |= RTC_RTC_CTRL_CALENDAR_LOAD_SET(1);
    afe_reg_write(&RTC->RTC_CTRL, reg_val);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    reg_val &= RTC_RTC_CTRL_CALENDAR_LOAD_CLR;
    afe_reg_write(&RTC->RTC_CTRL, reg_val);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    afe_reg_read(&RTC->RTC_CTRL, &reg_val);
    reg_val |= RTC_RTC_CTRL_RTC_LOAD_SET(1);  //RTC load
    afe_reg_write(&RTC->RTC_CTRL, reg_val);
    __NOP();
    __NOP();
    __NOP();
    __NOP();
    afe_reg_read(&RTC->RTC_CTRL, &reg_val);
    reg_val &= RTC_RTC_CTRL_RTC_LOAD_CLR;
    afe_reg_write(&RTC->RTC_CTRL, reg_val);
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    //afe_bit_clear(&RTC->RTC_CTRL, RTC_RTC_CTRL_RTC_HOLD_SHIFT);

    AFE_RTC_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_rtc_time_get
**
** \param   rtc_time_t*     time
**
** \retval  None
*********************************************************/
void ll_rtc_time_get(rtc_time_t *time)
{
    uint32_t reg_val;

    AFE_RTC_CONFIG_UNLOCK();

    afe_reg_read(&RTC->RTC_CALENDAR_1, &reg_val);
    time->year = (reg_val & RTC_RTC_CALENDAR_1_CALENDAR_YEAR_MASK) >> RTC_RTC_CALENDAR_1_CALENDAR_YEAR_SHIFT;
    time->month = (reg_val & RTC_RTC_CALENDAR_1_CALENDAR_MON_MASK) >> RTC_RTC_CALENDAR_1_CALENDAR_MON_SHIFT;
    time->day = (reg_val & RTC_RTC_CALENDAR_1_CALENDAR_DAY_MASK) >> RTC_RTC_CALENDAR_1_CALENDAR_DAY_SHIFT;

    afe_reg_read(&RTC->RTC_CALENDAR_0, &reg_val);
    time->hour = (reg_val & RTC_RTC_CALENDAR_0_CALENDAR_HOUR_MASK) >> RTC_RTC_CALENDAR_0_CALENDAR_HOUR_SHIFT;
    time->min = (reg_val & RTC_RTC_CALENDAR_0_CALENDAR_MIN_MASK) >> RTC_RTC_CALENDAR_0_CALENDAR_MIN_SHIFT;
    time->sec = (reg_val & RTC_RTC_CALENDAR_0_CALENDAR_SEC_MASK) >> RTC_RTC_CALENDAR_0_CALENDAR_SEC_SHIFT;

    AFE_RTC_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_rtc_alarm_set
**
** \param   rtc_alarm_t*        time
**
** \retval  None
*********************************************************/
void ll_rtc_alarm_set(rtc_alarm_t *time)
{
    AFE_RTC_CONFIG_UNLOCK();
    afe_bit_clear(&RTC->RTC_CTRL, RTC_RTC_CTRL_RTC_HOLD_SHIFT);

    afe_reg_write(&RTC->RTC_HOUR, (time->hour & 0x1F));
    afe_reg_write(&RTC->RTC_MIN, (time->min & 0x3F));
    afe_reg_write(&RTC->RTC_SEC, (time->sec & 0x3F));

    afe_bit_set(&RTC->RTC_CTRL, RTC_RTC_CTRL_RTC_HOLD_SHIFT);

    AFE_RTC_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_rtc_alarm_get
**
** \param   rtc_alarm_t*     time
**
** \retval  None
*********************************************************/
void ll_rtc_alarm_get(rtc_alarm_t *time)
{
    uint32_t reg_val;

    AFE_RTC_CONFIG_UNLOCK();

    afe_reg_read(&RTC->RTC_HOUR, &reg_val);
    time->hour =  reg_val & 0x1F;
    afe_reg_read(&RTC->RTC_MIN, &reg_val);
    time->min =  reg_val & 0x3F;
    afe_reg_read(&RTC->RTC_SEC, &reg_val);
    time->sec =  reg_val & 0x3F;

    AFE_RTC_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_rtc_trig0_set
**
** \param   uint16_t    trig_num
**
** \retval  None
*********************************************************/
void ll_rtc_trig0_set(uint16_t trig_num)
{
    uint32_t reg_val;

    AFE_RTC_CONFIG_UNLOCK();

    afe_reg_read(&RTC->RTC_CTRL, &reg_val);

    reg_val &= RTC_RTC_CTRL_RTC_LOAD_CLR;
    afe_reg_write(&RTC->RTC_CTRL, reg_val);

    reg_val &= RTC_RTC_CTRL_RTC_HOLD_CLR;
    afe_reg_write(&RTC->RTC_CTRL, reg_val);

#if defined ( __ARMCC_VERSION )
    __NOP();
    __NOP();
    __NOP();
#elif defined ( __GNUC__ )
    __NOP();
    __NOP();
    __NOP();
#endif
    /*set trig0 num*/
    afe_reg_read(&RTC->RTC_TRIG_0, &reg_val);
    reg_val |= RTC_RTC_TRIG_0_TRIG_NUM_0_SET(trig_num);
    afe_reg_write(&RTC->RTC_TRIG_0, reg_val);

    /*set trig load in rtc control register to 1 */
    afe_reg_read(&RTC->RTC_CTRL, &reg_val);
    reg_val |= RTC_RTC_CTRL_TRIG_EN_0_SET(1) | RTC_RTC_CTRL_TRIG_LOAD_0_SET(1) | RTC_RTC_CTRL_RTC_LOAD_SET(1);
    afe_reg_write(&RTC->RTC_CTRL, reg_val);

#if defined ( __ARMCC_VERSION )
    __NOP();
    __NOP();
    __NOP();
#elif defined ( __GNUC__ )
    __NOP();
    __NOP();
    __NOP();
#endif

    AFE_RTC_CONFIG_LOCK();
}

/********************************************************
** \brief   RTC_IRQHandler
**
** \param   uint32_t        isr0
** \param   uint32_t        isr1
**
** \retval  None
*********************************************************/
__attribute__((section("RAMCODE")))
void RTC_IRQHandler(uint32_t isr0, uint32_t isr1)
{
    if (isr1 & RTC_ISR1_FLAG)
    {
        if (NULL != rtc_isr_callback)
        {
            rtc_isr_callback(isr1 & RTC_ISR1_FLAG);
        }

        afe_syscfg_int_flag_clear(0, RTC_ISR1_FLAG);
    }
}
