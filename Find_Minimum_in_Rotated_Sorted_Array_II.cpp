// 154. Find Minimum in Rotated Sorted Array II
// Hard
// Topics
// premium lock icon
// Companies
// Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

// [4,5,6,7,0,1,4] if it was rotated 4 times.
// [0,1,4,4,5,6,7] if it was rotated 7 times.
// Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

// Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

// You must decrease the overall operation steps as much as possible.

 

// Example 1:

// Input: nums = [1,3,5]
// Output: 1
// Example 2:

// Input: nums = [2,2,2,0,1]
// Output: 0
 

// Constraints:

// n == nums.length
// 1 <= n <= 5000
// -5000 <= nums[i] <= 5000
// nums is sorted and rotated between 1 and n times.
class Solution {
public:
    int findMin(vector<int>& nums) {

        int left = 0;
        int right = nums.size() - 1;


        /*
        =====================================================
        Binary Search
        =====================================================

        In a rotated sorted array:

        - One half is always sorted
        - Minimum lies in the unsorted part

        With duplicates:
        nums[mid] == nums[right]
        becomes ambiguous,
        so shrink search space carefully.
        */

        while (left < right) {

            int mid = left + (right - left) / 2;


            /*
            CASE 1:
            Right half is unsorted

            nums[mid] > nums[right]

            Minimum must lie to the RIGHT of mid
            */
            if (nums[mid] > nums[right]) {

                left = mid + 1;
            }


            /*
            CASE 2:
            Right half is sorted

            nums[mid] < nums[right]

            Minimum can be at mid
            or to the LEFT
            */
            else if (nums[mid] < nums[right]) {

                right = mid;
            }


            /*
            CASE 3:
            nums[mid] == nums[right]

            Cannot determine which side contains minimum.

            Safely reduce search space by removing
            one duplicate from right side.
            */
            else {

                right--;
            }
        }


        /*
        left == right
        points to minimum element
        */
        return nums[left];
    }
};
// Time Complexity
// Average case:
// O(log n)
// Worst case (many duplicates):
// O(n)
// Example:
// [1,1,1,1,1]
// Space Complexity
// O(1)
