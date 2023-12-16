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