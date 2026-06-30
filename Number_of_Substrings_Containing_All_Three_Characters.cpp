// 1358. Number of Substrings Containing All Three Characters
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given a string s consisting only of characters a, b and c.

// Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

// Example 1:

// Input: s = "abcabc"
// Output: 10
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 
// Example 2:

// Input: s = "aaacb"
// Output: 3
// Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 
// Example 3:

// Input: s = "abc"
// Output: 1
 

// Constraints:

// 3 <= s.length <= 5 x 10^4
// s only consists of a, b or c characters.
class Solution {
public:
    int numberOfSubstrings(string s) {

        // Store the frequency of 'a', 'b' and 'c'
        // inside the current sliding window.
        vector<int> cnt(3, 0);

        int left = 0;
        int ans = 0;

        // Expand the window by moving the right pointer.
        for (int right = 0; right < s.size(); right++) {

            cnt[s[right] - 'a']++;

            // While the current window contains
            // at least one 'a', one 'b' and one 'c'.
            while (cnt[0] && cnt[1] && cnt[2]) {

                // Every substring starting at 'left'
                // and ending at 'right' or beyond
                // is also valid.
                ans += s.size() - right;

                // Shrink the window from the left
                // to look for more valid windows.
                cnt[s[left] - 'a']--;
                left++;
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n)

Space Complexity: O(1)
*/
