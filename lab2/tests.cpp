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


TEST(test7, sum_normal) 
{
    Eleven num = Eleven("12");
    Eleven num2 = Eleven("12");
    EXPECT_EQ((num + num2).get_stringified(), "24");
}

TEST(test8, sum_normal) 
{
    Eleven num = Eleven("A");
    Eleven num2 = Eleven("A");
    EXPECT_EQ((num + num2).get_stringified(), "19");
}

TEST(test9, sum_normal) 
{
    Eleven num = Eleven("34");
    Eleven num2 = Eleven("0");
    EXPECT_EQ((num + num2).get_stringified(), "34");
}

TEST(test10, sum_normal) 
{
    Eleven num = Eleven("0");
    Eleven num2 = Eleven("A");
    EXPECT_EQ((num + num2).get_stringified(), "A");
}

TEST(test11, sum_normal) 
{
    Eleven num = Eleven("A");
    Eleven num2 = Eleven("A1");
    EXPECT_EQ((num + num2).get_stringified(), "100");
}

TEST(test12, sum_normal) 
{
    Eleven num = Eleven("A111");
    Eleven num2 = Eleven("A999");
    EXPECT_EQ((num + num2).get_stringified(), "19AAA");
}

TEST(test13, sum_normal) 
{
    Eleven num = Eleven("A999");
    Eleven num2 = Eleven("");
    EXPECT_EQ((num + num2).get_stringified(), "A999");
}

TEST(test14, sum_normal) 
{
    Eleven num = Eleven("11999");
    Eleven num2 = Eleven("156");
    EXPECT_EQ((num + num2).get_stringified(), "12044");
}

// minus

TEST(Operators, minus) 
{
    Eleven num = Eleven("24");
    Eleven num2 = Eleven("12");
    EXPECT_EQ((num - num2).get_stringified(), "12");
}

TEST(Operators2, minus) 
{
    Eleven num = Eleven("12000");
    Eleven num2 = Eleven("1");
    EXPECT_EQ((num - num2).get_stringified(), "11AAA");
}

TEST(Operators3, minus) 
{
    Eleven num = Eleven("12000");
    Eleven num2 = Eleven("156");
    EXPECT_EQ((num - num2).get_stringified(), "11955");
}

TEST(Operators4, minus) 
{
    Eleven num = Eleven("12000");
    Eleven num2 = Eleven("0");
    EXPECT_EQ((num - num2).get_stringified(), "12000");
}

TEST(Operators5, minus) 
{
    Eleven num = Eleven("9999");
    Eleven num2 = Eleven("111");
    EXPECT_EQ((num - num2).get_stringified(), "9888");
}

TEST(Operators6, minus) 
{
    Eleven num = Eleven("A");
    Eleven num2 = Eleven("A");
    EXPECT_EQ((num - num2).get_stringified(), "0");
}

TEST(Operators, assignment) 
{
    Eleven num;
    num = Eleven("12");
    EXPECT_EQ(num.get_stringified(), "12");
}

TEST(Operators, comparison) 
{
    Eleven num = Eleven("12");
    Eleven num2 = Eleven("11");
    EXPECT_TRUE(num > num2);
    EXPECT_FALSE(num < num2);
    EXPECT_TRUE(num2 < num);
    EXPECT_FALSE(num2 > num);
}

TEST(Operators, equality) 
{
    Eleven num = Eleven("12");
    Eleven num2 = num;
    EXPECT_TRUE(num == num2);
    EXPECT_FALSE(num > num);
    EXPECT_FALSE(num > num);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}