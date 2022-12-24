#include "process.h"
#include "system.h"
#include "core.h"
#include "exception.h"

extern void main(void );

extern void mainHandler(void );
extern void processHandler(void );

static struct process_t processMain;
static struct process_t * currentProcess = 0;

void createMainProcess(uint32_t stackSize,
                       struct process_t *volatile process,
                               voidFunctionPointer handlerFunction,
                               uint8_t handlerSize,
                               voidFunctionPointer function,
                               uint8_t priority){
    static uint8_t currentId = 0;

    process->priority = priority;
    process->stack.size = stackSize;
    process->stack.handlerAddress = (uint32_t) handlerFunction;
    process->stack.handlerSize = handlerSize;
    process->stack.functionAddress = (uint32_t) function;

    MEMORY_STATUS status = stackAllocate(&process->stack,2); // size must be dynamic
    if(status != MEMORY_SUCCESS){
        //return status;
        return;
    } else{
        process->id = currentId++;
    }

    memoryCopy (process->stack.handlerAddress-1, process->stack.end-handlerSize+4, handlerSize);

    manipulateValue (process->stack.end, (uint32_t) function);

    process->next = currentProcess->next;
    currentProcess->next = process;

}

void createProcess(uint32_t stackSize,
                   struct process_t *process,
                   voidFunctionPointer handlerFunction,
                   uint8_t handlerSize,
                   parameterFunctionPointer function,
                   void * functionArguments,
                   uint8_t priority){

    static uint8_t currentId = 0;

    process->priority = priority;
    process->stack.size = stackSize;
    process->stack.handlerAddress = (uint32_t) handlerFunction;
    process->stack.handlerSize = handlerSize;
    process->stack.functionAddress = (uint32_t) function;

    MEMORY_STATUS status = stackAllocate(&process->stack,4); // size must be dynamic
    if(status != MEMORY_SUCCESS){
        //return status;
        return;
    } else{
        process->id = currentId++;
    }

    memoryCopy (process->stack.handlerAddress-1, process->stack.end-handlerSize+4, handlerSize);

    manipulateValue (process->stack.end-4, (uint32_t) functionArguments);
    manipulateValue (process->stack.end, (uint32_t) function);


    process->next = currentProcess->next;
    currentProcess->next = process;

}

void configureProcessContext(void ){

    createMainProcess (1024,&processMain,&mainHandler,12,&main,0);

    processMain.next = &processMain;
    processMain.previous = &processMain;
    currentProcess = &processMain;

    setPSP ((uint32_t) currentProcess->stack.current);

}

void SysTick_Handler(void ){
    SCB->ICSR.pendingSVSet_rw = HIGH;
}



void __attribute__((naked)) PendSV_Handler(void ){
    __asm__ volatile ("push {lr}");

    __asm__ volatile ("mov r0,%0"::"r"(&currentProcess->stack.current):);
    __asm__ volatile ("bl saveContext");

    __asm__ volatile ("mov %0,%1":"=r"(currentProcess):"r"(currentProcess->next):);

    __asm__ volatile ("mov r0,%0"::"r"(&currentProcess->stack.current):);
    __asm__ volatile ("bl retrieveContext");

    __asm__ volatile ("pop {pc}");

}
