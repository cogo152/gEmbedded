#include "memory.h"
#include "exception.h"

MEMORY_STATUS stackAllocate(struct stack_t * stack, uint32_t offset){

    uint32_t static currentFrame = END_OF_PSP;

    if((currentFrame - stack->size) < BEGIN_OF_PSP){
        return STACK_UNAVAILABLE;
    } else {
        //create stack
        stack->end = currentFrame;
        uintptr_t * stackPtr = ((uintptr_t *) currentFrame)-offset;
        currentFrame -= stack->size;
        stack->begin = currentFrame;
        currentFrame-=4; // dont touch

        // fill stack entry
        *(--stackPtr) = DUMMY_XPSR;
        *(--stackPtr) = ((uintptr_t) stackPtr)+5;
        *(--stackPtr) = THREAD_NOFPU_PSP;
        *(--stackPtr) = 12;
        *(--stackPtr) = 3;
        *(--stackPtr) = 2;
        *(--stackPtr) = 1;
        *(--stackPtr) = 0;
        *(--stackPtr) = 11;
        *(--stackPtr) = 10;
        *(--stackPtr) = 9;
        *(--stackPtr) = 8;
        *(--stackPtr) = 7;
        *(--stackPtr) = 6;
        *(--stackPtr) = 5;
        *(--stackPtr) = 4;
        stack->current = (uint32_t) stackPtr;

        return MEMORY_SUCCESS;
    }

}

MEMORY_STATUS manipulateValue(uint32_t destinationAddress, uint32_t value){

    uintptr_t *ptr = (uintptr_t *) destinationAddress;
    *ptr = value;

    if(value != *ptr){
        return VALUE_NOT_MANIPULATED;
    } else {
        return MEMORY_SUCCESS;
    }

}
