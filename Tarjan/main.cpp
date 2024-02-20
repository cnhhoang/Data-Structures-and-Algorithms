/*  Tarjan algorithm to find Strongly Connected Components of a directed graph.
    Complexity: O( |V|+|E| ) */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
int Input();
int Solve();

/* ============================================================================ */
/* ============================================================================ */

#define fi "TARJAN.INP"
#define For(i,l,r) for(int i=l; i<=r; i++)
#define Ford(i,r,l) for(int i=r; i>=l; i--)
#define ll long long
const int infi = 2e9;
const int mod = 1e9+7;
const int maxn = 1e4;
typedef int mang[maxn+10];
typedef vector<int> mangv[maxn+10];

mangv a;    int n, m;
mang num, low, del; int t;
stack<int> s;
int res;

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
    freopen(fi, "r", stdin);
    scanf("%i%i", &n, &m);
    int u, v;
    For(i,1,m)  {
        scanf("%i%i", &u, &v);
        a[u].push_back(v);
    }
}

/* ============================================================================ */

int DFS(int u)
{
    num[u] = ++t;   low[u] = n+1;
    s.push(u);

    if (!a[u].empty())
        For(i,0,a[u].size()-1)    {
            int v = a[u][i];
            if (del[v]) continue; // da thuoc TPLT khac
            if (num[v]==0)  { // v chua tham
                DFS(v);
                low[u] = min(low[u],low[v]);
            } else  low[u] = min(low[u],num[v]);
        }

    if (low[u] >= num[u])   { // u la chot
        res++;
        while (s.top()!=u)  del[s.top()] = 1,   s.pop();
        del[u] = 1;    s.pop();
    }
}

/* ---------------------------------- */

int Solve()
{
    For(i,1,n)
        if (num[i]==0)
            DFS(i);
    cout << res; // So thanh phan lien thong manh
}
