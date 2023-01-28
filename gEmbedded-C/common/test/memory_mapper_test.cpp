//
// Created by sondahi on 06.12.22.
//

#include "gtest/gtest.h"
extern "C" {
#include "memory_mapper.h"
}

#define MAPPER_FILE_NAME            ("/dev/gpiomem")
#define MAPPER_BLOCK_SIZE           (0X1000)
#define MAPPER_OFFSET               (0)
#define MAPPER_INVALID_FILE_NAME    ("/dev/invalidFile")
#define MAPPER_INVALID_BLOCK_SIZE   (0)

static void *pointer = nullptr;

TEST(MapperTest, testMapBaseRegister) {

    int status;

    status = mapBaseRegister(nullptr, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_EXCEPTION_MAPPING_ERROR);

    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_INVALID_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_EXCEPTION_MAPPING_ERROR);

    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, nullptr);
    EXPECT_EQ(status, MAPPER_EXCEPTION_MAPPING_ERROR);

    status = mapBaseRegister(MAPPER_INVALID_FILE_NAME, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_EXCEPTION_MAPPING_ERROR);

    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_BLOCK_SIZE, 1, &pointer);
    EXPECT_EQ(status, MAPPER_EXCEPTION_MAPPING_ERROR);

    status = mapBaseRegister(MAPPER_FILE_NAME, MAPPER_BLOCK_SIZE, MAPPER_OFFSET, &pointer);
    EXPECT_EQ(status, MAPPER_EXCEPTION_NO_EXCEPTION);
    EXPECT_NE(pointer, nullptr);

}

TEST(MapperTest, testUnmapBaseRegister) {

    int status;

    void *nullPointer = nullptr;

    void *invalidPointer = (void *) 1;

    status = unmapBaseRegister(nullptr, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_EXCEPTION_UNMAPPING_ERROR);

    status = unmapBaseRegister(&nullPointer, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_EXCEPTION_UNMAPPING_ERROR);

    status = unmapBaseRegister(&pointer, MAPPER_INVALID_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_EXCEPTION_UNMAPPING_ERROR);

    status = unmapBaseRegister(&invalidPointer, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_EXCEPTION_UNMAPPING_ERROR);

    status = unmapBaseRegister(&pointer, MAPPER_BLOCK_SIZE);
    EXPECT_EQ(status, MAPPER_EXCEPTION_NO_EXCEPTION);
    EXPECT_EQ(pointer, nullptr);

}