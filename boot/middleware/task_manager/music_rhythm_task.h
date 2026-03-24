/**
 * Copyright (C) 2018 Rebo, All rights reserved.
 * @file    music_rhythm_app.h
 * @brief   
 */
#ifndef MUSIC_RHYTHM_APP_H
#define MUSIC_RHYTHM_APP_H
/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "std_types.h"


/*******************************************************************************
 *    MACRO DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    TYPEDEF TYPES
 ******************************************************************************/

/*******************************************************************************
 *    CONSTANT VARIABLES DECLARATIONS
 ******************************************************************************/

/*******************************************************************************
 *    GLOBAL VARIABLES DECLARATIONS
 ******************************************************************************/


/*******************************************************************************
 *    GLOBAL FUNCTION DECLARATIONS
 ******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief: app init
     * @param[in]: s_default_rgb_cali_param: default rgb calibration param
     * @retval: STD_E_OK
     * @author: yan.chen
     * @date: 2024/01/26
     */
    std_rtn_type music_rhythm_app_task_init(void);

    /**
     * @brief: app task
     * @param[in]: s_led_status: the flag of led status
     * @retval: none
     * @author: yan.chen
     * @date: 2024/01/26
     */
    void music_rhythm_app_task(void);    
    
#ifdef __cplusplus
}
#endif
#endif
