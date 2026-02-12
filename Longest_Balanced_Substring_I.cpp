// 3713. Longest Balanced Substring I
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s consisting of lowercase English letters.

// A substring of s is called balanced if all distinct characters in the substring appear the same number of times.

// Return the length of the longest balanced substring of s.

 

// Example 1:

// Input: s = "abbac"

// Output: 4

// Explanation:

// The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.

// Example 2:

// Input: s = "zzabccy"

// Output: 4

// Explanation:

// The longest balanced substring is "zabc" because the distinct characters 'z', 'a', 'b', and 'c' each appear exactly 1 time.​​​​​​​

// Example 3:

// Input: s = "aba"

// Output: 2

// Explanation:

// ​​​​​​​One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each appear exactly 1 time. Another longest balanced substring is "ba".

 

// Constraints:

// 1 <= s.length <= 1000
// s consists of lowercase English letters.
 
//solu-

class Solution {
public:
    int longestBalancedSubstring(string s) {
        int n = s.size();

        // At minimum, any single character substring is balanced,
        // so we initialize the answer as 1
        int ans = 1;

        // We fix the starting index of the substring at position i
        // and try to extend the substring to the right
        for (int i = 0; i < n; i++) {

            // This frequency array keeps track of how many times
            // each character appears in the current substring
            vector<int> freq(26, 0);

            // j represents the ending index of the substring
            // We keep expanding the substring one character at a time
            for (int j = i; j < n; j++) {

                // Increment the frequency of the current character
                freq[s[j] - 'a']++;

                // These variables will track the minimum and maximum
                // frequencies among all distinct characters in the substring
                int minFreq = INT_MAX;
                int maxFreq = 0;

                // We scan through all 26 characters to find
                // the minimum and maximum frequency among those
                // that actually appear in the substring
                for (int k = 0; k < 26; k++) {
                    if (freq[k] > 0) {
                        minFreq = min(minFreq, freq[k]);
                        maxFreq = max(maxFreq, freq[k]);
                    }
                }

                // The substring is balanced if all distinct characters
                // appear the same number of times, which means
                // the minimum frequency equals the maximum frequency
                if (minFreq == maxFreq) {

                    // Update the answer with the length of this substring
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }
};
//tc= O(n^2)
//sc= O(1)
