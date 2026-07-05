// 1301. Number of Paths with Max Score
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.

// You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

// Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

// In case there is no path, return [0, 0].

 

// Example 1:

// Input: board = ["E23","2X2","12S"]
// Output: [7,1]
// Example 2:

// Input: board = ["E12","1X1","21S"]
// Output: [4,2]
// Example 3:

// Input: board = ["E11","XXX","11S"]
// Output: [0,0]
 

// Constraints:

// 2 <= board.length == board[i].length <= 100
class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> pathsWithMaxScore(vector<string>& board) {

        int n = board.size();

        // dp[i][j] stores the maximum score that can be
        // collected from cell (i, j) to the destination 'S'.
        // -1 means this cell cannot reach the destination.
        vector<vector<int>> dp(n, vector<int>(n, -1));

        // ways[i][j] stores the number of maximum-score
        // paths from (i, j) to the destination.
        vector<vector<int>> ways(n, vector<int>(n, 0));

        // Base case:
        // At the destination, score is 0 and
        // there is exactly one way to stay there.
        dp[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        // While filling DP from bottom-right to top-left,
        // we can come to the current cell from:
        // Down, Right or Down-Right.
        int dr[3] = {1, 0, 1};
        int dc[3] = {0, 1, 1};

        // Fill DP in reverse order.
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                // Skip blocked cells and destination,
                // since destination is already initialized.
                if (board[i][j] == 'X' ||
                    (i == n - 1 && j == n - 1))
                    continue;

                int bestScore = -1;
                long long totalWays = 0;

                // Check all three possible next cells.
                for (int k = 0; k < 3; k++) {

                    int ni = i + dr[k];
                    int nj = j + dc[k];

                    // Ignore invalid or unreachable cells.
                    if (ni >= n || nj >= n || dp[ni][nj] == -1)
                        continue;

                    // Found a better score.
                    if (dp[ni][nj] > bestScore) {
                        bestScore = dp[ni][nj];
                        totalWays = ways[ni][nj];
                    }

                    // Same maximum score,
                    // so add the number of paths.
                    else if (dp[ni][nj] == bestScore) {
                        totalWays = (totalWays + ways[ni][nj]) % MOD;
                    }
                }

                // No valid path from this cell.
                if (bestScore == -1)
                    continue;

                // Add the value of the current cell.
                // 'E' and 'S' contribute 0.
                int value = 0;

                if (board[i][j] >= '1' && board[i][j] <= '9')
                    value = board[i][j] - '0';

                dp[i][j] = bestScore + value;
                ways[i][j] = totalWays % MOD;
            }
        }

        // Start cannot reach destination.
        if (dp[0][0] == -1)
            return {0, 0};

        // Return:
        // {maximum score, number of maximum-score paths}
        return {dp[0][0], ways[0][0]};
    }
};

/*
Time Complexity: O(n^2)

Space Complexity: O(n^2)
*/
