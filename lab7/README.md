# Лабораторная работа 7. Асинхронное программирование

## Автор: Эсмедляев Федор, группа М8О-212Б-22

### Цель:
- Знакомство с асинхронным программированием;
- Получение практических навыков в параллельной обработке данных;
- Получение практических навыков в синхронизации потоков;

### Требования к программе:
Модифицируйте вашу лабораторную работу №6 следующим образом:
- Должно быть реализовано три потока:
    + Поток, который осуществляет передвижение NPC на определенное расстояние (см. таблицу), а также определяет, что два NPC находятся на расстоянии убийства (см. таблицу). Если два NPC вступили в «бой», то он создает задачу для потока, осуществляющего бои.
    + Поток, который осуществляет бои. Если один npc может убивать другой, то каждый npc «кидает 6-гранный кубик» определяя силу атаки и силу защиты (соответственно). Если сила атаки больше, чем сила защиты – то происходит убийство.
    + Мертвые npc не передвигаются (у нас тут без некромантов).
    + Живые npc не могут покинуть карту (размер задается через константы, например 100 x 100)
    + Основной поток раз в секунду печатает карту. Мертвые npc на карте не отображаются.
- Осуществить контроль доступа к разделяемым ресурсов с помощью std::shared_lock и std::lock_guard
- Осуществить контроль к потоку вывода std::cout через std::lock_guard
- Потоки могут запускаться как std::thread с использованием лямбда функций или функторов (классов с перегруженным оператором operator())
- Вначале игры должно создаваться 50 npc в случайных локациях.
- Игра должна останавливаться через 30 секунд и выводить на экран список выживших

### Таблица убиваемости:

Кто нагоняет         | Расстояние хода  | Расстояние убийства
---------------------|------------------|---------------------
Белка                | 5                | 5
Орк                  | 20               | 10
Медведь              | 5                | 10

## Программы

# CmakeLists.txt
```
cmake_minimum_required(VERSION 3.10)
project(oop7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(app main.cpp npc.cpp squirrel.cpp bear.cpp orc.cpp)

enable_testing()
add_subdirectory(googletest)

add_executable(tests tests.cpp npc.cpp squirrel.cpp bear.cpp orc.cpp)

target_link_libraries(tests PRIVATE GTest::gtest_main)
include(GoogleTest)
```

# squirrel.h
```
#pragma once
#include "npc.h"

struct Squirrel : public NPC
{
    Squirrel(int x, int y);
    Squirrel(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    bool accept(std::shared_ptr<NPC> visitor) override;

    friend std::ostream &operator<<(std::ostream &os, Squirrel &knight);
};
```

# squirrel.cpp
```
#include "squirrel.h"
#include "bear.h"
#include "orc.h"

Squirrel::Squirrel(int x, int y) : NPC(SquirrelType, x, y) {}
Squirrel::Squirrel(std::istream &is) : NPC(SquirrelType, is) {}

bool Squirrel::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Squirrel>(this,[](Squirrel*){}));
}

void Squirrel::print()
{
    std::cout << *this;
}

void Squirrel::save(std::ostream &os)
{
    os << SquirrelType << std::endl;
    NPC::save(os);
}


bool Squirrel::fight(std::shared_ptr<Orc> other)
{
    fight_notify(other, false);
    return true;
}

bool Squirrel::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, false);
    return true;
}

bool Squirrel::fight(std::shared_ptr<Squirrel> other)
{
    fight_notify(other, false);
    return true;
}

std::ostream &operator<<(std::ostream &os, Squirrel &Squirrel)
{
    os << "Squirrel: " << *static_cast<NPC *>(&Squirrel) << std::endl;
    return os;
}
```

# orc.h
```
#pragma once
#include "npc.h"

struct Orc : public NPC
{
    Orc(int x, int y);
    Orc(std::istream &is);
    void print() override;
    void save(std::ostream &os) override;
    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    friend std::ostream &operator<<(std::ostream &os, Orc &Orc);

    bool accept(std::shared_ptr<NPC> visitor) override;
};
```

