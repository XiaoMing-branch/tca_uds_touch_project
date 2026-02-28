/**
 *****************************************************************************
 * @brief   pal lin communication source file.
 *
 * @file    pal_lin_comm.c
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

#include "pal_func_def.h"
#include "pal_lin_comm.h"
#include "utilities.h"
/**
 * @brief LIN ISR FUNC FLAG
 */
#define LIN_ISR0_BASE_FLAG (SCI_INT_BRK_DET | SCI_INT_SYNC_DET | SCI_INT_SYNC_VAL_ERR |         \
                            SCI_INT_RX_PID_DONE | SCI_INT_RX_STP_ERR | SCI_INT_RX_PTY_CHK_ERR | \
                            SCI_INT_TX_RX_CONF)
#ifdef __TCPL01X__
#define LIN_ISR0_FUNC_FLAG (LIN_ISR0_BASE_FLAG | SCI_INT_TX_DONE)
#else
#define LIN_ISR0_FUNC_FLAG (LIN_ISR0_BASE_FLAG | SCI_INT_TX_DONE | SCI_INT_TX_FIFO_EMPTY)
#endif

#define BIT(A,B)            (((A)>>(B))&0x01)

/********************************************************
** \brief   pal_lin_init
**
** \param   lin_bus_e              bus
** \param   lin_mode_e             mode
** \param   uint32_t               baudrate
** \param   ISR_FUNC_CALLBACK      callback
**
** \retval  None
*********************************************************/
void pal_lin_init(lin_bus_e bus, lin_mode_e mode, uint32_t baudrate, ISR_FUNC_CALLBACK callback)
{
    sci_config_t config =
    {
        .clk_cfg = {
            .clk_source = FCLK_SRC_48M,
            .fclk_div = 0,
        },
        .isr_cfg = {
#ifdef MULTI_BYTES_MODE
            .isr = LIN_ISR0_FUNC_FLAG | SCI_INT_RX_DONE | SCI_INT_RX_FIFO_FULL,
#else
            .isr = LIN_ISR0_FUNC_FLAG | SCI_INT_RX_1BYTE_DONE,
#endif
#ifdef __TCPL01X__
            .isr1 = 0,
#endif
            .isr_enable = true,
            .priority = 3,
        },
        .mode = LIN_MODE_SLV == mode ? SCI_MODE_LIN_S : SCI_MODE_LIN_M,
        .baudrate = baudrate,
    };
    ll_sci_init((ll_sci_bus_e)bus, &config, callback);
    ll_sci_isr_enable((ll_sci_bus_e)bus, true);
}

/********************************************************
** \brief   pal_lin_deinit
**
** \param   lin_bus_e              bus
**
** \retval  None
*********************************************************/
void pal_lin_deinit(lin_bus_e bus)
{
    ll_sci_deinit((ll_sci_bus_e)bus);
}

/********************************************************
** \brief   pal_lin_parity_calib
**
** \param   lin_parity_type_e   type
** \param   uint8_t             pid
**
** \retval  None
*********************************************************/
uint8_t pal_lin_parity_calib(lin_parity_type_e type, uint8_t pid)
{
    uint8_t ret;

    uint8_t parity = (((BIT(pid, 0)^BIT(pid, 1)^BIT(pid, 2)^BIT(pid, 4)) << 6) |
                      ((~(BIT(pid, 1)^BIT(pid, 3)^BIT(pid, 4)^BIT(pid, 5))) << 7));

    if (LIN_PARITY_CHECK == type)
    {
        if ((pid & 0xC0) != parity)
        {
            ret = 0xFF;
        }
        else
        {
            ret = (uint8_t)(pid & 0x3F);
        }
    }
    else
    {
        ret = (uint8_t)(pid | parity);
    }

    return (ret);
}


/********************************************************
** \brief   pal_lin_checksum_calib
**
** \param   uint8_t             pid
** \param   uint8_t*            buffer
**
** \retval  None
*********************************************************/
uint8_t pal_lin_checksum_calib(uint8_t pid, uint8_t *buffer)
{
     uint8_t init_sum = ((0x3C != pid) && (0x7D != pid)) ? pid : 0;

     return (checksum_calculate_func(init_sum, buffer, 8));
}

#if CFG_SUPPORT_LIN_SNPD
/********************************************************
** \brief   pal_lin_aa_enter
**
** \param   uint16_t*       aa_cur_th
**
** \retval  None
*********************************************************/
void pal_lin_aa_enter(uint16_t *aa_cur_th)
{
#if CFG_SUPPROT_LINSNPD_EXT_RES
    bool use_ext_res = true;
#else
    bool use_ext_res = false;
#endif

    /* *adc ctrl config* */
    ll_adc_lin_aa_enable(LIN_AA_STYPE_STEPS_4, true);
    /* *IBIAS Control* */
    ll_bias_control_enable(true);
    /* *adc ctrl config backup* */
    ll_lin_aa_ready_set(LL_SCI_BUS_1, false);

    ll_lin_aa_enable(LL_SCI_BUS_1, LIN_AA_STYPE_STEPS_4, use_ext_res, aa_cur_th);
}

