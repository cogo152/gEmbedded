target_include_directories(${KERNEL_LIB} PUBLIC inc)

target_sources(${KERNEL_LIB} PUBLIC
        src/core.S
        src/exception.c
        src/memory.c
        src/memory.S
        src/process.c
        src/process.S
        src/startup.S
        src/system.c
        src/system.S
        src/systemcall.S
        src/vectors.S)