# orc.cpp
```
#include "orc.h"
#include "squirrel.h"
#include "bear.h"

Orc::Orc(int x, int y) : NPC(OrcType, x, y) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

void Orc::print()
{
    std::cout << *this;
}

bool Orc::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Orc>(this,[](Orc*){}));
}

void Orc::save(std::ostream &os)
{
    os << OrcType << std::endl;
    NPC::save(os);
}


bool Orc::fight(std::shared_ptr<Orc> other)
{
    fight_notify(other, true);
    return true;
}

bool Orc::fight(std::shared_ptr<Bear> other)
{
    fight_notify(other, true);
    return false;
}

bool Orc::fight(std::shared_ptr<Squirrel> other)
{
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, Orc &Orc)
{
    os << "Orc: " << *static_cast<NPC *>(&Orc) << std::endl;
    return os;
}
```

# bear.h
```
#pragma once
#include "npc.h"

struct Bear : public NPC
{
    Bear(int x, int y);
    Bear(std::istream &is);

    void print() override;

    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Bear &Bear);
};
```

# bear.cpp
```
#include "squirrel.h"
#include "bear.h"
#include "orc.h"

Bear::Bear(int x, int y) : NPC(BearType, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

bool Bear::accept(std::shared_ptr<NPC> visitor){
    return visitor->fight(std::shared_ptr<Bear>(this,[](Bear*){}));
}

void Bear::print()
{
    std::cout << *this;
}


bool Bear::fight(std::shared_ptr<Bear> other) 
{
    fight_notify(other, false);
    return false;
}

bool Bear::fight(std::shared_ptr<Orc> other) 
{
    fight_notify(other, false);
    return false;
}

bool Bear::fight(std::shared_ptr<Squirrel> other) 
{
    fight_notify(other, true);
    return false;
}

void Bear::save(std::ostream &os) 
{
    os << BearType << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Bear &Bear)
{
    os << "Bear: " << *static_cast<NPC *>(&Bear) << std::endl;
    return os;
}
```

# npc.h
```
#pragma once

#include <iostream>
#include <memory>
#include <cstring>
#include <string>
#include <random>
#include <fstream>
#include <set>
#include <math.h>
#include <shared_mutex>

// type for npcs
struct NPC;
struct Orc;
struct Bear;
struct Squirrel;
using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    OrcType = 1,
    BearType = 2,
    SquirrelType = 3
};

struct IFightObserver
{
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

class NPC
{
private:
    std::mutex mtx;

    NpcType type;
    int x{0};
    int y{0};
    bool alive{true};

    std::vector<std::shared_ptr<IFightObserver>> observers;

public:
    NPC(NpcType t, int _x, int _y);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    virtual bool is_close(const std::shared_ptr<NPC> &other, size_t distance);

    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;
    // visit
    virtual bool fight(std::shared_ptr<Orc> other) = 0;
    virtual bool fight(std::shared_ptr<Bear> other) = 0;
    virtual bool fight(std::shared_ptr<Squirrel> other) = 0;

    virtual void print() = 0;
    std::pair<int, int> position();
    NpcType get_type();

    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);

    void move(int shift_x, int shift_y, int max_x, int max_y);

    bool is_alive();
    void must_die();
};
```

# npc.cpp
```
#include "npc.h"

NPC::NPC(NpcType t, int _x, int _y) : type(t), x(_x), y(_y) {}
NPC::NPC(NpcType t, std::istream &is) : type(t)
{
    is >> x;
    is >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer)
{
    observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win)
{
    for (auto &o : observers)
        o->on_fight(std::shared_ptr<NPC>(this, [](NPC *) {}), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance)
{
    auto [other_x, other_y] = other->position();

    std::lock_guard<std::mutex> lck(mtx);
    if ((std::pow(x - other_x, 2) + std::pow(y - other_y, 2)) <= std::pow(distance, 2))
        return true;
    else
        return false;
}

NpcType NPC::get_type()
{
    std::lock_guard<std::mutex> lck(mtx);
    return type;
}

std::pair<int, int> NPC::position()
{
    std::lock_guard<std::mutex> lck(mtx);
    return {x, y};
}

void NPC::save(std::ostream &os)
{
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{ x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y)
{
    std::lock_guard<std::mutex> lck(mtx);

    if ((x + shift_x >= 0) && (x + shift_x <= max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y <= max_y))
        y += shift_y;
}

bool NPC::is_alive()
{
    std::lock_guard<std::mutex> lck(mtx);
    return alive;
}

void NPC::must_die()
{
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
}
```

