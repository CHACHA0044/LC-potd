// 3653. XOR After Range Multiplication Queries I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of length n and a 2D integer array queries of size q, where queries[i] = [li, ri, ki, vi].

// For each query, you must apply the following operations in order:

// Set idx = li.
// While idx <= ri:
// Update: nums[idx] = (nums[idx] * vi) % (109 + 7)
// Set idx += ki.
// Return the bitwise XOR of all elements in nums after processing all queries.

 

// Example 1:

// Input: nums = [1,1,1], queries = [[0,2,1,4]]

// Output: 4

// Explanation:

// A single query [0, 2, 1, 4] multiplies every element from index 0 through index 2 by 4.
// The array changes from [1, 1, 1] to [4, 4, 4].
// The XOR of all elements is 4 ^ 4 ^ 4 = 4.
// Example 2:

// Input: nums = [2,3,1,5,4], queries = [[1,4,2,3],[0,2,1,2]]

// Output: 31

// Explanation:

// The first query [1, 4, 2, 3] multiplies the elements at indices 1 and 3 by 3, transforming the array to [2, 9, 1, 15, 4].
// The second query [0, 2, 1, 2] multiplies the elements at indices 0, 1, and 2 by 2, resulting in [4, 18, 2, 15, 4].
// Finally, the XOR of all elements is 4 ^ 18 ^ 2 ^ 15 ^ 4 = 31.​​​​​​​​​​​​​​
 

// Constraints:

// 1 <= n == nums.length <= 103
// 1 <= nums[i] <= 109
// 1 <= q == queries.length <= 103
// queries[i] = [li, ri, ki, vi]
// 0 <= li <= ri < n
// 1 <= ki <= n
// 1 <= vi <= 105

// solu = 
class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        
        // --------------------------------------------------
        // CONSTANT: Modulo value as per problem statement
        // --------------------------------------------------
        // We must take modulo after every multiplication to:
        // 1. Prevent integer overflow
        // 2. Follow problem constraints
        
        const int MOD = 1e9 + 7;
        
        
        // --------------------------------------------------
        // STEP 1: Process each query one by one
        // --------------------------------------------------
        // Each query has 4 values:
        // [l, r, k, v]
        //
        // Meaning:
        // Start from index l
        // Keep jumping by k (l, l+k, l+2k, ...)
        // Until index <= r
        // Multiply those elements by v
        
        for(auto &q : queries) {
            
            int l = q[0];  // starting index of update
            int r = q[1];  // ending index (inclusive)
            int k = q[2];  // step size (jump distance)
            int v = q[3];  // multiplier value
            
            
            // --------------------------------------------------
            // Traverse indices affected by this query
            // --------------------------------------------------
            // Example:
            // l = 1, r = 7, k = 2
            // indices visited = 1, 3, 5, 7
            
            for(int idx = l; idx <= r; idx += k) {
                
                // --------------------------------------------------
                // Update the value at current index
                // --------------------------------------------------
                // Multiply by v and take modulo
                //
                // IMPORTANT:
                // Use 1LL (long long) to avoid overflow
                // because nums[idx] and v can be large
                
                nums[idx] = (1LL * nums[idx] * v) % MOD;
            }
        }
        
        
        // --------------------------------------------------
        // STEP 2: Compute XOR of all elements
        // --------------------------------------------------
        // XOR properties:
        // a ^ a = 0
        // a ^ 0 = a
        //
        // We simply XOR all elements sequentially
        
        int result = 0;
        
        for(int num : nums) {
            result ^= num;  // accumulate XOR
        }
        
        
        // --------------------------------------------------
        // STEP 3: Return final XOR result
        // --------------------------------------------------
        return result;
    }
};
// Time:
// Worst case:
// Each query touches ~n/k elements
// Worst when k = 1 → O(n)
// total:
// O(q * n) ≈ 10^6 (safe)
// Space:
// O(1)
