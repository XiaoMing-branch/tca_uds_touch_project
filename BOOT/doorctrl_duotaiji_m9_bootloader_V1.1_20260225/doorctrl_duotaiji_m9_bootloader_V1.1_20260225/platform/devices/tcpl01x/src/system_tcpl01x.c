/**
 *****************************************************************************
 * @brief   system_tcpl01 Source file.
 *
 * @file    system_tcpl01x.c
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

#include "tcpl01x.h"
#include "tcpl01x_ll_def.h"
#include "system_tcpl01x.h"

#if defined (__ARMCC_VERSION) /* Keil uVision 5.29.0.0 */

extern uint32_t Load$$RW_IRAM1$$Base;     /* Load Address of DDR_RW_DATA region*/
extern uint32_t Image$$RW_IRAM1$$Base;    /* Exec Address of DDR_RW_DATA region*/
extern uint32_t Image$$RW_IRAM1$$Length;  /* Length of DDR_RW_DATA region*/
extern uint32_t Image$$RW_IRAM1$$ZI$$Base;
extern uint32_t Image$$RW_IRAM1$$ZI$$Limit;
#endif
uint32_t  SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
#if defined (__ARMCC_VERSION) /* Keil uVision 5.29.0.0 */
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
    dst    = &(Image$$RW_IRAM1$$Base);
    src    = &(Load$$RW_IRAM1$$Base);
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
uint32_t SystemGetHClkFreq(void)
{
    return DEFAULT_SYSTEM_CLOCK;
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
    SysTick_Config(SystemCoreClock / 1000);
}

/********************************************************
** \brief   Set calibration for system
**
** \param   uint8_t         index:calibration value index
**
** \retval  None
*********************************************************/
static void system_trim_value_copy(uint8_t index)
{
    uint32_t reg_val = 0;
    reg_val = *(volatile uint32_t *)(0x00800608 + (index << 2));

    afe_reg_write(&AFE_TEST->TEST_LOCK, 0x76543210);

    switch (index)
    {
        case 0:
            /* lrc32k_trim */
            afe_reg_write(&AFE_TEST->TEST_LRC32K_TRIM, reg_val);
            break;

        case 1:
            /* hrc48m_trim */
            afe_reg_write(&AFE_TEST->TEST_HRC48M_TRIM, reg_val);
            break;

        case 2:
            /* tpref_trim */
            afe_reg_write(&AFE_TEST->TEST_TPREF_TRIM, reg_val);
            break;

        case 3:
            /* ldo35_trim */
            afe_reg_write(&AFE_TEST->TEST_LDO35V_TRIM, reg_val);
            break;

        case 4:
            /* led_trim */
            afe_reg_write(&AFE_TEST->TEST_LED_TRIM, reg_val);
            break;

        case 5:
            /* otp_trim */
            reg_val = 0x1f;
            afe_reg_write(&AFE_TEST->TEST_OTP_TRIM, reg_val);
            break;

        case 6:
            /* lin_trim */
            afe_reg_write(&AFE_TEST->TEST_LIN_TRIM, reg_val);
            break;

        case 7:
            /* saradc status*/
        {
            break;
        }

        case 8:
        {
            reg_val = *(volatile uint32_t *)(0x0080065c);
            TEST->TEST_HRC48M_CTRL = reg_val;
            break;
        }

        case 9:
            /* saradc trim status*/
        {
            break;
        }

        default:
            break;
    }
}

/********************************************************
** \brief   Initialization of calibration for analog system
**
** \param   None
**
** \retval  None
*********************************************************/
static void system_trim()
{
    uint8_t i;

    FLASH_UNLOCK_CONFIG();
    FLASH_UNLOCK_NVR_ACCESS();

    uint16_t trim_status = (uint16_t)(*(volatile uint32_t *)(0x00800604));

    for (i = 0; i < 10; i++)
    {
        if ((trim_status & (1 << i)) == 0)
        {
            system_trim_value_copy(i);
        }
    }

    FLASH_LOCK_NVR_ACCESS();
    FLASH_LOCK_CONFIG();
}

/********************************************************
** \brief   System initializes the HCLK
**
** \param   enumSystemHclkSrc_t     hclk_src
**
** \retval  None
*********************************************************/
void System_HclkConfig(enumSystemHclkSrc_t hclk_src)
{
    uint8_t ready_cnt = 50;
    CLOCK_CONFIG_UNLOCK();
    CRG->HCLK_CTRL_F.HCLK_SEL = hclk_src >= HCLK_SRC_MAX ? HCLK_SRC_RC48M : hclk_src;
    CRG->HCLK_CTRL_F.HCLK_DIV = 0;
    CRG->HCLK_CTRL_F.HCLK_DIV_LOAD = 1;

    // CRG->PCLK_CTRL_F.PCLK_DIV = 0; // use default config
    // CRG->PCLK_CTRL_F.PCLK_DIV_LOAD = 1;

    // CRG->M0_CLKRST_CTRL_F.FCLK_DIV_SYSTICK = 0; // close
    // CRG->M0_CLKRST_CTRL_F.FCLK_EN_SYSTICK = 1;

    // CRG->AFE_CLKRST_CTRL_F.PCLK_EN_AFE = 1; //afe com, use default enable
    // CRG->CRC_CLKRST_CTRL_F.PCLK_EN_CRC = 1; //use default enable
    // CRG->PINMUX_CLKRST_CTRL_F.PCLK_EN_PINMUX = 1; //use default enable
    // CRG->PCLK_CTRL_F.PCLK_EN_PMU = 1; //default 1

    CLOCK_CONFIG_LOCK();

    while (ready_cnt--); // wait for ready
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
#if defined (__ARMCC_VERSION) /* Keil uVision 5.29.0.0 */
    data_rw_init();
#endif
    ll_flash_configrctc(1);
    /* afe com init */
    afe_com_init(1);
    /* HCLK set:default 0:48MHz 1:24MHz */
    System_HclkConfig(HCLK_SRC_RC48M);
    system_trim();
    SystemCoreClockUpdate();
}

/********************************************************
** \brief   system_remap_config
**
** \param   uint32_t    vetor_offset
** \param   bool        enable
**
** \retval  None
*********************************************************/
void system_remap_config(uint32_t vetor_offset, bool enable)
{
    SYSCFG->SYSCFG_LOCK = 0XAA55AA55;

    SYSCFG->REMAP_F.CM0_VECT_BASE_ADDR = vetor_offset >> 8;
    SYSCFG->REMAP_F.CM0_REMAP_EN = (enable) ? 1 : 0;
}
