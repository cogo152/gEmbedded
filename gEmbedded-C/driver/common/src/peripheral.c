//
// Created by sondahi on 02.02.23.
//

#include "peripheral.h"

const uint8_t gpioPins[MAX_GPIO_PIN_SIZE] = {
        GPIO_PIN_5,
        GPIO_PIN_6,
        GPIO_PIN_16,
        GPIO_PIN_17,
        GPIO_PIN_22,
        GPIO_PIN_23,
        GPIO_PIN_24,
        GPIO_PIN_25,
        GPIO_PIN_26,
        GPIO_PIN_27,
};

const uint8_t clockPins[MAX_CLOCK_PIN_SIZE] = {
        CLOCK_PIN
};

const uint8_t pwmPins[MAX_PWM_PIN_SIZE] = {
        PWM_PIN_CHANNEL_0,
        PWM_PIN_CHANNEL_1
};

const uint8_t pcmPins[MAX_PCM_PIN_SIZE] = {
        PCM_PIN_CLK,
        PCM_PIN_FS,
        PCM_PIN_DIN,
        PCM_PIN_DOUT
};

const uint8_t i2cPins[MAX_I2C_PIN_SIZE] = {
        I2C_PIN_SDA1,
        I2C_PIN_SCL1
};

const uint8_t spiPins[MAX_SPI_PIN_SIZE] = {
        SPI_PIN_CE1_N,
        SPI_PIN_CE0_N,
        SPI_PIN_MISO,
        SPI_PIN_MOSI,
        SPI_PIN_SCLK
};

const uint8_t uartPins[MAX_UART_PIN_SIZE] = {
        UART_PIN_TXD,
        UART_PIN_RXD
};

int isElementInArray(const uint8_t *const array, const int arraySize, const uint8_t elementToValidate) {

    for (int i = 0; i < arraySize; ++i) {

        if (array[i] == elementToValidate) {
            return 0;
        }

    }

    return -1;

}