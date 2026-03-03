// 1545. Find Kth Bit in Nth Binary String
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given two positive integers n and k, the binary string Sn is formed as follows:

// S1 = "0"
// Si = Si - 1 + "1" + reverse(invert(Si - 1)) for i > 1
// Where + denotes the concatenation operation, reverse(x) returns the reversed string x, and invert(x) inverts all the bits in x (0 changes to 1 and 1 changes to 0).

// For example, the first four strings in the above sequence are:

// S1 = "0"
// S2 = "011"
// S3 = "0111001"
// S4 = "011100110110001"
// Return the kth bit in Sn. It is guaranteed that k is valid for the given n.

 

// Example 1:

// Input: n = 3, k = 1
// Output: "0"
// Explanation: S3 is "0111001".
// The 1st bit is "0".
// Example 2:

// Input: n = 4, k = 11
// Output: "1"
// Explanation: S4 is "011100110110001".
// The 11th bit is "1".
 

// Constraints:

// 1 <= n <= 20
// 1 <= k <= 2n - 1
//solu= 

class Solution {
public:
    
    char findKthBit(int n, int k) {
        /*
        Base Case:
        S1 = "0"
        */
        if (n == 1)
            return '0';
        
        /*
        Length of Sn = 2^n - 1
        Middle position = 2^(n-1)
        */
        int length = (1 << n) - 1;
        int mid = (1 << (n - 1));
        
        /*
        Case 1: k is exactly the middle element
        The middle bit is always '1'
        */
        if (k == mid)
            return '1';
        
        /*
        Case 2: k is in the left half
        Left half is exactly S(n-1)
        */
        if (k < mid)
            return findKthBit(n - 1, k);
        
        /*
        Case 3: k is in the right half
        
        Right half = reverse(invert(S(n-1)))
        
        So:
        - Find mirrored position in left half
        - Recursively get that bit
        - Invert it
        */
        
        int mirror = length - k + 1;
        
        char bit = findKthBit(n - 1, mirror);
        
        // Invert the bit
        return (bit == '0') ? '1' : '0';
    }
};
//tc = O(n)
//sc= O(n)
