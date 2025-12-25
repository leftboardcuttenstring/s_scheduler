/**
 * @file sch.h
 * @author Mike Strangewood (michael.a.strangewood@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-23
 * 
 */

#ifndef SCH_H
#define SCH_H

#include <stdio.h>
#include <stdint.h>
#include "sch_config.h"
#include "sch_assertion.h"

/*--Defining the 'alias'------------------------------------------------------*/

typedef struct sch_task_t sch_task_t;

/*--Definition of typedefs----------------------------------------------------*/

typedef uint8_t sch_task_priority;
typedef uint8_t sch_irq;

typedef void (*sch_task_dispatch_fn)(sch_task_t* task);
typedef void (*sch_task_presetting_fn)(sch_task_t* task);

struct sch_task_t {
    sch_task_dispatch_fn task_dispatch;
    sch_task_presetting_fn task_presetting;

    sch_task_priority priority;
    sch_irq irq;
};

/*--Scheduler API-------------------------------------------------------------*/

/**
 * @brief Function for creating a task
 * 
 * @param task 
 * @param priority 
 * @param irq 
 * @param dispatch 
 * @param init 
 */
void sch_task_create(sch_task_t* const task, sch_task_priority priority, sch_irq irq, sch_task_dispatch_fn dispatch, sch_task_presetting_fn init);

/**
 * @brief Function for running a task
 * 
 * @param task 
 * @param param 
 */
void sch_task_run(sch_task_t* const task, void* param);

/**
 * @brief Function for activating the task
 * 
 * @param task 
 */
void sch_task_activate(sch_task_t* const task);

/**
 * @brief A function for preparing the execution 
 * environment for task execution
 * 
 * @param task 
 * @return void
 */
__WEAK void sch_task_presetting(sch_task_t* const task);

#endif