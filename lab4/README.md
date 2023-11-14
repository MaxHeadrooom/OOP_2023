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
#pragma once

#include <iostream>
#include <utility>
#include <memory>
#include <cmath>

namespace fig {

template <typename T>
std::pair<double, double> calculate_mid(const T& figure) 
{
    std::pair<double, double> p = {0, 0};

    long long size = 0; 

    for (std::pair<double, double> point : figure.points) 
    {
        p.first += point.first;
        p.second += point.second;
        size++;
    }

    p.first /= size;
    p.second /= size;
    return p;
}

template <typename T> 
double calculate_S(const T& figura) 
{
    double side = std::sqrt(std::pow(figura.points[0].first - figura.points[1].first, 2)
    + std::pow(figura.points[0].second - figura.points[1].second, 2));
    double perimeter = figura.count * side;
    double angle = 360 / figura.count * 0.5;
    double apotheme = side / (2 * std::tan(std::acos(-1) / figura.count));
    return perimeter * apotheme / 2;
}

} //namespace fig
```

# hex.h
```
#pragma once

#include <iostream>
#include <vector>
#include <utility> // для pair
#include <memory>

using ll = long long;

template <typename T>
class Hexagon : public Figure
{
    using typ = std::pair<T, T>[6];
    public:
        typ points;
        ll count = 6;

        Hexagon() = default;
        Hexagon(typ& v)
        {
            for (int i = 0; i < 6; i++)
                points[i] = v[i];
        }
        ~Hexagon() = default;

        Hexagon<T>& operator=(const Hexagon<T>& other)
        {
            points = other.points;

            return *this;
        }

        Hexagon<T>& operator=(Hexagon<T>&& other)
        {
            points = std::move(other.points);

            return *this;
        }

        operator double() const 
        {
            return (double)fig::calculate_S(*this);
        }   

        friend std::istream& operator>>(std::istream& chten, Hexagon<T>& hex)
        {
            for (int i = 0; i < 6; i++)
            {
                chten >> hex.points[i].first >> hex.points[i].second;
            }
            return chten;
        }

        friend std::ostream& operator<<(std::ostream& vivod, Hexagon<T>& hex)
        {
            for (int i = 0; i < 6; i++)
            {
                vivod << hex.points[i].first << hex.points[i].second;
            }
            return vivod;
        }
};

template <typename T>
bool operator==(const Hexagon<T>& right, const Hexagon<T>& left)
{
    return right.points[0] == left.points[0] and right.points[1] == left.points[1] and
    right.points[2] == left.points[2] and right.points[3] == left.points[3] and
    right.points[4] == left.points[4] and right.points[5] == left.points[5];
}
```

# octo.h
```
#pragma once

#include <iostream>
#include <vector>
#include <utility> // для pair
#include <memory>

using ll = long long;

template <typename T>
class Octagon : public Figure
{
    using typ = std::pair<T, T>[8];
    public:
        typ points;
        ll count = 8;

        Octagon() = default;
        Octagon(typ& v)
        {
            for (int i = 0; i < 8; i++)
                points[i] = v[i];
        }
        ~Octagon() = default;

        Octagon<T>& operator=(const Octagon<T>& other)
        {
            points = other.points;

            return*this;
        }

        Octagon<T>& operator=(Octagon<T>&& other)
        {
            points = std::move(other.points);

            return*this;
        }

        operator double() const 
        {
            return (double)fig::calculate_S(*this);
        }   

        friend std::istream& operator>>(std::istream& chten, Octagon<T>& tria)
        {
            for (int i = 0; i < 8; i++)
            {
                chten >> tria.points[i].first >> tria.points[i].second;
            }
            return chten;
        }

        friend std::ostream& operator<<(std::ostream& vivod, Octagon<T>& tria)
        {
            for (int i = 0; i < 8; i++)
            {
                vivod << tria.points[i].first << tria.points[i].second;
            }
            return vivod;
        }
};

template <typename T>
bool operator==(const Octagon<T>& right, const Octagon<T>& left)
{
    return right.points[0] == left.points[0] and right.points[1] == left.points[1] and
    right.points[2] == left.points[2] and right.points[3] == left.points[3] and
    right.points[4] == left.points[4] and right.points[5] == left.points[5] and
    right.points[6] == left.points[6] and right.points[7] == left.points[7];
}
```

# tria.h
```
#pragma once

