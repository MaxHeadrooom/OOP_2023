#include <bits/stdc++.h>
#include "array.h"
#include "figure.h"

using namespace std;

using ll = long long;

arrayy::arrayy()
{
    this->size = 16;
    this->figuri = new Figure*[size];

    for (int i = 0; i < 16; i++)
    {
        figuri[i] = nullptr;
    }
}

arrayy::arrayy(ll sizee)
{
    this->size = sizee;
    this->figuri = new Figure*[sizee];

    for (int i = 0; i < sizee; i++)
    {
        figuri[i] = nullptr;
    }
}

Figure* arrayy::operator[](ll pos)
{
    if (pos >= size)
        throw   invalid_argument("Out of range");

    return figuri[pos];
}

void arrayy::push_back(ll pos, Figure* f)
{
    if (pos > size)
        throw invalid_argument("Out of range when push_back");

    if (figuri[pos] == nullptr)
        figuri[pos] = f;
    else
        throw runtime_error("I can't push because place is alredy exist");
}

void arrayy::pop(ll pos)
{
    if (pos < 0 or pos > size)
        throw invalid_argument("Out of range when pop");
    
    if (figuri[pos] != nullptr)
    {
        delete figuri[pos];
        figuri[pos] = nullptr;
    }
}

double arrayy::calc_all_s()
{
    double s = 0.0;

    for (int i = 0; i < size; i++)
    {
        if (figuri[i] != nullptr)
        {
            s += figuri[i]->calculate_s();
        }
    }
}

arrayy::~arrayy()
{
    for (int i = 0; i < size; i++)
    {
        delete figuri[i];
    }
    delete[] figuri;
    size = 0;
}