// 3070. Count Submatrices with Top-Left Element and Sum Less Than k
// Medium
// Topics
// premium lock icon
// Companies
// You are given a 0-indexed integer matrix grid and an integer k.

// Return the number of submatrices that contain the top-left element of the grid, and have a sum less than or equal to k.

 

// Example 1:


// Input: grid = [[7,6,3],[6,6,1]], k = 18
// Output: 4
// Explanation: There are only 4 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 18.
// Example 2:


// Input: grid = [[7,2,9],[1,5,0],[2,6,6]], k = 20
// Output: 6
// Explanation: There are only 6 submatrices, shown in the image above, that contain the top-left element of grid, and have a sum less than or equal to 20.
 

// Constraints:

// m == grid.length 
// n == grid[i].length
// 1 <= n, m <= 1000 
// 0 <= grid[i][j] <= 1000
// 1 <= k <= 109

// solu = 
class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();        // number of rows
        int n = grid[0].size();     // number of columns

        int count = 0;              // final answer

        // ------------------------------------------------------------
        // KEY IDEA:
        // Every valid submatrix MUST include (0,0)
        //
        // So each submatrix is uniquely defined by its bottom-right corner (i, j)
        //
        // That means:
        // Submatrix = rectangle from (0,0) to (i,j)
        //
        // So instead of checking all submatrices,
        // we just compute sum(0,0 → i,j) for every cell.
        // ------------------------------------------------------------

        // ------------------------------------------------------------
        // STEP 1: Convert grid into prefix sum matrix (in-place)
        //
        // After this:
        // grid[i][j] will store sum of rectangle from (0,0) to (i,j)
        // ------------------------------------------------------------

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Add sum from the cell ABOVE (i-1, j)
                if (i > 0) {
                    grid[i][j] += grid[i - 1][j];
                }

                // Add sum from the cell LEFT (i, j-1)
                if (j > 0) {
                    grid[i][j] += grid[i][j - 1];
                }

                // We added top and left, but top-left got counted twice
                // So subtract it once to fix double counting
                if (i > 0 && j > 0) {
                    grid[i][j] -= grid[i - 1][j - 1];
                }

                // Now grid[i][j] correctly stores:
                // sum of submatrix from (0,0) to (i,j)

                // ----------------------------------------------------
                // STEP 2: Check if this submatrix is valid
                //
                // If sum ≤ k → count it
                // ----------------------------------------------------
                if (grid[i][j] <= k) {
                    count++;
                }
            }
        }

        return count;
    }
};
// tc = O(m × n)
// sc = O(1)

// Formula used
// For prefix sum:

// grid[i][j] =
//     grid[i][j]           (original value)
//   + grid[i-1][j]         (top)
//   + grid[i][j-1]         (left)
//   - grid[i-1][j-1]       (remove double count)
