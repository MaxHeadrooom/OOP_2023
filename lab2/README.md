# Лабораторная 2(на 04.10.2023 без реализации перегрузки оператора, постараюсь потом сделать, просто никогда не делал с объектами, надо будет попробовать)   

# Эсмедляев Федор

вариант:
Создать класс Eleven для работы с беззнаковыми целыми одиннадцатиричными числами, используя для представления числа массив из элементов типа unsigned char, каждый из которых является одиннадцатиричными
цифрой. Младшая цифра имеет меньший индекс (единицы – в нулевом элементе массива).

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
Eleven.h
```
#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

class Eleven
{
public:
        Eleven();
        Eleven(const ll &n, unsigned char t = 0);
        Eleven(const initializer_list<unsigned char> &t);
        Eleven(const string &t);
        Eleven(const Eleven &other);
        Eleven(Eleven &&other) noexcept;
        virtual ~Eleven() noexcept;

        ll get_value();
        string get_stringified();
        ll get_size();

    private:
        ll size;
        unsigned char *num;
};
```
Eleven_constr.cpp
```
#include "eleven.h"
#include <bits/stdc++.h>

using namespace std;

Eleven::Eleven()//baza
{
    size = 0;
    num = new unsigned char[0];
}

Eleven::Eleven(const ll &n, unsigned char t)//zapolnenie n elmentov znach t
{
    if (t != 65)//bukva A v ASCII
    {
        if (t < 48 and t > 58)
        {
            cout << "gg, symbol just chilling, but not in 11 system";//mojno bilo cherez throw ili try cathc
            exit(0);
        }
    }

    size = n;
    num = new unsigned char[n];

    for (int i = 0; i < n; i++)
    {
        num[i] = t;
    }
}

Eleven::Eleven(const initializer_list<unsigned char> &t)
{
    size = t.size();
    num = new unsigned char[size];

    ll pos = size;

   for (const unsigned char &gicha : t) //pitalsya cherez t[i] ili cherez *(t[i]) ili cherez &(t)
   {
        if (gicha != 65)//bukva A v ASCII
        {
            if (gicha < 48 and gicha > 58)
            {
                cout << "gg, symbol just chilling, but not in 11 system";//mojno bilo cherez throw ili try cathc
                exit(0);
            }
        }
        num[pos - 1] = gicha;
        pos--;
   }
}

Eleven::Eleven(const string &t)
{
    size = t.size();
    num = new unsigned char[size];

    ll pos = size;

   for (const unsigned char &gicha : t) //pitalsya cherez t[i] ili cherez *(t[i]) ili cherez &(t)
   {
        if (gicha != 65)//bukva A v ASCII
        {
            if (gicha < 48 and gicha > 58)
            {
                cout << "gg, symbol just chilling, but not in 11 system";//mojno bilo cherez throw ili try cathc
                exit(0);
            }
        }
        num[pos - 1] = gicha;
        pos--;
   }
}

Eleven::Eleven(const Eleven &other)
{
    size  = other.size;
    num = new unsigned char [size];

    for (int i = 0; i < size; i++)
    {
        num[i] = other.num[i];
    }
}

Eleven::Eleven(Eleven &&other) noexcept
{
    size  = other.size;
    num = new unsigned char [size];

    for (int i = 0; i < size; i++)
    {
        num[i] = other.num[i];
    }
    delete other.num;
    other.size = 0;
}

Eleven::~Eleven() noexcept //prosto udalenie
{
    size = 0;
    delete num;
}
```
Eleven_get.cpp
```
#include "eleven.h"

using namespace std;

ll Eleven::get_value() {return size;}

string Eleven::get_stringified() 
{
    string gicha = "";

    for (int i = 0; i < size; i++) 
    {
        gicha += num[size - i - 1];
    }

    return gicha;
}

ll Eleven::get_size() {return size;}
```
main.cpp
```
#include <bits/stdc++.h>
#include "eleven.h"

using namespace std;

int main()
{
    try
    {
        string s1, s2;

        cin >> s1 >> s2;

        Eleven num1 = Eleven(s1);
        Eleven num2 = Eleven(s2);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
```
tests.cpp
```
#include <gtest/gtest.h>
#include "eleven.h"

using namespace std;

TEST(Constructors, gicha) 
{
    Eleven num = Eleven();
    EXPECT_EQ(num.get_size(), 0);
    EXPECT_EQ(num.get_stringified(), "\0");
}

TEST(Constructors1, gacha) 
{
    Eleven num = Eleven(3, '1');
    EXPECT_EQ(num.get_size(), 3);
    EXPECT_EQ(num.get_stringified(), "111");
}

TEST(Constructors2, initializer_list_filled) 
{
    Eleven num = Eleven({'1', '2'});
    EXPECT_EQ(num.get_size(), 2);
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Constructors3, initializer_list_filled) 
{
    Eleven num = Eleven({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A'});
    EXPECT_EQ(num.get_size(), 11);
    EXPECT_EQ(num.get_stringified(), "0123456789A");
}

TEST(Constructors4, initializer_list_empty) 
{
    Eleven num = Eleven({});
    EXPECT_EQ(num.get_size(), 0);
    EXPECT_EQ(num.get_stringified(), "");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
