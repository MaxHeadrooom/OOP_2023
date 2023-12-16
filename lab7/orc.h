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