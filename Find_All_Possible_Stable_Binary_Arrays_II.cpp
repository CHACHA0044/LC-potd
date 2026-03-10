// 3130. Find All Possible Stable Binary Arrays II
// Hard
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

// The two possible stable binary arrays are [1,0] and [0,1].

// Example 2:

// Input: zero = 1, one = 2, limit = 1

// Output: 1

// Explanation:

// The only possible stable binary array is [1,0,1].

// Example 3:

// Input: zero = 3, one = 3, limit = 2

// Output: 14

// Explanation:

// All the possible stable binary arrays are [0,0,1,0,1,1], [0,0,1,1,0,1], [0,1,0,0,1,1], [0,1,0,1,0,1], [0,1,0,1,1,0], [0,1,1,0,0,1], [0,1,1,0,1,0], [1,0,0,1,0,1], [1,0,0,1,1,0], [1,0,1,0,0,1], [1,0,1,0,1,0], [1,0,1,1,0,0], [1,1,0,0,1,0], and [1,1,0,1,0,0].

 

// Constraints:
// 1 <= zero, one, limit <= 1000

// solu = 
class Solution {
public:
    const int N = 1e9 + 7;

    /*
    dp[i][j][0] -> number of stable arrays using
                   i zeros and j ones
                   where the LAST element is 0

    dp[i][j][1] -> number of stable arrays using
                   i zeros and j ones
                   where the LAST element is 1
    */
    int dp[1001][1001][2];

    int numberOfStableArrays(int zero, int one, int limit) {

        /*
        Base case:
        Arrays containing ONLY zeros OR ONLY ones.

        We can place at most "limit" consecutive identical numbers,
        so we initialize dp for sequences up to length = limit.
        */

        for(int i = 0; i <= min(limit, max(one, zero)); i++) {
            dp[i][0][0] = 1; // array with i zeros only (ending with 0)
            dp[0][i][1] = 1; // array with i ones only (ending with 1)
        }

        /*
        Build the DP table.

        i -> number of zeros used
        j -> number of ones used
        */

        for(int i = 1; i <= zero; i++) {
            for(int j = 1; j <= one; j++) {

                /*
                Case 1: Current array ends with 0

                To end with 0, we append 0 to a previous array that used
                (i-1) zeros and j ones.

                The previous array could end with:
                - 0
                - 1
                */

                dp[i][j][0] =
                    ((long long)dp[i-1][j][0] + dp[i-1][j][1]) % N;


                /*
                Case 2: Current array ends with 1

                Append 1 to an array that used
                i zeros and (j-1) ones.
                */

                dp[i][j][1] =
                    ((long long)dp[i][j-1][1] + dp[i][j-1][0]) % N;


                /*
                Now enforce the stability rule:

                We cannot have more than "limit" consecutive 0s.

                If we already had "limit" zeros before,
                adding another zero would create (limit+1) zeros.

                So we subtract those invalid sequences.
                */

                if(i - 1 - limit >= 0)
                    dp[i][j][0] -= dp[i - 1 - limit][j][1];


                /*
                Similarly for ones:
                Remove sequences that would create
                more than "limit" consecutive 1s.
                */

                if(j - 1 - limit >= 0)
                    dp[i][j][1] -= dp[i][j - 1 - limit][0];


                /*
                Ensure values stay positive after subtraction
                because we are working modulo 1e9+7.
                */

                if(dp[i][j][0] < 0) dp[i][j][0] += N;
                if(dp[i][j][1] < 0) dp[i][j][1] += N;
            }
        }

        /*
        Final answer:
        Arrays that use all zeros and ones,
        regardless of whether the last element is 0 or 1.
        */

        return ((long long)dp[zero][one][1] + dp[zero][one][0]) % N;
    }
};
// tc = O(n^2)
// sc = O(n^2)


//solu 2 = 
class Solution {
public:
    const int N = 1e9 + 7;

    /*
    dp[i][j][0] -> number of stable arrays using
                   i zeros and j ones
                   where the LAST placed block is 0

    dp[i][j][1] -> number of stable arrays using
                   i zeros and j ones
                   where the LAST placed block is 1
    */
    int dp[1001][1001][2];


    /*
    f1(i, j, l)
    ----------------
    Returns number of valid arrays that use:
        i zeros
        j ones
    where the LAST block placed consists of 1s.

    Since the last block is 1s, the previous block must be 0s.
    */

    int f1(int i, int j, int l){

        // If we used more elements than available, invalid
        if(i < 0 || j < 0) return 0;

        // If no elements left, we formed a valid array
        if(i == 0 && j == 0) return 1;

        // Return memoized result if already computed
        if(dp[i][j][1] != -1) return dp[i][j][1];

        int ans = 0;

        /*
        Place a block of 1s of size k
        where 1 <= k <= limit.

        After placing k ones,
        the previous block must be zeros.
        */

        for(int k = 1; k <= l; k++){
            ans = ((long long)ans + f0(i, j - k, l)) % N;
        }

        return dp[i][j][1] = ans;
    }


    /*
    f0(i, j, l)
    ----------------
    Returns number of valid arrays that use:
        i zeros
        j ones
    where the LAST block placed consists of 0s.

    Since the last block is 0s, the previous block must be 1s.
    */

    int f0(int i, int j, int l){

        // Invalid if we used more elements than available
        if(i < 0 || j < 0) return 0;

        // If no elements left, we formed a valid array
        if(i == 0 && j == 0) return 1;

        // Return cached result if already computed
        if(dp[i][j][0] != -1) return dp[i][j][0];

        int ans = 0;

        /*
        Place a block of 0s of size k
        where 1 <= k <= limit.

        After placing k zeros,
        the previous block must be ones.
        */

        for(int k = 1; k <= l; k++){
            ans = ((long long)ans + f1(i - k, j, l)) % N;
        }

        return dp[i][j][0] = ans;
    }


    int numberOfStableArrays(int zero, int one, int limit) {

        /*
        Initialize DP table with -1
        to indicate "not computed yet".
        */

        for(int i = 0; i < 1001; i++){
            for(int j = 0; j < 1001; j++){
                dp[i][j][0] = dp[i][j][1] = -1;
            }
        }

        /*
        Final answer:
        Arrays can end with either
        - a block of 0s
        - a block of 1s
        */

        return ((long long)f1(zero, one, limit) + f0(zero, one, limit)) % N;
    }
};
// tc = O(n^3)
// sc = O(n^2)
