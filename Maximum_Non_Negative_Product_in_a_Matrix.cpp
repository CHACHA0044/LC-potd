// 1594. Maximum Non Negative Product in a Matrix
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.

// Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.

// Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.

// Notice that the modulo is performed after getting the maximum product.

 

// Example 1:


// Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
// Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
// Example 2:


// Input: grid = [[1,-2,1],[1,-2,1],[3,-4,1]]
// Output: 8
// Explanation: Maximum non-negative product is shown (1 * 1 * -2 * -4 * 1 = 8).
// Example 3:


// Input: grid = [[1,3],[0,-4]]
// Output: 0
// Explanation: Maximum non-negative product is shown (1 * 0 * -4 = 0).
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 15
// -4 <= grid[i][j] <= 4

// solu = 

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        /*
        IMPORTANT IDEA:
        ----------------
        At every cell, we don't store just ONE value.

        Why?
        Because multiplication with negative numbers can flip signs.

        Example:
        -2 * -3 = +6 (good)
        +6 * -1 = -6 (bad)

        So a "minimum" value today might become "maximum" later.

        👉 Therefore, we track:
            dpMax[i][j] → maximum product to reach (i,j)
            dpMin[i][j] → minimum product to reach (i,j)
        */
        vector<vector<long long>> dpMax(m, vector<long long>(n));
        vector<vector<long long>> dpMin(m, vector<long long>(n));

        /*
        BASE CASE:
        Start at (0,0)
        Only one value → both max and min are same
        */
        dpMax[0][0] = dpMin[0][0] = grid[0][0];

        /*
        FIRST ROW:
        ----------
        You can ONLY come from the left.

        So:
        dp[i][j] = dp[i][j-1] * current_value

        No branching here, but sign still matters.
        */
        for (int j = 1; j < n; j++) {
            dpMax[0][j] = dpMax[0][j - 1] * grid[0][j];
            dpMin[0][j] = dpMax[0][j];  // same value (only one path)
        }

        /*
        FIRST COLUMN:
        -------------
        You can ONLY come from above.
        */
        for (int i = 1; i < m; i++) {
            dpMax[i][0] = dpMax[i - 1][0] * grid[i][0];
            dpMin[i][0] = dpMax[i][0];  // same reason
        }

        /*
        MAIN DP LOGIC:
        --------------
        For each cell (i,j), we can come from:
        - Top (i-1, j)
        - Left (i, j-1)

        From EACH direction, we consider BOTH:
        - max value
        - min value

        Because:
        negative × negative = positive
        positive × negative = negative

        So total 4 possibilities:
        */
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {

                long long val = grid[i][j];

                // From top
                long long topMax = dpMax[i - 1][j] * val;
                long long topMin = dpMin[i - 1][j] * val;

                // From left
                long long leftMax = dpMax[i][j - 1] * val;
                long long leftMin = dpMin[i][j - 1] * val;

                /*
                Now we have 4 candidates:
                - topMax
                - topMin
                - leftMax
                - leftMin

                We pick:
                - maximum among them → dpMax
                - minimum among them → dpMin

                This ensures we never lose a potentially useful value.
                */
                dpMax[i][j] = max({topMax, topMin, leftMax, leftMin});
                dpMin[i][j] = min({topMax, topMin, leftMax, leftMin});
            }
        }

        /*
        FINAL ANSWER:
        --------------
        We want MAXIMUM NON-NEGATIVE product.

        So we check dpMax at destination.
        */
        long long result = dpMax[m - 1][n - 1];

        /*
        If result is negative → no valid non-negative path exists
        */
        if (result < 0) return -1;

        /*
        IMPORTANT:
        We apply modulo ONLY at the end.

        Why?
        Because applying modulo earlier can break sign tracking
        and ruin correctness.
        */
        int MOD = 1e9 + 7;
        return result % MOD;
    }
};
// tc = O(m x n)
// sc = O(m x n)
