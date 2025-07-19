/****************************************************************************************************
 *  Z-Algorithm
 * ---------------------------------------------------------------------------------
 *  This function computes the Z-array for a given string/array.
 * 
 *  Key Features:
 *   - Efficiently computes the Z-array in linear time.
 *   - For each position i, Z[i] stores the length of the longest substring starting
 *     at i that matches the prefix of the string.
 *   - Useful for solving problems like finding all occurrences of a pattern in a text.
 * 
 * Time Complexity:
 *      O(n), where n is the length of the input string.
 * Space Complexity:
 *      O(n), for storing the Z-array.
 * 
 * Sample Input/Output:
 * ---------------------------------------------------------------
 * Input:   "a a b c a a b x a a a z"
 * Output:   0 1 0 0 3 1 0 0 2 2 1 0
 ****************************************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

/************************************************************
 * ZAlgorithm computes the Z-array for a given string.
 * Input:  A string s.
 * Output: A vector<int> z 
 *      where z[i] is the length of the longest substring 
 *      starting at i that matches the prefix of s.   
 * ----------------------------------------------------------
 * Example: 
 * For s = "a a b c a a b x a a a z", 
 * returns {0,1,0,0,3,1,0,0,2,2,1,0}
 ************************************************************/
vector<int> ZAlgorithm(const string& s) {
    int n = s.size();
    int l = 0, r = 0;
    vector<int> z(n, 0);

    for (int i = 1; i < n; ++i) {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i]++;

        if (r < i + z[i] - 1) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    
    return z;
}

// ===================================================================================================
// ===================================================================================================

auto run_tests = []() {
    struct TestCase {
        string input;
        vector<int> expected;
    };

    vector<TestCase> tests = {
        {"aabcaabxaaaz", {0,1,0,0,3,1,0,0,2,2,1,0}},
        {"aaaaa", {0,4,3,2,1}},
        {"abcabcabcabcxabcabcabcabc", {0,0,0,9,0,0,6,0,0,3,0,0,0,12,0,0,9,0,0,6,0,0,3,0,0}}
    };

    for (const auto& test : tests) {
        assert(ZAlgorithm(test.input) == test.expected);
    }

    cout << "All tests passed!" << endl;
};

// --------------------------

int main()
{
    run_tests();
}