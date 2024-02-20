/* Bai toan:
Cho mang a gom n phan tu va q truy van. Co 2 loai truy van:
    0 i j: Gan gia tri j cho phan tu thu i
    1 i j: Xuat ra tong tu i -> j
*/

#include <cstdio>
int DocFile();
int XuLi();

/* ================================================================================= */
/* ================================================================================= */

const int maxn = 10000;
typedef int mang[maxn*4+10];

mang a; int n;
int q;
mang s, l, r;
mang leaf;

/* ================================================================================= */
/* ================================================================================= */

int main()
{
    DocFile();
    XuLi();
}

/* ================================================================================= */
/* ================================================================================= */

int DocFile()
{
    freopen("INTERVALTREE.INP", "r", stdin);
    scanf("%i %i", &n, &q);
    for (int i=1; i<=n; i++)
        scanf("%i", &a[i]);
}

/* ================================================================================= */

int BuildTree(int x, int left, int right) // dung cay interval
{
    l[x] = left;    r[x] = right;
    if (l[x] == r[x])   {
        leaf[l[x]] = x;
        s[x] = a[left];
    }
    else    {
        int m = (left+right)/2;
        BuildTree(x*2, left, m);
        BuildTree(x*2+1, m+1, right);
        s[x] = s[x*2] + s[x*2+1];
    }
}

/* -------------------------------------- */

int Update (int i, int d) // gan a[i] = d
{
    int x = leaf[i];
    s[x] = d;
    while (x>1) {
        x /= 2;
        s[x] = s[x*2] + s[x*2+1];
    }
}

/* -------------------------------------- */

int Query (int x, int left, int right)
{
    if (right < l[x] || r[x] < left)    // klq
        return 0;
    if (left <= l[x] && r[x] <= right)  // giao hoan toan
        return s[x];
    return Query(x*2, left, right) + Query(x*2+1, left, right);     // giao mot phan
}

/* -------------------------------------- */

int XuLi()
{
    BuildTree(1, 1, n);

    int c, i, j;
    for (int k=1; k<=q; k++)    {
        scanf("%i %i %i", &c, &i, &j);
        if (c==0)   // update
            Update(i, j);
        else printf("%i\n", Query(1, i, j));
    }
}
