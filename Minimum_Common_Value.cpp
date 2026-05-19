// 2540. Minimum Common Value
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given two integer arrays nums1 and nums2, sorted in non-decreasing order, return the minimum integer common to both arrays. If there is no common integer amongst nums1 and nums2, return -1.

// Note that an integer is said to be common to nums1 and nums2 if both arrays have at least one occurrence of that integer.

 

// Example 1:

// Input: nums1 = [1,2,3], nums2 = [2,4]
// Output: 2
// Explanation: The smallest element common to both arrays is 2, so we return 2.
// Example 2:

// Input: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
// Output: 2
// Explanation: There are two common elements in the array 2 and 3 out of which 2 is the smallest, so 2 is returned.
 

// Constraints:

// 1 <= nums1.length, nums2.length <= 105
// 1 <= nums1[i], nums2[j] <= 109
// Both nums1 and nums2 are sorted in non-decreasing order.
class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {

        /*
        Both arrays are sorted.

        Use two pointers:
        i -> nums1
        j -> nums2

        Move the pointer having smaller value.
        */

        int i = 0;
        int j = 0;


        while (i < nums1.size() && j < nums2.size()) {

            /*
            Common element found
            */
            if (nums1[i] == nums2[j]) {
                return nums1[i];
            }

            /*
            Move pointer of smaller element
            because larger one cannot match it.
            */
            else if (nums1[i] < nums2[j]) {
                i++;
            }

            else {
                j++;
            }
        }


        /*
        No common element exists
        */
        return -1;
    }
};
// Time Complexity
// O(n + m)
// Space Complexity
// O(1)
