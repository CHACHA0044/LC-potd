// 1878. Get Biggest Three Rhombus Sums in a Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n integer matrix grid​​​.

// A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:


// Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.

// Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct values, return all of them.

 

// Example 1:


// Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
// Output: [228,216,211]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 20 + 3 + 200 + 5 = 228
// - Red: 200 + 2 + 10 + 4 = 216
// - Green: 5 + 200 + 4 + 2 = 211
// Example 2:


// Input: grid = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [20,9,8]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 4 + 2 + 6 + 8 = 20
// - Red: 9 (area 0 rhombus in the bottom right corner)
// - Green: 8 (area 0 rhombus in the bottom middle)
// Example 3:

// Input: grid = [[7,7,7]]
// Output: [7]
// Explanation: All three possible rhombus sums are the same, so return [7].
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 50
// 1 <= grid[i][j] <= 105

// solu = 
class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size();         // number of rows
        int n = grid[0].size();      // number of columns

        // We want distinct sums in descending order.
        // set automatically keeps values unique,
        // and greater<int> keeps them sorted from largest to smallest.
        set<int, greater<int>> sums;

        // Try every cell as the TOP corner of a rhombus
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {

                // A rhombus of size 0 is just the single cell itself
                sums.insert(grid[r][c]);

                // Now try bigger rhombuses: size = 1, 2, 3, ...
                for (int k = 1; ; k++) {

                    // For a rhombus of size k:
                    // top    = (r, c)
                    // right  = (r+k, c+k)
                    // bottom = (r+2k, c)
                    // left   = (r+k, c-k)

                    int bottom = r + 2 * k;
                    int left = c - k;
                    int right = c + k;

                    // If any corner goes out of the grid,
                    // then this rhombus is invalid, and larger sizes
                    // will also be invalid, so we stop.
                    if (bottom >= m || left < 0 || right >= n) break;

                    int sum = 0;

                    // Start from the top corner
                    int x = r, y = c;

                    // Move from TOP to RIGHT
                    // direction: down-right
                    for (int i = 0; i < k; i++) {
                        sum += grid[x][y];
                        x++;
                        y++;
                    }

                    // Move from RIGHT to BOTTOM
                    // direction: down-left
                    for (int i = 0; i < k; i++) {
                        sum += grid[x][y];
                        x++;
                        y--;
                    }

                    // Move from BOTTOM to LEFT
                    // direction: up-left
                    for (int i = 0; i < k; i++) {
                        sum += grid[x][y];
                        x--;
                        y--;
                    }

                    // Move from LEFT back to TOP
                    // direction: up-right
                    for (int i = 0; i < k; i++) {
                        sum += grid[x][y];
                        x--;
                        y++;
                    }

                    // Store this rhombus border sum
                    sums.insert(sum);
                }
            }
        }

        // Take only the biggest 3 distinct sums
        vector<int> ans;
        for (int x : sums) {
            ans.push_back(x);
            if (ans.size() == 3) break;
        }

        return ans;
    }
};
// tc = O( m * n * K^2 )
// sc = O(number of distinct rhombus sums)
// Let K = min(m, n).

// For each cell, we try all possible rhombus sizes, and each rhombus border takes O(k) to compute.

// So total is about:

// O(m * n * K^2)
