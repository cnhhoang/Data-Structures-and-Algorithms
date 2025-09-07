/****************************************************************************************************
 * RMQ Library - Range Maximum Query using Sparse Table Algorithm
 * 
 * BASIC IDEA:
 * The Sparse Table is a data structure that allows range maximum queries (RMQ) 
 * to be answered in O(1) time after O(n log n) preprocessing.
 * 
 * How it works:
 * 1. Precompute the maximum for all ranges of length 2^k (k = 0, 1, 2, ...)
 * 2. For any query [L, R], find the largest k such that 2^k <= (R-L+1)
 * 3. The answer is max(sparseTable[L][k], sparseTable[R-2^k+1][k])
 * 
 * TIME COMPLEXITY:
 * - Preprocessing: O(n log n) - We build a table of size n × log n
 * - Query: O(1) - Each query requires only 2 table lookups and 1 max operation
 * 
 * SPACE COMPLEXITY:
 * - O(n log n) - The sparse table stores n × log n integers
 * 
 * USAGE:
 * #include "RMQ.cpp"
 * 
 * std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
 * RMQ rmq(arr);                    // O(n log n) preprocessing
 * int max_val = rmq.query(2, 5);   // O(1) query, returns 9
 * 
 * NOTE: Uses 0-based indexing for modern C++ compatibility
 ****************************************************************************************************/

#include <vector>
#include <cmath>
#include <algorithm>

class RMQ {
private:
    std::vector<std::vector<int>> sparseTable;
    int n;
    int maxK;
    
    void buildSparseTable(const std::vector<int>& arr) {
        maxK = static_cast<int>(std::log2(n)) + 1;
        sparseTable.assign(n, std::vector<int>(maxK));
        
        // Initialize base cases
        for (int i = 0; i < n; i++) {
            sparseTable[i][0] = arr[i];
        }
        
        // Build sparse table
        for (int j = 1; j < maxK; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                sparseTable[i][j] = std::max(
                    sparseTable[i][j-1], 
                    sparseTable[i + (1 << (j-1))][j-1]
                );
            }
        }
    }
    
public:
    RMQ() : n(0), maxK(0) {}
    
    RMQ(const std::vector<int>& arr) : n(arr.size()) {
        if (n == 0) {
            maxK = 0;
            return;
        }
        buildSparseTable(arr);
    }
    
    int query(int left, int right) const {
        if (left < 0 || right >= n || left > right) {
            return -1;
        }
        
        int k = static_cast<int>(std::log2(right - left + 1));
        return std::max(
            sparseTable[left][k], 
            sparseTable[right - (1 << k) + 1][k]
        );
    }
    
    int size() const {
        return n;
    }
};
