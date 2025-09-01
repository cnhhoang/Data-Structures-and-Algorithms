/* Bai toan:
Cho mang a gom n phan tu va q truy van. Co 2 loai truy van:
    0 i j: Gan gia tri j cho phan tu thu i
    1 i j: Xuat ra tong tu i -> j
*/

#include <cstdio>
#include <vector>

const int maxn = 10000;

class IntervalTree {
private:
    const int DEFAULT_OUT_OF_BOUNDS_VALUE = 0; // -INF for max, INF for min, 0 for sum, etc.

    int num_elements;
    std::vector<int> segmentValue, leftBound, rightBound;
    std::vector<int> leaf; // leaf[i] is the index of the leaf node that manages the i-th element

    int aggregate(int leftSegmentValue, int rightSegmentValue) {
        return leftSegmentValue + rightSegmentValue;
    }

    void build(int node, int left, int right, const std::vector<int>& arr) {
        leftBound[node] = left; 
        rightBound[node] = right;

        if (leftBound[node] == rightBound[node]) {
            leaf[leftBound[node]] = node;
            segmentValue[node] = arr[left];
        } else {
            int mid = (left + right) / 2;
            int leftChild = node * 2 + 1;
            int rightChild = node * 2 + 2;

            build(leftChild, left, mid, arr);
            build(rightChild, mid + 1, right, arr);
            segmentValue[node] = aggregate(segmentValue[leftChild], segmentValue[rightChild]);
        }
    }

    void update(int i, int newValue) {
        int node = leaf[i];
        segmentValue[node] = newValue;

        while (node != 0) {
            node = (node - 1) / 2;
            segmentValue[node] = aggregate(segmentValue[node * 2 + 1], segmentValue[node * 2 + 2]);
        }
    }

    int query(int node, int left, int right) {
        if (right < leftBound[node] || rightBound[node] < left)
            return DEFAULT_OUT_OF_BOUNDS_VALUE;
        if (left <= leftBound[node] && rightBound[node] <= right)
            return segmentValue[node];
        return aggregate(query(node * 2 + 1, left, right), query(node * 2 + 2, left, right));
    }

public:
    IntervalTree(const std::vector<int>& arr) 
        : num_elements(arr.size())
    {
        int sz = num_elements * 4 + 10;
        segmentValue.assign(sz, 0);
        leftBound.assign(sz, -1); // left
        rightBound.assign(sz, -1); // right
        leaf.assign(num_elements, -1); // leaf
        build(0, 0, num_elements - 1, arr);
    }

    void Update(int i, int d) {
        update(i, d);
    }

    int Query(int left, int right) {
        return query(0, left, right);
    }

    void PrintTree() {
        for (int i = 0; i < num_elements; i++) {
            printf("%i ", segmentValue[leaf[i]]);
        }
        printf("\n");

        for(int node = 0; node < num_elements * 4 + 10; node++) {
            if (leftBound[node] != -1 && rightBound[node] != -1)
                printf("Node %i: [%i, %i] = %i\n", node, leftBound[node], rightBound[node], segmentValue[node]);
        }
    }
};

//====================================================================================================

int main() {
    // Input
    const bool DEBUG = false;
    int n, q;
    std::vector<int> a;    
    
    freopen("INTERVALTREE.INP", "r", stdin);
    scanf("%i %i", &n, &q);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%i", &a[i]);

    // Process
    IntervalTree intervalTree(a);
    if (DEBUG) intervalTree.PrintTree();

    int c, i, j;
    for (int k = 1; k <= q; k++) {
        scanf("%i %i %i", &c, &i, &j);
        if (DEBUG) printf("\n=================================================================\n");
        if (c == 0) {
            intervalTree.Update(i-1, j);
            if (DEBUG) printf("Updated pos %i to %i\n", i-1, j);
            if (DEBUG) intervalTree.PrintTree();
        }
        else {
            if (DEBUG) printf("Query [%i, %i] = ", i-1, j-1);
            printf("%i\n", intervalTree.Query(i-1, j-1));
        }
            
    }
}
