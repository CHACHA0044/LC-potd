// 1340. Jump Game V
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// Given an array of integers arr and an integer d. In one step you can jump from index i to index:

// i + x where: i + x < arr.length and  0 < x <= d.
// i - x where: i - x >= 0 and  0 < x <= d.
// In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).

// You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.

// Notice that you can not jump outside of the array at any time.

 

// Example 1:


// Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
// Output: 4
// Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
// Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.
// Similarly You cannot jump from index 3 to index 2 or index 1.
// Example 2:

// Input: arr = [3,3,3,3,3], d = 3
// Output: 1
// Explanation: You can start at any index. You always cannot jump to any index.
// Example 3:

// Input: arr = [7,6,5,4,3,2,1], d = 1
// Output: 7
// Explanation: Start at index 0. You can visit all the indicies. 
 

// Constraints:

// 1 <= arr.length <= 1000
// 1 <= arr[i] <= 105
// 1 <= d <= arr.length
class Solution {
public:

    /*
    dp[i] = maximum number of indices that can be visited
    starting from index i.

    We use memoization so that each index is solved only once.
    */
    vector<int> dp;


    int dfs(int i, vector<int>& arr, int d) {

        /*
        If answer for this index is already computed,
        return it directly.
        */
        if (dp[i] != -1)
            return dp[i];


        /*
        Every index can at least visit itself.

        So initial answer = 1.
        */
        dp[i] = 1;

        int n = arr.size();


        /*
        =====================================================
        Explore LEFT side
        =====================================================

        We can jump at most d positions to the left.

        Important:
        - arr[j] must be smaller than arr[i]
        - every element between i and j must also be
          smaller than arr[i]

        If we encounter an element >= arr[i],
        it blocks the path completely and we must stop.
        */
        for (int j = i - 1; j >= max(0, i - d); j--) {

            /*
            Found a blocking element.

            We cannot jump to this index or
            any index beyond it in this direction.
            */
            if (arr[j] >= arr[i])
                break;


            /*
            Jump from i -> j

            Total visited indices:

            current index
            + best answer starting from j
            */
            dp[i] = max(
                dp[i],
                1 + dfs(j, arr, d)
            );
        }


        /*
        =====================================================
        Explore RIGHT side
        =====================================================

        Same logic as left side.
        */
        for (int j = i + 1; j <= min(n - 1, i + d); j++) {

            /*
            Blocking element encountered.

            Cannot continue further right.
            */
            if (arr[j] >= arr[i])
                break;


            /*
            Try jumping to index j and
            update the best possible answer.
            */
            dp[i] = max(
                dp[i],
                1 + dfs(j, arr, d)
            );
        }


        /*
        Store and return the best answer
        for starting index i.
        */
        return dp[i];
    }


    int maxJumps(vector<int>& arr, int d) {

        int n = arr.size();

        /*
        -1 means "not computed yet"
        */
        dp.assign(n, -1);

        int answer = 1;


        /*
        Any index can be chosen as the starting point.

        Compute the maximum reachable indices
        starting from every index.
        */
        for (int i = 0; i < n; i++) {

            answer = max(
                answer,
                dfs(i, arr, d)
            );
        }


        return answer;
    }
};
// Time Complexity
// Each index is solved once.
// For every index we scan at most:
// d left + d right
// So:
// O(n * d)
// Space Complexity
// Memoization array:
// O(n)
// Recursion stack:
// O(n)
// Overall:
// O(n)
