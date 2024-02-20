/* Cho do thi vo huong n dinh, m canh va q truy van. Tra loi 2 loai truy van:
    0 x y: Xuat ra do dai duong di ngan nhat tu u -> v
    1 x y: Xuat ra t la so dinh tren duong di ngan nhat tu u -> v, t so sau la cac dinh tren duong di
    Do phuc tap: O(n^3)
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int Input();
int Floyd();
int Output();

/* ============================================================================ */
/* ============================================================================ */

#define fi "FLOYD.INP"
#define For(i,l,r) for(int i=l; i<=r; i++)
#define Ford(i,r,l) for(int i=r; i>=l; i--)
#define ll long long
#define stop return(0);
const int infi = 1e9;
const int mod = 1e9+7;
const int maxn = 300;
typedef int array[maxn+10];
typedef int array2d[maxn+10][maxn+10];
array2d a;   int n, m, q;
array2d trace;
array s; int t;

/* ============================================================================ */
/* ============================================================================ */

int main()
{
    Input();
    Floyd();
    Output();
}

/* ============================================================================ */
/* ============================================================================ */

int Input()
{
    ios_base::sync_with_stdio(0);
    freopen(fi, "r", stdin);
    scanf("%i%i%i", &n, &m, &q);
    int u, v, c;
    For(i,1,m)
        scanf("%i%i%i", &u, &v, &c),    a[u][v] = a[v][u] = c;
}

/* ---------------------------------- */

int Output()
{
    int u, v, c;
    For(i,1,q)  {
        scanf("%i%i%i", &c, &u, &v);
        if (c)  {
            t = 0;
            while (u!=v)    s[++t] = u, u = trace[u][v];    s[++t] = v;
            printf("%i", t);    For(i,1,t)  printf(" %i", s[i]);
            printf("\n");
        } else printf("%i\n", a[u][v]);
    }
}

/* ============================================================================ */

int Init()
{
    For(u,1,n)  For(v,1,n)  {
        trace[u][v] = v;
        if (a[u][v])    continue;
        if (u==v)
            a[u][v] = 0;
        else a[u][v] = infi;
    }
}

/* ---------------------------------- */

int Floyd()
{
    Init();

    For(k,1,n)    For(u,1,n)
        if (a[u][k]!=infi)
        For(v,1,n)
            if (a[k][v]!=infi && a[u][k]+a[k][v] < a[u][v]) {
                a[u][v] = a[u][k]+a[k][v];
                trace[u][v] = trace[u][k];
            }
}
