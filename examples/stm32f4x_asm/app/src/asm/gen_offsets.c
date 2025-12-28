// gen_offsets.c
#include <stddef.h>
#include "sch.h"

#define EMIT(sym, val) \
    __asm__ volatile("\n-> " #sym " %0 " #val : : "i" (val))

__attribute__((used))
void get_offsets(void) {
    EMIT(SCH_TASK_SIZE, sizeof(sch_task_t));
    EMIT(SCH_PRIORITY_OFFSET, offsetof(sch_task_t, priority));
}