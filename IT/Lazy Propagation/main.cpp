/* Bai toan:
    Cho array a gom n phan tu va q truy van. Co 2 loai truy van:
        0 x y v: Tang gia tri cua cac phan tu tu x -> y len v don vi
        1 x y: Xuat ra tong cac phan tu tu x -> y
*/

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

class LazyIntervalTree {
private:
    int num_elements;
    std::vector<ll> segmentValue, lazy, leftBound, rightBound;

    // Helper functions
    void recalculate(int node) {
        if (leftBound[node] == rightBound[node])
            return;
        int leftChild = node * 2 + 1;
        int rightChild = node * 2 + 2;
        segmentValue[node] = segmentValue[leftChild] + segmentValue[rightChild];
    }

    // Main functions
    void build(int node, int left, int right, const std::vector<ll>& arr) {
        leftBound[node] = left;
        rightBound[node] = right;
        
        if (leftBound[node] == rightBound[node]) {
            segmentValue[node] = arr[left];
        } else {
            int mid = (left + right) / 2;
            build(node * 2 + 1, left, mid, arr);
            build(node * 2 + 2, mid + 1, right, arr);
            recalculate(node);
        }
    }

    void diffuse(int node) {
        if (!lazy[node])
            return;
            
        segmentValue[node] += lazy[node] * (rightBound[node] - leftBound[node] + 1); 

        if (leftBound[node] != rightBound[node]) { // Not a leaf node
            lazy[node * 2 + 1] += lazy[node];
            lazy[node * 2 + 2] += lazy[node];
        }

        lazy[node] = 0;
    }

    void update(int node, int left, int right, ll value) {
        diffuse(node); // Diffuse the lazy value to the children

        if (rightBound[node] < left || right < leftBound[node]) // Not in the range
            return;

        if (left <= leftBound[node] && rightBound[node] <= right) { // Fully in the range
            lazy[node] += value;
            diffuse(node);
        } else { // Partially in the range
            update(node * 2 + 1 , left, right, value);
            update(node * 2 + 2, left, right, value);
            recalculate(node);
        }
    }

    ll query(int node, int left, int right) {
        diffuse(node);
        
        if (rightBound[node] < left || right < leftBound[node]) // Not in the range
            return 0;
        if (left <= leftBound[node] && rightBound[node] <= right) // Fully in the range
            return segmentValue[node];
        return query(node * 2 + 1, left, right) + query(node * 2 + 2, left, right);
    }

public:
    LazyIntervalTree(const std::vector<ll>& arr) 
        : num_elements(arr.size()) 
    {
        int sz = num_elements * 4 + 10;
        segmentValue.assign(sz, 0);
        lazy.assign(sz, 0);
        leftBound.assign(sz, -1);
        rightBound.assign(sz, -1);
        build(0, 0, num_elements - 1, arr);
    }

    void Update(int left, int right, ll value) {
        update(0, left, right, value);
    }

    ll Query(int left, int right) {
        return query(0, left, right);
    }

    void PrintTree() {
        printf("Segment Tree Values:\n");
        for (int node = 0; node < num_elements * 4 + 10; node++) {
            if (leftBound[node] != -1 && rightBound[node] != -1)
                printf("Node %i: [%i, %i] = %lld (lazy: %lld)\n", 
                       node, leftBound[node], rightBound[node], 
                       segmentValue[node], lazy[node]);
        }
    }
};

//====================================================================================================

int main() {
    // Input
    const bool DEBUG = false;
    int n, q;
    std::vector<ll> a;
    
    freopen("LAZYPROPAGATION.INP", "r", stdin);
    scanf("%i %i", &n, &q);
    a.resize(n); // 1-indexed
    for (int i = 0; i < n; i++)
        scanf("%lld", &a[i]);

    // Process
    LazyIntervalTree lazyTree(a);
    if (DEBUG) lazyTree.PrintTree();

    // Truy van
    int choice, x, y;
    ll v;
    for (int k = 1; k <= q; k++) {
        scanf("%i", &choice);
        if (choice == 0) {
            scanf("%i %i %lld", &x, &y, &v);
            if (DEBUG) printf("Update [%i, %i] += %lld\n", x, y, v);
            lazyTree.Update(x-1, y-1, v);
            if (DEBUG) lazyTree.PrintTree();
        } else {
            scanf("%i %i", &x, &y);
            if (DEBUG) printf("Query [%i, %i] = ", x, y);
            cout << lazyTree.Query(x-1, y-1) << endl;
        }
    }
}
