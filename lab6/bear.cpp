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