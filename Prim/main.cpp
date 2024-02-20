#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int Input();
int Solve();
int Output();

/* ============================================================================ */
/* ============================================================================ */

#define fi "TEST.INP"
#define For(i,l,r) for(int i=l; i<=r; i++)
#define Ford(i,r,l) for(int i=r; i>=l; i--)
#define ll long long
struct T {
    int d, u;
};
struct cmp  {
    bool operator() (T a, T b)  {
        return a.d > b.d;
    }
};
const int infi = 2e9;
const int mod = 1e9+7;
const int maxn = 1e5;
typedef int array[maxn+10];
typedef vector<int> arrayv[maxn+10];
arrayv a, w;  int n, m;
array d;
priority_queue<T, vector<T>, cmp>   q;
ll res;

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
//    freopen(fi, "r", stdin);
    scanf("%i%i", &n, &m);
    int u, v, c;
    For(i,1,m)  {
        scanf("%i%i%i", &u, &v, &c);
        a[u].push_back(v);   w[u].push_back(c);
        a[v].push_back(u);   w[v].push_back(c);
    }
}

/* ---------------------------------- */

int Output()
{
    cout << res;
}

/* ============================================================================ */

int Push(int u, int d)
{
    T a;    a.u = u;    a.d = d;
    q.push(a);
}

/* ---------------------------------- */

int Solve()
{
    For(i,1,n)  d[i] = infi;    d[1] =0;
    Push(1,0);

    res = 0;
    while (q.size())    {
        int u = q.top().u,  du = q.top().d;    q.pop();    // Lay dinh u co du nho nhat ra
        if (d[u]!=du || a[u].empty())   continue;          // Neu du khac d[u] thuc su thi thoat
        res += d[u];    d[u] = 0;   // Cap nhat gia tri cay khung, gan d[u] = 0 <=> khong xet u nua
        For(i,0,a[u].size()-1)  {
            int v = a[u][i],   c = w[u][i];
            if (d[v] > c)   // Tim thay canh noi v toi cay khung gan hon
                d[v] = c,   Push(v,d[v]);   // Cap nhat khoang cach tu v toi cay khung
        }
    }
}
