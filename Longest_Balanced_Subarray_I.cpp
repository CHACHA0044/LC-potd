// 3719. Longest Balanced Subarray I
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums.

// A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

// Return the length of the longest balanced subarray.

 

// Example 1:

// Input: nums = [2,5,4,3]

// Output: 4

// Explanation:

// The longest balanced subarray is [2, 5, 4, 3].
// It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.
// Example 2:

// Input: nums = [3,2,2,5,4]

// Output: 5

// Explanation:

// The longest balanced subarray is [3, 2, 2, 5, 4].
// It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.
// Example 3:

// Input: nums = [1,2,3,2]

// Output: 3

// Explanation:

// The longest balanced subarray is [2, 3, 2].
// It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.
 

// Constraints:

// 1 <= nums.length <= 1500

//solu=
class Solution {
public:
    int longestBalancedSubarray(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        // We fix the starting index of the subarray at position i
        // From this index, we will expand the subarray towards the right
        for (int i = 0; i < n; i++) {

            // These sets store distinct even and odd numbers present
            // in the current subarray starting at index i
            unordered_set<int> evenSet;
            unordered_set<int> oddSet;

            // j represents the ending index of the subarray
            // We keep expanding the subarray one element at a time
            for (int j = i; j < n; j++) {

                // If the current number is even, insert it into the even set
                // Using a set automatically ensures only distinct values are counted
                if (nums[j] % 2 == 0) {
                    evenSet.insert(nums[j]);
                }
                // Otherwise, the number is odd, so we insert it into the odd set
                else {
                    oddSet.insert(nums[j]);
                }

                // A subarray is balanced if the number of distinct evens
                // is equal to the number of distinct odds
                if (evenSet.size() == oddSet.size()) {

                    // If the current subarray is balanced,
                    // update the answer with the maximum length found so far
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }
};

//tc= O(n^2)
//sc= O(n)

// 1 <= nums[i] <= 105
