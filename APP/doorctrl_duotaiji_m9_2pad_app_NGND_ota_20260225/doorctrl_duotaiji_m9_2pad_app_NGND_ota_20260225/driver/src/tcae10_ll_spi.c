/**
  ******************************************************************************
  * @brief  SPI Driver source file.
  *
  * @file   spi.c
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



#include "tcae10_ll_spi.h"
#include "tcae10_ll_gpio.h"


/**
  * @brief  This function De-Init spi all registers
  * @param  None
  * @retval None
  */
void ll_spi_deinit(void)
{
    CRG_CONFIG_UNLOCK();
    CRG->SPI_CLKRST_CTRL_F.RST_SPI = 1;
    __NOP();
    __NOP();
    CRG->SPI_CLKRST_CTRL_F.RST_SPI = 0;
    __NOP();
    __NOP();
    CRG_CONFIG_LOCK();
}



/**
  * @brief  This function enables or disable SPI output in Slave mode
  *         this is useful in 3wire mode
  * @param  state the new status of slave out
  *         NOTE slave output is default enable
  * @retval None
  */
void ll_spi_slaveoutenable(FunctionalState state)
{
    SPI->CR0_F.IO_DIS = (state ? 0 : 1);
}



/**
  * @brief  This function enables or disable SPI input in Master mode
  *         Disables Reciving data on RXd pin during sending data
  * @param  state the new status of master data in
  *         NOTE master data in is default enable
  * @retval None
  */
void ll_spi_masterinenable(FunctionalState state)
{
    SPI->CR0_F.IO_DIS = (state ? 0 : 1);
}



/**
  * @brief  This function initialize SPI
  * @param  config  a pointer to the spi configuration struct
  * @retval None
  */
void ll_spi_init(SPI_COnfig_t *config)
{
    CRG_CONFIG_UNLOCK();
    CRG->SPI_CLKRST_CTRL_F.RST_SPI = 1;
    __NOP();
    __NOP();
    CRG->SPI_CLKRST_CTRL_F.RST_SPI = 0;
    __NOP();
    __NOP();

    SPI->CR0_F.SLV_MODE = config->SPI_Mode;
    SPI->CR0_F.WIRE_MODE_4 = config->SPI_WireMode;

    SPI->CR0_F.DATA_SIZE_DIS = config->SPI_DataLengthSelect;

    if (config->SPI_DataLengthSelect == SPI_DataLengthSelect_Data)
    {
        SPI->CR0_F.DATA_SIZE = config->SPI_DataLength;
    }
    else if (config->SPI_DataLengthSelect == SPI_DataLengthSelect_Instruction)
    {
        SPI->CR0_F.INS_SIZE = config->SPI_InstructionLength;
    }

    SPI->CR0_F.L_FRAME_EN = config->LongFrame_Enable;
    SPI->CR0_F.CSN_POL_SEL = config->SPI_CSNPolarity;
    SPI->CR0_F.CRC_EN = config->CRC_Enable;
    SPI->CR0_F.LSB_FIRST = config->SPI_Encoding;
    SPI->CR0_F.SPH = config->SPI_ClockPhase;
    SPI->CR0_F.SPO = config->SPI_ClockPolarity;
    SPI->CR0_F.LP_BACK_EN = config->LoopBack_Enable;
    SPI->CPSR_F.FCLK_DIV = config->ClockPrescale;

}



/**
  * @brief  This function configures the spi related IOs
  * @param  w_mode the current spi wiring mode, to be configured based on
  *         this parameter can be any value of @ref SPI_WIREMODE_ENUM
  * @retval None
  */
