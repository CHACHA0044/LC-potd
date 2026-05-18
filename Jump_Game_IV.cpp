// 1345. Jump Game IV
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// Given an array of integers arr, you are initially positioned at the first index of the array.

// In one step you can jump from index i to index:

// i + 1 where: i + 1 < arr.length.
// i - 1 where: i - 1 >= 0.
// j where: arr[i] == arr[j] and i != j.
// Return the minimum number of steps to reach the last index of the array.

// Notice that you can not jump outside of the array at any time.

 

// Example 1:

// Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
// Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
// Example 2:

// Input: arr = [7]
// Output: 0
// Explanation: Start index is the last index. You do not need to jump.
// Example 3:

// Input: arr = [7,6,9,6,9,6,9,7]
// Output: 1
// Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
 

// Constraints:

// 1 <= arr.length <= 5 * 104
// -108 <= arr[i] <= 108
class Solution {
public:
    int minJumps(vector<int>& arr) {

        int n = arr.size();

        
        /*
        Already at last index
        */
        if (n == 1)
            return 0;


        /*
        =====================================================
        Store indices having same value
        =====================================================

        Example:
        arr = [7,6,9,6]

        mp:
        6 -> [1,3]
        7 -> [0]
        9 -> [2]
        */
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }


        /*
        =====================================================
        BFS for shortest path
        =====================================================

        From index i we can go to:
        - i+1
        - i-1
        - all indices having same value
        */
        queue<int> q;

        vector<bool> visited(n, false);

        q.push(0);
        visited[0] = true;


        int steps = 0;


        while (!q.empty()) {

            int sz = q.size();


            /*
            Process one BFS level
            */
            while (sz--) {

                int i = q.front();
                q.pop();


                /*
                Reached destination
                */
                if (i == n - 1)
                    return steps;


                /*
                =================================================
                Jump to i+1
                =================================================
                */
                if (i + 1 < n && !visited[i + 1]) {

                    visited[i + 1] = true;

                    q.push(i + 1);
                }


                /*
                =================================================
                Jump to i-1
                =================================================
                */
                if (i - 1 >= 0 && !visited[i - 1]) {

                    visited[i - 1] = true;

                    q.push(i - 1);
                }


                /*
                =================================================
                Jump to all same-value indices
                =================================================
                */
                for (int next : mp[arr[i]]) {

                    if (!visited[next]) {

                        visited[next] = true;

                        q.push(next);
                    }
                }


                /*
                IMPORTANT OPTIMIZATION

                After processing all indices
                with value arr[i],

                clear the vector.

                Otherwise same-value traversal
                repeats many times and causes TLE.
                */
                mp[arr[i]].clear();
            }


            /*
            One jump completed
            */
            steps++;
        }


        return -1;
    }
};
// Time Complexity
// Building hashmap:
// O(n)
// BFS traversal:
// O(n)
// Each same-value list is processed once due to clearing.
// Overall:
// O(n)
// Space Complexity
// Hashmap + queue + visited:
// O(n)
