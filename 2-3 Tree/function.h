#include <cstdio>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

/* ================================================================================== */

struct node
{
    node *up = NULL;
    int n = 0;
    int val[4] = {-2e9};
    node *link[4] = {NULL};

    void add(int,node*);
};

struct tree23
{
    node *root = NULL;

    void ins(int);
    void outIn();
    int width();
    int Min();
    int Max();
    int height();
};

/* ================================================================================== */
