#include "eleven.h"

using namespace std;

using ll = long long;

Eleven Eleven::operator+(const Eleven &other)
{
    ll maxSize, minSize;

    if (size >= other.size) 
    {
        maxSize = size;
        minSize = other.size;
    } 
    else 
    {
        maxSize = other.size;
        minSize = size;
    }

    Eleven result = Eleven(maxSize);  
    ll transfer = 0, remainder, num1, num2, sum;

    for (int i = 0; i < minSize; i++) 
    {
        if (num[i] == 65)
            num1 = 10;
        else
            num1 = num[i] - 48; // 48 - '0', 49 - '1', 65 - 'A'

        if (other.num[i] == 65)
            num2 = 10;
        else
            num2 = other.num[i] - 48;

        sum = num1 + num2 + transfer;
        transfer = sum / 11;
        remainder = sum % 11;
        if (remainder == 10)
            result.num[i] = 'A';
        else
            result.num[i] = remainder + 48;
    }

    for (int i = minSize; i < maxSize; i++) 
    {
        if (size >= other.size) 
        {
            if (num[i] == 65)
                num1 = 10;
            else
                num1 = num[i] - 48; 
        }
        else
        {
            if (other.num[i] == 65)
                num2 = 10;
            else
                num2 = other.num[i] - 48;
        }

        sum = num1 + transfer;
        transfer = sum / 11;
        remainder = sum % 11;
        if (remainder == 10)
            result.num[i] = 'A';
        else
            result.num[i] = remainder + 48;
    }

    if (transfer != 0) 
    {
        ++result.size;
        result.resize();
        result.num[maxSize] = transfer + 48;
    }

    return result;
}

Eleven Eleven::operator-(const Eleven &other)
{
    if (other.size > size)
        throw invalid_argument("The result of subtraction would be negative");

    Eleven result = Eleven(*this);

    for (size_t i = other.size - 1; i < other.size; i--) 
    {
        if (num[i] == 'A' and other.num[i] != 'A')
        {
            if (other.num[i] != 0)
                result.num[i] = 10 - other.num[i] + 48;
            else
                result.num[i] = num[i];
        }
        else
        {
            ll fl = 0; //tupo, kogda u menya bilo v 1 ife, prosto pereprigival if, hotya doljen bil bit'
            if (other.num[i] == 'A')
                fl++;
            if (num[i] == 'A')
                fl++;
                
            if (fl == 2)
                result.num[i] = 48;
            else
            {
                if (other.num[i] == 'A')
                    result.num[i] = num[i] - 10 + 48;
                else
                    result.num[i] = num[i] - other.num[i] + 48;
            }
        }
        if (result.num[i] < 48) 
        {
            result.num[i] = 'A';

            ll pos = i + 1;

            while (pos != result.size and result.num[pos] == 48) 
            {
                result.num[pos] = 'A';
                pos += 1;
            }

            if (pos == result.size)
                throw invalid_argument("The result of subtraction would be negative");

            --result.num[pos];

            if (pos + 1 == result.size and result.num[pos] == 48)
            {
                --result.size;
                result.resize();
            }
        }
    }

    return result;
}

Eleven& Eleven::operator=(const Eleven &other)
{
    size = other.size;
    num = new unsigned char[size];

    for (int i = 0; i != size; i++)
    {
        num[i] = other.num[i];
    }

    return *this;
}