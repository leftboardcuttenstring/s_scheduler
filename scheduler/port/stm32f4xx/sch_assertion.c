/**
 * @file sch_assertion.c
 * @author Mike Strangewood (michael.a.strangewood@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-23
 * 
 */

#include "../inc/sch_assertion.h"

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
