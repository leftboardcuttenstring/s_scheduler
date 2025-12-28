#ifndef SCH_TASK_MANAGEMENT_H
#define SCH_TASK_MANAGEMENT_H

#include "sch_common.h"

/*--Defining the 'alias'------------------------------------------------------*/

typedef struct sch_task_t sch_task_t;

extern int32_t sch_system_tasks_ready_set;
extern int32_t sch_preempt_tasks_ready_set;

/*--Definition of typedefs----------------------------------------------------*/

typedef int8_t sch_task_priority;
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