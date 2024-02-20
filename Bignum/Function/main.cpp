/* Given 2 big integers a, b (1000 digits), calculate:
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
mang a, b, c;

/* ============================================================================ */
/* ============================================================================ */

int main()
{
    Input();
    Solve();
}

/* ============================================================================ */
/* ============================================================================ */

int ToBig(char s[], mang a)
{
    int n = strlen(s)-1;  a[0] = 0;
    while (n>=0)    {
        ll x = 0;
        For(i,max(0,n-8),n)    x = x*10 + s[i]-'0';
        a[++a[0]] = x;
        n -= 9;
    }
}

/* ---------------------------------- */

int Output(mang a)
{
    printf("%i", a[a[0]]);
    Ford(i,a[0]-1,1)    {
        ll t = mod/10-1;
        while (t>0 && a[i]<=t)  printf("0"),    t/=10;
        printf("%i", a[i]);
    }
    printf("\n");
}

/* ---------------------------------- */

int Input()
{
    ios_base::sync_with_stdio(0);
//    freopen(fi, "r", stdin);
    char s[N];
    scanf("%s\n", &s);  ToBig(s,a);
    scanf("%s", &s);    ToBig(s,b);
}

/* ============================================================================ */

int Add(mang x, mang y, mang c)
{
    mang a, b;
    For(i,0,maxn)   a[i] = x[i],    b[i] = y[i];
    int nho = 0;
    c[0] = max(x[0],y[0]);
    For(i,1,c[0])   {
        c[i] = (a[i]+b[i]+nho)%mod;
        nho = (a[i]+b[i]+nho)/mod;
    }
    if (nho)    c[++c[0]] = nho;
    while (c[0]>1 && c[c[0]]==0)  c[0]--;
}

/* ---------------------------------- */

int Bigger(mang a, mang b)
{
    if (a[0] > b[0])    return 1;
    if (a[0] < b[0])    return 0;
    Ford(i,a[0],1)  {
        if (a[i] > b[i])    return 1;
        if (a[i] < b[i])    return 0;
    }
    return 0;
}

/* -------------- */

int Sub(mang a, mang b, mang c)
{
    if (Bigger(b,a))    swap(a,b),  printf("-");
    int nho = 0;
    c[0] = a[0];
    For(i,1,a[0])   {
        c[i] = (a[i]-b[i]-nho+mod)%mod;
        if (a[i]-b[i]-nho < 0)  nho = 1;    else nho = 0;
    }
    while (c[0]>1 && c[c[0]]==0)  c[0]--;
}

/* ---------------------------------- */

int Mul(mang a, mang b, mang c)
{
    For(i,1,maxn)   c[i] = 0;
    mang t; ll nho;
    For(j,1,b[0])   {
        nho = 0;
        For(i,1,maxn)   t[i] = 0;   t[0] = j-1;
        For(i,1,a[0])   {
            t[++t[0]] = (a[i]*b[j]+nho)%mod;
            nho = (a[i]*b[j]+nho)/mod;
        }
        if (nho)    t[++t[0]] = nho;
        Add(c,t,c);
    }
    while (c[0]>1 && c[c[0]]==0)  c[0]--;
}

/* ---------------------------------- */

int Solve()
{
    Add(a,b,c);
    Output(c);

    Sub(a,b,c);
    Output(c);

    Mul(a,b,c);
    Output(c);
}
