/**
 *****************************************************************************
 * @brief   crc Source file.
 *
 * @file    tcpl01x_ll_crc.c
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

#include "tcpl01x_ll_crc.h"

/********************************************************
** \brief   ll_crc_calculate8
**
** \param   uint8_t*    in_data
** \param   uint8_t     init_value
** \param   uint8_t     poly
** \param   uint32_t    data_length
**
** \retval  uint8_t
*********************************************************/
uint8_t ll_crc_calculate8(uint8_t *in_data, uint8_t init_value, uint8_t poly, uint32_t data_length)
{
    uint32_t last_word_length = data_length % 4;
    uint32_t temp_word = 0;
    uint32_t valid = 0;

    CRC->CRC_POLY_F.CRC_POLY = poly;
    CRC->CRC_INIT_VALUE_F.CRC_INIT_VALUE = init_value;
    CRC->CTRL_F.INIT = 0x01;

    CRC->CTRL_F.CRC_MODE = 0x02;   //0:32 , 1:16, 2:8
    CRC->CTRL_F.REV_IN   = 0;
    CRC->CTRL_F.REV_OUT  = 0;

    CRC->CTRL_F.EN = 1;

    //group bytes by words
    for (uint32_t i = 0 ; i < data_length; i = i + 4)
    {
        if ((i + 4) > data_length)
        {
            break;
        }

        temp_word = 0x00000000;
        temp_word = (in_data[i + 3] << 24) | (in_data[i + 2] << 16) | (in_data[i + 1] << 8) | (in_data[i]);
        CRC->CRC_VLDBIT_F.CRC_VLDBIT = 0xFFFFFFFF;
        CRC->CRC_DIN_F.CRC_DIN = temp_word;
    }

    if (last_word_length > 0)
    {
        temp_word = 0;

        //group the tail of data array by last word
        for (int32_t i = (data_length - 1) ; i >= (data_length - last_word_length) ; --i)
        {
            temp_word <<= 8;
            temp_word |= in_data[i];
            valid <<= 8;
            valid |= 0xFF ;
        }

        CRC->CRC_VLDBIT_F.CRC_VLDBIT = valid;
        CRC->CRC_DIN_F.CRC_DIN = temp_word;
    }

    while (CRC->STATUS_F.CRC_BUSY);

    return (CRC->CRC_RESULT_F.CRC_RESULT);
}

/********************************************************
** \brief   ll_crc_calculate16
**
** \param   uint8_t*    in_data
** \param   uint16_t    init_value
** \param   uint16_t    poly
** \param   uint32_t    data_length
**
** \retval  uint16_t
*********************************************************/
uint16_t ll_crc_calculate16(uint8_t *in_data, uint16_t init_value, uint16_t poly, uint32_t data_length)
{
    uint32_t last_word_length = data_length % 4;
    uint32_t temp_word = 0;
    uint32_t valid = 0;
    uint16_t result = 0;

    CRC->CRC_POLY_F.CRC_POLY = poly;
    CRC->CRC_INIT_VALUE_F.CRC_INIT_VALUE = init_value;
    CRC->CTRL_F.INIT = 0x01;

    CRC->CTRL_F.CRC_MODE = 1;   //0:32 , 1:16, 2:8
    CRC->CTRL_F.REV_IN = 1;
    CRC->CTRL_F.REV_OUT = 0;

    CRC->CTRL_F.EN = 1;

    //group bytes by words
    for (uint32_t i = 0 ; i < data_length; i = i + 4)
    {
        if ((i + 4) > data_length)
        {
            break;
        }

        temp_word = 0x00000000;
        temp_word = (in_data[i + 3] << 24) | (in_data[i + 2] << 16) | (in_data[i + 1] << 8) | (in_data[i]);
        CRC->CRC_VLDBIT_F.CRC_VLDBIT = 0xFFFFFFFF;
        CRC->CRC_DIN_F.CRC_DIN = temp_word;
    }

    if (last_word_length > 0)
    {
        temp_word = 0;

        //group the tail of data array by last word
        for (int32_t i = (data_length - 1) ; i >= (data_length - last_word_length) ; --i)
        {
            temp_word <<= 8;
            temp_word |= in_data[i];
            valid <<= 8;
            valid |= 0xFF ;
        }

        CRC->CRC_VLDBIT_F.CRC_VLDBIT = valid;
        CRC->CRC_DIN_F.CRC_DIN = temp_word;
    }

    while (CRC->STATUS_F.CRC_BUSY);

    result = CRC->CRC_RESULT_F.CRC_RESULT ^ 0xFFFF;

    result = ((result >> 1u) & 0x5555u) | ((result & 0x5555) << 1u) ;
    result = ((result >> 2u) & 0x3333u) | ((result & 0x3333) << 2u) ;
    result = ((result >> 4u) & 0x0f0fu) | ((result & 0x0f0f) << 4u) ;
    return ((result >> 8u) | (result << 8u));
}

