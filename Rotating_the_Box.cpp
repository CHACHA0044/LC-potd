// 1861. Rotating the Box
// Medium
// // Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:

// A stone '#'
// A stationary obstacle '*'
// Empty '.'
// The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.

// It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.

// Return an n x m matrix representing the box after the rotation described above.

 

// Example 1:



// Input: boxGrid = [["#",".","#"]]
// Output: [["."],
//          ["#"],
//          ["#"]]
// Example 2:



// Input: boxGrid = [["#",".","*","."],
//               ["#","#","*","."]]
// Output: [["#","."],
//          ["#","#"],
//          ["*","*"],
//          [".","."]]
// Example 3:



// Input: boxGrid = [["#","#","*",".","*","."],
//               ["#","#","#","*",".","."],
//               ["#","#","#",".","#","."]]
// Output: [[".","#","#"],
//          [".","#","#"],
//          ["#","#","*"],
//          ["#","*","."],
//          ["#",".","*"],
//          ["#",".","."]]
 

// Constraints:

// m == boxGrid.length
// n == boxGrid[i].length
// 1 <= m, n <= 500
// boxGrid[i][j] is either '#', '*', or '.'.
// solu- 
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {

        int m = boxGrid.size();       // number of rows
        int n = boxGrid[0].size();    // number of columns


        /*
        =========================================================
        STEP 1: Simulate gravity in the ORIGINAL box
        =========================================================

        Since the box will rotate clockwise,
        stones effectively fall DOWN after rotation.

        Instead of rotating first,
        we can simulate this by moving stones RIGHT
        in each row before rotation.

        Example:

        # . # .
        becomes:
        . . # #

        Obstacles '*' stop movement.
        */

        for (int i = 0; i < m; i++) {

            /*
            'empty' stores the next position where
            a stone can fall/move to.

            Initially, rightmost column is available.
            */
            int empty = n - 1;


            /*
            Traverse row from RIGHT → LEFT
            */
            for (int j = n - 1; j >= 0; j--) {

                /*
                CASE 1: Obstacle found

                Stones cannot cross obstacles.

                So reset empty position to:
                immediately LEFT of obstacle.
                */
                if (boxGrid[i][j] == '*') {
                    empty = j - 1;
                }


                /*
                CASE 2: Stone found

                Move stone to the current empty position.
                */
                else if (boxGrid[i][j] == '#') {

                    /*
                    Remove stone from current position
                    */
                    boxGrid[i][j] = '.';


                    /*
                    Place stone at rightmost available spot
                    */
                    boxGrid[i][empty] = '#';


                    /*
                    Next empty slot shifts left
                    */
                    empty--;
                }
            }
        }


        /*
        =========================================================
        STEP 2: Rotate matrix 90 degrees clockwise
        =========================================================

        Original size:
        m × n

        Rotated size:
        n × m

        Rotation mapping:
        (i, j) → (j, m-1-i)
        */

        vector<vector<char>> ans(n, vector<char>(m));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                ans[j][m - 1 - i] = boxGrid[i][j];
            }
        }


        return ans;
    }
};
// Rotation Formula
// For clockwise rotation:
// (i, j) → (j, m-1-i)
// VERY important matrix trick.

// Why simulate gravity BEFORE rotation?
// Because:
// after clockwise rotation,
// “downward falling” becomes
// “rightward movement” in original orientation
// This simplifies everything.
  
// Time Complexity
// Gravity simulation:
// O(m × n)
// Rotation:
// O(m × n)
// Total:
// O(m × n)
  
// Space Complexity
// O(m × n)
// (for rotated matrix)
