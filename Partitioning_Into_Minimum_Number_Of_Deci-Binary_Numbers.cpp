// 1689. Partitioning Into Minimum Number Of Deci-Binary Numbers
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros. For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.

// Given a string n that represents a positive decimal integer, return the minimum number of positive deci-binary numbers needed so that they sum up to n.

 

// Example 1:

// Input: n = "32"
// Output: 3
// Explanation: 10 + 11 + 11 = 32
// Example 2:

// Input: n = "82734"
// Output: 8
// Example 3:

// Input: n = "27346209830709182346"
// Output: 9
 

// Constraints:

// 1 <= n.length <= 105
// n consists of only digits.
// n does not contain any leading zeros and represents a positive integer.

//solu=
class Solution {
public:
    int minPartitions(string n) {
        
        /*
        Key Idea:
        A deci-binary number can only contain digits 0 or 1.

        When we sum multiple deci-binary numbers to form 'n',
        each deci-binary number can contribute at most 1 to
        any digit position.

        So if a digit in 'n' is, say, 7, that means we need
        at least 7 different deci-binary numbers to contribute
        a '1' in that position to reach 7.

        Therefore:
        The minimum number of deci-binary numbers required
        is simply the maximum digit present in the string.
        */

        int maxDigit = 0;  // This will store the largest digit we encounter

        // Traverse each character (digit) in the string
        for(char c : n) {
            
            // Convert character to integer by subtracting '0'
            int currentDigit = c - '0';
            
            // Update maxDigit if currentDigit is larger
            maxDigit = max(maxDigit, currentDigit);
        }

        // The largest digit determines the minimum number of deci-binary numbers needed
        return maxDigit;
    }
};
//tc= O(n) 
//sc = O(1)
