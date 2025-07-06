/***********************************************************************************
 *  Bellman-Ford Shortest Path Algorithm
 * ---------------------------------------------------------------------------------
 *  This program reads a directed weighted graph and computes the shortest path
 * from a source vertex to a target vertex using the Bellman-Ford algorithm.
 * 
 *  Key Features:
 *   - Handles graphs with negative edge weights.
 *   - Detects shortest distances using edge relaxation.
 *   - Traces and prints the actual shortest path from source to target.
 *   - Assumes no negative weight cycles.
 * 
 * Time Complexity:
 *      O(n * m), where n is the number of vertices and m is the number of edges
 * Space Complexity:
 *      O(n + m)
 ***********************************************************************************/

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

/***********************************************************************************
 *  Input Format (from file "BELLMANFORD.INP"):
 *      n m s t
 *      u1 v1 c1
 *      u2 v2 c2
 *      ...
 *      um vm cm
 *  Where:
 *      n  = number of vertices
 *      m  = number of edges
 *      s  = source vertex (1-based index)
 *      t  = target vertex (1-based index)
 *      (ui, vi, ci) are the directed edges with cost ci
 ***********************************************************************************/

int Input() 
{
    freopen("BELLMANFORD.INP", "r", stdin);

    scanf("%d %d %d %d", &n, &m, &source, &target);

    for (int i = 1; i <= m; ++i)
        scanf("%d %d %d", &from[i], &to[i], &cost[i]);

    return 0;
}

/***********************************************************************************
 *  Output:
 *  - Shortest distance from s to t
 *  - The path from s to t as a sequence of vertices
 **********************************************************************************/
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