/**
 *****************************************************************************
 * @brief   sci driver header.
 *
 * @file    tcpl01x_ll_sci.h
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

#ifndef __TCPL01X_LL_SCI_H__
#define __TCPL01X_LL_SCI_H__

#include "tcpl01x_ll_def.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define SCI_INT_OFFSET                (AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_SHIFT)
#define SCI_INT_OFFSET1               (AFE_SYSCFG_IMR0_TX_1BYTE_DONE_INT_MSK_SHIFT - AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_SHIFT - \
                                        AFE_SYSCFG_IMR1_BUS_IDLE_DET_INT_MSK_SHIFT + 1)
/* int0*/
#define SCI_INT_RX_1BYTE_DONE         AFE_SYSCFG_IMR0_RX_1BYTE_DONE_INT_MSK_MASK              //Mask LIN receive each byte data done interrupt.
#define SCI_INT_RX_DONE               AFE_SYSCFG_IMR0_RX_DONE_INT_MSK_MASK                    //Mask LIN receive all data done(when rx_num_mode =1) interrupt
#define SCI_INT_RX_PID_DONE           AFE_SYSCFG_IMR0_RX_PID_DONE_INT_MSK_MASK                //Mask LIN receive pid done interrupt.
#define SCI_INT_RX_PTY_CHK_ERR        AFE_SYSCFG_IMR0_RX_PTY_CHK_ERR_INT_MSK_MASK             //Mask LIN receive parity check error interrupt(in LIN parity check only in PID).
#define SCI_INT_RX_CHKSUM_ERR         AFE_SYSCFG_IMR0_RX_CHKSUM_ERR_INT_MSK_MASK              //Mask LIN receive checksum error interrupt.
#define SCI_INT_RX_STP_ERR            AFE_SYSCFG_IMR0_RX_STP_ERR_INT_MSK_MASK                 //Mask LIN receive no stop bit error interrupt.
#define SCI_INT_RX_FIFO_FULL          AFE_SYSCFG_IMR0_RX_FIFO_FULL_INT_MSK_MASK               //Mask LIN receive fifo full interrupt
#define SCI_INT_RX_FIFO_OVF_ERR       AFE_SYSCFG_IMR0_RX_FIFO_OVF_ERR_INT_MSK_MASK            //Mask LIN receive fifo overflow interrupt.
#define SCI_INT_TX_DONE               AFE_SYSCFG_IMR0_TX_DONE_INT_MSK_MASK                    //Mask LIN transmit done(when tx_num_mode =1) interrupt
#define SCI_INT_TX_FIFO_EMPTY         AFE_SYSCFG_IMR0_TX_FIFO_EMPTY_INT_MSK_MASK              //Mask LIN transmit fifo empty interrupt
#define SCI_INT_TX_COL_DET_ERR        AFE_SYSCFG_IMR0_TX_COL_DET_ERR_INT_MSK_MASK             //Mask LIN transmit collision detect error interrupt.
#define SCI_INT_BRK_DET               AFE_SYSCFG_IMR0_BRK_DET_INT_MSK_MASK                    //Mask LIN break bits detect interrupt.
#define SCI_INT_SYNC_DET              AFE_SYSCFG_IMR0_SYNC_DET_INT_MSK_MASK                   //Mask LIN sync bits detect interrupt.
#define SCI_INT_SYNC_VAL_ERR          AFE_SYSCFG_IMR0_SYNC_VAL_ERR_INT_MSK_MASK               //Mask LIN sync value check error interrupt.
#define SCI_INT_RX_TIMEOUT            AFE_SYSCFG_IMR0_RX_TIMEOUT_INT_MSK_MASK                 //Mask LIN rx time out interrupt.
#define SCI_INT_TX_PID_DONE           AFE_SYSCFG_IMR0_TX_PID_DONE_INT_MSK_MASK                //Mask LIN tx pid done interrupt.
#define SCI_INT_TX_RX_CONF            AFE_SYSCFG_IMR0_TX_RX_CONF_INT_MSK_MASK                 //Mask LIN tx rx conflict interrupt.
#define SCI_INT_SLV_SELECTED          AFE_SYSCFG_IMR0_SLV_SELECTED_INT_MSK_MASK               //Mask LIN auto address slave selected interrupt
#define SCI_INT_AUTO_ADDR_DONE        AFE_SYSCFG_IMR0_AUTO_ADDR_DONE_INT_MSK_MASK             //Mask LIN auto address done interrupt
#define SCI_INT_TX_1BYTE_DONE         AFE_SYSCFG_IMR0_TX_1BYTE_DONE_INT_MSK_MASK              //Mask LIN transmit 1 byte done interrupt
/* int1*/
#define SCI_INT_BUS_IDLE_DET          AFE_SYSCFG_IMR1_BUS_IDLE_DET_INT_MSK_MASK               //Mask LIN bus idle detect interrupt.
#define SCI_INT_WAKE_UP_DET           AFE_SYSCFG_IMR1_WAKE_UP_DET_INT_MSK_MASK                //Mask LIN RXD wake up interrupt
#define SCI_INT_SLV_TX_BRK_DONE       AFE_SYSCFG_IMR1_SLV_TX_BRK_DONE_INT_MSK_MASK            //Mask LIN slave tx break done interrupt
#define SCI_INT_MP_MODE_ADDR          AFE_SYSCFG_IMR1_MP_MODE_ADDR_INT_MSK_MASK               //Mask LIN multi_processor mode address received interrupt
#define SCI_INT_AUTO_ADDR_START       AFE_SYSCFG_IMR1_AUTO_ADDR_START_INT_MSK_MASK            //Mask LIN auto addressing start interrupt
#define SCI_INT_ADDR_1BIT             AFE_SYSCFG_IMR1_AUTO_ADDR_1BIT_INT_MSK_MASK             //Mask LIN auto addressing 1 bit interrupt

