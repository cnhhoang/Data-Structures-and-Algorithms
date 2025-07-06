#include <cstdio>

int Input();
int BellmanFord();
int Output();

/* ================================================================================= */

const int MAXN = 1000;
const int MAXM = MAXN * (MAXN - 1) / 2;
const int INF = 1000000000;

typedef int IntArray[MAXN + 10];
typedef int EdgeArray[MAXM + 10];

EdgeArray from, to, cost;
int n, m;
int source, target;
IntArray distance, predecessor;

/* ================================================================================= */

int main() 
{
    Input();
    BellmanFord();
    Output();

    return 0;
}

/* ================================================================================= */
/* ================================================================================= */

int Input() 
{
    freopen("BELLMANFORD.INP", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &source, &target);

    for (int i = 1; i <= m; ++i)
        scanf("%d %d %d", &from[i], &to[i], &cost[i]);

    return 0;
}

/* ------------------------------------ */

int Output() 
{
    printf("%d\n", distance[target]);

    IntArray stack;
    int top = 0;

    for (int current = target; current != source; current = predecessor[current])
        stack[++top] = current;
    stack[++top] = source;

    while (top)
        printf("%d ", stack[top--]);

    return 0;
}

/* ================================================================================= */

int Init() 
{
    for (int i = 1; i <= n; ++i) {
        distance[i] = INF;
        predecessor[i] = 0;
    }

    distance[source] = 0;

    return 0;
}

/* ------------------------------------ */

int Relax(int u, int v, int w) {
    if (distance[u] != INF && distance[v] > distance[u] + w) {
        distance[v] = distance[u] + w;
        predecessor[v] = u;

        return 1;
    }

    return 0;
}

/* ------------------------------------ */

int BellmanFord() {
    Init();
    
    while (true) {
        bool updated = false;

        for (int i = 1; i <= m; ++i)
            if (Relax(from[i], to[i], cost[i]))
                updated = true;

        if (!updated) break;
    }
    
    return 0;
}