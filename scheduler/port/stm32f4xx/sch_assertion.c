/**
 * @file sch_assertion.c
 * @author Mike Strangewood (michael.a.strangewood@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-23
 * 
 */

#include "sch.h"
#include "sch_assertion.h"

/**
 * @brief Handler for an error related to the 
 * scheduler's handling of process metadata
 * 
 * @return void
 */
__WEAK SCH_NORETURN_FUNC_ATTRIBUTE void sch_fault_handler(void) {
    __disable_irq();
    while (1) { }
}

/**
 * @brief A function for preparing the execution 
 * environment for task execution
 * 
 * @param task 
 * @return void
 */
__WEAK void sch_task_presetting(sch_task_t* const task) {
    
}
