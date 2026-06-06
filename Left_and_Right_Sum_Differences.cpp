// 2574. Left and Right Sum Differences
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given a 0-indexed integer array nums of size n.

// Define two arrays leftSum and rightSum where:

// leftSum[i] is the sum of elements to the left of the index i in the array nums. If there is no such element, leftSum[i] = 0.
// rightSum[i] is the sum of elements to the right of the index i in the array nums. If there is no such element, rightSum[i] = 0.
// Return an integer array answer of size n where answer[i] = |leftSum[i] - rightSum[i]|.

 

// Example 1:

// Input: nums = [10,4,8,3]
// Output: [15,1,11,22]
// Explanation: The array leftSum is [0,10,14,22] and the array rightSum is [15,11,3,0].
// The array answer is [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22].
// Example 2:

// Input: nums = [1]
// Output: [0]
// Explanation: The array leftSum is [0] and the array rightSum is [0].
// The array answer is [|0 - 0|] = [0].
 

// Constraints:

// 1 <= nums.length <= 1000
// 1 <= nums[i] <= 105
class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {

        int n = nums.size();

        vector<int> ans(n);


        /*
        Calculate total sum of the array.

        Initially this represents the sum of all elements.
        As we move left to right, it will be used to
        maintain the right-side sum.
        */
        int totalSum = accumulate(nums.begin(), nums.end(), 0);


        /*
        Stores the sum of elements to the left
        of the current index.
        */
        int leftSum = 0;


        /*
        Process every index.
        */
        for (int i = 0; i < n; i++) {

            /*
            Remove current element from totalSum.

            After removal:
            totalSum becomes the sum of elements
            strictly to the right of index i.
            */
            totalSum -= nums[i];

            int rightSum = totalSum;


            /*
            answer[i] = absolute difference
            between left sum and right sum.
            */
            ans[i] = abs(leftSum - rightSum);


            /*
            Add current element to leftSum.

            This prepares leftSum for the next index.
            */
            leftSum += nums[i];
        }

        return ans;
    }
};

/*
Time Complexity: O(n)

Space Complexity: O(1)
(excluding the output array)
*/
