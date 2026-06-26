// 3739. Count Subarrays With Majority Element II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums and an integer target.

// Return the number of subarrays of nums in which target is the majority element.

// The majority element of a subarray is the element that appears strictly more than half of the times in that subarray.

 

// Example 1:

// Input: nums = [1,2,2,3], target = 2

// Output: 5

// Explanation:

// Valid subarrays with target = 2 as the majority element:

// nums[1..1] = [2]
// nums[2..2] = [2]
// nums[1..2] = [2,2]
// nums[0..2] = [1,2,2]
// nums[1..3] = [2,2,3]
// So there are 5 such subarrays.

// Example 2:

// Input: nums = [1,1,1,1], target = 1

// Output: 10

// Explanation:

// ​​​​​​​All 10 subarrays have 1 as the majority element.

// Example 3:

// Input: nums = [1,2,3], target = 4

// Output: 0

// Explanation:

// target = 4 does not appear in nums at all. Therefore, there cannot be any subarray where 4 is the majority element. Hence the answer is 0.

 

// Constraints:

// 1 <= nums.length <= 10​​​​​​​5
// 1 <= nums[i] <= 10​​​​​​​9
// 1 <= target <= 109
class Fenwick {
public:
    int n;
    vector<int> bit;

    // Initialize Fenwick Tree
    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    // Add 'val' at index 'idx'
    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    // Returns prefix frequency from 1 to idx
    int query(int idx) {
        int res = 0;
        while (idx > 0) {
            res += bit[idx];
            idx -= idx & -idx;
        }
        return res;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {

        int n = nums.size();

        // Prefix sums can range from -n to +n.
        // Shift them to positive indices for Fenwick Tree.
        int offset = n + 2;

        Fenwick ft(2 * n + 5);

        long long ans = 0;
        int pref = 0;

        // Empty prefix sum (0) occurs once.
        ft.update(offset, 1);

        for (int x : nums) {

            // Treat target as +1 and every other element as -1.
            // A subarray has target as majority iff its transformed sum > 0.
            if (x == target)
                pref++;
            else
                pref--;

            // We need previous prefix sums strictly smaller than current prefix.
            ans += ft.query(pref + offset - 1);

            // Store current prefix sum.
            ft.update(pref + offset, 1);
        }

        return ans;
    }
};

/*
Time Complexity: O(n log n)

Space Complexity: O(n)
*/
