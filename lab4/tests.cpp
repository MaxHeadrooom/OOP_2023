#include "array.h"
#include "figure.h"
#include "functions.h"
#include "gtest/gtest.h"
#include "hex.h"
#include "octo.h"
#include "tria.h"

// Hexagon double tests

std::pair<double, double> v1[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}};
std::pair<double, double> v2[] = {{7, 7}, {8, 8}, {9, 9}, {10, 10}, {11, 11}, {12, 12}};

TEST(Hexagon_double, empty_constructor) 
{
    Hexagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::calculate_mid(h);
    double surf = fig::calculate_S(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Hexagon_double, vector_constructor) 
{
    Hexagon<double> h(v1);
    std::pair<double, double> center{3.5, 3.5};
    std::pair<double, double> res = fig::calculate_mid(h);
    EXPECT_EQ(res, center);
}

std::pair<double, double> v3[] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {8, 8}};
std::pair<double, double> v4[] = {{9, 9}, {10, 10}, {11, 11}, {12, 12}, {13, 13}, {14, 14}, {15, 15}, {16, 16}};

TEST(Octagon_double, empty_constructor) 
{
    Octagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::calculate_mid(h);
    double surf = fig::calculate_S(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Octagon_double, vector_constructor) 
{
    Octagon<double> h(v3);
    std::pair<double, double> center{4.5, 4.5};
    std::pair<double, double> res = fig::calculate_mid(h);
    EXPECT_EQ(res, center);
}

std::pair<double, double> v5[] = {{1, 1}, {2, 2}, {3, 3}};
std::pair<double, double> v6[] = {{4, 4}, {5, 5}, {6, 6}};

TEST(Triangle_double, empty_constructor) 
{
    Octagon<double> h;
    std::pair<double, double> center{0, 0};
    std::pair<double, double> res = fig::calculate_mid(h);
    double surf = fig::calculate_S(h);
    EXPECT_EQ(res, center);
    EXPECT_EQ(surf, 0);
}

TEST(Triangle_double, vector_constructor) 
{
    Triangle<double> h(v5);
    std::pair<double, double> center{2, 2};
    std::pair<double, double> res = fig::calculate_mid(h);
    EXPECT_EQ(res, center);
}

std::pair<double, double> v[] = {{10, 0}, {0, 0}, {5, 5*sqrt(3)}};

ll epsilon = 1e9;

TEST(Triangle_S, vector_constructor) 
{
    Triangle<double> h(v);
    double res = fig::calculate_S(h);
    EXPECT_LT(abs(res - 25*sqrt(3)), epsilon);
}

std::pair<double, double> gicha[] = {{1, 1}, {2, 2}, {3, 3}};
std::pair<double, double> gacha[] = {{1, 1}, {2, 2}, {3, 3}};

TEST(Octago, equal) 
{
    Triangle<double> h(gicha);
    Triangle<double> h1(gacha);
    EXPECT_EQ(h, h1);
}