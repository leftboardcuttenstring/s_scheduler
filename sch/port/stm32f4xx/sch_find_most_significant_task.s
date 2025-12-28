.thumb
.cpu cortex-m4
.section .text.sch_find_most_significant_task
.global sch_find_most_significant_task
.type sch_find_most_significant_task, %function

sch_find_most_significant_task:
    cbz r0, .is_data_zero
    clz r0, r0
    rsb r0, r0, #31
    bx lr

.is_data_zero:
    mov r0, #0
    bx lr
