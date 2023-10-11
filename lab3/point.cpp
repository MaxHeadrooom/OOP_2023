#include <point.h>
#include <bits/stdc++.h>

using namespace std;

point::point(double x, double y)
{
    double pos_x = x;
    double pos_y = y;
}

point::point(const initializer_list<double>& coord) 
{
    if (coord.size() != 2) 
    {
        throw invalid_argument("Only 2 arguments");
    }

    pos_x = *(coord.begin());
    pos_y = *(coord.begin() + 1);
}

point::point(const point& other)
{
    pos_x = other.pos_x;
    pos_y = other.pos_y;
}

const double point::get_x()
{
    return pos_x;
}

const double point::get_y()
{
    return pos_y;
}