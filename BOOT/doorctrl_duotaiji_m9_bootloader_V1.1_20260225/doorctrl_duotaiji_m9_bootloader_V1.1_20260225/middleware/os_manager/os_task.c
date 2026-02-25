/**
 *****************************************************************************
 * @brief   os task source file.
 *
 * @file    os_task.c
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

#include <stdio.h>
#include "os_task.h"
#include "logging.h"

static task_t sch_task_group[SCH_MAX_TASKS];

/********************************************************
** \brief   os_task_update
**
** \param   None
**
** \retval  None
*********************************************************/
void os_task_update(void)
{
    for (task_handle_t handle = 0; handle < SCH_MAX_TASKS; handle++)
    {
        if (sch_task_group[handle].ptask)
        {
            if (sch_task_group[handle].delay)
            {
                sch_task_group[handle].delay --;
            }

            if (sch_task_group[handle].delay == 0 || sch_task_group[handle].op == OS_TASK_MODE_LOOP)
            {
                if (sch_task_group[handle].op)
                {
                    sch_task_group[handle].runme += 1;
                }
                else
                {
                    (*sch_task_group[handle].ptask)();

                    if (sch_task_group[handle].period == 0)
                    {
                        sch_task_group[handle].ptask = 0;
                    }
                }

                if (sch_task_group[handle].period)
                {
                    sch_task_group[handle].delay = sch_task_group[handle].period;
                }
            }
        }
    }
}

/********************************************************
** \brief   os_task_create
**
** \param   pfun            ptask
** \param   uint32_t        delay
** \param   uint32_t        period
** \param   uint8_t         op
**
** \retval  uint8_t
*********************************************************/
task_handle_t os_task_create(pfun ptask, uint32_t delay, uint32_t period, uint8_t op)
{
    task_handle_t handle = 0;

    __disable_irq();

    while ((sch_task_group[handle].ptask != NULL)
           && (handle < SCH_MAX_TASKS))
    {
        handle ++;
    }

    if (handle == SCH_MAX_TASKS)
    {
        __enable_irq();
        return SCH_MAX_TASKS;
    }

    sch_task_group[handle].ptask = ptask;
    sch_task_group[handle].delay = delay;
    sch_task_group[handle].period = period;
    sch_task_group[handle].runme = 0;
    sch_task_group[handle].op = op;

    __enable_irq();

    return handle;
}

/********************************************************
** \brief   os_task_delete
**
** \param   task_handle_t   task handle
**
** \retval  None
*********************************************************/
os_status_e os_task_delete(task_handle_t handle)
{
    os_status_e status;

    __disable_irq();

    if (sch_task_group[handle].ptask == 0)
    {
        status  = OS_STATUS_DELE_ERROR;
    }
    else
    {
        status = OS_STATUS_OK;
    }

    sch_task_group[handle].ptask  = NULL;
    sch_task_group[handle].delay  = 0;
    sch_task_group[handle].period = 0;
    sch_task_group[handle].runme  = 0;

    __enable_irq();

    return status;
}

/********************************************************
** \brief   os_task_mode_set
**
** \param   task_handle_t   task handle
**
** \retval  os_status_e
*********************************************************/
os_status_e os_task_mode_set(task_handle_t handle, os_task_mode_e mode)
{
    os_status_e status;

    if (sch_task_group[handle].op != mode)
    {

        __disable_irq();

        if (sch_task_group[handle].ptask == 0)
        {
            status  = OS_STATUS_OPS_ERROR;
        }
        else
        {
            status = OS_STATUS_OK;
        }

        sch_task_group[handle].op  = mode;

        __enable_irq();
    }

    return status;
}

/********************************************************
** \brief   os_task_run
**
** \param   None
**
** \retval  None
*********************************************************/
void os_task_run(void)
{
    uint8_t handle;

    for (handle = 0; handle < SCH_MAX_TASKS; handle++)
    {
        if ((sch_task_group[handle].runme > 0)
            && (sch_task_group[handle].op))
        {
            (*sch_task_group[handle].ptask)();
            sch_task_group[handle].runme -= 1;

            if (sch_task_group[handle].period == 0)
            {
                os_task_delete(handle);
            }
        }
    }
}

/********************************************************
** \brief   os_assert
**
** \param   None
**
** \retval  None
*********************************************************/
void os_assert(uint8_t *file, uint32_t line)
{
    log_warn("[OS] assert file:%s line:%d\r\n", file, line);

    while (1);
}