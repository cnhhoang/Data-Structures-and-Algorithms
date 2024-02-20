/*  Given a tree with n elements. Given q queries consisting of 2 integers u, v.
    Find u and v's Lowest Common Ancestor.
    Complexity:
        + Initialize: O(NlogN)
        + Query: O(logN) */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int Input();
int Solve();

/* ============================================================================ */
/* ============================================================================ */

#define fi "LCA.INP"
#define For(i,l,r) for(int i=l; i<=r; i++)
#define Ford(i,r,l) for(int i=r; i>=l; i--)
#define ll long long
#define stop return(0);
const int infi = 2e9;
const int mod = 1e9+7;
const int maxn = 1e5;
const int maxk = log2(maxn); // C++ 4.3.2 : nen dung: maxk = 30;
typedef int array[maxn+10];
typedef int array2d[maxn+10][32];
typedef vector<int> arrayv[maxn+10];
arrayv a;    int n;
array2d s;   int k;  // s[i][k]: nut cha thu 2^k cua nut i
array c, d; // c[i] = x <=> x la cha cua i  ||  d[i] = x <=> Do sau cua nut i la x. D sau cua nut goc la 1

/* ============================================================================ */
/* ============================================================================ */

int main()
{
    Input();
    Solve();
}

/* ============================================================================ */
/* ============================================================================ */

int Prep() // Dung cho cac bai tap co nhieu test
{
    For(i,1,n)  {
        a[i].resize(0);
        d[i] = c[i] = 0;
        For(j,1,maxk)   s[i][j] = 0;
    }
}

/* ---------------------------------- */

int Input()
{
    ios_base::sync_with_stdio(0);
    freopen(fi, "r", stdin);
    scanf("%i", &n);
    int x, m;
    For(i,1,n)  {
        scanf("%i", &m);
        For(j,1,m)
            scanf("%i", &x),    a[i].push_back(x),  c[x] = i;
    }
}

/* ============================================================================ */

int DFS(int x, int h)
{
    d[x] = h;
    if (a[x].empty())   return 0;
    For(i,0,a[x].size()-1)  {
        int v = a[x][i];
        DFS(a[x][i],h+1);
    }
}

/* ---------------------------------- */

int Init()
{
    // s
    For(i,1,n)  s[i][0] = c[i];
    For(k,1,log2(n))    For(i,1,n)
        s[i][k] = s[s[i][k-1]][k-1];

    // d
        For(i,1,n)  if (c[i]==0)    // i la nut goc
            DFS(i,1);
}

/* ---------------------------------- */

int LCA(int u, int v)
{
    if (d[u]<d[v])  swap(u,v);  // u la nut co do sau >= v

    if (d[u]>d[v])  // lam cho d[u] = d[v]
        Ford(k,log2(n),0)
            if (d[s[u][k]] >= d[v])
                u = s[u][k];
    if (u==v)   return u;

    int res;    // tim LCA
    Ford(k,log2(n),0)
        if (s[u][k]==s[v][k])
            res = s[u][k];
        else u = s[u][k],   v = s[v][k];
    return res;
}

/* ---------------------------------- */

int Solve()
{
    Init();

    int u, v, q;
    scanf("%i", &q);
    For(i,1,q)  {
        scanf("%i%i", &u, &v);
        printf("%i\n", LCA(u,v));
    }
}

