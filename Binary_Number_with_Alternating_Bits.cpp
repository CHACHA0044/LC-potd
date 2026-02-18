// 693. Binary Number with Alternating Bits
// Easy
// Topics
// premium lock icon
// Companies
// Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.

 

// Example 1:

// Input: n = 5
// Output: true
// Explanation: The binary representation of 5 is: 101
// Example 2:

// Input: n = 7
// Output: false
// Explanation: The binary representation of 7 is: 111.
// Example 3:

// Input: n = 11
// Output: false
// Explanation: The binary representation of 11 is: 1011.
 

// Constraints:

// 1 <= n <= 231 - 1

//solu=
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // XOR the number with itself shifted right by 1.
        // If the bits in n are alternating (like 101010),
        // then n ^ (n >> 1) will produce a number consisting of all 1s.
        long x = n ^ (n >> 1);
        // A number that consists of all 1s (for example 1111 in binary)
        // has a special property:
        // x & (x + 1) will be 0
        // If this condition is true, the original number had alternating bits.
        return (x & (x + 1)) == 0;
    }
};

//tc = O(1)
//sc = O(1)
