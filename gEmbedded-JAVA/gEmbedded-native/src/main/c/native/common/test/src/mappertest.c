#include "mappertest.h"

void static *pointer = NULL;

void testMapBaseRegister (void) {

    MAPPER_STATUS status;

    // MAPPER_FILE_NAME_ERROR : if the fileName is NULL.
    status = mapBaseRegister (NULL, LENGTH, OFFSET, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_FILE_NAME_ERROR)

    // MAPPER_LENGTH_ERROR : if the length is less than 1.
    status = mapBaseRegister (FILE_NAME, INVALID_LENGTH, OFFSET, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_LENGTH_ERROR)

    // MAPPER_POINTER_ERROR : if the pointer is NULL.
    status = mapBaseRegister (FILE_NAME, LENGTH, OFFSET, NULL);
    CU_ASSERT_EQUAL(status, MAPPER_POINTER_ERROR)

    // MAPPER_FILE_OPEN_ERROR : if the fileName is invalid.
    status = mapBaseRegister (INVALID_FILE_NAME, LENGTH, OFFSET, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_FILE_OPEN_ERROR)

    // MAPPER_MAP_ERROR : if the mapping fails.
    status = mapBaseRegister (FILE_NAME, LENGTH, 1, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_MAP_ERROR)

    status = mapBaseRegister (FILE_NAME, LENGTH, OFFSET, &pointer);
    CU_ASSERT_EQUAL(status, MAPPER_SUCCESS)

}

void testUnmapBaseRegister (void) {

    MAPPER_STATUS status;

    void *nullPointer = NULL;

    void *invalidPointer = (void *) 1;

    // MAPPER_POINTER_ERROR : if the **pointer is NULL.
    status = unmapBaseRegister (NULL, LENGTH);
    CU_ASSERT_EQUAL(status, MAPPER_POINTER_ERROR)

    // MAPPER_POINTER_ERROR : if the *pointer is NULL.
    status = unmapBaseRegister (&nullPointer, LENGTH);
    CU_ASSERT_EQUAL(status, MAPPER_POINTER_ERROR)

    // MAPPER_LENGTH_ERROR : if the length is less than 1.
    status = unmapBaseRegister (&pointer, INVALID_LENGTH);
    CU_ASSERT_EQUAL(status, MAPPER_LENGTH_ERROR)

    // MAPPER_UNMAP_ERROR : if the unmapping fails.
    status = unmapBaseRegister (&invalidPointer, LENGTH);
    CU_ASSERT_EQUAL(status, MAPPER_UNMAP_ERROR)

    status = unmapBaseRegister (&pointer, LENGTH);
    CU_ASSERT_EQUAL(status, MAPPER_SUCCESS)
    CU_ASSERT_PTR_EQUAL(pointer, NULL)

}