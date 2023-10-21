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

bool pointer::operator==(const pointer& other)
{
    return (this->pos_x == other.pos_x and this->pos_y == other.pos_y);
}

istream& operator>>(istream& chten, pointer& point)
{
    chten >> point.pos_x >> point.pos_y;
    return chten;
}

ostream& operator<<(ostream& vivod, const pointer& point)
{
    vivod << point.pos_x << " " << point.pos_y;
    return vivod;
}