// 1752. Check if Array Is Sorted and Rotated
// Solved
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given an array nums, return true if the array was originally sorted in non-decreasing order, then rotated some number of positions (including zero). Otherwise, return false.

// There may be duplicates in the original array.

// Note: An array A rotated by x positions results in an array B of the same length such that B[i] == A[(i+x) % A.length] for every valid index i.

 

// Example 1:

// Input: nums = [3,4,5,1,2]
// Output: true
// Explanation: [1,2,3,4,5] is the original sorted array.
// You can rotate the array by x = 2 positions to begin on the element of value 3: [3,4,5,1,2].
// Example 2:

// Input: nums = [2,1,3,4]
// Output: false
// Explanation: There is no sorted array once rotated that can make nums.
// Example 3:

// Input: nums = [1,2,3]
// Output: true
// Explanation: [1,2,3] is the original sorted array.
// You can rotate the array by x = 0 positions (i.e. no rotation) to make nums.
 

// Constraints:

// 1 <= nums.length <= 100
// 1 <= nums[i] <= 100
class Solution {
public:
    bool check(vector<int>& nums) {

        int n = nums.size();

        /*
        Count how many times the order decreases.

        A decrease (drop) occurs when:
        current element > next element
        */
        int drops = 0;


        /*
        Traverse entire array.

        We use modulo (%) so that the last
        element is compared with the first
        element (circular comparison).
        */
        for (int i = 0; i < n; i++) {

            int next = (i + 1) % n;


            /*
            Found a drop.

            Example:
            5 > 1
            */
            if (nums[i] > nums[next]) {
                drops++;
            }
        }


        /*
        For a sorted rotated array,
        there can be at most one drop.

        0 drops -> already sorted
        1 drop  -> sorted and rotated
        >1      -> invalid
        */
        return drops <= 1;
    }
};
// Time Complexity
// O(n)
// Single traversal of the array.
// Space Complexity
// O(1)
// Only one counter variable is used.
