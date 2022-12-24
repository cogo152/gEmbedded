#ifndef I2CMASTERDRIVER_H
#define I2CMASTERDRIVER_H

#include "common.h"

#define I2C_C_OFFSET            (0x00 / 4)
#define I2C_S_OFFSET            (0x04 / 4)
#define I2C_DLEN_OFFSET         (0x08 / 4)
#define I2C_A_OFFSET            (0x0c / 4)
#define I2C_FIFO_OFFSET         (0x10 / 4)
#define I2C_DIV_OFFSET          (0x14 / 4)
#define I2C_DEL_OFFSET          (0x18 / 4)
#define I2C_CLKT_OFFSET         (0x1c / 4)

#define I2C_C_EN                (1 << 15)
#define I2C_C_DIS               (0 << 15)
#define I2C_C_INTR_EN           (1 << 10)
#define I2C_C_INTR_DIS          (0 << 10)
#define I2C_C_INTT_EN           (1 << 9)
#define I2C_C_INTT_DIS          (0 << 9)
#define I2C_C_INTD_EN           (1 << 8)
#define I2C_C_INTD_DIS          (0 << 8)
#define I2C_C_ST                (1 << 7)
#define I2C_C_CLEAR             (1 << 4)
#define I2C_C_READ              (1 << 0)
#define I2C_C_WRITE             (0 << 0)
#define I2C_C_RECEIVE           (I2C_C_EN | I2C_C_INTR_DIS | I2C_C_INTT_DIS | I2C_C_INTD_DIS | I2C_C_ST | I2C_C_CLEAR | I2C_C_READ)
#define I2C_C_SEND              (I2C_C_EN | I2C_C_INTR_DIS | I2C_C_INTT_DIS | I2C_C_INTD_DIS | I2C_C_ST | I2C_C_CLEAR | I2C_C_WRITE)

#define I2C_S_CLKT              (1 << 9)
#define I2C_S_ERR               (1 << 8)
#define I2C_S_RXF               (1 << 7)
#define I2C_S_TXE               (1 << 6)
#define I2C_S_RXD               (1 << 5)
#define I2C_S_TXD               (1 << 4)
#define I2C_S_RXR               (1 << 3)
#define I2C_S_TXW               (1 << 2)
#define I2C_S_DONE              (1 << 1)
#define I2C_S_TA_ACTIVE         (1 << 0)
#define I2C_S_CLEAR             (I2C_S_CLKT | I2C_S_ERR | I2C_S_DONE)

#define I2C_DEL_DIV(fedl, redl) (((fedl)<<16) | ((redl)<<0))

typedef enum {
    I2C_SUCCESS = 0,
    I2C_NO_ACKNOWLEDGE = 1,
    I2C_CLOCK_STRETCH_TIMEOUT = 2,
    I2C_DATA_LOSS = 3
} I2C_STATUS;

#endif //I2CMASTERDRIVER_H
