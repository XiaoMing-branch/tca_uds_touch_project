/**
 * Copyright (C) 2018 Rebo, All rights reserved.
 * @file    music_rhythm_app.c
 * @brief
 */

/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "osal.h"
#include "music_rhythm_task.h"
#include "parse_music_api.h"
#include "light_effect_api.h"
#include "parse_algo_main.h"
#include "light_effect_main.h"
#include "colormixing.h"
#include <string.h>
#include <stdint.h>
#include "lin.h"
/*******************************************************************************
 *    MACRO DEFINITIONS
 ******************************************************************************/
extern uint8_t           lin_pFrameBuf[];
/*******************************************************************************
 *    STATIC FUNCTION DECLARATIONS
 ******************************************************************************/
const static effect_attri_t k_effect_attr0_0_0 =
	{
		.effect_type = effect_breath,
		.source = &g_music_msg_output.output[0],
};

const static effect_attri_t k_effect_attr1_0_0 =
	{
		.effect_type = effect_colorful,
		.source = &g_music_msg_output.output[1],
};

const static effect_attri_t k_effect_attr2_0_0 =
	{
		.effect_type = effect_color_mix,
		.source = &g_music_msg_output.output[1],
		.attri.coolormix.lamp_loc = 0,
};

const static effect_color_rgb_t k_color_array_0_0_0[12] =
	{
		{255, 255, 255},
		{76, 151, 220},
		{76, 161, 213},
		{77, 174, 202},
		{78, 187, 190},
		{78, 198, 178},
		{79, 209, 164},
		{79, 219, 149},
		{80, 228, 131},
		{81, 237, 110},
		{115, 232, 101},
		{149, 219, 100},
};

const static brush_attri_u k_brush_0_0_0 =
	{
		.color_single.type = BRUSH_TYPE_SINGLE,
		.color_single.color_len = 12u,
		.color_single.color = k_color_array_0_0_0,
		.color_single.color_bg = {0x00, 0x00, 0x00},
		.color_single.speed = 1u};

const static effect_color_rgb_t k_color_array_1_0_0[3] =
	{
		{255, 128, 0},
		{128, 0, 255},
		{0, 255, 128},
};

const static brush_attri_u k_brush_1_0_0 =
	{
		.color_single.type = BRUSH_TYPE_SINGLE,
		.color_single.color_len = 3u,
		.color_single.color = k_color_array_1_0_0,
		.color_single.color_bg = {0x00, 0x00, 0x00},
		.color_single.speed = 1u};

static effect_design_t g_design_0_0[1] =
	{
		{.effect_attri = &k_effect_attr0_0_0, .brush_attri = &k_brush_0_0_0},
};

static effect_design_t g_design_1_0[1] =
	{
		{.effect_attri = &k_effect_attr1_0_0, .brush_attri = &k_brush_1_0_0},
};

static effect_design_t g_design_2_0[1] =
	{
		{.effect_attri = &k_effect_attr2_0_0, .brush_attri = &k_brush_0_0_0},
};

const static effect_design_hub_t g_vm_design_hub[3] =
	{
		{&g_design_0_0[0], _SIZE(g_design_0_0)},
		{&g_design_1_0[0], _SIZE(g_design_1_0)},
		{&g_design_2_0[0], _SIZE(g_design_2_0)},
};

const static effect_attri_t k_effect_attr1_1_1 =
	{
		.effect_type = effect_breath,
		.source = &g_effect_cfg.standby_cnt,
};

static effect_design_t g_design_1_1[1] =
	{
		{.effect_attri = &k_effect_attr1_1_1, .brush_attri = &k_brush_0_0_0},
};

const static effect_design_hub_t g_vm_design_standby[1] =
	{
		{&g_design_1_1[0], SIZE(g_design_1_1)},
};

/*******************************************************************************
 *    CONSTANT VARIABLES DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    STATIC VARIABLES DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    GLOBAL VARIABLES DEFINITIONS
 ******************************************************************************/

