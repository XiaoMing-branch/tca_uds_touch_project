/**
 *****************************************************************************
 * @brief   store manager source file.
 *
 * @file    store_manager.c
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

#include "store_manager.h"
#include "pal_store.h"
#include "colormixing.h"
#include "app.h"
#include "lin_cfg.h"
extern const cm_led_param_ref_t default_led_param_ref;
extern cm_led_param_ref_t g_led_param_ref[LED_CHANNEL_MAX];

#ifndef R_MIN_INTENSITY_FACTOR
#define  R_MIN_INTENSITY_FACTOR  0.65
#endif
#ifndef G_MIN_INTENSITY_FACTOR
#define  G_MIN_INTENSITY_FACTOR  0.95
#endif
#ifndef B_MIN_INTENSITY_FACTOR
#define  B_MIN_INTENSITY_FACTOR  0.95
#endif


sys_cfg_t g_sys_cfgs =
{
    .nad = 0x01,
#if CFG_SUPPROT_LINSNPD_EXT_RES
    .cur_th_st12 = 0x68003C00,
    .cur_th_st34 = 0x50009D00,
#else
    .cur_th_st12 = 0x70004000,
    .cur_th_st34 = 0x3000B000,
#endif
    .org_nad = 0x01,
};

const uint32_t led_param_addr_map[] =
{
    LED0_PARAM_BASE_ADDR,
    LED0_PARAM_BASE_ADDR,
};

const uint32_t led_param_offset_map[][5] =
{
    {
        LED_TEMP_PN_VOLT_OFFSET,
        LED_RGB_OFFSET,
        LED_WHITE_COLOR_OFFSET,
        LED_RELATIVE_FACTOR_OFFSET,
        LED_SERIES_NUM_OFFSET
    },
    {
        LED_TEMP_PN_VOLT_OFFSET + TOTAL_LED_PARAM_SIZE,
        LED_RGB_OFFSET + TOTAL_LED_PARAM_SIZE,
        LED_WHITE_COLOR_OFFSET + TOTAL_LED_PARAM_SIZE,
        LED_RELATIVE_FACTOR_OFFSET + TOTAL_LED_PARAM_SIZE,
        LED_SERIES_NUM_OFFSET + TOTAL_LED_PARAM_SIZE
    },
};

const uint32_t sys_param_addr_map[] =
{
    SYSTEM_CFG_OFFSET,
    SYSTEM_ID_CFG_OFFSET,
};

/********************************************************
** \brief   store_system_data_init
**
** \param   None
**
** \retval  None
*********************************************************/
static void store_system_data_init(void)
{
    uint32_t addr = 0;

    extern uint8_t lin_configuration_RAM[];
    extern uint8_t lin_configured_NAD;
    /*system cfg param init*/
    g_sys_cfgs.frame_id_cfg = lin_configuration_RAM;
    g_sys_cfgs.nad = lin_configured_NAD;

    /*nad cfg param init*/
    addr = SYSTEM_PARAM_BASE_ADDR + SYSTEM_CFG_OFFSET;

    if (true == pal_store_data_init(addr, (uint8_t *)&g_sys_cfgs, SYSTEM_CFG_SIZE))
    {
        lin_configured_NAD = (uint8_t)g_sys_cfgs.nad;
    }

    /*frame id cfg param init*/
    // addr = SYSTEM_PARAM_BASE_ADDR + SYSTEM_ID_CFG_OFFSET;
    // pal_store_data_init(addr, (uint8_t *)g_sys_cfgs.frame_id_cfg, LIN_SIZE_OF_CFG);
}

