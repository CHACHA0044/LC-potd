// 3546. Equal Sum Grid Partition I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:

// Each of the two resulting sections formed by the cut is non-empty.
// The sum of the elements in both sections is equal.
// Return true if such a partition exists; otherwise return false.

 

// Example 1:

// Input: grid = [[1,4],[2,3]]

// Output: true

// Explanation:



// A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.

// Example 2:

// Input: grid = [[1,3],[2,4]]

// Output: false

// Explanation:

// No horizontal or vertical cut results in two non-empty sections with equal sums. Thus, the answer is false.

 

// Constraints:

// 1 <= m == grid.length <= 105
// 1 <= n == grid[i].length <= 105
// 2 <= m * n <= 105
// 1 <= grid[i][j] <= 105

// solu = 
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        /*
        Step 1: Compute total sum of all elements in the grid.

        Why?
        We want to split the grid into two parts with equal sum.
        So total must be divisible by 2.
        */
        long long total = 0;

        for (auto& row : grid) {
            for (int val : row) {
                total += val;
            }
        }

        /*
        If total sum is odd, it's impossible to split into two equal parts.
        */
        if (total % 2 != 0) return false;

        /*
        Target sum each partition should have.
        */
        long long target = total / 2;

        /*
        Step 2: Try horizontal cuts (cut between rows)

        Idea:
        Keep adding row sums from top to bottom.
        At any point, if accumulated sum == target,
        we can split the grid horizontally here.
        */
        long long sum = 0;

        for (int i = 0; i < n; i++) {

            /*
            Calculate sum of current row
            */
            long long rowSum = 0;
            for (int j = 0; j < m; j++) {
                rowSum += grid[i][j];
            }

            /*
            Add this row to running sum (top portion)
            */
            sum += rowSum;

            /*
            If top portion equals target,
            bottom portion will also be equal automatically.
            */
            if (sum == target) return true;
        }

        /*
        Step 3: Try vertical cuts (cut between columns)

        Same idea, but now we accumulate column-wise.
        */
        sum = 0;

        for (int j = 0; j < m; j++) {

            /*
            Calculate sum of current column
            */
            long long colSum = 0;
            for (int i = 0; i < n; i++) {
                colSum += grid[i][j];
            }

            /*
            Add this column to running sum (left portion)
            */
            sum += colSum;

            /*
            If left portion equals target,
            right portion will also be equal.
            */
            if (sum == target) return true;
        }

        /*
        If neither horizontal nor vertical cuts worked,
        then partition is not possible.
        */
        return false;
    }
};
// Time: O(n × m)
// Space: O(1)
