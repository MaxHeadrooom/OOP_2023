# Лабораторная 2

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

        //baza

        Eleven operator+(const Eleven& other);
        Eleven operator-(const Eleven& other);
        Eleven& operator=(const Eleven& other);

        //sravnenie

        bool operator>(const Eleven& other);
        bool operator<(const Eleven& other);
        bool operator==(const Eleven& other);

    private:
        ll size;
        unsigned char *num;
        void resize();
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
    num = new unsigned char[0]{};
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

ll Eleven::get_value() {return num[0];}

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

        char op;

        cin >> op;

        bool res;
        switch (op) 
        {
            case '+':
                cout << "Result: " << (num1 + num2).get_stringified() << '\n';
                break;

            case '-':
                cout << "Result: " << (num1 - num2).get_stringified() << '\n';
                break;

            case '>':
                res = num1 > num2;
                cout << "Result: " << res << '\n';
                break;

            case '<':
                res = num1 < num2;
                cout << "Result: " << res << '\n';
                break;

            case '=':
                res = num1 == num2;
                cout << "Result: " << res << '\n';
                break;

            default:
                cout << "No such operation" << '\n';
                break;
        }
    }
    catch(const exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
```
private.cpp
```
#include "eleven.h"

using namespace std;
 
using ll = long long; 

void Eleven::resize()
{
    unsigned char* resized = new unsigned char[size]{};

    for (int i = 0; i < size; i++)
    {
        resized[i] = num[i];
    }

    delete num;
    num = resized;
}
```

bool_op.cpp
```
#include "eleven.h"

using namespace std;

using ll = long long;

bool Eleven::operator>(const Eleven &other)
{
    if (size > other.size)
        return true;

    if (other.size > size)
        return false;

    for (size_t i = size - 1; i < size; i--)
    {
        if (num[i] > other.num[i])
            return true;
        if (other.num[i] > num[i])
            return false;
    }

    return false;
}

bool Eleven::operator<(const Eleven &other)
{
    if (size < other.size)
        return true;

    if (other.size < size)
        return false;

    for (size_t i = size - 1; i < size; i--)
    {
        if (num[i] < other.num[i])
            return true;
        if (other.num[i] < num[i])
            return false;
    }

    return false;
}

bool Eleven::operator==(const Eleven &other)
{
    if (size != other.size)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (num[i] != other.num[i])
            return false;
    }

    return true;
}

```
operations.cpp
```
#include "eleven.h"

using namespace std;

using ll = long long;

Eleven Eleven::operator+(const Eleven &other)
{
    ll maxSize, minSize;

    if (size >= other.size) 
    {
        maxSize = size;
        minSize = other.size;
    } 
    else 
    {
        maxSize = other.size;
        minSize = size;
    }

    Eleven result = Eleven(maxSize);  
    ll transfer = 0, remainder, num1, num2, sum;

    for (int i = 0; i < minSize; i++) 
    {
        if (num[i] == 65)
            num1 = 10;
        else
            num1 = num[i] - 48; // 48 - '0', 49 - '1', 65 - 'A'

        if (other.num[i] == 65)
            num2 = 10;
        else
            num2 = other.num[i] - 48;

        sum = num1 + num2 + transfer;
        transfer = sum / 11;
        remainder = sum % 11;
        if (remainder == 10)
            result.num[i] = 'A';
        else
            result.num[i] = remainder + 48;
    }

    for (int i = minSize; i < maxSize; i++) 
    {
        if (size >= other.size) 
        {
            if (num[i] == 65)
                num1 = 10;
            else
                num1 = num[i] - 48; 
        }
        else
        {
            if (other.num[i] == 65)
                num2 = 10;
            else
                num2 = other.num[i] - 48;
        }

        sum = num1 + transfer;
        transfer = sum / 11;
        remainder = sum % 11;
        if (remainder == 10)
            result.num[i] = 'A';
        else
            result.num[i] = remainder + 48;
    }

    if (transfer != 0) 
    {
        ++result.size;
        result.resize();
        result.num[maxSize] = transfer + 48;
    }

    return result;
}

