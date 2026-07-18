// 1979. Find Greatest Common Divisor of Array
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given an integer array nums, return the greatest common divisor of the smallest number and largest number in nums.

// The greatest common divisor of two numbers is the largest positive integer that evenly divides both numbers.

 

// Example 1:

// Input: nums = [2,5,6,9,10]
// Output: 2
// Explanation:
// The smallest number in nums is 2.
// The largest number in nums is 10.
// The greatest common divisor of 2 and 10 is 2.
// Example 2:

// Input: nums = [7,5,6,8,3]
// Output: 1
// Explanation:
// The smallest number in nums is 3.
// The largest number in nums is 8.
// The greatest common divisor of 3 and 8 is 1.
// Example 3:

// Input: nums = [3,3]
// Output: 3
// Explanation:
// The smallest number in nums is 3.
// The largest number in nums is 3.
// The greatest common divisor of 3 and 3 is 3.
 

// Constraints:

// 2 <= nums.length <= 1000
// 1 <= nums[i] <= 1000
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int findGCD(vector<int>& nums) {

        // Find the smallest element in the array.
        int minimumValue = *min_element(nums.begin(), nums.end());

        // Find the largest element in the array.
        int maximumValue = *max_element(nums.begin(), nums.end());

        // Compute and return the GCD of the smallest and largest elements.
        return gcd(minimumValue, maximumValue);
    }
};

/*
Time Complexity:

Finding minimum : O(n)
Finding maximum : O(n)
GCD computation : O(log(min(minimumValue, maximumValue)))

Overall:
O(n)

Space Complexity:

O(1)
*/
