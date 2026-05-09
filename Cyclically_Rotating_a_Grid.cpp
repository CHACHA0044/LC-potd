// 1914. Cyclically Rotating a Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.

// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:



// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:


// Return the matrix after applying k cyclic rotations to it.

 

// Example 1:


// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
// Example 2:


// Input: grid = [[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]], k = 2
// Output: [[3,4,8,12],[2,11,10,16],[1,7,6,15],[5,9,13,14]]
// Explanation: The figures above represent the grid at every state.
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 2 <= m, n <= 50
// Both m and n are even integers.
// 1 <= grid[i][j] <= 5000
// 1 <= k <= 109
// solu = 
class Solution {
public:
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {

        int m = grid.size();
        int n = grid[0].size();

        
        /*
        Number of layers in matrix

        Example:
        4 x 4 matrix -> 2 layers
        */
        int layers = min(m, n) / 2;


        /*
        Process every layer independently
        */
        for (int layer = 0; layer < layers; layer++) {

            vector<int> elements;


            /*
            =====================================================
            STEP 1: Extract current layer elements
            =====================================================

            Order:
            top row
            right column
            bottom row
            left column

            This creates a circular sequence.
            */

            int top = layer;
            int bottom = m - layer - 1;

            int left = layer;
            int right = n - layer - 1;


            // top row
            for (int j = left; j <= right; j++) {
                elements.push_back(grid[top][j]);
            }

            // right column
            for (int i = top + 1; i <= bottom - 1; i++) {
                elements.push_back(grid[i][right]);
            }

            // bottom row
            for (int j = right; j >= left; j--) {
                elements.push_back(grid[bottom][j]);
            }

            // left column
            for (int i = bottom - 1; i >= top + 1; i--) {
                elements.push_back(grid[i][left]);
            }


            /*
            =====================================================
            STEP 2: Rotate layer
            =====================================================

            Counter-clockwise rotation by k

            Effective rotations:
            k % layer_size
            */
            int sz = elements.size();

            int rotate = k % sz;

            vector<int> rotated(sz);

            for (int i = 0; i < sz; i++) {

                /*
                Shift left for counter-clockwise rotation
                */
                rotated[i] = elements[(i + rotate) % sz];
            }


            /*
            =====================================================
            STEP 3: Put rotated values back into matrix
            =====================================================
            */
            int idx = 0;


            // top row
            for (int j = left; j <= right; j++) {
                grid[top][j] = rotated[idx++];
            }

            // right column
            for (int i = top + 1; i <= bottom - 1; i++) {
                grid[i][right] = rotated[idx++];
            }

            // bottom row
            for (int j = right; j >= left; j--) {
                grid[bottom][j] = rotated[idx++];
            }

            // left column
            for (int i = bottom - 1; i >= top + 1; i--) {
                grid[i][left] = rotated[idx++];
            }
        }

        return grid;
    }
};
// Time Complexity
// Each cell is processed once:
// O(m × n)
// Space Complexity
// Extra array for one layer:
// O(m + n)
