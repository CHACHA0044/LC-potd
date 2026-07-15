// 3658. GCD of Odd and Even Sums
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n. Your task is to compute the GCD (greatest common divisor) of two values:

// sumOdd: the sum of the smallest n positive odd numbers.

// sumEven: the sum of the smallest n positive even numbers.

// Return the GCD of sumOdd and sumEven.

 

// Example 1:

// Input: n = 4

// Output: 4

// Explanation:

// Sum of the first 4 odd numbers sumOdd = 1 + 3 + 5 + 7 = 16
// Sum of the first 4 even numbers sumEven = 2 + 4 + 6 + 8 = 20
// Hence, GCD(sumOdd, sumEven) = GCD(16, 20) = 4.

// Example 2:

// Input: n = 5

// Output: 5

// Explanation:

// Sum of the first 5 odd numbers sumOdd = 1 + 3 + 5 + 7 + 9 = 25
// Sum of the first 5 even numbers sumEven = 2 + 4 + 6 + 8 + 10 = 30
// Hence, GCD(sumOdd, sumEven) = GCD(25, 30) = 5.

 

// Constraints:

// 1 <= n <= 10​​​​​​​00
#include <numeric>

class Solution {
public:
    int gcdOfOddEvenSums(int n) {

        // The sum of the first n odd numbers is always n².
        // Example:
        // n = 4
        // 1 + 3 + 5 + 7 = 16 = 4²
        int sumOdd = n * n;

        // The sum of the first n even numbers is:
        // 2 + 4 + ... + 2n
        // = 2 * (1 + 2 + ... + n)
        // = 2 * (n * (n + 1) / 2)
        // = n * (n + 1)
        int sumEven = n * (n + 1);

        // Return the greatest common divisor of the two sums.
        return std::gcd(sumOdd, sumEven);
    }
};

/*
Time Complexity:
O(log(min(sumOdd, sumEven)))
The complexity comes from the Euclidean GCD algorithm.

Space Complexity:
O(1)
Only a constant amount of extra space is used.
*/
