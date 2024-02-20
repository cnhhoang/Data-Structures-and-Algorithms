#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int Dijkstra();

/* ============================================================================ */
/* ============================================================================ */

#define fi "INPUT.TXT"
#define For(i,l,r) for(int i=l; i<=r; i++)
#define Ford(i,r,l) for(int i=r; i>=l; i--)
#define ll long long
#define stop return(0);
struct T    {
    int u, d;
};
struct cmp  {
    bool operator() (T a, T b)  {
        return a.d > b.d;
    }
};
const int infi = 1e9;
const int mod = 1e9+7;
const int maxn = 1e5;
typedef int array[maxn+10];
typedef vector<int> arrayv[maxn+10];
arrayv a, w;    int n;
array d;
int s, t;
priority_queue <T, vector<T>, cmp> q;

/* ============================================================================ */
/* ============================================================================ */

int Init1()
{
    For(i,1,n)
        a[i].resize(0), w[i].resize(0);
}

/* ---------------------------------- */

int main()
{
    ios_base::sync_with_stdio(0);
    freopen(fi, "r", stdin);
    int u, v, c, m;
    scanf("%i%i", &n, &m);
    For(i,1,m)  {
        scanf("%i%i%i", &u, &v, &c);
        a[u].push_back(v);  w[u].push_back(c);
    }
    scanf("%i%i", &s, &t);
    Dijkstra();
}

/* ============================================================================ */
/* ============================================================================ */

int Push(int u, int d)
{
    T x;    x.u = u;    x.d = d;
    q.push(x);
}

/* ---------------------------------- */

int Dijkstra()
{
    For(i,1,n)  d[i] = infi;    d[s] = 0;
    Push(s,0);

    while (q.size())    {
        int u = q.top().u,  du = q.top().d;  q.pop();
        if (du!=d[u] || a[u].empty())   continue;
        For(i,0,a[u].size()-1)  {
            int v = a[u][i], c = w[u][i];
            if (d[v] > d[u]+c)
                d[v] = d[u]+c,  Push(v,d[v]);
        }
    }

    if (d[dst]!=infi)
        printf("%i\n", d[t]);
    else printf("There is no path from %i to %i.\n", s, t);
}

