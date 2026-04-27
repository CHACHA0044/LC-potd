// 1391. Check if There is a Valid Path in a Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:

// 1 which means a street connecting the left cell and the right cell.
// 2 which means a street connecting the upper cell and the lower cell.
// 3 which means a street connecting the left cell and the lower cell.
// 4 which means a street connecting the right cell and the lower cell.
// 5 which means a street connecting the left cell and the upper cell.
// 6 which means a street connecting the right cell and the upper cell.

// You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

// Notice that you are not allowed to change any street.

// Return true if there is a valid path in the grid or false otherwise.

 

// Example 1:


// Input: grid = [[2,4,3],[6,5,2]]
// Output: true
// Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
// Example 2:


// Input: grid = [[1,2,1],[1,2,1]]
// Output: false
// Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
// Example 3:

// Input: grid = [[1,1,2]]
// Output: false
// Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 300
// 1 <= grid[i][j] <= 6
// solu -
class Solution {
public:

    bool hasValidPath(vector<vector<int>>& grid) {
        
        int m = grid.size();       // number of rows
        int n = grid[0].size();    // number of columns


        /*
        STEP 1: Define movement directions
        
        We encode directions as:
        0 → Right  (0, +1)
        1 → Left   (0, -1)
        2 → Down   (+1, 0)
        3 → Up     (-1, 0)
        
        This indexing is important because we will use it
        consistently for both movement and reverse direction checks.
        */
        vector<vector<int>> dirs = {
            {0,1}, {0,-1}, {1,0}, {-1,0}
        };


        /*
        STEP 2: Street type → allowed directions mapping
        
        Each street type tells us:
        "From this cell, which directions can we move?"

        Example:
        Type 1 → left ↔ right → [right(0), left(1)]
        Type 2 → up ↔ down   → [down(2), up(3)]

        This mapping is the CORE of the problem.
        */
        vector<vector<int>> street = {
            {},         // dummy index (0 unused)
            {0,1},      // type 1: left ↔ right
            {2,3},      // type 2: up ↔ down
            {1,2},      // type 3: left ↔ down
            {0,2},      // type 4: right ↔ down
            {1,3},      // type 5: left ↔ up
            {0,3}       // type 6: right ↔ up
        };


        /*
        STEP 3: Visited matrix
        
        We need this to avoid:
        - infinite loops
        - re-processing same cells
        */
        vector<vector<bool>> vis(m, vector<bool>(n, false));


        /*
        STEP 4: BFS initialization
        
        We start from (0,0) because problem requires path from top-left.
        */
        queue<pair<int,int>> q;
        q.push({0,0});
        vis[0][0] = true;


        /*
        STEP 5: BFS traversal
        
        We explore all reachable cells using valid street connections.
        */
        while (!q.empty()) {

            auto [x, y] = q.front();
            q.pop();


            // If we reached bottom-right → path exists
            if (x == m-1 && y == n-1) return true;


            // Current street type
            int type = grid[x][y];


            /*
            STEP 6: Try all allowed directions from current cell
            
            IMPORTANT:
            We DO NOT try all 4 directions blindly.
            Only directions allowed by current street type.
            */
            for (int d : street[type]) {

                int nx = x + dirs[d][0];
                int ny = y + dirs[d][1];


                // STEP 6.1: Boundary check
                if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;


                // STEP 6.2: Skip already visited cells
                if (vis[nx][ny]) continue;


                int nextType = grid[nx][ny];


                /*
                STEP 7: Connection validation (MOST IMPORTANT PART)
                
                Moving from (x,y) → (nx,ny) is valid ONLY IF:
                
                1. Current cell allows direction 'd'
                2. Next cell allows the OPPOSITE direction
                
                Example:
                If we go RIGHT (0),
                the next cell MUST allow LEFT (1)
                */


                // Compute opposite direction
                int opposite;
                if (d == 0) opposite = 1;       // right → left
                else if (d == 1) opposite = 0;  // left → right
                else if (d == 2) opposite = 3;  // down → up
                else opposite = 2;              // up → down


                /*
                Now check if next cell supports this reverse connection
                */
                bool valid = false;

                for (int nd : street[nextType]) {
                    if (nd == opposite) {
                        valid = true;
                        break;
                    }
                }


                /*
                STEP 8: If connection is valid → proceed
                */
                if (valid) {
                    vis[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }


        /*
        If BFS finishes without reaching destination,
        no valid path exists.
        */
        return false;
    }
};
// Time Complexity
// O(m * n)
// Each cell visited once
// Space Complexity
// O(m * n)
// visited + queue
