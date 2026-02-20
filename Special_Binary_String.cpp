// 761. Special Binary String
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// Special binary strings are binary strings with the following two properties:

// The number of 0's is equal to the number of 1's.
// Every prefix of the binary string has at least as many 1's as 0's.
// You are given a special binary string s.

// A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.

// Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.

 

// Example 1:

// Input: s = "11011000"
// Output: "11100100"
// Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
// This is the lexicographically largest string possible after some number of swaps.
// Example 2:

// Input: s = "10"
// Output: "10"
 

// Constraints:

// 1 <= s.length <= 50
// s[i] is either '0' or '1'.
// s is a special binary string.
//solu=  
class Solution {
public:
    string makeLargestSpecial(string s) {
        // This vector will store all top-level special substrings (blocks)
        vector<string> blocks;

        // count keeps track of balance:
        // +1 for '1' and -1 for '0'
        // When count becomes 0, we found a valid special substring
        int count = 0;

        // start marks the beginning index of the current special block
        int start = 0;

        // Traverse the string to split it into balanced special substrings
        for (int i = 0; i < s.size(); i++) {
            // Update balance: '1' increases, '0' decreases
            count += (s[i] == '1') ? 1 : -1;

            // When balance becomes 0, we found one complete special substring
            if (count == 0) {
                // Extract the inner substring (excluding the outer 1 and 0)
                string inner = s.substr(start + 1, i - start - 1);

                // Recursively make the inner part lexicographically largest
                // Then wrap it again with '1' and '0' to keep it special
                string largestInner = makeLargestSpecial(inner);
                blocks.push_back("1" + largestInner + "0");

                // Move start to the next position for the next block
                start = i + 1;
            }
        }

        // Sort all special blocks in descending lexicographical order
        // This ensures the final string is the largest possible
        sort(blocks.begin(), blocks.end(), greater<string>());

        // Concatenate all sorted blocks to form the final result
        string result;
        for (const string &block : blocks) {
            result += block;
        }

        return result;
    }
};

//tc= O(n^2)
//sc = O(n)
