// 2075. Decode the Slanted Ciphertext
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// A string originalText is encoded using a slanted transposition cipher to a string encodedText with the help of a matrix having a fixed number of rows rows.

// originalText is placed first in a top-left to bottom-right manner.


// The blue cells are filled first, followed by the red cells, then the yellow cells, and so on, until we reach the end of originalText. The arrow indicates the order in which the cells are filled. All empty cells are filled with ' '. The number of columns is chosen such that the rightmost column will not be empty after filling in originalText.

// encodedText is then formed by appending all characters of the matrix in a row-wise fashion.


// The characters in the blue cells are appended first to encodedText, then the red cells, and so on, and finally the yellow cells. The arrow indicates the order in which the cells are accessed.

// For example, if originalText = "cipher" and rows = 3, then we encode it in the following manner:


// The blue arrows depict how originalText is placed in the matrix, and the red arrows denote the order in which encodedText is formed. In the above example, encodedText = "ch ie pr".

// Given the encoded string encodedText and number of rows rows, return the original string originalText.

// Note: originalText does not have any trailing spaces ' '. The test cases are generated such that there is only one possible originalText.

 

// Example 1:

// Input: encodedText = "ch   ie   pr", rows = 3
// Output: "cipher"
// Explanation: This is the same example described in the problem description.
// Example 2:


// Input: encodedText = "iveo    eed   l te   olc", rows = 4
// Output: "i love leetcode"
// Explanation: The figure above denotes the matrix that was used to encode originalText. 
// The blue arrows show how we can find originalText from encodedText.
// Example 3:


// Input: encodedText = "coding", rows = 1
// Output: "coding"
// Explanation: Since there is only 1 row, both originalText and encodedText are the same.
 

// Constraints:

// 0 <= encodedText.length <= 106
// encodedText consists of lowercase English letters and ' ' only.
// encodedText is a valid encoding of some originalText that does not have trailing spaces.
// 1 <= rows <= 1000
// The testcases are generated such that there is only one possible originalText.

// solu = 
class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        
        int n = encodedText.size();
        
        // Edge case: if rows = 1, string is already original
        if(rows == 1) return encodedText;
        
        // Number of columns in matrix
        int cols = n / rows;
        
        // --------------------------------------------------
        // STEP 1: Reconstruct matrix row-wise
        // --------------------------------------------------
        
        vector<vector<char>> mat(rows, vector<char>(cols));
        
        int idx = 0;
        
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                mat[i][j] = encodedText[idx++];
            }
        }
        
        
        // --------------------------------------------------
        // STEP 2: Traverse diagonals
        // --------------------------------------------------
        // Start from each column in first row
        
        string result = "";
        
        for(int startCol = 0; startCol < cols; startCol++) {
            
            int i = 0;
            int j = startCol;
            
            // Move diagonally down-right
            while(i < rows && j < cols) {
                result += mat[i][j];
                i++;
                j++;
            }
        }
        
        
        // --------------------------------------------------
        // STEP 3: Remove trailing spaces
        // --------------------------------------------------
        
        while(!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        
        return result;
    }
};
// Time:
// O(n)
// Filling matrix → O(n)
// Diagonal traversal → O(n)
// Space:
// O(n)
// Matrix storage


// solu2 = 

class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        
        // Total length of encoded string
        int n = encodedText.size();
        
        // If there is only 1 row, encoding didn't change anything
        // So original string is same as encoded string
        if(rows == 1) return encodedText;
        
        
        // Number of columns in the matrix
        // Since encodedText is formed by reading matrix row-wise:
        // total elements = rows * cols
        int cols = n / rows;
        
        
        // This will store our final decoded string
        string result = "";
        
        
        // ------------------------------------------------------
        // KEY IDEA:
        // Instead of building a matrix, we directly access elements
        // using index mapping:
        //
        // matrix[i][j] = encodedText[i * cols + j]
        //
        // Now we simulate diagonal traversal
        // ------------------------------------------------------
        
        
        // We start diagonals from each column of the first row
        for(int startCol = 0; startCol < cols; startCol++) {
            
            int i = 0;              // start from first row
            int j = startCol;       // start from current column
            
            
            // Move diagonally: (i+1, j+1)
            while(i < rows && j < cols) {
                
                // Instead of mat[i][j], compute index directly
                // Row-wise storage → index = i * cols + j
                result += encodedText[i * cols + j];
                
                i++;   // move down
                j++;   // move right
            }
        }
        
        
        // ------------------------------------------------------
        // Remove trailing spaces
        // ------------------------------------------------------
        // Problem guarantees original string has NO trailing spaces
        // So we trim them from result
        
        while(!result.empty() && result.back() == ' ') {
            result.pop_back();
        }
        
        
        return result;
    }
};

// Time: O(n)
// Space: O(1) (excluding output)
