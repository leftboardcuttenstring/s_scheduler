#ifndef SCH_CHANGE_OF_CONTEXT_H
#define SCH_CHANGE_OF_CONTEXT_H

#ifdef __cplusplus
extern "C" {
#endif

void sch_context_switch(void);

/**
 * @brief Function for finding the most significant task flag
 * in the "registry" what'd been imaged in variable
 * 
 * @param sch_system_tasks_ready_set 
 */
uint8_t sch_find_most_significant_task(uint32_t sch_system_tasks_ready_set);

#ifdef __cplusplus
}
#endif

#endif