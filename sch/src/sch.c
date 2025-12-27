/**
 * @file sch.c
 * @author Mike Strangewood (michael.a.strangewood@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sch.h"

int32_t sch_system_tasks_ready_set = 0;
int32_t sch_preempt_tasks_ready_set = 0;

sch_task_t queue[SCH_MAX_QUANTITY_OF_TASKS] = {0};

/**
 * @brief Function for creating a task
 * 
 * @param task 
 * @param priority 
 * @param irq 
 * @param dispatch 
 * @param init 
 */
void sch_task_create(sch_task_t* const task, sch_task_priority priority, sch_irq irq, sch_task_dispatch_fn dispatch, sch_task_presetting_fn presetting) {
    if (task != (sch_task_t* const)NULL) {
        task->irq = irq;
        task->priority = priority;
        task->task_dispatch = dispatch;
        task->task_presetting = presetting;

        task->task_presetting(task);
    }
}

/**
 * @brief Function for running a task
 * 
 * @param task 
 * @param param 
 */
void sch_task_run(sch_task_t* const task, void* param) {
    SCH_ASSERT((task->priority > 0) && (task->priority < SCH_MAX_QUANTITY_OF_TASKS));
    (*task->task_dispatch)(task);
}

/**
 * @brief Function for activating the task
 * 
 * @param task 
 */
void sch_task_activate(sch_task_t* const task) {
    if (task->priority < 0) {
        sch_system_tasks_ready_set |= (1U << (uint8_t)(-task->priority - 1));
    } else {
        sch_preempt_tasks_ready_set |= (1U << (uint8_t)(task->priority - 1));
    }
}