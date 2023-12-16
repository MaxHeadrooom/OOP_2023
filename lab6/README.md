# Лабораторная работа 6. Паттерны проектирования

## Автор: Эсмедляев Федор, группа М8О-212Б-22

Вы разрабатываете редактор подземелья для новой RPG игры Balagur Fate 3. Ваша задача сделать
программу, которая позволит моделировать базовые локации, расставляя на них NPC (non-player
characters).
Редактор должен позволять делать следующие действия:
1. Добавлять новые NPC по разным координатам (типы объектов предопределены заданием)
a. NPC размещаются в квадрате 0<=x<=500 метров, 0<=y<=500 метров
b. У каждого типа объекта помимо координат должно быть уникальное имя.
2. Сохранять объекты в файл и загружать из файла
3. Печатать перечень объектов на экран (с типом объектов, координатами и именем)
4. Запускать боевой режим с указанием дальности, на которой могут сражаться NPC. В
боевом режиме NPC начинают сражаться каждый с каждым (если дальность позволяет),
проигравший NPC – удаляется. При этом погибнуть могут и оба NPC.
При создании программы обязательно использовать паттерны:
- Какой-нибудь из вариантов Factory для создания NPC и загрузки NPC из файла
- Visitor – для проведения цикла сражения
- Observer – для печати событий о совершенных убийствах. Сделать два класса Observer – для
записи в файл “log.txt” и для печати на экран.

## Программы

# CMakeLists.txt

```
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
```

# observer.h
```
#pragma once
#include <iostream>
#include <fstream>
#include <memory>

class NPC;

class Observer 
{
    public:
        Observer() = default;
        virtual void update(NPC*, NPC*, bool) = 0;
};

class ConsoleObserver: public Observer 
{
    public:
        ConsoleObserver() = default;
        void update(NPC*, NPC*, bool) override;
};

class FileObserver: public Observer 
{
    std::unique_ptr<std::ostream> stream;
    
    public:
        FileObserver(std::ofstream&);
    
    void update(NPC*, NPC*, bool) override;
};
```

# observer.cpp
```
#include "observer.h"
#include "npc.h"

void ConsoleObserver::update(NPC* defender, NPC* attacker, bool win) 
{
    if (!win) 
        return;

    std::cout << "KILL: ";
    defender->print(std::cout);
    std::cout << " was killed by ";
    attacker->print(std::cout);
    std::cout << '\n';
}

FileObserver::FileObserver(std::ofstream& str) 
{
    stream = std::make_unique<std::ofstream>(std::move(str));
}

void FileObserver::update(NPC* defender, NPC* attacker, bool win) 
{
    if (!win) return;
    *stream << "KILL: ";
    defender->print(*stream);
    *stream << " was killed by ";
    attacker->print(*stream);
    *stream << '\n';
}
```

# npc.h
```
#pragma once

#include <list>
#include <memory>
#include "observer.h"


class Squirrel;
class Bear;
class Orc;

class NPC 
{
    protected:
        std::list<Observer*> observers;
        int x;
        int y;
        std::string name;
    bool alive;

    public:
        NPC() = default;
        ~NPC() = default;

        virtual void print(std::ostream&) = 0;

        virtual void accept(NPC*, const int&) = 0;

        virtual void attach(Observer*);
        virtual void detach(Observer*);
        virtual void notify(NPC*, bool);

        virtual bool is_close(const NPC&, const int&) const noexcept;
        virtual bool is_alive() const noexcept;

        friend std::ostream& operator<<(std::ostream&, const NPC&);
};
```
# npc.cpp
```
#include "npc.h"
#include <algorithm>

bool NPC::is_close(const NPC& other, const int& distance) const noexcept 
{
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y) <= distance * distance;
}

void NPC::notify(NPC* attacker, bool win) 
{
    if (win) 
    {
        for (auto &elem : NPC::observers) 
        {
            elem->update(this, attacker, win);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const NPC& other) 
{
    return out << "$NPC {" << other.x << ", " << other.y << '}';
}

void NPC::attach(Observer* observer) 
{
    observers.push_back(observer);
}
void NPC::detach(Observer* observer) 
{
    observers.erase(std::find(NPC::observers.begin(), NPC::observers.end(), observer));
}

bool NPC::is_alive() const noexcept { return alive; }
```

# factory.h
```
#include "npc.h"

std::shared_ptr<NPC> factory(std::istream&);
std::shared_ptr<NPC> factory(const std::string&, const std::string&, const int&, const int&);
```

