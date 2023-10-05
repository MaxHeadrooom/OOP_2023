#include "eleven.h"

using namespace std;

using ll = long long;

bool Eleven::operator>(const Eleven &other)
{
    if (size > other.size)
        return true;

    if (other.size > size)
        return false;

    for (size_t i = size - 1; i < size; i--)
    {
        if (num[i] > other.num[i])
            return true;
        if (other.num[i] > num[i])
            return false;
    }

    return false;
}

bool Eleven::operator<(const Eleven &other)
{
    if (size < other.size)
        return true;

    if (other.size < size)
        return false;

    for (size_t i = size - 1; i < size; i--)
    {
        if (num[i] < other.num[i])
            return true;
        if (other.num[i] < num[i])
            return false;
    }

    return false;
}

bool Eleven::operator==(const Eleven &other)
{
    if (size != other.size)
        return false;

    for (int i = 0; i < size; i++)
    {
        if (num[i] != other.num[i])
            return false;
    }

    return true;
}
