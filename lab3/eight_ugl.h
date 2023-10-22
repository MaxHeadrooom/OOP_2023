
#include "figure.h"
#include <bits/stdc++.h>

using namespace std;

class eight_ugl : public Figure
{
    //tret'ya cartinka v poiske nachinaem s levogo nijnego i protiv chasovoy
    private:
        pointer12 left_down_dot;
        pointer12 left_mid_down_dot;
        pointer12 left_mid_up_dot;
        pointer12 left_up_dot;
        pointer12 right_up_dot;
        pointer12 right_mid_down_dot;
        pointer12 right_mid_up_dot;
        pointer12 right_down_dot;

        double storona;
        
    public:
        eight_ugl() = default;

        eight_ugl(const pointer12&, const pointer12&, const pointer12&, const pointer12&, const pointer12&,
        const pointer12&, const pointer12&, const pointer12&);
        
        eight_ugl(const eight_ugl&) noexcept;
        eight_ugl(eight_ugl&&) noexcept;

        eight_ugl& operator=(const eight_ugl&) noexcept;
        eight_ugl& operator=(eight_ugl&&) noexcept;

        bool operator==(const eight_ugl&);

        virtual double calculate_s() const;
        virtual pointer12 calculate_mid() const;

        friend istream& operator>>(istream&, eight_ugl&);//ya dumal chto i bez frienda doljo rabotat'
        friend ostream& operator<<(ostream& vivod, const eight_ugl& eighttt_ugl);

        virtual ~eight_ugl() = default; 
};