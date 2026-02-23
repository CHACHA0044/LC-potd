// 1461. Check If a String Contains All Binary Codes of Size K
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.

 

// Example 1:

// Input: s = "00110110", k = 2
// Output: true
// Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
// Example 2:

// Input: s = "0110", k = 1
// Output: true
// Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring. 
// Example 3:

// Input: s = "0110", k = 2
// Output: false
// Explanation: The binary code "00" is of length 2 and does not exist in the array.
 

// Constraints:

// 1 <= s.length <= 5 * 105
// s[i] is either '0' or '1'.
// 1 <= k <= 20

//solu=
class Solution {
public:
    bool hasAllCodes(string s, int k) {

        int n = s.size();

        // If total possible substrings of size k is greater than s length
        // it's impossible to contain all binary codes
        if (n < k) 
            return false;

        int totalCodes = 1 << k;   // 2^k possible codes
        vector<bool> seen(totalCodes, false);

        int mask = totalCodes - 1; // Used to keep only last k bits
        int current = 0;
        int count = 0;

        for (int i = 0; i < n; i++) {

            // Shift left and add new bit
            current = ((current << 1) & mask) | (s[i] - '0');

            // Start checking once window size reaches k
            if (i >= k - 1) {
                if (!seen[current]) {
                    seen[current] = true;
                    count++;

                    // If all codes found, return early
                    if (count == totalCodes)
                        return true;
                }
            }
        }

        return false;
    }
};
//tc = O(n)
//sc = O(2^k)
