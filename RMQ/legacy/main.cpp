/*  Given an array a of n elements and q queries: "u v". For each queries, find maximum value of a[u..v].
    Complexity:
        + Initialize: O(nlogn)
        + Query: O(1)
*/

#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;

int Input();
int Solve();

/* ================================================================================= */
/* ================================================================================= */

const int maxn = 50000;
const int maxk = log2(maxn);
typedef int array[maxn+10];
typedef int array2d[maxn+10][maxk+10];

array a; int n, m;
array2d s;

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
    freopen("RMQ.INP", "r", stdin);
    scanf("%i", &n);
    for (int i=1; i<=n; i++)
        scanf("%i", &a[i]);
}

/* ================================================================================= */

int RMQ()
{
    // s[i][j]: gia tri lon nhat cua doan bat dau tu i va co j phan tu
    // Khoi tao
    for (int i=1; i<=n; i++)
        s[i][0] = a[i];

    // Quy hoach dong
    for (int j=1; (1<<j)<=n; j++)
        for (int i=1; i-1+(1<<j) <= n; i++)
            s[i][j] = max(s[i][j-1], s[i+(1<<(j-1))][j-1]);
}

/* ----------------------------------- */

int Solve()
{
    RMQ(); // Khoi tao bang gia tri

    // Tra loi truy van
    int u, v, k, res;
    scanf("%i", &m);

    for (int i=1; i<=m; i++)    {
        scanf("%i %i", &u, &v);

        k = log2(v-u+1);
        res = max (s[u][k], s[v-(1<<k)+1][k]);
        printf("%i\n", res);
    }
}