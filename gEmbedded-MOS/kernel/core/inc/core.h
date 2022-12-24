#ifndef CORE_H
#define CORE_H

    #include "common.h"

    #define FPU_ACTIVE          (1U<<2)
    #define FPU_NONACTIVE       (0<<2)
    #define MSP_ACTIVE          (0<<1)
    #define PSP_ACTIVE          (1U<<1)
    #define THREAD_PRIVILEGED   (0<<0)
    #define THREAD_UNPRIVILEGED (1U<<0)

    #define KERNEL_MODE         (FPU_NONACTIVE|MSP_ACTIVE|THREAD_PRIVILEGED)
    #define USER_MODE           (FPU_NONACTIVE|PSP_ACTIVE|THREAD_UNPRIVILEGED)


    #ifdef __ASSEMBLER__
        .global setMode
        .global setMSP
        .global getMSP
        .global setPSP
        .global getPSP
    #else
        void setMode(uint8_t coreMode);
        void setMSP(uint32_t mspAddress);
        uint32_t getMSP();
        void setPSP(uint32_t pspAddress);
        uint32_t getPSP();
    #endif

#endif //CORE_H
