#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int readFile();
int dijkstra();
int printResult();

/* ================================================================================= */

const int MAXN = 10000;
const int INF = 2000000000;
typedef int IntArray[MAXN + 10];
typedef vector<int> AdjList[MAXN + 10];

AdjList adj, weight;
IntArray degree;
int n;
int start, target;

IntArray dist, prev;
IntArray heap, pos;
int heapSize;

/* ================================================================================= */

int main() {
    readFile();
    dijkstra();
    printResult();
    return 0;
}

/* ================================================================================= */
/* ================================================================================= */

int readFile() {
    int u, v, c, m;
    freopen("DIJKSTRA.INP", "r", stdin);
    scanf("%d %d %d %d", &n, &m, &start, &target);
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &u, &v, &c);
        adj[u].push_back(v);
        weight[u].push_back(c);
        adj[v].push_back(u);
        weight[v].push_back(c);
        ++degree[u];
        ++degree[v];
    }
    return 0;
}

/* ------------------------------------ */

int printResult() {
    if (dist[target] == INF) {
        printf("There is no path from %d to %d", start, target);
        return 0;
    }

    stack<int> st;
    printf("Length of the shortest path: %d\n", dist[target]);
    printf("The path from %d to %d: ", start, target);
    int cur = target;
    while (cur) {
        st.push(cur);
        cur = prev[cur];
    }
    while (!st.empty()) {
        printf("%d ", st.top());
        st.pop();
    }
    return 0;
}

/* ================================================================================= */

void upHeap(int i) {
    int x = pos[i];
    while (true) {
        int parent = x / 2;
        if (!parent || dist[heap[parent]] <= dist[i])
            break;
        heap[x] = heap[parent];
        pos[heap[x]] = x;
        x = parent;
    }
    heap[x] = i;
    pos[i] = x;
}

/* ------------------------------------ */

void downHeap(int i) {
    int x = pos[i];
    while (true) {
        int child = x * 2;
        if (child < heapSize && dist[heap[child]] > dist[heap[child + 1]])
            ++child;
        if (child > heapSize || dist[heap[child]] >= dist[i])
            break;
        heap[x] = heap[child];
        pos[heap[x]] = x;
        x = child;
    }
    heap[x] = i;
    pos[i] = x;
}

/* ------------------------------------ */

int extract() {
    if (heapSize == 0)
        return 0;
    int res = heap[1];
    heap[1] = heap[heapSize--];
    pos[heap[1]] = 1;
    if (heapSize)
        downHeap(heap[1]);
    return res;
}

/* ------------------------------------ */

void insert(int i) {
    heap[++heapSize] = i;
    pos[i] = heapSize;
    upHeap(i);
}

/* --------------------------------------------------------------------------------- */

void init() {
    for (int i = 1; i <= n; ++i) {
        prev[i] = 0;
        dist[i] = INF;
        pos[i] = 0;
    }
    dist[start] = 0;

    heapSize = 1;
    heap[heapSize] = start;
    pos[start] = heapSize;
}

/* ------------------------------------ */

int dijkstra() {
    init();
    while (true) {
        int u = extract();
        if (u == 0 || u == target)
            return 0;

        for (int i = 0; i < degree[u]; ++i) {
            int v = adj[u][i];
            int w = weight[u][i];
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                if (pos[v] == 0)
                    insert(v);
            }
        }
    }
    return 0;
}
