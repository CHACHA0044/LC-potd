// 2784. Check if Array is Good
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums. We consider an array good if it is a permutation of an array base[n].

// base[n] = [1, 2, ..., n - 1, n, n] (in other words, it is an array of length n + 1 which contains 1 to n - 1 exactly once, plus two occurrences of n). For example, base[1] = [1, 1] and base[3] = [1, 2, 3, 3].

// Return true if the given array is good, otherwise return false.

// Note: A permutation of integers represents an arrangement of these numbers.

 

// Example 1:

// Input: nums = [2, 1, 3]
// Output: false
// Explanation: Since the maximum element of the array is 3, the only candidate n for which this array could be a permutation of base[n], is n = 3. However, base[3] has four elements but array nums has three. Therefore, it can not be a permutation of base[3] = [1, 2, 3, 3]. So the answer is false.
// Example 2:

// Input: nums = [1, 3, 3, 2]
// Output: true
// Explanation: Since the maximum element of the array is 3, the only candidate n for which this array could be a permutation of base[n], is n = 3. It can be seen that nums is a permutation of base[3] = [1, 2, 3, 3] (by swapping the second and fourth elements in nums, we reach base[3]). Therefore, the answer is true.
// Example 3:

// Input: nums = [1, 1]
// Output: true
// Explanation: Since the maximum element of the array is 1, the only candidate n for which this array could be a permutation of base[n], is n = 1. It can be seen that nums is a permutation of base[1] = [1, 1]. Therefore, the answer is true.
// Example 4:

// Input: nums = [3, 4, 4, 1, 2, 1]
// Output: false
// Explanation: Since the maximum element of the array is 4, the only candidate n for which this array could be a permutation of base[n], is n = 4. However, base[4] has five elements but array nums has six. Therefore, it can not be a permutation of base[4] = [1, 2, 3, 4, 4]. So the answer is false.
 

// Constraints:

// 1 <= nums.length <= 100
// 1 <= num[i] <= 200
// sol 
class Solution {
public:
    bool isGood(vector<int>& nums) {

        /*
        Sort array to compare easily
        */
        sort(nums.begin(), nums.end());

        int n = nums.size();


        /*
        For a valid base array:

        base[x] = [1,2,3,...,x,x]

        Length becomes:
            x + 1

        Since nums length = n,
        required maximum number should be:
            n - 1
        */


        /*
        Check first n-1 elements

        They must be:
            1,2,3,...,n-1
        */
        for (int i = 0; i < n - 1; i++) {

            if (nums[i] != i + 1)
                return false;
        }


        /*
        Last element must also equal n-1

        because maximum value appears twice
        */
        return nums[n - 1] == n - 1;
    }
};
// Time Complexity
// Sorting dominates:
// O(n log n)
// Space Complexity
// O(1)
