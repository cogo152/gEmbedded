    .syntax unified
    .cpu    cortex-m4
    .fpu softvfp
    .thumb

    #include "core.h"

    .section .text
    .type setMode, %function
setMode:
    msr control, r0
    bx lr
    .align FUNCTION_ALIGNMENT

    .section .text
    .type setMSP, %function
setMSP:
    msr msp, r0
    bx lr
    .align FUNCTION_ALIGNMENT

    .section .text
    .type getMSP, %function
getMSP:
    mrs r0, msp
    bx lr
    .align FUNCTION_ALIGNMENT

    .section .text
    .type setPSP, %function
setPSP:
    msr psp, r0
    bx lr
    .align FUNCTION_ALIGNMENT

    .section .text
    .type getPSP, %function
getPSP:
    mrs r0, psp
    bx lr
    .align FUNCTION_ALIGNMENT

