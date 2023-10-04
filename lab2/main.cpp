#include <bits/stdc++.h>
#include "eleven.h"

using namespace std;

int main()
{
    try
    {
        string s1, s2;

        cin >> s1 >> s2;

        Eleven num1 = Eleven(s1);
        Eleven num2 = Eleven(s2);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}