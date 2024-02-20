#include <cstdio>
#include <vector>
#include <stack>
using namespace std;
int DocFile();
int Dijkstra();
int GhiKQ();

/* ================================================================================= */

const int maxn = 10000;
const int infi = 2000000000;
typedef int mang[maxn+10];
typedef bool mangkt[maxn+10];
typedef vector<int> mangv[maxn+10];

mangv a, w;    int n;   // a, w: danh sach ke lan luot chua dinh va trong so
mang na;                // na[u]=x <=> dinh u co x dinh ke voi no
int s, t;               // dinh bat dau & ket thuc

mang d, trace;          // d[i]: khoang cach ngan nhat tu s toi t
                        // trace[u] = v <=> truy vet. Tren duong di ngan nhat tu s toi u la dinh v
                        // Free[u] = true <=> u chua co dinh nhan
mang h, pos;    int nh; // h: heap min;   pos[i]=x <=> vi tri cua i trong heap la x.

/* ================================================================================= */

int main()
{
    DocFile();
    Dijkstra();
    GhiKQ();
}

/* ================================================================================= */
/* ================================================================================= */

int DocFile()
{
    int u, v, c, m;
    freopen("DIJKSTRA.INP", "r", stdin);
    scanf("%i %i %i %i", &n, &m, &s, &t);       // n: so dinh;   m: so canh;   s: dinh bat dau;   t: dinh ket thuc
    for (int i=1; i<=m; i++)
    {
        scanf("%i %i %i", &u, &v, &c);          // canh noi tu u toi v co trong so c
        a[u].push_back(v);  w[u].push_back(c);  // luu: tu u co the toi v voi canh trong so c
        a[v].push_back(u);  w[v].push_back(c);  // do thi vo huong
        na[u]++;    na[v]++;
    }
}

/* ------------------------------------ */

int GhiKQ()
{
    if (d[t]==infi) {
        printf("There is no path from %i to %i", s, t);
        return 0;
    }

    stack<int>  st;
    printf("Length of the shortest path: %i\n", d[t]);
    printf("The path from %i to %i: ", s, t);
    while (t)   {
        st.push(t);
        t = trace[t];
    }
    while (!st.empty()) {
        printf("%i ", st.top());
        st.pop();
    }
}

/* ================================================================================= */

int UpHeap(int i)
{
    int x = pos[i];
    while (1)
    {
        int c = x/2;
        if (!c || d[h[c]]<=d[i])
            break;
        h[x] = h[c];    pos[h[x]] = x;
        x = c;
    }
    h[x] = i;   pos[i] = x;
}

/* ------------------------------------ */

int DownHeap(int i)
{
    int x = pos[i];
    while (1)
    {
        int c = x*2;
        if (c<nh && a[h[c]]>a[h[c+1]])
            c++;
        if (c>nh || a[h[c]]>=a[i])
            break;
        h[x] = h[c];    pos[h[x]] = x;
        x = c;
    }
    h[x] = i;   pos[i] = x;
}

/* ------------------------------------ */

int Extract()
{
    if (nh==0)  return 0;
    int res = h[1];
    h[1] = h[nh--];   pos[h[1]] = 1;
    if (nh) DownHeap(h[1]);
    return res;
}

/* ------------------------------------ */

int Insert(int i)
{
    h[++nh] = i;    pos[i] = nh;
    UpHeap(i);
}

/* --------------------------------------------------------------------------------- */

int Init()
{
    // d, trace & pos
    for (int i=1; i<=n; i++)    {
        trace[i] = 0;
        d[i] = infi;
        pos[i] = 0;
    }
    d[s] = 0;

    // Khoi tao Heap
    nh = 1;
    h[nh] = s;  pos[s] = nh;
}

/* ------------------------------------ */

int Dijkstra()
{
    Init();
    while (1)
    {
        // Tim dinh u chua co dinh va d[u] nho nhat
        int u = Extract();
        if (u==0 || u==t)   return 0;   // Neu khong tim duoc duong di || da tim duoc duong di => thoat

        // Cap nhat lai cac nhan khoang cach
        for (int i=0; i<na[u]; i++)
            if (d[a[u][i]] > d[u]+w[u][i])  {
                d[a[u][i]] = d[u]+w[u][i];
                trace[a[u][i]] = u;
                if (pos[a[u][i]]==0)    // neu chua ton tai dinh a[u][i] trong heap => them vao
                    Insert(a[u][i]);
            }
    }
}
