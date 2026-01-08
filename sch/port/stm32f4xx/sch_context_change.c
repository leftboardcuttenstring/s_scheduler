/**
 * @file sch_change_of_context.c
 * @author Mike Strangewood (michael.a.strangewood@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-01-07
 */

/* 
    Note:
    i'll try to correct the pathes and architecture of the project actually,
    but for now you can use the implementation of fucntions in C or in ASM,
    choosing actually the implementation in Makefile for concrete project in
    the folder 'examples/PROJECT_NAME/Makefile', and there you can even change
    the source file in there...but be careful
*/

#include "sch_change_of_context.h"

#define SCH_SCS_BASE (0xE000E000UL)
#define SCH_ICSR_OFFSET (0xD04)
#define SCH_ICSR (*(volatile uint32_t*)(SCH_SCS_BASE + SCH_ICSR_OFFSET))
#define SCH_ICSR_PENDSVET_BIT (1UL << 28)

void sch_context_change(void) {
    SCH_ICSR = SCH_ICSR_PENDSVET_BIT;
}