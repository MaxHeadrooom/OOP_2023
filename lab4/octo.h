#pragma once

#include <iostream>
#include <vector>
#include <utility> // для pair
#include <memory>

using ll = long long;

template <typename T>
class Octagon : public Figure
{
    using typ = std::pair<T, T>[8];
    public:
        typ points;
        ll count = 8;

        Octagon() = default;
        Octagon(typ& v)
        {
            for (int i = 0; i < 8; i++)
                points[i] = v[i];
        }
        ~Octagon() = default;

        Octagon<T>& operator=(const Octagon<T>& other)
        {
            points = other.points;

            return*this;
        }

        Octagon<T>& operator=(Octagon<T>&& other)
        {
            points = std::move(other.points);

            return*this;
        }

        operator double() const 
        {
            return (double)fig::calculate_S(*this);
        }   

        friend std::istream& operator>>(std::istream& chten, Octagon<T>& tria)
        {
            for (int i = 0; i < 8; i++)
            {
                chten >> tria.points[i].first >> tria.points[i].second;
            }
            return chten;
        }

        friend std::ostream& operator<<(std::ostream& vivod, Octagon<T>& tria)
        {
            for (int i = 0; i < 8; i++)
            {
                vivod << tria.points[i].first << tria.points[i].second;
            }
            return vivod;
        }
};

template <typename T>
bool operator==(const Octagon<T>& right, const Octagon<T>& left)
{
    return right.points[0] == left.points[0] and right.points[1] == left.points[1] and
    right.points[2] == left.points[2] and right.points[3] == left.points[3] and
    right.points[4] == left.points[4] and right.points[5] == left.points[5] and
    right.points[6] == left.points[6] and right.points[7] == left.points[7];
}
