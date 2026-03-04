// 1582. Special Positions in a Binary Matrix
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given an m x n binary matrix mat, return the number of special positions in mat.

// A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).

 

// Example 1:


// Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
// Output: 1
// Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.
// Example 2:


// Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
// Output: 3
// Explanation: (0, 0), (1, 1) and (2, 2) are special positions.
 

// Constraints:

// m == mat.length
// n == mat[i].length
// 1 <= m, n <= 100
// mat[i][j] is eithe


//solu=
class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        
        int m = mat.size();
        int n = mat[0].size();
        
        /*
        rowCount[i]  -> number of 1s in row i
        colCount[j]  -> number of 1s in column j
        */
        vector<int> rowCount(m, 0);
        vector<int> colCount(n, 0);
        
        /*
        Step 1: Count how many 1s appear in each row and column
        */
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(mat[i][j] == 1) {
                    rowCount[i]++;
                    colCount[j]++;
                }
            }
        }
        
        int special = 0;
        
        /*
        Step 2: Check each cell
        A position is special if:
        - It contains a 1
        - Its row has exactly one 1
        - Its column has exactly one 1
        */
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(mat[i][j] == 1 && rowCount[i] == 1 && colCount[j] == 1) {
                    special++;
                }
            }
        }
        
        return special;
    }
};
//tc= O(m * n)
//sc= O(m + n)
