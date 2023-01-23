//
// Created by sondahi on 06.12.22.
//

#include "memory_mapper.h"

MAPPER_STATUS
mapBaseRegister(const char *const fileName, const size_t length, const off_t offset, void **const pointer) {

    if (fileName == NULL) {
        return MAPPER_ERROR;
    }

    if (length < 1) {
        return MAPPER_ERROR;
    }

    if (pointer == NULL) {
        return MAPPER_ERROR;
    }

    const int memoryFileDescriptor = open(fileName, FILE_FLAG);

    if (memoryFileDescriptor < 0) {
        return MAPPER_ERROR;
    }

    void *const ptr = mmap(NULL, length, PROT_FLAG, MAP_FLAG, memoryFileDescriptor, offset);
    if (ptr == MAP_FAILED) {
        close(memoryFileDescriptor);
        *pointer = NULL;
        return MAPPER_ERROR;
    } else {
        *pointer = ptr;
    }

    close(memoryFileDescriptor);

    return MAPPER_SUCCESS;

}

MAPPER_STATUS unmapBaseRegister(void **const pointer, size_t const length) {

    if (pointer == NULL) {
        return MAPPER_ERROR;
    }

    if (*pointer == NULL) {
        return MAPPER_ERROR;
    }

    if (length < 1) {
        return MAPPER_ERROR;
    }

    const int memoryUnmapResult = munmap(*pointer, length);

    if (memoryUnmapResult < 0) {
        return MAPPER_ERROR;
    } else {
        *pointer = NULL;
    }

    return MAPPER_SUCCESS;

}