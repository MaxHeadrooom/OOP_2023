#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class eight_ugl : public Figure
{
    //tret'ya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer left_down_dot;
        pointer left_mid_down_dot;
        pointer left_mid_up_dot;
        pointer left_up_dot;
        pointer right_up_dot;
        pointer right_mid_down_dot;
        pointer right_mid_up_dot;
        pointer right_down_dot;

        double storona;
        
    public:
        eight_ugl() = default;

        eight_ugl(const pointer&, const pointer&, const pointer&, const pointer&, const pointer&,
        const pointer&, const pointer&, const pointer&);
        
        eight_ugl(const eight_ugl&) noexcept;
        eight_ugl(eight_ugl&&) noexcept;

        eight_ugl& operator=(const eight_ugl&) noexcept;
        eight_ugl& operator=(eight_ugl&&) noexcept;

        bool operator==(const eight_ugl&);

        virtual double calculate_S();
        virtual pointer calculate_mid();

        friend istream& operator>>(istream&, eight_ugl&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const eight_ugl& eighttt_ugl);

        virtual ~eight_ugl() = default; 
};