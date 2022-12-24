    .syntax unified
    .cpu    cortex-m4
    .fpu softvfp
    .thumb

    #include "memory.h"

    .section .text
    .type memoryCopy, %function
memoryCopy:
     cbz r2, memoryCopyExit
     sub r2, r2, #0x01
     ldrb r3, [r0,r2]
     strb r3, [r1,r2]
     b memoryCopy
     memoryCopyExit:
        bx lr
    .align FUNCTION_ALIGNMENT

    .section .text
    .type memoryFill, %function
memoryFill:
     cbz r1, memoryFillExit
     sub r1, r1, #0x01
     strb r2, [r0,r1]
     b memoryFill
     memoryFillExit:
        bx lr
    .align FUNCTION_ALIGNMENT