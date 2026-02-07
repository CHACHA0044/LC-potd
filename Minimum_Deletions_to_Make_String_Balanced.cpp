// 1653. Minimum Deletions to Make String Balanced
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s consisting only of characters 'a' and 'b'​​​​.

// You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

// Return the minimum number of deletions needed to make s balanced.

 

// Example 1:

// Input: s = "aababbab"
// Output: 2
// Explanation: You can either:
// Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
// Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
// Example 2:

// Input: s = "bbaaaaabb"
// Output: 2
// Explanation: The only solution is to delete the first two characters.
 

// Constraints:

// 1 <= s.length <= 105
// s[i] is 'a' or 'b'​​.

//solu= 
class Solution {
public:
    int minimumDeletions(string s) {
        // This variable keeps track of how many 'b' characters
        // we have seen so far while scanning the string from left to right.
        // These represent potential violations if an 'a' appears later.
        int count_b = 0;

        // This variable stores the minimum number of deletions required
        // to make the string balanced up to the current position.
        int deletions = 0;

        // We process the string character by character in order.
        // This allows us to make optimal decisions based only on past information.
        for (char c : s) {

            // If the current character is 'b',
            // it does not break the balance immediately.
            // We simply count it, since future 'a' characters
            // may conflict with it.
            if (c == 'b') {
                count_b++;
            } 
            else {
                // If the current character is 'a',
                // and we have already seen some 'b's before,
                // this creates a violation of the balanced condition.
                //
                // At this point, we have two choices:
                // 1. Delete the current 'a', which increases deletions by 1.
                // 2. Delete all previous 'b' characters, which costs count_b deletions.
                //
                // We choose the cheaper option to minimize total deletions.
                deletions = min(deletions + 1, count_b);
            }
        }

        // After processing the entire string,
        // the deletions variable contains the minimum number
        // of removals needed to make the string balanced.
        return deletions;
    }
};

//tc= O(n)
//sc= O(1)
