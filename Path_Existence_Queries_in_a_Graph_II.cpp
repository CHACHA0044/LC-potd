// 3534. Path Existence Queries in a Graph II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.

// You are also given an integer array nums of length n and an integer maxDiff.

// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).

// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.

// Return an array answer, where answer[i] is the result of the ith query.

// Note: The edges between the nodes are unweighted.

 

// Example 1:

// Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]

// Output: [1,1]

// Explanation:

// The resulting graph is:



// Query	Shortest Path	Minimum Distance
// [0, 3]	0 → 3	1
// [2, 4]	2 → 4	1
// Thus, the output is [1, 1].

// Example 2:

// Input: n = 5, nums = [5,3,1,9,10], maxDiff = 2, queries = [[0,1],[0,2],[2,3],[4,3]]

// Output: [1,2,-1,1]

// Explanation:

// The resulting graph is:



// Query	Shortest Path	Minimum Distance
// [0, 1]	0 → 1	1
// [0, 2]	0 → 1 → 2	2
// [2, 3]	None	-1
// [4, 3]	3 → 4	1
// Thus, the output is [1, 2, -1, 1].

// Example 3:

// Input: n = 3, nums = [3,6,1], maxDiff = 1, queries = [[0,0],[0,1],[1,2]]

// Output: [0,-1,-1]

// Explanation:

// There are no edges between any two nodes because:

// Nodes 0 and 1: |nums[0] - nums[1]| = |3 - 6| = 3 > 1
// Nodes 0 and 2: |nums[0] - nums[2]| = |3 - 1| = 2 > 1
// Nodes 1 and 2: |nums[1] - nums[2]| = |6 - 1| = 5 > 1
// Thus, no node can reach any other node, and the output is [0, -1, -1].

 

// Constraints:

