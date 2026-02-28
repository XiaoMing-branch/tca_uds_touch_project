/**
 ******************************************************************************
 *       Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice,
 *       this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice,
 *       this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *    3. Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE  DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************
 */

#include "tcae10.h"
#include "system_tcae10.h"

#if defined (__ARMCC_VERSION) /* Keil ��Vision 5.29.0.0 */

    extern uint32_t Load$$RW_IRAM1$$Base;     /* Load Address of DDR_RW_DATA region*/
    extern uint32_t Image$$RW_IRAM1$$Base;    /* Exec Address of DDR_RW_DATA region*/
    extern uint32_t Image$$RW_IRAM1$$Length;  /* Length of DDR_RW_DATA region*/
    extern uint32_t Image$$RW_IRAM1$$ZI$$Base;
    extern uint32_t Image$$RW_IRAM1$$ZI$$Limit;
#endif

#ifndef CFG_HCLK_CLOCK          //配置hclk时钟
    #define CFG_HCLK_CLOCK DEFAULT_SYSTEM_CLOCK
#endif

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

#if defined (__ARMCC_VERSION) /* Keil ��Vision 5.29.0.0 */
void CopyDataRWtoImage(void)
{
    uint32_t *src;
    uint32_t *dst;
    uint32_t length;
    dst    = & (Image$$RW_IRAM1$$Base);
    src    = & (Load$$RW_IRAM1$$Base);
    length = (unsigned int) & (Image$$RW_IRAM1$$Length);
    length /= sizeof(unsigned int);

    if (dst != src)
    {
        while (length > 0)
        {
            dst[length - 1] = src[length - 1];
            length--;
        }
    }
}

#endif

uint32_t SystemGetHClkFreq(void)
{
    return sys_hclk_freq_get();
}

/********************************************************
** \brief   Get system HCLK
**
** \param   None
**
** \retval  uint32_t        Value of system hclk
*********************************************************/
uint32_t sys_hclk_freq_get(void)
{
    uint8_t sel = 0;
    uint8_t div = 0;
    uint32_t clk;

    sel = CRG->HCLK_CTRL_F.HCLK_SEL;
    div = CRG->HCLK_CTRL_F.HCLK_DIV;

    clk = (sel == 0) ? CPU_INT_FAST_CLK_HZ : CPU_INT_SLOW_CLK_HZ;

    return clk / (div + 1);
}

/********************************************************
** \brief   Get system PCLK
**
** \param   None
**
** \retval  uint32_t        Value of system pclk
*********************************************************/
uint32_t sys_pclk_freq_get(void)
{
    uint8_t div = 0;
    uint32_t clk;

    div = CRG->PCLK_CTRL_F.PCLK_DIV;

    clk = sys_hclk_freq_get();

    return clk / (div + 1);
}

/********************************************************
** \brief   Update system clock value
**
** \param   None
**
** \retval  None
*********************************************************/
void SystemCoreClockUpdate(void)
{
    /*Later update SystemCoreClock according to clock tree*/
    SystemCoreClock = SystemGetHClkFreq();
}

