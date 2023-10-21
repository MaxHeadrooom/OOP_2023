#include "six_ugl.h"
#include <bits/stdc++.h>

using namespace std;

six_ugl::six_ugl(const pointer12& left_down_dot, const pointer12& left_mid_dot, const pointer12& left_up_dot,
const pointer12& right_up_dot, const pointer12& right_mid_dot, const pointer12& right_down_dot)
{
    this->storona = sqrt((left_down_dot.pos_x - right_down_dot.pos_x)*(left_down_dot.pos_x - right_down_dot.pos_x)
    + (left_down_dot.pos_y - right_down_dot.pos_y) * (left_down_dot.pos_y - right_down_dot.pos_y));

    if (storona <= 0)
        throw invalid_argument("It's not a six_ugl");
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}

six_ugl::six_ugl(const six_ugl& other) noexcept
{
    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_dot = other.left_mid_dot;
    this->left_up_dot = other.left_up_dot;
    this->right_down_dot = other.right_down_dot;
    this->right_mid_dot = other.right_mid_dot;
    this->right_up_dot = other.right_up_dot;
}

six_ugl::six_ugl(six_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_dot = move(other.left_mid_dot);
    this->left_up_dot = move(other.left_up_dot);
    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_dot = move(other.right_mid_dot);
    this->right_up_dot = move(other.right_up_dot);
}

six_ugl& six_ugl::operator=(const six_ugl& other) noexcept
{
    //this - tekuschiy ob'ect
    if (this == &other)//oznachaet cto uje est, t.e. prisvaevaet sam sebe, poetomu uje est'
        return *this;

    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_dot = other.left_mid_dot;
    this->left_up_dot = other.left_up_dot;
    this->right_down_dot = other.right_down_dot;
    this->right_mid_dot = other.right_mid_dot;
    this->right_up_dot = other.right_up_dot;

    return *this;
}

six_ugl& six_ugl::operator=(six_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_dot = move(other.left_mid_dot);
    this->left_up_dot = move(other.left_up_dot);
    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_dot = move(other.right_mid_dot);
    this->right_up_dot = move(other.right_up_dot);

    return *this;
}

bool six_ugl::operator==(const six_ugl& other)
{
    if (this->left_down_dot == other.left_down_dot and this->left_mid_dot == other.left_mid_dot and
    this->left_up_dot == other.left_up_dot and this->right_up_dot == other.right_up_dot and
    this->right_mid_dot == other.right_mid_dot and this->right_down_dot == other.right_down_dot)
        return true;
    return false;
}

double six_ugl::calculate_S()
{
    return 3*sqrt(3)*storona*storona/2;
}

pointer12 six_ugl::calculate_mid()
{
    pointer12 geom_mid((left_up_dot.pos_x + right_up_dot.pos_x +
    left_mid_dot.pos_x + right_mid_dot.pos_x + left_down_dot.pos_x + right_down_dot.pos_x)/6 ,
    (left_up_dot.pos_y + right_up_dot.pos_y + left_mid_dot.pos_y + right_mid_dot.pos_y +
    left_down_dot.pos_y + right_down_dot.pos_y)/6);

    return geom_mid;
}

istream& operator>>(istream& chten, six_ugl& sixxx_ugl)
{
    chten >> sixxx_ugl.left_down_dot >> sixxx_ugl.left_mid_dot >> sixxx_ugl.left_up_dot >>
    sixxx_ugl.right_down_dot >> sixxx_ugl.right_mid_dot >> sixxx_ugl.right_up_dot;

    return chten;
}

ostream& operator<<(ostream& vivod, const six_ugl& sixxx_ugl)
{
    vivod << sixxx_ugl.left_down_dot << " " << sixxx_ugl.left_mid_dot << " " <<sixxx_ugl.left_up_dot <<
    " " << sixxx_ugl.right_down_dot << " " << sixxx_ugl.right_mid_dot << " " << sixxx_ugl.right_up_dot; 

    return vivod;
}