# factory.cpp
```
#include "factory.h"
#include "squirrel.h"
#include "orc.h"
#include "bear.h"

std::shared_ptr<NPC> factory(std::istream& in) 
{
    std::string type, name;
    int x, y;
    char c;
    in >> type >> name >> c >> x >> c >> y >> c;
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") 
    {
        res = std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Orc") 
    {
        res = std::make_shared<Orc>(x, y, name);
    }
    else if (type == "Bear") 
    {
        res = std::make_shared<Bear>(x, y, name);
    }
    else if (type != "") 
    {
        std::cerr << "Unknown type" << '\n';
    }
    return res;
}

std::shared_ptr<NPC> factory(const std::string& type, const std::string& name, const int& x, const int& y) 
{
    std::shared_ptr<NPC> res;
    if (type == "Squirrel") 
    {
        res = std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Orc") 
    {
        res = std::make_shared<Orc>(x, y, name);
    }
    else if (type == "Bear") 
    {
        res = std::make_shared<Bear>(x, y, name);
    }
    else 
    {
        std::cerr << "Unknown type" << '\n';
    }
    return res;
}
```

# bear.h
```
#pragma once
#include "npc.h"


class Bear: public NPC 
{
    public:
        Bear(const int&, const int&, const std::string&);

        void print(std::ostream&) override;

        void accept(NPC*, const int&) override;

        friend std::ostream& operator<<(std::ostream&, const Bear&);
};
```

# bear.cpp
```
#include "bear.h"
#include "orc.h"
#include "squirrel.h"
#include <algorithm>

Bear::Bear(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Bear::print(std::ostream& out) 
{
    out << *this;
}

void Bear::accept(NPC* attacker, const int& distance) 
{
    if (alive and dynamic_cast<Orc*>(attacker)) 
    {
        bool win = is_close(*attacker, distance);
        if (win) 
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Bear& other) 
{
    return out << "Bear " << other.name << " {" << other.x << ", " << other.y << '}';
}
```

# squirrel.h
```
#pragma once
#include "npc.h"


class Squirrel: public NPC 
{
    public:
        Squirrel(const int&, const int&, const std::string&);

        void print(std::ostream&) override;

        void accept(NPC*, const int&) override;

        friend std::ostream& operator<<(std::ostream&, const Squirrel&);
};
```

# squirrel.cpp
```
#include "orc.h"
#include "bear.h"
#include "squirrel.h"
#include <algorithm>

Squirrel::Squirrel(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Squirrel::print(std::ostream& out) 
{
    out << *this;
}

void Squirrel::accept(NPC* attacker, const int& distance) 
{
    if (alive and dynamic_cast<Bear*>(attacker)) 
    {
        bool win = is_close(*attacker, distance);
        if (win) 
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Squirrel& other) 
{
    return out << "Squirrel " << other.name << " {" << other.x << ", " << other.y << '}';
}
```

# orc.h
```
#pragma once
#include "npc.h"


class Orc: public NPC 
{
    public:
        Orc(const int&, const int&, const std::string&);

        void print(std::ostream&) override;

        void accept(NPC*, const int&) override;

        friend std::ostream& operator<<(std::ostream&, const Orc&);
};
```#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <memory>
#include "squirrel.h"
#include "bear.h"
#include "orc.h"
#include "factory.h"

TEST(Constructors1, Squirrel) 
{
    Squirrel s(0, 0, "Belka");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Squirrel Belka {0, 0}");
}

TEST(Constructors2, Bear) 
{
    Bear s(0, 0, "Bear");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Bear Bear {0, 0}");
}

TEST(Constructors3, Orc) 
{
    Orc s(0, 0, "Orc");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Orc Orc {0, 0}");
}

TEST(Fabric, basic) 
{
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Squirrel", "Name", 0, 0));
    persons.push_back(factory("Orc", "Name", 0, 0));
    persons.push_back(factory("Bear", "Name", 0, 0));

    std::stringstream out;
    for (auto& elem : persons) 
    {
        elem->print(out);
    }
    ASSERT_EQ(out.str(), "Squirrel Name {0, 0}Orc Name {0, 0}Bear Name {0, 0}");
}

