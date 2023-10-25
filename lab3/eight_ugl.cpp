#include "eight_ugl.h"
#include <bits/stdc++.h>

using namespace std;

eight_ugl::eight_ugl(const pointer12& left_down_dot, const pointer12& left_mid_down_dot, const pointer12&
left_mid_up_dot, const pointer12& left_up_dot, const pointer12& right_up_dot, const pointer12& right_mid_up_dot,
const pointer12& right_mid_down_dot, const pointer12& right_down_dot)
{
    this->storona = sqrt((left_up_dot.pos_x - right_up_dot.pos_x)*(left_up_dot.pos_x - right_up_dot.pos_x)
    + (left_up_dot.pos_y - right_up_dot.pos_y) * (left_up_dot.pos_y - right_up_dot.pos_y));

    if (storona <= 0)
        throw invalid_argument("It's not a eight_ugl");
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}

eight_ugl::eight_ugl(const eight_ugl& other) noexcept
{
    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_down_dot = other.left_mid_down_dot;
    this->left_mid_up_dot = other.left_mid_up_dot;
    this->left_up_dot = other.left_up_dot;

    this->right_down_dot = other.right_down_dot;
    this->right_mid_down_dot = other.right_mid_down_dot;
    this->right_mid_up_dot = other.right_mid_up_dot;
    this->right_up_dot = other.right_up_dot;
}

eight_ugl::eight_ugl(eight_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_down_dot = move(other.left_mid_down_dot);
    this->left_mid_up_dot = move(other.left_mid_up_dot);
    this->left_up_dot = move(other.left_up_dot);

    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_down_dot = move(other.right_mid_down_dot);
    this->right_mid_up_dot = move(other.right_mid_up_dot);
    this->right_up_dot = move(other.right_up_dot);
}

eight_ugl& eight_ugl::operator=(const eight_ugl& other) noexcept
{
    //this - tekuschiy ob'ect
    if (this == &other)//oznachaet cto uje est, t.e. prisvaevaet sam sebe, poetomu uje est'
        return *this;

    //prisvaivanie iz other v tekuschee - this
    this->left_down_dot = other.left_down_dot;
    this->left_mid_down_dot = other.left_mid_down_dot;
    this->left_mid_up_dot = other.left_mid_up_dot;
    this->left_up_dot = other.left_up_dot;

    this->right_down_dot = other.right_down_dot;
    this->right_mid_down_dot = other.right_mid_down_dot;
    this->right_mid_up_dot = other.right_mid_up_dot;
    this->right_up_dot = other.right_up_dot;

    return *this;
}

eight_ugl& eight_ugl::operator=(eight_ugl&& other) noexcept
{
    //imenno peremeschenie iz other v tekuschee - this
    //move - peredelivaet lvalue v rvalue
    this->left_down_dot = move(other.left_down_dot);
    this->left_mid_down_dot = move(other.left_mid_down_dot);
    this->left_mid_up_dot = move(other.left_mid_up_dot);
    this->left_up_dot = move(other.left_up_dot);

    this->right_down_dot = move(other.right_down_dot);
    this->right_mid_down_dot = move(other.right_mid_down_dot);
    this->right_mid_up_dot = move(other.right_mid_up_dot);
    this->right_up_dot = move(other.right_up_dot);

    return *this;
}

bool eight_ugl::operator==(const eight_ugl& other)
{
    if (this->left_down_dot == other.left_down_dot and this->left_mid_down_dot == other.left_mid_down_dot
    and this->left_mid_up_dot == other.left_mid_up_dot and this->left_up_dot == other.left_up_dot and
    this->right_down_dot == other.right_down_dot and this->right_mid_down_dot == other.right_mid_down_dot
    and this->right_mid_up_dot == other.right_mid_up_dot and this->right_up_dot == other.right_up_dot)
        return true;
    return false;
}

double eight_ugl::calculate_s() const
{
    return (2*storona*storona*(sqrt(2) + 1));
}

pointer12 eight_ugl::calculate_mid() const
{
    pointer12 geom_mid((left_down_dot.pos_x + left_mid_down_dot.pos_x + left_mid_up_dot.pos_x + 
    left_up_dot.pos_x + right_down_dot.pos_x + right_mid_down_dot.pos_x + right_mid_up_dot.pos_x + 
    right_up_dot.pos_x)/8,(left_down_dot.pos_y + left_mid_down_dot.pos_y + left_mid_up_dot.pos_y + 
    left_up_dot.pos_y + right_down_dot.pos_y + right_mid_down_dot.pos_y + right_mid_up_dot.pos_y + 
    right_up_dot.pos_y)/8);

    return geom_mid;
}

istream& operator>>(istream& chten, eight_ugl& eighttt_ugl)
{
    chten >> eighttt_ugl.left_down_dot >> eighttt_ugl.left_mid_down_dot >> eighttt_ugl.left_mid_up_dot >>
    eighttt_ugl.left_up_dot >> eighttt_ugl.right_up_dot >> eighttt_ugl.right_mid_up_dot >>
    eighttt_ugl.right_mid_down_dot >> eighttt_ugl.right_down_dot;

    return chten;
}

ostream& operator<<(ostream& vivod, const eight_ugl& eighttt_ugl)
{
    vivod << eighttt_ugl.left_down_dot << " " << eighttt_ugl.left_mid_down_dot << " " << 
    eighttt_ugl.left_mid_up_dot << " " << eighttt_ugl.left_up_dot << " " <<
    eighttt_ugl.right_up_dot << " " << eighttt_ugl.right_mid_up_dot << " " <<
    eighttt_ugl.right_mid_down_dot << " " << eighttt_ugl.right_down_dot;

    return vivod;
}

eight_ugl::~eight_ugl()
{
    storona = 0;
}