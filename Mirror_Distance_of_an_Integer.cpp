// 3783. Mirror Distance of an Integer
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n.

// Define its mirror distance as: abs(n - reverse(n))​​​​​​​ where reverse(n) is the integer formed by reversing the digits of n.

// Return an integer denoting the mirror distance of n​​​​​​​.

// abs(x) denotes the absolute value of x.

 

// Example 1:

// Input: n = 25

// Output: 27

// Explanation:

// reverse(25) = 52.
// Thus, the answer is abs(25 - 52) = 27.
// Example 2:

// Input: n = 10

// Output: 9

// Explanation:

// reverse(10) = 01 which is 1.
// Thus, the answer is abs(10 - 1) = 9.
// Example 3:

// Input: n = 7

// Output: 0

// Explanation:

// reverse(7) = 7.
// Thus, the answer is abs(7 - 7) = 0.
 

// Constraints:

// 1 <= n <= 109

// solu =
class Solution {
public:
    int mirrorDistance(int n) {
        
        // Store original number (we’ll need it later)
        int original = n;

        
        // This will hold the reversed number
        int reversed = 0;

        
        // Reverse the digits of n
        // Example: 120 → 21
        while (n > 0) {
            int digit = n % 10;           // extract last digit
            reversed = reversed * 10 + digit; // build reversed number
            n /= 10;                     // remove last digit
        }

        
        // Return absolute difference between original and reversed
        return abs(original - reversed);
    }
};
// Time Complexity:
// O(d)
// where d = number of digits (max ~10)
// Space Complexity:
// O(1)
