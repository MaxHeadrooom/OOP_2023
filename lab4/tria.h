#pragma once

#include <iostream>
#include <vector>
#include <utility> // для pair
#include <memory>

using ll = long long;

template <typename T>
class Triangle : public Figure
{
    using typ = std::pair<T, T>[3];
    public:
        typ points;
        ll count = 3;

        Triangle() = default;
        Triangle(typ& v)
        {
            for (int i = 0; i < 3; i++)
                points[i] = v[i];
        }
        ~Triangle() = default;

        Triangle<T>& operator=(const Triangle<T>& other)
        {
            points = other.points;

            return*this;
        }

        Triangle<T>& operator=(Triangle<T>&& other)
        {
            points = std::move(other.points);

            return*this;
        }

        operator double() const 
        {
            return (double)fig::calculate_S(*this);
        }   

        friend std::istream& operator>>(std::istream& chten, Triangle<T>& tria)
        {
            for (int i = 0; i < 3; i++)
            {
                chten >> tria.points[i].first >> tria.points[i].second;
            }
            return chten;
        }

        friend std::ostream& operator<<(std::ostream& vivod, Triangle<T>& tria)
        {
            for (int i = 0; i < 3; i++)
            {
                vivod << tria.points[i].first << tria.points[i].second;
            }
            return vivod;
        }
};

template <typename T>
bool operator==(const Triangle<T>& right, const Triangle<T>& left)
{
    return right.points[0] == left.points[0] and right.points[1] == left.points[1] and
    right.points[2] == left.points[2];
}

