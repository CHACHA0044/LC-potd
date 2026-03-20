// 3567. Minimum Absolute Difference in Sliding Submatrix
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n integer matrix grid and an integer k.

// For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.

// Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.

// Note: If all elements in the submatrix have the same value, the answer will be 0.

// A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.
 

// Example 1:

// Input: grid = [[1,8],[3,-2]], k = 2

// Output: [[2]]

// Explanation:

// There is only one possible k x k submatrix: [[1, 8], [3, -2]].
// Distinct values in the submatrix are [1, 8, 3, -2].
// The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
// Example 2:

// Input: grid = [[3,-1]], k = 1

// Output: [[0,0]]

// Explanation:

// Both k x k submatrix has only one distinct element.
// Thus, the answer is [[0, 0]].
// Example 3:

// Input: grid = [[1,-2,3],[2,3,5]], k = 2

// Output: [[1,2]]

// Explanation:

// There are two possible k × k submatrix:
// Starting at (0, 0): [[1, -2], [2, 3]].
// Distinct values in the submatrix are [1, -2, 2, 3].
// The minimum absolute difference in the submatrix is |1 - 2| = 1.
// Starting at (0, 1): [[-2, 3], [3, 5]].
// Distinct values in the submatrix are [-2, 3, 5].
// The minimum absolute difference in the submatrix is |3 - 5| = 2.
// Thus, the answer is [[1, 2]].
 

// Constraints:

// 1 <= m == grid.length <= 30
// 1 <= n == grid[i].length <= 30
// -105 <= grid[i][j] <= 105
// 1 <= k <= min(m, n)

// solu = 
class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int n = grid.size(), m = grid[0].size();

        // Result matrix of size (n-k+1) x (m-k+1)
        vector<vector<int>> ans(n - k + 1, vector<int>(m - k + 1));

        // Loop over each possible starting row of k x k submatrix
        for (int i = 0; i <= n - k; i++) {

            // Map to store frequency of elements in current window
            // Keeps elements sorted automatically
            map<int, int> mp;

            // Build initial window for column = 0
            // (i.e., first k x k submatrix in this row strip)
            for (int r = i; r < i + k; r++) {
                for (int c = 0; c < k; c++) {
                    mp[grid[r][c]]++;
                }
            }

            // Slide window across columns
            for (int c = 0; c <= m - k; c++) {

                // If more than one distinct element exists
                if (mp.size() > 1) {
                    int mini = 1e9;

                    // Since map is sorted, min difference will be between adjacent keys
                    auto it = mp.begin();
                    int prev = it->first;

                    // Traverse sorted keys to find minimum absolute difference
                    for (++it; it != mp.end(); it++) {
                        mini = min(mini, abs(it->first - prev));
                        prev = it->first;
                    }

                    ans[i][c] = mini;
                } 
                else {
                    // If all elements are same → min diff = 0
                    ans[i][c] = 0;
                }

                // Move window to the right (sliding window)
                if (c < m - k) {
                    for (int r = i; r < i + k; r++) {

                        // Remove leftmost column element
                        mp[grid[r][c]]--;
                        if (mp[grid[r][c]] == 0)
                            mp.erase(grid[r][c]);

                        // Add new rightmost column element
                        mp[grid[r][c + k]]++;
                    }
                }
            }
        }
        return ans;
    }
};
// Time complexity: O(m⋅n⋅k⋅log(k^2))
// We iterate through m−k+1 rows.
// For each row, we slide a window across n−k+1 columns.
// In each step, we perform k insertions and k deletions in the map (klog(size)).
// We also traverse the map to find the minimum difference, which takes O(k^2) in the worst case (if all elements are unique), though for 30×30, this is very fast.
// Space complexity:O(k^2)
// The map stores at most k×k elements at any given time to represent the current submatrix.
