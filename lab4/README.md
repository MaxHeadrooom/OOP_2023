# Лабораторная 4

# Эсмедляев Федор

Разработать шаблоны классов согласно варианту задания. Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. Классы должны иметь только публичные поля. В классах не должно быть методов, только поля. Фигуры являются фигурами вращения (равнобедренными), за исключением трапеции и прямоугольника. Для хранения координат фигур необходимо использовать шаблон std::pair (или реализовать свой шаблон template Point в качестве параметра шаблона должен быть тип для переменных координат)

Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:

Вычисление геометрического центра фигуры вращения;
Вывод в стандартный поток вывода std::cout координат вершин фигуры;
Вычисление площади фигуры; Создать программу, которая позволяет:
Запрещается использовать сырые указатели
Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
Сохранять созданные фигуры в динамический массив (переиспользовать от предыдущей лабораторной работы) умных указатели на фигуру (std::smart_ptr<Figure*>)
Динамический массив должен быть сделан в виде шаблона (параметр шаблона – класс для хранения в массиве template Array {...})
Фигуры должны иметь переопределенные операции копирования, сравнения и приведение к типу double (вычисление площади)
Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.
Необходимо уметь вычислять общую площадь фигур в массиве.
Удалять из массива фигуру по индексу;

Вариант 23: 6-угольник, 8-угольник, треугольник.

# Программы

# CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10)

project(oop_mai_4)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(googletest)

enable_testing()

add_executable(
    main
    main.cpp
)

add_executable(
    tests
    tests.cpp
)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
```

# array.h
```
#include "figure.h"
#include "functions.h"

#include <iostream>
#include <utility>
#include <memory>// для shared_ptr
#include <stdexcept>//throw

using ll = long long;

template<typename T>
class Array
{
private:
    std::shared_ptr<T[]> figuri = nullptr;
    ll size = 0;

 public:
    Array() = default;

    Array(ll sizee) : size(sizee)
    {
        figuri = std::shared_ptr<T[]>(new T[size]);

        figuri.reset(new T[size]);
    }

    ~Array() = default;

    Array operator=(const Array<T>& figuri);


    void push_back(ll pos, T fig)
    {
        if (pos > size)
        throw std::invalid_argument("Out of range when push_back");

        if (figuri[pos] == nullptr)
        figuri[pos] = fig;
        else
        throw std::runtime_error("I can't push because place is alredy exist");
    }


    void pop(ll pos)
    {
        if (pos < 0 or pos > size)
        throw std::invalid_argument("Out of range when pop");

        if (figuri[pos] != nullptr)
        {
        delete figuri[pos];
        figuri[pos] = nullptr;
        }
    }


    double calc_all_s()
    {
        double s = 0.0;

        for (int i = 0; i < size; i++)
        {
            s += figuri[i].calculate_S();
        }

        return s;
    }
    

    T& operator[](ll index);
};

template <class T>
inline T& Array<T>::operator[](ll index)
{
    if (index >= size)
        throw std::invalid_argument("The array index is out of range");

    return figuri.get()[index];
}
```

# figure.h
```
#pragma once

class Figure
{
    public:
        Figure() = default;
        virtual ~Figure() = default;

        // virtual pointer12 calculate_mid() const = 0;
        //double calculate_S() const = 0;

        virtual explicit operator double() const 
        {
            return 0.0;
        };

    protected:
};
```

# functions.h
```
```

# hex.h
```
```

# octo.h
```
```

# tria.h
```
```

# main.cpp
```
```

# tests.cpp
```
```
