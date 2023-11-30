
# Лабораторная работа 5. Итераторы и аллокаторы

## Автор: Эсмедляев Федор, группа М8О-212Б-22
1. Аллокатор
- a. Реализовать свой аллокатор памяти. Проверить что он корректно работает для контейнера std::map.
- b. Аллокатор должен параметризоваться количеством выделяемых за раз элементов.
- c. Освобождение конкретного элемента не предполагается - аллокатор должен освобождать всю память самостоятельно.
2. Контейнер
- a. Реализовать свой контейнер (согласно варианта задания), который по аналогии с контейнерами stl, параметрезуя аллокатором.
3. Итератор
- a. Реализовать итераторы (обычный и const)
- b. Итератор должен соответствовать std::forward_iterator_tag

Прикладной код должен содержать следующие вызовы:
- создание экземпляра std::map с созданным аллокатором
- заполнение 10 элементами, где ключ — это число от 0 до 9, а значение - факториал ключа
- вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
- создание экземпляра своего контейнера для хранения int с собственным vаллокатором – заполнение контейнера и печать его элементов

Вариант 3: Контейнер: Однонаправленный список, Аллокатор: std::vector

## Программы

## CMakeLists.txt
```
cmake_minimum_required(VERSION 3.10)

project(oop_mai_5)

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

## allocator.h
```
#pragma once
#include <memory>
#include <vector>

template <class T>
class Allocator 
{
public:
    static constexpr int size = 100;
    std::vector<T> data;
    int ost;

    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = int;

    Allocator() 
    {
        data.resize(size);
        ost = size;
    }

    ~Allocator() = default;

    pointer allocate(int n) 
    {
        if (n > ost) 
        {
            throw std::bad_alloc();
        }

        ost -= n;

        return &data[ost];
    }

    void deallocate(pointer p, int n)
    {
        ost += n;
    }

    template <class... Args>
    void construct(pointer p, Args&&... args) 
    {
        new (p) T(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        std::destroy_at(p); // аналогично p -> ~T(), но современный
    }

    template <class U>
    struct rebind 
    {
        using other = Allocator<U>;
    };
};

template <class T, class U>
constexpr bool operator==(const Allocator<T>& lhs, const Allocator<U>& rhs) 
{
    return true;
}

template <class T, class U>
constexpr bool operator!=(const Allocator<T>& lhs, const Allocator<U>& rhs)
{
    return false;
}
```

# list.h
```
#include <memory>

template <class T, class Alloc = std::allocator<T>>
class List
{
    private:
        struct Node
        {
            T data;
            Node* next;

            explicit Node(const T& value) : data(value), next(nullptr) {}
            // чтобы не было ситуаций когда Node<int> = 42; мне надо только Node<int> node(42);
        };

    using Alloc_traits = std::allocator_traits<Alloc>;
    using NodeAllocator = typename Alloc_traits::rebind_alloc<Node>;
    using Alloc_Item_traits = std::allocator_traits<NodeAllocator>;

    Node* head;
    int size;
    NodeAllocator allocator;

    class Iterator
    {
        private:
            friend List;
            Node* current;

        public:
            using value_type = T; //data
            using pointer = T*; // * on current
            using reference = T&; // & on elements
            using difference_type = std::ptrdiff_t; // diff between next and last
            using iterator_category = std::forward_iterator_tag;

            Iterator(Node* node) : current(node) {}

            reference operator*() const
            {
                return current->data;
            }

            pointer operator->() const 
            {
                return &(current->data);
            }

            Iterator& operator++() 
            {
                current = current->next;
                return *this;
            }

            Iterator operator++(int) 
            {
                Iterator temp = *this;
                current = current->next;
                return temp;
            }

            bool operator==(const Iterator& other) const
            {
                return this->current == other.current;
            }

            bool operator!=(const Iterator& other) const
            {
                return this->current != other.current;
            }
    };

    public:

        List(): head(nullptr), size(0) {}

        ~List()
        {
            while (head) 
            {
                Node* temp = head;
                head = head->next;

                // Destroy the data and deallocate the node
                Alloc_Item_traits::destroy(allocator, &(temp->data));
                Alloc_Item_traits::deallocate(allocator, temp, 1);
            }
            size = 0;
        }

        void push(const T& value)
        {
            //alloc for 1 element
            Node* newNode = Alloc_Item_traits::allocate(allocator, 1);
            Alloc_Item_traits::construct(allocator, newNode, value);

            newNode->next = head;
            head = newNode;
            size++;
        }

        void pop()
        {
            if (head) 
            {
                size--;
                Node* temp = head;
                head = head->next;

                // Deallocate the node before destroying the data
                Alloc_Item_traits::deallocate(allocator, temp, 1);
                // Destroy the data after deallocation
                Alloc_Item_traits::destroy(allocator, &(temp->data));
            }
        }

        int getsize() const
        {
            return size;
        }

        Iterator begin()
        {
            return Iterator(head);
        }

        Iterator end()
        {
            return Iterator(nullptr);
        }
};
```

# main.cpp
```
#include <iostream>
#include "allocator.h"
#include "list.h"

int main()
{
    std::cout << 1;
}
```

# tests.cpp
```
#include <gtest/gtest.h>
#include "list.h"
#include "allocator.h"

//Allocator

TEST(alloc, test1)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    EXPECT_EQ(v[0], 12);
}

TEST(alloc, test2)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    v.push_back(34);
    v.push_back(56);
    EXPECT_EQ(v[0], 12);
    EXPECT_EQ(v[1], 34);
    EXPECT_EQ(v[2], 56);
}

TEST(alloc, test3)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    EXPECT_EQ(v.size(), 1);
    v.push_back(34);
    v.push_back(56);
    EXPECT_EQ(v.size(), 3);
}

TEST(alloc, test4)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    EXPECT_EQ(v.size(), 1);
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

TEST(alloc, test5)
{
    std::vector<int, Allocator<int>> v;
    v.push_back(12);
    v.push_back(34);
    v.push_back(56);
    EXPECT_EQ(v.size(), 3);
    v.pop_back();
    v.pop_back();
    v.pop_back();
    EXPECT_EQ(v.size(), 0);
}

//List

TEST(List, test1)
{
    List<int> l;
    EXPECT_EQ(l.getsize(), 0); 
}

TEST(List, test2)
{
    List<int> l;
    l.push(12);
    EXPECT_EQ(l.getsize(), 1); 
}

TEST(List, test3)
{
    List<int> l;
    l.push(12);
    EXPECT_EQ(l.getsize(), 1); 
    l.pop();
    EXPECT_EQ(l.getsize(), 0);
}


TEST(List, test4)
{
    List<int> l;
    l.push(66);
    
    EXPECT_EQ(l.end(), nullptr);
}


TEST(List, test5)
{
    List<int> l;
    l.push(66);
    l.push(78);
    l.push(90);
    
    EXPECT_EQ(l.getsize(), 3);
}
```
