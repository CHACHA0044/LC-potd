// 3740. Minimum Distance Between Three Equal Elements I
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums.

// A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

// The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

// Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.

 

// Example 1:

// Input: nums = [1,2,1,1,3]

// Output: 6

// Explanation:

// The minimum distance is achieved by the good tuple (0, 2, 3).

// (0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. Its distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

// Example 2:

// Input: nums = [1,1,2,3,2,1,2]

// Output: 8

// Explanation:

// The minimum distance is achieved by the good tuple (2, 4, 6).

// (2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. Its distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

// Example 3:

// Input: nums = [1]

// Output: -1

// Explanation:

// There are no good tuples. Therefore, the answer is -1.

 

// Constraints:

// 1 <= n == nums.length <= 100
// 1 <= nums[i]

// solu = 
class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        
        int n = nums.size();
        
        // --------------------------------------------------
        // last2[val] stores last two positions of each value
        // --------------------------------------------------
        // Each entry is packed into a single integer:
        //
        // lower 8 bits  → previous occurrence (old)
        // upper bits    → latest occurrence (cur)
        //
        // Why 8 bits?
        // Because positions are stored as (i+1) and n ≤ 100,
        // so 8 bits (0–255) is enough.
        
        int last2[100] = {};  // supports values from 1 to 100
        
        
        // --------------------------------------------------
        // Initialize result with a large value
        // --------------------------------------------------
        int res = 200;  // larger than any possible answer
        
        
        // --------------------------------------------------
        // Traverse array
        // --------------------------------------------------
        for (int i = 0; i < n; i++) {
            
            // Convert value to 0-based index
            int val = nums[i] - 1;
            
            // Store position as (i+1) instead of i
            // so that 0 can represent "not present"
            int pos = i + 1;
            
            
            // --------------------------------------------------
            // Extract last two occurrences
            // --------------------------------------------------
            
            int pack = last2[val];
            
            // lower 8 bits → older occurrence
            int old = pack & 255;
            
            // upper bits → most recent occurrence
            int cur = pack >> 8;
            
            
            // --------------------------------------------------
            // Update storage:
            // shift current to old, and store new position
            // --------------------------------------------------
            last2[val] = cur | (pos << 8);
            
            
            // --------------------------------------------------
            // If we have seen this value before
            // compute distance
            // --------------------------------------------------
            if (old) {
                
                // distance = 2 * (pos - old)
                // (problem-specific transformation)
                res = min(res, (pos - old) << 1);
            }
        }
        
        
        // --------------------------------------------------
        // If no valid pair found → return -1
        // else return minimum distance
        // --------------------------------------------------
        
        return -(res == 200) | res;
        
        // Explanation of this trick:
        // if res == 200 → returns -1
        // else → returns res
    }
};

// Time Complexity
// O(n)
// Single pass through array
// Constant work per element
// Space Complexity
// O(1)
// Fixed array of size 100
// No extra dynamic space
