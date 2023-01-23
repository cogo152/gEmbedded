//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PERIPHERAL_BCM2711_H
#define GEMBEDDED_C_PERIPHERAL_BCM2711_H

#include "common.h"

#define CORE_CLOCK_SPEED                        (1500000000U)
#define PERIPHERAL_BASE_ADDRESS                 (0xFE000000U)
#define GPIO_BASE_ADDRESS                       (PERIPHERAL_BASE_ADDRESS+0x00200000U)

#define PIN_CONFIG_FUNCTION_OUTPUT              (0b001U)
#define PIN_CONFIG_FUNCTION_INPUT               (0b000U)
#define PIN_CONFIG_FUNCTION_ALT0                (0b100U)
#define PIN_CONFIG_FUNCTION_ALT1                (0b101U)
#define PIN_CONFIG_FUNCTION_ALT2                (0b110U)
#define PIN_CONFIG_FUNCTION_ALT3                (0b111U)
#define PIN_CONFIG_FUNCTION_ALT4                (0b011U)
#define PIN_CONFIG_FUNCTION_ALT5                (0b010U)
#define PIN_CONFIG_FUNCTION_MOD_DIV             (10U)
#define PIN_CONFIG_FUNCTION_MASK                (0b111U)
#define PIN_CONFIG_FUNCTION_MUL                 (3U)

#define PIN_CONFIG_PUD_NO_RESISTOR              (0b00U)
#define PIN_CONFIG_PUD_PULL_UP                  (0b01U)
#define PIN_CONFIG_PUD_PULL_DOWN                (0b10U)
#define PIN_CONFIG_PUD_MOD_DIV                  (16U)
#define PIN_CONFIG_PUD_MASK                     (0b11U)
#define PIN_CONFIG_PUD_MUL                      (2U)

#define PIN_CONFIG_GPIO_CHIP                    ("/dev/gpiochip0")
#define PIN_CONFIG_EVENT_RISING                 (0b00U)
#define PIN_CONFIG_EVENT_FALLING                (0b01U)
#define PIN_CONFIG_EVENT_BOTH                   (0b10U)
#define PIN_CONFIG_EVENT_MOD_DIV                (32U)
#define PIN_CONFIG_EVENT_MASK                   (0b1U)
#define PIN_CONFIG_EVENT_SET                    (0b1U)
#define PIN_CONFIG_EVENT_MUL                    (1U)

struct PinConfigRegs {
    volatile uintptr_t FSEL[6];
    uintptr_t NotUsed1[10];
    volatile uintptr_t EDS[2];
    uintptr_t NotUsed2;
    volatile uintptr_t REN[2];
    uintptr_t NotUsed3;
    volatile uintptr_t FEN[2];
    uintptr_t NotUsed4;
    volatile uintptr_t HEN[2];
    uintptr_t NotUsed5;
    volatile uintptr_t LEN[2];
    uintptr_t NotUsed6;
    volatile uintptr_t AREN[2];
    uintptr_t NotUsed7;
    volatile uintptr_t AFEN[2];
    uintptr_t NotUsed8[21];
    volatile uintptr_t PUP_PDN[4];
};

struct PinIORegs {
    uintptr_t NotUsed1[7];
    volatile uintptr_t SET[2];
    uintptr_t NotUsed2;
    volatile uintptr_t CLR[2];
    uintptr_t NotUsed3;
    volatile uintptr_t LEV[2];
    uintptr_t NotUsed4;
    volatile uintptr_t EDS[2];
};

#endif //GEMBEDDED_C_PERIPHERAL_BCM2711_H
