/**
 *****************************************************************************
 * @brief   sci driver source file.
 *
 * @file    tcpl01x_ll_sci.c
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

#include "tcpl01x_ll_sci.h"
#include "tcpl01x_ll_cortex.h"
#include "tcpl01x_ll_flash.h"

static uint32_t sci_isr0_flag = 0;
static uint32_t sci_isr1_flag = 0;

static ISR_FUNC_CALLBACK sci_isr_callback = NULL;

#define LIN_ISR0_FLAG       (0x1FFFFE00UL)
#define LIN_ISR1_FLAG       (0x3F00UL)

#define LIN_WAKEUP_ENABLE   (0x31UL)
#define LIN_WAKEUP_DISABLE  (0x30UL)

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
    uint32_t reg_val = 0;

    AFE_CLOCK_CONFIG_UNLOCK();

    switch (bus)
    {
        case LL_SCI_BUS_0:
            CRG->PRINT_UART_CLKRST_CTRL_F.PCLK_EN_PRINT_UART = 1;
            break;

        case LL_SCI_BUS_1:

            //clk rtst
            afe_bit_set(&AFE_CRG->LIN_SCI_CLKRST_CTRL, AFE_CRG_LIN_SCI_CLKRST_CTRL_RST_LIN_SCI_SHIFT);
            afe_bit_clear(&AFE_CRG->LIN_SCI_CLKRST_CTRL, AFE_CRG_LIN_SCI_CLKRST_CTRL_RST_LIN_SCI_SHIFT);
            //fclk div config
            reg_val = AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_SEL_LIN_SCI_SET(config->clk_source) | AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_EN_LIN_SCI_SET(1) | AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_SET(config->fclk_div);
            afe_reg_write(&AFE_CRG->LIN_SCI_CLKRST_CTRL, reg_val);
            break;

        default:
            break;
    }

    AFE_CLOCK_CONFIG_LOCK();
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

    uint32_t reg_val = 0;

    if (bus == LL_SCI_BUS_0)
    {
        reg_val |= AFE_PINMUX_OUT0_CFG_OUT0_SRC_SEL_SET(3);
        afe_reg_write(&AFE_PINMUX->OUT0_CFG, reg_val);

        PINMUX->LED_DIS_CFG_F.LED_DIS_SRC_SEL = 1;
    }
    else
    {
        if (SCI_MODE_UART == mode)
        {
            reg_val = AFE_PINMUX_OUT1_CFG_OUT1_SRC_SEL_SET(3);
            afe_reg_write(&AFE_PINMUX->OUT1_CFG, reg_val);   //Rx config
            reg_val = AFE_PINMUX_OUT2_CFG_OUT2_SRC_SEL_SET(3);
            afe_reg_write(&AFE_PINMUX->OUT2_CFG, reg_val);   //Tx config
        }
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

    if (!type)
    {
        return;
    }

    uint32_t s_reg_val, c_reg_val = 0;

    /* 设置Master发送相关 */
    afe_reg_read(&LIN_SCI->CTRL, &s_reg_val);
    c_reg_val = s_reg_val;

    if (type & SCI_CLEAR_TX_FIFO)
    {
        c_reg_val  &= LIN_SCI_CTRL_TX_FIFO_CLR_CLR;
        s_reg_val |= LIN_SCI_CTRL_TX_FIFO_CLR_SET(1);
    }

    if (type & SCI_CLEAR_RX_FIFO)
    {
        c_reg_val &= LIN_SCI_CTRL_RX_FIFO_CLR_CLR;
        s_reg_val |= LIN_SCI_CTRL_RX_FIFO_CLR_SET(1);
    }

    if (type & SCI_CLEAR_TX_ABORT)
    {
        c_reg_val &= LIN_SCI_CTRL_TX_ABORT_CLR;
        s_reg_val |= LIN_SCI_CTRL_TX_ABORT_SET(1);
    }

    if (type & SCI_CLEAR_RX_ABORT)
    {
        c_reg_val &= LIN_SCI_CTRL_RX_ABORT_CLR;
        s_reg_val |= LIN_SCI_CTRL_RX_ABORT_SET(1);
    }

    afe_reg_write(&LIN_SCI->CTRL, c_reg_val); //置高前先置低
    /* 清空TX FIFO ☆AFE的trig/clr/abort要先高后低☆ */
    afe_reg_write(&LIN_SCI->CTRL, s_reg_val);
    afe_reg_write(&LIN_SCI->CTRL, c_reg_val);
}

