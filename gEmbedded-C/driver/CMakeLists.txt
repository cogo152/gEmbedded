set(
        INC
        ${CMAKE_CURRENT_SOURCE_DIR}/api
        ${CMAKE_CURRENT_SOURCE_DIR}/common
)

target_include_directories(
        ${LIB}
        PUBLIC
        ${INC}
)

set(
        INC_TEST
        ${CMAKE_CURRENT_SOURCE_DIR}/commontest
)

target_include_directories(
        ${LIB_TEST}
        PRIVATE
        ${INC_TEST}
)

# order is important for test
add_subdirectory(memory)
add_subdirectory(context)
add_subdirectory(gpio)
add_subdirectory(i2c)