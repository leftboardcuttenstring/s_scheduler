#ifndef SCH_CHANGE_OF_CONTEXT_H
#define SCH_CHANGE_OF_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sch_common.h"

/**
 * @brief Function for finding the most significant task flag
 * in the "registry" what'd been imaged in variable
 * 
 * @param sch_system_tasks_ready_set 
 */
uint8_t sch_find_most_significant_task(uint32_t sch_system_tasks_ready_set);

/**
 * @brief Function for changing the context
 * 
 */
void sch_context_change(void);

/**
 * @brief Function for planning goddammit
 * 
 */
void sch_call_dispatch(uint8_t sch_most_significant_task);

/**
 * @brief Function an optional function that is executed as 
 * a postcondition after calling the context change function
 * 
 * @return void 
 */
__WEAK void sch_context_change_postfunc(void);

#ifdef __cplusplus
}
#endif

#endif