// 1081. Smallest Subsequence of Distinct Characters
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

 

// Example 1:

// Input: s = "bcabc"
// Output: "abc"
// Example 2:

// Input: s = "cbacdcbc"
// Output: "acdb"
 

// Constraints:

// 1 <= s.length <= 1000
// s consists of lowercase English letters.
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string smallestSubsequence(string s) {

        // lastIndex[c] stores the last occurrence
        // of character c in the string.
        vector<int> lastIndex(26);

        // inSubsequence[c] tells whether the character
        // is already present in the current answer.
        vector<bool> inSubsequence(26, false);

        // Compute the last occurrence of every character.
        for (int i = 0; i < s.size(); i++) {
            lastIndex[s[i] - 'a'] = i;
        }

        // We use the answer string itself as a stack.
        string result;

        // Process every character from left to right.
        for (int i = 0; i < s.size(); i++) {

            int current = s[i] - 'a';

            // If this character is already included,
            // skip it because every character should
            // appear exactly once.
            if (inSubsequence[current]) {
                continue;
            }

            // Remove characters from the end while:
            //
            // 1. The last character is lexicographically larger.
            // 2. That character appears again later.
            //
            // Removing it now allows us to place it later,
            // producing a smaller lexicographical answer.
            while (!result.empty() &&
                   result.back() > s[i] &&
                   lastIndex[result.back() - 'a'] > i) {

                inSubsequence[result.back() - 'a'] = false;
                result.pop_back();
            }

            // Add the current character.
            result.push_back(s[i]);
            inSubsequence[current] = true;
        }

        return result;
    }
};

/*
Time Complexity:

O(n)

Each character is pushed into the stack once
and popped at most once.

Space Complexity:

O(1)

The auxiliary arrays have fixed size 26,
and the stack stores at most 26 distinct characters.
*/
