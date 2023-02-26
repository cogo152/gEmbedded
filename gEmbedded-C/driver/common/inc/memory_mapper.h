//
// Created by sondahi on 15.01.23.
//

#ifndef GEMBEDDED_C_MEMORY_MAPPER_H
#define GEMBEDDED_C_MEMORY_MAPPER_H

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "common.h" // no size_t vs

#define MEMORY_FILE_NAME    ("/dev/mem")
#define BLOCK_SIZE          (0X1000)
#define FILE_FLAG           (O_RDWR | O_SYNC)
#define PROT_FLAG           (PROT_READ | PROT_WRITE)
#define MAP_FLAG            (MAP_SHARED)

typedef enum{
    MAPPER_ERROR_NO = 0,
    MAPPER_ERROR_MAP = -1,
    MAPPER_ERROR_UNMAP = -2
} MAPPER_ERROR;


MAPPER_ERROR mapBaseRegister(const char* pFileName, size_t length, off_t offset, void** pBase);

MAPPER_ERROR unmapBaseRegister(void** pBase, size_t length);

#endif //GEMBEDDED_C_MEMORY_MAPPER_H
