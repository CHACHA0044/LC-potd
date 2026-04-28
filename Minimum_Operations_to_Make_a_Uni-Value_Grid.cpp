// 2033. Minimum Operations to Make a Uni-Value Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.

// A uni-value grid is a grid where all the elements of it are equal.

// Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.

 

// Example 1:


// Input: grid = [[2,4],[6,8]], x = 2
// Output: 4
// Explanation: We can make every element equal to 4 by doing the following: 
// - Add x to 2 once.
// - Subtract x from 6 once.
// - Subtract x from 8 twice.
// A total of 4 operations were used.
// Example 2:


// Input: grid = [[1,5],[2,3]], x = 1
// Output: 5
// Explanation: We can make every element equal to 3.
// Example 3:


// Input: grid = [[1,2],[3,4]], x = 2
// Output: -1
// Explanation: It is impossible to make every element equal.
 

// Constraints:

// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 105
// 1 <= m * n <= 105
// 1 <= x, grid[i][j] <= 104

// solu = 
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        
        vector<int> nums;

        
        // STEP 1: Flatten the 2D grid into a 1D array
        // This makes it easier to work with values
        for (auto &row : grid) {
            for (int val : row) {
                nums.push_back(val);
            }
        }

        
        int n = nums.size();


        /*
        STEP 2: Check feasibility
        
        All numbers must have the SAME remainder when divided by x.
        Why?
        Because we can only add/subtract multiples of x.
        
        Example:
        x = 2
        2 % 2 = 0
        4 % 2 = 0
        6 % 2 = 0  → OK
        
        But:
        1 % 2 = 1
        2 % 2 = 0  → NOT possible to make equal
        */
        int remainder = nums[0] % x;

        for (int val : nums) {
            if (val % x != remainder) {
                return -1;   // impossible case
            }
        }


        /*
        STEP 3: Sort values
        
        To minimize total operations, we want to convert all values
        to the MEDIAN value.
        
        WHY MEDIAN?
        → It minimizes sum of absolute differences.
        */
        sort(nums.begin(), nums.end());


        // Median element
        int median = nums[n / 2];


        /*
        STEP 4: Compute operations
        
        For each value:
        operations needed = |val - median| / x
        
        Because each operation changes value by x
        */
        int operations = 0;

        for (int val : nums) {
            operations += abs(val - median) / x;
        }


        return operations;
    }
};
// Time Complexity
// O(n log n)
// Sorting dominates
// Space Complexity
// O(n)
// Flattened array
