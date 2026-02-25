/**
 *****************************************************************************
 * @brief   sci driver source file.
 *
 * @file    tcae10_ll_sci.c
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

#include "tcae10_ll_sci.h"
#include "tcae10_ll_cortex.h"
#include "tcae10_ll_flash.h"
#include "tcae10_ll_gpio.h"
#include "tcae10_ll_lpm.h"
#include "system_tcae10.h"

static ISR_FUNC_CALLBACK sci_isr_callback[LL_SCI_BUS_MAX - 1] = {NULL};

#define LIN_ISR_FLAG       (0x7FFFFFUL)
#define LIN_CHECKSUM_USE_SW     0
/********************************************************
** \brief   ll_sci_clk_config
**
** \param   ll_sci_bus_e        bus
** \param   ll_clk_config_t*    config
**
** \retval  None
*********************************************************/
static void ll_sci_clk_config(ll_sci_bus_e bus, ll_clk_config_t *config)
{
    CRG_CONFIG_UNLOCK();

    switch (bus)
    {
        case LL_SCI_BUS_0:
            /* enable bus0 pclk */
            CRG->PRINT_UART_CLKRST_CTRL_F.PCLK_EN_PRINT_UART = 1;
            break;

        case LL_SCI_BUS_1:
            /* lin baudrate change, need reset */
            CRG->LIN_SCI_CLKRST_CTRL_F.RST_LIN_SCI = 1;
            CRG->LIN_SCI_CLKRST_CTRL_F.RST_LIN_SCI = 0;

            CRG->LIN_SCI_CLKRST_CTRL_F.PCLK_EN_LIN_SCI = 1;
            CRG->LIN_SCI_CLKRST_CTRL_F.FCLK_EN_LIN_SCI = 1;
            CRG->LIN_SCI_CLKRST_CTRL_F.FCLK_DIV_LIN_SCI = config->fclk_div;
            break;

        case LL_SCI_BUS_2:
            CRG->LIN_SCI1_CLKRST_CTRL_F.RST_LIN_SCI1 = 1;
            CRG->LIN_SCI1_CLKRST_CTRL_F.RST_LIN_SCI1 = 0;

            CRG->LIN_SCI1_CLKRST_CTRL_F.PCLK_EN_LIN_SCI1 = 1;
            CRG->LIN_SCI1_CLKRST_CTRL_F.FCLK_EN_LIN_SCI1 = 1;
            CRG->LIN_SCI1_CLKRST_CTRL_F.FCLK_DIV_LIN_SCI1 = config->fclk_div;
            break;

        default:
            break;
    }

    CRG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_sci_gpio_config
**
** \param   ll_sci_bus_e        bus
** \param   ll_sci_mode_e       mode
**
** \retval  ll_status_e
*********************************************************/
static ll_status_e ll_sci_gpio_config(ll_sci_bus_e bus, ll_sci_mode_e mode)
{
    if (bus >= LL_SCI_BUS_MAX)
    {
        return LL_ERROR;
    }

    switch (bus)
    {
        case LL_SCI_BUS_0:
            ll_gpio_afio_config(GPIO_PIN_2, AFIO_MUX_1);
            //            ll_gpio_afio_config(GPIO_PIN_3, AFIO_MUX_1);
            //            ll_gpio_afio_config(GPIO_PIN_6, AFIO_MUX_2);
            break;

        case LL_SCI_BUS_1:
            if (SCI_MODE_UART == mode)
            {
                ll_gpio_afio_config(GPIO_PIN_7, AFIO_MUX_2);
                ll_gpio_afio_config(GPIO_PIN_8,  AFIO_MUX_2);
            }
            break;

        case LL_SCI_BUS_2:
            ll_gpio_afio_config(GPIO_PIN_3, AFIO_MUX_5);
            ll_gpio_afio_config(GPIO_PIN_4, AFIO_MUX_5);
            break;

        default:
            break;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_sci_state_clear
**
** \param   ll_sci_bus_e            bus
** \param   ll_sci_clear_type_e     type
**
** \retval  None
*********************************************************/
void ll_sci_state_clear(ll_sci_bus_e bus, ll_sci_clear_type_e type)
{
    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

    if (!type || bus < LL_SCI_BUS_1)
    {
        return;
    }

    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR :
                                          LIN_SCI1_BASE_ADDR);

    if (type & SCI_CLEAR_TX_FIFO)
    {
        lin_sci_reg->CTRL_F.TX_FIFO_CLR = 1;
    }

    if (type & SCI_CLEAR_RX_FIFO)
    {
        lin_sci_reg->CTRL_F.RX_FIFO_CLR = 1;
    }

    if (type & SCI_CLEAR_TX_ABORT)
    {
        lin_sci_reg->CTRL_F.TX_ABORT = 1;
    }

    if (type & SCI_CLEAR_RX_ABORT)
    {
        lin_sci_reg->CTRL_F.RX_ABORT = 1;
    }
}

/********************************************************
** \brief   ll_sci_contrl_config
**
** \param   ll_sci_bus_e        bus
** \param   ll_sci_mode_e       mode
**
** \retval  None
*********************************************************/
static void ll_sci_contrl_config(ll_sci_bus_e bus, ll_sci_mode_e mode)
{
    uint32_t reg_val = 0;

    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

    if (bus < LL_SCI_BUS_1)
    {
        return;
    }

    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR :
                                          LIN_SCI1_BASE_ADDR);

    /* setup master send config */
    ll_sci_state_clear(bus, (ll_sci_clear_type_e)(SCI_CLEAR_TX_FIFO | SCI_CLEAR_RX_FIFO));

    if (SCI_MODE_UART == mode)
    {
        reg_val |= LIN_SCI_CTRL_GLB_EN_SET(1) | LIN_SCI_CTRL_TX_EN_SET(1) | LIN_SCI_CTRL_RX_EN_SET(1);
        reg_val &= (LIN_SCI_CTRL_TX_NUM_MODE_CLR & LIN_SCI_CTRL_TX_NUM_CLR);
        reg_val &= (LIN_SCI_CTRL_RX_NUM_MODE_CLR & LIN_SCI_CTRL_RX_NUM_CLR);
    }
    else
    {
        reg_val |= LIN_SCI_CTRL_GLB_EN_SET(1) | LIN_SCI_CTRL_RX_EN_SET(1) | LIN_SCI_CTRL_AUTO_BAUD_EN_SET(1);
#if !LIN_CHECKSUM_USE_SW
        reg_val |= LIN_SCI_CTRL_CHKSUM_EN_SET(1) | LIN_SCI_CTRL_CHKSUM_TYPE_SET(1) ; //crc
#else
        reg_val |= LIN_SCI_CTRL_CHKSUM_EN_SET(0);
#endif
        /* reg_val |= LIN_SCI_CTRL_TX_WAIT_FIFO_VLD_EN_SET(1); */
        reg_val |= LIN_SCI_CTRL_TX_NUM_MODE_SET(1) | LIN_SCI_CTRL_TX_NUM_SET(8);
        reg_val |= LIN_SCI_CTRL_RX_NUM_MODE_SET(1) | LIN_SCI_CTRL_RX_NUM_SET(8);
        reg_val |= LIN_SCI_CTRL_SHORT_GND_DET_EN_SET(1) | LIN_SCI_CTRL_BIT_ERR_DET_EN_SET(1);

        if (SCI_MODE_LIN_M == mode)
        {
            reg_val |= LIN_SCI_CTRL_MASTER_EN_SET(1);
        }
    }

    lin_sci_reg->CTRL = reg_val;
}

/********************************************************
** \brief   ll_sci_isr_config
**
** \param   ll_sci_bus_e          bus
** \param   ll_isr_config_t*      config
** \param   AFE_FUNC_CALLBAC      callback
**
** \retval  None
*********************************************************/
static void ll_sci_isr_config(ll_sci_bus_e bus, ll_isr_config_t *config, ISR_FUNC_CALLBACK callback)
{
    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;
    IRQn_Type irq = (LL_SCI_BUS_1 == bus) ? LINSCI_IRQn : LINSCI_UART_IRQn;
    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR :
                                          LIN_SCI1_BASE_ADDR);

    lin_sci_reg->ICR |= LIN_ISR_FLAG;

    if (config->isr_enable)
    {
        lin_sci_reg->IMR &= ~(config->isr & LIN_ISR_FLAG);
        sci_isr_callback[bus - 1] = callback;
        NVIC_SetPriority(irq, config->priority);
    }
    else
    {
        lin_sci_reg->IMR |= LIN_ISR_FLAG;
    }
}

