// 3867. Sum of GCD of Formed Pairs
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of length n.

// Construct an array prefixGcd where for each index i:

// Let mxi = max(nums[0], nums[1], ..., nums[i]).
// prefixGcd[i] = gcd(nums[i], mxi).
// After constructing prefixGcd:

// Sort prefixGcd in non-decreasing order.
// Form pairs by taking the smallest unpaired element and the largest unpaired element.
// Repeat this process until no more pairs can be formed.
// For each formed pair, compute the gcd of the two elements.
// If n is odd, the middle element in the prefixGcd array remains unpaired and should be ignored.
// Return an integer denoting the sum of the GCD values of all formed pairs.

// The term gcd(a, b) denotes the greatest common divisor of a and b.
 

// Example 1:

// Input: nums = [2,6,4]

// Output: 2

// Explanation:

// Construct prefixGcd:

// i	nums[i]	mxi	prefixGcd[i]
// 0	2	2	2
// 1	6	6	6
// 2	4	6	2
// prefixGcd = [2, 6, 2]. After sorting, it forms [2, 2, 6].

// Pair the smallest and largest elements: gcd(2, 6) = 2. The remaining middle element 2 is ignored. Thus, the sum is 2.

// Example 2:

// Input: nums = [3,6,2,8]

// Output: 5

// Explanation:

// Construct prefixGcd:

// i	nums[i]	mxi	prefixGcd[i]
// 0	3	3	3
// 1	6	6	6
// 2	2	6	2
// 3	8	8	8
// prefixGcd = [3, 6, 2, 8]. After sorting, it forms [2, 3, 6, 8].

// Form pairs: gcd(2, 8) = 2 and gcd(3, 6) = 3. Thus, the sum is 2 + 3 = 5.

 

// Constraints:

// 1 <= n == nums.length <= 105
// 1 <= nums[i] <= 10​​​​​​​9
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    long long sumOfGCDPairs(vector<int>& nums) {

        // Stores gcd(nums[i], maximum element seen up to index i).
        vector<int> prefixGcd;
        prefixGcd.reserve(nums.size());

        // Keeps track of the maximum element encountered so far.
        int currentMax = 0;

        // Construct the prefixGcd array.
        for (int value : nums) {

            // Update the running maximum.
            currentMax = max(currentMax, value);

            // Store gcd(current element, current maximum).
            prefixGcd.push_back(gcd(value, currentMax));
        }

        // Sort the array so that we can always pair
        // the smallest remaining element with the largest remaining element.
        sort(prefixGcd.begin(), prefixGcd.end());

        long long answer = 0;

        // Two pointers for pairing.
        int left = 0;
        int right = prefixGcd.size() - 1;

        // Continue until all possible pairs are formed.
        // If the array size is odd, the middle element is automatically ignored.
        while (left < right) {

            // Add the GCD of the current smallest and largest elements.
            answer += gcd(prefixGcd[left], prefixGcd[right]);

            // Move towards the center.
            left++;
            right--;
        }

        return answer;
    }
};

/*
Time Complexity:

Building prefixGcd : O(n)
Sorting            : O(n log n)
Pairing            : O(n)

Overall:
O(n log n)

Space Complexity:

O(n)
For storing the prefixGcd array.
*/
