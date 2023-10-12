#include "point.h"
#include <bits/stdc++.h>

using namespace std;

pointer::pointer(double x, double y)
{
    double pos_x = x;
    double pos_y = y;
}

pointer::pointer(const initializer_list<double>& coord) 
{
    if (coord.size() != 2) 
    {
        throw invalid_argument("Only 2 arguments");
    }

    pos_x = *(coord.begin());
    pos_y = *(coord.begin() + 1);
}

pointer::pointer(const pointer& other)
{
    pos_x = other.pos_x;
    pos_y = other.pos_y;
}

const double pointer::get_x()
{
    return pos_x;
}

const double pointer::get_y()
{
    return pos_y;
}