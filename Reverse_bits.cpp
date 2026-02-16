// 190. Reverse Bits
// Solved
// Easy
// Topics
// premium lock icon
// Companies
// Reverse bits of a given 32 bits signed integer.

 

// Example 1:

// Input: n = 43261596

// Output: 964176192

// Explanation:

// Integer	Binary
// 43261596	00000010100101000001111010011100
// 964176192	00111001011110000010100101000000
// Example 2:

// Input: n = 2147483644

// Output: 1073741822

// Explanation:

// Integer	Binary
// 2147483644	01111111111111111111111111111100
// 1073741822	00111111111111111111111111111110
 

// Constraints:

// 0 <= n <= 231 - 2
// n is even.
 

// Follow up: If this function is called many times, how would you optimize it?
//solu=
class Solution {
public:
    int reverseBits(int n) {
        // This variable will store the final reversed-bit result
        uint32_t result = 0;

        // We process all 32 bits of the integer
        for (int i = 0; i < 32; i++) {

            // Shift result to the left to make space for the next bit
            // Then add the least significant bit of n to result
            result = (result << 1) | (n & 1);

            // Shift n to the right to process the next bit
            n >>= 1;
        }

        // Return the integer whose bits are reversed
        return result;
    }
};

//tc= O(32) (const)
//sc= O(1)

//follow=If this function is called many times:

// Use a Lookup Table (Memoization)

// Precompute reversed values for 8-bit (1 byte) numbers

// Split the 32-bit number into 4 bytes

// Reverse each byte using the table

// Recombine them

// This reduces repeated computation and speeds up execution in bulk calls.