le_register_msg_t g_vm_register_msg1 =
	{
		.design_hub = &g_vm_design_hub[0],
		.design_major_max = 3u,
		.design_std_hub = g_vm_design_standby,
		.design_std_hub_max = 1u,
		.intensity_level = 20u,
		.light_output_cb = NULL,
		.mute_cb = NULL,
		//.is_active = TRUE
};

/*******************************************************************************
 *    FUNCTION DEFINITIONS
 ******************************************************************************/

static void mute_detect_cb(void *reg_dev)
{
	// uint8 idx;
	// le_register_msg_t* dev = (le_register_msg_t*)reg_dev;

	// idx = (uint8)((g_standby_cnt / STANDBY_CNT_MAX) % (uint32)dev->design_std_hub_max);

	// if (dev->design_std_hub_use != idx)
	// {
	// 	dev->design_std_hub_use = idx;
	// 	UNUSED(light_effect_calibration(dev));
	// }
}

static void light_output(effect_color_rgbi_t *color, int led_num)
{
	// to light led by using color
	cm_set_target_RGBL(color->R, color->G, color->B, (uint16_t)(color->intensity)*39, 0);
	cm_target_RGBL_lighting(1);
}

/**
 * @brief: updata frquency
 * @param[out]:
 * @retval: none
 * @author: yan.chen
 * @date: 2024/01/26
 */
static void freq_singal_update_handle(uint8 *freq, int freq_len)
{
	if (freq_len < 8u)
	{
		return;
	}

	// need to fill freq by using lin data
	memcpy((void *)freq, (const void *)&(lin_pFrameBuf[0]), 8u);
}


/**
 * @brief: app init
 * @param[in]: s_default_rgb_cali_param: default rgb calibration param
 * @retval: STD_E_OK
 * @author: yan.chen
 * @date: 2024/01/26
 */
std_rtn_type music_rhythm_app_task_init(void)
{
	parse_cfg_t parse_init = {0};
	effect_init_t effect_init;

	// 1. initialize The parsing algorithm
	parse_init.use_fre_spec = TRUE;
	parse_init.use_major_ratio = TRUE;
	parse_init.use_minor_ratio = TRUE;
	parse_init.fre_spec_len = FREQ_LEN_USE;
	if ((parse_music_init(&parse_init)) != STD_E_OK)
	{
		return STD_E_NOT_OK;
	}

	// 2. initialize the light effect algorithm
	/* @note: Due to different systems, the data sources here are not the same,
		so the registration method is used here to give the data to the lamp effect generation module */
	effect_init.max_value = FREQ_MAX_NUM;
	if ((light_effect_init(&effect_init)) != STD_E_OK)
	{
		return STD_E_NOT_OK;
	}

	UNUSED(light_effect_unregister_all());
	UNUSED(light_effect_register(&g_vm_register_msg1));
	g_vm_register_msg1.mute_cb = mute_detect_cb;
	g_vm_register_msg1.light_output_cb = light_output;

	g_vm_register_msg1.design_major_use = 2;
	light_effect_calibration_all();

	// to start a task to run function : music_rhythm_app_task!!!
	// task_register_periodic_func(TASK_PRIO_HIGH, TIME_10_MS, music_rhythm_app_task);
	OS_TASK_CREATE(music_rhythm_app_task, 10, 10, 10);
	return STD_E_OK;
}

/**
 * @brief: app task
 * @param[in]: s_led_status: the flag of led status
 * @retval: none
 * @author: yan.chen
 * @date: 2024/01/26
 */
void music_rhythm_app_task(void)
{
	uint8 freq[8u] = {0};
	static uint32 g_sys_run_cnt = 0u;
	if (l_flg_tst_LI0_ALE_MSG_flag())
	{
		l_flg_clr_LI0_ALE_MSG_flag();
		freq_singal_update_handle(freq, 8);
		set_freq_data(freq, 8u);
	}

	(void)parse_music_task();
	if (g_sys_run_cnt % 2u == 0u)
	{
		// generate light effect
		UNUSED(light_effect_task());
	}
}
