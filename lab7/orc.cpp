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