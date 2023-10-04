#include "eleven.h"
#include <bits/stdc++.h>

using namespace std;

Eleven::Eleven()//baza
{
    size = 0;
    num = new unsigned char[0];
}

Eleven::Eleven(const ll &n, unsigned char t)//zapolnenie n elmentov znach t
{
    if (t != 65)//bukva A v ASCII
    {
        if (t < 48 and t > 58)
        {
            cout << "gg, symbol just chilling, but not in 11 system";//mojno bilo cherez throw ili try cathc
            exit(0);
        }
    }

    size = n;
    num = new unsigned char[n];

    for (int i = 0; i < n; i++)
    {
        num[i] = t;
    }
}

Eleven::Eleven(const initializer_list<unsigned char> &t)
{
    size = t.size();
    num = new unsigned char[size];

    ll pos = size;

   for (const unsigned char &gicha : t) //pitalsya cherez t[i] ili cherez *(t[i]) ili cherez &(t)
   {
        if (gicha != 65)//bukva A v ASCII
        {
            if (gicha < 48 and gicha > 58)
            {
                cout << "gg, symbol just chilling, but not in 11 system";//mojno bilo cherez throw ili try cathc
                exit(0);
            }
        }
        num[pos - 1] = gicha;
        pos--;
   }
}

Eleven::Eleven(const string &t)
{
    size = t.size();
    num = new unsigned char[size];

    ll pos = size;

   for (const unsigned char &gicha : t) //pitalsya cherez t[i] ili cherez *(t[i]) ili cherez &(t)
   {
        if (gicha != 65)//bukva A v ASCII
        {
            if (gicha < 48 and gicha > 58)
            {
                cout << "gg, symbol just chilling, but not in 11 system";//mojno bilo cherez throw ili try cathc
                exit(0);
            }
        }
        num[pos - 1] = gicha;
        pos--;
   }
}

Eleven::Eleven(const Eleven &other)
{
    size  = other.size;
    num = new unsigned char [size];

    for (int i = 0; i < size; i++)
    {
        num[i] = other.num[i];
    }
}

Eleven::Eleven(Eleven &&other) noexcept
{
    size  = other.size;
    num = new unsigned char [size];

    for (int i = 0; i < size; i++)
    {
        num[i] = other.num[i];
    }
    delete other.num;
    other.size = 0;
}

Eleven::~Eleven() noexcept //prosto udalenie
{
    size = 0;
    delete num;
}