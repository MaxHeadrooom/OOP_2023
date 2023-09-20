cmake_minimum_required(VERSION 3.27)
project(OOP_MAI)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

add_executable(OOP_MAI "test.cpp" "raschet.cpp" "func.h")

add_executable(tests tests.cpp raschet.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)