# main.cpp
```
#include "npc.h"
#include "bear.h"
#include "squirrel.h"
#include "orc.h"
#include <sstream>

#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <optional>
#include <array>

using namespace std::chrono_literals;
std::mutex print_mutex;


class TextObserver : public IFightObserver
{
private:
    TextObserver(){};

public:
    static std::shared_ptr<IFightObserver> get()
    {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override
    {
        if (win)
        {
            std::lock_guard<std::mutex> lck(print_mutex);
            std::cout << std::endl
                      << "Murder --------" << std::endl;
            attacker->print();
            defender->print();
        }
    }
};


std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    int type{0};
    if (is >> type)
    {
        switch (type)
        {
        case OrcType:
            result = std::make_shared<Orc>(is);
            break;
        case BearType:
            result = std::make_shared<Bear>(is);
            break;
        case SquirrelType:
            result = std::make_shared<Squirrel>(is);
            break;
        }
    }
    else
        std::cerr << "unexpected NPC type:" << type << std::endl;

    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y)
{
    std::shared_ptr<NPC> result;
    switch (type)
    {
    case OrcType:
        result = std::make_shared<Orc>(x, y);
        break;
    case BearType:
        result = std::make_shared<Bear>(x, y);
        break;
    case SquirrelType:
        result = std::make_shared<Squirrel>(x, y);
        break;
    default:
        break;
    }
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

// save array to file
void save(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename)
{
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is));
        is.close();
    }
    else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}


std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}

set_t fight(const set_t &array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                attacker->is_close(defender, distance) &&
                defender->accept(attacker))
                dead_list.insert(defender);

    return dead_list;
}

struct print : std::stringstream
{
    ~print()
    {
        static std::mutex mtx;
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << this->str();
        std::cout.flush();
    }
};

struct FightEvent
{
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager
{
private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() {}

public:
    static FightManager &get()
    {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent &&event)
    {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(event);
    }

    void operator()()
    {
        while (true)
        {
            {
                std::optional<FightEvent> event;

                {
                    std::lock_guard<std::shared_mutex> lock(mtx);
                    if (!events.empty())
                    {
                        event = events.back();
                        events.pop();
                    }
                }

                if (event)
                {
                    try
                    {
                        if (event->attacker->is_alive())    
                            if (event->defender->is_alive()) 
                                if (event->defender->accept(event->attacker))
                                    event->defender->must_die();
                    }
                    catch (...)
                    {
                        std::lock_guard<std::shared_mutex> lock(mtx);
                        events.push(*event);
                    }
                }
                else
                    std::this_thread::sleep_for(100ms);
            }
        }
    }
};

int main()
{
    //srand(time(NULL));
    set_t array; 

    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE{40};

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % MAX_X,
                             std::rand() % MAX_Y));

    std::cout << "Starting list:" << std::endl
              << array;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, MAX_X, MAX_Y, DISTANCE]()
                            {
            while (true)
            {
                for (std::shared_ptr<NPC> npc : array)
                {
                        if(npc->is_alive()){
                            int shift_x = std::rand() % 20 - 10;
                            int shift_y = std::rand() % 20 - 10;
                            npc->move(shift_x, shift_y, MAX_X, MAX_Y);
                        }
                }
                for (std::shared_ptr<NPC> npc : array)
                    for (std::shared_ptr<NPC> other : array)
                        if (other != npc)
                            if (npc->is_alive())
                            if (other->is_alive())
                            if (npc->is_close(other, DISTANCE))
                                FightManager::get().add_event({npc, other});

                std::this_thread::sleep_for(1s);
            } });

    while (true)
    {
        const int grid{20}, step_x{MAX_X / grid}, step_y{MAX_Y / grid};
        {
            std::array<char, grid * grid> fields{0};
            for (std::shared_ptr<NPC> npc : array)
            {
                auto [x, y] = npc->position();
                int i = x / step_x;
                int j = y / step_y;

                if (npc->is_alive())
                {
                    switch (npc->get_type())
                    {
                    case OrcType:
                        fields[i + grid * j] = 'O';
                        break;
                    case BearType:
                        fields[i + grid * j] = 'B';
                        break;
                    case SquirrelType:
                        fields[i + grid * j] = 'S';
                        break;

                    default:
                        break;
                    }
                }
                else
                    fields[i + grid * j] = '.';
            }

            std::lock_guard<std::mutex> lck(print_mutex);
            for (int j = 0; j < grid; ++j)
            {
                for (int i = 0; i < grid; ++i)
                {
                    char c = fields[i + j * grid];
                    if (c != 0)
                        std::cout << "[" << c << "]";
                    else
                        std::cout << "[ ]";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
        std::this_thread::sleep_for(1s);
    };

    move_thread.join();
    fight_thread.join();

    return 0;
}
```

