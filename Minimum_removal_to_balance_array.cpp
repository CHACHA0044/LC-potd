//array , sliding window
// You are given an integer array nums and an integer k.

// An array is considered balanced if the value of its maximum element is at most k times the minimum element.

// You may remove any number of elements from nums​​​​​​​ without making it empty.

// Return the minimum number of elements to remove so that the remaining array is balanced.

// Note: An array of size 1 is considered balanced as its maximum and minimum are equal, and the condition always holds true.

 

// Example 1:

// Input: nums = [2,1,5], k = 2

// Output: 1

// Explanation:

// Remove nums[2] = 5 to get nums = [2, 1].
// Now max = 2, min = 1 and max <= min * k as 2 <= 1 * 2. Thus, the answer is 1.
// Example 2:

// Input: nums = [1,6,2,9], k = 3

// Output: 2

// Explanation:

// Remove nums[0] = 1 and nums[3] = 9 to get nums = [6, 2].
// Now max = 6, min = 2 and max <= min * k as 6 <= 2 * 3. Thus, the answer is 2.
// Example 3:

// Input: nums = [4,6], k = 2

// Output: 0

// Explanation:

// Since nums is already balanced as 6 <= 4 * 2, no elements need to be removed.
 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 109
// 1 <= k <= 105

class Solution {
public:
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        // 'left' represents the starting index of our current window
        // This index always points to the minimum element in the window
        int left = 0;

        // We want to keep as many elements as possible,
        // so we track the maximum size of a valid balanced window
        int maxLen = 1;

        // Iterate through the array using 'i' as the right boundary
        // of the sliding window
        for (int i = 0; i < n; i++) {

            // If the current maximum element nums[i] violates
            // the balance condition with the current minimum nums[left],
            // we move the left pointer forward to increase the minimum
            // and try to restore the condition
            while ((long long) nums[i] > (long long) nums[left] * k) {
                left++;
            }

            // At this point, the window from 'left' to 'i' is balanced,
            // so we update the maximum length of any valid window found so far
            maxLen = max(maxLen, i - left + 1);
        }

        // The minimum number of removals is equal to
        // total elements minus the size of the largest balanced subset
        return n - maxLen;
    }
};

// TC = O(n log n)
// SC = O(1)
