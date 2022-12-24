enable_language(C)

set(CMAKE_C_STANDARD 11)

add_library(
        ${LIB}
        STATIC
)

set(
        LIB_SRC
        src/mapper.c
        src/devicecontext.c
        src/pinvalidator.c
        src/pinregistrator.c
        src/pinfunction.c
        src/pullupdown.c
        src/inputpin.c
)

target_include_directories(
        ${LIB}
        PUBLIC
        inc
)

target_sources(
        ${LIB}
        PUBLIC
        ${LIB_SRC}
)

add_custom_command(
        TARGET ${LIB}
        POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble lib${LIB}.a > library.list
)