void ll_spi_ioconfig(SPI_WireMode_t w_mode)
{
    if (w_mode == SPI_WireMode_3Wires)
    {
        ll_gpio_afio_config(GPIO_PIN_3, (gpio_afio_mux_e)GPIO3_SOFTWARE_INPUT_FUNCTION_SPI_CSN);
        ll_gpio_afio_config(GPIO_PIN_1, (gpio_afio_mux_e)GPIO1_SOFTWARE_INPUT_FUNCTION_SPI_CLK);
        ll_gpio_afio_config(GPIO_PIN_2, (gpio_afio_mux_e)GPIO2_SOFTWARE_INPUT_FUNCTION_SPI_DATA);
    }

    else if (w_mode == SPI_WireMode_4Wires)
    {
        ll_gpio_afio_config(GPIO_PIN_3, (gpio_afio_mux_e)GPIO3_SOFTWARE_INPUT_FUNCTION_SPI_CSN);
        ll_gpio_afio_config(GPIO_PIN_1, (gpio_afio_mux_e)GPIO1_SOFTWARE_INPUT_FUNCTION_SPI_CLK);
        ll_gpio_afio_config(GPIO_PIN_4, (gpio_afio_mux_e)GPIO4_SOFTWARE_INPUT_FUNCTION_SPI_TXD);
        ll_gpio_afio_config(GPIO_PIN_2, (gpio_afio_mux_e)GPIO2_SOFTWARE_INPUT_FUNCTION_SPI_RXD);
    }
}



/**
  * @brief  This function configures SPI FIFO
  * @param  fifo selects the fifo to be configured,
  *         this parameter can be any value of @ref SPI_FIFOSELECT_ENUM
  * @param  threshold selects the FIFO threshold value,
  *         this parameter can be any value of @ref SPI_FIFOTHRESHOLD_ENUM
  * @retval None
  */
void ll_spi_fifoconfig(SPI_FifoSelect_t fifo, SPI_FifoThreshold_t threshold)
{
    if (fifo == SPI_FifoSelect_Rx)
    {
        SPI->CR1_F.RX_FIFO_INT_TH = threshold;
    }
    else if (fifo == SPI_FifoSelect_Tx)
    {
        SPI->CR1_F.TX_FIFO_INT_TH = threshold;
    }
}



/**
  * @brief  This function enables or disables SPI
  * @param  state specifies the new state of spi, can be ENABLE or DISABLE
  * @retval None
  */
void ll_spi_cmd(FunctionalState state)
{
    SPI->CR0_F.SPI_EN = (state ? 1 : 0);
}



/**
  * @brief  This function sends data over SPI
  * @param  data a pointer to the data packet
  * @param  length the data length
  * @retval None
  */
void ll_spi_senddata(const uint32_t *data, uint16_t length)
{
    while (length-- > 0)
    {
        SPI->WDR_F.TX_DATA = *data;
        while (SPI->SR_F.TX_FIFO_FULL_FLG != 0);
        data++;
    }

}



/**
  * @brief  This function receives data over SPI
  * @param  a pointer to the buffer where the received data will be stored
  * @param  the data length user wants to receive
  * @retval None
  */
void ll_spi_receivedata(uint32_t *buffer, uint16_t length)
{
    for (uint8_t i = 0; i < length ; i++)
    {
        buffer[i] = SPI->RDR_F.RX_DATA;
    }
}



/**
  * @brief  This function gets SPI status for specific flag
  * @param  status_flag the status flag to get status
  *         this parameter can be any value of @ref SPI_STATUS_ENUM
  * @retval the status of the specified flag
  */
bool ll_spi_statusget(SPI_Status_t status_flag)
{
    return (SPI->SR & 1 << status_flag) ;
}



/**
  * @brief  This function enables spi interrupt
  * @param  spi_int the interrupt to be enabled, this value can be one or
  *         combination of @ref SPI_INTERRUPT_Definitions
  * @retval None
  */
void ll_spi_interruptenable(uint16_t spi_int)
{
    SPI->IMR &= ~(spi_int);
}



/**
  * @brief  This function disables spi interrupt
  * @param  spi_int the interrupt to be disabled,this value can be one or
  *         combination of @ref SPI_INTERRUPT_Definitions
  * @retval None
  */
void ll_spi_interruptdisable(uint16_t spi_int)
{
    SPI->IMR |= spi_int;
}



/**
  * @brief  This function gets the status of a specified spi interrupt flag
  * @param  spi_int the interrupt to read status, this value can be one or
  *          combination of @ref SPI_INTERRUPT_Definitions
  * @retval returns the specified flag's status
  */
bool ll_spi_interruptstatusget(uint16_t spi_int)
{
    return (SPI->ISR & spi_int) ;
}



/**
  * @brief  This function clears the specified spi interrupt flag
  * @param  spi_int the interrupt flag to be cleard this value can be one or
  *          combination of @ref SPI_INTERRUPT_Definitions
  * @retval None
  */
void ll_spi_interruptclear(uint16_t spi_int)
{
    SPI->ICR |= spi_int;
}
