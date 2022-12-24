#ifndef COMMON_H
#define COMMON_H

    #define HIGH    (0X01U)
    #define LOW     (0x00U)

    #ifdef __ASSEMBLER__

        .equ FUNCTION_ALIGNMENT, 2
        .equ DATA_WORD_ALIGNMENT, 4

    #else

        #include <stdint.h>
        typedef void (* voidFunctionPointer)(void );
        typedef void (* parameterFunctionPointer)(void *);

    #endif

#endif //COMMON_H
