#include "gtest/gtest.h"
#include "func.h"

using namespace std;

string s;

TEST(test01, basic_test_set)
{
    s = "()";
    ASSERT_TRUE(func(s)==true);
}

TEST(test02, basic_test_set)
{
    s = "(";
    ASSERT_TRUE(func(s)==false);
}

TEST(test03, basic_test_set)
{
    s = ")(())";
    ASSERT_TRUE(func(s)==false);
}

TEST(test04, basic_test_set)
{
    s = "(())((()())())";
    ASSERT_TRUE(func(s)==true);
}

TEST(test05, basic_test_set)
{
    s = "";
    ASSERT_TRUE(func(s)==true);
}

TEST(test06, basic_test_set)
{
    s = "(((((((((((((((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))))))))))))))";//100скобок
    ASSERT_TRUE(func(s)==true);
}

TEST(test07, basic_test_set)
{
    s = ")((((((((((((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))))))))))))";
    ASSERT_TRUE(func(s)==false);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}