#include <bits/stdc++.h>

using namespace std;

using ll = long long;

class pointer 
{
    private:

    public:
        double pos_x = 0, pos_y = 0;
        pointer() = default;//net dop deystviy
        
        pointer(double, double);
        pointer(const initializer_list<double>&);
        pointer(const pointer &other);

        const double get_x();
        const double get_y();

        bool operator==(const pointer& other);

        friend istream& operator>>(istream&, pointer&);
        friend ostream& operator<<(ostream&, const pointer&);

        virtual ~pointer() = default;
};
