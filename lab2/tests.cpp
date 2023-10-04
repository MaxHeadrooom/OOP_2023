#include <gtest/gtest.h>
#include "eleven.h"

using namespace std;

TEST(Constructors, gicha) 
{
    Eleven num = Eleven();
    EXPECT_EQ(num.get_size(), 0);
    EXPECT_EQ(num.get_stringified(), "\0");
}

TEST(Constructors1, gacha) 
{
    Eleven num = Eleven(3, '1');
    EXPECT_EQ(num.get_size(), 3);
    EXPECT_EQ(num.get_stringified(), "111");
}

TEST(Constructors2, initializer_list_filled) 
{
    Eleven num = Eleven({'1', '2'});
    EXPECT_EQ(num.get_size(), 2);
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Constructors3, initializer_list_filled) 
{
    Eleven num = Eleven({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A'});
    EXPECT_EQ(num.get_size(), 11);
    EXPECT_EQ(num.get_stringified(), "0123456789A");
}

TEST(Constructors4, initializer_list_empty) 
{
    Eleven num = Eleven({});
    EXPECT_EQ(num.get_size(), 0);
    EXPECT_EQ(num.get_stringified(), "");
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}