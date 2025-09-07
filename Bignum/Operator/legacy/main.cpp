/* Given 2 non-negative big integer a, b (1000 digits), calculate:
    a + b
    a - b
    a * b
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int Input();
int Solve();

/* ============================================================================ */
/* ============================================================================ */

#define fi "BIGNUM.INP"
#define For(i,l,r) for(int i=l; i<=r; i++)
#define Ford(i,r,l) for(int i=r; i>=l; i--)
#define pb push_back
#define ll long long
const int infi = 2e9;
const int mod = 1e9;
const int maxn = 1000;
const int N = maxn+10;
typedef ll mang[N];
struct bignum   {
    mang x; int n;
    void init() {    For(i,1,maxn)   x[i] = 0;    }
    void tobig(char s[])    {
        n = strlen(s)-1;
        while (n>=0)    {
            int t = 0;
            For(i,max(0,n-8),n) t = t*10 + s[i]-'0';
            x[++x[0]] = t;
            n -= 9;
        }
        n = x[0];
    }
    void Output()  {
        printf("%i", x[n]);
        Ford(i,n-1,1)   {
            int t = mod/10-1;
            while (t>0 && x[i]<=t)  printf("0"),   t /= 10;
            printf("%i", x[i]);
        }
        printf("\n");
    }
};

bignum a, b, c;

/* ============================================================================ */
/* ============================================================================ */

int main()
{
    Input();
    Solve();
}

/* ============================================================================ */
/* ============================================================================ */

int Input()
{
    ios_base::sync_with_stdio(0);
//    freopen(fi, "r", stdin);
    char s[N];
    scanf("%s\n", &s);  a.tobig(s);
    scanf("%s", &s);    b.tobig(s);
}

/* ============================================================================ */

bignum operator+(bignum a, bignum b)
{
    bignum c;       c.init();    c.n = max(a.n,b.n);
    int nho = 0;
    For(i,1,c.n)    {
        c.x[i] = a.x[i]+b.x[i]+nho;
        nho = c.x[i]/mod;    c.x[i] %= mod;
    }
    if (nho)    c.x[++c.n] = nho;
    while (c.n>1 && c.x[c.n]==0)    c.n--;
    return c;
}

/* ---------------------------------- */

int Bigger(bignum a, bignum b)
{
    if (a.n > b.n)  return 1;
    if (a.n < b.n)  return 0;
    Ford(i,a.n,1)   {
        if (a.x[i] > b.x[i])    return 1;
        if (a.x[i] < b.x[i])    return 0;
    }
    return 0;
}

/* - - - - - - - - */

bignum operator-(bignum a, bignum b)
{
    if (Bigger(b,a))   swap(a,b),   printf("-");
    bignum c;    c.init();    c.n = a.n;
    int nho = 0;

    For(i,1,a.n)    {
        c.x[i] = (a.x[i]-b.x[i]-nho + mod)%mod;
        if (a.x[i]-b.x[i]-nho < 0)  nho = 1;    else nho = 0;
    }

    while (c.n>1 && c.x[c.n]==0)    c.n--;
    return c;
}

/* ---------------------------------- */

bignum operator*(bignum a, bignum b)
{
    bignum c, t;    c.init();
    ll nho = 0;
    For(j,1,b.n)    {
        t.init();   t.n = j-1;    nho = 0;
        For(i,1,a.n)    {
            t.x[++t.n] = (a.x[i]*b.x[j]+nho)%mod;
            nho = (a.x[i]*b.x[j]+nho)/mod;
        }
        if (nho)    t.x[++t.n] = nho;
        c = c+t;
    }

    while (c.n>1 && c.x[c.n]==0) c.n--;
    return c;
}

/* ---------------------------------- */

int Solve()
{
    c = a+b;
    c.Output();

    c = a-b;
    c.Output();

    c = a*b;
    c.Output();
}
