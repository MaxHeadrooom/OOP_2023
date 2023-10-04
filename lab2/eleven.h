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

        ll get_value();
        string get_stringified();
        ll get_size();

    private:
        ll size;
        unsigned char *num;
};