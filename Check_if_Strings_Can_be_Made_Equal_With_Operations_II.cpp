// 2840. Check if Strings Can be Made Equal With Operations II
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given two strings s1 and s2, both of length n, consisting of lowercase English letters.

// You can apply the following operation on any of the two strings any number of times:

// Choose any two indices i and j such that i < j and the difference j - i is even, then swap the two characters at those indices in the string.
// Return true if you can make the strings s1 and s2 equal, and false otherwise.

 

// Example 1:

// Input: s1 = "abcdba", s2 = "cabdab"
// Output: true
// Explanation: We can apply the following operations on s1:
// - Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
// - Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
// - Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.
// Example 2:

// Input: s1 = "abe", s2 = "bea"
// Output: false
// Explanation: It is not possible to make the two strings equal.
 

// Constraints:

// n == s1.length == s2.length
// 1 <= n <= 105
// s1 and s2 consist only of lowercase English letters.

// solu = 
class Solution {
public:
    bool checkStrings(string s1, string s2) {
        
        // ------------------------------------------
        // STEP 1: Get length of strings
        // ------------------------------------------
        int n = s1.size();
        
        
        // ---------------------------------------------------------
        // STEP 2: Create frequency arrays for both strings
        // ---------------------------------------------------------
        
        // We use vectors of size 26 because:
        // - Strings contain only lowercase English letters ('a' to 'z')
        // - Each index represents a character:
        //     index 0 → 'a'
        //     index 1 → 'b'
        //     ...
        //     index 25 → 'z'
        
        // even1 → frequency of characters at EVEN indices in s1
        // odd1  → frequency of characters at ODD indices in s1
        
        // even2 → frequency of characters at EVEN indices in s2
        // odd2  → frequency of characters at ODD indices in s2
        
        // Example:
        // if even1[0] = 2 → character 'a' appears 2 times at even positions in s1
        
        vector<int> even1(26, 0), odd1(26, 0);
        vector<int> even2(26, 0), odd2(26, 0);
        
        
        // ---------------------------------------------------------
        // STEP 3: Traverse both strings and fill frequencies
        // ---------------------------------------------------------
        
        for(int i = 0; i < n; i++) {
            
            // Check if index is EVEN or ODD
            if(i % 2 == 0) {
                
                // ------------------------------------------
                // EVEN INDEX CASE
                // ------------------------------------------
                
                // Convert character to index:
                // 'a' → 0, 'b' → 1, ..., 'z' → 25
                
                // Example:
                // if s1[i] = 'c'
                // then 'c' - 'a' = 2
                
                even1[s1[i] - 'a']++;  // increment count in s1
                even2[s2[i] - 'a']++;  // increment count in s2
            } 
            else {
                
                // ------------------------------------------
                // ODD INDEX CASE
                // ------------------------------------------
                
                odd1[s1[i] - 'a']++;   // count for s1
                odd2[s2[i] - 'a']++;   // count for s2
            }
        }
        
        
        // ---------------------------------------------------------
        // STEP 4: Compare frequency arrays
        // ---------------------------------------------------------
        
        // Why comparison works:
        // ---------------------
        // Allowed operation lets us swap indices where (j - i) is even
        // → means we can only swap within SAME parity:
        //    even ↔ even
        //    odd  ↔ odd
        
        // So:
        // - All even index characters can be rearranged freely among themselves
        // - All odd index characters can be rearranged freely among themselves
        
        // Therefore:
        // For s1 to become s2:
        // - even1 must match even2 (same characters at even positions)
        // - odd1 must match odd2 (same characters at odd positions)
        
        
        // vector comparison:
        // (even1 == even2) checks if all 26 counts match exactly
        
        return (even1 == even2) && (odd1 == odd2);
    }
};
// Time: O(n)
// Space: O(1) (since only 26 letters)
