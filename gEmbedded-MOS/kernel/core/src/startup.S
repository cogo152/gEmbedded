    .syntax unified
    .cpu    cortex-m4
    .fpu softvfp
    .thumb

    #include "common.h"
    #include "core.h"
    #include "memory.h"
    #include "process.h"

    .global Reset_Handler

    .section .text
    .type Reset_Handler, %function
Reset_Handler:
    ldr r0, = END_OF_MSP
    bl setMSP

    mov r0, #KERNEL_MODE
    bl setMode

    ldr r0, =_eROM
    ldr r1, =_bROMtoSRAM
    ldr r2, =_eROMtoSRAM
    sub r2, r2, r1
    bl memoryCopy

    ldr r0, =_bSRAM
    ldr r1, =_eSRAM
    sub r1, r1, r0
    mov r2, #BSS_DEFAULT_VALUE
    bl memoryFill

    bl configureSystem

    mov r0, #USER_MODE
    bl setMode

    bl startProcessContext
    .align FUNCTION_ALIGNMENT