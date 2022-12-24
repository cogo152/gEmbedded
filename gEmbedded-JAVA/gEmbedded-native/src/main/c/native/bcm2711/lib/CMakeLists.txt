set(OBJ_SRC
        src/clockmanager.c
        src/devicedriver.c
        src/gpiodriver.c
        src/i2cmasterdriver.c
        src/pwmdriver.c)

target_include_directories(${OBJ_LIB} PUBLIC ${COMMON_INC} ${OBJ_INC})
target_sources(${OBJ_LIB} PUBLIC ${COMMON_SRC} ${OBJ_SRC})
target_compile_options(${OBJ_LIB} PUBLIC ${GCC_COMPILE_RELEASE_OPTIONS})

target_include_directories(${SHARED_LIB} PRIVATE ${COMMON_INC} ${OBJ_INC})
target_sources(${SHARED_LIB} PRIVATE ${COMMON_SRC} ${OBJ_SRC})
target_compile_options(${SHARED_LIB} PRIVATE ${GCC_COMPILE_RELEASE_OPTIONS})