void CopyAnalogTrimValue(uint8_t index)
{
#if 1

    switch (index)
    {
    case 0:
        //RC32K trim
        TEST->TEST_LRC32K_TRIM = * (volatile uint32_t *)(0x00800008);
        break;

    case 1:
        //RC48M trim
        TEST->TEST_HRC48M_TRIM = * (volatile uint32_t *)(0x0080000C);
        break;

    case 2:
        //TPREF trim
        TEST->TEST_TPREF_TRIM = * (volatile uint32_t *)(0x00800010);
        break;

    case 3:
        //BIAS trim
        TEST->TEST_BIAS_TRIM  = * (volatile uint32_t *)(0x00800014);
        break;

    case 4:
        //LDO15 trim
        TEST->TEST_LDO15_TRIM  = * (volatile uint32_t *)(0x00800018);
        break;

    case 5:
        //LDO33 trim
        TEST->TEST_LDO33_TRIM  = * (volatile uint32_t *)(0x0080001C);
        break;

    case 6:
        //LED_LDO5 trim
        TEST->TEST_LED_LDO5_TRIM  = * (volatile uint32_t *)(0x00800020);
        break;

    case 7:
        //LED trim
        TEST->TEST_LED_TRIM  = * (volatile uint32_t *)(0x00800024);
        break;

    case 8:
        //LED_IB_DIAG trim
        TEST->TEST_LED_IB_DIAG_TRIM  = * (volatile uint32_t *)(0x00800028);
        break;

    case 9:
        //OTP trim
        TEST->TEST_OTP_TRIM  = * (volatile uint32_t *)(0x0080002C);
        break;

    case 10:
        //LIN trim
        TEST->TEST_LIN_TRIM  = * (volatile uint32_t *)(0x00800030);
        break;

    case 11:
        //TOUCH trim
        TEST->TEST_TOUCH_TRIM  = * (volatile uint32_t *)(0x00800034);
        break;

    case 12:
    {
        //SARADC trim
//        TEST->ADC_TRIM0       = * (volatile uint32_t *)(0x00800038);
//        TEST->ADC_TRIM1       = * (volatile uint32_t *)(0x0080003C);
//        TEST->ADC_TRIM2       = * (volatile uint32_t *)(0x00800040);
//        TEST->ADC_TRIM3       = * (volatile uint32_t *)(0x00800044);
//        TEST->ADC_TRIM4       = * (volatile uint32_t *)(0x00800048);
//        TEST->ADC_TRIM5       = * (volatile uint32_t *)(0x0080004C);
//        TEST->ADC_TRIM6       = * (volatile uint32_t *)(0x00800050);
//        TEST->ADC_TRIM7       = * (volatile uint32_t *)(0x00800054);
        TEST->ADC_TRIM0     = 0x74371F1D;
        TEST->ADC_TRIM1     = 0xFA007C;
        TEST->ADC_TRIM2     = 0x2EF0177;
        TEST->ADC_TRIM3     = 0xB0404F8;
        TEST->ADC_TRIM4     = 0x16010B04;
        TEST->ADC_TRIM5     = 0x108020ff;
        TEST->ADC_TRIM6     = 0x3F402100;
        TEST->ADC_TRIM7     = 0x7900;

        break;
    }

    default:
        break;
    }

#endif
}
void SystemAnlogTrim()
{
    uint8_t i;
    uint32_t trimStatus = (uint32_t)(*(volatile uint32_t *)(0x00800004));
    TEST->TEST_LOCK = 0x76543210;

//    for ( i = 0; i <= 12 ; i++ )
//    {
//        if ( ( trimStatus  & ( 0x1 << i ) ) == 0 )
//        {
//            CopyAnalogTrimValue ( i );
//        }
//    }

    for (i = 0; i <= 12 ; i++)
    {
        CopyAnalogTrimValue(i);
    }
}

/**
 * @brief  This function initializes the HCLK
 * @param  hclk_src specifies the HCLK source
 *         This parameter can be one of the following values:
 *            @arg 0: the HCLK source is RC48 MHz
 *            @arg 1: the HCLK source is RC32 KHz
 *            seer @ref CRG_CLOCK_SOURCE_Definitions
 * @retval div specifies the HCLK source divider
 *         this parameter is 4-bit length, and
 *         can be any value between 0 and 15
 */
void System_HclkConfig(uint8_t hclk_src, uint8_t div)
{
    uint8_t ready_cnt = 50;

    CRG->CRG_LOCK = 0X5A5A5A5A;

    switch (hclk_src)
    {
    case HCLK_SRC_RC48M:
        CRG->HCLK_CTRL_F.HCLK_SEL = 0;
        CRG->HCLK_CTRL_F.HCLK_DIV = div;
        while (ready_cnt--);  // wait for ready
        break;

    case HCLK_SRC_RC32K:
        CRG->HCLK_CTRL_F.HCLK_SEL = 1;
        CRG->HCLK_CTRL_F.HCLK_DIV_LOAD = 1;
        while (ready_cnt--);  // wait for ready
        break;

    default:
        break;
    }

    CRG->HCLK_CTRL_F.HCLK_DIV_LOAD = 1;

    CRG->CRG_LOCK = 0X12345678;
}


