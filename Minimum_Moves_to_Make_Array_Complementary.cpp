// 1674. Minimum Moves to Make Array Complementary
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of even length n and an integer limit. In one move, you can replace any integer from nums with another integer between 1 and limit, inclusive.

// The array nums is complementary if for all indices i (0-indexed), nums[i] + nums[n - 1 - i] equals the same number. For example, the array [1,2,3,4] is complementary because for all indices i, nums[i] + nums[n - 1 - i] = 5.

// Return the minimum number of moves required to make nums complementary.

 

// Example 1:

// Input: nums = [1,2,4,3], limit = 4
// Output: 1
// Explanation: In 1 move, you can change nums to [1,2,2,3] (underlined elements are changed).
// nums[0] + nums[3] = 1 + 3 = 4.
// nums[1] + nums[2] = 2 + 2 = 4.
// nums[2] + nums[1] = 2 + 2 = 4.
// nums[3] + nums[0] = 3 + 1 = 4.
// Therefore, nums[i] + nums[n-1-i] = 4 for every i, so nums is complementary.
// Example 2:

// Input: nums = [1,2,2,1], limit = 2
// Output: 2
// Explanation: In 2 moves, you can change nums to [2,2,2,2]. You cannot change any number to 3 since 3 > limit.
// Example 3:

// Input: nums = [1,2,1,2], limit = 2
// Output: 0
// Explanation: nums is already complementary.
 

// Constraints:

// n == nums.length
// 2 <= n <= 105
// 1 <= nums[i] <= limit <= 105
// n is even.
// solu -
class Solution {
public:
    int minMoves(vector<int>& nums, int limit) {

        int n = nums.size();


        /*
        =====================================================
        Difference Array Technique
        =====================================================

        Possible pair sums range from:
            2 to 2*limit

        For every mirrored pair:
            (nums[i], nums[n-1-i])

        We calculate how many moves are needed
        for every possible target sum.
        */


        vector<int> diff(2 * limit + 2, 0);


        /*
        Process every pair
        */
        for (int i = 0; i < n / 2; i++) {

            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = min(a, b);
            int high = max(a, b);

            int sum = a + b;


            /*
            =================================================
            Move Ranges
            =================================================

            Initially assume:
                every target needs 2 moves

            Then optimize ranges.

            -------------------------------------------------
            0 moves:
                target = a+b

            1 move:
                target in:
                [low+1 , high+limit]

            2 moves:
                everything else
            */


            /*
            By default:
            add +2 moves for all sums
            */
            diff[2] += 2;
            diff[2 * limit + 1] -= 2;


            /*
            One move range starts
            */
            diff[low + 1] -= 1;

            /*
            One move range ends
            */
            diff[high + limit + 1] += 1;


            /*
            Zero move at exact current sum
            */
            diff[sum] -= 1;
            diff[sum + 1] += 1;
        }


        /*
        =====================================================
        Build prefix sum to get moves for each target sum
        =====================================================
        */
        int ans = INT_MAX;

        int curr = 0;

        for (int s = 2; s <= 2 * limit; s++) {

            curr += diff[s];

            ans = min(ans, curr);
        }


        return ans;
    }
};
// Time Complexity
// Processing all pairs:
// O(n)
// Prefix sum traversal:
// O(limit)
// Overall:
// O(n + limit)
// Space Complexity
// Difference array:
// O(limit)
