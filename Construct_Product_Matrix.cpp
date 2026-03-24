// 2906. Construct Product Matrix
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:

// Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
// Return the product matrix of grid.

 

// Example 1:

// Input: grid = [[1,2],[3,4]]
// Output: [[24,12],[8,6]]
// Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
// p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
// p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
// p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
// So the answer is [[24,12],[8,6]].
// Example 2:

// Input: grid = [[12345],[2],[1]]
// Output: [[2],[0],[0]]
// Explanation: p[0][0] = grid[0][1] * grid[0][2] = 2 * 1 = 2.
// p[0][1] = grid[0][0] * grid[0][2] = 12345 * 1 = 12345. 12345 % 12345 = 0. So p[0][1] = 0.
// p[0][2] = grid[0][0] * grid[0][1] = 12345 * 2 = 24690. 24690 % 12345 = 0. So p[0][2] = 0.
// So the answer is [[2],[0],[0]].
 

// Constraints:

// 1 <= n == grid.length <= 105
// 1 <= m == grid[i].length <= 105
// 2 <= n * m <= 105
// 1 <= grid[i][j] <= 109

// solu =
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>>& grid) {
        
        int n = grid.size();
        int m = grid[0].size();
        int MOD = 12345;

        /*
        Step 1: Flatten the 2D grid into a 1D array

        Why?
        This problem is essentially "product of array except self".
        It's much easier to apply prefix/suffix logic on a 1D array
        rather than dealing with 2D indices.

        We'll later map results back to 2D.
        */
        int size = n * m;
        vector<long long> arr(size);

        int idx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                /*
                We take modulo early to avoid overflow.
                Since final answer is also modulo 12345,
                reducing intermediate values is safe.
                */
                arr[idx++] = grid[i][j] % MOD;
            }
        }

        /*
        Step 2: Build prefix product array

        prefix[i] = product of all elements BEFORE index i

        Example:
        arr = [a, b, c, d]
        prefix = [1, a, a*b, a*b*c]

        Why start with 1?
        Because "product of nothing" = 1 (neutral element)
        */
        vector<long long> prefix(size, 1);
        for (int i = 1; i < size; i++) {
            prefix[i] = (prefix[i - 1] * arr[i - 1]) % MOD;
        }

        /*
        Step 3: Build suffix product array

        suffix[i] = product of all elements AFTER index i

        Example:
        arr = [a, b, c, d]
        suffix = [b*c*d, c*d, d, 1]
        */
        vector<long long> suffix(size, 1);
        for (int i = size - 2; i >= 0; i--) {
            suffix[i] = (suffix[i + 1] * arr[i + 1]) % MOD;
        }

        /*
        Step 4: Construct result

        For each position i:
        product of all elements except itself =
            prefix[i] * suffix[i]

        Because:
        - prefix[i] contains everything before i
        - suffix[i] contains everything after i
        */
        vector<vector<int>> result(n, vector<int>(m));

        idx = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                result[i][j] = (prefix[idx] * suffix[idx]) % MOD;
                idx++;
            }
        }

        /*
        Final matrix is ready
        */
        return result;
    }
};
// Time: O(n × m)
// Space: O(n × m)
