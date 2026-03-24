/**
 *****************************************************************************
 * @brief   system_tcpl03x Source file.
 *
 * @file    system_tcpl03x.c
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

#include "tcpl03x.h"
#include "system_tcpl03x.h"

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* Keil uVision 5.29.0.0 */
#if defined (__ARMCC_VERSION)

/* Load Address of DDR_RW_DATA region */
extern uint32_t Load$$RW_IRAM1$$Base;
/* Exec Address of DDR_RW_DATA region */
extern uint32_t Image$$RW_IRAM1$$Base;
/* Length of DDR_RW_DATA region */
extern uint32_t Image$$RW_IRAM1$$Length;
extern uint32_t Image$$RW_IRAM1$$ZI$$Base;
extern uint32_t Image$$RW_IRAM1$$ZI$$Limit;

/********************************************************
** \brief   Make necessary initializations for RAM.
            - Copy initialized data from ROM to RAM.
            - Copy code that should reside in RAM from ROM
**
** \param   None
**
** \retval  None
*********************************************************/
void data_rw_init(void)
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

    return clk >> div;
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

    return clk >> div;
}

/********************************************************
** \brief   Update system clock value
**
** \param   None
**
** \retval  None
*********************************************************/
void sys_core_clock_update(void)
{
    /*Later update SystemCoreClock according to clock tree*/
    SystemCoreClock = sys_hclk_freq_get();
    SysTick_Config(SystemCoreClock / 1000);
}

/********************************************************
** \brief   Set calibration for system
**
** \param   uint8_t         index:calibration value index
**
** \retval  None
*********************************************************/
static void trimvalue_load(uint8_t index)
{
    TEST->TEST_LOCK = 0x76543210;

    switch (index)
    {
        /* lrc32k_trim */
        case 0:
            TEST->TEST_LRC32K_TRIM = REG_READ32(0x00800008);
            break;

        /* hrc48m_trim */
        case 1:
            TEST->TEST_HRC48M_TRIM = REG_READ32(0x0080000C);
            break;

        /* tpref_trim */
        case 2:
            TEST->TEST_TPREF_TRIM = REG_READ32(0x00800010);
            break;

        /* bias_trim */
        case 3:
            TEST->TEST_BIAS_TRIM = REG_READ32(0x00800014);
            break;

        /* ldo15_trim */
        case 4:
            TEST->TEST_LDO15_TRIM = REG_READ32(0x00800018);
            break;

        /* ldo33_trim */
        case 5:
            TEST->TEST_LDO33_TRIM = REG_READ32(0x0080001C);
            break;

        /* led_ldo5_trim */
        case 6:
            TEST->TEST_LED_LDO5_TRIM = REG_READ32(0x00800020);
            break;

        /* led_trim */
        case 7:
            TEST->TEST_LED_TRIM = REG_READ32(0x00800024);
            break;

        /* led_ib_diag_trim */
        case 8:
            TEST->TEST_LED_IB_DIAG_TRIM = REG_READ32(0x00800028);
            break;

        /* otp_trim */
        case 9:
            TEST->TEST_OTP_TRIM = REG_READ32(0x0080002C);
            break;

        /* lin_trim */
        case 10:
            TEST->TEST_LIN_TRIM = REG_READ32(0x00800030);
            break;

        default:
            break;
    }

    //    TEST->TEST_LOCK = 0xFEDCBA98;
}

/********************************************************
** \brief   Initialization of calibration for analog system
**
** \param   None
**
** \retval  None
*********************************************************/
void sys_trimvalue_load(void)
{
    uint8_t i;
    uint32_t trim_status = REG_READ32(0x00800004);

    for (i = 0; i < 32; i++)
    {
        if ((trim_status >> i) & 0x01)
        {
            continue;
        }

        trimvalue_load(i);
    }
}

