/**
 *****************************************************************************
 * @brief   sci driver source file.
 *
 * @file   tcae10_ll_lin_uart.c
 * @author AE/FAE team
 * @date   23/11/2022
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2022 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */
#include <stdio.h>
#include "tcae10.h"
#include "system_tcae10.h"
#include "tcae10_ll_lin_uart.h"
#include "tcae10_ll_gpio.h"

/*******************************************************************************
* Definitions:
******************************************************************************/

/*******************************************************************************
* Variables:
******************************************************************************/

uint32_t uartCount = 0;
uint32_t uartStatus = 0;
uint8_t  uartTxEmpty = 1;

/*******************************************************************************
* Prototypes:
******************************************************************************/

/*******************************************************************************
* Code:
******************************************************************************/

void ll_lin_sci_uart_deinit(void)
{
    CRG_CONFIG_UNLOCK();
    CRG->LIN_SCI1_CLKRST_CTRL_F.RST_LIN_SCI1 = 1;
    __NOP();
    __NOP();
    CRG->LIN_SCI1_CLKRST_CTRL_F.RST_LIN_SCI1 = 0;
    __NOP();
    __NOP();
    CRG_CONFIG_LOCK();
}

/********************************************************
 @brief  SCI
 @param  uart:uart
         option:
 @retval void
 *********************************************************/
void ll_lin_sci_uart_mode(sci_mode_t mode)
{
//    uint32_t reg_val = 0;
//    uint8_t status = 0;
//    ( void ) ( &status );
//    afe_reg_read(&LIN_SCI->CTRL_UART, &reg_val, &status);
//    if (mode == LIN)
//    {
//        reg_val &= LIN_SCI_CTRL_UART_MODE_CLR;
//    }
//    else
//    {
//        reg_val |= LIN_SCI_CTRL_UART_MODE_SET(1);
//    }
    LIN_SCI->CTRL_UART_F.MODE = mode;
    /* set uart communication crc bit mode */
    //    reg_val &= LIN_SCI_CTRL_UART_PTY_CHK_EN_CLR;
    //    reg_val |= LIN_SCI_CTRL_UART_PTY_CHK_EN_SET(0x00);
    //    reg_val &= LIN_SCI_CTRL_UART_PTY_MODE_CLR;
    //    reg_val |= LIN_SCI_CTRL_UART_PTY_MODE_SET(0x00);
    /* set uart stop bit*/
    //reg_val &= LIN_SCI_CTRL_UART_STP_BIT_SEL_CLR;
    LIN_SCI->CTRL_UART_F.STP_BIT_SEL = 0;
    /* set uart MP mode */
    //reg_val |= LIN_SCI_CTRL_UART_MP_MODE_EN_SET(1);
    LIN_SCI->CTRL_UART_F.MP_MODE_EN = 1;
    //reg_val |= LIN_SCI_CTRL_UART_MP_RX_ADDR_WR_EN_SET(1);
    LIN_SCI->CTRL_UART_F.MP_RX_ADDR_WR_EN = 1;
    //reg_val |= LIN_SCI_CTRL_UART_MP_TX_ADDR_DATA_SEL_SET(1);
    LIN_SCI->CTRL_UART_F.MP_TX_ADDR_DATA_SEL = 1;
    //afe_reg_write(&LIN_SCI->CTRL_UART, reg_val, &status);
    /* set uart MP address */
    //afe_reg_read(&LIN_SCI->RX_CFG, &reg_val, &status);
    //reg_val &= LIN_SCI_RX_CFG_MP_SLAVE_ADDR_CLR;
    LIN_SCI->RX_CFG_F.MP_SLAVE_ADDR = 0;
    //reg_val |= LIN_SCI_RX_CFG_MP_SLAVE_ADDR_SET(0xaa);
    LIN_SCI->RX_CFG_F.MP_SLAVE_ADDR = 0xAA;
    //reg_val |= LIN_SCI_RX_CFG_MP_SLAVE_ADDR_MSK_SET(1);
    LIN_SCI->RX_CFG_F.MP_SLAVE_ADDR_MSK = 1;
    //afe_reg_write(&LIN_SCI->RX_CFG, reg_val, &status);
}

/********************************************************
 @brief  UART??????
 @retval void
 *********************************************************/
void ll_lin_sci_uart_io_config(void)
{
#if 0
    CRG_FclkCmd(CRG_FCLK_GATED_GPIO, ENABLE);
    LED_IO_SoftwarInputSet(LED_IO_Pin_1, LED_IO1_SOFTWARE_INPUT_FUNCTION_LIN_RXD);
    LED_IO_SoftwarInputSet(LED_IO_Pin_2, LED_IO2_SOFTWARE_INPUT_FUNCTION_LIN_TXD);

#else

    /*Use a2d_lin_rx pin on J1004 */
    /*Use a2d_lin_tx pin on J1009 */

#endif
}

static uint32_t lin_sci_uart_clock_get(void)
{
    uint32_t reg_val = 0;
    uint8_t status = 0;
    (void)(&status);

    reg_val = CRG->LIN_SCI1_CLKRST_CTRL;
    reg_val &= CRG_LIN_SCI1_CLKRST_CTRL_FCLK_DIV_LIN_SCI1_MASK;
    reg_val >>= CRG_LIN_SCI1_CLKRST_CTRL_FCLK_DIV_LIN_SCI1_SHIFT;

    return ((SystemGetHClkFreq()) / (reg_val + 1));
}

