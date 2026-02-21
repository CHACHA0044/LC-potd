// 762. Prime Number of Set Bits in Binary Representation
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given two integers left and right, return the count of numbers in the inclusive range [left, right] having a prime number of set bits in their binary representation.

// Recall that the number of set bits an integer has is the number of 1's present when written in binary.

// For example, 21 written in binary is 10101, which has 3 set bits.
 

// Example 1:

// Input: left = 6, right = 10
// Output: 4
// Explanation:
// 6  -> 110 (2 set bits, 2 is prime)
// 7  -> 111 (3 set bits, 3 is prime)
// 8  -> 1000 (1 set bit, 1 is not prime)
// 9  -> 1001 (2 set bits, 2 is prime)
// 10 -> 1010 (2 set bits, 2 is prime)
// 4 numbers have a prime number of set bits.
// Example 2:

// Input: left = 10, right = 15
// Output: 5
// Explanation:
// 10 -> 1010 (2 set bits, 2 is prime)
// 11 -> 1011 (3 set bits, 3 is prime)
// 12 -> 1100 (2 set bits, 2 is prime)
// 13 -> 1101 (3 set bits, 3 is prime)
// 14 -> 1110 (3 set bits, 3 is prime)
// 15 -> 1111 (4 set bits, 4 is not prime)
// 5 numbers have a prime number of set bits.
 

// Constraints:

// 1 <= left <= right <= 106
//solu=
class Solution {
public:
    // Function to check whether a number is prime
    bool isPrime(int n) {
        // Numbers less than 2 are not prime
        if (n < 2)
            return false;

        // Check divisibility from 2 up to sqrt(n)
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }

        return true;
    }

    int countPrimeSetBits(int left, int right) {
        // This will store the final count of valid numbers
        int count = 0;

        // Traverse through every number in the inclusive range
        for (int num = left; num <= right; num++) {

            // Count the number of set bits (1s) in the binary representation
            // __builtin_popcount is a built-in function in C++
            int setBits = __builtin_popcount(num);

            // If the number of set bits is prime, increase the counter
            if (isPrime(setBits)) {
                count++;
            }
        }

        // Return the total count of numbers
        // that have a prime number of set bits
        return count;
    }
};

//tc = O(n) n= right-left
//sc = O(1)
// 0 <= right - left <= 104
