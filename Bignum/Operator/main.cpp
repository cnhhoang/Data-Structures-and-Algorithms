/* BigNum Operations - Clean Implementation
 * Given 2 non-negative big integers a, b (up to 1000 digits), calculate:
 *    a + b
 *    a - b  
 *    a * b
 */

#include <iostream>
#include <string>
#include "BigNum.cpp"

using namespace std;

/* ============================================================================ */
/* ============================================================================ */
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("BIGNUM.INP", "r", stdin);
    
    string s;
    BigNum result;
    
    // Input two big numbers
    cin >> s;
    BigNum a(s);
    
    cin >> s;
    BigNum b(s);
    
    // Perform operations and output results
    bool isBigger = a > b;
    cout << "a" << (isBigger ? " > " : " < ") << "b" << endl;
    
    result = a + b;
    result.output();
    
    result = a - b;
    result.output();
    
    result = a * b;
    result.output();

    return 0;
}

/* ============================================================================ */
/* ============================================================================ */