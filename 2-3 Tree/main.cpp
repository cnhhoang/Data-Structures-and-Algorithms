#include "function.h"

/* ================================================================================== */

int main()
{
    /// Input
    ifstream f;
    f.open("TEST.INP");

    int n, x;
    tree23 a;
    f >> n;
    for (int i=1; i<=n; i++)
    {
        f >> x;
        a.ins(x);
    }

    /// Output in-order
    cout << "Output the 2-3 Tree (in-order): " << endl;
    a.outIn();
    cout << endl << endl;

    /// Width of the tree <=> the number of leaf nodes
    cout << "Width of the tree: " << a.width() << endl << endl;


    /// Max & Min of the tree
    cout << "Min value: " << a.Min() << endl << "Max value: " << a.Max() << endl << endl;

    /// Height of the tree
    cout << "Height of the tree: " << a.height();
}

