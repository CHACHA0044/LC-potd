// 1727. Largest Submatrix With Rearrangements
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.

// Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.

 

// Example 1:


// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
// Example 2:


// Input: matrix = [[1,0,1,0,1]]
// Output: 3
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 3.
// Example 3:

// Input: matrix = [[1,1,0],[1,0,1]]
// Output: 2
// Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.
 

// Constraints:

// m == matrix.length
// n == matrix[i].length
// 1 <= m * n <= 105
// matrix[i][j] is either 0 or 1.

// solu = 
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // ------------------------------------------------------------
        // STEP 1: Convert matrix into "heights"
        // ------------------------------------------------------------
        // Idea:
        // Instead of thinking row-wise, think column-wise.
        // For each cell, store how many consecutive 1s are stacked
        // vertically ending at that cell.
        //
        // This turns each row into something like a histogram.
        //
        // Example:
        // Original:
        // 0 0 1
        // 1 1 1
        // 1 0 1
        //
        // After conversion:
        // 0 0 1
        // 1 1 2
        // 2 0 3
        //
        // Now each row tells us how tall a column of 1s is at that point.

        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    // Add height from the row above
                    matrix[i][j] += matrix[i - 1][j];
                }
            }
        }

        int maxArea = 0;

        // ------------------------------------------------------------
        // STEP 2: Process each row independently
        // ------------------------------------------------------------
        // Important idea:
        // We are allowed to rearrange columns.
        //
        // That means:
        // Instead of worrying about column positions,
        // we can just reorder heights in descending order.
        //
        // Why descending?
        // Because we want tallest columns grouped together
        // to maximize rectangle area.

        for (int i = 0; i < m; i++) {

            // Copy current row (heights)
            vector<int> row = matrix[i];

            // Sort heights in descending order
            // So tallest columns come first
            sort(row.begin(), row.end(), greater<int>());

            // ------------------------------------------------------------
            // STEP 3: Try forming rectangles using sorted heights
            // ------------------------------------------------------------
            // Now imagine:
            // If we take first k columns (after sorting),
            // the minimum height among them will be row[k-1]
            //
            // So:
            // width = k
            // height = row[k-1]
            //
            // area = width * height

            for (int j = 0; j < n; j++) {
                int height = row[j];     // height of shortest column in this group
                int width = j + 1;       // number of columns used

                // Calculate area of rectangle
                int area = height * width;

                // Update maximum area
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;
    }
};
// tc = O(m * n log n)
// Build heights → O(m * n)
// Sort each row → O(m * n log n)
// sc = O(n)

// solu2 =
class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // ------------------------------------------------------------
        // STEP 1: Convert matrix into heights (same as before)
        // ------------------------------------------------------------
        for (int i = 1; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1) {
                    matrix[i][j] += matrix[i - 1][j];
                }
            }
        }

        int maxArea = 0;

        // ------------------------------------------------------------
        // STEP 2: Process each row using frequency (no sorting)
        // ------------------------------------------------------------
        for (int i = 0; i < m; i++) {

            // freq[h] = how many columns have height = h
            vector<int> freq(m + 1, 0);

            for (int j = 0; j < n; j++) {
                int h = matrix[i][j];
                if (h > 0) {
                    freq[h]++;
                }
            }

            // ------------------------------------------------------------
            // STEP 3: Traverse from largest height → smallest
            // ------------------------------------------------------------
            // Idea:
            // Instead of sorting, we simulate it by counting
            // how many columns have height >= current height

            int width = 0;

            for (int h = m; h >= 1; h--) {
                width += freq[h];   // add all columns with this height

                // Now we have "width" columns with height at least h
                // So we can form rectangle:
                // height = h
                // width = width

                maxArea = max(maxArea, h * width);
            }
        }

        return maxArea;
    }
};

// Build heights → O(mn)
// Frequency + traversal → O(mn)
// tc = O(m × n)
// sc = O(m)
