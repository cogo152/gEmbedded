#ifndef PROCESS_H
#define PROCESS_H

    #include "common.h"
    #include "memory.h"

    #ifdef __ASSEMBLER__
        .global saveContext
        .global retrieveContext
        .global startProcessContext
    #else
        struct process_t {
            uint8_t id;
            uint8_t priority;
            struct stack_t stack;
            struct process_t *previous;
            struct process_t *next;
        };

        void configureProcessContext(void );
        void createProcess (uint32_t stackSize,
                            struct process_t *process,
                                    voidFunctionPointer handlerFunction,
                                    uint8_t handlerSize,
                                    parameterFunctionPointer function,
                                    void * functionArguments,
                                    uint8_t priority);

        void createMainProcess (uint32_t stackSize,
                    struct process_t *process,
                    voidFunctionPointer handlerFunction,
                    uint8_t handlerSize,
                    voidFunctionPointer function,
                    uint8_t priority);

        uintptr_t saveContext();
        uintptr_t retrieveContext(uintptr_t currentStack);
        void startProcessContext(void );
    #endif

#endif //PROCESS_H
