#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class six_ugl : public Figure
{
    //vtoraya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer left_mid_dot;
        pointer left_down_dot;
        pointer left_up_dot;
        pointer right_up_dot;
        pointer right_mid_dot;
        pointer right_down_dot;

        double storona;
        
    public:
        six_ugl() = default;

        six_ugl(const pointer&, const pointer&, const pointer&, const pointer&,
        const pointer&, const pointer&, const pointer&, const pointer&);
        
        virtual ~six_ugl() = default; 
};