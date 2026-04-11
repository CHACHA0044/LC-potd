// 3741. Minimum Distance Between Three Equal Elements II
// Medium
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

// 1 <= n == nums.length <= 105
// 1 <= nums[i] <= n

// solu =
class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        
        int n = nums.size();
        
        
        // Store indices of each value
        unordered_map<int, vector<int>> pos;
        
        for(int i = 0; i < n; i++) {
            pos[nums[i]].push_back(i);
        }
        
        
        int ans = INT_MAX;
        
        
        // Process each value independently
        for(auto &entry : pos) {
            
            vector<int>& indices = entry.second;
            
            
            // Need at least 3 occurrences
            if(indices.size() < 3) continue;
            
            
            // Check every consecutive triple
            for(int i = 2; i < indices.size(); i++) {
                
                int left = indices[i - 2];
                int right = indices[i];
                
                // Distance = 2 * (right - left)
                ans = min(ans, 2 * (right - left));
            }
        }
        
        
        return ans == INT_MAX ? -1 : ans;
    }
};
// Time:
// O(n)
// Each index stored once
// Each occurrence processed once
// Space:
// O(n)
// Storing positions of all elements