// 1 <= n == nums.length <= 105
// 0 <= nums[i] <= 105
// 0 <= maxDiff <= 105
// 1 <= queries.length <= 105
// queries[i] == [ui, vi]
// 0 <= ui, vi < n
class Solution {
public:
    vector<int> pathExistenceQueries(int n,
                                     vector<int>& nums,
                                     int maxDiff,
                                     vector<vector<int>>& queries) {

        // ------------------------------------------------------------
        // STEP 1 : Store every value with its original node index.
        //
        // Since edges depend ONLY on the values (not on indices),
        // sorting the values makes the graph much easier to analyze.
        // ------------------------------------------------------------
        vector<pair<int,int>> ord;

        for (int i = 0; i < n; i++)
            ord.push_back({nums[i], i});

        sort(ord.begin(), ord.end());

        // ------------------------------------------------------------
        // STEP 2 : Find every node's position in the sorted array.
        //
        // Example:
        //
        // nums = [1,8,3,4,2]
        //
        // sorted = [(1,0),(2,4),(3,2),(4,3),(8,1)]
        //
        // pos[0]=0
        // pos[4]=1
        // pos[2]=2
        // pos[3]=3
        // pos[1]=4
        //
        // Later every query is converted into sorted positions.
        // ------------------------------------------------------------
        vector<int> pos(n);

        for (int i = 0; i < n; i++)
            pos[ord[i].second] = i;

        // ------------------------------------------------------------
        // STEP 3 : Build connected components.
        //
        // Observation:
        //
        // If two consecutive sorted values differ by more than
        // maxDiff, NO EDGE can cross that gap.
        //
        // Therefore that gap separates two completely different
        // connected components.
        //
        // Example:
        //
        // values = 1 2 4 9 10
        //
        // maxDiff = 2
        //
        // gaps:
        //
        // 1->2 =1
        // 2->4 =2
        // 4->9 =5  <-- component breaks here
        // 9->10=1
        //
        // Components:
        //
        // {1,2,4}
        // {9,10}
        // ------------------------------------------------------------
        vector<int> comp(n);

        int componentID = 0;
        comp[0] = 0;

        for (int i = 1; i < n; i++) {

            if (ord[i].first - ord[i - 1].first > maxDiff)
                componentID++;

            comp[i] = componentID;
        }

        // ------------------------------------------------------------
        // STEP 4 : Compute farthest node reachable in ONE EDGE.
        //
        // nxt[i] =
        // farthest sorted position that node i can directly connect to.
        //
        // We compute this using the sliding window / two pointers.
        //
        // Example:
        //
        // values = [1,2,3,4,8]
        //
        // maxDiff=3
        //
        // From value 1 we can directly reach
        // 2,3,4
        //
        // so nxt[0]=3
        // ------------------------------------------------------------
        vector<int> nxt(n);

        int right = 0;

        for (int left = 0; left < n; left++) {

            while (right + 1 < n &&
                   ord[right + 1].first - ord[left].first <= maxDiff)
                right++;

            nxt[left] = right;
        }

        // ------------------------------------------------------------
        // STEP 5 : Binary Lifting
        //
        // up[k][i]
        //
        // =
        //
        // position reached after making exactly 2^k greedy jumps.
        //
        // This reduces every query from O(n)
        // to O(log n).
        // ------------------------------------------------------------
        const int LOG = 18;

        vector<vector<int>> up(LOG, vector<int>(n));

        // First level (1 jump)
        for (int i = 0; i < n; i++)
            up[0][i] = nxt[i];

        // Higher levels
        for (int k = 1; k < LOG; k++) {

            for (int i = 0; i < n; i++)
                up[k][i] =
                    up[k-1][ up[k-1][i] ];
        }

        vector<int> answer;

        // ------------------------------------------------------------
        // STEP 6 : Answer every query.
        // ------------------------------------------------------------
        for (auto &q : queries) {

            // Convert original indices into sorted positions.
            int u = pos[q[0]];
            int v = pos[q[1]];

            if (u > v)
                swap(u, v);

            // Same node.
            if (u == v) {
                answer.push_back(0);
                continue;
            }

            // Different connected components.
            // Impossible to travel.
            if (comp[u] != comp[v]) {
                answer.push_back(-1);
                continue;
            }

            int current = u;
            int jumps = 0;

            // --------------------------------------------------------
            // Binary lifting.
            //
            // We try the largest possible jump first.
            //
            // We only jump if we STILL remain before destination.
            //
            // This greedily minimizes total jumps.
            // --------------------------------------------------------
            for (int k = LOG - 1; k >= 0; k--) {

                if (up[k][current] < v) {

                    jumps += (1 << k);
                    current = up[k][current];
                }
            }

            // One last jump reaches destination.
            answer.push_back(jumps + 1);
        }

        return answer;
    }
};

/*
======================================================================
Why the Previous Solution Failed
======================================================================

My previous approach only divided the sorted array into connected
components.

For every query it simply computed

    abs(component(u) - component(v))

or something equivalent.

That logic works for Problem 3532
(Path Existence Queries I)

because that problem ONLY asks

    "Can we reach?"

Connected component information is enough for that.

----------------------------------------------------------------------
But this problem asks something much harder:

"What is the MINIMUM NUMBER OF EDGES?"

Being inside the same connected component DOES NOT mean
the answer is 1.

Example:

values = [1,3,4]

maxDiff = 2

Edges:

1 -- 3 -- 4

There is NO direct edge

1 ----X---- 4

Minimum distance is

1 -> 3 -> 4

Answer = 2

A component-based solution cannot distinguish between

1 edge
2 edges
10 edges

because it only stores connectivity.

======================================================================
Why This Greedy + Binary Lifting Works
======================================================================

Suppose we stand at value X.

Among all neighbors we could visit next,
choosing the FARTEST reachable one can never hurt.

Jumping farther can only reduce the number of edges needed.

So the optimal strategy becomes

Always jump as far as possible.

The problem is that repeating this jump one by one
could still take O(n) time.

Binary lifting precomputes

1 jump
2 jumps
4 jumps
8 jumps
16 jumps
...

allowing us to simulate all greedy jumps in O(log n).

======================================================================

Time Complexity

Sorting               : O(n log n)

Two Pointers          : O(n)

Binary Lifting Build  : O(n log n)

Each Query            : O(log n)

Overall

O((n + q) log n)

======================================================================

Space Complexity

Binary Lifting Table

O(n log n)
*/
======================================================================*
