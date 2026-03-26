// 3548. Equal Sum Grid Partition II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:

// Each of the two resulting sections formed by the cut is non-empty.
// The sum of elements in both sections is equal, or can be made equal by discounting at most one single cell in total (from either section).
// If a cell is discounted, the rest of the section must remain connected.
// Return true if such a partition exists; otherwise, return false.

// Note: A section is connected if every cell in it can be reached from any other cell by moving up, down, left, or right through other cells in the section.

 

// Example 1:

// Input: grid = [[1,4],[2,3]]

// Output: true

// Explanation:



// A horizontal cut after the first row gives sums 1 + 4 = 5 and 2 + 3 = 5, which are equal. Thus, the answer is true.
// Example 2:

// Input: grid = [[1,2],[3,4]]

// Output: true

// Explanation:



// A vertical cut after the first column gives sums 1 + 3 = 4 and 2 + 4 = 6.
// By discounting 2 from the right section (6 - 2 = 4), both sections have equal sums and remain connected. Thus, the answer is true.
// Example 3:

// Input: grid = [[1,2,4],[2,3,5]]

// Output: false

// Explanation:



// A horizontal cut after the first row gives 1 + 2 + 4 = 7 and 2 + 3 + 5 = 10.
// By discounting 3 from the bottom section (10 - 3 = 7), both sections have equal sums, but they do not remain connected as it splits the bottom section into two parts ([2] and [5]). Thus, the answer is false.
// Example 4:

// Input: grid = [[4,1,8],[3,2,6]]

// Output: false

// Explanation:

// No valid cut exists, so the answer is false.

 

// Constraints:

// 1 <= m == grid.length <= 105
// 1 <= n == grid[i].length <= 105
// 2 <= m * n <= 105
// 1 <= grid[i][j] <= 105

// solu =
class Solution {
public:
    typedef long long ll;

    /*
    This function tries to solve the problem assuming we are making
    HORIZONTAL cuts on the given grid.

    Note:
    - We will call this twice:
        1. On original grid → handles horizontal cuts
        2. On transposed grid → handles vertical cuts
    */
    bool solve(vector<vector<int>>& grid) {

        int n = grid.size(), m = grid[0].size();

        /*
        bottomSum → sum of lower section (initially whole grid)
        topSum    → sum of upper section (initially empty)
        */
        ll bottomSum = 0, topSum = 0;

        /*
        Frequency arrays to quickly check:
        "Does a value exist in this section?"

        Why needed?
        → To check if we can remove a cell equal to 'diff'
        */
        vector<int> bottomFreq(100001, 0), topFreq(100001, 0);

        /*
        Step 1: Initialize bottomSum and bottomFreq
        (Initially, entire grid is bottom section)
        */
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                bottomSum += grid[i][j];
                bottomFreq[grid[i][j]]++;
            }
        }

        /*
        Step 2: Try every possible horizontal cut

        Cut after row i:
        - Top section → rows [0 to i]
        - Bottom section → rows [i+1 to n-1]
        */
        for (int i = 0; i < n - 1; i++) {

            /*
            Move row i from bottom → top
            Update:
            - sums
            - frequency arrays
            */
            for (int j = 0; j < m; j++) {
                int val = grid[i][j];

                bottomSum -= val;
                bottomFreq[val]--;

                topSum += val;
                topFreq[val]++;
            }

            /*
            Case 1: Already equal → perfect partition
            */
            if (topSum == bottomSum) return true;

            /*
            -------------------------------------------------
            Case 2: Try removing ONE cell from TOP section
            -------------------------------------------------
            */
            ll diffTop = topSum - bottomSum;

            if (diffTop > 0 && diffTop <= 100000) {

                int height = i + 1;
                int width = m;

                /*
                Case A: Top section is 2D (safe removal anywhere)
                */
                if (height > 1 && width > 1) {
                    if (topFreq[diffTop]) return true;
                }

                /*
                Case B: Single column → only top/bottom cell removable
                */
                else if (height > 1 && width == 1) {
                    if (grid[0][0] == diffTop || grid[i][0] == diffTop)
                        return true;
                }

                /*
                Case C: Single row → only left/right cell removable
                */
                else if (height == 1 && width > 1) {
                    if (grid[0][0] == diffTop || grid[0][width - 1] == diffTop)
                        return true;
                }
            }

            /*
            -------------------------------------------------
            Case 3: Try removing ONE cell from BOTTOM section
            -------------------------------------------------
            */
            ll diffBot = bottomSum - topSum;

            if (diffBot > 0 && diffBot <= 100000) {

                int height = n - i - 1;
                int width = m;

                /*
                Case A: Bottom is 2D → safe anywhere
                */
                if (height > 1 && width > 1) {
                    if (bottomFreq[diffBot]) return true;
                }

                /*
                Case B: Single column
                */
                else if (height > 1 && width == 1) {
                    if (grid[i + 1][0] == diffBot || grid[n - 1][0] == diffBot)
                        return true;
                }

                /*
                Case C: Single row
                */
                else if (height == 1 && width > 1) {
                    if (grid[n - 1][0] == diffBot || grid[n - 1][width - 1] == diffBot)
                        return true;
                }
            }
        }

        return false;
    }

    bool canPartitionGrid(vector<vector<int>>& grid) {

        /*
        Step 1: Try horizontal cuts directly
        */
        if (solve(grid)) return true;

        /*
        Step 2: Convert vertical cuts into horizontal
        by transposing the matrix

        Why?
        → So we reuse the same logic
        */
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> transposed(m, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                transposed[j][i] = grid[i][j];
            }
        }

        /*
        Step 3: Try again on transposed grid
        */
        return solve(transposed);
    }
};
// Complexity	Value
// Time	O(n × m)
// Space	O(n × m)
