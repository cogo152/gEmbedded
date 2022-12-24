    .syntax unified
    .cpu    cortex-m4
    .fpu softvfp
    .thumb

    #include "systemcall.h"
    #include "system.h"

    .global SVC_Handler

    .section .text
    .type SVC_Handler, %function
SVC_Handler:
    mrs r0, psp
    ldr r1, [r0,#24]
    sub r1, r1, #2
    ldrh r2, [r1]
    bic r2, r2, #0xFF00
    cmp r2, INIT_TIMER
    beq startTimer
    .align FUNCTION_ALIGNMENT