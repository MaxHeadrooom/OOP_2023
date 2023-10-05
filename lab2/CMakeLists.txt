cmake_minimum_required(VERSION 3.10)

project(oop_mai_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

add_executable(
    main 
    main.cpp 
    eleven_constr.cpp 
    eleven_get.cpp 
    operations.cpp 
    bool_op.cpp
    private.cpp
)

add_executable(
    tests
    tests.cpp
    eleven_constr.cpp 
    eleven_get.cpp 
    operations.cpp 
    bool_op.cpp
    private.cpp
)
target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)