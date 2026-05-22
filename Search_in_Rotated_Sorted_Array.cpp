// 33. Search in Rotated Sorted Array
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// There is an integer array nums sorted in ascending order (with distinct values).

// Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].

// Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

// You must write an algorithm with O(log n) runtime complexity.

 

// Example 1:

// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4
// Example 2:

// Input: nums = [4,5,6,7,0,1,2], target = 3
// Output: -1
// Example 3:

// Input: nums = [1], target = 0
// Output: -1
 

// Constraints:

// 1 <= nums.length <= 5000
// -104 <= nums[i] <= 104
// All values of nums are unique.
// nums is an ascending array that is possibly rotated.
// -104 <= target <= 104
class Solution {
public:
    int search(vector<int>& nums, int target) {

        int left = 0;
        int right = nums.size() - 1;


        /*
        Standard Binary Search loop
        */
        while (left <= right) {

            int mid = left + (right - left) / 2;


            /*
            Target found
            */
            if (nums[mid] == target) {
                return mid;
            }


            /*
            ------------------------------------------------
            CASE 1:
            Left half is sorted
            ------------------------------------------------

            Example:
            [4,5,6,7,0,1,2]

            left = 4
            mid  = 7

            Since nums[left] <= nums[mid],
            left portion is sorted.
            */
            if (nums[left] <= nums[mid]) {

                /*
                Check if target lies inside
                the sorted left half.
                */
                if (target >= nums[left] &&
                    target < nums[mid]) {

                    right = mid - 1;
                }

                /*
                Otherwise search right half.
                */
                else {
                    left = mid + 1;
                }
            }


            /*
            ------------------------------------------------
            CASE 2:
            Right half is sorted
            ------------------------------------------------

            Example:
            [6,7,0,1,2,4,5]

            mid = 1

            Right side [1,2,4,5]
            is sorted.
            */
            else {

                /*
                Check if target lies inside
                the sorted right half.
                */
                if (target > nums[mid] &&
                    target <= nums[right]) {

                    left = mid + 1;
                }

                /*
                Otherwise search left half.
                */
                else {
                    right = mid - 1;
                }
            }
        }


        /*
        Target not present
        */
        return -1;
    }
};
// Time Complexity
// Binary Search halves the search space every iteration.
// O(log n)
// Space Complexity
// Only a few variables are used.
// O(1)
