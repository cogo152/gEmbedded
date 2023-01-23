set(
        INC
        ${CMAKE_CURRENT_SOURCE_DIR}/api
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
add_subdirectory(common)
#add_subdirectory(context)
add_subdirectory(pin)
#add_subdirectory(i2c)