/**
 *****************************************************************************
 * @brief   interrupt Source file.
 *
 * @file    tcpl01x_ll_cortex.c
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

#include "tcpl01x_ll_def.h"
#include "tcpl01x_ll_cortex.h"

extern void SCI_IRQHandler(uint32_t isr0, uint32_t isr1);
extern void ADC_IRQHandler(uint32_t isr0, uint32_t isr1);
extern void PWM_IRQHandler(uint32_t isr0, uint32_t isr1);
extern void GPIO_IRQHandler(uint32_t isr0, uint32_t isr1);
extern void RTC_IRQHandler(uint32_t isr0, uint32_t isr1);
extern void OTP_IRQHandler(uint32_t isr0, uint32_t isr1);

__attribute__((weak)) void SCI_IRQHandler(uint32_t isr0, uint32_t isr1)
{

}

__attribute__((weak)) void ADC_IRQHandler(uint32_t isr0, uint32_t isr1)
{

}

__attribute__((weak)) void PWM_IRQHandler(uint32_t isr0, uint32_t isr1)
{

}

__attribute__((weak)) void GPIO_IRQHandler(uint32_t isr0, uint32_t isr1)
{

}

__attribute__((weak)) void RTC_IRQHandler(uint32_t isr0, uint32_t isr1)
{

}

__attribute__((weak)) void OTP_IRQHandler(uint32_t isr0, uint32_t isr1)
{

}

void NMI_Handler(void)
{
    volatile int a = 0;

    while (0 == a)
    {
        ;
    }
}

void HardFault_Handler(void)
{
    volatile int a = 0;

    while (0 == a)
    {
        ;
    }
}

/********************************************************
** \brief  EnableNvic
**
** \param   uint32_t        irq
** \param   uint8_t         level
** \param   bool            en
**
** \retval  None
**
** \note   the Cortex-M0 or Cortex-M0+/the dynamic changing of the priority
**         level of enabled interrupts or exceptions is not supported,
**         You should setup the priority levels before enabling the interrupts
*********************************************************/
void EnableNvic(uint32_t irq, uint8_t level, bool en)
{
    IRQn_Type enIrq = (IRQn_Type)irq;

    if (AFE_INT_IRQn == irq)
    {
        afe_isr_all_clear();
    }

    NVIC_DisableIRQ(enIrq);
    NVIC_ClearPendingIRQ(enIrq);
    NVIC_SetPriority(enIrq, level);

    if (true == en)
    {
        NVIC_EnableIRQ(enIrq);
    }
    else
    {
    }
}

