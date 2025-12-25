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

#include <stdint.h>

/*--Defining the 'alias'------------------------------------------------------*/

typedef struct sch_task_t sch_task_t;

/*--Definition of typedefs----------------------------------------------------*/

typedef uint8_t sch_task_priority;
typedef uint8_t sch_irq;

typedef void (*sch_task_dispatch_fn)(sch_task_t* task);
typedef void (*sch_task_init_fn)(sch_task_t* task);

struct sch_task_t {
    sch_task_dispatch_fn task_dispatch;
    sch_task_init_fn task_init;

    sch_task_priority priority;
    sch_irq irq;
    //void* task_context_data;
};

/*--Scheduler API-------------------------------------------------------------*/

/**
 * @brief Function for creating a task
 * 
 * @param task 
 * @param init 
 * @param dispatch 
 */
void sch_task_create(sch_task_t* const task, sch_task_dispatch_fn dispatch, sch_task_init_fn init);

/**
 * @brief Function for running a task
 * 
 * @param task 
 * @param param 
 */
void sch_task_run(sch_task_t* const task, void* param);

void sch_task_run();
void sch_task_init();


#endif