// 1306. Jump Game III
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given an array of non-negative integers arr, you are initially positioned at start index of the array. When you are at index i, you can jump to i + arr[i] or i - arr[i], check if you can reach any index with value 0.

// Notice that you can not jump outside of the array at any time.

 

// Example 1:

// Input: arr = [4,2,3,0,3,1,2], start = 5
// Output: true
// Explanation: 
// All possible ways to reach at index 3 with value 0 are: 
// index 5 -> index 4 -> index 1 -> index 3 
// index 5 -> index 6 -> index 4 -> index 1 -> index 3 
// Example 2:

// Input: arr = [4,2,3,0,3,1,2], start = 0
// Output: true 
// Explanation: 
// One possible way to reach at index 3 with value 0 is: 
// index 0 -> index 4 -> index 1 -> index 3
// Example 3:

// Input: arr = [3,0,2,1,2], start = 2
// Output: false
// Explanation: There is no way to reach at index 1 with value 0.
 

// Constraints:

// 1 <= arr.length <= 5 * 104
// 0 <= arr[i] < arr.length
// 0 <= start < arr.length
class Solution {
public:

    bool canReach(vector<int>& arr, int start) {

        int n = arr.size();


        /*
        =====================================================
        BFS Traversal
        =====================================================

        From index i,
        we can jump to:

            i + arr[i]
            i - arr[i]

        We need to check whether
        any reachable index has value 0.
        */


        queue<int> q;

        /*
        visited[i] prevents infinite loops
        */
        vector<bool> visited(n, false);


        /*
        Start BFS from given index
        */
        q.push(start);
        visited[start] = true;


        while (!q.empty()) {

            int i = q.front();
            q.pop();


            /*
            If current index has value 0,
            answer is true.
            */
            if (arr[i] == 0)
                return true;


            /*
            Next possible jumps
            */
            int forward = i + arr[i];
            int backward = i - arr[i];


            /*
            Try forward jump
            */
            if (forward < n && !visited[forward]) {

                visited[forward] = true;

                q.push(forward);
            }


            /*
            Try backward jump
            */
            if (backward >= 0 && !visited[backward]) {

                visited[backward] = true;

                q.push(backward);
            }
        }


        /*
        No reachable index contains 0
        */
        return false;
    }
};
// Time Complexity
// Each index is visited at most once:
// O(n)
// Space Complexity
// Visited array + queue:
// O(n)