/********************************************************
** \brief   store_generic_data_init
**
** \param   None
**
** \retval  None
*********************************************************/
static void store_generic_data_init(void)
{
    uint32_t base_addr;

    for (uint8_t index = 0 ; index < LED_CHANNEL_MAX; index++)
    {
        memcpy(&g_led_param_ref[index], &default_led_param_ref, sizeof(cm_led_param_ref_t));
#if !CFG_SUPPORT_SINGAL_BIN
        /*LED pn volt typical param init*/
        base_addr = led_param_addr_map[index] + led_param_offset_map[index][LED_PN_VOLT_PARAM];
        pal_store_data_init(base_addr, (uint8_t *)&g_led_param_ref[index].pn_volt, LED_TEMP_PN_VOLT_SIZE);
#endif

        /*LED rgb param init*/
        base_addr = led_param_addr_map[index] + led_param_offset_map[index][LED_RGB_PARAM];
        pal_store_data_init(base_addr, (uint8_t *)g_led_param_ref[index].color, LED_RGB_SIZE);

        /*LED white color param init*/
        base_addr = led_param_addr_map[index] + led_param_offset_map[index][LED_WHITE_COLOR_PARAM];
        g_led_param_ref[index].white_point.intensity_limit[0] = g_led_param_ref[index].color[LED_R].intensity * R_MIN_INTENSITY_FACTOR;
        g_led_param_ref[index].white_point.intensity_limit[1] = g_led_param_ref[index].color[LED_G].intensity * G_MIN_INTENSITY_FACTOR;
        g_led_param_ref[index].white_point.intensity_limit[2] = g_led_param_ref[index].color[LED_B].intensity * B_MIN_INTENSITY_FACTOR;
        pal_store_data_init(base_addr, (uint8_t *)&g_led_param_ref[index].white_point, LED_WHITE_COLOR_SIZE);

        /*LED relative factor param init*/
        base_addr = led_param_addr_map[index] + led_param_offset_map[index][LED_RELATIVE_FACTOR_PARAM];
        pal_store_data_init(base_addr, (uint8_t *)&g_led_param_ref[index].relative_ratio.relative_factor, LED_RELATIVE_FACTOR_SIZE);
    }
}

/********************************************************
** \brief   store_manager_init
**
** \param   None
**
** \retval  None
*********************************************************/
void store_manager_init(void)
{
    store_system_data_init();
    store_generic_data_init();
}

/********************************************************
** \brief   store_manager_clear
**
** \param   None
**
** \retval  None
*********************************************************/
void store_manager_clear(void)
{
    for (uint8_t index = 0 ; index < LED_CHANNEL_MAX; index++)
    {
        pal_store_data_clear(led_param_addr_map[index], STORE_SECTOR_SIZE);
    }

    pal_store_data_clear(SYSTEM_PARAM_BASE_ADDR, STORE_SECTOR_SIZE);
}

/********************************************************
** \brief   store_generic_data_set
**
** \param   led_channel_e       channel
** \param   led_param_type_e    type
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  None
*********************************************************/
void store_generic_data_set(led_channel_e channel, led_param_type_e type, uint8_t *param, uint16_t len)
{
    uint32_t addr = led_param_addr_map[channel] + led_param_offset_map[channel][type];

    pal_store_data_set(addr, param, len);
}

/********************************************************
** \brief   store_generic_data_get
**
** \param   led_channel_e       channel
** \param   led_param_type_e    type
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  None
*********************************************************/
bool store_generic_data_get(led_channel_e channel, led_param_type_e type, uint8_t *param, uint16_t len)
{
    uint32_t addr = led_param_addr_map[channel] + led_param_offset_map[channel][type];

    return (pal_store_data_get(addr, param, len));
}

/********************************************************
** \brief   store_system_data_set
**
** \param   system_param_type_e type
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  bool
*********************************************************/
void store_system_data_set(system_param_type_e type, uint8_t *param, uint16_t len)
{
    uint32_t addr = SYSTEM_PARAM_BASE_ADDR + sys_param_addr_map[type];

    pal_store_data_set(addr, param, len);
}

/********************************************************
** \brief   store_system_data_get
**
** \param   system_param_type_e type
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  None
*********************************************************/
bool store_system_data_get(system_param_type_e type, uint8_t *param, uint16_t len)
{
    uint32_t addr = SYSTEM_PARAM_BASE_ADDR + sys_param_addr_map[type];

    return (pal_store_data_get(addr, param, len));
}

