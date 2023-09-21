#include <bits/stdc++.h>

using namespace std;

bool funcii(string& s)
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