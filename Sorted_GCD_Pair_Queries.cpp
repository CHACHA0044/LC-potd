// 3312. Sorted GCD Pair Queries
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of length n and an integer array queries.

// Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.

// For each query queries[i], you need to find the element at index queries[i] in gcdPairs.

// Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.

// The term gcd(a, b) denotes the greatest common divisor of a and b.

 

// Example 1:

// Input: nums = [2,3,4], queries = [0,2,2]

// Output: [1,2,2]

// Explanation:

// gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].

// After sorting in ascending order, gcdPairs = [1, 1, 2].

// So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].

// Example 2:

// Input: nums = [4,4,2,1], queries = [5,3,1,0]

// Output: [4,2,1,1]

// Explanation:

// gcdPairs sorted in ascending order is [1, 1, 1, 2, 2, 4].

// Example 3:

// Input: nums = [2,2], queries = [0,0]

// Output: [2,2]

// Explanation:

// gcdPairs = [2].

 

// Constraints:

// 2 <= n == nums.length <= 105
// 1 <= nums[i] <= 5 * 104
// 1 <= queries.length <= 105
// 0 <= queries[i] < n * (n - 1) / 2
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {

        // Find the maximum value present in the array.
        // This limits the range of all possible GCD values.
        int maxValue = *max_element(nums.begin(), nums.end());

        // frequency[x] = number of times value x appears.
        vector<int> frequency(maxValue + 1);
        for (int value : nums) {
            frequency[value]++;
        }

        // divisibleCount[g]
        // Stores how many numbers are divisible by g.
        vector<long long> divisibleCount(maxValue + 1);

        // For every possible GCD value,
        // count all array elements divisible by it.
        for (int gcdValue = 1; gcdValue <= maxValue; gcdValue++) {
            for (int multiple = gcdValue; multiple <= maxValue; multiple += gcdValue) {
                divisibleCount[gcdValue] += frequency[multiple];
            }
        }

        // exactPairs[g]
        // Number of pairs whose GCD is exactly g.
        vector<long long> exactPairs(maxValue + 1);

        // Inclusion-Exclusion (Mobius-like sieve).
        // First count all pairs divisible by g,
        // then remove pairs already counted for larger multiples.
        for (int gcdValue = maxValue; gcdValue >= 1; gcdValue--) {

            long long count = divisibleCount[gcdValue];

            // Total pairs whose numbers are both divisible by gcdValue.
            exactPairs[gcdValue] = count * (count - 1) / 2;

            // Remove pairs whose actual GCD is a larger multiple.
            for (int multiple = gcdValue * 2; multiple <= maxValue; multiple += gcdValue) {
                exactPairs[gcdValue] -= exactPairs[multiple];
            }
        }

        // prefix[g]
        // Total number of pairs having GCD <= g.
        vector<long long> prefix(maxValue + 1);

        for (int gcdValue = 1; gcdValue <= maxValue; gcdValue++) {
            prefix[gcdValue] = prefix[gcdValue - 1] + exactPairs[gcdValue];
        }

        vector<int> answer;
        answer.reserve(queries.size());

        // For every query,
        // binary search the first GCD whose cumulative
        // pair count exceeds the queried index.
        for (long long query : queries) {
            int gcdValue =
                lower_bound(prefix.begin() + 1, prefix.end(), query + 1) - prefix.begin();

            answer.push_back(gcdValue);
        }

        return answer;
    }
};

/*
Time Complexity:

Let:
N = nums.size()
M = maximum value in nums (<= 50000)
Q = queries.size()

Frequency array          : O(N)
Divisibility sieve       : O(M log M)
Inclusion-Exclusion      : O(M log M)
Binary search per query  : O(Q log M)

Overall:
O(N + M log M + Q log M)

Space Complexity:

O(M)
*/
