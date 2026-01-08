.thumb
.cpu cortex-m4

.equ __sch_scs_base, (0xE000E000UL)
.equ __sch_icsr_offset, (0xD04)
.equ __sch_icsr, (__sch_scs_base + __sch_icsr_offset)
.equ __sch_icsr_pendvset, (1 << 28)

.section .text.sch_context_change

.type sch_context_change, %function
.type sch_call_dispatch, %function


.global sch_call_dispatch
sch_call_dispatch:
    ldr r1, =sch_task_registry
    lsl r0, r0, #2
    add r0, r1, r0
    ldr r0, [r0]
    ldr r3, [r0]
    blx r3
    bx lr


.global sch_context_change
sch_context_change:
    ldr r0, =__sch_icsr
    ldr r1, =__sch_icsr_pendvset
    str r1, [r0]
    bx lr
