/*  Ma bai test: NKFLOW
    Cho do thi co huong:n dinh, m canh, dinh phat s, dinh thu t.
    Tim luong cuc dai Fmax tu s -> t.
    Do phuc tap: O(min(Fmax,n.m^2))
*/

/* ============================================================================ */
/* ============================================================================ */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int Input();
int Solve();
int Output();

/* ============================================================================ */
/* ============================================================================ */

#define fi "NKFLOW.INP"
#define fo "NKFLOW.OUT"
#define For(i,l,r) for(int i=(int)l; i<=(int)r; i++)
#define Ford(i,r,l) for(int i=(int)r; i>=(int)l; i--)
#define pb push_back
#define ll long long
const int infi = 2e9;
const int mod = 1e9+7;
const int maxn = 1e3;
const int N = maxn+10;
typedef int array[N];
typedef int array2d[N][N];
typedef vector<int> arrayv[N];
arrayv a;    int n, s, t;
array2d c, f;    // c[u][v]: suc chua cung (u,v) ; f[u][v]: luong tren cung (u,v)
array trace;
array q; int l, r;

/* ============================================================================ */
/* ============================================================================ */

int main()
{
    Input();
    Solve();
    Output();
}

/* ============================================================================ */
/* ============================================================================ */

int Input()
{
    ios_base::sync_with_stdio(0);
    freopen(fi, "r", stdin);
//    freopen(fo, "w", stdout);
    int m, u, v;
    scanf("%i%i%i%i", &n, &m, &s, &t);
    For(i,1,m)  {
        scanf("%i%i", &u, &v);    scanf("%i", &c[u][v]);
        a[u].pb(v);
        a[v].pb(u);    // tuy la cung (u,v) co huong nhung phai co cung doi
    }
}

/* ---------------------------------- */

int Output()
{
    ll MaxFlow = 0;
    For(u,1,n)
        if (f[s][u] > 0)
            MaxFlow += f[s][u];
    cout << MaxFlow;
}

/* ============================================================================ */

int FindPath()
{
    l = r = 1;  q[1] = s;
    For(i,1,n)  trace[i] = 0;   trace[s] = -1;

    while (l<=r)    {   int u = q[l++];
        For(i,0,a[u].size()-1)  {   int v = a[u][i];
            if (trace[v] || c[u][v]==f[u][v])   continue;   // da tham v || (u,v) la critical edge
            q[++r] = v;    trace[v] = u;
            if (v==t)   return 1;
        }
    }
    return 0;
}

/* ---------------------------------- */

int IncFlow()
{
    int u, v = t, Delta = infi; // Delta: luong co the tang lon nhat tren duong tang luong
    while (v!=s)    {
        u = trace[v];
        Delta = min(Delta,c[u][v]-f[u][v]);
        v = u;
    }

    v = t;
    while (v!=s)    {
        u = trace[v];
        f[u][v] += Delta;
        f[v][u] -= Delta;
        v = u;
    }
}

/* ---------------------------------- */

int Solve()
{
    while (FindPath())  IncFlow();
}
