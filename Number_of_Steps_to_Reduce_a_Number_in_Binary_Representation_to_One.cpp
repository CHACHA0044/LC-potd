// 1404. Number of Steps to Reduce a Number in Binary Representation to One
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given the binary representation of an integer as a string s, return the number of steps to reduce it to 1 under the following rules:

// If the current number is even, you have to divide it by 2.

// If the current number is odd, you have to add 1 to it.

// It is guaranteed that you can always reach one for all test cases.

 

// Example 1:

// Input: s = "1101"
// Output: 6
// Explanation: "1101" corressponds to number 13 in their decimal representation.
// Step 1) 13 is odd, add 1 and obtain 14. 
// Step 2) 14 is even, divide by 2 and obtain 7.
// Step 3) 7 is odd, add 1 and obtain 8.
// Step 4) 8 is even, divide by 2 and obtain 4.  
// Step 5) 4 is even, divide by 2 and obtain 2. 
// Step 6) 2 is even, divide by 2 and obtain 1.  
// Example 2:

// Input: s = "10"
// Output: 1
// Explanation: "10" corresponds to number 2 in their decimal representation.
// Step 1) 2 is even, divide by 2 and obtain 1.  
// Example 3:

// Input: s = "1"
// Output: 0
 

// Constraints:

// 1 <= s.length <= 500
// s consists of characters '0' or '1'
// s[0] == '1'

//solu= 
class Solution {
public:
    int numSteps(string s) {
        int steps = 0;

        // This will simulate the carry generated when we add 1
        int carry = 0;

        // Traverse from the last bit toward the first bit
        // We stop at index 1 because we don't reduce beyond MSB
        for (int i = s.size() - 1; i > 0; i--) {

            // Current bit after including carry
            int bit = (s[i] - '0') + carry;

            // If bit is 1 → number is odd
            if (bit % 2 == 1) {
                // One step for +1
                // One step for divide by 2
                steps += 2;

                // Adding 1 creates a carry
                carry = 1;
            }
            else {
                // Even number → just divide by 2
                steps += 1;
            }
        }

        // If carry remains at the most significant bit
        // we need one extra step
        return steps + carry;
    }
};
//tc = O(n)
//sc = O(1)
