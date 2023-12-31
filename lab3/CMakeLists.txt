cmake_minimum_required(VERSION 3.10)

project(oop_mai_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

add_executable(
    main 
    main.cpp
    point.cpp 
    six_ugl.cpp
    eight_ugl.cpp
    triangle.cpp 
    array.cpp
)

add_executable(
    tests
    tests.cpp
    point.cpp 
    six_ugl.cpp
    eight_ugl.cpp
    triangle.cpp 
    array.cpp 
)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)