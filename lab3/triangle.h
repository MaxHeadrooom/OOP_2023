#pragma once

#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class triangle : public Figure
{
    //vtoraya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer12 left_dot;
        pointer12 mid_dot;
        pointer12 right_dot;

        double storona;

    public:
        triangle() = default;

        triangle(const pointer12&, const pointer12&, const pointer12&);
        
        triangle(const triangle&) noexcept;
        triangle(triangle&&) noexcept;

        triangle& operator=(const triangle&) noexcept;
        triangle& operator=(triangle&&) noexcept;

        bool operator==(const triangle&);

        virtual double calculate_s() const;
        virtual pointer12 calculate_mid() const;

        friend istream& operator>>(istream&, triangle&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const triangle& sixxx_ugl);

        virtual ~triangle(); 
};