#include <iostream>
#include <vector>
#include <utility> // для pair
#include <memory>

using ll = long long;

template <typename T>
class Triangle : public Figure
{
    using typ = std::pair<T, T>[3];
    public:
        typ points;
        ll count = 3;

        Triangle() = default;
        Triangle(typ& v)
        {
            for (int i = 0; i < 3; i++)
                points[i] = v[i];
        }
        ~Triangle() = default;

        Triangle<T>& operator=(const Triangle<T>& other)
        {
            points = other.points;

            return*this;
        }

        Triangle<T>& operator=(Triangle<T>&& other)
        {
            points = std::move(other.points);

            return*this;
        }

        operator double() const 
        {
            return (double)fig::calculate_S(*this);
        }   

        friend std::istream& operator>>(std::istream& chten, Triangle<T>& tria)
        {
            for (int i = 0; i < 3; i++)
            {
                chten >> tria.points[i].first >> tria.points[i].second;
            }
            return chten;
        }

        friend std::ostream& operator<<(std::ostream& vivod, Triangle<T>& tria)
        {
            for (int i = 0; i < 3; i++)
            {
                vivod << tria.points[i].first << tria.points[i].second;
            }
            return vivod;
        }
};

template <typename T>
bool operator==(const Triangle<T>& right, const Triangle<T>& left)
{
    return right.points[0] == left.points[0] and right.points[1] == left.points[1] and
    right.points[2] == left.points[2];
}
```

# main.cpp
```
#include "array.h"
#include "figure.h"
#include "functions.h"
#include "hex.h"
#include "octo.h"
#include "tria.h"

#include <iostream>
#include <memory>

using ll = long long;

int main()
{
}
```

# tests.cpp
```
#include "array.h"
#include "figure.h"
#include "functions.h"
#include "gtest/gtest.h"
#include "hex.h"
#include "octo.h"
#include "tria.h"

// Hexagon double tests

std::pair<double, double> v1[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::pair<double, double> v2[] = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon_double, empty_constructor) 
{
    Hexagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::calculate_mid(h);
    double surf = fig::calculate_S(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Hexagon_double, vector_constructor) 
{
    Hexagon<double> h(v1);
    std::pair<double, double> center{3.5, 3.5};
    std::pair<double, double> res = fig::calculate_mid(h);
    EXPECT_EQ(res, center);
}

std::pair<double, double> v3[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::pair<double, double> v4[] = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon_double, empty_constructor) 
{
    Octagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::calculate_mid(h);
    double surf = fig::calculate_S(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Octagon_double, vector_constructor) 
{
    Octagon<double> h(v3);
    std::pair<double, double> center{4.5, 4.5};
    std::pair<double, double> res = fig::calculate_mid(h);
    EXPECT_EQ(res, center);
}

std::pair<double, double> v5[] = {{1, 1}, {2, 2}, {3, 3}};
std::pair<double, double> v6[] = {{4, 4}, {5, 5}, {6, 6}};

TEST(Triangle_double, empty_constructor) 
{
    Octagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::calculate_mid(h);
    double surf = fig::calculate_S(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Triangle_double, vector_constructor) 
{
    Triangle<double> h(v5);
    std::pair<double, double> center{2, 2};
    std::pair<double, double> res = fig::calculate_mid(h);
    EXPECT_EQ(res, center);
}

std::pair<double, double> v[] = {{10, 0}, {0, 0}, {5, 5*sqrt(3)}};

ll epsilon = 1e9;

TEST(Triangle_S, vector_constructor) 
{
    Triangle<double> h(v);
    double res = fig::calculate_S(h);
    EXPECT_LT(abs(res - 25*sqrt(3)), epsilon);
}

std::pair<double, double> gicha[] = {{1, 1}, {2, 2}, {3, 3}};
std::pair<double, double> gacha[] = {{1, 1}, {2, 2}, {3, 3}};

TEST(Octago, equal) 
{
    Triangle<double> h(gicha);
    Triangle<double> h1(gacha);
    EXPECT_EQ(h, h1);
}
```
