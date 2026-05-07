// 3660. Jump Game IX
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums.

// From any index i, you can jump to another index j under the following rules:

// Jump to index j where j > i is allowed only if nums[j] < nums[i].
// Jump to index j where j < i is allowed only if nums[j] > nums[i].
// For each index i, find the maximum value in nums that can be reached by following any sequence of valid jumps starting at i.

// Return an array ans where ans[i] is the maximum value reachable starting from index i.

 

// Example 1:

// Input: nums = [2,1,3]

// Output: [2,2,3]

// Explanation:

// For i = 0: No jump increases the value.
// For i = 1: Jump to j = 0 as nums[j] = 2 is greater than nums[i].
// For i = 2: Since nums[2] = 3 is the maximum value in nums, no jump increases the value.
// Thus, ans = [2, 2, 3].

// Example 2:

// Input: nums = [2,3,1]

// Output: [3,3,3]

// Explanation:

// For i = 0: Jump forward to j = 2 as nums[j] = 1 is less than nums[i] = 2, then from i = 2 jump to j = 1 as nums[j] = 3 is greater than nums[2].
// For i = 1: Since nums[1] = 3 is the maximum value in nums, no jump increases the value.
// For i = 2: Jump to j = 1 as nums[j] = 3 is greater than nums[2] = 1.
// Thus, ans = [3, 3, 3].

 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 109
// solu =
class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {

        int n = nums.size();

        
        /*
        pre[i]  = maximum value from nums[0 ... i]
        suf[i]  = minimum value from nums[i ... n-1]
        res[i]  = answer for index i
        */
        vector<int> pre(n), suf(n), res(n);


        /*
        =========================================================
        STEP 1: Build Prefix Maximum Array
        =========================================================

        pre[i] stores the largest value seen so far
        from the left side.

        Example:
        nums = [2,1,3]

        pre:
        [2,2,3]
        */
        pre[0] = nums[0];

        for (int i = 1; i < n; i++) {
            pre[i] = max(pre[i - 1], nums[i]);
        }


        /*
        =========================================================
        STEP 2: Build Suffix Minimum Array
        =========================================================

        suf[i] stores the smallest value seen so far
        from the right side.

        Example:
        nums = [2,1,3]

        suf:
        [1,1,3]
        */
        suf[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suf[i] = min(suf[i + 1], nums[i]);
        }


        /*
        =========================================================
        CORE OBSERVATION
        =========================================================

        A split between i and i+1 is possible if:

            pre[i] < suf[i+1]

        Meaning:
        - every value on left side is smaller
          than every value on right side

        So:
        - no inversion exists across the split
        - no jumps can connect both parts

        Otherwise:
        - components merge together
        */


        /*
        Last index always belongs to a component
        whose maximum value is pre[n-1]
        */
        res[n - 1] = pre[n - 1];


        /*
        =========================================================
        STEP 3: Build Answer from Right → Left
        =========================================================
        */
        for (int i = n - 2; i >= 0; i--) {


            /*
            CASE 1: Components merge

            If:
                pre[i] > suf[i + 1]

            Then an inversion exists:
                left value > right value

            So jumps can connect both segments.

            Therefore:
            current index belongs to same connected
            component as index i+1.
            */
            if (pre[i] > suf[i + 1]) {

                // same component → same maximum reachable value
                res[i] = res[i + 1];
            }


            /*
            CASE 2: New component starts

            If:
                pre[i] < suf[i+1]

            Then no inversion crosses the split.

            So current segment becomes isolated.

            Maximum reachable value inside this component
            is simply pre[i].
            */
            else {
                res[i] = pre[i];
            }
        }


        return res;
    }
};
// Time Complexity
// O(n)
// Why?
// One pass for prefix max
// One pass for suffix min
// One pass for answer
// Space Complexity
// O(n)
// Used for:
// prefix array
// suffix array
// result array