/********************************************************
** \brief   ll_sci_deinit
**
** \param   ll_sci_bus_e            bus
**
** \retval  None
*********************************************************/
void ll_sci_deinit(ll_sci_bus_e bus)
{
    CRG_CONFIG_UNLOCK();

    if (bus == LL_SCI_BUS_0)
    {
        CRG->PRINT_UART_CLKRST_CTRL_F.RST_PRINT_UART = 1 ;
        __NOP();
        __NOP();
        CRG->PRINT_UART_CLKRST_CTRL_F.RST_PRINT_UART = 0 ;
        __NOP();
        __NOP();
    }
    else
    {
        CRG->LIN_SCI_CLKRST_CTRL_F.RST_LIN_SCI = 1;
        __NOP();
        __NOP();
        CRG->LIN_SCI_CLKRST_CTRL_F.RST_LIN_SCI = 0;
        __NOP();
        __NOP();

        NVIC_ClearPendingIRQ(LINSCI_IRQn);
        NVIC_DisableIRQ(LINSCI_IRQn);

        sci_isr_callback[bus - 1] = NULL;
    }

    CRG_CONFIG_LOCK();
}

/********************************************************
** \brief   ll_lin_aa_enable
**
** \param   ll_sci_bus_e            bus
** \param   lin_aa_type_e           type
** \param   bool                    ext_shunt_res
** \param   uint16_t*               cur_th
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_aa_enable(ll_sci_bus_e bus, lin_aa_type_e type, bool ext_shunt_res, uint16_t *cur_th)
{
    if (LL_SCI_BUS_1 != bus)
    {
        return LL_ERROR;
    }

    /* ll_lin_aa_diable, need reset */
    LIN_SCI->ANALOG_CTRL = 4;
    ll_lin_rx_delay_set(bus, 0);

    if (LIN_AA_STYPE_STEPS_2 == type)
    {
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP1 = 0b10001;    /* 1.1mA */
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP2 = 0b11000;    /* 1.1mA */
    }
    else if (LIN_AA_STYPE_STEPS_3 == type)
    {
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP1 = 0b00001;    /*   1mA */
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP2 = 0b00111;    /*   4mA */
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP3 = 0b01111;    /*   8mA */
    }
    else
    {
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP1 = 0b00000;    /* 0.5mA */
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP2 = 0b00011;    /*   2mA */
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP3 = 0b01001;    /*   5mA */
        LIN_SCI->CURRENT_SOURCE_ISET_F.LIN_ISET_STEP4 = 0b01111;    /*   8mA */
    }

    if (!ext_shunt_res)
    {
        uint32_t reg_val = 0xFFF;
        reg_val = REG_READ32(0x00800080);
        reg_val &= 0xFFF;

        if (reg_val != 0xFFF)
        {
            float resistor_ration = (float)reg_val / 800;

            for (uint8_t i = 0; i < 3; i++)
            {
                cur_th[i] = (uint16_t)((uint32_t)cur_th[i] * resistor_ration);
            }
        }
    }

    /* Current threshold for test value 0x043 0x075, 0x0b9, 0x032 */
    LIN_SCI->CUR_TH1_F.CUR_TH_STEP1 = cur_th[0];
    LIN_SCI->CUR_TH1_F.CUR_TH_STEP2 = cur_th[1];
    LIN_SCI->CUR_TH2_F.CUR_TH_STEP3 = cur_th[2];
    LIN_SCI->CUR_TH2_F.CUR_TH_STEP4 = cur_th[3];

    /* Clk deviation time config */
    if (DEFAULT_SYSTEM_CLOCK < 48000000UL)
    {
        if (LIN_AA_STYPE_STEPS_2 == type)
        {
            LIN_SCI->CLK_DEV_TIM_CFG_F.CLK_DEV_TIM = 0x3FF >> 1;
        }
        else
        {
            LIN_SCI->CLK_DEV_TIM_CFG_F.CLK_DEV_TIM = 0x290 >> 1;
            LIN_SCI->CLK_DEV_TIM_CFG_F.CLK_DEV_TIM_DELTA = 0xF0 >> 1;
        }
    }
    else
    {
        if (LIN_AA_STYPE_STEPS_2 == type)
        {
            LIN_SCI->CLK_DEV_TIM_CFG_F.CLK_DEV_TIM = 0x3FF;
        }
        else
        {
            LIN_SCI->CLK_DEV_TIM_CFG_F.CLK_DEV_TIM = 0x290;
            LIN_SCI->CLK_DEV_TIM_CFG_F.CLK_DEV_TIM_DELTA = 0xF0;
        }
    }

    /* Pga ready time config:time base = 20.8ns */
    if (DEFAULT_SYSTEM_CLOCK < 48000000UL)
    {
        if (LIN_AA_STYPE_STEPS_2 == type)
        {
            LIN_SCI->PGA_RDY_TIM_CFG_F.PGA_RDY_TIM =  0xB20 >> 1;
        }
        else
        {
            LIN_SCI->PGA_RDY_TIM_CFG_F.PGA_RDY_TIM =  0xA50 >> 1;
        }
    }
    else
    {
        if (LIN_AA_STYPE_STEPS_2 == type)
        {
            LIN_SCI->PGA_RDY_TIM_CFG_F.PGA_RDY_TIM =  0xB20;
        }
        else
        {
            LIN_SCI->PGA_RDY_TIM_CFG_F.PGA_RDY_TIM =  0xA50;
        }
    }

    /* Auto addressing analog config  */
    if (ext_shunt_res)
    {
        LIN_SCI->AUTO_ADDR_ANA_CFG = 0x04F;
    }
    else
    {
        LIN_SCI->AUTO_ADDR_ANA_CFG = (LIN_AA_STYPE_STEPS_2 == type) ? 0x047 : 0x042;
    }

    /* Auto addressing control */
    LIN_SCI->AUTO_ADDR_CTRL = LIN_SCI_AUTO_ADDR_CTRL_AUTO_ADDR_EN_SET(1) | LIN_SCI_AUTO_ADDR_CTRL_AUTO_ADDR_ANA_EN_SET(1) | LIN_SCI_AUTO_ADDR_CTRL_MEAS_STEP_SEL_SET(type);

    /* LIN_AA interrupt enable */
    LIN_SCI->ICR |= (SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE);
    LIN_SCI->IMR &= ~(SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE);

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_aa_disable
**
** \param   ll_sci_bus_e            bus
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_aa_disable(ll_sci_bus_e bus)
{
    if (LL_SCI_BUS_1 != bus)
    {
        return LL_ERROR;
    }

    LIN_SCI->ICR |= (SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE);
    LIN_SCI->IMR |= (SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE);

    /* current_source_iset */
    LIN_SCI->CURRENT_SOURCE_ISET = 0;

    /* Current threshold */
    LIN_SCI->CUR_TH1 = 0;
    LIN_SCI->CUR_TH2 = 0;

    /* Clk deviation time config */
    LIN_SCI->CLK_DEV_TIM_CFG = 0;

    /* Pga ready time config */
    LIN_SCI->PGA_RDY_TIM_CFG = 0;

    /* Auto addressing analog config  */
    LIN_SCI->AUTO_ADDR_ANA_CFG = 0x04F;

    /* Auto addressing control */
    LIN_SCI->AUTO_ADDR_CTRL = 0x00;

    /* ll_lin_aa_enable, need 4 & 3 */
    LIN_SCI->ANALOG_CTRL = 7;
    ll_lin_rx_delay_set(bus, 3);

    return LL_OK;
}

