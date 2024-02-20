#include "function.h"

/* ================================================================================== */

void node::add(int x, node *L)
{
    n++;
    val[n] = x;
    link[n] = L;

    for(int i=n; i>=1; i--)
        if (val[i-1] > val[i])
    {
        swap(val[i-1],val[i]);
        swap(link[i-1],link[i]);
    }
}

/* ------------------------------------ */

void tree23::ins(int x)
{
    if (root==NULL)
    {
        root = new node;
        root->n = 1;
        root->val[1] = x;
        return;
    }

    node *cur = root, *tem;
    while (cur->link[0])
        for(int i=cur->n; i>=0; i--)
            if (x > cur->val[i])
            {
                cur = cur->link[i];
                break;
            }
    cur->add(x,NULL);

    while (cur && cur->n==3)
    {
            /// Split
        tem = new node;
        tem->up = cur->up;
        tem->n = cur->n = 1;
        tem->val[1] = cur->val[3];
        tem->link[0] = cur->link[2];
        tem->link[1] = cur->link[3];
        if (tem->link[0])
            tem->link[0]->up = tem->link[1]->up = tem;

            /// Upper node
        if (cur->up==NULL)
        {
            root = new node;
            root->n = 1;
            root->val[1] = cur->val[2];
            root->link[0] = cur;
            root->link[1] = tem;
            tem->up = cur->up = root;
        }
        else
            cur->up->add(cur->val[2],tem);

            /// Go up
        cur = cur->up;
    }
}

/* ================================================================================== */

void DFS(node *cur)
{
    if (!cur->link[0])
    {
        for(int i=1; i<=cur->n; i++)
            cout << cur->val[i] << " ";
        return;
    }

    for(int i=1; i<=cur->n; i++)
    {
        DFS(cur->link[i-1]);
        cout << cur->val[i] << " ";
    }

    DFS(cur->link[cur->n]);
}

/* ------------------------------------ */

void tree23::outIn()
{
    DFS(root);
}

/* ================================================================================== */

int DFS2(node *cur)
{
    if (!cur->link[0])
        return 1;

    int res = DFS2(cur->link[0]);
    for(int i=1; i<=cur->n; i++)
        res += DFS2(cur->link[i]);
    return res;
}

/* ------------------------------------ */

int tree23::width()
{
    return DFS2(root);
}

/* ================================================================================== */

int tree23::Min()
{
    node *cur = root;
    while (cur->link[0])
        cur = cur->link[0];
    return cur->val[1];
}

/* ------------------------------------ */

int tree23::Max()
{
    node *cur = root;
    while (cur->link[0])
        cur = cur->link[cur->n];
    return cur->val[cur->n];
}

/* ================================================================================== */

int DFS3(node *cur)
{
    if (!cur->link[0])
        return 1;
    int res = DFS3(cur->link[0]);
    for(int i=1; i<=cur->n; i++)
        res = max(res,DFS3(cur->link[i]));
    return res+1;
}

/* ------------------------------------ */

int tree23::height()
{
    return DFS3(root);
}
