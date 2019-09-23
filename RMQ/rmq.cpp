#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int Input();
int Solve();
/* ============================================================================ */
/* ============================================================================ */
#define FI "input.txt"
#define FO ""
#define For(i,l,r) for(int i=(int)(l); i<=(int)(r); i++)
#define Ford(i,r,l) for(int i=(int)(r); i>=(int)(l); i--)
#define pb push_back
#define ll long long
const int INFI = 2e9+1;
const int MOD = 1e9+7;
const int MAXN = 1e5;
const int MAXK = log2(MAXN);
const int N = MAXN+10;
const int K = MAXK+10;

typedef int Array[N];
typedef int Array2[N][K];
Array a;    int n;
Array2 s;
/* ============================================================================ */
/* ============================================================================ */
int main()
{
//    freopen(FI, "r", stdin);
    Input();
    Solve();
}
/* ============================================================================ */
/* ============================================================================ */
int Input()
{
    scanf("%i", &n);
    For(i,1,n)
        scanf("%i", &a[i]);
}
/* ============================================================================ */
int InitRMQ()
{
    For(i,1,n)
        s[i][0] = a[i];

    for(int k=1; (1<<k)<=n; k++)
        for(int i=1; i+(1<<k)-1 <= n; i++)
            s[i][k] = max(s[i][k-1], s[i+(1<<(k-1))][k-1]);
}
/* ---------------------------------- */
int QueryRMQ(int l, int r)
{
    int k = log2(r-l+1);
    return max(s[l][k], s[r-(1<<k)+1][k]);
}
/* ---------------------------------- */
int Solve()
{
    InitRMQ();

    int q, x, y;
    scanf("%i", &q);
    while (q--)
    {
        scanf("%i%i", &x, &y);
        printf("%i\n", QueryRMQ(x,y));
    }
}
