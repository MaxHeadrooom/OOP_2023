#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class triangle : public Figure
{
    //vtoraya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer left_dot;
        pointer mid_dot;
        pointer right_dot;

        double storona;
        
    public:
        triangle() = default;

        triangle(const pointer&, const pointer&, const pointer&);
        
        triangle(const triangle&) noexcept;
        triangle(triangle&&) noexcept;

        triangle& operator=(const triangle&) noexcept;
        triangle& operator=(triangle&&) noexcept;

        bool operator==(const triangle&);

        virtual double calculate_S();
        virtual pointer calculate_mid();

        friend istream& operator>>(istream&, triangle&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const triangle& sixxx_ugl);

        virtual ~triangle() = default; 
};