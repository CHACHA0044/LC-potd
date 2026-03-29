// 2839. Check if Strings Can be Made Equal With Operations I
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given two strings s1 and s2, both of length 4, consisting of lowercase English letters.

// You can apply the following operation on any of the two strings any number of times:

// Choose any two indices i and j such that j - i = 2, then swap the two characters at those indices in the string.
// Return true if you can make the strings s1 and s2 equal, and false otherwise.

 

// Example 1:

// Input: s1 = "abcd", s2 = "cdab"
// Output: true
// Explanation: We can do the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbad".
// - Choose the indices i = 1, j = 3. The resulting string is s1 = "cdab" = s2.
// Example 2:

// Input: s1 = "abcd", s2 = "dacb"
// Output: false
// Explanation: It is not possible to make the two strings equal.
 

// Constraints:

// s1.length == s2.length == 4
// s1 and s2 consist only of lowercase English letters.

// solu = 
return (
    ( (s1[0]==s2[0] && s1[2]==s2[2]) || (s1[0]==s2[2] && s1[2]==s2[0]) ) &&
    ( (s1[1]==s2[1] && s1[3]==s2[3]) || (s1[1]==s2[3] && s1[3]==s2[1]) )
);

// Time: O(1) (fixed size 4)
// Space: O(1)


// alternate with sorting = 
class Solution {
public:
    bool canBeEqual(string s1, string s2) {
        
        // ----------------------------------------
        // STEP 1: Extract even and odd index groups
        // ----------------------------------------
        
        // Group 1 → indices 0 and 2
        string s1_even = {s1[0], s1[2]};
        string s2_even = {s2[0], s2[2]};
        
        // Group 2 → indices 1 and 3
        string s1_odd = {s1[1], s1[3]};
        string s2_odd = {s2[1], s2[3]};
        
        
        // ----------------------------------------
        // STEP 2: Sort both groups
        // ----------------------------------------
        
        // Why sort?
        // Because within a group we can swap freely,
        // so only the multiset of characters matters
        
        sort(s1_even.begin(), s1_even.end());
        sort(s2_even.begin(), s2_even.end());
        
        sort(s1_odd.begin(), s1_odd.end());
        sort(s2_odd.begin(), s2_odd.end());
        
        
        // ----------------------------------------
        // STEP 3: Compare groups
        // ----------------------------------------
        
        // Both even groups must match
        // AND both odd groups must match
        
        return (s1_even == s2_even) && (s1_odd == s2_odd);
    }
};
