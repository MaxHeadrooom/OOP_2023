#include <bits/stdc++.h>
#include "func.h"

using namespace std;

bool func(string& s)
{
    stack<char>st;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            st.push('(');
        }
        else
        {
            if (st.size() != 0)
                st.pop();
            else
                return false;
        }
    }
    if (st.size() == 0)
        return true;
    else
        return false;
}