#include "eleven.h"

using namespace std;

ll Eleven::get_value() {return num[0];}

string Eleven::get_stringified() 
{
    string gicha = "";

    for (int i = 0; i < size; i++) 
    {
        gicha += num[size - i - 1];
    }

    return gicha;
}

ll Eleven::get_size() {return size;}