#include <bits/stdc++.h>
#include "point.h"
#pragma once

using namespace std;

using ll = long long;

class Figure
{
    public:
        Figure() = default;
        virtual ~Figure() = default;

        virtual pointer12 calculate_mid() const = 0;
        virtual double calculate_s() const = 0;
        //virtual double calculate_all_S() const = 0;

    protected:
        
};
