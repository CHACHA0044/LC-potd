// 3532. Path Existence Queries in a Graph I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.

// You are also given an integer array nums of length n sorted in non-decreasing order, and an integer maxDiff.

// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).

// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], determine whether there exists a path between nodes ui and vi.

// Return a boolean array answer, where answer[i] is true if there exists a path between ui and vi in the ith query and false otherwise.

 

// Example 1:

// Input: n = 2, nums = [1,3], maxDiff = 1, queries = [[0,0],[0,1]]

// Output: [true,false]

// Explanation:

// Query [0,0]: Node 0 has a trivial path to itself.
// Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |1 - 3| = 2, which is greater than maxDiff.
// Thus, the final answer after processing all the queries is [true, false].
// Example 2:

// Input: n = 4, nums = [2,5,6,8], maxDiff = 2, queries = [[0,1],[0,2],[1,3],[2,3]]

// Output: [false,false,true,true]

// Explanation:

// The resulting graph is:



// Query [0,1]: There is no edge between Node 0 and Node 1 because |nums[0] - nums[1]| = |2 - 5| = 3, which is greater than maxDiff.
// Query [0,2]: There is no edge between Node 0 and Node 2 because |nums[0] - nums[2]| = |2 - 6| = 4, which is greater than maxDiff.
// Query [1,3]: There is a path between Node 1 and Node 3 through Node 2 since |nums[1] - nums[2]| = |5 - 6| = 1 and |nums[2] - nums[3]| = |6 - 8| = 2, both of which are within maxDiff.
// Query [2,3]: There is an edge between Node 2 and Node 3 because |nums[2] - nums[3]| = |6 - 8| = 2, which is equal to maxDiff.
// Thus, the final answer after processing all the queries is [false, false, true, true].
 

// Constraints:

// 1 <= n == nums.length <= 105
// 0 <= nums[i] <= 105
// nums is sorted in non-decreasing order.
// 0 <= maxDiff <= 105
// 1 <= queries.length <= 105
// queries[i] == [ui, vi]
// 0 <= ui, vi < n
class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff,
                                      vector<vector<int>>& queries) {

        // ------------------------------------------------------------
        // Since nums is already sorted, we only need to check
        // consecutive elements.
        //
        // If the difference between two consecutive numbers is
        // greater than maxDiff, then no edge can connect across
        // this gap.
        //
        // Example:
        //
        // nums = [2,5,6,8]
        // maxDiff = 2
        //
        // Differences:
        // 5-2 = 3  -> Break
        // 6-5 = 1  -> Connected
        // 8-6 = 2  -> Connected
        //
        // Components become:
        //
        // [2] | [5,6,8]
        //
        // component ids:
        //
        // [0,1,1,1]
        // ------------------------------------------------------------

        vector<int> component(n);

        // Current connected component id.
        int id = 0;

        component[0] = 0;

        // ------------------------------------------------------------
        // Build connected components.
        //
        // Whenever the gap between consecutive numbers exceeds
        // maxDiff, we start a new component.
        // ------------------------------------------------------------
        for (int i = 1; i < n; i++) {

            // Gap too large.
            // No path can ever cross this boundary.
            if (nums[i] - nums[i - 1] > maxDiff)
                id++;

            component[i] = id;
        }

        vector<bool> answer;

        // ------------------------------------------------------------
        // For every query:
        //
        // Two nodes have a path between them
        // iff they belong to the same connected component.
        // ------------------------------------------------------------
        for (auto &query : queries) {

            int u = query[0];
            int v = query[1];

            answer.push_back(component[u] == component[v]);
        }

        return answer;
    }
};

/*
------------------------------------------------------------
Why does checking only consecutive elements work?
------------------------------------------------------------

Suppose

nums = [1,4,7]

maxDiff = 2

Differences:

4-1 = 3
7-4 = 3

There is no edge between consecutive numbers.

Since the array is sorted,

every later element is even farther away.

Therefore there is NO way to jump across this gap.

------------------------------------------------------------

Example

nums = [1,2,4,5,7]

maxDiff = 1

Edges:

1--2

4--5

5--7 (No)

Components:

[1,2]   [4,5]   [7]

IDs:

0 0 1 1 2

Query:
1 -> 2

Different IDs

Answer = false

------------------------------------------------------------

Edge Cases
------------------------------------------------------------

1. n = 1

Only one node exists.

Every query [0,0] is true.

------------------------------------------------------------

2. maxDiff = 0

Only equal values are connected.

Example:

[1,1,1,2,2,3]

Components:

[1,1,1] [2,2] [3]

------------------------------------------------------------

3. All elements connected

nums = [1,2,3,4]

maxDiff = 10

Every consecutive difference <= maxDiff

Only one component.

Every query is true.

------------------------------------------------------------

4. Every element isolated

nums = [1,5,10]

maxDiff = 1

Every gap > maxDiff

Each node forms its own component.

------------------------------------------------------------

Time Complexity
------------------------------------------------------------

Building components : O(n)

Answering queries : O(q)

Total : O(n + q)

------------------------------------------------------------

Space Complexity
------------------------------------------------------------

O(n)

for the component array.
*/
