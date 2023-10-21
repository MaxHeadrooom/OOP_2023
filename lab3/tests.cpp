#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "six_ugl.h"
#include "eight_ugl.h"
#include "triangle.h"

//triangle

TEST(calc_s, test_1) 
{
    triangle test1 (pointer(0, 0), pointer(10, 0), pointer(5, 5*sqrt(3)));

    EXPECT_DOUBLE_EQ(test1.calculate_s(), 25*sqrt(3));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}