/********************************************************
** \brief   ll_sci_init
**
** \param   ll_sci_bus_e            bus
** \param   sci_config_t*           config
** \param   ISR_FUNC_CALLBACK       callback
**
** \retval  None
*********************************************************/
void ll_sci_init(ll_sci_bus_e bus, sci_config_t *config, ISR_FUNC_CALLBACK callback)
{
    assert_param(IS_SCI_BUS(bus));
    assert_param(IS_SCI_MODE(config->mode));

    ll_sci_gpio_config(bus, config->mode);
    ll_sci_clk_config(bus, &config->clk_cfg);
    ll_sci_baudrate_config(bus, config->baudrate);

    if (bus == LL_SCI_BUS_0)
    {
    }
    else
    {
        LIN_SCI_REG_TypeDef *lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                           LIN_SCI_BASE_ADDR : LIN_SCI1_BASE_ADDR);

        if (SCI_MODE_UART == config->mode)
        {
            lin_sci_reg->CTRL_UART_F.MODE = 1;
            /* set uart stop 1 bit*/
            lin_sci_reg->CTRL_UART_F.STP_BIT_SEL = 0;
            /* default disable mp mode*/
            // /* set uart MP mode */
            // LIN_SCI->CTRL_UART_F.MP_MODE_EN = 1;
            // LIN_SCI->CTRL_UART_F.MP_RX_ADDR_WR_EN = 1;
            // LIN_SCI->CTRL_UART_F.MP_TX_ADDR_DATA_SEL = 1;
            // /* set uart MP address */
            // LIN_SCI->RX_CFG_F.MP_SLAVE_ADDR = 0;
            // LIN_SCI->RX_CFG_F.MP_SLAVE_ADDR = 0xAA;
            // LIN_SCI->RX_CFG_F.MP_SLAVE_ADDR_MSK = 1;
        }
        else
        {
            lin_sci_reg->CTRL_UART_F.MODE = 0;

            if (SCI_MODE_LIN_M == config->mode)
            {
                config->isr_cfg.isr |= SCI_INT_TX_PID_DONE;
            }
        }

        /* bit error check point sel:0@middle, 1@last */
        lin_sci_reg->TX_CFG_F.CHK_PT_SEL = 1;

        if (config->baudrate > 19200UL)
        {
            /* 高速模式下需要关闭TX_RX检测 */
            config->isr_cfg.isr &= ~SCI_INT_TX_RX_CONF;
        }

        ll_sci_contrl_config(bus, config->mode);
        ll_sci_isr_config(bus, &config->isr_cfg, callback);
    }
}

