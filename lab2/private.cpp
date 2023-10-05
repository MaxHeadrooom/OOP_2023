#include "eleven.h"

using namespace std;
 
using ll = long long; 

void Eleven::resize()
{
    unsigned char* resized = new unsigned char[size]{};

    for (int i = 0; i < size; i++)
    {
        resized[i] = num[i];
    }

    delete num;
    num = resized;
}
