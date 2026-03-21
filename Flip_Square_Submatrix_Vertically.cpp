// 3643. Flip Square Submatrix Vertically
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n integer matrix grid, and three integers x, y, and k.

// The integers x and y represent the row and column indices of the top-left corner of a square submatrix and the integer k represents the size (side length) of the square submatrix.

// Your task is to flip the submatrix by reversing the order of its rows vertically.

// Return the updated matrix.

 

// Example 1:


// Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], x = 1, y = 0, k = 3

// Output: [[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]

// Explanation:

// The diagram above shows the grid before and after the transformation.

// Example 2:

// ​​​​​​​
// Input: grid = [[3,4,2,3],[2,3,4,2]], x = 0, y = 2, k = 2

// Output: [[3,4,4,2],[2,3,2,3]]

// Explanation:

// The diagram above shows the grid before and after the transformation.

 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 50
// 1 <= grid[i][j] <= 100
// 0 <= x < m
// 0 <= y < n
// 1 <= k <= min(m - x, n - y)

// solu = 
class Solution {
public:
    vector<vector<int>> flipSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        int m = grid.size();
        int n = grid[0].size();

        /*
        Goal:
        We are given a k x k square starting at (x, y).
        We need to flip this square "vertically".

        Vertical flip means:
        - Reverse the order of rows inside this square
        - Columns remain unchanged

        Example idea:
        Row x           ↔ Row x + k - 1
        Row x + 1       ↔ Row x + k - 2
        and so on...

        So instead of creating a new matrix, we do it IN-PLACE by swapping rows.
        */

        // We only iterate through half of the rows because each swap fixes two rows
        for (int i = 0; i < k / 2; i++) {
            
            // Identify the pair of rows to swap
            int topRow = x + i;                 // current row from top
            int bottomRow = x + k - 1 - i;      // corresponding row from bottom

            /*
            Now, we don't swap entire rows blindly,
            because we only want to affect the square region (columns y to y+k-1).

            So we swap element-by-element within the square.
            */
            for (int j = 0; j < k; j++) {
                int col = y + j;  // actual column inside the grid

                // Swap the elements of the two rows at this column
                swap(grid[topRow][col], grid[bottomRow][col]);
            }
        }

        /*
        Why this approach?
        - In-place: No extra space used
        - Efficient: Only touches k x k elements
        - Simple: Just reversing rows using two-pointer style

        Time Complexity: O(k^2)
        Space Complexity: O(1)
        */

        return grid;
    }
};
// tc = O(k²) → we process k × k square
// sc = O(1) → in-place swapping
