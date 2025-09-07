/*  Given an array a consisting of n elements.
    Given 2 types of query:
        0 u v: returns the sum of a[u..v]
        1 u v: Increase u-th element by v (a[u] += v)
 */

#include <cstdio>
#include <iostream>
using namespace std;
int Input();
int BIT();
int Output();

/* ============================================================================= */

const int maxn = 10000;
typedef int array[maxn+5];

array a; int n;
array s;

/* ============================================================================= */

int main()
{
    Input();
    BIT();
}

/* ============================================================================= */
/* ============================================================================= */

int BuildTree()
{
    for (int x=1; x<=n; x++)
    {
        s[x] = a[x];
        int low = x & (x-1); // cay s quan li tu low+1 .. i
        int y = x-1;    // nut thap nhat x quan li
        while (y > low) {
            s[x] += s[y];
            y = y & (y-1);  // nhay toi nut con
        }
    }
}

/* --------------------------------- */

int Increase (int x, int Delta)
{
    while (x<=n)    {
        s[x] += Delta;
        x += x & (-x);
    }
}

/* --------------------------------- */

int Query (int x)   // tinh tong tu a[1] -> a[x]
{
    int t = 0;
    while (x > 0)   {
        t += s[x];
        x = x & (x-1);
    }
    return t;
}

/* --------------------------------- */

int BIT()
{
    BuildTree();

    int nq, u, v, x;
    scanf("%i", &nq);
    for (int i=1; i<=nq; i++)    {
        scanf("%i %i %i", &x, &u, &v);
        if (x)
            Increase(u, v); // tang u len v don vi
        else cout << Query(v) - Query(u-1) << endl;

    }
}

/* ============================================================================= */
/* ============================================================================= */

int Input()
{
    freopen("BIT.INP", "r", stdin);
    scanf("%i", &n);
    for (int i=1; i<=n; i++)
        scanf("%i", &a[i]);
}