Eleven Eleven::operator-(const Eleven &other)
{
    if (other.size > size)
        throw invalid_argument("The result of subtraction would be negative");

    Eleven result = Eleven(*this);

    for (size_t i = other.size - 1; i < other.size; i--) 
    {
        if (num[i] == 'A' and other.num[i] != 'A')
        {
            if (other.num[i] != 0)
                result.num[i] = 10 - other.num[i] + 48;
            else
                result.num[i] = num[i];
        }
        else
        {
            ll fl = 0; //tupo, kogda u menya bilo v 1 ife, prosto pereprigival if, hotya doljen bil bit'
            if (other.num[i] == 'A')
                fl++;
            if (num[i] == 'A')
                fl++;
                
            if (fl == 2)
                result.num[i] = 48;
            else
            {
                if (other.num[i] == 'A')
                    result.num[i] = num[i] - 10 + 48;
                else
                    result.num[i] = num[i] - other.num[i] + 48;
            }
        }
        if (result.num[i] < 48) 
        {
            result.num[i] = 'A';

            ll pos = i + 1;

            while (pos != result.size and result.num[pos] == 48) 
            {
                result.num[pos] = 'A';
                pos += 1;
            }

            if (pos == result.size)
                throw invalid_argument("The result of subtraction would be negative");

            --result.num[pos];

            if (pos + 1 == result.size and result.num[pos] == 48)
            {
                --result.size;
                result.resize();
            }
        }
    }

    return result;
}

Eleven& Eleven::operator=(const Eleven &other)
{
    size = other.size;
    num = new unsigned char[size];

    for (int i = 0; i != size; i++)
    {
        num[i] = other.num[i];
    }

    return *this;
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


TEST(test7, sum_normal) 
{
    Eleven num = Eleven("12");
    Eleven num2 = Eleven("12");
    EXPECT_EQ((num + num2).get_stringified(), "24");
}

TEST(test8, sum_normal) 
{
    Eleven num = Eleven("A");
    Eleven num2 = Eleven("A");
    EXPECT_EQ((num + num2).get_stringified(), "19");
}

TEST(test9, sum_normal) 
{
    Eleven num = Eleven("34");
    Eleven num2 = Eleven("0");
    EXPECT_EQ((num + num2).get_stringified(), "34");
}

TEST(test10, sum_normal) 
{
    Eleven num = Eleven("0");
    Eleven num2 = Eleven("A");
    EXPECT_EQ((num + num2).get_stringified(), "A");
}

TEST(test11, sum_normal) 
{
    Eleven num = Eleven("A");
    Eleven num2 = Eleven("A1");
    EXPECT_EQ((num + num2).get_stringified(), "100");
}

TEST(test12, sum_normal) 
{
    Eleven num = Eleven("A111");
    Eleven num2 = Eleven("A999");
    EXPECT_EQ((num + num2).get_stringified(), "19AAA");
}

TEST(test13, sum_normal) 
{
    Eleven num = Eleven("A999");
    Eleven num2 = Eleven("");
    EXPECT_EQ((num + num2).get_stringified(), "A999");
}

// minus

TEST(Operators, minus) 
{
    Eleven num = Eleven("24");
    Eleven num2 = Eleven("12");
    EXPECT_EQ((num - num2).get_stringified(), "12");
}

TEST(Operators2, minus) 
{
    Eleven num = Eleven("12000");
    Eleven num2 = Eleven("1");
    EXPECT_EQ((num - num2).get_stringified(), "11AAA");
}

TEST(Operators3, minus) 
{
    Eleven num = Eleven("12000");
    Eleven num2 = Eleven("");
    EXPECT_EQ((num - num2).get_stringified(), "12000");
}

TEST(Operators4, minus) 
{
    Eleven num = Eleven("12000");
    Eleven num2 = Eleven("0");
    EXPECT_EQ((num - num2).get_stringified(), "12000");
}

TEST(Operators5, minus) 
{
    Eleven num = Eleven("9999");
    Eleven num2 = Eleven("111");
    EXPECT_EQ((num - num2).get_stringified(), "9888");
}

TEST(Operators6, minus) 
{
    Eleven num = Eleven("A");
    Eleven num2 = Eleven("A");
    EXPECT_EQ((num - num2).get_stringified(), "0");
}

TEST(Operators, assignment) 
{
    Eleven num;
    num = Eleven("12");
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Operators, comparison) 
{
    Eleven num = Eleven("12");
    Eleven num2 = Eleven("11");
    EXPECT_TRUE(num > num2);
    EXPECT_FALSE(num < num2);
    EXPECT_TRUE(num2 < num);
    EXPECT_FALSE(num2 > num);
}

TEST(Operators, equality) 
{
    Eleven num = Eleven("12");
    Eleven num2 = num;
    EXPECT_TRUE(num == num2);
    EXPECT_FALSE(num > num);
    EXPECT_FALSE(num > num);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
