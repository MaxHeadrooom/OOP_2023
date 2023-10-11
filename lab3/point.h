#include <figure.h>
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

class point 
{
    private:
        double pos_x = 0, pos_y = 0;

    public:
        point() = default;//net dop peystviy
        
        point(double, double);
        point(const initializer_list<double>&);
        point(const point &other);

        const double get_x();
        const double get_y();

        virtual ~point() = default;
};
