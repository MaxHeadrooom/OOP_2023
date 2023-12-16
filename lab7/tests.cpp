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