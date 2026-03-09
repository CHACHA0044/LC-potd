// 3129. Find All Possible Stable Binary Arrays I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given 3 positive integers zero, one, and limit.

// A binary array arr is called stable if:

// The number of occurrences of 0 in arr is exactly zero.
// The number of occurrences of 1 in arr is exactly one.
// Each subarray of arr with a size greater than limit must contain both 0 and 1.
// Return the total number of stable binary arrays.

// Since the answer may be very large, return it modulo 109 + 7.

 

// Example 1:

// Input: zero = 1, one = 1, limit = 2

// Output: 2

// Explanation:

// The two possible stable binary arrays are [1,0] and [0,1], as both arrays have a single 0 and a single 1, and no subarray has a length greater than 2.

// Example 2:

// Input: zero = 1, one = 2, limit = 1

// Output: 1

// Explanation:

// The only possible stable binary array is [1,0,1].

// Note that the binary arrays [1,1,0] and [0,1,1] have subarrays of length 2 with identical elements, hence, they are not stable.

// Example 3:

// Input: zero = 3, one = 3, limit = 2

// Output: 14

// Explanation:

// All the possible stable binary arrays are [0,0,1,0,1,1], [0,0,1,1,0,1], [0,1,0,0,1,1], [0,1,0,1,0,1], [0,1,0,1,1,0], [0,1,1,0,0,1], [0,1,1,0,1,0], [1,0,0,1,0,1], [1,0,0,1,1,0], [1,0,1,0,0,1], [1,0,1,0,1,0], [1,0,1,1,0,0], [1,1,0,0,1,0], and [1,1,0,1,0,0].

 

// Constraints:

// 1 <= zero, one, limit <= 200// 1 <= zero, one, limit <= 200

//solu = 
#define MOD 1000000007

class Solution {
public:
    int numberOfStableArrays(int zero, int one, int limit) {

        /*
        dp[i][j][0] -> number of valid arrays using
                      i zeros and j ones
                      where the LAST element is 0

        dp[i][j][1] -> number of valid arrays using
                      i zeros and j ones
                      where the LAST element is 1
        */
        vector<vector<array<int, 2>>> dp(
            zero + 1,
            vector<array<int, 2>>(one + 1, {0, 0})
        );


        /*
        Base Case 1:
        Arrays that contain only zeros.

        We can place up to "limit" consecutive zeros.
        Any more than that would violate the stability rule.
        */
        for (int i = 1; i <= min(zero, limit); i++)
            dp[i][0][0] = 1;


        /*
        Base Case 2:
        Arrays that contain only ones.

        Similarly, we can place at most "limit" ones consecutively.
        */
        for (int j = 1; j <= min(one, limit); j++)
            dp[0][j][1] = 1;


        /*
        Fill the DP table.

        For each combination of zeros (i) and ones (j),
        we compute the number of valid arrays that end
        with 0 or end with 1.
        */
        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {

                /*
                ----------------------------
                Case 1: Last element = 0
                ----------------------------

                To end with 0, we append a 0 to any valid
                array that previously used (i-1) zeros.

                That previous array could end with:
                - 0
                - 1
                */
                long long val0 =
                    (0LL + dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;

                /*
                However, we must ensure we do NOT create
                more than "limit" consecutive zeros.

                If we already had "limit" zeros before,
                adding another 0 would break the rule.

                So we subtract the invalid sequences where
                the last block already had 'limit' zeros.
                */
                if (i > limit)
                    val0 = (val0 - dp[i - limit - 1][j][1] + MOD) % MOD;

                dp[i][j][0] = val0;



                /*
                ----------------------------
                Case 2: Last element = 1
                ----------------------------

                Similar logic:
                Append 1 to arrays that previously used (j-1) ones.
                */
                long long val1 =
                    (0LL + dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD;

                /*
                Again remove cases where we would exceed
                "limit" consecutive ones.
                */
                if (j > limit)
                    val1 = (val1 - dp[i][j - limit - 1][0] + MOD) % MOD;

                dp[i][j][1] = val1;
            }
        }


        /*
        Final answer:
        Arrays that use all zeros and ones,
        regardless of whether they end in 0 or 1.
        */
        return (dp[zero][one][0] + dp[zero][one][1]) % MOD;
    }
};
// tc = O( 0 * 1)
// sc = O( 0 * 1)
