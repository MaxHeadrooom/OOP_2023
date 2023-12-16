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