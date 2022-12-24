#ifndef PWMMANAGERDRIVER_H
#define PWMMANAGERDRIVER_H

#include "common.h"

#define CM_PWM_CTL_OFFSET   (0xa0/4)
#define CM_PWM_DIV_OFFSET   (0xa4/4)

#define PWM_CTL_OFFSET  (0x00 / 4)
#define PWM_STA_OFFSET  (0x04 / 4)
#define PWM_DMAC_OFFSET (0X08 / 4)
#define PWM_RNG0_OFFSET (0X10 / 4)
#define PWM_DAT0_OFFSET (0X14 / 4)
#define PWM_FIF_OFFSET  (0X18 / 4)
#define PWM_RNG1_OFFSET (0X20 / 4)
#define PWM_DAT1_OFFSET (0X24 / 4)

#define PWM_MSEN_DEFAULT        (0)
#define PWM_MSEN_MS             (1)
#define PWM_USEF_DATA           (0)
#define PWM_USEF_FIFO           (1)
#define PWM_POLA_LOWHIGH        (0)
#define PWM_POLA_HIGHLOW        (1)
#define PWM_SBIT_LOW            (0)
#define PWM_SBIT_HIGH           (1)
#define PWM_RPTL                (1)
#define PWM_NO_RPTL             (0)
#define PWM_MODE_PWM            (0)
#define PWM_MODE_SERIALIZER     (1)
#define PWM_CLEAR_FIFO          (1)
#define PWM_PWEN_ENABLE         (1)
#define PWM_PWEN_DISABLE        (0)

struct PWM_CTL_t {
    uintptr_t pwen0 : 1;
    uintptr_t mode0 : 1;
    uintptr_t rptl0 : 1;
    uintptr_t sbit0 : 1;
    uintptr_t pola0 : 1;
    uintptr_t usef0 : 1;
    uintptr_t clrf  : 1;
    uintptr_t msen0 : 1;
    uintptr_t pwen1 : 1;
    uintptr_t mode1 : 1;
    uintptr_t rptl1 : 1;
    uintptr_t sbit1 : 1;
    uintptr_t pola1 : 1;
    uintptr_t usef1 : 1;
    uintptr_t       : 1;
    uintptr_t msen1 : 1;
    uintptr_t       : 16;
};

#endif //PWMMANAGERDRIVER_H