/********************************************************
** \brief   initializes the PCLK
**
** \param   uint8_t     div:APB clock divider
**
** \retval  None
*********************************************************/
static void sys_pclk_config(uint8_t div)
{
    CRG->CRG_LOCK = 0X5A5A5A5A;
    /* set the divider for the Pclk */
    CRG->PCLK_CTRL_F.PCLK_DIV = div;
    CRG->PCLK_CTRL_F.PCLK_DIV_LOAD = 1;

    CRG->TIM_LITE_CLKRST_CTRL_F.PCLK_EN_TIM_LITE = 0;

    CRG->PRINT_UART_CLKRST_CTRL_F.PCLK_EN_PRINT_UART = 0;

    CRG->IWDG_CLKRST_CTRL_F.PCLK_EN_IWDG = 1;       //看门狗时钟开启

    CRG->PWM_CLKRST_CTRL_F.PCLK_EN_PWM = 0;

    CRG->ADC_CLKRST_CTRL_F.PCLK_EN_ADC = 0;

    CRG->LIN_SCI_CLKRST_CTRL_F.PCLK_EN_LIN_SCI = 0;

    CRG->CAPTOUCH_CLKRST_CTRL_F.PCLK_EN_CAPTOUCH = 0;

    CRG->SPI_CLKRST_CTRL_F.PCLK_EN_SPI = 0;

    CRG->LIN_SCI1_CLKRST_CTRL_F.PCLK_EN_LIN_SCI1 = 0;

    CRG->CRG_LOCK = 0X12345678;
}

/********************************************************
** \brief   sys_dummy_load_config
**
** \param   None
**
** \retval  None
*********************************************************/
static void sys_dummy_load_enable(void)
{
    ASYSCFG->LDO15_CTRL_F.LDO15_DL_SW_ENB = 1;
    ASYSCFG->LDO15_CTRL_F.LDO15_DL_IBASE_SEL = 0;
    ASYSCFG->LDO33_CTRL_F.LDO33_DL_SW_ENB = 1;
    ASYSCFG->LDO33_CTRL_F.LDO33_DL_IBASE_SEL = 0;
}

/********************************************************
** \brief   WDOG DISABLE
**
** \param   None
**
** \retval  None
*********************************************************/
static void wdg_disable(void)
{
    IWDG->LOCK = 0xAAAA5555;

    IWDG->CTRL_F.EN = false;
    IWDG->CTRL_F.RST_EN = false;

    IWDG->LOCK = 0x12345678;
}

void SystemInit(void)
{
#if defined   ( __ICCARM__   ) /* iar */

#elif defined ( __ARMCC_VERSION )     /* keil */
    CopyDataRWtoImage();
#elif defined (__GNUC__)        /* GNU GCC*/
#endif
    System_HclkConfig(HCLK_SRC_RC48M, DEFAULT_SYSTEM_CLOCK / CFG_HCLK_CLOCK - 1);
    SystemCoreClockUpdate();
    SystemAnlogTrim();
    sys_pclk_config(0);  //set the divider for the Pclk

    /* enable dummy load */
    sys_dummy_load_enable();

    wdg_disable();

#ifdef CUTOFF_POWER_EN      //降低功耗
    EFLASH->WR_LOCK = 0X12345678;       //锁flash
#else
    EFLASH->WR_LOCK = 0XAA55AA55;
    EFLASH->RD_TIME_CFG_F.RC_CYC = 0x1;
    EFLASH->WR_LOCK = 0X12345678;
#endif
}
