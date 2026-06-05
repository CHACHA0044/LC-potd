// 3753. Total Waviness of Numbers in Range II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given two integers num1 and num2 representing an inclusive range [num1, num2].

// The waviness of a number is defined as the total count of its peaks and valleys:

// A digit is a peak if it is strictly greater than both of its immediate neighbors.
// A digit is a valley if it is strictly less than both of its immediate neighbors.
// The first and last digits of a number cannot be peaks or valleys.
// Any number with fewer than 3 digits has a waviness of 0.
// Return the total sum of waviness for all numbers in the range [num1, num2].
 

// Example 1:

// Input: num1 = 120, num2 = 130

// Output: 3

// Explanation:

// In the range [120, 130]:

// 120: middle digit 2 is a peak, waviness = 1.
// 121: middle digit 2 is a peak, waviness = 1.
// 130: middle digit 3 is a peak, waviness = 1.
// All other numbers in the range have a waviness of 0.
// Thus, total waviness is 1 + 1 + 1 = 3.

// Example 2:

// Input: num1 = 198, num2 = 202

// Output: 3

// Explanation:

// In the range [198, 202]:

// 198: middle digit 9 is a peak, waviness = 1.
// 201: middle digit 0 is a valley, waviness = 1.
// 202: middle digit 0 is a valley, waviness = 1.
// All other numbers in the range have a waviness of 0.
// Thus, total waviness is 1 + 1 + 1 = 3.

// Example 3:

// Input: num1 = 4848, num2 = 4848

// Output: 2

// Explanation:

// Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

 

// Constraints:

// 1 <= num1 <= num2 <= 1015​​​​​​​
class Solution {
public:
    using ll = long long;

    /*
    ---------------------------------------------------------
    Each DP state returns:

    cnt  = number of valid numbers that can be formed
    wav  = total waviness contributed by those numbers
    ---------------------------------------------------------
    */
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;

    /*
    DP dimensions:

    pos     = current digit position

    p2      = digit before previous
    p1      = previous digit

    10 is used as a sentinel value
    meaning "digit does not exist yet"

    tight   = are we still restricted
              by the upper bound?

    started = have we started building
              a non-leading-zero number?
    */
    Node dp[20][11][11][2][2];
    bool vis[20][11][11][2][2];


    Node dfs(int pos,
             int p2,
             int p1,
             int tight,
             int started) {

        /*
        -----------------------------------------------------
        Reached end of the number.

        One valid number formed.
        No extra waviness to add.
        -----------------------------------------------------
        */
        if (pos == s.size()) {
            return {1, 0};
        }


        /*
        Memoized state.
        */
        if (vis[pos][p2][p1][tight][started]) {
            return dp[pos][p2][p1][tight][started];
        }

        vis[pos][p2][p1][tight][started] = true;


        Node res = {0, 0};


        /*
        Maximum digit allowed here.

        If tight = 1,
        cannot exceed digit from upper bound.

        Otherwise can use 0..9.
        */
        int limit = tight ? s[pos] - '0' : 9;


        /*
        Try every possible digit.
        */
        for (int d = 0; d <= limit; d++) {

            int ntight = tight && (d == limit);


            /*
            =================================================
            CASE 1:
            Still skipping leading zeros
            =================================================
            */
            if (!started && d == 0) {

                Node nxt =
                    dfs(pos + 1,
                        10,
                        10,
                        ntight,
                        0);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            }


            /*
            =================================================
            CASE 2:
            First non-zero digit
            =================================================
            */
            else if (!started) {

                Node nxt =
                    dfs(pos + 1,
                        10,
                        d,
                        ntight,
                        1);

                res.cnt += nxt.cnt;
                res.wav += nxt.wav;
            }


            /*
            =================================================
            CASE 3:
            Number already started
            =================================================
            */
            else {

                /*
                Move digit window:

                Before:
                    p2 p1

                After choosing d:
                    p1 d
                */
                Node nxt =
                    dfs(pos + 1,
                        p1,
                        d,
                        ntight,
                        1);

                long long add = 0;


                /*
                ------------------------------------------------
                We can determine whether p1 is a peak
                or valley only after seeing digit d.

                Pattern:

                    p2 p1 d

                Peak:
                    p1 > p2
                    p1 > d

                Valley:
                    p1 < p2
                    p1 < d
                ------------------------------------------------
                */
                if (p2 != 10) {

                    if ((p1 > p2 && p1 > d) ||
                        (p1 < p2 && p1 < d)) {

                        add = 1;
                    }
                }


                /*
                Every number represented by nxt.cnt
                receives this additional waviness.
                */
                res.cnt += nxt.cnt;

                res.wav +=
                    nxt.wav +
                    add * nxt.cnt;
            }
        }


        return dp[pos][p2][p1][tight][started] = res;
    }


    /*
    ---------------------------------------------------------
    Returns total waviness of all numbers
    in range [1, x].
    ---------------------------------------------------------
    */
    long long solve(long long x) {

        if (x <= 0) {
            return 0;
        }

        s = to_string(x);

        memset(vis, 0, sizeof(vis));

        return dfs(
            0,
            10,
            10,
            1,
            0
        ).wav;
    }


    long long totalWaviness(long long num1,
                            long long num2) {

        /*
        Range answer:

        waviness(1...num2)
        -
        waviness(1...num1-1)
        */
        return solve(num2) -
               solve(num1 - 1);
    }
};
// Time Complexity
// Number of DP states:
// 20 × 11 × 11 × 2 × 2
// Each state tries:
// 10 digits
// Overall:
// O(20 × 11 × 11 × 2 × 2 × 10)
// ≈ O(100000)
// Space Complexity
// DP table:
// O(20 × 11 × 11 × 2 × 2)
// Which is approximately:
// O(10000)
