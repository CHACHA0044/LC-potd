// 2812. Find the Safest Path in a Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

// A cell containing a thief if grid[r][c] = 1
// An empty cell if grid[r][c] = 0
// You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

// The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.

// Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

// An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

// The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.

 

// Example 1:


// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
// Example 2:


// Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
// Output: 2
// Explanation: The path depicted in the picture above has a safeness factor of 2 since:
// - The closest cell of the path to the thief at cell (0, 2) is cell (0, 0). The distance between them is | 0 - 0 | + | 0 - 2 | = 2.
// It can be shown that there are no other paths with a higher safeness factor.
// Example 3:


// Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
// Output: 2
// Explanation: The path depicted in the picture above has a safeness factor of 2 since:
// - The closest cell of the path to the thief at cell (0, 3) is cell (1, 2). The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
// - The closest cell of the path to the thief at cell (3, 0) is cell (3, 2). The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
// It can be shown that there are no other paths with a higher safeness factor.
 

// Constraints:

// 1 <= grid.length == n <= 400
// grid[i].length == n
// grid[i][j] is either 0 or 1.
// There is at least one thief in the grid.
class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();

        // dist[i][j] stores the minimum Manhattan distance
        // from cell (i, j) to the nearest thief.
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        queue<pair<int,int>> q;

        // Push every thief into the queue as a BFS source.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j]) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        // Multi-source BFS to compute the minimum distance
        // of every cell from the nearest thief.
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < n &&
                    dist[nr][nc] == INT_MAX) {

                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Max heap stores:
        // {current safeness factor, row, column}
        priority_queue<vector<int>> pq;

        vector<vector<int>> vis(n, vector<int>(n, 0));

        // Start from the top-left cell.
        pq.push({dist[0][0], 0, 0});

        while (!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            int safe = cur[0];
            int r = cur[1];
            int c = cur[2];

            // Skip already processed cells.
            if (vis[r][c]) continue;
            vis[r][c] = 1;

            // First time reaching the destination gives
            // the maximum possible safeness factor.
            if (r == n - 1 && c == n - 1)
                return safe;

            // Explore all four neighbouring cells.
            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr >= 0 && nr < n &&
                    nc >= 0 && nc < n &&
                    !vis[nr][nc]) {

                    // Safeness of the new path is limited by
                    // the minimum distance encountered so far.
                    pq.push({min(safe, dist[nr][nc]), nr, nc});
                }
            }
        }

        return 0;
    }
};

/*
Time Complexity: O(n^2 log(n^2)) = O(n^2 log n)

Space Complexity: O(n^2)
*/