/********************************************************
** \brief   System initializes the HCLK
**
** \param   uint8_t     hclk_src:AHB clock source selection
** \param   uint8_t     div:AHB clock divider, default divide by 1
**
** \retval  None
*********************************************************/
void sys_hclk_config(uint8_t hclk_src, uint8_t div)
{
    uint8_t ready_cnt = 50;

    CRG->CRG_LOCK = 0X5A5A5A5A;

    switch (hclk_src)
    {
        case HCLK_SRC_RC48M:
            CRG->HCLK_CTRL_F.HCLK_SEL = 0;
            break;

        case HCLK_SRC_RC32K:
            CRG->HCLK_CTRL_F.HCLK_SEL = 1;
            break;

        default:
            break;
    }

    CRG->HCLK_CTRL_F.HCLK_DIV = div;
    CRG->HCLK_CTRL_F.HCLK_DIV_LOAD = 1;

    /* wait for ready */
    while (ready_cnt--);

    CRG->CRG_LOCK = 0X12345678;
}

/********************************************************
** \brief   initializes the PCLK
**
** \param   uint8_t     div:APB clock divider
**
** \retval  None
*********************************************************/
void sys_pclk_config(uint8_t div)
{
    CRG->CRG_LOCK = 0X5A5A5A5A;

    /* set the divider for the Pclk */
    CRG->PCLK_CTRL_F.PCLK_DIV = div;
    CRG->PCLK_CTRL_F.PCLK_DIV_LOAD = 1;

    CRG->TIM_LITE_CLKRST_CTRL_F.PCLK_EN_TIM_LITE = 0;
    CRG->PRINT_UART_CLKRST_CTRL_F.PCLK_EN_PRINT_UART = 0;
    CRG->IWDG_CLKRST_CTRL_F.PCLK_EN_IWDG = 0;
    CRG->PWM_CLKRST_CTRL_F.PCLK_EN_PWM = 0;
    CRG->ADC_CLKRST_CTRL_F.PCLK_EN_ADC = 0;
    CRG->LIN_SCI_CLKRST_CTRL_F.PCLK_EN_LIN_SCI = 0;
    CRG->RESERVED_T_CLKRST_CTRL_F.PCLK_EN_RESERVED_T = 0;
    CRG->RESERVED_S_CLKRST_CTRL_F.PCLK_EN_RESERVED_S = 0;
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
    ASYSCFG->LDO15_CTRL_F.LDO15_DL_SW_ENB = 0;
    ASYSCFG->LDO15_CTRL_F.LDO15_DL_IBASE_SEL = 0;
    ASYSCFG->LDO33_CTRL_F.LDO33_DL_SW_ENB = 0;
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
#if (DISABLE_WDOG)
    IWDG->LOCK = 0xAAAA5555;
    IWDG->CTRL_F.EN = false;
    IWDG->CTRL_F.RST_EN = false;
    IWDG->LOCK = 0x12345678;
#endif
}

/********************************************************
** \brief   System initializes
**
** \param   None
**
** \retval  None
*********************************************************/
void SystemInit(void)
{
#if defined ( __ARMCC_VERSION )
    /* keil */
    data_rw_init();
#elif defined ( __ICCARM__ )
    /* iar */
#elif defined (__GNUC__)
    /* GNU GCC*/
#endif

    /* System initializes the HCLK */
    sys_hclk_config(HCLK_SRC_RC48M, 0);

    /* system core clock update */
    sys_core_clock_update();

    /* diable watchdog */
    wdg_disable();

    /* set the divider for the Pclk */
    sys_pclk_config(0);

    /* enable dummy load */
    sys_dummy_load_enable();

    /* sys_trimvalue_load */
    sys_trimvalue_load();
}

/********************************************************
** \brief  system_remap_config
**
** \param  uint32_t    vetor_offset
** \param  bool        enable
**
** \retval None
*********************************************************/
void system_remap_config(uint32_t vetor_offset, bool enable)
{
    SYSCFG->SYSCFG_LOCK = 0xaa55aa55;

    SYSCFG->REMAP_F.CM0_VECT_BASE_ADDR = vetor_offset >> 8;
    SYSCFG->REMAP_F.CM0_REMAP_EN = (enable) ? 1 : 0;
}
