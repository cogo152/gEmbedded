//
// Created by sondahi on 06.12.22.
//

#include "memory_mapper.h"

int mapBaseRegister(const char *const fileName, const size_t length, const off_t offset, void **const pointer) {

    if (fileName == NULL) {
        return MAPPER_EXCEPTION_MAPPING_ERROR;
    }

    if (length < 1) {
        return MAPPER_EXCEPTION_MAPPING_ERROR;
    }

    if (pointer == NULL) {
        return MAPPER_EXCEPTION_MAPPING_ERROR;
    }

    const int memoryFileDescriptor = open(fileName, FILE_FLAG);

    if (memoryFileDescriptor < 0) {
        return MAPPER_EXCEPTION_MAPPING_ERROR;
    }

    void *const ptr = mmap(NULL, length, PROT_FLAG, MAP_FLAG, memoryFileDescriptor, offset);
    if (ptr == MAP_FAILED) {
        close(memoryFileDescriptor);
        *pointer = NULL;
        return MAPPER_EXCEPTION_MAPPING_ERROR;
    } else {
        *pointer = ptr;
    }

    close(memoryFileDescriptor);

    return MAPPER_EXCEPTION_NO_ERROR;

}

int unmapBaseRegister(void **const pointer, size_t const length) {

    if (pointer == NULL) {
        return MAPPER_EXCEPTION_UNMAPPING_ERROR;
    }

    if (*pointer == NULL) {
        return MAPPER_EXCEPTION_UNMAPPING_ERROR;
    }

    if (length < 1) {
        return MAPPER_EXCEPTION_UNMAPPING_ERROR;
    }

    const int memoryUnmapResult = munmap(*pointer, length);

    if (memoryUnmapResult < 0) {
        return MAPPER_EXCEPTION_UNMAPPING_ERROR;
    } else {
        *pointer = NULL;
    }

    return MAPPER_EXCEPTION_NO_ERROR;

}