/********************************************************
** \brief   ll_sci_baudrate_config
**
** \param   ll_sci_bus_e    bus
** \param   uint32_t    baudrate
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_sci_baudrate_config(ll_sci_bus_e bus, uint32_t baudrate)
{
    if (bus >= LL_SCI_BUS_MAX)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_0 == bus)
    {
        /* baudrate = pclk / (prescale + 1) */
        PRINT_UART->PRESCALE_F.PRESCALE = sys_pclk_freq_get() / baudrate - 1;
    }
    else
    {
        uint32_t fclk, div = 0;
        uint32_t frac;
        uint32_t intr;
        LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

        lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                              LIN_SCI_BASE_ADDR : LIN_SCI1_BASE_ADDR);
        if (LL_SCI_BUS_1 == bus)
        {
            div = CRG->LIN_SCI_CLKRST_CTRL_F.FCLK_DIV_LIN_SCI;
        }
        else  if (LL_SCI_BUS_2 == bus)
        {
            div = CRG->LIN_SCI1_CLKRST_CTRL_F.FCLK_DIV_LIN_SCI1;
        }
        /* fclk(sci) = hclk / (div(sci) + 1) */
        fclk = DEFAULT_SYSTEM_CLOCK / (div + 1);

        /* baudrate = fclk / (intr + frac / 16) */
        frac = (fclk >> 4) % baudrate;
        frac = (frac << 4) / baudrate;
        intr = (fclk >> 4) / baudrate;
        lin_sci_reg->BAUD_CFG = ((frac & 0xF) << 12) | (intr & 0x1FF);

        if (baudrate > 19200UL)
        {
            lin_sci_reg->RX_FILTER_CFG_F.RX_FILTER_TIM = 8;
            lin_sci_reg->ANALOG_CTRL = 0;
            ll_lin_rx_delay_set(bus, 0);
            TEST_CONFIG_UNLOCK();
            TEST->TEST_LIN_CTRL_F.LIN_EMC_FBNEG_EN = false;
            TEST_CONFIG_LOCK();
        }
        else
        {
            lin_sci_reg->RX_FILTER_CFG_F.RX_FILTER_TIM = 200;
            lin_sci_reg->ANALOG_CTRL = 7;
            ll_lin_rx_delay_set(bus, 3);
            TEST_CONFIG_UNLOCK();
            TEST->TEST_LIN_CTRL_F.LIN_EMC_FBNEG_EN = true;
            TEST_CONFIG_LOCK();
        }
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_sci_isr_enable
**
** \param   ll_sci_bus_e    bus
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_sci_isr_enable(ll_sci_bus_e bus, bool enable)
{
    if (bus >= LL_SCI_BUS_MAX || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    IRQn_Type irq = (LL_SCI_BUS_1 == bus) ? LINSCI_IRQn : LINSCI_UART_IRQn;

    NVIC_ClearPendingIRQ(irq);

    if (enable)
    {
        /* TODO: lin speed: 10ms need change priority? */
        NVIC_EnableIRQ(irq);
    }
    else
    {
        NVIC_DisableIRQ(irq);
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_rx_delay_set
**
** \param   ll_sci_bus_e    bus
** \param   uint8_t         count
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_rx_delay_set(ll_sci_bus_e bus, uint8_t count)
{
    if (bus >= LL_SCI_BUS_MAX || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        TEST_CONFIG_UNLOCK();
        TEST->TEST_LIN_CTRL_F.LIN_RX_DELAY = count;
        TEST_CONFIG_LOCK();
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_wakeup_enable
**
** \param   ll_sci_bus_e    bus
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_wakeup_enable(ll_sci_bus_e bus, bool enable)
{
    if (LL_SCI_BUS_1 != bus)
    {
        return LL_ERROR;
    }

    ll_wakeup_init(WAKEUP_SOUERCE_LIN, WAKEUP_TIME_5, WAKEUP_FILTER_3);

    ll_syscfg_isr_enable(ASYSCFG_INT_WAKEUP, enable);

    NVIC_SetPriority(AON_IRQn, 3);
    NVIC_EnableIRQ(AON_IRQn);

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_aa_ready_set
**
** \param   ll_sci_bus_e    bus
** \param   bool            enable
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_aa_ready_set(ll_sci_bus_e bus, bool enable)
{
    if (LL_SCI_BUS_1 != bus)
    {
        return LL_ERROR;
    }

    LIN_SCI->AUTO_ADDR_CTRL_F.ADDR_ALREADY_FLAG = enable ? 1 : 0;

    return LL_OK;
}

/********************************************************
** \brief   ll_sci_transmit
**
** \param   ll_sci_bus_e   bus
** \param   uint8_t*        buffer
** \param   uint16_t        length
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_sci_transmit(ll_sci_bus_e bus, uint8_t *buffer, uint16_t length)
{
    if (bus >= LL_SCI_BUS_MAX || NULL == buffer || !length)
    {
        return LL_ERROR;
    }

    for (uint16_t i = 0; i < length; i++)
    {
        switch (bus)
        {
            case LL_SCI_BUS_0:
                while (PRINT_UART->STATUS_F.TX_BUSY == 1);
                PRINT_UART->TX_DATA_F.TX_DATA = buffer[i];
                break;

            case LL_SCI_BUS_1:
                while (LIN_SCI->STATUS_F.TX_FIFO_FULL);
                LIN_SCI->TX_DATA_F.TX_DATA = buffer[i];
                break;

            case LL_SCI_BUS_2:
                while (LIN_SCI1->STATUS_F.TX_FIFO_FULL);
                LIN_SCI1->TX_DATA_F.TX_DATA = buffer[i];
                break;

            default:
                break;
        }
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_sci_receive
**
** \param   ll_sci_bus_e    bus
** \param   uint8_t*        buffer
** \param   uint16_t        length
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_sci_receive(ll_sci_bus_e bus, uint8_t *buffer, uint16_t length)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus || NULL == buffer || !length)
    {
        return LL_ERROR;
    }

    for (uint16_t i = 0; i < length; i++)
    {
        if (LL_SCI_BUS_1 == bus)
        {
            buffer[i] = LIN_SCI->RX_DATA_F.RX_DATA;
        }
        else
        {
            buffer[i] = LIN_SCI1->RX_DATA_F.RX_DATA;
        }
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_transmit
**
** \param   ll_sci_bus_e        bus
** \param   uint8_t             pid
** \param   uint8_t*            buffer
** \param   uint16_t            length
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_transmit(ll_sci_bus_e bus, uint8_t pid, uint8_t *buffer, uint16_t length)
{
    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus || NULL == buffer || !length)
    {
        return LL_ERROR;
    }

#if !LIN_CHECKSUM_USE_SW
    ll_lin_checksum_e checksum_type = ((0x3C == pid) || (0x7D == pid)) ? LIN_CHECKSUM_CLASSIC : LIN_CHECKSUM_ENHANCED;
#endif

    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR : LIN_SCI1_BASE_ADDR);

    //pid 中断先于 stop error中断，发送前先查询是否有stop error并做相应TX RX ABORT处理，避免发出无效数据
    for (int i = 0; i < 100; ++i)       //等待足够时间，让stop error置位
    {
        __NOP();
    }
    if (lin_sci_reg->ISR & SCI_INT_RX_STP_ERR)
    {
        lin_sci_reg->ICR |= SCI_INT_RX_STP_ERR;
        ll_sci_state_clear(bus, (ll_sci_clear_type_e)(SCI_CLEAR_TX_ABORT | SCI_CLEAR_RX_ABORT));
        return LL_COMM_ERROR;
    }

    lin_sci_reg->CTRL_F.TX_EN = 0;

    //First: clear tx fifo
    ll_sci_state_clear(bus, SCI_CLEAR_TX_FIFO);

#if !LIN_CHECKSUM_USE_SW
    lin_sci_reg->CTRL_F.CHKSUM_TYPE = (LIN_CHECKSUM_CLASSIC == checksum_type) ? 0 : 1;
    lin_sci_reg->CTRL_F.TX_NUM = length;
#endif

    lin_sci_reg->CTRL_F.TX_EN = 1;

    length = (length > 4) ? 4 : length;
    for (uint8_t i = 0; i < length; i++)
    {
        while (lin_sci_reg->STATUS_F.TX_FIFO_FULL);
        lin_sci_reg->TX_DATA_F.TX_DATA = buffer[i];
    }

#if LIN_CHECKSUM_USE_SW

    while (lin_sci_reg->STATUS_F.TX_FIFO_FULL);

    lin_sci_reg->TX_DATA_F.TX_DATA = ll_lin_checksum_calib_func(pid, buffer, length);
#endif

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_receive
**
** \param   ll_sci_bus_e        bus
** \param   uint8_t             pid
** \param   uint8_t*            buffer
** \param   uint16_t            length
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_receive(ll_sci_bus_e bus, uint8_t pid, uint8_t *buffer,  uint16_t length)
{
    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus || NULL == buffer || !length)
    {
        return LL_ERROR;
    }

    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR : LIN_SCI1_BASE_ADDR);

    lin_sci_reg->CTRL_F.TX_EN = 0;
    lin_sci_reg->CTRL_F.RX_EN = 1;

    ll_sci_state_clear(bus, SCI_CLEAR_RX_FIFO);

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_checksum_calib_func
**
** \param   uint8_t             pid
** \param   uint8_t*            buffer
** \param   uint16_t            length
**
** \retval  None
*********************************************************/
uint8_t ll_lin_checksum_calib_func(uint8_t pid, uint8_t *buffer, uint16_t length)
{
    uint16_t check_sum;

    /* 1. PID correspond to Master request and Slave response,
     * their checksum cal is classic the non-diagnostic frame is calculated in Enhanced
     */
    check_sum = ((0x3C == pid) || (0x7D == pid))  ? 0 : pid;

    for (uint8_t i = 0; i < length; i++)
    {

        check_sum += buffer[i];

        /* 2. to deal with the carry */
        if (check_sum > 0xFF)
        {
            check_sum -= 0xFF;
        }
    }

    /* 3. to reverse */
    return (uint8_t)(~check_sum);
}

/********************************************************
** \brief   ll_lin_pid_read
**
** \param   ll_sci_bus_e    bus
** \param   uint8_t*        pid
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_pid_read(ll_sci_bus_e bus, uint8_t *pid)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        *pid = LIN_SCI->RX_PID_F.RX_PID;
    }
    else
    {
        *pid = LIN_SCI1->RX_PID_F.RX_PID;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_read_byte
**
** \param   ll_sci_bus_e    bus
** \param   uint8_t*        byte
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_read_byte(ll_sci_bus_e bus, uint8_t *byte)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus || NULL == byte)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        *byte = LIN_SCI->RX_DATA_F.RX_DATA;
    }
    else
    {

        *byte = LIN_SCI1->RX_DATA_F.RX_DATA;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_auto_baudrate_read
**
** \param   ll_sci_bus_e    bus
** \param   uint32_t*       baud
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_auto_baudrate_read(ll_sci_bus_e bus, uint32_t *baud)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        *baud = LIN_SCI->AUTO_BAUD_VAL_F.AUTO_BD_INTR;
    }
    else
    {
        *baud = LIN_SCI1->AUTO_BAUD_VAL_F.AUTO_BD_INTR;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_baudrate_read
**
** \param   ll_sci_bus_e    bus
** \param   uint32_t*       baud
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_baudrate_read(ll_sci_bus_e bus, uint32_t *baud)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        *baud = LIN_SCI->BAUD_CFG_F.BD_INTR;
    }
    else
    {
        *baud = LIN_SCI1->BAUD_CFG_F.BD_INTR;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_ctrl_glben
**
** \param   ll_sci_bus_e    bus
** \param   bool            sw
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_ctrl_glben(ll_sci_bus_e bus, bool sw)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        LIN_SCI->CTRL_F.GLB_EN = sw;
    }
    else
    {
        LIN_SCI1->CTRL_F.GLB_EN = sw;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_ctrl_rx_abort
**
** \param   ll_sci_bus_e    bus
** \param   bool            sw
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_ctrl_rx_abort(ll_sci_bus_e bus, bool sw)
{
    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    if (LL_SCI_BUS_1 == bus)
    {
        LIN_SCI->CTRL_F.RX_ABORT = sw;
    }
    else
    {
        LIN_SCI1->CTRL_F.RX_ABORT = sw;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_ctrl_brk_tx
**
** \param   ll_sci_bus_e    bus
** \param   uint8_t         brk_num
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_ctrl_brk_tx(ll_sci_bus_e bus, uint8_t brk_num)
{
    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR : LIN_SCI1_BASE_ADDR);

    lin_sci_reg->BRK_SYNC_CFG_F.BRK_NUM = brk_num;
    lin_sci_reg->CTRL_F.BRK_TX_TRIG = true;

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_tx_header
**
** \param   ll_sci_bus_e    bus
** \param   uint8_t         pid
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_tx_header(ll_sci_bus_e bus, uint8_t pid)
{
    LIN_SCI_REG_TypeDef *lin_sci_reg = NULL;

    if (bus >= LL_SCI_BUS_MAX  || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    lin_sci_reg = (LIN_SCI_REG_TypeDef *)((LL_SCI_BUS_1 == bus) ?
                                          LIN_SCI_BASE_ADDR : LIN_SCI1_BASE_ADDR);

    lin_sci_reg->CTRL_F.RX_EN = 0;
    lin_sci_reg->TX_CFG_F.TX_PID = pid;
    lin_sci_reg->CTRL_F.BRK_TX_TRIG = true;

    return LL_OK;
}

/********************************************************
** \brief   SCI_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
void SCI_IRQHandler(void)
{
    uint32_t isr = LIN_SCI->ISR & LIN_ISR_FLAG;

    if (isr)
    {
        if (NULL != sci_isr_callback[0])
        {
            sci_isr_callback[0](isr);
        }

        LIN_SCI->ICR |= isr;
    }
}

/********************************************************
** \brief   UART_IRQHandler
**
** \param   None
**
** \retval  None
*********************************************************/
void UART_IRQHandler(void)
{
    uint32_t isr = LIN_SCI1->ISR & LIN_ISR_FLAG;

    if (isr)
    {
        if (NULL != sci_isr_callback[1])
        {
            sci_isr_callback[1](isr);
        }

        LIN_SCI1->ICR |= isr;
    }
}
