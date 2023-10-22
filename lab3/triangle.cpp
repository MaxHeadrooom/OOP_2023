#include "triangle.h"
#include <bits/stdc++.h>

using namespace std;

triangle::triangle()
{
    this->left_dot.pos_x = 0;
    this->left_dot.pos_y = 0;
    this->mid_dot.pos_x = 0;
    this->mid_dot.pos_y = 0;
    this->right_dot.pos_x = 0;
    this->right_dot.pos_y = 0;

    this->storona = 0;
}

triangle::triangle(const pointer12& left_dot, const pointer12& mid_dot, const pointer12& right_dot)
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

double triangle::calculate_s() const
{
    return (storona*storona*sqrt(3)/4);
}

pointer12 triangle::calculate_mid() const
{
    pointer12 geom_mid((left_dot.pos_x + mid_dot.pos_x + right_dot.pos_x)/3,
    (left_dot.pos_y + mid_dot.pos_y + right_dot.pos_y)/3);

    return geom_mid;
}

istream& operator>>(istream& chten, triangle& tria)
{
    pointer12 left_dot, mid_dot, right_dot;
    chten >> left_dot >> mid_dot >> right_dot;

    tria = triangle(left_dot, mid_dot, right_dot);

    return chten;
}

ostream& operator<<(ostream& vivod, const triangle& tria)
{
    vivod << tria.left_dot << " " <<  tria.mid_dot << " " << tria.right_dot;

    return vivod;
}