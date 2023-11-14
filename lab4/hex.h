#pragma once

#include <iostream>
#include <vector>
#include <utility> // для pair
#include <memory>

using ll = long long;

template <typename T>
class Hexagon : public Figure
{
    using typ = std::pair<T, T>[6];
    public:
        typ points;
        ll count = 6;

        Hexagon() = default;
        Hexagon(typ& v)
        {
            for (int i = 0; i < 6; i++)
                points[i] = v[i];
        }
        ~Hexagon() = default;

        Hexagon<T>& operator=(const Hexagon<T>& other)
        {
            points = other.points;

            return *this;
        }

        Hexagon<T>& operator=(Hexagon<T>&& other)
        {
            points = std::move(other.points);

            return *this;
        }

        operator double() const 
        {
            return (double)fig::calculate_S(*this);
        }   

        friend std::istream& operator>>(std::istream& chten, Hexagon<T>& hex)
        {
            for (int i = 0; i < 6; i++)
            {
                chten >> hex.points[i].first >> hex.points[i].second;
            }
            return chten;
        }

        friend std::ostream& operator<<(std::ostream& vivod, Hexagon<T>& hex)
        {
            for (int i = 0; i < 6; i++)
            {
                vivod << hex.points[i].first << hex.points[i].second;
            }
            return vivod;
        }
};

template <typename T>
bool operator==(const Hexagon<T>& right, const Hexagon<T>& left)
{
    return right.points[0] == left.points[0] and right.points[1] == left.points[1] and
    right.points[2] == left.points[2] and right.points[3] == left.points[3] and
    right.points[4] == left.points[4] and right.points[5] == left.points[5];
}

