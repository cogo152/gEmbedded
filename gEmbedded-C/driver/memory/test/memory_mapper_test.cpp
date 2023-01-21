//
// Created by sondahi on 06.12.22.
//

#include "common_test.h"
#include "memory_test.h"

extern "C" {
#include "memory_mapper.h"
}

static void  *pointer = nullptr;

TEST(MapperTest, testMapBaseRegister) {

    MAPPER_STATUS status;

    // MAPPER_FILE_NAME_ERROR : if the fileName is NULL.
    status = mapBaseRegister(nullptr, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_LENGTH_ERROR : if the length is less than 1.
    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_INVALID_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_POINTER_ERROR : if the pointer is NULL.
    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, nullptr);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_FILE_OPEN_ERROR : if the fileName is invalid.
    status = mapBaseRegister(MAPPER_INVALID_FILE_NAME, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_MAP_ERROR : if the mapping fails.
    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_BLOCK_SIZE, 1, &pointer);
    EXPECT_EQ(status, MAPPER_ERROR);

    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_SUCCESS);
    EXPECT_NE(pointer, nullptr);

}

TEST(MapperTest, testUnmapBaseRegister) {

    MAPPER_STATUS status;

    void *nullPointer = nullptr;

    void *invalidPointer = (void *) 1;

    // MAPPER_POINTER_ERROR : if the **pointer is NULL.
    status = unmapBaseRegister(nullptr, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_POINTER_ERROR : if the *pointer is NULL.
    status = unmapBaseRegister(&nullPointer, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_LENGTH_ERROR : if the length is less than 1.
    status = unmapBaseRegister(&pointer, MAPPER_INVALID_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_ERROR);

    // MAPPER_UNMAP_ERROR : if the unmapping fails.
    status = unmapBaseRegister(&invalidPointer, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_ERROR);

    status = unmapBaseRegister(&pointer, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_SUCCESS);
    EXPECT_EQ(pointer, nullptr);

}