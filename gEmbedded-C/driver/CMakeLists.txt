set(
        INC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

set(
        LIB_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/x.c
)

set(
        LIB_TEST_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/test/xtest.cpp
)

target_include_directories(
        ${LIB}
        PUBLIC
        ${INC}
)

target_sources(
        ${LIB}
        PUBLIC
        ${LIB_SRC}
)

target_sources(
        ${LIB_TEST}
        PRIVATE
        ${LIB_TEST_SRC}
)