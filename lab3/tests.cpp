#include <gtest/gtest.h>
#include <bits/stdc++.h>
#include "six_ugl.h"
#include "eight_ugl.h"
#include "triangle.h"
#include "array.h"

using namespace std;

TEST(calc_s, test_1) 
{
    triangle test1(pointer12(10, 0), pointer12(0, 0), pointer12(5, 5*sqrt(3)));

    EXPECT_DOUBLE_EQ(test1.calculate_s(), 25*sqrt(3));
}

/*TEST(calc_s, test_2) 
{
    triangle test2(pointer12(0, 0), pointer12(0, 0), pointer12(0, 0));

    EXPECT_ANY_THROW(test2.calculate_s()); 
}*/

TEST(calc_s, test_3) 
{
    six_ugl test3 (pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6));

    EXPECT_DOUBLE_EQ(test3.calculate_s(), 3*sqrt(3));
}

TEST(calc_s, test_4) 
{
    eight_ugl test4 (pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6), pointer12(7, 7), pointer12(8, 8));

    EXPECT_DOUBLE_EQ(test4.calculate_s(), 4*sqrt(2) + 4);
}

TEST(pereg, test_5)
{
    triangle test1(pointer12(10, 0), pointer12(0, 0), pointer12(5, 5*sqrt(3)));
    triangle test2(pointer12(10, 0), pointer12(0, 0), pointer12(5, 5*sqrt(3)));

    EXPECT_TRUE(test1 == test2);
}

TEST(pereg, test_6)
{
    six_ugl test1(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6));
    six_ugl test2(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6));

    EXPECT_TRUE(test1 == test2);
}

TEST(pereg, test_7)
{
    eight_ugl test1(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6), pointer12(7, 7), pointer12(8, 8));
    eight_ugl test2(pointer12(1, 1), pointer12(2, 2), pointer12(3, 3), pointer12(4, 4),
    pointer12(5, 5), pointer12(6, 6), pointer12(7, 7), pointer12(8, 8));

    EXPECT_TRUE(test1 == test2);
}

TEST(arra, push) 
{
    arrayy a(10);
    triangle* p = new triangle();
    a.push_back(1, p);
    EXPECT_EQ(a[1], p);
}

TEST(arra, delete_element) 
{
    arrayy a(10);
    triangle* p = new triangle();
    a.push_back(1, p);
    EXPECT_EQ(a[1], p);
    a.pop(1);
    EXPECT_EQ(a[1], nullptr);
}

ll epsilon = 1e9;

TEST(Array, sum_s) 
{
    arrayy a(10);
    triangle* p1 = new triangle();
    triangle* p2 = new triangle();
    a.push_back(0, p1);
    a.push_back(1, p2);
    EXPECT_LT(abs(a.calc_all_s() - 0.0), epsilon);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}