// 3558. Number of Ways to Assign Edge Weights I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.

// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.

// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.

// Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.

// Since the answer may be large, return it modulo 109 + 7.

// Note: Ignore all edges not in the path from node 1 to x.

 

// Example 1:



// Input: edges = [[1,2]]

// Output: 1

// Explanation:

// The path from Node 1 to Node 2 consists of one edge (1 → 2).
// Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// Example 2:



// Input: edges = [[1,2],[1,3],[3,4],[3,5]]

// Output: 2

// Explanation:

// The maximum depth is 2, with nodes 4 and 5 at the same depth. Either node can be selected for processing.
// For example, the path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4).
// Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
 

// Constraints:

// 2 <= n <= 105
// edges.length == n - 1
// edges[i] == [ui, vi]
// 1 <= ui, vi <= n
// edges represents a valid tree.
class Solution {
public:
    static constexpr long long MOD = 1e9 + 7;

    /*
    Fast Binary Exponentiation

    Computes:
        base^exp % MOD

    in O(log exp) time.
    */
    long long modPow(long long base, long long exp) {

        long long res = 1;

        while (exp > 0) {

            /*
            If current bit is set,
            include current base in answer.
            */
            if (exp & 1) {
                res = (res * base) % MOD;
            }

            /*
            Move to next power.
            */
            base = (base * base) % MOD;

            exp >>= 1;
        }

        return res;
    }

    int assignEdgeWeights(vector<vector<int>>& edges) {

        int n = edges.size() + 1;

        /*
        Build adjacency list representation
        of the tree.
        */
        vector<vector<int>> adj(n + 1);

        for (auto &e : edges) {

            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        /*
        ----------------------------------------------------
        BFS from root node 1 to compute depth
        of every node.

        depth[node] =
        number of edges from root to node.
        ----------------------------------------------------
        */
        queue<int> q;

        vector<int> depth(n + 1, -1);

        q.push(1);

        depth[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            /*
            Keep track of deepest level reached.
            */
            maxDepth = max(maxDepth, depth[node]);

            for (int nei : adj[node]) {

                /*
                Already visited.
                */
                if (depth[nei] != -1) {
                    continue;
                }

                depth[nei] = depth[node] + 1;

                q.push(nei);
            }
        }

        /*
        ====================================================
        KEY OBSERVATION
        ====================================================

        We can choose ANY node at maximum depth.

        Let:

            d = maximum depth

        Then the path from root to that node
        contains exactly d edges.

        We completely ignore all other edges
        as stated in the problem.

        ----------------------------------------------------

        Each edge can receive:

            weight = 1
            weight = 2

        Therefore each edge has 2 choices.

        For d edges:

            Total assignments = 2^d

        ----------------------------------------------------

        We need path cost to be ODD.

        Observe parity only:

            1 -> odd
            2 -> even

        Sum is odd iff the count of odd
        contributions (weight 1 edges)
        is odd.

        ----------------------------------------------------

        Among all binary assignments of d edges:

            2^d assignments total

        Exactly half produce an odd sum
        and half produce an even sum.

        Therefore:

            valid assignments

            = 2^d / 2

            = 2^(d - 1)

        ----------------------------------------------------

        Example:

        d = 3

        Total assignments = 8

        Odd sums:
            111
            122
            212
            221

        Count = 4 = 2^(3-1)

        ====================================================
        */

        return modPow(2, maxDepth - 1);
    }
};

/*
Time Complexity:
O(n)

- Building adjacency list: O(n)
- BFS traversal: O(n)
- Fast exponentiation: O(log n)

Overall: O(n)

------------------------------------------------

Space Complexity:
O(n)

- Adjacency list: O(n)
- Queue: O(n)
- Depth array: O(n)
*/
