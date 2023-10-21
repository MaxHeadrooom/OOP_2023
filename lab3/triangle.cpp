#include "triangle.h"
#include <bits/stdc++.h>

using namespace std;

triangle::triangle(const pointer& left_dot, const pointer& mid_dot, const pointer& right_dot)
{
    this->storona = sqrt((left_dot.pos_x - right_dot.pos_x)*(left_dot.pos_x - right_dot.pos_x) + 
    (left_dot.pos_y - right_dot.pos_y)*(left_dot.pos_y - right_dot.pos_y));

    if (storona <= 0)
        throw invalid_argument("It's not a triangle");
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}

triangle::triangle(const triangle& other) noexcept
{
    //prisvaivanie iz other v tekuschee - this
    this->left_dot = other.left_dot;
    this->mid_dot = other.mid_dot;
    this->right_dot = other.right_dot;
}

triangle::triangle(triangle&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_dot = move(other.left_dot);
    this->mid_dot = move(other.mid_dot);
    this->right_dot = move(other.right_dot);
}

triangle& triangle::operator=(const triangle& other) noexcept
{
    //this - tekuschiy ob'ect
    if (this == &other)//oznachaet cto uje est, t.e. prisvaevaet sam sebe, poetomu uje est'
        return *this;

    //prisvaivanie iz other v tekuschee - this
    this->left_dot = other.left_dot;
    this->mid_dot = other.mid_dot;
    this->right_dot = other.right_dot;

    return *this;
}

triangle& triangle::operator=(triangle&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_dot = move(other.left_dot);
    this->mid_dot = move(other.mid_dot);
    this->right_dot = move(other.right_dot);

    return *this;
}

bool triangle::operator==(const triangle& other)
{
    if (this->left_dot == other.left_dot and this->mid_dot == other.mid_dot and
    this->right_dot == other.right_dot)
        return true;
    return false;
}

double triangle::calculate_S()
{
    return (storona*storona*sqrt(3)/4);
}

pointer triangle::calculate_mid()
{
    pointer geom_mid((left_dot.pos_x + mid_dot.pos_x + right_dot.pos_x)/3,
    (left_dot.pos_y + mid_dot.pos_y + right_dot.pos_y)/3);

    return geom_mid;
}

istream& operator>>(istream& chten, triangle& tria)
{
    chten >> tria.left_dot >> tria.mid_dot >> tria.right_dot;

    return chten;
}

ostream& operator<<(ostream& vivod, const triangle& tria)
{
    vivod << tria.left_dot << " " <<  tria.mid_dot << " " << tria.right_dot;

    return vivod;
}