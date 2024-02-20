/* 
    Given a graph with N vertexes, M edges. Output its Minimim SPanning Tree.
    O ( MlogM )
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
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
struct T    {
    int u, v, c, p; // u, v: 2 dinh cua canh || c: do dai canh || p: so thu tu cua canh trong array a
};
struct cmp  {
    bool operator() (T a, T b)  {
        return (a.c > b.c);
    }
};
const int infi = 2e9;
const int mod = 1e9+7;
const int maxn = 1e5;
typedef int array[maxn+10];
typedef T arrayT[maxn+10];
arrayT a;   int n, m;
array lab, chose;
priority_queue <T, vector<T>, cmp>  q;
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
    freopen(fi, "r", stdin);
    scanf("%i%i", &n, &m);
    For(i,1,m)  {
        scanf("%i%i%i", &a[i].u, &a[i].v, &a[i].c);   a[i].p = i;
        q.push(a[i]);
    }
}

/* ---------------------------------- */

int Output()
{
    cout << res << endl;    // Xuat ra trong so cay khung nho nhat
    For(i,1,m)  // Xuat ra cac canh duoc chon
        if (chose[i])   printf("%i %i %i\n", a[i].u, a[i].v, a[i].c);
}

/* ============================================================================ */

int GetRoot(int u)
{
    if (lab[u] < 0) return u;   // u la root
    return lab[u] = GetRoot(lab[u]);    // Goi de quy tim goc
}

/* ---------------------------------- */

int Union(int u, int v)
{
    int t = lab[u]+lab[v];  // -t la tong so phan tu cua 2 tap con
    if (lab[u] > lab[v])    // so phan tu tap v nhieu hon
        lab[u] = v,   lab[v] = t;   // Cho tap co nhieu phan tu hon lam cha
    else lab[v] = u,  lab[u] = t;
}

/* ---------------------------------- */

int Solve()
{
    For(i,1,n)  lab[i] = -1;
    int t = 0;  // So canh da chon
    res = 0;
    while (t!=n-1)   {  // Chon toi khi du n-1 canh
        int u = q.top().u,  v = q.top().v,  c = q.top().c,  p = q.top().p;
        q.pop();
        int ru = GetRoot(u),  rv = GetRoot(v);
        if (ru!=rv) {// 2 tap con khac nhau
            chose[p] = 1;   // Chon canh p vao cay khung
            res += c;   // Tang gia tri cay khung
            t++;    // Tang so canh chon len
            Union(ru, rv);  // Hpo nhat 2 tap con
        }
    }
}
