cmake_minimum_required(VERSION 3.22.1)

if(NOT "${CMAKE_GENERATOR}" STREQUAL "Ninja")
        message(STATUS "cmake genarator is set to Ninja")
        set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "cmake generator" FORCE)
endif()

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/toolchain-none.cmake")

project(gMOS)

set(CPU_ARCH    "-mcpu=cortex-m4 -mthumb")
set(FPU         "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(C_LIB       "-nostdlib")
set(VERBOSE     "-Wall -v -Wl,--verbose")
set(LINKER_FILE "${CMAKE_SOURCE_DIR}/config/STM32F411.ld")


set(CMAKE_C_FLAGS                   "${CPU_ARCH} ${FPU} ${C_LIB} -fdata-sections -ffunction-sections" CACHE INTERNAL "c flags")
set(CMAKE_CXX_FLAGS                 "${CMAKE_C_FLAGS}" CACHE INTERNAL "cpp flags")

set(CMAKE_C_FLAGS_DEBUG             "-O0 -ggdb ${VERBOSE}" CACHE INTERNAL "debug options")
set(CMAKE_C_FLAGS_MINSIZEREL        "-O2 -DNDEBUG" CACHE INTERNAL "min size options")
set(CMAKE_C_FLAGS_RELWITHDEBINFO    "-O3 -ggdb ${VERBOSE}" CACHE INTERNAL "release with debug options")
set(CMAKE_C_FLAGS_RELEASE           "-O3 -DNDEBUG" CACHE INTERNAL "release options")
set(CMAKE_EXE_LINKER_FLAGS          "-T${LINKER_FILE} -Wl,-fuse-ld=mold -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref" CACHE INTERNAL "linker flags")

enable_language(ASM C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(KERNEL_INC ${CMAKE_CURRENT_SOURCE_DIR/kernel/core/inc})
set(KERNEL_LIB ${CMAKE_PROJECT_NAME})
add_library(${KERNEL_LIB} STATIC)

set(EXECUTABLE ${CMAKE_PROJECT_NAME}.elf)
add_executable(${EXECUTABLE})

add_custom_command(TARGET ${EXECUTABLE}
        POST_BUILD
        COMMAND ${CMAKE_SIZE} ${EXECUTABLE}
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble ${EXECUTABLE} > ${CMAKE_PROJECT_NAME}.list
        COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${CMAKE_PROJECT_NAME}.bin
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${CMAKE_PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJCOPY} -O srec --srec-len 0x10 ${EXECUTABLE} ${CMAKE_PROJECT_NAME}.srec)
        

add_subdirectory(kernel)
add_subdirectory(user)

