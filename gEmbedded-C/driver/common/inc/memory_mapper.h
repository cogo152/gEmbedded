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

#define MAPPER_EXCEPTION_NO_EXCEPTION       (0)
#define MAPPER_EXCEPTION_MAPPING_ERROR      (-1)
#define MAPPER_EXCEPTION_UNMAPPING_ERROR    (-2)

int mapBaseRegister(const char *fileName, size_t length, off_t offset, void **pointer);

int unmapBaseRegister(void **pointer, size_t length);

#endif //GEMBEDDED_C_MEMORY_MAPPER_H
