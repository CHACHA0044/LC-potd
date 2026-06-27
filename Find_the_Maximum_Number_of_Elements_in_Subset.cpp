// 3020. Find the Maximum Number of Elements in Subset
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an array of positive integers nums.

// You need to select a subset of nums which satisfies the following condition:

// You can place the selected elements in a 0-indexed array such that it follows the pattern: [x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] (Note that k can be be any non-negative power of 2). For example, [2, 4, 16, 4, 2] and [3, 9, 3] follow the pattern while [2, 4, 8, 4, 2] does not.
// Return the maximum number of elements in a subset that satisfies these conditions.

 

// Example 1:

// Input: nums = [5,4,1,2,2]
// Output: 3
// Explanation: We can select the subset {4,2,2}, which can be placed in the array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer is 3.
// Example 2:

// Input: nums = [1,3,2,4]
// Output: 1
// Explanation: We can select the subset {1}, which can be placed in the array as [1] which follows the pattern. Hence the answer is 1. Note that we could have also selected the subsets {2}, {3}, or {4}, there may be multiple subsets which provide the same answer. 
 

// Constraints:

// 2 <= nums.length <= 105
// 1 <= nums[i] <= 109
class Solution {
public:
    int maximumLength(vector<int>& nums) {

        // Store the frequency of every number.
        unordered_map<int, int> freq;
        for (auto &n : nums)
            freq[n]++;

        // Handle the special case for number 1.
        // Since 1^2 = 1, we can only use an odd number of ones.
        int res = (freq[1] - 1) | 1;

        // Remove 1 because it is already processed separately.
        freq.erase(1);

        // Try every remaining distinct number as the starting value.
        for (auto &f : freq) {

            int n = 0;
            int x = f.first;

            // If x itself is the square of another number that already
            // has at least two occurrences, then this chain will be
            // considered while processing the smaller number.
            // Skip it to avoid duplicate work.
            int sq = sqrt(x);
            if (sq * sq == x && freq.count(sq) && freq[sq] > 1)
                continue;

            // Every intermediate value in the chain must appear
            // at least twice because it appears on both sides
            // of the palindrome.
            while (x < 31623 && freq.count(x) && freq[x] > 1) {
                n += 2;
                x *= x;
            }

            // The last value in the chain only needs one occurrence
            // because it becomes the center of the palindrome.
            // If it exists:
            //      contribution = +1
            // Otherwise:
            //      contribution = -1
            res = max(res, n + ((freq.count(x) << 1) - 1));
        }

        return res;
    }
};

/*
Time Complexity: O(n)

Space Complexity: O(n)
*/
