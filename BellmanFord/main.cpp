#include <cstdio>
int Input();
int BellmanFord();
int Output();

/* ================================================================================= */

const int maxn = 1000;
const int maxm = maxn*(maxn-1)/2;
const int infi = 1000000000;
typedef int mang[maxn+10];
typedef int dscanh[maxm+10];
dscanh u, v, c;    int n, m;
int s, t;
mang d, trace;

/* ================================================================================= */

int main()
{
    Input();
    BellmanFord();
    Output();
}

/* ================================================================================= */
/* ================================================================================= */

int Input()
{
    freopen("BELLMANFORD.INP", "r", stdin);
    scanf("%i %i %i %i", &n, &m, &s, &t);
    for (int i=1; i<=m; i++)
    scanf("%i %i %i", &u[i], &v[i], &c[i]);
}

/* ------------------------------------ */

int Output()
{
    printf("%i\n", d[t]);
    mang st;    int top=0;
    while (t!=s)    {
        st[++top] = t;
        t = trace[t];
    }
    st[++top] = s;
    while (top) {
        printf("%i ", st[top]);
        top--;
    }
}

/* ================================================================================= */

int Init()
{
    for (int i=1; i<=n; i++)
        d[i] = infi,   trace[i] = 0;
    d[s] = 0;
}

/* ------------------------------------ */

int Relax(int u, int v, int c)
{
    if (d[u]!=infi && d[v]>d[u]+c)  {
        d[v] = d[u]+c;
        trace[v] = u;
        return 1;
    }
    return 0;
}

/* ------------------------------------ */

int BellmanFord()
{
    Init();
    while (1)
    {
        bool stop = true;
        for (int i=1; i<=m; i++)
            if (Relax(u[i], v[i], c[i]))
                stop = false;
        if (stop)   break;
    }
}
