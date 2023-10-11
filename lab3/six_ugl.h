#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class six_ugl : public Figure
{
    //vtoraya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        point left_mid_dot;
        point left_down_dot;
        point left_up_dot;
        point right_up_dot;
        point right_mid_dot;
        point right_down_dot;

        double storona;
        
    public:
        six_ugl() = default;

        six_ugl(const point&, const point&, const point&, const point&,
        const point&, const point&, const point&, const point&);
        
        virtual ~six_ugl() = default; 
};