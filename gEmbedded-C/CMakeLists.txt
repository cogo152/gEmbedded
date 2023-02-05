cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain.cmake")

project(gEmbedded-C)

# compiler options
set(COMPILER_FLAGS "-Wall -mcpu=cortex-a72 -mtune=cortex-a72 -mfloat-abi=hard -mfpu=neon-fp-armv8")
set(VERBOSE "-v -Wl,--verbose")
set(CMAKE_C_FLAGS           "${COMPILER_FLAGS}" CACHE STRING    "c flags"           FORCE)
set(CMAKE_CXX_FLAGS         "${COMPILER_FLAGS}" CACHE STRING    "cpp flags"         FORCE)
set(CMAKE_C_FLAGS_RELEASE   "-O3 -DNDEBUG"      CACHE STRING    "c flags release"   FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O0 -ggdb -DDEBUG" CACHE STRING    "cpp flags release" FORCE)

# project languages
enable_language(C)
set(CMAKE_C_STANDARD 23)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)

# static library
set(LIB ${CMAKE_PROJECT_NAME})
add_library(
        ${LIB}
        STATIC
)
target_include_directories(
        ${LIB}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/common
)
add_custom_command(
        TARGET ${LIB}
        POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble lib${LIB}.a > library.list
)

# executable test
set(LIB_TEST "${LIB}_test")
add_executable(
        ${LIB_TEST}
)
target_include_directories(
        ${LIB_TEST}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/commontest
)
enable_testing()
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
target_link_libraries(
        ${LIB_TEST}
        PRIVATE
        ${LIB}
        GTest::gtest_main
)
add_custom_command(
        TARGET ${LIB_TEST}
        POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble ${LIB_TEST} > library_test.list
)

# order is important for test
add_subdirectory(driver)
