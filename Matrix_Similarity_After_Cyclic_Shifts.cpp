// 2946. Matrix Similarity After Cyclic Shifts
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n integer matrix mat and an integer k. The matrix rows are 0-indexed.

// The following proccess happens k times:

// Even-indexed rows (0, 2, 4, ...) are cyclically shifted to the left.


// Odd-indexed rows (1, 3, 5, ...) are cyclically shifted to the right.


// Return true if the final modified matrix after k steps is identical to the original matrix, and false otherwise.

 

// Example 1:

// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 4

// Output: false

// Explanation:

// In each step left shift is applied to rows 0 and 2 (even indices), and right shift to row 1 (odd index).



// Example 2:

// Input: mat = [[1,2,1,2],[5,5,5,5],[6,3,6,3]], k = 2

// Output: true

// Explanation:



// Example 3:

// Input: mat = [[2,2],[2,2]], k = 3

// Output: true

// Explanation:

// As all the values are equal in the matrix, even after performing cyclic shifts the matrix will remain the same.

 

// Constraints:

// 1 <= mat.length <= 25
// 1 <= mat[i].length <= 25
// 1 <= mat[i][j] <= 25
// 1 <= k <= 50

// sol u = 
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        
        // Step 1: Get matrix dimensions
        int m = mat.size();        // number of rows
        int n = mat[0].size();    // number of columns
        
        // Step 2: Reduce k using modulo
        // --------------------------------
        // Since shifting a row n times brings it back to original,
        // we only care about k % n shifts.
        // Example:
        // n = 4, k = 10 → effective shifts = 10 % 4 = 2
        int shift = k % n;
        
        // Step 3: Traverse each element of the matrix
        for(int i = 0; i < m; i++) {          // iterate over rows
            for(int j = 0; j < n; j++) {      // iterate over columns
                
                // Case 1: EVEN indexed row (0, 2, 4, ...)
                // ---------------------------------------
                // These rows are shifted LEFT.
                // After shifting left by 'shift':
                // element originally at index (j + shift) % n
                // will come to index j.
                if(i % 2 == 0) {
                    
                    // Compare current element with the element
                    // that should come here after shifting
                    if(mat[i][j] != mat[i][(j + shift) % n]) {
                        // If mismatch found → matrix is NOT same
                        return false;
                    }
                }
                
                // Case 2: ODD indexed row (1, 3, 5, ...)
                // ---------------------------------------
                // These rows are shifted RIGHT.
                // After shifting right by 'shift':
                // element originally at index (j - shift + n) % n
                // will come to index j.
                else {
                    
                    // (j - shift + n) ensures index stays non-negative
                    if(mat[i][j] != mat[i][(j - shift + n) % n]) {
                        // If mismatch found → matrix is NOT same
                        return false;
                    }
                }
            }
        }
        
        // Step 4: If no mismatches found in entire matrix
        // -----------------------------------------------
        // It means after k cyclic shifts, matrix remains identical
        return true;
    }
};
// Time Complexity: O(m * n)
// Space Complexity: O(1)
