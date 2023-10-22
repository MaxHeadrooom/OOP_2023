#include <bits/stdc++.h>
#include "figure.h"

using namespace std;

using ll = long long;

class arrayy
{
    private:
        Figure** figuri; // s * ne rabotaet **
        ll size;

    public:
        arrayy();
        arrayy(ll size);
        virtual ~arrayy() = default;

        Figure* operator[](ll pos); // obrasch k elem

        void push_back(ll pos, Figure* fig);
        void pop(ll pos);
        double calc_all_s();
};