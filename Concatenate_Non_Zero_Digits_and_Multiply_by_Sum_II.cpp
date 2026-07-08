// 3756. Concatenate Non-Zero Digits and Multiply by Sum II
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s of length m consisting of digits. You are also given a 2D integer array queries, where queries[i] = [li, ri].

// For each queries[i], extract the substring s[li..ri]. Then, perform the following:

// Form a new integer x by concatenating all the non-zero digits from the substring in their original order. If there are no non-zero digits, x = 0.
// Let sum be the sum of digits in x. The answer is x * sum.
// Return an array of integers answer where answer[i] is the answer to the ith query.

// Since the answers may be very large, return them modulo 109 + 7.

 

// Example 1:

// Input: s = "10203004", queries = [[0,7],[1,3],[4,6]]

// Output: [12340, 4, 9]

// Explanation:

// s[0..7] = "10203004"
// x = 1234
// sum = 1 + 2 + 3 + 4 = 10
// Therefore, answer is 1234 * 10 = 12340.
// s[1..3] = "020"
// x = 2
// sum = 2
// Therefore, the answer is 2 * 2 = 4.
// s[4..6] = "300"
// x = 3
// sum = 3
// Therefore, the answer is 3 * 3 = 9.
// Example 2:

// Input: s = "1000", queries = [[0,3],[1,1]]

// Output: [1, 0]

// Explanation:

// s[0..3] = "1000"
// x = 1
// sum = 1
// Therefore, the answer is 1 * 1 = 1.
// s[1..1] = "0"
// x = 0
// sum = 0
// Therefore, the answer is 0 * 0 = 0.
// Example 3:

// Input: s = "9876543210", queries = [[0,9]]

// Output: [444444137]

// Explanation:

// s[0..9] = "9876543210"
// x = 987654321
// sum = 9 + 8 + 7 + 6 + 5 + 4 + 3 + 2 + 1 = 45
// Therefore, the answer is 987654321 * 45 = 44444444445.
// We return 44444444445 modulo (109 + 7) = 444444137.
 

// Constraints:

// 1 <= m == s.length <= 105
// s consists of digits only.
// 1 <= queries.length <= 105
// queries[i] = [li, ri]
// 0 <= li <= ri < m
class Solution {
private:
    static constexpr int MOD = 1000000007;
    static constexpr int MAX = 100001;

    // pow[i] = (10^i) % MOD
    // This is precomputed once and reused for every test case.
    inline static int pow[MAX];

    // Static initializer.
    // Executes only once before any object of Solution is created.
    // It fills the powers of 10 array.
    inline static int init = []() {
        pow[0] = 1;

        for (int i = 1; i < MAX; i++)
            pow[i] = pow[i - 1] * 10LL % MOD;

        return 0;
    }();

public:
    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {

        int n = s.length();

        // ------------------------------------------------------------
        // A[i]   -> Prefix sum of ALL digits till index i-1.
        //
        // Example:
        // s = "10203004"
        //
        // A = [0,1,1,3,3,6,6,6,10]
        //
        // Using prefix sums,
        // Sum of digits in any substring [l,r]
        // = A[r+1] - A[l]
        // ------------------------------------------------------------
        vector<int> A(n + 1, 0);

        // ------------------------------------------------------------
        // B[i] stores the concatenated value formed by all NON-ZERO
        // digits till index i-1 (mod MOD).
        //
        // Example:
        // s = "10203004"
        //
        // Process:
        //
        // 1 -> 1
        // 0 -> ignored
        // 2 -> 12
        // 0 -> ignored
        // 3 -> 123
        // 0 -> ignored
        // 0 -> ignored
        // 4 -> 1234
        //
        // B keeps these values modulo MOD.
        // ------------------------------------------------------------
        vector<int> B(n + 1, 0);

        // ------------------------------------------------------------
        // len[i] = number of NON-ZERO digits till index i-1.
        //
        // Example:
        // s = "10203004"
        //
        // len = [0,1,1,2,2,3,3,3,4]
        //
        // This helps us determine how many digits belong to the suffix
        // while extracting the concatenated number.
        // ------------------------------------------------------------
        vector<int> len(n + 1, 0);

        // Build all prefix arrays.
        for (int i = 0; i < n; i++) {

            int d = s[i] - '0';

            // Prefix sum of digits.
            A[i + 1] = A[i] + d;

            if (d) {

                // Non-zero digit contributes to concatenation.
                //
                // Previous Number = 123
                // Current Digit = 4
                //
                // New Number = 1234
                //
                // Formula:
                // old * 10 + digit
                B[i + 1] = (B[i] * 10LL + d) % MOD;

                len[i + 1] = len[i] + 1;
            }
            else {

                // Zero digits are ignored while forming x.
                //
                // Example:
                // 10203
                //
                // Concatenation remains 123.
                B[i + 1] = B[i];
                len[i + 1] = len[i];
            }
        }

        vector<int> res;
        res.reserve(queries.size());

        for (auto &q : queries) {

            int l = q[0];

            // Convert to prefix indexing.
            int r = q[1] + 1;

            // --------------------------------------------------------
            // We need the concatenated NON-ZERO digits only inside
            // substring [l,r].
            //
            // Suppose:
            //
            // Entire prefix till r gives
            //
            // B[r] = 123456
            //
            // Prefix till l gives
            //
            // B[l] = 123
            //
            // We cannot simply subtract.
            //
            // Why?
            //
            // 123456 - 123 != 456
            //
            // The prefix digits occupy higher decimal places.
            //
            // So first shift B[l] left by the number of remaining
            // non-zero digits.
            //
            // Example:
            //
            // B[l] = 123
            // Remaining digits = 3
            //
            // Shift:
            //
            // 123 -> 123000
            //
            // achieved using
            //
            // 123 * 10^3
            // --------------------------------------------------------
            long long sub =
                B[l] * 1LL * pow[len[r] - len[l]] % MOD;

            // Remove the shifted prefix.
            //
            // x = concatenated number inside substring.
            //
            // Add MOD before taking modulo to avoid negative values.
            long long x = (B[r] - sub + MOD) % MOD;

            // Sum of digits in substring.
            long long digitSum = A[r] - A[l];

            // Required answer.
            res.push_back(x * digitSum % MOD);
        }

        return res;
    }
};

/*
------------------------------------------------------------
Time Complexity
------------------------------------------------------------

Preprocessing:
O(N)

Each Query:
O(1)

Total:
O(N + Q)

------------------------------------------------------------
Space Complexity
------------------------------------------------------------

O(N)

------------------------------------------------------------
Important Observations / Edge Cases
------------------------------------------------------------

1. Substring contains only zeros.

Example:
"000"

Concatenated value x = 0
Digit sum = 0

Answer = 0

------------------------------------------------------------

2. Substring begins or ends with zeros.

Example:
"0012030"

Only non-zero digits are concatenated.

x = 123

The leading/trailing zeros do not affect x.

------------------------------------------------------------

3. Very large concatenated number.

Example:
999999999999999...

It easily exceeds 64-bit integer range.

Hence B[] always stores values modulo MOD.

------------------------------------------------------------

4. Why do we need len[] ?

Suppose

B[r] = 123456
B[l] = 123

Simply subtracting is incorrect.

We must first convert

123 -> 123000

using

123 × 10^(remaining non-zero digits)

Only then can we subtract to obtain 456.

len[] tells exactly how many non-zero digits remain.

------------------------------------------------------------

5. Why precompute powers of 10?

Every query requires multiplying by

10^(remaining digits)

Computing exponentiation every query would be O(log N).

By precomputing,

every query becomes O(1).

------------------------------------------------------------
*/
