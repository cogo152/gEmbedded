//
// Created by sondahi on 06.12.22.
//

#include "memory_mapper.h"

MAPPER_ERROR
mapBaseRegister(const char* const pFileName, const size_t length, const off_t offset, void** const pBase) {

    if (pFileName == NULL) {
        return MAPPER_ERROR_MAP;
    }

    if (length < 1) {
        return MAPPER_ERROR_MAP;
    }

    if (pBase == NULL) {
        return MAPPER_ERROR_MAP;
    }

    const int memoryFileDescriptor = open(pFileName, FILE_FLAG);

    if (memoryFileDescriptor < 0) {
        return MAPPER_ERROR_MAP;
    }

    void* const base = mmap(NULL, length, PROT_FLAG, MAP_FLAG, memoryFileDescriptor, offset);
    if (base == MAP_FAILED) {
        close(memoryFileDescriptor);
        *pBase = NULL;
        return MAPPER_ERROR_MAP;
    } else {
        *pBase = base;
    }

    close(memoryFileDescriptor);

    return MAPPER_ERROR_NO;

}

MAPPER_ERROR unmapBaseRegister(void** const pBase, const size_t length) {

    if (pBase == NULL) {
        return MAPPER_ERROR_UNMAP;
    }

    if (*pBase == NULL) {
        return MAPPER_ERROR_UNMAP;
    }

    if (length < 1) {
        return MAPPER_ERROR_UNMAP;
    }

    const int memoryUnmapResult = munmap(*pBase, length);

    if (memoryUnmapResult < 0) {
        return MAPPER_ERROR_UNMAP;
    } else {
        *pBase = NULL;
    }

    return MAPPER_ERROR_NO;

}