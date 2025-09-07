/*  Given an array a of n elements and q queries: "u v". For each queries, find maximum value of a[u..v].
    Complexity:
        + Initialize: O(nlogn)
        + Query: O(1)
    
    Using header-only RMQ library with 0-based indexing
*/

#include <cstdio>
#include <vector>
#include "RMQ.cpp"  // Include the header-only library

int main() {
    freopen("RMQ.INP", "r", stdin);
    
    // Read array size and elements
    int n;
    scanf("%d", &n);
    
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Create RMQ instance using the header-only library
    RMQ rmq(arr);
    
    // Process queries
    int m;
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        
        // Convert from 1-based to 0-based indexing
        u--; v--;
        
        int result = rmq.query(u, v);
        printf("%d\n", result);
    }
    
    return 0;
}