/**
  * @brief  ll sci bus enumeration
  */
typedef enum
{
    LL_SCI_BUS_0 = 0,
    LL_SCI_BUS_1,
    LL_SCI_BUS_MAX
} ll_sci_bus_e;

/**
  * @brief  ll sic mode enumeration
  */
typedef enum
{
    SCI_MODE_LIN_S         = 0,
    SCI_MODE_LIN_M,
    SCI_MODE_UART,
    SCI_MODE_MAX,
} ll_sci_mode_e;

/**
  * @brief  ll sic clear enumeration
  */
typedef enum
{
    SCI_CLEAR_NULL          = (0),
    SCI_CLEAR_TX_FIFO     = (0x01 << 0),
    SCI_CLEAR_RX_FIFO     = (0x01 << 1),
    SCI_CLEAR_TX_ABORT    = (0x01 << 2),
    SCI_CLEAR_RX_ABORT    = (0x01 << 3),
} ll_sci_clear_type_e;

/**
  * @brief  ll sic mode enumeration
  */
typedef enum
{
    LIN_CHECKSUM_CLASSIC           = 0,
    LIN_CHECKSUM_ENHANCED          = 1,
    LIN_CHECKSUM_MAX,
} ll_lin_checksum_e;

typedef struct
{
    ll_clk_config_t clk_cfg;
    ll_isr_config_t isr_cfg;
    ll_sci_mode_e mode;
    uint32_t baudrate;
} sci_config_t;

#define IS_SCI_BUS(__BUS__)         (((__BUS__) == LL_SCI_BUS_0) || ((__BUS__) ==LL_SCI_BUS_1) )
#define IS_SCI_MODE(__MODE__)       ((__MODE__) < SCI_MODE_MAX )

void ll_sci_deinit(ll_sci_bus_e bus);
void ll_sci_init(ll_sci_bus_e bus, sci_config_t *config, ISR_FUNC_CALLBACK callback);
ll_status_e ll_sci_baudrate_config(ll_sci_bus_e bus, uint32_t baudrate);
ll_status_e ll_sci_isr_enable(ll_sci_bus_e bus, bool enable);
void ll_sci_state_clear(ll_sci_bus_e bus, ll_sci_clear_type_e type);
ll_status_e ll_lin_rx_delay_clear(ll_sci_bus_e bus);
ll_status_e ll_lin_wakeup_enable(ll_sci_bus_e bus, bool enable);
ll_status_e ll_lin_aa_enable(ll_sci_bus_e bus, lin_aa_type_e type, bool ext_shunt_res, uint16_t *cur_th);
ll_status_e ll_lin_aa_disable(ll_sci_bus_e bus);
ll_status_e ll_lin_aa_ready_set(ll_sci_bus_e bus, bool enable);
ll_status_e ll_sci_transmit(ll_sci_bus_e bus, uint8_t *buffer, uint16_t length);
ll_status_e ll_sci_receive(ll_sci_bus_e bus, uint8_t *buffer, uint16_t length);
ll_status_e ll_lin_transmit(ll_sci_bus_e bus, uint8_t pid, uint8_t *buffer, uint16_t length);
ll_status_e ll_lin_receive(ll_sci_bus_e bus, uint8_t pid, uint8_t *buffer,  uint16_t length);
uint8_t ll_lin_checksum_calib_func(uint8_t pid, uint8_t *buffer, uint16_t length);
ll_status_e ll_lin_pid_read(ll_sci_bus_e bus, uint8_t *pid);
ll_status_e ll_lin_read_byte(ll_sci_bus_e bus, uint8_t *byte);
void SCI_IRQHandler(uint32_t isr0, uint32_t isr1);

#if defined(__cplusplus)
}
#endif
#endif /* __TCPL01X_LL_SCI_H__ */