/**
  * @brief  Sets sci Baudrate
  * @param  badreate Bardrate
  * @retval None
  */
static void sci_uart_divided(unsigned int dlh, unsigned int dll, unsigned int frac)
{
    uint32_t reg_val = 0;
    uint8_t status = 0;
    (void)(&status);

    dlh &= 0x0f;
    dll &= 0xff;
    frac &= 0x0f;
    reg_val |= (frac << 12 | dlh << 8 | dll);
    LIN_SCI1->BAUD_CFG = reg_val;
}

void ll_lin_sci_uart_setbaudrate(uint32_t baudrate)
{
    uint32_t  clk;

    uint32_t div;
    uint8_t frac = 0;
    clk = lin_sci_uart_clock_get();
    /* Fck/(16*Baud_Rate) */
    div = clk >> 4;
    frac = div % baudrate;
    frac = (frac << 4) / baudrate;
    div  = div / baudrate;
    sci_uart_divided(((div >> 8) & 0xff), ((div >> 0) & 0xff), frac);
}

/**
  * @brief  Sets sci Baudrate
  * @param  badreate Bardrate
  * @retval None
  */
void ll_lin_sci_uart_rxfilter_cfg(uint16_t filter)
{
    LIN_SCI->RX_FILTER_CFG_F.RX_FILTER_TIM = filter;
    TEST->TEST_LIN_CTRL_F.LIN_RX_DELAY = 0;
}

#if 0
uint8_t GetRxFifoTrigNum(uint8_t triggerLevel)
{
    uint8_t value = 0;

    if (triggerLevel == 0)
    {
        value = 1;
    }
    else if (triggerLevel == 1)
    {
        value = 8;
    }
    else if (triggerLevel == 2)
    {
        value = 16;
    }
    else if (triggerLevel == 3)
    {
        value = 30;
    }

    return value;
}
#endif

/**
  * @brief  Init UART peripheral
  * @param  uartConfig a pointer to uart configuration struct where teh configuration information are exist
  * @retval None
  */

void ll_lin_sci_uart_init(void)
{
    LIN_SCI->CTRL_UART_F.MODE = 1;
}

/**
  * @brief  Enables or disables sci
  * @param  en TRUE for enable, FASLE for disable
  * @retval None
  */

void ll_lin_sci_uart_enable(boolean_t en)
{
    /* Config Master Tx related settings*/
    /*First clear Tx FIFO ,trig,clr,abort first high then low*/
    LIN_SCI->CTRL_F.TX_FIFO_CLR = 1;
    LIN_SCI->CTRL_F.RX_FIFO_CLR = 1;
    LIN_SCI->CTRL_F.TX_NUM_MODE = 0;
    LIN_SCI->CTRL_F.RX_NUM_MODE = 0;
    LIN_SCI->CTRL_F.TX_EN = 1;
    LIN_SCI->CTRL_F.RX_EN = 1;
    LIN_SCI->CTRL_F.GLB_EN = 1;
    LIN_SCI->CTRL_F.TX_NUM = 0;
    LIN_SCI->CTRL_F.RX_NUM = 0;
}



/**
  * @brief  Send one byte over UART
  * @param  data The byte to be sent over UART
  * @retval None
  */
//#if defined   ( __ICCARM__   ) /* iar */
//    #pragma location = "RAMUSERCODE"
//#elif defined ( __CC_ARM )     /* keil */
//    __attribute__((section("RAMCODE")))
//#endif
void ll_lin_sci_uart_send_byte(uint8_t data)
{
    LIN_SCI->TX_DATA_F.TX_DATA = data;
    while (LIN_SCI->STATUS_F.TX_FIFO_FULL);

}


/**
  * @brief  Send data over UART
  * @param  pu8Buffer The data to be sent over UART
  * @param  u32Len  Data length
  * @retval None
  */

void ll_lin_sci_uart_send_bytes(uint8_t *pu8Buffer, uint32_t u32Len)
{
    while (u32Len != 0)
    {
        /* Send one character to UART */
        ll_lin_sci_uart_send_byte(*pu8Buffer);
        pu8Buffer++;
        u32Len--;
    }
}

//#if defined   ( __ICCARM__   ) /* iar */
//    #pragma location = "RAMUSERCODE"
//#elif defined ( __CC_ARM )     /* keil */
//    __attribute__((section("RAMCODE")))
//#endif
//uint8_t UART_ReceiveByte(void)
//{
//    return (LIN_SCI->RX_DATA_F.RX_DATA);
//}

/**
  * @brief  Selects the check point position for Tx
  * @param  sel: the position of the check poin
            0 at the middle of tx bit
            1 at the last fclk of tx bit
  * @retval None
  */

void ll_lin_sci_tx_check_point_select(uint8_t sel)
{
    LIN_SCI->TX_CFG_F.CHK_PT_SEL = sel;
}

void ll_lin_sci_interrupt_enable(uint32_t lin_sci_int)
{
    LIN_SCI->IMR &= ~(lin_sci_int);
}

void ll_lin_sci_interrupt_disable(uint32_t lin_sci_int)
{
    LIN_SCI->IMR |= lin_sci_int;
}

bool ll_lin_sci_interrupt_status_get(uint32_t lin_sci_int)
{
    return ((LIN_SCI->ISR & lin_sci_int));
}

void ll_lin_sci_interrupt_clear(uint32_t lin_sci_int)
{
    LIN_SCI->ICR |= lin_sci_int;
}
