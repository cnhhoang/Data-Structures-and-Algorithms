/* BigNum Class - Reusable Big Integer Implementation
 * Supports operations: +, -, * for non-negative integers up to 1000 digits
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

/* ============================================================================ */
/* ============================================================================ */

constexpr int infi = 2e9;
constexpr int mod = 1e9;

class BigNum {
private:
    vector<long long> x;

public:
    // Default constructor
    BigNum() {
        init();
    }
    
    // Constructor from string
    BigNum(const string& s) {
        init();
        int len = s.length() - 1;
        while (len >= 0) {
            int t = 0;
            for (int i = max(0, len-8); i <= len; i++) {
                t = t*10 + s[i] - '0';
            }
            x.push_back(t);
            len -= 9;
        }
    }
    
    // Initialize all digits to 0
    void init() {
        x.clear();
    }
    
    // Output the BigNum
    void output() const {
        if (x.empty()) {
            cout << "0\n";
            return;
        }
        cout << x[x.size()-1];
        for (int i = x.size()-2; i >= 0; i--) {
            int t = mod/10 - 1;
            while (t > 0 && x[i] <= t) {
                cout << "0";
                t /= 10;
            }
            cout << x[i];
        }
        cout << "\n";
    }

    
    // Greater than operator
    bool operator>(const BigNum& other) const {
        if (x.size() > other.x.size()) return true;
        if (x.size() < other.x.size()) return false;
        for (int i = x.size()-1; i >= 0; i--) {
            if (x[i] > other.x[i]) return true;
            if (x[i] < other.x[i]) return false;
        }
        return false;
    }    
    
    // Addition operator
    BigNum operator+(const BigNum& other) const {
        BigNum result;
        result.init();
        int maxSize = max(x.size(), other.x.size());
        long long carry = 0;
        
        for (int i = 0; i < maxSize; i++) {
            long long sum = carry;
            if (i < x.size()) sum += x[i];
            if (i < other.x.size()) sum += other.x[i];
            
            result.x.push_back(sum % mod);
            carry = sum / mod;
        }
        
        if (carry) {
            result.x.push_back(carry);
        }
        
        // Remove leading zeros
        while (result.x.size() > 1 && result.x.back() == 0) {
            result.x.pop_back();
        }
        
        return result;
    }
    
    // Subtraction operator
    BigNum operator-(const BigNum& other) const {
        BigNum result;
        result.init();
        
        // Determine which number is larger and handle sign
        if (*this > other) {
            long long borrow = 0;
            
            for (int i = 0; i < x.size(); i++) {
                long long diff = x[i] - borrow;
                if (i < other.x.size()) diff -= other.x[i];
                
                if (diff < 0) {
                    result.x.push_back((diff + mod) % mod);
                    borrow = 1;
                } else {
                    result.x.push_back(diff);
                    borrow = 0;
                }
            }
        } else {
            // If other is bigger, swap and add negative sign
            long long borrow = 0;
            
            for (int i = 0; i < other.x.size(); i++) {
                long long diff = other.x[i] - borrow;
                if (i < x.size()) diff -= x[i];
                
                if (diff < 0) {
                    result.x.push_back((diff + mod) % mod);
                    borrow = 1;
                } else {
                    result.x.push_back(diff);
                    borrow = 0;
                }
            }
        }
        
        // Remove leading zeros
        while (result.x.size() > 1 && result.x.back() == 0) {
            result.x.pop_back();
        }
        
        // Only print negative sign if result is not zero and other was bigger
        if (!(*this > other) && !result.x.empty() && !(result.x.size() == 1 && result.x[0] == 0)) {
            cout << "-";
        }
        
        return result;
    }
    
    // Multiplication operator
    BigNum operator*(const BigNum& other) const {
        BigNum result, temp;
        result.init();
        long long carry = 0;
        
        for (int j = 0; j < other.x.size(); j++) {
            temp.init();
            carry = 0;
            
            // Add j zeros at the beginning
            for (int k = 0; k < j; k++) {
                temp.x.push_back(0);
            }
            
            for (int i = 0; i < x.size(); i++) {
                temp.x.push_back((x[i] * other.x[j] + carry) % mod);
                carry = (x[i] * other.x[j] + carry) / mod;
            }
            
            if (carry) {
                temp.x.push_back(carry);
            }
            result = result + temp;
        }
        
        // Remove leading zeros
        while (result.x.size() > 1 && result.x.back() == 0) {
            result.x.pop_back();
        }
        return result;
    }
    
    // Assignment operator
    BigNum& operator=(const BigNum& other) {
        if (this != &other) {
            x = other.x;
        }
        return *this;
    }
};

/* ============================================================================ */
/* ============================================================================ */
