/**
  ******************************************************************************
  * @brief  application main file.
  *
  * @file   custom_diagnosticlll.h
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
#ifndef __CUSTOM_DIAGNOSTICLLL_H__
#define __CUSTOM_DIAGNOSTICLLL_H__

typedef enum
{
    LEFT_FRONT_DOOR = 0,
    LEFT_REAR_DOOR,
    RIGHT_FRONT_DOOR,
    RIGHT_REAR_DOOR,
} T_Door;

/**
 * @brief app sys info
 */
typedef struct
{
    uint8_t config_word; /* user's config word */
    uint8_t nad_info;
} user_cfg_t __attribute__((aligned(1)));

void uds_diagnostic_configword_remap_nad(void);

#endif
