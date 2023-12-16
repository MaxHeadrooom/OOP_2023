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