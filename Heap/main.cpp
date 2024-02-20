// Heap Min
#include <cstdio>
int Input();
int Heap();
int Output();

int UpHeap();
int DownHeap();

int MakeHeap();
int Extract();
int Update();
int Insert();

/* ================================================================================= */

const int maxn = 100000;
typedef int array[maxn+10];

array a; int n;
array h, pos; int nh;

/* ================================================================================= */

int main()
{
    Input();
    Heap();
    Output();
}

/* ================================================================================= */
/* ================================================================================= */

int Input()
{
    freopen("HEAP.INP", "r", stdin);
    scanf("%i", &n);
    for (int i=1; i<=n; i++)
        scanf("%i", &a[i]);
}

/* -------------------------------------- */

int Output()
{
    // Ghi ra day tang dan
    for (int i=1; i<=n; i++)
        printf("%i\n", a[Extract()]);
}

/* ================================================================================= */

int UpHeap(int i) // i la vi tri cua phan tu a[i] trong array a
{
    int x = pos[i]; // x la vi tri cua a[i] trong heap
    while (1)
    {
        int c = x/2;    // c la cha cua x
        if (!c || a[h[c]]<=a[i]) // c = 0 hoac heap da dam bao thu tu: cha <= con
            break;
        h[x] = h[c];    pos[h[x]] = x;  // keo cha xuong vi tri con (x)
        x = c;  // a[i] len vi tri c de xet tiep
    }
    h[x] = i;   pos[i] = x; // dat i vao vi tri x & cap nhat lai pos[i] la vi tri cua i trong heap
}

/* -------------------------------------- */

int DownHeap(int i)
{
    int x = pos[i]; // vi tri cua a[i] trong heap
    while (1)
    {
        int c = x*2; // c la cha trai cua x
        if (c<nh && a[h[c+1]]<a[h[c]])  //  neu ton tai nut con phai & nut con phai < nut con trai (chon nut con be nhat)
            c++;
        if (c>nh || a[i]<a[h[c]])   // neu x khong co cha || a[i] be hon nut con be nhat
            break;
        h[x] = h[c];    pos[h[x]] = x;  // keo c xuong vi tri nut con x
        x = c;  // a[i] len vi tri c de xet tiep
    }
    h[x] = i;   pos[i] = x; // dat i vao /* -------------------------------------- */vi tri x & cap nhat lai pos[i] la vi tri cua i trong heaps
}

/* --------------------------------------------------------------------------------- */

int MakeHeap()
{
    nh = 0;
    for (int i=1; i<=n; i++)    {
        h[++nh] = i;    pos[i] = nh;
        UpHeap(i);
    }
}

/* -------------------------------------- */

int Extract()   // Lay phan tu dau heap ra khoi heap
{
    int res = h[1];
    h[1] = h[nh--];    pos[h[1]] = 1;
    DownHeap(h[1]);
    return res;
}

/* -------------------------------------- */

int Update(int i, int New)  // Cap nhat a[i] = New
{
    if (New<a[i])
        UpHeap(i);
    else DownHeap(i);
/*    a[i] = New;   */
}

/* -------------------------------------- */

int Insert(int i)   // Chen phan tu moi vao heap
{
/*    a[i]=New;   */
    h[++nh] = i;    pos[i] = nh;
    UpHeap(i);
}

/* -------------------------------------- */

int Heap()
{
    MakeHeap();

/*  Update
    a[4] = 10;
    Update (4, 10); */

/*  Insert
    a[++n] = -1;
    Insert(10);
    a[++n] = 100;
    Insert(n);  */
}
