target_include_directories(${EXECUTABLE} PRIVATE ${KERNEL_INC} inc)

target_sources(${EXECUTABLE} PRIVATE
        src/test.c)

        target_link_libraries(${EXECUTABLE} PRIVATE ${KERNEL_LIB})