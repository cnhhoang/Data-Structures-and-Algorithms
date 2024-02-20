#include <cstdio>
#include <cmath>
int Query(int, int);
int Update(int, int, int);

/* ============================================================================ */
/* ============================================================================ */

#define For(i,l,r)  for(int i=l; i<=r; i++)
const int maxn = 5e4;
typedef int array[maxn+10];

array a; int n, q;
array s, t;  int ns;

/* ============================================================================ */
/* ============================================================================ */

int main()
{
//    freopen("SQRT.INP", "r", stdin);
    scanf("%i%i", &n, &q);  ns = sqrt(n);

    int l, r, x;
    For(i,1,q)  {
        scanf("%i%i%i", &x, &l, &r);
        if (x)
            printf("%i\n", Query(l,r));
        else scanf("%i", &x),   Update(l,r,x);
    }
}

/* ============================================================================ */
/* ============================================================================ */

int Update(int x, int y, int v)
{
    int px = (x-1)/ns+1,   py = (y-1)/ns+1;
    if (px==py) {
        For(i,x,y)  {
            a[i] += v;
            if (a[i] > s[px])   s[px] = a[i];
        }
        return 0;
    }

    For(i,x,px*ns)  {
        a[i] += v;
        if (a[i] > s[px])   s[px] = a[i];
    }
    For(i,px+1,py-1)
        t[i] += v;
    For(i,(py-1)*ns+1,y)    {
        a[i] += v;
        if (a[i] > s[py])   s[py] = a[i];
    }
}

/* ============================================================================ */

int Query(int x, int y)
{
    int px = (x-1)/ns+1,   py = (y-1)/ns+1,   Max = a[x]+t[px];
    if (px==py) {
        For(i,x,y)
            if (Max < a[i]+t[px])
                Max = a[i]+t[px];
        return Max;
    }

    For(i,x,px*ns)
        if (Max < a[i]+t[px])
            Max = a[i]+t[px];
    For(i,px+1,py-1)
        if (Max < s[i]+t[i])
            Max = s[i]+t[i];
    For(i,(py-1)*ns+1,y)
        if (Max < a[i]+t[py])
            Max = a[i]+t[py];
    return Max;
}
