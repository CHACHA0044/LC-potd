// 3212. Count Submatrices With Equal Frequency of X and Y
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:

// grid[0][0]
// an equal frequency of 'X' and 'Y'.
// at least one 'X'.
 

// Example 1:

// Input: grid = [["X","Y","."],["Y",".","."]]

// Output: 3

// Explanation:



// Example 2:

// Input: grid = [["X","X"],["X","Y"]]

// Output: 0

// Explanation:

// No submatrix has an equal frequency of 'X' and 'Y'.

// Example 3:

// Input: grid = [[".","."],[".","."]]

// Output: 0

// Explanation:

// No submatrix has at least one 'X'.

 

// Constraints:

// 1 <= grid.length, grid[i].length <= 1000
// grid[i][j] is either 'X', 'Y', or '.'.

// solu - 
class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        
        // Get dimensions of the grid
        int n = grid.size(), m = grid[0].size();

        // sum[i][j] will store the prefix sum of transformed values
        // (X = +1, Y = -1, . = 0) from (0,0) to (i,j)
        vector<vector<int>> sum(n, vector<int>(m, 0));

        // countX[i][j] will store how many 'X' are present
        // in submatrix from (0,0) to (i,j)
        vector<vector<int>> countX(n, vector<int>(m, 0));

        // Step 1: Build prefix sum matrices
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {

                // Convert grid value to numeric:
                // X → +1, Y → -1, . → 0
                int val = 0;
                if(grid[i][j] == 'X') val = 1;
                else if(grid[i][j] == 'Y') val = -1;

                // Initialize current cell
                sum[i][j] = val;

                // countX tracks number of X's
                countX[i][j] = (grid[i][j] == 'X');

                // Add contribution from top cell (i-1, j)
                if(i > 0) {
                    sum[i][j] += sum[i-1][j];
                    countX[i][j] += countX[i-1][j];
                }

                // Add contribution from left cell (i, j-1)
                if(j > 0) {
                    sum[i][j] += sum[i][j-1];
                    countX[i][j] += countX[i][j-1];
                }

                // Remove double-counted area (overlap)
                // This is standard 2D prefix sum correction
                if(i > 0 && j > 0) {
                    sum[i][j] -= sum[i-1][j-1];
                    countX[i][j] -= countX[i-1][j-1];
                }
            }
        }

        int ans = 0;

        // Step 2: Check all submatrices from (0,0) to (i,j)
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {

                // Condition 1: Equal number of X and Y → sum == 0
                // Condition 2: At least one X → countX > 0
                if(sum[i][j] == 0 && countX[i][j] > 0) {
                    ans++;
                }
            }
        }

        return ans;
    }
};

// tc = O(n x m)
// sc = O(n x m)
