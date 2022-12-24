target_include_directories(${KERNEL_LIB} PUBLIC inc)

target_sources(${KERNEL_LIB} PUBLIC
        src/userinterface.c)