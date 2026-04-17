// 3761. Minimum Absolute Distance Between Mirror Pairs
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums.

// A mirror pair is a pair of indices (i, j) such that:

// 0 <= i < j < nums.length, and
// reverse(nums[i]) == nums[j], where reverse(x) denotes the integer formed by reversing the digits of x. Leading zeros are omitted after reversing, for example reverse(120) = 21.
// Return the minimum absolute distance between the indices of any mirror pair. The absolute distance between indices i and j is abs(i - j).

// If no mirror pair exists, return -1.

 

// Example 1:

// Input: nums = [12,21,45,33,54]

// Output: 1

// Explanation:

// The mirror pairs are:

// (0, 1) since reverse(nums[0]) = reverse(12) = 21 = nums[1], giving an absolute distance abs(0 - 1) = 1.
// (2, 4) since reverse(nums[2]) = reverse(45) = 54 = nums[4], giving an absolute distance abs(2 - 4) = 2.
// The minimum absolute distance among all pairs is 1.

// Example 2:

// Input: nums = [120,21]

// Output: 1

// Explanation:

// There is only one mirror pair (0, 1) since reverse(nums[0]) = reverse(120) = 21 = nums[1].

// The minimum absolute distance is 1.

// Example 3:

// Input: nums = [21,120]

// Output: -1

// Explanation:

// There are no mirror pairs in the array.

 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 109​
// solu =
class Solution {
public:
    int minMirrorPairDistance(vector<int>& nums) {
        
        // Initialize result with a large value (acts like infinity)
        // If no valid pair is found, we will detect it later
        int res = 100000;

        
        // i will track the current index while iterating
        int i = 0;

        
        // HashMap to store:
        // key   -> reversed value of a number
        // value -> index where this reversed value was seen
        unordered_map<int, int> seen;

        
        // Iterate through each number in the array
        for (int& n : nums) {

            int r;  // will store reversed number

            
            // Check if current number 'n' has already been seen
            // as a reversed value of some previous number
            // If yes → we found a mirror pair
            if (seen.count(n)) {
                
                // Compute distance between current index and previous index
                // Update minimum distance
                res = min(res, i - seen[n]);
            }

            
            // Reverse the digits of current number
            // Example: 120 → 21
            // NOTE: This modifies 'n' directly (important side-effect)
            for (r = 0; n; n /= 10) {
                r = r * 10 + (n % 10);
            }

            
            // Store reversed number with its index
            // This helps future elements match with it
            seen[r] = i;

            
            // Move to next index
            i++;
        }

        
        // If res was never updated → no mirror pair exists
        // Trick used here:
        // -(res == 100000) evaluates to:
        //    0  if false
        //   -1  if true
        // Then OR with res gives:
        //    res if found
        //   -1  if not found
        return -(res == 100000) | res;
    }
};
// Time:
// O(n * d)
// d = digits per number (≤10)
// Space:
// O(n)​​​​​​
