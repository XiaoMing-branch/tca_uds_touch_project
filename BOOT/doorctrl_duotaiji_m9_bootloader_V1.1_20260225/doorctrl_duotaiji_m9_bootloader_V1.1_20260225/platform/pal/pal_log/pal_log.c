/**
 *****************************************************************************
 * @brief   pal log source file.
 *
 * @file    pal_log.c
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

#include "pal_log.h"

/********************************************************
** \brief   pal_log_print
**
** \param   uint8_t     ch
**
** \retval  ll_status_e
*********************************************************/
void pal_log_print(uint8_t ch)
{
    ll_sci_transmit(LL_SCI_BUS_0, (uint8_t *)&ch, 1);
}

/********************************************************
** \brief   pal_log_init
**
** \param   uint32_t    baudrate
**
** \retval  ll_status_e
*********************************************************/
void pal_log_init(uint32_t baudrate)
{
    sci_config_t config =
    {
        .baudrate = baudrate,
        .mode = SCI_MODE_UART,
    };

    ll_sci_init(LL_SCI_BUS_0, &config, NULL);
}

/********************************************************
** \brief   pal_log_deinit
**
** \param   None
**
** \retval  None
*********************************************************/
void pal_log_deinit(void)
{
    ll_sci_deinit(LL_SCI_BUS_0);
}
