cmake_minimum_required(VERSION 3.18.4)

if(NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja")
        message(STATUS "cmake genarator is set to Ninja")
        set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "cmake generator" FORCE)
endif()

project(native)

enable_language(C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(VERBOSE "-v")

set(CMAKE_C_FLAGS                   "-Wall -march=native -mcpu=native -mtune=native" CACHE INTERNAL "c flags")
set(CMAKE_C_FLAGS_DEBUG             "-O0 -ggdb ${VERBOSE}" CACHE INTERNAL "debug options")
set(CMAKE_C_FLAGS_MINSIZEREL        "-O2 -DNDEBUG" CACHE INTERNAL "minsizerel options")
set(CMAKE_C_FLAGS_RELWITHDEBINFO    "-O3 -ggdb ${VERBOSE}" CACHE INTERNAL "relwithdebinfo options")
set(CMAKE_C_FLAGS_RELEASE           "-O3 -DNDEBUG" CACHE INTERNAL "release options")

find_package(JNI REQUIRED)

include_directories(
        ${JNI_INCLUDE_DIRS}
)

set(COMMON_INC
        ${CMAKE_CURRENT_SOURCE_DIR}/common/lib/inc)
set(COMMON_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/common/lib/src/jniutil.c
        ${CMAKE_CURRENT_SOURCE_DIR}/common/lib/src/mapper.c)

set(COMMON_TEST_INC
        ${CMAKE_CURRENT_SOURCE_DIR}/common/test/inc)
set(COMMON_TEST_RSRC
        ${CMAKE_CURRENT_SOURCE_DIR}/common/test/rsrc)
set(COMMON_TEST_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/common/test/src/jvm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/common/test/src/jniutiltest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/common/test/src/mappertest.c)

set(SHARED_LIB gEbcm271132)
add_library(${SHARED_LIB} SHARED)
set_target_properties(${SHARED_LIB} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "/usr/lib")

add_custom_command(TARGET ${SHARED_LIB}
        POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble /usr/lib/lib${SHARED_LIB}.so > ${PROJECT_NAME}.dump)

add_subdirectory(bcm2711)

