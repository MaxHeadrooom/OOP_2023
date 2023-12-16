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