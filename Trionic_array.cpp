// 3637. Trionic Array I - 2/2/26
// Solved
// Easy
// You are given an integer array nums of length n.

// An array is trionic if there exist indices 0 < p < q < n − 1 such that:

// nums[0...p] is strictly increasing,
// nums[p...q] is strictly decreasing,
// nums[q...n − 1] is strictly increasing.
// Return true if nums is trionic, otherwise return false.

 

// Example 1:

// Input: nums = [1,3,5,4,2,6]

// Output: true

// Explanation:

// Pick p = 2, q = 4:

// nums[0...2] = [1, 3, 5] is strictly increasing (1 < 3 < 5).
// nums[2...4] = [5, 4, 2] is strictly decreasing (5 > 4 > 2).
// nums[4...5] = [2, 6] is strictly increasing (2 < 6).
// Example 2:

// Input: nums = [2,1,3]

// Output: false

// Explanation:

// There is no way to pick p and q to form the required three segments.

 

// Constraints:

// 3 <= n <= 100
// -1000 <= nums[i] <= 1000

//Sol=
class Solution {
public:
    bool isTrionic(vector<int>& nums) {

        // A trionic array must have at least:
        // increasing part + decreasing part + increasing part
        // So minimum length required is 4
        int n = nums.size();
        if (n < 4) return false;

        // Pointer to traverse the array
        int i = 0;

        // ---------- First phase: strictly increasing ----------
        // We count how many valid increasing steps we have
        // nums[0] < nums[1] < nums[2] < ... < nums[p]
        int inc1 = 0;
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            inc1++;
            i++;
        }

        // ---------- Second phase: strictly decreasing ----------
        // After the first increase, values must strictly decrease
        // nums[p] > nums[p+1] > ... > nums[q]
        int dec = 0;
        while (i + 1 < n && nums[i] > nums[i + 1]) {
            dec++;
            i++;
        }

        // ---------- Third phase: strictly increasing again ----------
        // Final part must increase again
        // nums[q] < nums[q+1] < ... < nums[n-1]
        int inc2 = 0;
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            inc2++;
            i++;
        }

        // The array is trionic only if:
        // 1. All three phases exist (each has at least one valid step)
        // 2. We consumed the entire array (no leftover elements)
        return inc1 > 0 && dec > 0 && inc2 > 0 && i == n - 1;
    }
};

