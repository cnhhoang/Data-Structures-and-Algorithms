/* Bai toan:
    Cho array a gom n phan tu va q truy van. Co 2 loai truy van:
        0 x y v: Tang gia tri cua cac phan tu tu x -> y len v don vi
        1 x y: Xuat ra tong cac phan tu tu x -> y
*/

#include <cstdio>
#include <iostream>
using namespace std;
int Input();
int Solve();

/* ================================================================================= */
/* ================================================================================= */

const int maxn = 100000;
typedef long long ll;
typedef ll array[maxn*4+10];

array a; int n, q;
array s, lazy, l, r;

/* ================================================================================= */
/* ================================================================================= */

int main()
{
    Input();
    Solve();
}

/* ================================================================================= */
/* ================================================================================= */

int Input()
{
    freopen("LAZYPROPAGATION.INP", "r", stdin);
    scanf("%i %i", &n, &q);
    for (int i=1; i<=n; i++)
        scanf("%i", &a[i]);
}

/* ================================================================================= */

int BuildTree(int x, int left, int right)
{
    l[x] = left;    r[x] = right;
    if (l[x]==r[x])
        s[x] = a[left];
    else    {
        int m = (left+right)/2;
        BuildTree(x*2, left, m);
        BuildTree(x*2+1, m+1, right);
        s[x] = s[x*2] + s[x*2+1];
    }
}

/* ------------------------------------- */

int Diffuse(int x)
{
    if (!lazy[x])
        return 0;
    s[x] += lazy[x] * (r[x]-l[x]+1); // lazy nhan cho so phan tu x quan ly

    if (l[x]!=r[x]) { // khong phai nut la
        lazy[x*2] += lazy[x];
        lazy[x*2+1] += lazy[x];
    }
    lazy[x] = 0;
}

/* ------------------------------------- */

int Update(int x, int left, int right, int v)
{
    Diffuse(x);
    if (r[x] < left || right < l[x]) // klq
        return 0;
    if (left <= l[x] && r[x] <= right)    { // thuoc hoan toan
        s[x] += v * (r[x]-l[x]+1);
        if (l[x]==r[x])
            return 0;
        lazy[x*2] += v;
        lazy[x*2+1] += v;
    }
    else    {
        Update(x*2, left, right, v);
        Update(x*2+1, left, right, v);
        s[x] = s[x*2] + s[x*2+1];
    }
}

/* ------------------------------------- */

int Query(int x, int left, int right)
{
    Diffuse(x);
    if (r[x] < left || right < l[x]) // klq
        return 0;
    if (left <= l[x] && r[x] <= right)
        return s[x];
    return Query(x*2, left, right) + Query(x*2+1, left, right);
}

/* ------------------------------------- */

int Solve()
{
    BuildTree(1, 1, n);

    // Truy van
    int choice, x, y, v;
    for (int k=1; k<=q; k++)    {
        scanf("%i", &choice);
        if (choice==0)  {
            scanf("%i %i %i", &x, &y, &v);
            Update (1, x, y, v);
        }
        else    {
            scanf("%i %i", &x, &y);
            cout << Query(1, x, y) << endl;
        }
    }
}
