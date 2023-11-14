#include "figure.h"
#include "functions.h"

#include <iostream>
#include <utility>
#include <memory>// для shared_ptr
#include <stdexcept>//throw

using ll = long long;

template<typename T>
class Array
{
private:
    std::shared_ptr<T[]> figuri = nullptr;
    ll size = 0;

 public:
    Array() = default;

    Array(ll sizee) : size(sizee)
    {
        figuri = std::shared_ptr<T[]>(new T[size]);

        figuri.reset(new T[size]);
    }

    ~Array() = default;

    Array operator=(const Array<T>& figuri);


    void push_back(ll pos, T fig)
    {
        if (pos > size)
        throw std::invalid_argument("Out of range when push_back");

        if (figuri[pos] == nullptr)
        figuri[pos] = fig;
        else
        throw std::runtime_error("I can't push because place is alredy exist");
    }


    void pop(ll pos)
    {
        if (pos < 0 or pos > size)
        throw std::invalid_argument("Out of range when pop");

        if (figuri[pos] != nullptr)
        {
        delete figuri[pos];
        figuri[pos] = nullptr;
        }
    }


    double calc_all_s()
    {
        double s = 0.0;

        for (int i = 0; i < size; i++)
        {
            s += figuri[i].calculate_S();
        }

        return s;
    }
    

    T& operator[](ll index);
};

template <class T>
inline T& Array<T>::operator[](ll index)
{
    if (index >= size)
        throw std::invalid_argument("The array index is out of range");

    return figuri.get()[index];
}