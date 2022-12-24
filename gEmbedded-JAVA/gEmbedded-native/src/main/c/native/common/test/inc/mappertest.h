#ifndef MAPPERTEST_H
#define MAPPERTEST_H

#include "commontest.h"
#include "mapper.h"

#define FILE_NAME           ("/dev/gpiomem")
#define LENGTH              (0xF4)
#define OFFSET              (0)

#define INVALID_FILE_NAME   ("/dev/invalidFile")
#define INVALID_LENGTH      (0)

void testMapBaseRegister (void);

void testUnmapBaseRegister (void);

#define MAPPER_TEST \
            CU_TestInfo mapperTests[] = { \
                { "testMapBaseRegister", testMapBaseRegister }, \
                { "testUnmapBaseRegister", testUnmapBaseRegister }, \
                CU_TEST_INFO_NULL }; \

#endif //MAPPERTEST_H
