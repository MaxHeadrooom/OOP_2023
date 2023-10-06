#include "eleven.h"

using namespace std;

using ll = long long;

ll bin_pow(ll a, ll n)
{
    ll res = 1;

    while (n > 0)
    {
        if (n%2==1)
        {
            res = res*a;
        }
        a=(a*a);
        n/=2;
    }

    return res;
}


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

    ll chisl_1 = 0, step = 0;

    for (int i = 0; i < other.size; i++)
    {
        chisl_1 += ((other.num[i])- 48)*bin_pow(11, step);
        step++;
    }

    ll chisl_2 = 0;

    step = 0;

    for (int i = 0; i < size; i++)
    {
        chisl_2 += ((num[i])- 48)*bin_pow(11, step);
        step++;
    }

    ll res = chisl_2 - chisl_1;

    string s = "";

    if (res == 0)
    {
        s = "0"; 
    }

    while (res > 0)
    {
        if (res % 11 == 10)
            s += "A";
        else
            s += to_string(res%11);
        res /= 11;
    }

    reverse(s.begin(), s.end());

    result = Eleven(s);

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