/********************************************************
** \brief   ll_crc_calculate32
**
** \param   uint8_t*    in_data
** \param   uint32_t    init_value
** \param   uint32_t    poly
** \param   uint32_t    data_length
**
** \retval  uint32_t
*********************************************************/
uint32_t ll_crc_calculate32(uint8_t *in_data, uint32_t init_value, uint32_t poly, uint32_t data_length)
{
    uint32_t last_word_length = data_length % 4;
    uint32_t temp_word = 0;
    uint32_t valid = 0;

    if (init_value != 0xFFFFFFFF && init_value != 0)
    {
        init_value = ((init_value >> 1u) & 0x55555555u) | ((init_value & 0x55555555u) << 1u);
        init_value = ((init_value >> 2u) & 0x33333333u) | ((init_value & 0x33333333u) << 2u);
        init_value = ((init_value >> 4u) & 0x0F0F0F0Fu) | ((init_value & 0x0F0F0F0Fu) << 4u);
        init_value = ((init_value >> 8u) & 0x00FF00FFu) | ((init_value & 0x00FF00FFu) << 8u);
        init_value = ((init_value >> 16u) | (init_value << 16u));
    }

    CRC->CRC_POLY_F.CRC_POLY = poly;
    CRC->CRC_INIT_VALUE_F.CRC_INIT_VALUE = init_value;
    CRC->CTRL_F.INIT = 0x01;

    CRC->CTRL_F.CRC_MODE = 0;   //0:32 , 1:16, 2:8
    CRC->CTRL_F.REV_IN = 1;
    CRC->CTRL_F.REV_OUT = 1;

    CRC->CTRL_F.EN = 1;

    //group bytes by words
    for (uint32_t i = 0 ; i < data_length; i = i + 4)
    {
        if ((i + 4) > data_length)
        {
            break;
        }

        temp_word = 0x00000000;
        temp_word = (in_data[i + 3] << 24) | (in_data[i + 2] << 16) | (in_data[i + 1] << 8) | (in_data[i]);
        CRC->CRC_VLDBIT_F.CRC_VLDBIT = 0xFFFFFFFF;
        CRC->CRC_DIN_F.CRC_DIN = temp_word;
    }

    if (last_word_length > 0)
    {
        temp_word = 0;

        //group the tail of data array by last word
        for (int32_t i = (data_length - 1) ; i >= (data_length - last_word_length) ; --i)
        {
            temp_word <<= 8;
            temp_word |= in_data[i];
            valid <<= 8;
            valid |= 0xFF ;
        }

        CRC->CRC_VLDBIT_F.CRC_VLDBIT = valid;
        CRC->CRC_DIN_F.CRC_DIN = temp_word;
    }

    while (CRC->STATUS_F.CRC_BUSY);

    return (CRC->CRC_RESULT_F.CRC_RESULT);
}
