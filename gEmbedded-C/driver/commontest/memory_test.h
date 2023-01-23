//
// Created by sondahi on 15.01.23.
//

#ifndef GEMBEDDED_C_MEMORY_TEST_H
#define GEMBEDDED_C_MEMORY_TEST_H

extern "C" {
#include "memory_mapper.h"
}

/*
 * mapper definitions
 */
#define MAPPER_FILE_NAME            ("/dev/gpiomem")
#define MAPPER_BLOCK_SIZE           (0X1000)
#define MAPPER_OFFSET               (0)
#define MAPPER_INVALID_FILE_NAME    ("/dev/invalidFile")
#define MAPPER_INVALID_BLOCK_SIZE   (0)

#endif //GEMBEDDED_C_MEMORY_TEST_H
