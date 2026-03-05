// 1758. Minimum Changes To Make Alternating Binary String
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s consisting only of the characters '0' and '1'. In one operation, you can change any '0' to '1' or vice versa.

// The string is called alternating if no two adjacent characters are equal. For example, the string "010" is alternating, while the string "0100" is not.

// Return the minimum number of operations needed to make s alternating.

 

// Example 1:

// Input: s = "0100"
// Output: 1
// Explanation: If you change the last character to '1', s will be "0101", which is alternating.
// Example 2:

// Input: s = "10"
// Output: 0
// Explanation: s is already alternating.
// Example 3:

// Input: s = "1111"
// Output: 2
// Explanation: You need two operations to reach "0101" or "1010".
 

// Constraints:

// 1 <= s.length <= 104
//solu =
class Solution {
public:
    int minOperations(string s) {
        
        /*
        Two possible valid alternating patterns:
        
        Pattern A: 010101...
        Pattern B: 101010...
        
        We'll count how many characters need to change
        to convert the string into each pattern.
        */
        
        int changesPattern1 = 0; // assuming string starts with '0'
        int changesPattern2 = 0; // assuming string starts with '1'
        
        for(int i = 0; i < s.size(); i++) {
            
            /*
            For Pattern1 (0101...):
            - even index -> '0'
            - odd index  -> '1'
            */
            char expected1 = (i % 2 == 0) ? '0' : '1';
            
            if(s[i] != expected1)
                changesPattern1++;
            
            
            /*
            For Pattern2 (1010...):
            - even index -> '1'
            - odd index  -> '0'
            */
            char expected2 = (i % 2 == 0) ? '1' : '0';
            
            if(s[i] != expected2)
                changesPattern2++;
        }
        
        /*
        We return the smaller number of changes
        because we can choose whichever pattern
        requires fewer flips.
        */
        return min(changesPattern1, changesPattern2);
    }
};
//tc = O(n)
//sc = O(1)
// s[i] is either '0' or '1'.
