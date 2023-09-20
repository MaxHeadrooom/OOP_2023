#include "gtest/gtest.h"
#include "raschet.cpp"
#include "func.h"

using namespace std;

namespace my{

TEST(test01, basic_test_set)
{
    ASSERT_TRUE(func("()")==true);
}
TEST(test02, basic_test_set)
{
    ASSERT_TRUE(func("(")==false);
}
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
