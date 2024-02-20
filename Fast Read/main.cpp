/* An improved version of scanf for reading integers.*/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

/* ============================================================================ */
/* ============================================================================ */

#define fi "TEST.INP"
#define fo ""
#define For(i,l,r) for(int i=(int)l; i<=(int)r; i++)
#define ll long long
const int maxn = 1e6;    const int N = maxn+10;
typedef int mang[N];
mang a;    int n;

/* ============================================================================ */
/* ============================================================================ */

void fast_read(int &x)
{
    char c = getchar();
    while (c == ' ' || c == '\n')    c = getchar();
    x = 0;
    while (c != ' ' && c != '\n' && c != EOF) {
        x = x * 10 + c - '0';
        c = getchar();
    }
}

/* ============================================================================ */
/* ============================================================================ */


int main()
{
    freopen(fi, "r", stdin);//    freopen(fo, "w", stdout);
    scanf("%i", &n);
//    For(i,1,n)  scanf("%i", &a[i]);
    For(i,1,n)  fast_read(a[i]);
    For(i,1,n)  printf("%i\n", a[i]);
}

