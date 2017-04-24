#include <cstdio>
#include <algorithm>
 
#define MAXN 1009

using namespace std;
 
inline bool ri(int *n)
{
    char ch;
    bool negative = false;
    while ((ch = getchar_unlocked()) < '-');
    if (ch == '-') {
            negative = true;
            ch = getchar_unlocked();
    }
    for (*n = ch - '0'; (ch = getchar_unlocked()) >= '0'; *n = ((*n * 5) << 1) + ch - '0');
    if (negative) *n = -*n;
    return true;
}

 
