// 3666. Minimum Operations to Equalize Binary String
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given a binary string s, and an integer k.

// In one operation, you must choose exactly k different indices and flip each '0' to '1' and each '1' to '0'.

// Return the minimum number of operations required to make all characters in the string equal to '1'. If it is not possible, return -1.

 

// Example 1:

// Input: s = "110", k = 1

// Output: 1

// Explanation:

// There is one '0' in s.
// Since k = 1, we can flip it directly in one operation.
// Example 2:

// Input: s = "0101", k = 3

// Output: 2

// Explanation:

// One optimal set of operations choosing k = 3 indices in each operation is:

// Operation 1: Flip indices [0, 1, 3]. s changes from "0101" to "1000".
// Operation 2: Flip indices [1, 2, 3]. s changes from "1000" to "1111".
// Thus, the minimum number of operations is 2.

// Example 3:

// Input: s = "101", k = 2

// Output: -1

// Explanation:

// Since k = 2 and s has only one '0', it is impossible to flip exactly k indices to make all '1'. Hence, the answer is -1.

 

// Constraints:

// 1 <= s.length <= 10​​​​​​​5
// s[i] is either '0' or '1'.
//solu = 
class Solution {
public:
    int minOperations(string s, int k) {

        int zero = 0;
        int len = s.length();

        // Count number of zeros
        // (~s[i] & 1) is a trick:
        // if s[i] == '0' → contributes 1
        // if s[i] == '1' → contributes 0
        for (int i = 0; i < len; i++)
            zero += ~s[i] & 1;

        // If there are no zeros, already all '1'
        if (!zero)
            return 0;

        // Special case: if k == n
        // Every operation flips the entire string
        if (len == k)
            return ((zero == len) << 1) - 1;

        int base = len - k;

        // Case 1: total operations is ODD
        // In odd case, total flips = t*k
        // So parity of total flips = k mod 2
        int odd = max(
            (zero + k - 1) / k,                  // enough flips to remove zeros
            (len - zero + base - 1) / base       // enough flips to not over-create zeros
        );

        // Make sure odd is actually odd
        odd += ~odd & 1;

        // Case 2: total operations is EVEN
        // parity of total flips = 0
        int even = max(
            (zero + k - 1) / k,                  // enough flips to remove zeros
            (zero + base - 1) / base             // balancing condition
        );

        // Make sure even is actually even
        even += even & 1;

        int res = INT_MAX;

        // If odd total flips matches required parity
        if ((k & 1) == (zero & 1))
            res = min(res, odd);

        // If even total flips matches required parity
        if (~zero & 1)
            res = min(res, even);

        return res == INT_MAX ? -1 : res;
    }
};
// tc = O(n)
// sc = O(1)
// 1 <= k <= s.length
