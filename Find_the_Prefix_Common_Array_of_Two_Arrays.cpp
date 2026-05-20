// 2657. Find the Prefix Common Array of Two Arrays
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given two 0-indexed integer permutations A and B of length n.

// A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B.

// Return the prefix common array of A and B.

// A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly once.

 

// Example 1:

// Input: A = [1,3,2,4], B = [3,1,2,4]
// Output: [0,2,3,4]
// Explanation: At i = 0: no number is common, so C[0] = 0.
// At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
// At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
// At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.
// Example 2:

// Input: A = [2,3,1], B = [3,1,2]
// Output: [0,1,3]
// Explanation: At i = 0: no number is common, so C[0] = 0.
// At i = 1: only 3 is common in A and B, so C[1] = 1.
// At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
 

// Constraints:

// 1 <= A.length == B.length == n <= 50
// 1 <= A[i], B[i] <= n
// It is guaranteed that A and B are both a permutation of n integers.
class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {

        int n = A.size();

        vector<int> ans(n);


        /*
        visited[x] tells whether number x
        has already appeared before.

        Since values are from 1 to n,
        size = n + 1.
        */
        vector<int> visited(n + 1, 0);


        /*
        count = current number of common elements
        found in both prefixes.
        */
        int count = 0;


        /*
        Traverse both arrays together.
        */
        for (int i = 0; i < n; i++) {

            /*
            Process A[i]

            If already seen before,
            then this number has now appeared
            in both arrays.
            */
            visited[A[i]]++;

            if (visited[A[i]] == 2) {
                count++;
            }


            /*
            Process B[i]

            Same logic for B[i].
            */
            visited[B[i]]++;

            if (visited[B[i]] == 2) {
                count++;
            }


            /*
            Store prefix common count
            for current index.
            */
            ans[i] = count;
        }


        return ans;
    }
};
// Time Complexity
// O(n)
// Space Complexity
// O(n)
