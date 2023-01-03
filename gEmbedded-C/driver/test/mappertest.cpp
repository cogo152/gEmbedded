//
// Created by sondahi on 06.12.22.
//

#include "gtest/gtest.h"

extern "C" {
#include "mapper.h"
#include "registers.h"
}

#define FILE_NAME           (MEMORY_FILE_NAME)
#define LENGTH              (BLOCK_SIZE)
#define OFFSET              (GPIO_BASE_ADDRESS)

#define INVALID_FILE_NAME   ("/dev/invalidFile")
#define INVALID_LENGTH      (0)


void static *pointer = nullptr;

TEST(MapperTest, testMapBaseRegister) {

    MAPPER_STATUS status;

    // MAPPER_FILE_NAME_ERROR : if the fileName is NULL.
    status = mapBaseRegister(nullptr, LENGTH, OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_FILE_NAME_ERROR);

    // MAPPER_LENGTH_ERROR : if the length is less than 1.
    status = mapBaseRegister(FILE_NAME, INVALID_LENGTH, OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_LENGTH_ERROR);

    // MAPPER_POINTER_ERROR : if the pointer is NULL.
    status = mapBaseRegister(FILE_NAME, LENGTH, OFFSET, nullptr);
    EXPECT_EQ(status, MAPPER_POINTER_ERROR);

    // MAPPER_FILE_OPEN_ERROR : if the fileName is invalid.
    status = mapBaseRegister(INVALID_FILE_NAME, LENGTH, OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_FILE_OPEN_ERROR);

    // MAPPER_MAP_ERROR : if the mapping fails.
    status = mapBaseRegister(FILE_NAME, LENGTH, 1, &pointer);
    EXPECT_EQ(status, MAPPER_MAP_ERROR);

    status = mapBaseRegister(FILE_NAME, LENGTH, OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_SUCCESS);
    EXPECT_NE(pointer, nullptr);

}

TEST(MapperTest, testUnmapBaseRegister) {

    MAPPER_STATUS status;

    void *nullPointer = nullptr;

    void *invalidPointer = (void *) 1;

    // MAPPER_POINTER_ERROR : if the **pointer is NULL.
    status = unmapBaseRegister(nullptr, LENGTH);
    EXPECT_EQ(status, MAPPER_POINTER_ERROR);

    // MAPPER_POINTER_ERROR : if the *pointer is NULL.
    status = unmapBaseRegister(&nullPointer, LENGTH);
    EXPECT_EQ(status, MAPPER_POINTER_ERROR);

    // MAPPER_LENGTH_ERROR : if the length is less than 1.
    status = unmapBaseRegister(&pointer, INVALID_LENGTH);
    EXPECT_EQ(status, MAPPER_LENGTH_ERROR);

    // MAPPER_UNMAP_ERROR : if the unmapping fails.
    status = unmapBaseRegister(&invalidPointer, LENGTH);
    EXPECT_EQ(status, MAPPER_UNMAP_ERROR);

    status = unmapBaseRegister(&pointer, LENGTH);
    EXPECT_EQ(status, MAPPER_SUCCESS);
    EXPECT_EQ(pointer, nullptr);

}