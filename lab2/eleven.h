#pragma once

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

class Eleven
{
public:
        Eleven();
        Eleven(const ll &n, unsigned char t = 0);
        Eleven(const initializer_list<unsigned char> &t);
        Eleven(const string &t);
        Eleven(const Eleven &other);
        Eleven(Eleven &&other) noexcept;
        virtual ~Eleven() noexcept;

    private:
        ll size;
        unsigned char *num;
};