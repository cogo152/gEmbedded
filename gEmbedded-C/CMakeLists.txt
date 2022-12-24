cmake_minimum_required(VERSION 3.22.1)

if(NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja")
    message(STATUS "cmake genarator is set to Ninja")
    set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "cmake generator" FORCE)
endif()

if(NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "cmake build type is set to Release" FORCE)
endif()

project(gEmbedded-C)

set(COMPILER_FLAGS              "-mcpu=native -march=native -mtune=native -mfloat-abi=hard -mfpu=auto")
set(VERBOSE                     "-Wall -v -Wl,--verbose")
set(CMAKE_C_FLAGS               "${COMPILER_FLAGS}" CACHE INTERNAL "c flags")
set(CMAKE_CXX_FLAGS             "${CMAKE_C_FLAGS}" CACHE INTERNAL "cpp flags")
set(LIBRARY_OPTIONS             "-O3")
set(LIBRARY_TEST_OPTIONS        "-O0 -ggdb")
set(CMAKE_C_FLAGS_RELEASE       "${LIBRARY_OPTIONS}" CACHE INTERNAL "c release options")
set(CMAKE_CXX_FLAGS_RELEASE     "${LIBRARY_TEST_OPTIONS}" CACHE INTERNAL "cpp release-test options")

include_directories(api)

set(
        LIB
        ${CMAKE_PROJECT_NAME}
)

set(
        LIB_TEST
        "${LIB}_test"
)

add_subdirectory(lib)
add_subdirectory(test)
