# Лабораторная 3

# Эсмедляев Федор 23 вариант

Разработать программу на языке C++ согласно варианту задания. Программа на C++ должна собираться с помощью системы сборки CMake. Программа должна получать данные из стандартного ввода (std::cin) и выводить данные в стандартный вывод (std::cout).
Необходимо зарегистрироваться на GitHub и создать репозитарий для задания лабораторных работ.
Преподавателю необходимо предъявить ссылку на публичный репозиторий на Github. Необходимо реализовать функцию согласно варианту задания. Функция должна быть помещена в отдельный файл.

Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения.
Все классы должны поддерживать набор общих методов:
1. Вычисление геометрического центра фигуры вращения;
2. Вывод в стандартный поток вывода std::cout координат вершин фигуры через перегрузку оператора << для std::ostream;
3. Чтение из стандартного потока данных фигур через перегрузку оператора >> для std::istream
4. Вычисление площади фигуры через перегрузку оператора приведения к типу double;


Создать программу, которая позволяет:
- Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.
- Сохранять созданные фигуры в динамический массив (по аналогии с предыдущей лабораторной работой Array) указатели на фигуру (Figure*)
- Фигуры должны иметь переопределенные операции копирования (=), перемещения (=) и сравнения (==)
- Вызывать для всего массива общие функции (1-3 см. выше).Т.е. распечатывать для каждой фигуры в массиве геометрический центр и площадь.
- Необходимо уметь вычислять общую площадь фигур в массиве. •Удалять из массива фигуру по индексу;

Вариант 23, фигуры: 6-угольник, 8-угольник, Треугольник

## Программы

