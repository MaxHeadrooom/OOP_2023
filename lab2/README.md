# Лабораторная 2(на 04.10.2023 без реализации перегрузки оператора, постараюсь потом сделать, просто никогда не делал с объектами, надо будет попробовать)   

# Эсмедляев Федор

CMakeList.txt
```
cmake_minimum_required(VERSION 3.10)

project(oop_mai_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

add_executable(tests eleven_constr.cpp tests.cpp eleven_get.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
```