/********************************************************
** \brief   store_chip_info_get
**
** \param   chip_info_type_e    type
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  bool
*********************************************************/
bool store_chip_info_get(chip_info_type_e type, uint8_t *param, uint16_t len)
{
    chip_ver_id_t *chip_ver_id = (chip_ver_id_t *)param;

    switch (type)
    {
        case CHIP_INFO_VER_ID:
            pal_store_chip_ver_id_get(&chip_ver_id->ver, &chip_ver_id->id);
            break;

        case CHIP_INFO_UUID:
            pal_store_uid_get((uint32_t *)param);
            break;

        case CHIP_INFO_BOOT_VER:
            pal_store_boot_ver_get((uint32_t *)param);
            break;
    }

    return true;
}

/********************************************************
** \brief   store_customer_data_set
**
** \param   uint32_t            addr_offset
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  bool
*********************************************************/
bool store_customer_data_set(uint32_t addr_offset, uint8_t *param, uint16_t len)
{
    if (addr_offset >= FLASH_SECTOR_SIZE || (addr_offset + len) > FLASH_SECTOR_SIZE)
    {
        return false;
    }

    uint32_t addr = CUSTOMER_PARAM_BASE_ADDR + addr_offset;

    pal_store_data_set(addr, param, len);
    return true;
}

/********************************************************
** \brief   store_customer_data_get
**
** \param   uint32_t            addr_offset
** \param   uint8_t*            param
** \param   uint16_t            len
**
** \retval  bool
*********************************************************/
bool store_customer_data_get(uint32_t addr_offset, uint8_t *param, uint16_t len)
{
    if (addr_offset >= FLASH_SECTOR_SIZE || (addr_offset + len) > FLASH_SECTOR_SIZE)
    {
        return false;
    }

    uint32_t addr = CUSTOMER_PARAM_BASE_ADDR + addr_offset;

    return (pal_store_data_get(addr, param, len));
}

/********************************************************
** \brief   store_reg_param_set
**
** \param   uint8_t  address
**
** \retval  void
*********************************************************/
void store_reg_param_set(uint8_t *addr, uint8_t *value)
{
    uint32_t address = addr[3] << 24 | addr[2] << 16 | addr[1] << 8 | addr[0];
    uint32_t reg_val = value[3] << 24 | value[2] << 16 | value[1] << 8 | value[0];;

    pal_store_reg_rw(true, address, &reg_val);
}

/********************************************************
** \brief   store_reg_param_get
**
** \param   uint8_t   address
** \param   uint8_t   value
**
** \retval  bool
*********************************************************/
void store_reg_param_get(uint8_t *addr, uint8_t *value)
{
    uint32_t address = addr[3] << 24 | addr[2] << 16 | addr[1] << 8 | addr[0];
    uint32_t reg_val;

    pal_store_reg_rw(false, address, &reg_val);
    memcpy(value, (uint8_t *)&reg_val, sizeof(uint32_t));
}

/********************************************************
** \brief   store_led_param_load
**
** \param   led_channel_e   channel
**
** \retval  None
*********************************************************/
void store_led_param_load(led_channel_e channel)
{
    uint8_t *ptr = NULL;
    uint16_t length;

    for (uint8_t param_type = 0; param_type <= LED_RELATIVE_FACTOR_PARAM ; param_type++)
    {
        switch (param_type)
        {
            case LED_PN_VOLT_PARAM:
                ptr = (uint8_t *)&g_led_param_ref[channel].pn_volt;
                length = LED_TEMP_PN_VOLT_SIZE;
                break;

            case LED_RGB_PARAM:
                ptr = (uint8_t *)g_led_param_ref[channel].color;
                length = LED_RGB_SIZE;
                break;

            case LED_WHITE_COLOR_PARAM:
                ptr = (uint8_t *)&g_led_param_ref[channel].white_point;
                length = LED_WHITE_COLOR_SIZE;
                break;

            case LED_RELATIVE_FACTOR_PARAM:
                ptr = (uint8_t *)&g_led_param_ref[channel].relative_ratio.relative_factor;
                length = LED_RELATIVE_FACTOR_SIZE;
                break;

            default:
                break;
        }

        if (true == store_generic_data_get((led_channel_e)channel, (led_param_type_e)param_type, ptr, length))
        {
        }
    }
}
