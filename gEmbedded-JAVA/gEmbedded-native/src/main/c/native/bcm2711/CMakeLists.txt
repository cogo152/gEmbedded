set(OBJ_INC ${CMAKE_CURRENT_SOURCE_DIR}/lib/inc)
set(OBJ_LIB bcm271132_obj)
add_library(${OBJ_LIB} OBJECT)

set(TEST_LIB bcm271132_test)
add_executable(${TEST_LIB})

add_subdirectory(lib)
add_subdirectory(test)