/********************************************************
** \brief   ll_sci_contrl_config
**
** \param   ll_sci_bus_e            bus
** \param   ll_sci_mode_e           mode
**
** \retval  None
*********************************************************/
static void ll_sci_contrl_config(ll_sci_bus_e bus, ll_sci_mode_e mode)
{
    uint32_t reg_val = 0;

    /* 设置Master发送相关 */
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
        reg_val |= LIN_SCI_CTRL_CHKSUM_EN_SET(1) | LIN_SCI_CTRL_CHKSUM_TYPE_SET(1) ; //crc
        reg_val |= LIN_SCI_CTRL_TX_NUM_MODE_SET(1) | LIN_SCI_CTRL_TX_NUM_SET(8);
        reg_val |= LIN_SCI_CTRL_RX_NUM_MODE_SET(1) | LIN_SCI_CTRL_RX_NUM_SET(8);
        reg_val |= LIN_SCI_CTRL_DUTY_CYC_CHK_EN_SET(1) | LIN_SCI_CTRL_BIT_ERR_DET_EN_SET(1);

        if (SCI_MODE_LIN_M == mode)
        {
            reg_val |= LIN_SCI_CTRL_MASTER_EN_SET(1);
        }
    }

    afe_reg_write(&LIN_SCI->CTRL, reg_val);
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
    if (config->isr_enable)
    {

        sci_isr0_flag = config->isr & LIN_ISR0_FLAG;
        sci_isr1_flag = config->isr1 & LIN_ISR1_FLAG; /* int1 use backup flag*/

        sci_isr_callback = callback;

    }
    else
    {
        sci_isr0_flag = 0;
        sci_isr1_flag = 0;
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
    uint32_t reg_val = 0;

    if (bus == LL_SCI_BUS_0)
    {
        CRG->PRINT_UART_CLKRST_CTRL_F.PCLK_EN_PRINT_UART = 0;

        reg_val &= AFE_PINMUX_OUT0_CFG_OUT0_SRC_SEL_CLR;
        afe_reg_write(&AFE_PINMUX->OUT0_CFG, reg_val);

        PINMUX->LED_DIS_CFG_F.LED_DIS_SRC_SEL = 0;
    }
    else
    {
        afe_reg_write(&AFE_PINMUX->OUT1_CFG, 0);   //Rx config
        afe_reg_write(&AFE_PINMUX->OUT2_CFG, 0);   //Tx config
        afe_reg_write(&LIN_SCI->CTRL_UART, 0);
        afe_reg_write(&LIN_SCI->RX_CFG, 0);
        afe_reg_write(&LIN_SCI->CTRL, 0);

        afe_reg_write(&LIN_SCI->BAUD_CFG, 0);

        afe_reg_write(&LIN_SCI->CURRENT_SOURCE_ISET, 0);
        afe_reg_write(&LIN_SCI->CUR_TH1, 0);
        afe_reg_write(&LIN_SCI->CUR_TH2, 0);
        afe_reg_write(&LIN_SCI->CLK_DEV_TIM_CFG, 0);
        afe_reg_write(&LIN_SCI->PGA_RDY_TIM_CFG, 0);
        afe_reg_write(&LIN_SCI->AUTO_ADDR_ANA_CFG, 0x04F);
        afe_reg_write(&LIN_SCI->AUTO_ADDR_CTRL, 0x20);

        afe_syscfg_int_disable(LIN_ISR0_FLAG, LIN_ISR1_FLAG); //disable isr_falg

        sci_isr0_flag = 0;
        sci_isr0_flag = 0;
        sci_isr_callback = NULL;
    }
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

    uint32_t reg_val = 0;

    if (LIN_AA_STYPE_STEPS_2 == type)
    {
        reg_val = LIN_SCI_CURRENT_SOURCE_ISET_LIN_ISET_STEP2_SET(0x04) |
                  LIN_SCI_CURRENT_SOURCE_ISET_LIN_ISET_STEP1_SET(0x00);
    }
    else
    {
        reg_val = LIN_SCI_CURRENT_SOURCE_ISET_LIN_ISET_STEP4_SET(0x0f) |
                  LIN_SCI_CURRENT_SOURCE_ISET_LIN_ISET_STEP3_SET(0x09) |
                  LIN_SCI_CURRENT_SOURCE_ISET_LIN_ISET_STEP2_SET(0x03) |
                  LIN_SCI_CURRENT_SOURCE_ISET_LIN_ISET_STEP1_SET(0x00);
    }

    afe_reg_write(&LIN_SCI->CURRENT_SOURCE_ISET, reg_val);

    if (!ext_shunt_res)
    {
        ll_flash_read(FLASH_TYPE_NVR, 0x00800698, (uint8_t *)&reg_val, sizeof(uint32_t));
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

    /* Current threshold */
    reg_val = LIN_SCI_CUR_TH1_CUR_TH_STEP1_SET(cur_th[0]) | LIN_SCI_CUR_TH1_CUR_TH_STEP2_SET(cur_th[1]);
    // reg_val = 0x00075043; //for test
    afe_reg_write(&LIN_SCI->CUR_TH1, reg_val);
    reg_val = LIN_SCI_CUR_TH2_CUR_TH_STEP3_SET(cur_th[2]) | LIN_SCI_CUR_TH2_CUR_TH_STEP4_SET(cur_th[3]);
    // reg_val = 0x000320B9; //for test
    afe_reg_write(&LIN_SCI->CUR_TH2, reg_val);

    /* Clk deviation time config */
    if (LIN_AA_STYPE_STEPS_2 == type)
    {
        reg_val = LIN_SCI_CLK_DEV_TIM_CFG_CLK_DEV_TIM_SET(0x3FF);
    }
    else
    {
        reg_val = LIN_SCI_CLK_DEV_TIM_CFG_CLK_DEV_TIM_SET(0x290) |
                  LIN_SCI_CLK_DEV_TIM_CFG_CLK_DEV_TIM_DELTA_SET(0xF0);
    }

    afe_reg_write(&LIN_SCI->CLK_DEV_TIM_CFG, reg_val);

    /* Pga ready time config */
    if (LIN_AA_STYPE_STEPS_2 == type)
    {
        reg_val = LIN_SCI_PGA_RDY_TIM_CFG_PGA_RDY_TIM_SET(0xB20);
    }
    else
    {
        reg_val = LIN_SCI_PGA_RDY_TIM_CFG_PGA_RDY_TIM_SET(0xA50);
    }

    afe_reg_write(&LIN_SCI->PGA_RDY_TIM_CFG, reg_val);

    /* Auto addressing analog config  */
    if (ext_shunt_res)
    {
        reg_val = 0x04F;
    }
    else
    {
        reg_val = (LIN_AA_STYPE_STEPS_2 == type) ? 0x047 : 0x042;
    }

    afe_reg_write(&LIN_SCI->AUTO_ADDR_ANA_CFG, reg_val);

    /* Auto addressing control */
    reg_val =  LIN_SCI_AUTO_ADDR_CTRL_AUTO_ADDR_EN_SET(1) | LIN_SCI_AUTO_ADDR_CTRL_AUTO_ADDR_ANA_EN_SET(1) | LIN_SCI_AUTO_ADDR_CTRL_MEAS_STEP_SEL_SET(type);
    afe_reg_write(&LIN_SCI->AUTO_ADDR_CTRL, reg_val);

    /* 使能LIN_AA中断 */
    afe_syscfg_int_flag_clear(SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE, 0);
    afe_syscfg_int_enable(SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE, 0);
    sci_isr0_flag |=  SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE;

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

    uint32_t reg_val = 0;

    sci_isr0_flag &=  AFE_SYSCFG_IMR0_AUTO_ADDR_DONE_INT_MSK_CLR & AFE_SYSCFG_IMR0_SLV_SELECTED_INT_MSK_CLR;

    afe_syscfg_int_disable(SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE, 0);
    afe_syscfg_int_flag_clear(SCI_INT_SLV_SELECTED | SCI_INT_AUTO_ADDR_DONE, 0);

    /* current_source_iset */
    reg_val = 0;
    afe_reg_write(&LIN_SCI->CURRENT_SOURCE_ISET, reg_val);

    /* Current threshold */
    reg_val = 0;
    afe_reg_write(&LIN_SCI->CUR_TH1, reg_val);
    afe_reg_write(&LIN_SCI->CUR_TH2, reg_val);

    /* Clk deviation time config */
    reg_val = 0;
    afe_reg_write(&LIN_SCI->CLK_DEV_TIM_CFG, reg_val);

    /* Pga ready time config */
    reg_val = 0;
    afe_reg_write(&LIN_SCI->PGA_RDY_TIM_CFG, reg_val);

    /* Auto addressing analog config  */
    reg_val = 0x04f;
    afe_reg_write(&LIN_SCI->AUTO_ADDR_ANA_CFG, reg_val);

    /* Auto addressing control */
    reg_val = 0x20;
    afe_reg_write(&LIN_SCI->AUTO_ADDR_CTRL, reg_val);

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

    ll_sci_clk_config(bus, &config->clk_cfg);
    ll_sci_gpio_config(bus, config->mode);
    ll_sci_baudrate_config(bus, config->baudrate);

    if (bus == LL_SCI_BUS_0)
    {

    }
    else
    {
        uint32_t reg_val = 0;
        afe_reg_read(&LIN_SCI->CTRL_UART, &reg_val);

        if (SCI_MODE_UART == config->mode)
        {
            reg_val |= LIN_SCI_CTRL_UART_MODE_SET(1);
            /* 设置串口通信校验位模式 */
            //    reg_val &= LIN_SCI_CTRL_UART_PTY_CHK_EN_CLR;
            //    reg_val |= LIN_SCI_CTRL_UART_PTY_CHK_EN_SET(0x00);
            //    reg_val &= LIN_SCI_CTRL_UART_PTY_MODE_CLR;
            //    reg_val |= LIN_SCI_CTRL_UART_PTY_MODE_SET(0x00);
            /* 设置串口通信停止位的长度 */
            reg_val &= LIN_SCI_CTRL_UART_STP_BIT_SEL_CLR;
            /* 设置串口通信MP模式 */
            reg_val |= LIN_SCI_CTRL_UART_MP_MODE_EN_SET(1);
            reg_val |= LIN_SCI_CTRL_UART_MP_RX_ADDR_WR_EN_SET(1);
            reg_val |= LIN_SCI_CTRL_UART_MP_TX_ADDR_DATA_SEL_SET(1);
            afe_reg_write(&LIN_SCI->CTRL_UART, reg_val);

            /* 设置串口通信MP的地址 */
            afe_reg_read(&LIN_SCI->RX_CFG, &reg_val);
            reg_val &= LIN_SCI_RX_CFG_MP_SLAVE_ADDR_CLR;
            reg_val |= LIN_SCI_RX_CFG_MP_SLAVE_ADDR_SET(0xAA);
            reg_val |= LIN_SCI_RX_CFG_MP_SLAVE_ADDR_MSK_SET(1);
            afe_reg_write(&LIN_SCI->RX_CFG, reg_val);

        }
        else
        {
            reg_val &= LIN_SCI_CTRL_UART_MODE_CLR;
            afe_reg_write(&LIN_SCI->CTRL_UART, reg_val);

            if (SCI_MODE_LIN_M == config->mode)
            {
                config->isr_cfg.isr |= SCI_INT_TX_PID_DONE;
            }

        }

        if (config->baudrate > 19200UL)
        {
            config->isr_cfg.isr &= AFE_SYSCFG_IMR0_TX_RX_CONF_INT_MSK_CLR; //高速模式下需要关闭TX_RX中断
        }

        ll_sci_contrl_config(bus, config->mode);
        ll_sci_isr_config(bus, &config->isr_cfg, callback);
    }
}

/********************************************************
** \brief   ll_sci_baudrate_config
**
** \param   ll_sci_bus_e    bus
** \param   uint32_t        baudrate
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_sci_baudrate_config(ll_sci_bus_e bus, uint32_t baudrate)
{
    if (bus >= LL_SCI_BUS_MAX)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;

    if (LL_SCI_BUS_0 == bus)
    {
        //print uart baudrate:48M/115200-1
        PRINT_UART->PRESCALE_F.PRESCALE = DEFAULT_SYSTEM_CLOCK / baudrate - 1;
    }
    else
    {
        uint32_t fclk, div = 0;
        uint32_t d_div, frac;

        afe_reg_read(&AFE_CRG->GPIO_CLKRST_CTRL, &reg_val); // read config

        div = (AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_MASK & reg_val) >> AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_DIV_LIN_SCI_SHIFT;

        if (reg_val & AFE_CRG_LIN_SCI_CLKRST_CTRL_FCLK_SEL_LIN_SCI_MASK)
        {
            fclk = DEFAULT_RC32K_CLOCK >> div;
        }
        else
        {
            fclk = DEFAULT_AFE_CLOCK >> div;
        }

        /* Fck/(16*Baud_Rate) */
        d_div = fclk >> 4;
        frac = d_div % baudrate;
        frac = (frac << 4) / baudrate;
        d_div  = d_div / baudrate;

        reg_val = ((frac & 0xF) << 12) | (d_div & 0x0F00) | (d_div & 0xFF);

        afe_reg_write(&LIN_SCI->BAUD_CFG, reg_val);

        if (baudrate > 19200UL)
        {

            reg_val = LIN_SCI_RX_FILTER_CFG_RX_FILTER_TIM_SET(0x08); //RX_FILTER_CFG
            afe_reg_write(&LIN_SCI->RX_FILTER_CFG, reg_val);
            afe_reg_write(&LIN_SCI->ANALOG_CTRL, 0x00);
        }
        else
        {
            reg_val = LIN_SCI_RX_FILTER_CFG_RX_FILTER_TIM_SET(0x64);
            afe_reg_write(&LIN_SCI->RX_FILTER_CFG, reg_val);
        }

        ll_lin_rx_delay_clear(bus);
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

    afe_syscfg_int_flag_clear(LIN_ISR0_FLAG, LIN_ISR1_FLAG);

    if (enable)
    {
        afe_syscfg_int_enable(sci_isr0_flag,  sci_isr1_flag); //enable isr_falg
    }
    else
    {
        afe_syscfg_int_disable(LIN_ISR0_FLAG,  LIN_ISR1_FLAG); //enable isr_falg
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_rx_delay_clear
**
** \param   ll_sci_bus_e    bus
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_rx_delay_clear(ll_sci_bus_e bus)
{
    if (bus >= LL_SCI_BUS_MAX || LL_SCI_BUS_0 == bus)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;

    afe_reg_write(&AFE_TEST->TEST_LOCK, 0x76543210);
    afe_reg_read(&AFE_TEST->TEST_LIN_CTRL, &reg_val);
    reg_val &= AFE_TEST_TEST_LIN_CTRL_LIN_RX_DELAY_CLR;
    afe_reg_write(&AFE_TEST->TEST_LIN_CTRL, reg_val);
    afe_reg_write(&AFE_TEST->TEST_LOCK, 0xFEDCBA98);

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

    uint32_t reg_val = enable ? LIN_WAKEUP_ENABLE : LIN_WAKEUP_DISABLE;

    AFE_SYSCFG_UNLOCK();
    afe_reg_write(&AFE_SYSCFG->LIN_WU_CTRL, reg_val);
    AFE_SYSCFG_LOCK();

    if (enable)
    {
        /* Save imr0&imr1 status */
        // afe_isr_mask_get(&imr0, &imr1);
        afe_syscfg_int_enable(0, AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_MASK);
    }
    else
    {
        afe_syscfg_int_disable(0, AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_MASK);
        /* Restore imr0&imr1 status */
        // afe_isr_mask_set(imr0, imr1);
    }

    afe_isr_all_clear();

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

    uint32_t reg_val = 0;

    afe_reg_read(&LIN_SCI->AUTO_ADDR_CTRL, &reg_val);

    if (enable)
    {
        reg_val |= LIN_SCI_AUTO_ADDR_CTRL_ADDR_ALREADY_FLAG_SET(1);
    }
    else
    {
        reg_val &= LIN_SCI_AUTO_ADDR_CTRL_ADDR_ALREADY_FLAG_CLR;
    }

    afe_reg_write(&LIN_SCI->AUTO_ADDR_CTRL, reg_val);
    return LL_OK;
}

/********************************************************
** \brief   ll_sci_transmit
**
** \param   ll_uart_bus_t   bus
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
        if (LL_SCI_BUS_0 == bus)
        {
            while (PRINT_UART->STATUS_F.TX_BUSY == 1);

            PRINT_UART->TX_DATA = buffer[i];
        }
        else
        {
            afe_reg_write(&LIN_SCI->TX_DATA, buffer[i]);
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

    uint32_t reg_val = 0;

    for (uint16_t i = 0; i < length; i++)
    {

        afe_reg_read(&LIN_SCI->RX_DATA, &reg_val);
        buffer[i] = reg_val;
    }

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_transmit
**
** \param   ll_uart_bus_t       bus
** \param   uint8_t             pid
** \param   uint8_t*            buffer
** \param   uint16_t            length
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_transmit(ll_sci_bus_e bus, uint8_t pid, uint8_t *buffer, uint16_t length)
{
    if (bus != LL_SCI_BUS_1 || NULL == buffer || !length)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;

    ll_lin_checksum_e checksum_type = ((0x3C == pid) || (0x7D == pid)) ? LIN_CHECKSUM_CLASSIC : LIN_CHECKSUM_ENHANCED;

    //pid 中断先于 stop error中断，发送前先查询是否有stop error并做相应TX RX ABORT处理，避免发出无效数据
    afe_reg_read(&AFE_SYSCFG->ISR0, &reg_val);

    if (reg_val & AFE_SYSCFG_IMR0_RX_STP_ERR_INT_MSK_MASK)
    {
        afe_syscfg_int_flag_clear(SCI_INT_RX_STP_ERR, 0);
        ll_sci_state_clear(bus, (ll_sci_clear_type_e)(SCI_CLEAR_TX_ABORT | SCI_CLEAR_RX_ABORT));
        return LL_COMM_ERROR;
    }

    //First: clear tx fifo
    ll_sci_state_clear(bus, SCI_CLEAR_TX_FIFO);

    afe_reg_read(&LIN_SCI->CTRL, &reg_val);

    //Second: set to TX mode
    if (LIN_CHECKSUM_CLASSIC == checksum_type)//0x3d should be 0x7d
    {
        reg_val &= LIN_SCI_CTRL_CHKSUM_TYPE_CLR;
    }
    else
    {
        reg_val |= LIN_SCI_CTRL_CHKSUM_TYPE_SET(1);
    }

    reg_val &= LIN_SCI_CTRL_TX_EN_CLR;
    reg_val &= LIN_SCI_CTRL_TX_NUM_CLR;
    reg_val |= LIN_SCI_CTRL_TX_NUM_SET(length);
    afe_reg_write(&LIN_SCI->CTRL, reg_val);

    for (uint16_t i = 0; i < length; i++)
    {
        afe_reg_write(&LIN_SCI->TX_DATA, buffer[i]);
    }

    reg_val |= LIN_SCI_CTRL_TX_EN_SET(1);
    afe_reg_write(&LIN_SCI->CTRL, reg_val);

    return LL_OK;
}

/********************************************************
** \brief   ll_sci_receive
**
** \param   ll_uart_bus_t       bus
** \param   uint8_t             pid
** \param   uint8_t*            buffer
** \param   uint16_t            length
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_receive(ll_sci_bus_e bus, uint8_t pid, uint8_t *buffer, uint16_t length)
{
    if (bus != LL_SCI_BUS_1)
    {
        return LL_ERROR;
    }

    ll_sci_state_clear(bus, SCI_CLEAR_RX_FIFO);

    // afe_reg_read(&LIN_SCI->CTRL, &reg_val);
    // if (LIN_CHECKSUM_CLASSIC == checksum)//0x3d should be 0x7d
    // {
    //     reg_val &= LIN_SCI_CTRL_CHKSUM_TYPE_CLR;
    // }
    // else
    // {
    //     reg_val |= LIN_SCI_CTRL_CHKSUM_TYPE_SET(1);
    // }

    // reg_val &= LIN_SCI_CTRL_TX_EN_CLR;
    // reg_val &= LIN_SCI_CTRL_TX_NUM_CLR;
    // reg_val |= LIN_SCI_CTRL_TX_NUM_SET(length);
    // afe_reg_write(&LIN_SCI->CTRL, reg_val);

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_checksum_calib_func
**
** \param   uint8_t             pid
** \param   uint8_t*            buffer
**
** \retval  None
*********************************************************/
uint8_t ll_lin_checksum_calib_func(uint8_t pid, uint8_t *buffer, uint16_t length)
{
    uint16_t check_sum;

    /* 1. PID correspond to Master request and Slave response, their checksum cal is classic
    the non-diagnostic frame is calculated in Enhanced */
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
** \param   ll_uart_bus_t   bus
** \param   uint8_t*        pid
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_pid_read(ll_sci_bus_e bus, uint8_t *pid)
{

    if (bus != LL_SCI_BUS_1)
    {
        return LL_ERROR;
    }

    uint8_t status = 0;
    (void)(&status);

    uint32_t reg_val = 0;
    afe_reg_read(&LIN_SCI->RX_PID, &reg_val);
    *pid = (uint8_t)reg_val;

    return LL_OK;
}

/********************************************************
** \brief   ll_lin_read_byte
**
** \param   ll_uart_bus_t   bus
** \param   uint8_t*        byte
**
** \retval  ll_status_e
*********************************************************/
ll_status_e ll_lin_read_byte(ll_sci_bus_e bus, uint8_t *byte)
{

    if (bus != LL_SCI_BUS_1)
    {
        return LL_ERROR;
    }

    uint32_t reg_val = 0;
    afe_reg_read(&LIN_SCI->RX_DATA, &reg_val);
    *byte = (uint8_t)reg_val;

    return LL_OK;
}

/********************************************************
** \brief   SCI_IRQHandler
**
** \param   uint32_t        isr0
** \param   uint32_t        isr1
**
** \retval  None
*********************************************************/
__attribute__((section("RAMCODE")))
void SCI_IRQHandler(uint32_t isr0, uint32_t isr1)
{
    uint32_t isr_flag = 0;

    if (isr0 & LIN_ISR0_FLAG || isr1 & LIN_ISR1_FLAG)
    {
        afe_syscfg_int_flag_clear(isr0 & LIN_ISR0_FLAG, isr1 & LIN_ISR1_FLAG);

        if (NULL != sci_isr_callback)
        {
            isr_flag = ((isr0 & sci_isr0_flag) >> 9) | ((isr1 & sci_isr1_flag) << 20);

            sci_isr_callback(isr_flag);
        }
    }
}
