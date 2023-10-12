#include "six_ugl.h"
#include <bits/stdc++.h>

using namespace std;

six_ugl::six_ugl(const pointer& left_down_dot, const pointer& left_mid_dot, const pointer& left_up_dot,
const pointer& right_up_dot, const pointer& right_mid_dot, const pointer& right_down_dot)
{
    storona = (left_up_dot.pos_x - right_up_dot.pos_x)*(left_up_dot.pos_x - right_up_dot.pos_x);
    //esli ne delat' public v point.h pochemu-to ne rabotaet
}