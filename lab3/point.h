#include <bits/stdc++.h>
#pragma once

using namespace std;

using ll = long long;

class pointer12 
{
    private:

    public:
        double pos_x = 0, pos_y = 0;
        pointer12();
        
        pointer12(double, double);
        pointer12(const initializer_list<double>&);
        pointer12(const pointer12 &other);

        const double get_x();
        const double get_y();

        bool operator==(const pointer12& other);

        friend istream& operator>>(istream&, pointer12&);
        friend ostream& operator<<(ostream&, const pointer12&);

        virtual ~pointer12() = default;
};