/********************************************************
** \brief   afe_isr_mask_get
**
** \param   uint32_t*       Imr0
** \param   uint32_t*       Imr1
**
** \retval  None
*********************************************************/
void afe_isr_mask_get(uint32_t *Imr0, uint32_t *Imr1)
{
    uint32_t val = 0;

    AFE_SYSCFG_UNLOCK();

    afe_reg_read(&AFE_SYSCFG->IMR0, &val);
    *Imr0 = val;
    afe_reg_read(&AFE_SYSCFG->IMR1, &val);
    *Imr1 = val;

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   afe_isr_mask_set
**
** \param   uint32_t*       Imr0
** \param   uint32_t*       Imr1
**
** \retval  None
*********************************************************/
void afe_isr_mask_set(uint32_t Imr0, uint32_t Imr1)
{
    AFE_SYSCFG_UNLOCK();

    afe_reg_write(&AFE_SYSCFG->IMR0, Imr0);
    afe_reg_write(&AFE_SYSCFG->IMR1, Imr1);

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   afe_isr_all_clear
**
** \param   None
**
** \retval  None
*********************************************************/
void afe_isr_all_clear(void)
{
    AFE_SYSCFG_UNLOCK();

    afe_reg_write(&AFE_SYSCFG->ICR0, 0xFFFFFFFF);
    afe_reg_write(&AFE_SYSCFG->ICR0, 0);
    afe_reg_write(&AFE_SYSCFG->ICR1, 0xFFFFFFFF);
    afe_reg_write(&AFE_SYSCFG->ICR1, 0);

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   afe_syscfg_int_enable
**
** \param   uint32_t        int0
** \param   uint32_t        int1
**
** \retval  None
*********************************************************/
void afe_syscfg_int_enable(uint32_t int0, uint32_t int1)
{
    uint32_t tmp;

    AFE_SYSCFG_UNLOCK();

    if (int0)
    {
        afe_reg_read(&AFE_SYSCFG->IMR0, &tmp);
        tmp &= ~int0;
        afe_reg_write(&AFE_SYSCFG->IMR0, tmp);
    }

    if (int1)
    {
        afe_reg_read(&AFE_SYSCFG->IMR1, &tmp);
        tmp &= ~int1;
        afe_reg_write(&AFE_SYSCFG->IMR1, tmp);
    }

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   afe_syscfg_int_disable
**
** \param   uint32_t        int0
** \param   uint32_t        int1
**
** \retval  None
*********************************************************/
void afe_syscfg_int_disable(uint32_t int0, uint32_t int1)
{
    uint32_t tmp;

    AFE_SYSCFG_UNLOCK();

    if (int0)
    {
        afe_reg_read(&AFE_SYSCFG->IMR0, &tmp);
        tmp |= int0;
        afe_reg_write(&AFE_SYSCFG->IMR0, tmp);
    }

    if (int1)
    {
        afe_reg_read(&AFE_SYSCFG->IMR1, &tmp);
        tmp |= int1;
        afe_reg_write(&AFE_SYSCFG->IMR1, tmp);
    }

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   used to clear the interrupt flags
**
** \param   uint32_t        int0
** \param   uint32_t        int1
**
** \retval  None
*********************************************************/
void afe_syscfg_int_flag_clear(uint32_t int0, uint32_t int1)
{
    uint32_t tmp;

    AFE_SYSCFG_UNLOCK();

    if (int0)
    {
        afe_reg_read(&AFE_SYSCFG->ICR0, &tmp);
        tmp |= int0;
        afe_reg_write(&AFE_SYSCFG->ICR0, tmp);
        afe_reg_read(&AFE_SYSCFG->ICR0, &tmp);
        tmp &= ~int0;
        afe_reg_write(&AFE_SYSCFG->ICR0, tmp);
    }

    if (int1)
    {
        afe_reg_read(&AFE_SYSCFG->ICR1, &tmp);
        tmp |= int1;
        afe_reg_write(&AFE_SYSCFG->ICR1, tmp);
        afe_reg_read(&AFE_SYSCFG->ICR1, &tmp);
        tmp &= ~int1;
        afe_reg_write(&AFE_SYSCFG->ICR1, tmp);
    }

    AFE_SYSCFG_LOCK();
}

/********************************************************
** \brief   used to get the status of the event occur
**
** \param   uint32_t        int0
** \param   uint32_t        int1
**
** \retval  None
*********************************************************/
bool afe_syscfg_event_status_get(uint32_t int0, uint32_t int1)
{
    uint8_t status = 0;
    (void)(&status);
    uint32_t reg_val;

    if (NULL != int0)
    {
        afe_reg_read(&AFE_SYSCFG->IRSR0, &reg_val);

        if (reg_val & int0)
        {
            return true;
        }
    }

    if (NULL != int1)
    {
        afe_reg_read(&AFE_SYSCFG->IRSR1, &reg_val);

        if (reg_val & int1)
        {
            return true;
        }
    }

    return false;
}

/********************************************************
** \brief   Sets the clock speed for SPI which is used to communicate to AFE
**
** \param   uint8_t         clk_div
**
** \retval  None
*********************************************************/
void afe_com_init(uint8_t clk_div)
{
    PINMUX->INT_IO0_CFG_F.INT_IO0_SRC_SEL = 1;
    PINMUX->INT_IO1_CFG_F.INT_IO1_SRC_SEL = 1;
    PINMUX->INT_IO2_CFG_F.INT_IO2_SRC_SEL = 1;
    PINMUX->INT_IO3_CFG_F.INT_IO3_SRC_SEL = 1;
    AFE_COM->CTRL_F.CLK_DIV = (uint8_t) clk_div;
}

/********************************************************
** \brief   Gets the AFE Communication address
**
** \param   None
**
** \retval  uint16_t
*********************************************************/
uint16_t afe_com_address_get(void)
{
    return (AFE_COM->ADDR_F.COM_ADDR);
}

/********************************************************
** \brief   Gets the AFE Communication address
**
** \param   uint8_t         it_bit
** \param   bool            enbale
**
** \retval  None
*********************************************************/
void afe_com_isr_enable(uint8_t it_bit, bool enbale)
{
    if (enbale)
    {
        AFE_COM->IMR &= ~(it_bit);
    }
    else
    {
        AFE_COM->IMR |= it_bit;
    }
}

/********************************************************
** \brief   Clears AFE Communication interrupt flag
**
** \param   uint8_t         it_bit
**
** \retval  None
*********************************************************/
void afe_com_isr_flag_clear(uint8_t it_bit)
{
    AFE_COM->ICR |= it_bit;
}

/********************************************************
** \brief   Gets AFE Communication interrupt status
**
** \param   None
**
** \retval  uint8_t
*********************************************************/
uint8_t afe_com_isr_flag_get(void)
{
    return (AFE_COM->ISR);
}

/********************************************************
** \brief   afe_com_crc_enable
**
** \param   bool        enable
**
** \retval  None
*********************************************************/
void afe_com_crc_enable(bool enable)
{
    *(uint32_t *)0x4000FFFC = enable ? 0xAA5015FA : 0x550A05FB;

    while (AFE_COM->ADDR_F.BUSY);
}

/********************************************************
** \brief   afe_reg_write
**
** \param   volatile uint32_t*      reg
** \param   uint32_t                val
**
** \retval  uint8_t
*********************************************************/
uint8_t afe_reg_write(volatile uint32_t *reg, uint32_t val)
{
    uint8_t status;

    __disable_irq();

    *reg = val;

    while (!(AFE_COM->IRSR & 0x4));

    status = AFE_COM->IRSR;
    AFE_COM->ICR = AFE_COM->IRSR;

    __enable_irq();

    return status;
}

/********************************************************
** \brief   afe_reg_read
**
** \param   volatile uint32_t*      reg
** \param   uint32_t                val
**
** \retval  uint8_t
*********************************************************/
uint8_t afe_reg_read(volatile uint32_t *reg, uint32_t *val)
{
    uint8_t status;

    __disable_irq();

    *val = *reg;

    while (!(AFE_COM->IRSR & 0x4));

    status = AFE_COM->IRSR;
    *val = AFE_COM->RDATA_F.COM_RDATA;
    AFE_COM->ICR = AFE_COM->IRSR;

    __enable_irq();

    return status;
}

/********************************************************
** \brief   afe_bit_set
**
** \param   volatile uint32_t*      reg
** \param   uint32_t                pos
**
** \retval  None
*********************************************************/
void afe_bit_set(volatile uint32_t *reg, uint32_t pos)
{
    uint32_t temp = 0;

    afe_reg_read(reg, &temp);
    temp |= (1 << pos);
    afe_reg_write(reg, temp);
}

/********************************************************
** \brief   afe_bit_clear
**
** \param   volatile uint32_t*      reg
** \param   uint32_t                pos
**
** \retval  None
*********************************************************/
void afe_bit_clear(volatile uint32_t *reg, uint32_t pos)
{
    uint32_t temp = 0;

    afe_reg_read(reg, &temp);
    temp &= ~(1 << pos);
    afe_reg_write(reg, temp);
}

/********************************************************
** \brief   afe_bit_read
**
** \param   volatile uint32_t*      reg
** \param   uint32_t                pos
** \param   uint32_t*               val
**
** \retval  None
*********************************************************/
void afe_bit_read(volatile uint32_t *reg, uint32_t pos, uint32_t *val)
{
    afe_reg_read(reg, val);
    *val &= (1 << pos);
}

/********************************************************
** \brief   AFE_INT_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
void AFE_INT_IRQHandler(void)
{
    uint32_t isr0, isr1;
    afe_reg_read(&AFE_SYSCFG->ISR0, &isr0);
    afe_reg_read(&AFE_SYSCFG->ISR1, &isr1);

    SCI_IRQHandler(isr0, isr1);

    PWM_IRQHandler(isr0, isr1);
    ADC_IRQHandler(isr0, isr1);
    GPIO_IRQHandler(isr0, isr1);
    RTC_IRQHandler(isr0, isr1);
    OTP_IRQHandler(isr0, isr1);
}
