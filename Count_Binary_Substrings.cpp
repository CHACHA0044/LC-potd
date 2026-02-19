// 96. Count Binary Substrings
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given a binary string s, return the number of non-empty substrings that have the same number of 0's and 1's, and all the 0's and all the 1's in these substrings are grouped consecutively.

// Substrings that occur multiple times are counted the number of times they occur.

 

// Example 1:

// Input: s = "00110011"
// Output: 6
// Explanation: There are 6 substrings that have equal number of consecutive 1's and 0's: "0011", "01", "1100", "10", "0011", and "01".
// Notice that some of these substrings repeat and are counted the number of times they occur.
// Also, "00110011" is not a valid substring because all the 0's (and 1's) are not grouped together.
// Example 2:

// Input: s = "10101"
// Output: 4
// Explanation: There are 4 substrings: "10", "01", "10", "01" that have equal number of consecutive 1's and 0's.
 

// Constraints:

// 1 <= s.length <= 105
// s[i] is either '0' or '1'.

//solu= 
class Solution {
public:
    int countBinarySubstrings(string s) {
        // prevCount stores the length of the previous group of same characters
        // currCount stores the length of the current group of same characters
        int prevCount = 0;
        int currCount = 1;

        // This will store the total number of valid substrings
        int result = 0;

        // Traverse the string starting from the second character
        for (int i = 1; i < s.size(); i++) {

            // If the current character is the same as the previous one,
            // we are still in the same group, so increase current group length
            if (s[i] == s[i - 1]) {
                currCount++;
            } 
            else {
                // When the character changes, a new group starts
                // Add the minimum of previous and current group lengths
                // because that many valid substrings can be formed
                result += min(prevCount, currCount);

                // Update previous group to current group
                prevCount = currCount;

                // Reset current group length for the new character
                currCount = 1;
            }
        }

        // Add the result for the last pair of groups
        result += min(prevCount, currCount);

        return result;
    }
};

//tc = O(n)
//sc= O(1) 
