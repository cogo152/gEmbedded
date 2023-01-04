//
// Created by sondahi on 06.12.22.
//

#include "mapper.h"

MAPPER_STATUS
mapBaseRegister(const char *const fileName, const size_t length, const off_t offset, void **const pointer) {

    if (fileName == NULL) {
        printf("(fileName == NULL)\n");
        return MAPPER_ERROR;
    }

    if (length < 1) {
        printf("(length < 1)\n");
        return MAPPER_ERROR;
    }

    if (pointer == NULL) {
        printf("(pointer == NULL)\n");
        return MAPPER_ERROR;
    }

    const int memoryFileDescriptor = open(fileName, FILE_FLAG);

    if (memoryFileDescriptor < 0) {
        printf("(memoryFileDescriptor < 0)\n");
        return MAPPER_ERROR;
    }

    void *const ptr = mmap(NULL, length, PROT_FLAG, MAP_FLAG, memoryFileDescriptor, offset);
    if (ptr == MAP_FAILED) {
        close(memoryFileDescriptor);
        *pointer = NULL;
        printf("(ptr == MAP_FAILED)\n");
        return MAPPER_ERROR;
    } else {
        *pointer = ptr;
    }

    close(memoryFileDescriptor);

    return MAPPER_SUCCESS;

}

MAPPER_STATUS unmapBaseRegister(void **const pointer, size_t const length) {

    if (pointer == NULL) {
        printf("(pointer == NULL)\n");
        return MAPPER_ERROR;
    }

    if (*pointer == NULL) {
        printf("(*pointer == NULL)\n");
        return MAPPER_ERROR;
    }

    if (length < 1) {
        printf("(length < 1)\n");
        return MAPPER_ERROR;
    }

    const int memoryUnmapResult = munmap(*pointer, length);

    if (memoryUnmapResult < 0) {
        printf("(memoryUnmapResult < 0)\n");
        return MAPPER_ERROR;
    } else {
        *pointer = NULL;
    }

    return MAPPER_SUCCESS;

}