### main.cpp
```
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
```
#main.cpp
```
#include <bits/stdc++.h>
#include "figure.h"

using namespace std;

int main()
{
    try
    {
    }
    catch(const exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
```
#point.h
```
#include <bits/stdc++.h>
#pragma once

using namespace std;

using ll = long long;

class pointer12 
{
    private:

    public:
        double pos_x = 0, pos_y = 0;
        pointer12() = default;
        
        pointer12(double, double);
        pointer12(const initializer_list<double>&);
        pointer12(const pointer12 &other);

        const double get_x();
        const double get_y();

        bool operator==(const pointer12& other);

        friend istream& operator>>(istream&, pointer12&);
        friend ostream& operator<<(ostream&, const pointer12&);

        virtual ~pointer12() = default;
};
```
#point.cpp
```
#pragma once

#include "point.h"
#include <bits/stdc++.h>

using namespace std;

pointer12::pointer12(double x, double y)
{
    this->pos_x = x;
    this->pos_y = y;
}

pointer12::pointer12(const initializer_list<double>& coord) 
{
    if (coord.size() != 2) 
    {
        throw invalid_argument("Only 2 arguments");
    }

    this->pos_x = *(coord.begin());
    this->pos_y = *(coord.begin() + 1);
}

pointer12::pointer12(const pointer12& other)
{
    this->pos_x = other.pos_x;
    this->pos_y = other.pos_y;
}

const double pointer12::get_x()
{
    return pos_x;
}

const double pointer12::get_y()
{
    return pos_y;
}

bool pointer12::operator==(const pointer12& other)
{
    return (this->pos_x == other.pos_x and this->pos_y == other.pos_y);
}

istream& operator>>(istream& chten, pointer12& point)
{
    chten >> point.pos_x >> point.pos_y;
    return chten;
}

ostream& operator<<(ostream& vivod, const pointer12& point)
{
    vivod << point.pos_x << " " << point.pos_y;
    return vivod;
}
```
#figure.h
```
#include <bits/stdc++.h>
#include "point.h"
#pragma once

using namespace std;

using ll = long long;

class Figure
{
    public:
        Figure() = default;
        virtual ~Figure() = default;

        virtual pointer12 calculate_mid() const = 0;
        virtual double calculate_s() const = 0;
        //virtual double calculate_all_s() const = 0;

    protected:

};
```
#array.h
```
#include <bits/stdc++.h>
#include "figure.h"

using namespace std;

using ll = long long;

class arrayy
{
    private:
        Figure** figuri; // s * ne rabotaet **
        ll size;

    public:
        arrayy();
        arrayy(ll size);
        virtual ~arrayy() = default;

        Figure* operator[](ll pos); // obrasch k elem

        void push_back(ll pos, Figure* fig);
        void pop(ll pos);
        double calc_all_s();
};
```
#array.cpp
```
#include <bits/stdc++.h>
#include "array.h"
#include "figure.h"

using namespace std;

using ll = long long;

arrayy::arrayy()
{
    this->size = 16;
    this->figuri = new Figure*[size];

    for (int i = 0; i < 16; i++)
    {
        figuri[i] = nullptr;
    }
}

arrayy::arrayy(ll sizee)
{
    this->size = sizee;
    this->figuri = new Figure*[sizee];

    for (int i = 0; i < sizee; i++)
    {
        figuri[i] = nullptr;
    }
}

Figure* arrayy::operator[](ll pos)
{
    if (pos >= size)
        throw   invalid_argument("Out of range");

    return figuri[pos];
}

void arrayy::push_back(ll pos, Figure* f)
{
    if (pos > size)
        throw invalid_argument("Out of range when push_back");

    if (figuri[pos] == nullptr)
        figuri[pos] = f;
    else
        throw runtime_error("I can't push because place is alredy exist");
}

void arrayy::pop(ll pos)
{
    if (pos < 0 or pos > size)
        throw invalid_argument("Out of range when pop");
    
    if (figuri[pos] != nullptr)
    {
        delete figuri[pos];
        figuri[pos] = nullptr;
    }
}

double arrayy::calc_all_s()
{
    double s = 0.0;

    for (int i = 0; i < size; i++)
    {
        if (figuri[i] != nullptr)
        {
            s += figuri[i]->calculate_s();
        }
    }
}
```
#triangle.h
```
#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class triangle : public Figure
{
    //vtoraya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer12 left_dot;
        pointer12 mid_dot;
        pointer12 right_dot;

        double storona;

    public:
        triangle() = default;

        triangle(const pointer12&, const pointer12&, const pointer12&);
        
        triangle(const triangle&) noexcept;
        triangle(triangle&&) noexcept;

        triangle& operator=(const triangle&) noexcept;
        triangle& operator=(triangle&&) noexcept;

        bool operator==(const triangle&);

        virtual double calculate_s() const;
        virtual pointer12 calculate_mid() const;

        friend istream& operator>>(istream&, triangle&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const triangle& sixxx_ugl);

        virtual ~triangle() = default; 
};
```
#triangle.cpp
```
#include "triangle.h"
#include <bits/stdc++.h>

using namespace std;

triangle::triangle(const pointer12& left_dot, const pointer12& mid_dot, const pointer12& right_dot)
{
    this->storona = sqrt((left_dot.pos_x - right_dot.pos_x)*(left_dot.pos_x - right_dot.pos_x) + 
    (left_dot.pos_y - right_dot.pos_y)*(left_dot.pos_y - right_dot.pos_y));

    if (storona <= 0)
        throw invalid_argument("It's not a triangle");
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}

triangle::triangle(const triangle& other) noexcept
{
    //prisvaivanie iz other v tekuschee - this
    this->left_dot = other.left_dot;
    this->mid_dot = other.mid_dot;
    this->right_dot = other.right_dot;
}

triangle::triangle(triangle&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_dot = move(other.left_dot);
    this->mid_dot = move(other.mid_dot);
    this->right_dot = move(other.right_dot);
}

triangle& triangle::operator=(const triangle& other) noexcept
{
    //this - tekuschiy ob'ect
    if (this == &other)//oznachaet cto uje est, t.e. prisvaevaet sam sebe, poetomu uje est'
        return *this;

    //prisvaivanie iz other v tekuschee - this
    this->left_dot = other.left_dot;
    this->mid_dot = other.mid_dot;
    this->right_dot = other.right_dot;

    return *this;
}

triangle& triangle::operator=(triangle&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_dot = move(other.left_dot);
    this->mid_dot = move(other.mid_dot);
    this->right_dot = move(other.right_dot);

    return *this;
}

bool triangle::operator==(const triangle& other)
{
    if (this->left_dot == other.left_dot and this->mid_dot == other.mid_dot and
    this->right_dot == other.right_dot)
        return true;
    return false;
}

double triangle::calculate_s() const
{
    return (storona*storona*sqrt(3)/4);
}

pointer12 triangle::calculate_mid() const
{
    pointer12 geom_mid((left_dot.pos_x + mid_dot.pos_x + right_dot.pos_x)/3,
    (left_dot.pos_y + mid_dot.pos_y + right_dot.pos_y)/3);

    return geom_mid;
}

istream& operator>>(istream& chten, triangle& tria)
{
    pointer12 left_dot, mid_dot, right_dot;
    chten >> left_dot >> mid_dot >> right_dot;

    tria = triangle(left_dot, mid_dot, right_dot);

    return chten;
}

ostream& operator<<(ostream& vivod, const triangle& tria)
{
    vivod << tria.left_dot << " " <<  tria.mid_dot << " " << tria.right_dot;

    return vivod;
}
```
#six_ugl.h
```
#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class six_ugl : public Figure
{
    //vtoraya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer12 left_mid_dot;
        pointer12 left_down_dot;
        pointer12 left_up_dot;
        pointer12 right_up_dot;
        pointer12 right_mid_dot;
        pointer12 right_down_dot;

        double storona;
        
    public:
        six_ugl() = default;

        six_ugl(const pointer12&, const pointer12&, const pointer12&, const pointer12&,
        const pointer12&, const pointer12&);
        
        six_ugl(const six_ugl&) noexcept;
        six_ugl(six_ugl&&) noexcept;

        six_ugl& operator=(const six_ugl&) noexcept;
        six_ugl& operator=(six_ugl&&) noexcept;

        bool operator==(const six_ugl&);

        virtual double calculate_s() const;
        virtual pointer12 calculate_mid() const;

        friend istream& operator>>(istream&, six_ugl&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const six_ugl& sixxx_ugl);

        virtual ~six_ugl() = default; 
};
```
#six_ugl.cpp
```
#include "six_ugl.h"
#include <bits/stdc++.h>

using namespace std;

six_ugl::six_ugl(const pointer12& left_down_dot, const pointer12& left_mid_dot, const pointer12& left_up_dot,
const pointer12& right_up_dot, const pointer12& right_mid_dot, const pointer12& right_down_dot)
{
    this->storona = sqrt((left_down_dot.pos_x - left_mid_dot.pos_x)*(left_down_dot.pos_x - left_mid_dot.pos_x)
    + (left_down_dot.pos_y - left_mid_dot.pos_y) * (left_down_dot.pos_y - left_mid_dot.pos_y));

    if (storona <= 0)
        throw invalid_argument("It's not a six_ugl");
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}

six_ugl::six_ugl(const six_ugl& other) noexcept
{
    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_dot = other.left_mid_dot;
    this->left_up_dot = other.left_up_dot;
    this->right_down_dot = other.right_down_dot;
    this->right_mid_dot = other.right_mid_dot;
    this->right_up_dot = other.right_up_dot;
}

six_ugl::six_ugl(six_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_dot = move(other.left_mid_dot);
    this->left_up_dot = move(other.left_up_dot);
    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_dot = move(other.right_mid_dot);
    this->right_up_dot = move(other.right_up_dot);
}

six_ugl& six_ugl::operator=(const six_ugl& other) noexcept
{
    //this - tekuschiy ob'ect
    if (this == &other)//oznachaet cto uje est, t.e. prisvaevaet sam sebe, poetomu uje est'
        return *this;

    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_dot = other.left_mid_dot;
    this->left_up_dot = other.left_up_dot;
    this->right_down_dot = other.right_down_dot;
    this->right_mid_dot = other.right_mid_dot;
    this->right_up_dot = other.right_up_dot;

    return *this;
}

six_ugl& six_ugl::operator=(six_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_dot = move(other.left_mid_dot);
    this->left_up_dot = move(other.left_up_dot);
    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_dot = move(other.right_mid_dot);
    this->right_up_dot = move(other.right_up_dot);

    return *this;
}

bool six_ugl::operator==(const six_ugl& other)
{
    if (this->left_down_dot == other.left_down_dot and this->left_mid_dot == other.left_mid_dot and
    this->left_up_dot == other.left_up_dot and this->right_up_dot == other.right_up_dot and
    this->right_mid_dot == other.right_mid_dot and this->right_down_dot == other.right_down_dot)
        return true;
    return false;
}

double six_ugl::calculate_s() const
{
    return 3*sqrt(3)*storona*storona/2;
}

pointer12 six_ugl::calculate_mid() const
{
    pointer12 geom_mid((left_up_dot.pos_x + right_up_dot.pos_x +
    left_mid_dot.pos_x + right_mid_dot.pos_x + left_down_dot.pos_x + right_down_dot.pos_x)/6 ,
    (left_up_dot.pos_y + right_up_dot.pos_y + left_mid_dot.pos_y + right_mid_dot.pos_y +
    left_down_dot.pos_y + right_down_dot.pos_y)/6);

    return geom_mid;
}

istream& operator>>(istream& chten, six_ugl& sixxx_ugl)
{
    chten >> sixxx_ugl.left_down_dot >> sixxx_ugl.left_mid_dot >> sixxx_ugl.left_up_dot >>
    sixxx_ugl.right_down_dot >> sixxx_ugl.right_mid_dot >> sixxx_ugl.right_up_dot;

    return chten;
}

ostream& operator<<(ostream& vivod, const six_ugl& sixxx_ugl)
{
    vivod << sixxx_ugl.left_down_dot << " " << sixxx_ugl.left_mid_dot << " " <<sixxx_ugl.left_up_dot <<
    " " << sixxx_ugl.right_down_dot << " " << sixxx_ugl.right_mid_dot << " " << sixxx_ugl.right_up_dot; 

    return vivod;
}
```
#eight_ugl.h
```

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class eight_ugl : public Figure
{
    //tret'ya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer12 left_down_dot;
        pointer12 left_mid_down_dot;
        pointer12 left_mid_up_dot;
        pointer12 left_up_dot;
        pointer12 right_up_dot;
        pointer12 right_mid_down_dot;
        pointer12 right_mid_up_dot;
        pointer12 right_down_dot;

        double storona;
        
    public:
        eight_ugl() = default;

        eight_ugl(const pointer12&, const pointer12&, const pointer12&, const pointer12&, const pointer12&,
        const pointer12&, const pointer12&, const pointer12&);
        
        eight_ugl(const eight_ugl&) noexcept;
        eight_ugl(eight_ugl&&) noexcept;

        eight_ugl& operator=(const eight_ugl&) noexcept;
        eight_ugl& operator=(eight_ugl&&) noexcept;

        bool operator==(const eight_ugl&);

        virtual double calculate_s() const;
        virtual pointer12 calculate_mid() const;

        friend istream& operator>>(istream&, eight_ugl&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const eight_ugl& eighttt_ugl);

        virtual ~eight_ugl() = default; 
};
```
#eight_ugl.cpp
```
#include "eight_ugl.h"
#include <bits/stdc++.h>

using namespace std;

eight_ugl::eight_ugl(const pointer12& left_down_dot, const pointer12& left_mid_down_dot, const pointer12&
left_mid_up_dot, const pointer12& left_up_dot, const pointer12& right_up_dot, const pointer12& right_mid_up_dot,
const pointer12& right_mid_down_dot, const pointer12& right_down_dot)
{
    this->storona = sqrt((left_up_dot.pos_x - right_up_dot.pos_x)*(left_up_dot.pos_x - right_up_dot.pos_x)
    + (left_up_dot.pos_y - right_up_dot.pos_y) * (left_up_dot.pos_y - right_up_dot.pos_y));

    if (storona <= 0)
        throw invalid_argument("It's not a eight_ugl");
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}

eight_ugl::eight_ugl(const eight_ugl& other) noexcept
{
    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_down_dot = other.left_mid_down_dot;
    this->left_mid_up_dot = other.left_mid_up_dot;
    this->left_up_dot = other.left_up_dot;

    this->right_down_dot = other.right_down_dot;
    this->right_mid_down_dot = other.right_mid_down_dot;
    this->right_mid_up_dot = other.right_mid_up_dot;
    this->right_up_dot = other.right_up_dot;
}

eight_ugl::eight_ugl(eight_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_down_dot = move(other.left_mid_down_dot);
    this->left_mid_up_dot = move(other.left_mid_up_dot);
    this->left_up_dot = move(other.left_up_dot);

    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_down_dot = move(other.right_mid_down_dot);
    this->right_mid_up_dot = move(other.right_mid_up_dot);
    this->right_up_dot = move(other.right_up_dot);
}

eight_ugl& eight_ugl::operator=(const eight_ugl& other) noexcept
{
    //this - tekuschiy ob'ect
    if (this == &other)//oznachaet cto uje est, t.e. prisvaevaet sam sebe, poetomu uje est'
        return *this;

    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_down_dot = other.left_mid_down_dot;
    this->left_mid_up_dot = other.left_mid_up_dot;
    this->left_up_dot = other.left_up_dot;

    this->right_down_dot = other.right_down_dot;
    this->right_mid_down_dot = other.right_mid_down_dot;
    this->right_mid_up_dot = other.right_mid_up_dot;
    this->right_up_dot = other.right_up_dot;

    return *this;
}

eight_ugl& eight_ugl::operator=(eight_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_down_dot = move(other.left_mid_down_dot);
    this->left_mid_up_dot = move(other.left_mid_up_dot);
    this->left_up_dot = move(other.left_up_dot);

    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_down_dot = move(other.right_mid_down_dot);
    this->right_mid_up_dot = move(other.right_mid_up_dot);
    this->right_up_dot = move(other.right_up_dot);

    return *this;
}

bool eight_ugl::operator==(const eight_ugl& other)
{
    if (this->left_down_dot == other.left_down_dot and this->left_mid_down_dot == other.left_mid_down_dot
    and this->left_mid_up_dot == other.left_mid_up_dot and this->left_up_dot == other.left_up_dot and
    this->right_down_dot == other.right_down_dot and this->right_mid_down_dot == other.right_mid_down_dot
    and this->right_mid_up_dot == other.right_mid_up_dot and this->right_up_dot == other.right_up_dot)
        return true;
    return false;
}

double eight_ugl::calculate_s() const
{
    return (2*storona*storona*(sqrt(2) + 1));
}

pointer12 eight_ugl::calculate_mid() const
{
    pointer12 geom_mid((left_down_dot.pos_x + left_mid_down_dot.pos_x + left_mid_up_dot.pos_x + 
    left_up_dot.pos_x + right_down_dot.pos_x + right_mid_down_dot.pos_x + right_mid_up_dot.pos_x + 
    right_up_dot.pos_x)/8,(left_down_dot.pos_y + left_mid_down_dot.pos_y + left_mid_up_dot.pos_y + 
    left_up_dot.pos_y + right_down_dot.pos_y + right_mid_down_dot.pos_y + right_mid_up_dot.pos_y + 
    right_up_dot.pos_y)/8);

    return geom_mid;
}

istream& operator>>(istream& chten, eight_ugl& eighttt_ugl)
{
    chten >> eighttt_ugl.left_down_dot >> eighttt_ugl.left_mid_down_dot >> eighttt_ugl.left_mid_up_dot >>
    eighttt_ugl.left_up_dot >> eighttt_ugl.right_up_dot >> eighttt_ugl.right_mid_up_dot >>
    eighttt_ugl.right_mid_down_dot >> eighttt_ugl.right_down_dot;

    return chten;
}

ostream& operator<<(ostream& vivod, const eight_ugl& eighttt_ugl)
{
    vivod << eighttt_ugl.left_down_dot << " " << eighttt_ugl.left_mid_down_dot << " " << 
    eighttt_ugl.left_mid_up_dot << " " << eighttt_ugl.left_up_dot << " " <<
    eighttt_ugl.right_up_dot << " " << eighttt_ugl.right_mid_up_dot << " " <<
    eighttt_ugl.right_mid_down_dot << " " << eighttt_ugl.right_down_dot;

    return vivod;
}
```
#tests.cpp
```
#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "six_ugl.h"
#include "eight_ugl.h"
#include "triangle.h"
#include "array.h"

using namespace std;

TEST(calc_s, test_1) 
{
    triangle test1(pointer12(10, 0), pointer12(0, 0), pointer12(5, 5*sqrt(3)));

    EXPECT_DOUBLE_EQ(test1.calculate_s(), 25*sqrt(3));
}

/*TEST(calc_s, test_2) 
{
    triangle test2(pointer12(0, 0), pointer12(0, 0), pointer12(0, 0));

    EXPECT_ANY_THROW(test2.calculate_s()); 
}*/

TEST(calc_s, test_3) 
{
    six_ugl test3 (pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6));

    EXPECT_DOUBLE_EQ(test3.calculate_s(), 3*sqrt(3));
}

TEST(calc_s, test_4) 
{
    eight_ugl test4 (pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6), pointer12(7, 7), pointer12(8, 8));

    EXPECT_DOUBLE_EQ(test4.calculate_s(), 4*sqrt(2) + 4);
}

TEST(pereg, test_5)
{
    triangle test1(pointer12(10, 0), pointer12(0, 0), pointer12(5, 5*sqrt(3)));
    triangle test2(pointer12(10, 0), pointer12(0, 0), pointer12(5, 5*sqrt(3)));

    EXPECT_TRUE(test1 == test2);
}

TEST(pereg, test_6)
{
    six_ugl test1(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6));
    six_ugl test2(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6));

    EXPECT_TRUE(test1 == test2);
}

TEST(pereg, test_7)
{
    eight_ugl test1(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6), pointer12(7, 7), pointer12(8, 8));
    eight_ugl test2(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6), pointer12(7, 7), pointer12(8, 8));

    EXPECT_TRUE(test1 == test2);
}

TEST(arra, push) 
{
    arrayy a(10);
    triangle* p = new triangle();
    a.push_back(1, p);
    EXPECT_EQ(a[1], p);
}

TEST(arra, delete_element) 
{
    arrayy a(10);
    triangle* p = new triangle();
    a.push_back(1, p);
    EXPECT_EQ(a[1], p);
    a.pop(1);
    EXPECT_EQ(a[1], nullptr);
}

ll epsilon = 1e9;

TEST(Array, sum_s) 
{
    arrayy a(10);
    triangle* p1 = new triangle();
    triangle* p2 = new triangle();
    a.push_back(0, p1);
    a.push_back(1, p2);
    EXPECT_LT(abs(a.calc_all_s() - 0.0), epsilon);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
