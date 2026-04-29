// 3225. Maximum Score From Grid Operations
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.

// The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.

// Return the maximum score that can be achieved after some number of operations.

 

// Example 1:

// Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]

// Output: 11

// Explanation:


// In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.

// Example 2:

// Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]

// Output: 94

// Explanation:


// We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. The score of the resulting grid is grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4] which is equal to 94.

 

// Constraints:

// 1 <= n == grid.length <= 100
// n == grid[i].length
// 0 <= grid[i][j] <= 109
// solu =
class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {

        int n = grid.size();        // number of rows
        int m = grid[0].size();    // number of columns

        // If only one column → no horizontal neighbor exists → score = 0
        if (m == 1) return 0;


        /*
        STEP 1: Prefix sums for each column
        
        col[j][i] = sum of values in column j from row 0 to row i-1
        
        This allows O(1) range sum queries:
        sum of rows [l, r-1] = col[j][r] - col[j][l]
        */
        vector<vector<long long>> col(m, vector<long long>(n + 1, 0));

        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                col[j][i + 1] = col[j][i] + grid[i][j];
            }
        }


        /*
        STEP 2: DP Definition
        
        dp[curr][prev] =
        Maximum score considering processed columns so far,
        where:
            - current column has height = curr
            - previous column had height = prev
        
        Height = last row painted black (so rows ≤ height are black)
        */
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));


        /*
        Optimization arrays:
        
        prefMax[curr][prev] → prefix maximum (left to right)
        suffMax[curr][prev] → suffix maximum (right to left)
        
        These help reduce O(n³) → O(n²)
        */
        vector<vector<long long>> prefMax(n + 1, vector<long long>(n + 1, 0));
        vector<vector<long long>> suffMax(n + 1, vector<long long>(n + 1, 0));


        /*
        STEP 3: Process columns from left to right
        */
        for (int c = 1; c < m; c++) {

            // New DP for this column
            vector<vector<long long>> newdp(n + 1, vector<long long>(n + 1, 0));


            /*
            STEP 4: Transition
            
            curr = height of current column
            prev = height of previous column
            */
            for (int curr = 0; curr <= n; curr++) {
                for (int prev = 0; prev <= n; prev++) {

                    if (curr <= prev) {
                        /*
                        CASE 1: curr ≤ prev
                        
                        Current column has fewer black cells than previous.
                        
                        Contribution comes from:
                        rows in (curr, prev] → white in current but black in previous
                        
                        So we take values from column c
                        */
                        long long gain = col[c][prev] - col[c][curr];

                        newdp[curr][prev] = max(
                            newdp[curr][prev],
                            suffMax[prev][0] + gain
                        );
                    }
                    else {
                        /*
                        CASE 2: curr > prev
                        
                        Current column has more black cells than previous.
                        
                        Contribution comes from:
                        rows in (prev, curr] → white in previous but black in current
                        
                        So we take values from column c-1
                        */
                        long long gain = col[c-1][curr] - col[c-1][prev];

                        newdp[curr][prev] = max({
                            newdp[curr][prev],

                            // case without gain
                            suffMax[prev][curr],

                            // case including gain
                            prefMax[prev][curr] + gain
                        });
                    }
                }
            }


            /*
            STEP 5: Build prefix and suffix maximum arrays
            
            These allow fast DP transitions instead of nested loops
            */

            for (int curr = 0; curr <= n; curr++) {

                // Build prefix max (left → right)
                prefMax[curr][0] = newdp[curr][0];

                for (int prev = 1; prev <= n; prev++) {

                    /*
                    If prev > curr, subtract penalty
                    (because part already counted in gain logic)
                    */
                    long long penalty = 0;
                    if (prev > curr)
                        penalty = col[c][prev] - col[c][curr];

                    prefMax[curr][prev] = max(
                        prefMax[curr][prev - 1],
                        newdp[curr][prev] - penalty
                    );
                }


                // Build suffix max (right → left)
                suffMax[curr][n] = newdp[curr][n];

                for (int prev = n - 1; prev >= 0; prev--) {
                    suffMax[curr][prev] = max(
                        suffMax[curr][prev + 1],
                        newdp[curr][prev]
                    );
                }
            }


            // Move newdp → dp for next iteration
            dp = move(newdp);
        }


        /*
        STEP 6: Final answer
        
        Valid final states are:
        curr = 0 (no black)
        curr = n (all black)
        */
        long long ans = 0;

        for (int k = 0; k <= n; k++) {
            ans = max({ans, dp[0][k], dp[n][k]});
        }

        return ans;
    }
};
// Time Complexity
// O(m * n²)
// m columns
// n² states
// optimized transitions
// Space Complexity
// O(n²)
// DP + prefix/suffix arrays
