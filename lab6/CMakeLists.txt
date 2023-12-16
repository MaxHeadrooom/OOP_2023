cmake_minimum_required(VERSION 3.10)
project(Lab06)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

add_executable(
    main 
    main.cpp
    observer.cpp
    factory.cpp
    npc.cpp
    squirrel.cpp
    bear.cpp
    orc.cpp)

enable_testing()
add_executable(
    tests
    tests.cpp
    observer.cpp
    factory.cpp
    npc.cpp
    squirrel.cpp
    bear.cpp
    orc.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)