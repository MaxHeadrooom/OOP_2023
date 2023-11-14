#pragma once

#include <iostream>
#include <utility>
#include <memory>
#include <cmath>

namespace fig {

template <typename T>
std::pair<double, double> calculate_mid(const T& figure) 
{
    std::pair<double, double> p = {0, 0};

    long long size = 0; 

    for (std::pair<double, double> point : figure.points) 
    {
        p.first += point.first;
        p.second += point.second;
        size++;
    }

    p.first /= size;
    p.second /= size;
    return p;
}

template <typename T> 
double calculate_S(const T& figura) 
{
    double side = std::sqrt(std::pow(figura.points[0].first - figura.points[1].first, 2)
    + std::pow(figura.points[0].second - figura.points[1].second, 2));
    double perimeter = figura.count * side;
    double angle = 360 / figura.count * 0.5;
    double apotheme = side / (2 * std::tan(std::acos(-1) / figura.count));
    return perimeter * apotheme / 2;
}

} //namespace fig