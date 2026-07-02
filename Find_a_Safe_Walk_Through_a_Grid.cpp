// 3286. Find a Safe Walk Through a Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n binary matrix grid and an integer health.

// You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).

// You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.

// Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.

// Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.

 

// Example 1:

// Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1

// Output: true

// Explanation:

// The final cell can be reached safely by walking along the gray cells below.


// Example 2:

// Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3

// Output: false

// Explanation:

// A minimum of 4 health points is needed to reach the final cell safely.


// Example 3:

// Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5

// Output: true

// Explanation:

// The final cell can be reached safely by walking along the gray cells below.



// Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.

 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 50
// 2 <= m * n
// 1 <= health <= m + n
// grid[i][j] is either 0 or 1.
class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        // best[r][c] stores the maximum health remaining
        // when reaching cell (r, c).
        vector<vector<int>> best(m, vector<int>(n, -1));

        // Max heap:
        // {remaining health, row, column}
        priority_queue<vector<int>> pq;

        // Enter the starting cell.
        int start = health - grid[0][0];

        // If health becomes zero or negative immediately,
        // we cannot even stand on the first cell.
        if (start <= 0) return false;

        pq.push({start, 0, 0});
        best[0][0] = start;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            int hp = cur[0];
            int r = cur[1];
            int c = cur[2];

            // Destination reached with positive health.
            if (r == m - 1 && c == n - 1)
                return true;

            // Ignore outdated states that are worse than
            // an already discovered path.
            if (hp < best[r][c]) continue;

            // Try moving in all four directions.
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                // Lose one health if the next cell is unsafe.
                int nhp = hp - grid[nr][nc];

                // Visit only if health stays positive and
                // this path leaves us with more health.
                if (nhp > 0 && nhp > best[nr][nc]) {
                    best[nr][nc] = nhp;
                    pq.push({nhp, nr, nc});
                }
            }
        }

        return false;
    }
};

/*
Time Complexity: O(m * n * log(m * n))

Space Complexity: O(m * n)
*/
