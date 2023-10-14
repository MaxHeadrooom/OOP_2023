#include <bits/stdc++.h>
#include "point.h"

using namespace std;

using ll = long long;

class Figure
{
    public:
        virtual ~Figure() = default;

        virtual double calculate_mid() const = 0;
        virtual double calculate_s() const = 0;
        virtual double calculate_all_S() const = 0;

    protected:
        Figure() = default;
};
