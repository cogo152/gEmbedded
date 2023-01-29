set(
        INC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

target_include_directories(
        ${LIB}
        PUBLIC
        ${INC}
)

aux_source_directory(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        LIB_SRC
)

#aux_source_directory(
#        ${CMAKE_CURRENT_SOURCE_DIR}/test
#        LIB_TEST_SRC
#)

target_sources(
        ${LIB}
        PUBLIC
        ${LIB_SRC}
)

#target_sources(
#        ${LIB_TEST}
#        PRIVATE
#        ${LIB_TEST_SRC}
#)