// 1559. Detect Cycles in 2D Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given a 2D array of characters grid of size m x n, you need to find if there exists any cycle consisting of the same value in grid.

// A cycle is a path of length 4 or more in the grid that starts and ends at the same cell. From a given cell, you can move to one of the cells adjacent to it - in one of the four directions (up, down, left, or right), if it has the same value of the current cell.

// Also, you cannot move to the cell that you visited in your last move. For example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1, 2) we visited (1, 1) which was the last visited cell.

// Return true if any cycle of the same value exists in grid, otherwise, return false.

 

// Example 1:



// Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
// Output: true
// Explanation: There are two valid cycles shown in different colors in the image below:

// Example 2:



// Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
// Output: true
// Explanation: There is only one valid cycle highlighted in the image below:

// Example 3:



// Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
// Output: false
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 500
// grid consists only of lowercase English letters.
// solu = 
class Solution {
public:
    
    // Direction vectors to move in 4 directions:
    // up, down, left, right
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

    
    /*
    DFS FUNCTION PURPOSE:
    ---------------------
    From a given cell (x, y), explore all connected cells
    with the same character and check if a cycle exists.

    PARAMETERS:
    x, y  -> current cell
    px, py -> parent cell (the cell we came from)
              This is CRUCIAL to avoid false cycle detection
    grid  -> input grid
    vis   -> visited matrix

    RETURNS:
    true  -> if a cycle is found
    false -> otherwise
    */
    bool dfs(int x, int y, int px, int py,
             vector<vector<char>>& grid,
             vector<vector<bool>>& vis) {
        
        // Mark current cell as visited
        vis[x][y] = true;

        int m = grid.size();
        int n = grid[0].size();

        
        // Explore all 4 directions from current cell
        for (int d = 0; d < 4; d++) {

            int nx = x + dx[d];  // next row
            int ny = y + dy[d];  // next column

            
            // STEP 1: Boundary check
            // Skip invalid positions outside grid
            if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;

            
            // STEP 2: Character match condition
            // We can ONLY move to cells having SAME character
            if (grid[nx][ny] != grid[x][y]) continue;

            
            // STEP 3: If next cell is NOT visited → explore deeper
            if (!vis[nx][ny]) {

                // Recursive DFS call
                if (dfs(nx, ny, x, y, grid, vis)) {
                    return true;  // propagate cycle detection upward
                }
            }
            else {

                /*
                STEP 4: Cycle detection condition
                
                If the neighbor is already visited AND
                it is NOT the parent cell → we found a cycle

                WHY parent check?
                ------------------
                Example invalid cycle:
                A → B → A

                Without parent check:
                we would incorrectly detect a cycle immediately

                So we ensure:
                we are not just going back to where we came from
                */
                if (nx != px || ny != py) {
                    return true;
                }
            }
        }

        
        // No cycle found from this path
        return false;
    }

    
    bool containsCycle(vector<vector<char>>& grid) {
        
        int m = grid.size();
        int n = grid[0].size();

        
        // Visited matrix:
        // Keeps track of cells already explored
        vector<vector<bool>> vis(m, vector<bool>(n, false));

        
        /*
        MAIN IDEA:
        ----------
        Grid can have multiple disconnected components.
        So we must start DFS from EVERY unvisited cell.
        */
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                // Only start DFS if cell is not visited yet
                if (!vis[i][j]) {

                    /*
                    Start DFS with parent = (-1, -1)
                    because starting cell has no parent
                    */
                    if (dfs(i, j, -1, -1, grid, vis)) {
                        return true;  // cycle found anywhere in grid
                    }
                }
            }
        }

        
        // If no cycle found after exploring entire grid
        return false;
    }
};
// Time Complexity
// O(m * n)
// Each cell visited once
// Space Complexity
// O(m * n)
// Visited matrix + recursion stack
