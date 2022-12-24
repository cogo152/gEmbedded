#ifndef SYSTEM_H
#define SYSTEM_H

    #include "common.h"

    #ifdef __ASSEMBLER__
        .global configureSystem
    #else
        struct CPUID_t {
            uintptr_t revision_r        : 4;
            uintptr_t partNo_r          : 12;
            uintptr_t constant_r        : 4;
            uintptr_t variant_r         : 4;
            uintptr_t implementer_r     : 8;
        };

        struct ICSR_t {
            uintptr_t vectorActivate_rw : 9;
            uintptr_t                   : 2;
            uintptr_t returnToBase_r    : 1;
            uintptr_t vectorPending_r   : 7;
            uintptr_t                   : 3;
            uintptr_t isrPending_r      : 1;
            uintptr_t                   : 2;
            uintptr_t pendingSTClear_w  : 1;
            uintptr_t pendingSTSet_rw   : 1;
            uintptr_t pendingSVClear_w  : 1;
            uintptr_t pendingSVSet_rw   : 1;
            uintptr_t                   : 2;
            uintptr_t nmiPendingSet_rw  : 1;
        };

        struct SHPR1_t{
            uintptr_t memManFault_r     : 4;
            uintptr_t memManFault_rw    : 4;
            uintptr_t busFault_r        : 4;
            uintptr_t busFault_rw       : 4;
            uintptr_t usageFault_r      : 4;
            uintptr_t usageFault_rw     : 4;
            uintptr_t                   : 8;
        };

        struct SHPR2_t{
            uintptr_t                   : 24;
            uintptr_t svcCall_r         : 4;
            uintptr_t svcCall_rw        : 4;
        };

        struct SHPR3_t{
            uintptr_t                           : 16;
            uintptr_t pendSV_r                  : 4;
            uintptr_t pendSV_rw                 : 4;
            uintptr_t sysTick_r                 : 4;
            uintptr_t sysTick_rw                : 4;
        };

        struct SHCSR_t{
            uintptr_t memFaultAct_rw    : 1;
            uintptr_t busFaultAct_rw    : 1;
            uintptr_t                   : 1;
            uintptr_t usgFaultAct_rw    : 1;
            uintptr_t                   : 3;
            uintptr_t svCallAct_rw      : 1;
            uintptr_t monitorAct_rw     : 1;
            uintptr_t                   : 1;
            uintptr_t pendSvAct_rw      : 1;
            uintptr_t sysTickAct_rw     : 1;
            uintptr_t usgFaultPended_rw : 1;
            uintptr_t memFaultPended_rw : 1;
            uintptr_t busFaultPended_rw : 1;
            uintptr_t svCallPended_rw   : 1;
            uintptr_t memFaultEna_rw    : 1;
            uintptr_t busFaultEna_rw    : 1;
            uintptr_t usgFaultEna_rw    : 1;
            uintptr_t                   : 13;
        };

        struct SCB_t{
            struct CPUID_t CPUID;
            struct ICSR_t ICSR;
            uintptr_t VTOR;
            uintptr_t AIRCR;
            uintptr_t SCR;
            uintptr_t CCR;
            struct SHPR1_t SHPR1;
            struct SHPR2_t SHPR2;
            struct SHPR3_t SHPR3;
            struct SHCSR_t SHCSR;
            uintptr_t CFSR;
            uintptr_t MMSR;
            uintptr_t BFSR;
            uintptr_t UFSR;
            uintptr_t HFSR;
            uintptr_t MMAR;
            uintptr_t BFAR;
            uintptr_t AFSR;
        };

        /*
        * The processor has a 24-bit system timer, SysTick, that counts down from the reload value to zero reloads (wraps to)
        * the value in the STK_LOAD register on the next clock edge, then counts down on subsequent clocks.
        * When the processor is halted for debugging the counter does not decrement.
        * The SysTick counter runs on the processor clock. If this clock signal is stopped for low power mode, the SysTick
        * counter stops.
        */

        struct STK_CTRL_t{
            uintptr_t enable_rw         : 1;
            uintptr_t tickInt_rw        : 1;
            uintptr_t clockSource_rw    : 1;
            uintptr_t                   : 13;
            uintptr_t countFlag_rw      : 1;
            uintptr_t                   : 15;
        };

        struct STK_LOAD_t{
            uintptr_t reloadValue_rw    : 24;
            uintptr_t                   : 8;
        };

        struct STK_VAL_t{
            uintptr_t currentValue_rw   : 24;
            uintptr_t                   : 8;
        };

        struct STK_CALIB_t{
            uintptr_t tenMS_r           : 24;
            uintptr_t                   : 6;
            uintptr_t skew_r            : 1;
            uintptr_t noReference_r     : 1;
        };

        struct ST_t{
            struct STK_CTRL_t STK_CTRL;     // Privileged
            struct STK_LOAD_t STK_LOAD;     // Privileged
            struct STK_VAL_t STK_VAL;       // Privileged
            struct STK_CALIB_t STK_CALIB;   // Privileged
        };

        #define AHB_CLOCK_SPEED                 (16000000U)
        #define SEC                             (AHB_CLOCK_SPEED)
        #define MIL_SEC                         (SEC / 1000U)
        #define MIC_SEC                         (MIL_SEC / 1000U)
        #define DEFAULT_PROCESS_SWITCH          ((MIL_SEC) - (1U))

        #define CLOCK_SOURCE_AHB                (0X1U)
        #define CLOCK_SOURCE_AHB8               (0X0)

        #define SCB ((volatile struct SCB_t *)  (0xE000ED00))
        #define ST ((volatile struct ST_t *)    (0xE000E010))

    void configureSystem(void );

    #endif

#endif //SYSTEM_H
