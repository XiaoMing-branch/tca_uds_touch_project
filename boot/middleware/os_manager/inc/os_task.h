/**
 *****************************************************************************
 * @brief   os task header file.
 *
 * @file    os_task.h
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

#ifndef __OS_TASK_H__
#define __OS_TASK_H__

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define SCH_MAX_TASKS       10

typedef void (*pfun)(void);

typedef uint8_t task_handle_t;
typedef enum
{
    OS_STATUS_OPS_ERROR,
    OS_STATUS_OK,
    OS_STATUS_DELE_ERROR,
    OS_STATUS_TASK_OVERFLOW,
} os_status_e;

typedef enum
{
    OS_TASK_MODE_PRE_EMPTIVE,
    OS_TASK_MODE_TIME_SLICE,
    OS_TASK_MODE_LOOP,
} os_task_mode_e;

typedef struct task_t
{
    void (*ptask)();
    uint32_t delay;         /* 延迟 unit 1ms*/
    uint32_t period;        /* 运行的时间间隔 0表示只执行一次 */
    uint8_t  runme;         /* 当前任务需要运行，+1  */
    uint8_t  op;            /* 0-抢占式 1-合作式 2-后台运行模式*/
    struct task_t *next;
} task_t;

void os_task_update(void);
task_handle_t os_task_create(pfun ptask, uint32_t delay, uint32_t period, uint8_t op);
os_status_e os_task_delete(task_handle_t handle);
os_status_e os_task_mode_set(task_handle_t handle, os_task_mode_e mode);
void os_task_run(void);
void os_assert(uint8_t *file, uint32_t line);

#ifdef __cplusplus
}
#endif
#endif /* __OS_TASK_H__ */
