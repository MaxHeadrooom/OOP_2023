#include <iostream>

using namespace std;

using ll = long long;

class pointer 
{
    private:
        double pos_x = 0, pos_y = 0;

    public:
        pointer() = default;//net dop peystviy
        
        pointer(double, double);
        pointer(const initializer_list<double>&);
        pointer(const pointer &other);

        const double get_x();
        const double get_y();

        virtual ~pointer() = default;
};
