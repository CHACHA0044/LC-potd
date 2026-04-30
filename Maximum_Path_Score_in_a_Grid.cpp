// 3742. Maximum Path Score in a Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n grid where each cell contains one of the values 0, 1, or 2. You are also given an integer k.

// You start from the top-left corner (0, 0) and want to reach the bottom-right corner (m - 1, n - 1) by moving only right or down.

// Each cell contributes a specific score and incurs an associated cost, according to their cell values:

// 0: adds 0 to your score and costs 0.
// 1: adds 1 to your score and costs 1.
// 2: adds 2 to your score and costs 1. ​​​​​​​
// Return the maximum score achievable without exceeding a total cost of k, or -1 if no valid path exists.

// Note: If you reach the last cell but the total cost exceeds k, the path is invalid.

 

// Example 1:

// Input: grid = [[0, 1],[2, 0]], k = 1

// Output: 2

// Explanation:​​​​​​​

// The optimal path is:

// Cell	grid[i][j]	Score	Total
// Score	Cost	Total
// Cost
// (0, 0)	0	0	0	0	0
// (1, 0)	2	2	2	1	1
// (1, 1)	0	0	2	0	1
// Thus, the maximum possible score is 2.

// Example 2:

// Input: grid = [[0, 1],[1, 2]], k = 1

// Output: -1

// Explanation:

// There is no path that reaches cell (1, 1)​​​​​​​ without exceeding cost k. Thus, the answer is -1.

 

// Constraints:

// 1 <= m, n <= 200
// 0 <= k <= 103​​​​​​​
// ​​​​​​​grid[0][0] == 0
// 0 <= grid[i][j] <= 2
// solu = 
class Solution {
public:
    int maximumScore(vector<vector<int>>& grid, int k) {
        
        int m = grid.size();
        int n = grid[0].size();

        
        /*
        STEP 1: 3D DP
        
        dp[i][j][c] =
        maximum score to reach (i,j) using total cost = c
        
        Initialize with -1 (invalid/unreachable state)
        */
        vector<vector<vector<int>>> dp(
            m, vector<vector<int>>(n, vector<int>(k + 1, -1))
        );


        /*
        STEP 2: Initialize start cell (0,0)
        
        grid[0][0] = 0 → score = 0, cost = 0
        */
        dp[0][0][0] = 0;


        /*
        STEP 3: Traverse grid
        */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                for (int cost = 0; cost <= k; cost++) {

                    // Skip invalid states
                    if (dp[i][j][cost] == -1) continue;


                    /*
                    STEP 4: Move RIGHT
                    */
                    if (j + 1 < n) {

                        int val = grid[i][j + 1];

                        
                        // Determine score & cost of next cell
                        int addScore = val;
                        int addCost = (val == 0 ? 0 : 1);

                        
                        int newCost = cost + addCost;

                        
                        // Only proceed if within allowed cost
                        if (newCost <= k) {
                            dp[i][j + 1][newCost] = max(
                                dp[i][j + 1][newCost],
                                dp[i][j][cost] + addScore
                            );
                        }
                    }


                    /*
                    STEP 5: Move DOWN
                    */
                    if (i + 1 < m) {

                        int val = grid[i + 1][j];

                        int addScore = val;
                        int addCost = (val == 0 ? 0 : 1);

                        int newCost = cost + addCost;

                        if (newCost <= k) {
                            dp[i + 1][j][newCost] = max(
                                dp[i + 1][j][newCost],
                                dp[i][j][cost] + addScore
                            );
                        }
                    }
                }
            }
        }


        /*
        STEP 6: Find best answer at destination
        
        We can reach (m-1, n-1) with different costs,
        so take max score among all valid costs ≤ k
        */
        int ans = -1;

        for (int c = 0; c <= k; c++) {
            ans = max(ans, dp[m - 1][n - 1][c]);
        }

        return ans;
    }
};
// Time Complexity
// O(m * n * k)
// m*n cells
// k cost states
// Max:
// 200 * 200 * 1000 = 40M → OK in C++
// Space Complexity
// O(m * n * k)
