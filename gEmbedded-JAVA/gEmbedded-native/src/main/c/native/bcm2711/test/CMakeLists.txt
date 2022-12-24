set(TEST_SRC
        src/devicedrivertest.c
        src/test.c)

target_include_directories(${TEST_LIB} PRIVATE /usr/include/CUnit ${COMMON_INC} ${COMMON_TEST_INC} ${OBJ_INC} inc)
target_sources(${TEST_LIB} PRIVATE $<TARGET_OBJECTS:${OBJ_LIB}> ${COMMON_TEST_RSRC} ${COMMON_TEST_SRC} ${TEST_SRC})
target_link_libraries(${TEST_LIB} PRIVATE ${JNI_LIBRARIES} cunit)
target_compile_options(${TEST_LIB} PRIVATE ${GCC_COMPILE_TEST_OPTIONS})