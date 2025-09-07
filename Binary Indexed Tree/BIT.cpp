/* Binary Indexed Tree (Fenwick Tree) - Reusable Implementation
 * Supports range sum queries and point updates efficiently
 */

#include <iostream>
#include <vector>
using namespace std;

class BinaryIndexedTree {
private:
    vector<int> tree;
    int n;
    
    // Helper function to get the least significant bit
    int lsb(int x) const {
        return x & (-x);
    }

public:
    // Constructor
    BinaryIndexedTree(int size) : n(size) {
        tree.resize(n + 1, 0);
    }
    
    // Constructor from array
    BinaryIndexedTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(n + 1, 0);
        
        // Build the tree
        for (int i = 1; i <= n; i++) {
            tree[i] = arr[i-1]; // Convert to 1-based indexing
            int low = i & (i-1); // Range this node manages: low+1 to i
            int j = i - 1;       // Lowest node this node manages
            
            while (j > low) {
                tree[i] += tree[j];
                j = j & (j-1);   // Jump to parent node
            }
        }
    }
    
    // Update: Add delta to element at position x (1-based)
    void update(int x, int delta) {
        while (x <= n) {
            tree[x] += delta;
            x += lsb(x);
        }
    }
    
    // Query: Get sum from 1 to x (1-based)
    int query(int x) const {
        int sum = 0;
        while (x > 0) {
            sum += tree[x];
            x -= lsb(x);
        }
        return sum;
    }
    
    // Range query: Get sum from l to r (1-based, inclusive)
    int rangeQuery(int l, int r) const {
        return query(r) - query(l - 1);
    }
    
    // Get the size of the tree
    int size() const {
        return n;
    }
};

/* ============================================================================ */
/* ============================================================================ */