# tests.cpp
```
#include <gtest/gtest.h>
#include <memory>
#include "npc.h"
#include "squirrel.h"
#include "orc.h"
#include "bear.h"

TEST(test_01, Squirrel_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);

    EXPECT_EQ((a->position()).first,100);
}

TEST(test_02, Squirrel_constructor)
{
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);

    EXPECT_EQ((a->position()).second,100);
}

TEST(test_03, Squirrel_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);
    EXPECT_EQ(SquirrelType,a->get_type());
}

TEST(test_04, Squirrel_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);
    EXPECT_TRUE(a->is_alive());
}


TEST(test_05, Squirrel_constructor){
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Squirrel>(x2, y2);
    EXPECT_TRUE(a->is_close(b,100));
}

TEST(test_06, Squirrel_constructor){
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Squirrel>(x, y);

    a->move(50,50,100,100);
    EXPECT_EQ((a->position()).first,60);
}

TEST(test_07, Bear_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x, y);

    EXPECT_EQ((a->position()).first,100);
}

TEST(test_08, Bear_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x, y);

    EXPECT_EQ((a->position()).second,100);
}

TEST(test_09, Bear_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x, y);
    EXPECT_EQ(BearType,a->get_type());
}

TEST(test_10, Bear_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x, y);
    EXPECT_TRUE(a->is_alive());
}


TEST(test_11, Bear_constructor){
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Squirrel>(x2, y2);
    EXPECT_TRUE(a->is_close(b,100));
}

TEST(test_12, Bear_constructor){
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Bear>(x, y);

    a->move(50,50,100,100);
    EXPECT_EQ((a->position()).first,60);
}

TEST(test_13, Orc_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Orc>(x, y);

    EXPECT_EQ((a->position()).first,100);
}

TEST(test_14, Orc_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Orc>(x, y);

    EXPECT_EQ((a->position()).second,100);
}

TEST(test_15, Orc_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Orc>(x, y);
    EXPECT_EQ(OrcType,a->get_type());
}

TEST(test_16, Orc_constructor){
    int x{100};
    int y{100};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Orc>(x, y);
    EXPECT_TRUE(a->is_alive());
}


TEST(test_17, Orc_constructor){
    int x1{100};
    int y1{100};

    int x2{90};
    int y2{90};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Orc>(x1, y1);

    std::shared_ptr<NPC> b;
    b = std::make_shared<Squirrel>(x2, y2);
    EXPECT_TRUE(a->is_close(b,100));
}

TEST(test_18, Orc_constructor){
    int x{10};
    int y{10};

    std::shared_ptr<NPC> a;
    a = std::make_shared<Orc>(x, y);

    a->move(50,50,100,100);
    EXPECT_EQ((a->position()).first,60);
}
```
