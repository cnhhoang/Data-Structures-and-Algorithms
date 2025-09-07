/* Binary Indexed Tree Operations - Clean Implementation
 * Given an array a consisting of n elements.
 * Given 2 types of query:
 *     0 u v: returns the sum of a[u..v]
 *     1 u v: Increase u-th element by v (a[u] += v)
 */

#include <iostream>
#include <vector>
#include "BIT.cpp"

using namespace std;

/* ============================================================================ */
/* ============================================================================ */

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("BIT.INP", "r", stdin);
    
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (auto& element : arr) {
        cin >> element;
    }
    
    // Create Binary Indexed Tree from array
    BinaryIndexedTree bit(arr);
    
    int nq;
    cin >> nq;
    
    for (int i = 0; i < nq; i++) {
        int queryType, u, v;
        cin >> queryType >> u >> v;
        
        if (queryType == 1) {
            // Update: Increase u-th element by v
            bit.update(u, v);
        } else {
            // Query: Get sum from u to v
            cout << bit.rangeQuery(u, v) << '\n';
        }
    }
    
    return 0;
}

/* ============================================================================ */
/* ============================================================================ */
