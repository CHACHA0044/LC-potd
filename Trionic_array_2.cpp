// 3640. Trionic Array II
// Solved
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of length n.

// A trionic subarray is a contiguous subarray nums[l...r] (with 0 <= l < r < n) for which there exist indices l < p < q < r such that:

// nums[l...p] is strictly increasing,
// nums[p...q] is strictly decreasing,
// nums[q...r] is strictly increasing.
// Return the maximum sum of any trionic subarray in nums.

 

// Example 1:

// Input: nums = [0,-2,-1,-3,0,2,-1]

// Output: -4

// Explanation:

// Pick l = 1, p = 2, q = 3, r = 5:

// nums[l...p] = nums[1...2] = [-2, -1] is strictly increasing (-2 < -1).
// nums[p...q] = nums[2...3] = [-1, -3] is strictly decreasing (-1 > -3)
// nums[q...r] = nums[3...5] = [-3, 0, 2] is strictly increasing (-3 < 0 < 2).
// Sum = (-2) + (-1) + (-3) + 0 + 2 = -4.
// Example 2:

// Input: nums = [1,4,2,7]

// Output: 14

// Explanation:

// Pick l = 0, p = 1, q = 2, r = 3:

// nums[l...p] = nums[0...1] = [1, 4] is strictly increasing (1 < 4).
// nums[p...q] = nums[1...2] = [4, 2] is strictly decreasing (4 > 2).
// nums[q...r] = nums[2...3] = [2, 7] is strictly increasing (2 < 7).
// Sum = 1 + 4 + 2 + 7 = 14.
 

// Constraints:

// 4 <= n = nums.length <= 105
// -109 <= nums[i] <= 109
// It is guaranteed that at least one trionic subarray exists.

//solu=
class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        const int n = nums.size();

        // We will track the maximum sum of any valid trionic subarray
        // Initialize with a very small value since sums can be negative
        long long ans = -1e15;

        // i is the main pointer that scans the array
        // l, p, q, r represent the boundaries of the trionic subarray:
        // l -> start of first increasing part
        // p -> peak after first increasing
        // q -> valley after decreasing
        // r -> end of second increasing
        for (int i = 0, l = 0, p = 0, q = 0, r = 0; i < n - 1; i += (i == l)) {

            // Step 1: Find start of first increasing segment
            // Skip all non-increasing pairs
            while (i < n - 1 && nums[i] >= nums[i + 1]) i++;
            l = i;

            long long Sum = 0;

            // Step 2: First uphill (strictly increasing)
            // We only add positive values here to avoid hurting the sum
            while (i < n - 1 && nums[i] < nums[i + 1]) {
                if (nums[i] > 0) Sum += nums[i];
                i++;
            }
            p = i;

            // If no valid increasing segment OR equality breaks strictness, skip
            if (p == l || (p + 1 < n && nums[p] == nums[p + 1]))
                continue;

            // We must include the last element of the uphill
            // Add it only if it is negative (positive already counted)
            if (nums[p - 1] < 0) Sum += nums[p - 1];

            // Step 3: Downhill (strictly decreasing)
            // All values must be included
            while (i < n - 1 && nums[i] > nums[i + 1]) {
                Sum += nums[i];
                i++;
            }
            q = i;

            // If no valid downhill OR equality breaks strictness, skip
            if (p == q || (q + 1 < n && nums[q] == nums[q + 1]))
                continue;

            // Step 4: Second uphill (strictly increasing)
            // The valley (nums[q]) must be included
            // We want the maximum suffix sum of this segment
            Sum += nums[q];  // valley is mandatory

            long long incr = 0;           // current increasing sum
            long long maxIncr = INT_MIN;  // best increasing sum so far

            while (i < n - 1 && nums[i] < nums[i + 1]) {
                incr += nums[i + 1];
                maxIncr = max(maxIncr, incr);
                i++;
            }
            r = i;

            // If a valid second uphill exists, update answer
            if (r > q) {
                ans = max(ans, Sum + maxIncr);
                // Backtrack so overlapping trionic subarrays are explored
                i = q;
            }
        }

        return ans;
    }
};