/********************************************************
** \brief   pal_lin_aa_exit
**
** \param   None
**
** \retval  None
*********************************************************/
void pal_lin_aa_exit(void)
{
    /* *disable Lin aa* */
    ll_lin_aa_disable(LL_SCI_BUS_1);
}

/********************************************************
** \brief   pal_lin_aa_ready
**
** \param   None
**
** \retval  None
*********************************************************/
void pal_lin_aa_ready(void)
{
    /* *Enable Lin aa* */
    ll_lin_aa_ready_set(LL_SCI_BUS_1, true);
}

/********************************************************
** \brief   pal_lin_aa_raw_code_get
**
** \param   uint16_t*               bufffer
** \param   uint16_t                length
**
** \retval  uint16_t                raw code length
*********************************************************/
uint16_t pal_lin_aa_raw_code_get(uint16_t *bufffer, uint16_t length)
{
    uint8_t len = ll_adc_fifo_get(bufffer, length);
    return len;
}
#endif

/********************************************************
** \brief   pal_lin_rx_response
**
** \param   lin_bus_e               bus
** \param   uint8_t                 pid
** \param   uint8_t*                buffer
** \param   uint8_t                 msg_length
**
** \retval  None
*********************************************************/
void pal_lin_rx_response(lin_bus_e bus, uint8_t pid, uint8_t *buffer, uint8_t msg_length)
{
    ll_lin_receive((ll_sci_bus_e)bus, pid, buffer, msg_length);
}

/********************************************************
** \brief   pal_lin_tx_4byte
**
** \param   lin_bus_e               bus
** \param   uint8_t*                buffer
** \param   uint8_t                 msg_length
**
** \retval  ll_status_e
*********************************************************/
void pal_lin_tx_4byte(lin_bus_e bus, uint8_t *buffer, uint8_t msg_length)
{
    ll_sci_transmit((ll_sci_bus_e)bus, buffer, msg_length);
}

/********************************************************
** \brief   pal_lin_tx_response
**
** \param   lin_bus_e               bus
** \param   uint8_t                 pid
** \param   uint8_t*                buffer
** \param   uint8_t                 msg_length
**
** \retval  bool                    true:success, false:failed
*********************************************************/
bool pal_lin_tx_response(lin_bus_e bus, uint8_t pid, uint8_t *buffer, uint8_t msg_length)
{
    if (LL_OK == ll_lin_transmit((ll_sci_bus_e)bus, pid, buffer, msg_length))
    {
        return true;
    }

    return false;
}

/********************************************************
** \brief   pal_lin_abort_handle
**
** \param   lin_bus_e               bus
** \param   lin_abort_type_e        type
**
** \retval  None
*********************************************************/
void pal_lin_abort_handle(lin_bus_e bus, lin_abort_type_e type)
{
    ll_sci_clear_type_e clear_type = SCI_CLEAR_NULL;

    if (type & LIN_ABORT_TYPE_TX)
    {
        clear_type |= (SCI_CLEAR_TX_ABORT | SCI_CLEAR_TX_FIFO);
    }

    if (type & LIN_ABORT_TYPE_RX)
    {
        clear_type |= (SCI_CLEAR_RX_ABORT | SCI_CLEAR_RX_FIFO);
    }

    ll_sci_state_clear((ll_sci_bus_e)bus, (ll_sci_clear_type_e)clear_type);
}

/********************************************************
** \brief   pal_lin_read_byte
**
** \param   lin_bus_e               bus
** \param   lin_read_type_e         type
** \param   uint8_t*                byte
**
** \retval  None
*********************************************************/
void pal_lin_read_byte(lin_bus_e bus, lin_read_type_e type, uint8_t *byte)
{
    if (LIN_READ_TYPE_PID == type)
    {
        ll_lin_pid_read((ll_sci_bus_e)bus, byte);
    }
    else
    {
        ll_lin_read_byte((ll_sci_bus_e)bus, byte);
    }
}

/********************************************************
** \brief   pal_lin_autobaudrate_check
**
** \param   lin_bus_e               bus
**
** \retval  None
*********************************************************/
void pal_lin_autobaudrate_check(lin_bus_e bus)
{
#ifdef __TCPL03X__
    uint32_t baud;
    uint32_t auto_baud;
    uint32_t diff_baud;

    ll_lin_baudrate_read(LL_SCI_BUS_1, &baud);
    ll_lin_auto_baudrate_read(LL_SCI_BUS_1, &auto_baud);

    diff_baud = (auto_baud >= baud) ? (auto_baud - baud) : (baud - auto_baud);

    if (diff_baud > (baud * 14 / 100))
    {
        ll_lin_ctrl_glben(LL_SCI_BUS_1, false);
        ll_lin_ctrl_glben(LL_SCI_BUS_1, true);
    }

#endif
}
