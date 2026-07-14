// 3336. Find the Number of Subsequences With Equal GCD
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums.

// Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:

// The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
// The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
// Return the total number of such pairs.

// Since the answer may be very large, return it modulo 109 + 7.

 

// Example 1:

// Input: nums = [1,2,3,4]

// Output: 10

// Explanation:

// The subsequence pairs which have the GCD of their elements equal to 1 are:

// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// ([1, 2, 3, 4], [1, 2, 3, 4])
// Example 2:

// Input: nums = [10,20,30]

// Output: 2

// Explanation:

// The subsequence pairs which have the GCD of their elements equal to 10 are:

// ([10, 20, 30], [10, 20, 30])
// ([10, 20, 30], [10, 20, 30])
// Example 3:

// Input: nums = [1,1,1,1]

// Output: 50

 

// Constraints:

// 1 <= nums.length <= 200
// 1 <= nums[i] <= 200
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        // Modulo required by the problem statement
        const int MOD = 1000000007;

        // Maximum possible value of any element in nums
        // Since nums[i] <= 200, every possible GCD also lies in [1, 200]
        const int MAXV = 200;

        // dp[gcd1][gcd2]
        // Stores the number of ways to process the elements seen so far such that:
        // - First subsequence has GCD = gcd1
        // - Second subsequence has GCD = gcd2
        //
        // gcd value 0 means that subsequence is still empty.
        vector<vector<int>> dp(MAXV + 1, vector<int>(MAXV + 1, 0));

        // Initially, both subsequences are empty.
        dp[0][0] = 1;

        // Process every number one by one.
        for (int value : nums) {

            // Copy current DP.
            // This automatically handles the third choice:
            // "Do not use this element in either subsequence."
            vector<vector<int>> next = dp;

            // Try every previously reachable state.
            for (int gcd1 = 0; gcd1 <= MAXV; gcd1++) {
                for (int gcd2 = 0; gcd2 <= MAXV; gcd2++) {

                    // Ignore unreachable states.
                    if (dp[gcd1][gcd2] == 0)
                        continue;

                    // If we place current value into subsequence 1,
                    // update its GCD.
                    //
                    // If subsequence 1 is empty (gcd1 == 0),
                    // its GCD simply becomes value.
                    //
                    // Otherwise,
                    // new GCD = gcd(previous GCD, current value).
                    int newGcd1 = (gcd1 == 0 ? value : gcd(gcd1, value));

                    // Similarly compute the updated GCD
                    // if current value is added to subsequence 2.
                    int newGcd2 = (gcd2 == 0 ? value : gcd(gcd2, value));

                    // Choice 1:
                    // Put current element into subsequence 1.
                    next[newGcd1][gcd2] =
                        (next[newGcd1][gcd2] + dp[gcd1][gcd2]) % MOD;

                    // Choice 2:
                    // Put current element into subsequence 2.
                    next[gcd1][newGcd2] =
                        (next[gcd1][newGcd2] + dp[gcd1][gcd2]) % MOD;

                    // Choice 3:
                    // Ignore this element.
                    // Already handled because "next" was initialized as "dp".
                }
            }

            // Move to the next iteration.
            dp.swap(next);
        }

        int answer = 0;

        // We only want states where:
        // - Both subsequences are non-empty
        //   (GCD cannot be 0 anymore)
        // - Their GCDs are equal.
        for (int g = 1; g <= MAXV; g++) {
            answer = (answer + dp[g][g]) % MOD;
        }

        return answer;
    }
};

/*
Time Complexity:

Let:
N = nums.size()
V = 200 (maximum possible value)

For every element, we iterate over all possible pairs of GCD values.

Time Complexity = O(N * V^2)
                = O(N * 200 * 200)
                = O(8 × 10^6)

This easily fits within the given constraints.

Space Complexity:

We maintain two DP tables of size (201 × 201).

Space Complexity = O(V^2)
                 = O(200^2)
                 = O(40,000)
*/
