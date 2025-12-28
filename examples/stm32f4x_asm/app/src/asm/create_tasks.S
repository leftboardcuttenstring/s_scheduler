#include "sch_asm_offsets.h"

.thumb
.cpu cortex-m4
.syntax unified

.section .bss
.align 4
.global first_task
.global second_task
.global echo_data

first_task:
    .space SCH_TASK_SIZE
second_task:
    .space SCH_TASK_SIZE
echo_data:
    .space SCH_TASK_SIZE