TEST(Fighting, basic) 
{
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Squirrel", "Name", 0, 0));
    persons.push_back(factory("Orc", "Name", 1, 1));
    persons.push_back(factory("Bear", "Name", 2, 2));

    for (auto& defender : persons) 
    {
        for (auto& attacker : persons) 
        {
            defender->accept(attacker.get(), 2);
        }
    }

    int i = 0;

    for (auto& elem : persons) 
    {
        i++;
        if (i == 3)
            ASSERT_FALSE(elem->is_alive());
        else
            ASSERT_TRUE(elem->is_alive());
    }
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

# orc.cpp
```
#include "orc.h"
#include "bear.h"
#include "squirrel.h"
#include <algorithm>

Orc::Orc(const int& _x, const int& _y, const std::string& _name) 
{
    x = _x;
    y = _y;
    name = _name;
    alive = true;
}

void Orc::print(std::ostream& out) 
{
    out << *this;
}

void Orc::accept(NPC* attacker, const int& distance) 
{
    if (alive && (dynamic_cast<Orc*>(attacker) && attacker != this)) 
    {
        bool win = is_close(*attacker, distance);
        if (win) 
            alive = false;
        notify(attacker, win);
    }
}

std::ostream& operator<<(std::ostream& out, const Orc& other) 
{
    return out << "Orc " << other.name << " {" << other.x << ", " << other.y << '}';
}
```

# main.cpp
```
#include <iostream>
#include <vector>
#include "squirrel.h"
#include "bear.h"
#include "orc.h"
#include "observer.h"
#include "factory.h"


void load(std::vector<std::shared_ptr<NPC>>& array, std::ifstream& file) 
{
    while (file) 
    {
        auto tmp = factory(file);
        if (tmp)
            array.push_back(tmp);
    }
}

void save(std::vector<std::shared_ptr<NPC>>& array, std::ofstream& file) 
{
    for (std::shared_ptr<NPC>& elem : array) 
    {
        elem->print(file);
        file << '\n';
    }
}

int main() 
{
    ConsoleObserver cobs;
    std::ofstream filelog("log.txt");
    FileObserver fobs(filelog);

    std::vector<std::shared_ptr<NPC>> persons;

    std::string query;
    do 
    {
        std::cin >> query;
        if (query == "load") 
        {
            std::ifstream file_for_load;
            std::string filename;
            std::cin >> filename;
            file_for_load.open(filename);
            load(persons, file_for_load);
        }
        else if (query == "save") 
        {
            std::ofstream file_for_save;
            std::string filename;
            std::cin >> filename;
            file_for_save.open(filename);
            save(persons, file_for_save);
        }
        else if (query == "add") 
        {
            auto new_npc = factory(std::cin);
            if (new_npc)
                persons.push_back(new_npc);
        }
        else if (query == "show") 
        {
            for (auto& elem : persons) 
            {
                elem->print(std::cout);
                std::cout << '\n';
            }
        }
    } while(query != "fight");

    for (auto& elem : persons) 
    {
        elem->attach(&cobs);
        elem->attach(&fobs);
    }
    std::cout << "Enter a distance" << '\n';
    
    int distance;
    std::cin >> distance;

    for (auto& defender : persons) 
    {
        for (auto& attacker : persons) 
        {
            defender->accept(attacker.get(), distance);
        }
    }
}
```

# tests.cpp
```
#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <memory>
#include "squirrel.h"
#include "bear.h"
#include "orc.h"
#include "factory.h"

TEST(Constructors1, Squirrel) 
{
    Squirrel s(0, 0, "Belka");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Squirrel Belka {0, 0}");
}

TEST(Constructors2, Bear) 
{
    Bear s(0, 0, "Bear");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Bear Bear {0, 0}");
}

TEST(Constructors3, Orc) 
{
    Orc s(0, 0, "Orc");
    std::stringstream out;
    s.print(out);
    ASSERT_EQ(out.str(), "Orc Orc {0, 0}");
}

TEST(Fabric, basic) 
{
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Squirrel", "Name", 0, 0));
    persons.push_back(factory("Orc", "Name", 0, 0));
    persons.push_back(factory("Bear", "Name", 0, 0));

    std::stringstream out;
    for (auto& elem : persons) 
    {
        elem->print(out);
    }
    ASSERT_EQ(out.str(), "Squirrel Name {0, 0}Orc Name {0, 0}Bear Name {0, 0}");
}

TEST(Fighting, basic) 
{
    std::vector<std::shared_ptr<NPC>> persons;
    persons.push_back(factory("Squirrel", "Name", 0, 0));
    persons.push_back(factory("Orc", "Name", 1, 1));
    persons.push_back(factory("Bear", "Name", 2, 2));

    for (auto& defender : persons) 
    {
        for (auto& attacker : persons) 
        {
            defender->accept(attacker.get(), 2);
        }
    }

    int i = 0;

    for (auto& elem : persons) 
    {
        i++;
        if (i == 3)
            ASSERT_FALSE(elem->is_alive());
        else
            ASSERT_TRUE(elem->is_alive());
    }
}

int main(int argc, char** argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
