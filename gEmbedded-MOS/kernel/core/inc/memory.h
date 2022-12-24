#ifndef MEMORY_H
#define MEMORY_H

    #include "common.h"

    #define END_OF_MSP          (0X20020000U)
    #define LENGTH_OF_MSP       ((1U)*(1024U))
    #define BEGIN_OF_MSP        ((END_OF_MSP)-(LENGTH_OF_MSP))
    #define END_OF_PSP          ((BEGIN_OF_MSP) - (4U))
    #define LENGTH_OF_PSP       ((27U)*(1024U))
    #define BEGIN_OF_PSP        ((END_OF_PSP)-(LENGTH_OF_PSP))

    #ifdef __ASSEMBLER__
        #define BSS_DEFAULT_VALUE (0x00U)

        .global memoryCopy
        .global memoryFill
    #else
        typedef enum MEMORY_STATUS_t{
            MEMORY_SUCCESS = 0,
            STACK_UNAVAILABLE = 1,
            HEAP_UNAVAILABLE = 2,
            VALUE_NOT_MANIPULATED = 3,
        } MEMORY_STATUS;

        struct stack_t {
            uint32_t size;
            uint32_t end;
            uint32_t current;
            uint32_t begin;
            uint32_t handlerAddress;
            uint8_t handlerSize;
            uint32_t functionAddress;
        };

        void memoryCopy(uint32_t sourceAddress, uint32_t destinationAddress, uint32_t blockSize);
        void memoryFill(uint32_t destinationAddress, uint32_t blockSize, uint32_t value);
        MEMORY_STATUS stackAllocate(struct stack_t *stack, uint32_t offset);
        MEMORY_STATUS manipulateValue(uint32_t destinationAddress, uint32_t value);

        #define DUMMY_XPSR          (0x01000000U)

    #endif

#endif //MEMORY_H
