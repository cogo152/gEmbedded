//
// Created by sondahi on 23.01.23.
//

#ifndef GEMBEDDED_C_PERIPHERAL_H
#define GEMBEDDED_C_PERIPHERAL_H

#include "common.h"

#define CORE_CLOCK_SPEED                        (1500000000U)
#define PERIPHERAL_BASE_ADDRESS                 (0xFE000000U)

/*
 * PIN DRIVER BLOCK BEGIN
 */
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
#define PIN_CONFIG_EVENT_RISING                 (1)
#define PIN_CONFIG_EVENT_FALLING                (2)
#define PIN_CONFIG_EVENT_BOTH                   (3)
#define PIN_CONFIG_EVENT_MOD_DIV                (32U)
#define PIN_CONFIG_EVENT_MASK                   (0b1U)
#define PIN_CONFIG_EVENT_SET                    (0b1U)
#define PIN_CONFIG_EVENT_MUL                    (1U)

#define GPIO_GPFSEL_OFFSET                      (0x00U)
#define GPIO_GPSET_OFFSET                       (0x1cU)
#define GPIO_GPCLR_OFFSET                       (0x28U)
#define GPIO_GPLEV_OFFSET                       (0x34U)
#define GPIO_GPEDS_OFFSET                       (0x40U)
#define GPIO_GPREN_OFFSET                       (0x4cU)
#define GPIO_GPFEN_OFFSET                       (0x58U)
#define GPIO_GPHEN_OFFSET                       (0x64U)
#define GPIO_GPLEN_OFFSET                       (0x70U)
#define GPIO_GPAREN_OFFSET                      (0x7cU)
#define GPIO_GPAFEN_OFFSET                      (0x88U)
#define GPIO_GPPUD_OFFSET                       (0xe4U)

typedef volatile struct gpio_registers {
    uintptr_t *GPFSEL;
    uintptr_t *GPSET;
    uintptr_t *GPCLR;
    uintptr_t *GPLEV;
    uintptr_t *GPEDS;
    uintptr_t *GPREN;
    uintptr_t *GPFEN;
    uintptr_t *GPHEN;
    uintptr_t *GPLEN;
    uintptr_t *GPAREN;
    uintptr_t *GPAFEN;
    uintptr_t *GPPUD;
} gpio_registers_t;
/*
 * PIN DRIVER BLOCK END
 */

/*
 * I2C DRIVER BLOCK BEGIN
 */
#define BSC1_BASE_ADDRESS       (PERIPHERAL_BASE_ADDRESS+0x804000)

#define I2C_C_OFFSET            (0x00U)
#define I2C_S_OFFSET            (0x04U)
#define I2C_DLEN_OFFSET         (0x08U)
#define I2C_A_OFFSET            (0x0cU)
#define I2C_FIFO_OFFSET         (0x10U)
#define I2C_DIV_OFFSET          (0x14U)
#define I2C_DEL_OFFSET          (0x18U)
#define I2C_CLKT_OFFSET         (0x1cU)
#define I2C_C_EN                (1 << 15U)
#define I2C_C_DIS               (0 << 15U)
#define I2C_C_INTR_EN           (1 << 10U)
#define I2C_C_INTR_DIS          (0 << 10U)
#define I2C_C_INTT_EN           (1 << 9U)
#define I2C_C_INTT_DIS          (0 << 9U)
#define I2C_C_INTD_EN           (1 << 8U)
#define I2C_C_INTD_DIS          (0 << 8U)
#define I2C_C_ST                (1 << 7U)
#define I2C_C_CLEAR             (1 << 4U)
#define I2C_C_READ              (1 << 0U)
#define I2C_C_WRITE             (0 << 0U)
#define I2C_C_RECEIVE           (I2C_C_EN | I2C_C_INTR_DIS | I2C_C_INTT_DIS | I2C_C_INTD_DIS | I2C_C_ST | I2C_C_CLEAR | I2C_C_READ)
#define I2C_C_SEND              (I2C_C_EN | I2C_C_INTR_DIS | I2C_C_INTT_DIS | I2C_C_INTD_DIS | I2C_C_ST | I2C_C_CLEAR | I2C_C_WRITE)
#define I2C_S_CLKT              (1 << 9U)
#define I2C_S_ERR               (1 << 8U)
#define I2C_S_RXF               (1 << 7U)
#define I2C_S_TXE               (1 << 6U)
#define I2C_S_RXD               (1 << 5U)
#define I2C_S_TXD               (1 << 4U)
#define I2C_S_RXR               (1 << 3U)
#define I2C_S_TXW               (1 << 2U)
#define I2C_S_DONE              (1 << 1U)
#define I2C_S_TA_ACTIVE         (1 << 0U)
#define I2C_S_CLEAR             (I2C_S_CLKT | I2C_S_ERR | I2C_S_DONE)
#define I2C_DEL_DIV(fedl, redl) (((fedl)<<16U) | ((redl)<<0U))

