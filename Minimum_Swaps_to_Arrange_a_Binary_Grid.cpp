// 1536. Minimum Swaps to Arrange a Binary Grid
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given an n x n binary grid, in one step you can choose two adjacent rows of the grid and swap them.

// A grid is said to be valid if all the cells above the main diagonal are zeros.

// Return the minimum number of steps needed to make the grid valid, or -1 if the grid cannot be valid.

// The main diagonal of a grid is the diagonal that starts at cell (1, 1) and ends at cell (n, n).

 

// Example 1:


// Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
// Output: 3
// Example 2:


// Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
// Output: -1
// Explanation: All rows are similar, swaps have no effect on the grid.
// Example 3:


// Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
// Output: 0
 

// Constraints:

// n == grid.length == grid[i].length
// 1 <= n <= 200
//solu =
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        
        /*
        ---------------------------------------------------------
        STEP 1: Convert each row into "trailing zero count"
        ---------------------------------------------------------
        
        For the grid to be valid:
        - All cells above the main diagonal must be 0.
        
        For row i:
        - Positions from column (i+1) to (n-1) must be 0.
        - That means this row must have at least (n - i - 1)
          trailing zeros.
        
        So instead of working with the full grid repeatedly,
        we simplify the problem by counting how many consecutive
        zeros each row has from the right.
        */
        
        vector<int> trailingZeros(n);
        
        for(int i = 0; i < n; i++) {
            int count = 0;
            
            // Count consecutive zeros starting from the last column
            for(int j = n - 1; j >= 0; j--) {
                if(grid[i][j] == 0)
                    count++;
                else
                    break;  // Stop once we see a 1
            }
            
            trailingZeros[i] = count;
        }
        
        /*
        ---------------------------------------------------------
        STEP 2: Greedily arrange rows using adjacent swaps
        ---------------------------------------------------------
        
        For each row position i:
        - We need a row with at least (n - i - 1) trailing zeros.
        - If the current row doesn't satisfy it,
          we search downward for the nearest row that does.
        - Then we "bubble" it up using adjacent swaps.
        
        Why nearest?
        Because each adjacent swap costs 1 step,
        so the closest valid row minimizes swaps.
        */
        
        int swaps = 0;
        
        for(int i = 0; i < n; i++) {
            int required = n - i - 1;
            
            int j = i;
            
            // Find the first row below (or at i) that satisfies requirement
            while(j < n && trailingZeros[j] < required) {
                j++;
            }
            
            // If no such row exists, it's impossible to form a valid grid
            if(j == n)
                return -1;
            
            /*
            Bring row j up to position i by swapping
            with the row above repeatedly (like bubble sort).
            Each swap moves it one step closer.
            */
            while(j > i) {
                swap(trailingZeros[j], trailingZeros[j - 1]);
                swaps++;
                j--;
            }
        }
        
        return swaps;
    }
};
//tc = O(n^2)
//sc = O(n)
// grid[i][j] is either 0 or 1
