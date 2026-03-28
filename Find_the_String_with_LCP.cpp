// 2573. Find the String with LCP
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// We define the lcp matrix of any 0-indexed string word of n lowercase English letters as an n x n grid such that:

// lcp[i][j] is equal to the length of the longest common prefix between the substrings word[i,n-1] and word[j,n-1].
// Given an n x n matrix lcp, return the alphabetically smallest string word that corresponds to lcp. If there is no such string, return an empty string.

// A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "aabd" is lexicographically smaller than "aaca" because the first position they differ is at the third letter, and 'b' comes before 'c'.

 

// Example 1:

// Input: lcp = [[4,0,2,0],[0,3,0,1],[2,0,2,0],[0,1,0,1]]
// Output: "abab"
// Explanation: lcp corresponds to any 4 letter string with two alternating letters. The lexicographically smallest of them is "abab".
// Example 2:

// Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,1]]
// Output: "aaaa"
// Explanation: lcp corresponds to any 4 letter string with a single distinct letter. The lexicographically smallest of them is "aaaa". 
// Example 3:

// Input: lcp = [[4,3,2,1],[3,3,2,1],[2,2,2,1],[1,1,1,3]]
// Output: ""
// Explanation: lcp[3][3] cannot be equal to 3 since word[3,...,3] consists of only a single letter; Thus, no answer exists.
 

// Constraints:

// 1 <= n == lcp.length == lcp[i].length <= 1000
// 0 <= lcp[i][j] <= n

// solu = 
class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        
        // -------------------------------
        // STEP 0: Get size of the matrix
        // -------------------------------
        int n = lcp.size();
        
        
        // ------------------------------------------------------
        // STEP 1: Validate basic properties of LCP matrix
        // ------------------------------------------------------
        
        // Property 1: Diagonal must be lcp[i][i] = n - i
        // Because suffix starting at i matches itself fully
        // Example: word[i..] with word[i..] → full match length = n - i
        
        // Property 2: Symmetry → lcp[i][j] == lcp[j][i]
        // Because LCP between suffix i and j is same as j and i
        
        for(int i = 0; i < n; i++) {
            
            // Check diagonal condition
            if(lcp[i][i] != n - i) {
                return "";  // invalid matrix → no possible string
            }
            
            for(int j = 0; j < n; j++) {
                
                // Check symmetry condition
                if(lcp[i][j] != lcp[j][i]) {
                    return "";  // invalid matrix
                }
            }
        }
        
        
        // ------------------------------------------------------
        // STEP 2: Construct the string (greedy grouping)
        // ------------------------------------------------------
        
        // Initialize string with '?' meaning "not assigned yet"
        string word(n, '?');
        
        // Start assigning characters from 'a'
        char currChar = 'a';
        
        
        // Traverse each index
        for(int i = 0; i < n; i++) {
            
            // If already assigned, skip
            // (it might have been assigned while processing some earlier index)
            if(word[i] != '?') continue;
            
            
            // If we exceed 'z', we cannot assign more distinct groups
            // Because only 26 lowercase letters are allowed
            if(currChar > 'z') {
                return "";
            }
            
            
            // Assign current smallest character to this index
            word[i] = currChar;
            
            
            // --------------------------------------------------
            // Key Rule:
            // If lcp[i][j] > 0 → word[i] must equal word[j]
            // Because they share at least 1 common prefix character
            // --------------------------------------------------
            
            for(int j = i + 1; j < n; j++) {
                
                // If LCP > 0, first character must match
                if(lcp[i][j] > 0) {
                    word[j] = currChar;
                }
            }
            
            // Move to next character for next independent group
            currChar++;
        }
        
        
        // ------------------------------------------------------
        // STEP 3: Verify constructed string using LCP recomputation
        // ------------------------------------------------------
        
        // Why needed?
        // Because grouping using lcp[i][j] > 0 is necessary but NOT sufficient
        // Some invalid matrices can still pass construction phase
        // So we must recompute LCP and compare
        
        
        // Create a matrix to compute LCP of constructed string
        vector<vector<int>> calc(n, vector<int>(n, 0));
        
        
        // We compute LCP using bottom-up DP
        // Start from bottom-right corner
        
        for(int i = n - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                
                // If characters match
                if(word[i] == word[j]) {
                    
                    // If at last position, only 1 character matches
                    if(i == n - 1 || j == n - 1) {
                        calc[i][j] = 1;
                    }
                    else {
                        // Otherwise:
                        // LCP = 1 + LCP of next suffixes
                        calc[i][j] = 1 + calc[i + 1][j + 1];
                    }
                }
                else {
                    // If characters differ → no common prefix
                    calc[i][j] = 0;
                }
                
                
                // --------------------------------------------------
                // Compare computed LCP with given LCP
                // --------------------------------------------------
                
                if(calc[i][j] != lcp[i][j]) {
                    return "";  // mismatch → invalid construction
                }
            }
        }
        
        
        // ------------------------------------------------------
        // STEP 4: If everything matches, return the string
        // ------------------------------------------------------
        return word;
    }
};
// Time: O(n²)
// Space: O(n²)