typedef volatile struct i2c_registers {
    uintptr_t *C;
    uintptr_t *S;
    uintptr_t *DLEN;
    uintptr_t *A;
    uintptr_t *FIFO;
    uintptr_t *DIV;
    uintptr_t *DEL;
    uintptr_t *CLKT;
} i2c_registers_t;

/*
 * I2C DRIVER BLOCK BEGIN
 */

#define MAX_GPIO_PIN_SIZE   (10)
#define GPIO_PIN_5          (5)
#define GPIO_PIN_6          (6)
#define GPIO_PIN_16         (16)
#define GPIO_PIN_17         (17)
#define GPIO_PIN_22         (22)
#define GPIO_PIN_23         (23)
#define GPIO_PIN_24         (24)
#define GPIO_PIN_25         (25)
#define GPIO_PIN_26         (26)
#define GPIO_PIN_27         (27)

#define MAX_CLOCK_PIN_SIZE  (1)
#define CLOCK_PIN           (4)
#define CLOCK_PIN_FUNCTION  (PIN_CONFIG_FUNCTION_ALT0)

#define MAX_PWM_PIN_SIZE    (2)
#define PWM_PIN_CHANNEL_0   (12)
#define PWM_PIN_CHANNEL_1   (13)
#define PWM_PIN_FUNCTION    (PIN_CONFIG_FUNCTION_ALT0)

#define MAX_PCM_PIN_SIZE    (4)
#define PCM_PIN_CLK         (18)
#define PCM_PIN_FS          (19)
#define PCM_PIN_DIN         (20)
#define PCM_PIN_DOUT        (21)
#define PCM_PIN_FUNCTION    (PIN_CONFIG_FUNCTION_ALT0)

#define MAX_I2C_PIN_SIZE    (2)
#define I2C_PIN_SDA1        (2)
#define I2C_PIN_SCL1        (3)
#define I2C_PIN_FUNCTION    (PIN_CONFIG_FUNCTION_ALT0)

#define MAX_SPI_PIN_SIZE    (5)
#define SPI_PIN_CE1_N       (7)
#define SPI_PIN_CE0_N       (8)
#define SPI_PIN_MISO        (9)
#define SPI_PIN_MOSI        (10)
#define SPI_PIN_SCLK        (11)
#define SPI_PIN_FUNCTION    (PIN_CONFIG_FUNCTION_ALT0)

#define MAX_UART_PIN_SIZE   (2)
#define UART_PIN_TXD        (14)
#define UART_PIN_RXD        (15)
#define UART_PIN_FUNCTION   (PIN_CONFIG_FUNCTION_ALT0)

/*
 * gpio0 ?
 * gpio1 ?
 */


extern const uint8_t gpioPins[MAX_GPIO_PIN_SIZE];
extern const uint8_t clockPins[MAX_CLOCK_PIN_SIZE];
extern const uint8_t pwmPins[MAX_PWM_PIN_SIZE];
extern const uint8_t pcmPins[MAX_PCM_PIN_SIZE];
extern const uint8_t i2cPins[MAX_I2C_PIN_SIZE];
extern const uint8_t spiPins[MAX_SPI_PIN_SIZE];
extern const uint8_t uartPins[MAX_UART_PIN_SIZE];

int isElementInArray(const uint8_t *array, int arraySize, uint8_t elementToValidate);

#endif //GEMBEDDED_C_PERIPHERAL_H
