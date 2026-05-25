// 1871. Jump Game VII
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a 0-indexed binary string s and two integers minJump and maxJump. In the beginning, you are standing at index 0, which is equal to '0'. You can move from index i to index j if the following conditions are fulfilled:

// i + minJump <= j <= min(i + maxJump, s.length - 1), and
// s[j] == '0'.
// Return true if you can reach index s.length - 1 in s, or false otherwise.

 

// Example 1:

// Input: s = "011010", minJump = 2, maxJump = 3
// Output: true
// Explanation:
// In the first step, move from index 0 to index 3. 
// In the second step, move from index 3 to index 5.
// Example 2:

// Input: s = "01101110", minJump = 2, maxJump = 3
// Output: false
 

// Constraints:

// 2 <= s.length <= 105
// s[i] is either '0' or '1'.
// s[0] == '0'
// 1 <= minJump <= maxJump < s.length
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {

        int n = s.size();

        
        /*
        dp[i] = true if index i can be reached.
        */
        vector<bool> dp(n, false);

        dp[0] = true;


        /*
        reachableCount stores the number of
        reachable indices currently inside the window:

        [i - maxJump, i - minJump]
        */
        int reachableCount = 0;


        for (int i = 1; i < n; i++) {

            /*
            -------------------------------------------------
            Add new index entering the window
            -------------------------------------------------

            When processing index i,

            index:
                i - minJump

            becomes eligible as a jump source.
            */
            if (i - minJump >= 0) {

                reachableCount += dp[i - minJump];
            }


            /*
            -------------------------------------------------
            Remove index leaving the window
            -------------------------------------------------

            index:
                i - maxJump - 1

            is no longer a valid jump source.
            */
            if (i - maxJump - 1 >= 0) {

                reachableCount -= dp[i - maxJump - 1];
            }


            /*
            -------------------------------------------------
            Current index is reachable if:

            1. Character is '0'
            2. At least one reachable index exists
               inside the valid jump window
            -------------------------------------------------
            */
            if (s[i] == '0' && reachableCount > 0) {

                dp[i] = true;
            }
        }


        /*
        Answer: can we reach last index?
        */
        return dp[n - 1];
    }
};
// Example
// s = "011010"
// minJump = 2
// maxJump = 3
// Reachable indices:
// 0 → 3 → 5
// Result:
// true
// Time Complexity
// O(n)
// Each index enters and leaves the sliding window once.
// Space Complexity
// O(n)
// For the DP array.
