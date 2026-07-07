// 3754. Concatenate Non-Zero Digits and Multiply by Sum I
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n.

// Form a new integer x by concatenating all the non-zero digits of n in their original order. If there are no non-zero digits, x = 0.

// Let sum be the sum of digits in x.

// Return an integer representing the value of x * sum.

 

// Example 1:

// Input: n = 10203004

// Output: 12340

// Explanation:

// The non-zero digits are 1, 2, 3, and 4. Thus, x = 1234.
// The sum of digits is sum = 1 + 2 + 3 + 4 = 10.
// Therefore, the answer is x * sum = 1234 * 10 = 12340.
// Example 2:

// Input: n = 1000

// Output: 1

// Explanation:

// The non-zero digit is 1, so x = 1 and sum = 1.
// Therefore, the answer is x * sum = 1 * 1 = 1.
 

// Constraints:

// 0 <= n <= 109
class Solution {
public:
    long long sumAndMultiply(int n) {

        // x stores the number formed by
        // concatenating all non-zero digits.
        long long x = 0;

        // Stores the sum of digits in x.
        int sum = 0;

        // If the number itself is 0,
        // there are no non-zero digits.
        if (n == 0)
            return 0;

        // Convert the number to a string so
        // that digits are processed from left to right.
        string s = to_string(n);

        for (char c : s) {

            // Ignore all zero digits.
            if (c != '0') {

                // Append the current digit to x.
                x = x * 10 + (c - '0');

                // Add the digit to the digit sum.
                sum += c - '0';
            }
        }

        // IMPORTANT:
        // The answer can exceed the range of a 32-bit integer.
        // Example:
        // n = 65463628
        // x = 65463628
        // sum = 40
        // answer = 65463628 * 40 = 2618545120 (> INT_MAX)
        //
        // Therefore, the function must return long long.
        return x * 1LL * sum;
    }
};

/*
Time Complexity: O(d)
where d = number of digits in n.

Space Complexity: O(d)
because of the string created using to_string().
*/
