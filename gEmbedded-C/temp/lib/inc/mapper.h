//
// Created by sondahi on 06.12.22.
//

#ifndef GEMBEDDED_C_MAPPER_H
#define GEMBEDDED_C_MAPPER_H

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h"

#define FILE_FLAG   (O_RDWR | O_SYNC)
#define PROT_FLAG   (PROT_READ | PROT_WRITE)
#define MAP_FLAG    (MAP_SHARED)

typedef enum {
    MAPPER_SUCCESS = 0,
    MAPPER_FILE_NAME_ERROR = 1,
    MAPPER_LENGTH_ERROR = 2,
    MAPPER_POINTER_ERROR = 3,
    MAPPER_FILE_OPEN_ERROR = 4,
    MAPPER_MAP_ERROR = 5,
    MAPPER_UNMAP_ERROR = 6
} MAPPER_STATUS;

MAPPER_STATUS mapBaseRegister(const char *fileName, size_t length, off_t offset, void **pointer);

MAPPER_STATUS unmapBaseRegister(void **pointer, size_t length);

#endif //GEMBEDDED_C_MAPPER_H
