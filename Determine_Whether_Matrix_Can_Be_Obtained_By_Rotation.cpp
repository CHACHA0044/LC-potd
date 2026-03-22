// 1886. Determine Whether Matrix Can Be Obtained By Rotation
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given two n x n binary matrices mat and target, return true if it is possible to make mat equal to target by rotating mat in 90-degree increments, or false otherwise.

 

// Example 1:


// Input: mat = [[0,1],[1,0]], target = [[1,0],[0,1]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise to make mat equal target.
// Example 2:


// Input: mat = [[0,1],[1,1]], target = [[1,0],[0,1]]
// Output: false
// Explanation: It is impossible to make mat equal to target by rotating mat.
// Example 3:


// Input: mat = [[0,0,0],[0,1,0],[1,1,1]], target = [[1,1,1],[0,1,0],[0,0,0]]
// Output: true
// Explanation: We can rotate mat 90 degrees clockwise two times to make mat equal target.
 

// Constraints:

// n == mat.length == target.length
// n == mat[i].length == target[i].length
// 1 <= n <= 10
// mat[i][j] and target[i][j] are either 0 or 1.

// solu = 
 class Solution {
public:

    /*
    Rotate matrix 90° clockwise IN-PLACE.

    Why this method?
    Instead of creating a new matrix (extra space),
    we use a well-known trick:

    1. Transpose → convert rows into columns
    2. Reverse each row → gives final rotated matrix

    Example:
    [1 2]       [1 3]       [3 1]
    [3 4]  -->  [2 4]  -->  [4 2]
    */
    void rotate90(vector<vector<int>>& mat) {
        int n = mat.size();

        // Step 1: Transpose (swap across diagonal)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(mat[i][j], mat[j][i]);
            }
        }

        // Step 2: Reverse every row
        for (int i = 0; i < n; i++) {
            reverse(mat[i].begin(), mat[i].end());
        }
    }

    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {

        /*
        Instead of writing separate comparison logic,
        we directly compare matrices using ==

        Also, we try all 4 possible orientations:
        0°, 90°, 180°, 270°
        */
        for (int rotation = 0; rotation < 4; rotation++) {

            // If current matrix matches target → success
            if (mat == target) {
                return true;
            }

            // Otherwise rotate for next attempt
            rotate90(mat);
        }

        /*
        If after all 4 rotations we didn't match,
        then it's impossible.
        */
        return false;
    }
};
// Time: O(4 × n²) ≈ O(n²)
// Space: O(1)
