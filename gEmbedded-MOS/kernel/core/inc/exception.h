#ifndef EXCEPTION_H
#define EXCEPTION_H

    #include "common.h"

    #define PRIORITY_0  (0X00U)
    #define PRIORITY_1  (0X01U)
    #define PRIORITY_2  (0X02U)
    #define PRIORITY_3  (0X03U)

    #define HANDLER_NOFPU_MSP   (0xFFFFFFF1U)
    #define HANDLER_FPU_MSP     (0xFFFFFFE1U)
    #define THREAD_FPU_MSP      (0xFFFFFFE9U)
    #define THREAD_FPU_PSP      (0xFFFFFFEDU)
    #define THREAD_NOFPU_MSP    (0xFFFFFFF9U)
    #define THREAD_NOFPU_PSP    (0xFFFFFFFDU)

    void configureExceptions(void );

#endif //EXCEPTION_H
