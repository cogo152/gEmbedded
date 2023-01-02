enable_language(CXX)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

add_executable(
        ${LIB_TEST}
)

set(
        TEST_SRC
        #mappertest.cpp
        #devicecontexttest.cpp
        #pinvalidatortest.cpp
        #pinregistratortest.cpp
        #pinfunctiontest.cpp
        #pullupdowntest.cpp
)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/a16bfcfda1ea994c1abec23cca8f530953042dfa.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

gtest_discover_tests(${LIB_TEST})

target_sources(
        ${LIB_TEST}
        PRIVATE
        ${TEST_SRC}
)

target_link_libraries(
        ${LIB_TEST}
        PRIVATE
        ${LIB}
        GTest::gtest_main
)

add_custom_command(
        TARGET ${LIB_TEST}
        POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -S --disassemble ${LIB_TEST} > library_test.list
)