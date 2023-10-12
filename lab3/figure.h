#include <bits/stdc++.h>
#include "point.h"

using namespace std;

using ll = long long;

class Figure
{
    public:
        virtual ~Figure() = default;

        virtual double calc_mid() const = 0;
        virtual double calc__loc_S() const = 0;
        virtual double calc_pub_S() const = 0;

    protected:
        Figure() = default;
};
