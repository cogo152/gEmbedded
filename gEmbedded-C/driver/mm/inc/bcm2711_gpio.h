//
// Created by sondahi on 13.01.23.
//

#ifndef GEMBEDDED_C_BCM2711_GPIO_H
#define GEMBEDDED_C_BCM2711_GPIO_H

#include "common.h"
#include "bcm2711_common.h"

#define SIZE    (2U)
#define TRUE    (1U)
#define FALSE   (0U)

#define GPIO_BASE_ADDRESS   (PERIPHERAL_BASE_ADDRESS+0x00200000)

#define FSEL_OFFSET         (0x00/4)
#define REN_OFFSET          (0x4c/4)
#define FEN_OFFSET          (0x58/4)
#define HEN_OFFSET          (0x64/4)
#define LEN_OFFSET          (0x70/4)
#define AREN_OFFSET         (0x7c/4)
#define AFEN_OFFSET         (0x88/4)
#define PUP_PDN_OFFSET      (0xe4/4)

#define SET_OFFSET          (0x1c/4)
#define CLR_OFFSET          (0x28/4)
#define LEV_OFFSET          (0x34/4)
#define EDS_OFFSET          (0x40/4)

#endif //GEMBEDDED_C_BCM2711_GPIO_H
