// 3559. Number of Ways to Assign Edge Weights II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.

// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.

// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.

// You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.

// Return an array answer, where answer[i] is the number of valid assignments for queries[i].

// Since the answer may be large, apply modulo 109 + 7 to each answer[i].

// Note: For each query, disregard all edges not in the path between node ui and vi.

 

// Example 1:



// Input: edges = [[1,2]], queries = [[1,1],[1,2]]

// Output: [0,1]

// Explanation:

// Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
// Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// Example 2:



// Input: edges = [[1,2],[1,3],[3,4],[3,5]], queries = [[1,4],[3,4],[2,5]]

// Output: [2,1,4]

// Explanation:

// Query [1,4]: The path from Node 1 to Node 4 consists of two edges (1 → 3 and 3 → 4). Assigning weights (1,2) or (2,1) results in an odd cost. Thus, the number of valid assignments is 2.
// Query [3,4]: The path from Node 3 to Node 4 consists of one edge (3 → 4). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
// Query [2,5]: The path from Node 2 to Node 5 consists of three edges (2 → 1, 1 → 3, and 3 → 5). Assigning (1,2,2), (2,1,2), (2,2,1), or (1,1,1) makes the cost odd. Thus, the number of valid assignments is 4.
 

// Constraints:

// 2 <= n <= 105
// edges.length == n - 1
// edges[i] == [ui, vi]
// 1 <= queries.length <= 105
// queries[i] == [ui, vi]
// 1 <= ui, vi <= n
// edges represents a valid tree.
class Solution {
public:
    static constexpr long long MOD = 1e9 + 7;

    /*
    parent[node]
        Direct parent of node in rooted tree.

    depth[node]
        Distance (in edges) from root node 1.

    up[node][j]
        2^j-th ancestor of node.

    Used for Binary Lifting LCA queries.
    */
    vector<int> parent, depth;
    vector<vector<int>> up;


    /*
    Fast Modular Exponentiation

    Computes:
        base^exp % MOD

    in O(log exp) time.
    */
    long long modPow(long long base, long long exp) {

        long long result = 1;

        while (exp > 0) {

            /*
            If current bit is set,
            multiply current power into answer.
            */
            if (exp & 1) {
                result = (result * base) % MOD;
            }

            /*
            Move to next power.
            */
            base = (base * base) % MOD;

            exp >>= 1;
        }

        return result;
    }


    /*
    Lowest Common Ancestor using Binary Lifting.

    Returns the deepest node that is
    an ancestor of both u and v.
    */
    int lca(int u, int v) {

        /*
        Ensure u is the deeper node.
        */
        if (depth[u] < depth[v]) {
            swap(u, v);
        }


        /*
        Bring u to the same depth as v.
        */
        int depthDifference = depth[u] - depth[v];

        for (int bit = 0; bit < up[0].size(); bit++) {

            if (depthDifference & (1 << bit)) {
                u = up[u][bit];
            }
        }


        /*
        If both nodes become equal,
        that node itself is the LCA.
        */
        if (u == v) {
            return u;
        }


        /*
        Lift both nodes upward together.

        Start from largest jump and move down.

        Whenever ancestors differ,
        move both nodes upward.
        */
        for (int bit = up[0].size() - 1; bit >= 0; bit--) {

            if (up[u][bit] != up[v][bit]) {

                u = up[u][bit];
                v = up[v][bit];
            }
        }


        /*
        Their parents are now equal
        and represent the LCA.
        */
        return parent[u];
    }


    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {

        int n = edges.size() + 1;


        /*
        ----------------------------------------------------
        Build adjacency list representation of tree.
        ----------------------------------------------------
        */
        vector<vector<int>> adj(n + 1);

        for (auto &edge : edges) {

            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }


        /*
        Number of levels needed for
        Binary Lifting table.
        */
        int LOG = 17;

        while ((1 << LOG) <= n) {
            LOG++;
        }


        parent.assign(n + 1, 0);
        depth.assign(n + 1, 0);

        up.assign(n + 1, vector<int>(LOG));


        /*
        ----------------------------------------------------
        BFS from root node 1

        Computes:
            parent[node]
            depth[node]
        ----------------------------------------------------
        */
        queue<int> bfsQueue;

        bfsQueue.push(1);

        parent[1] = 1;

        while (!bfsQueue.empty()) {

            int currentNode = bfsQueue.front();
            bfsQueue.pop();

            for (int nextNode : adj[currentNode]) {

                /*
                Skip edge back to parent.
                */
                if (nextNode == parent[currentNode]) {
                    continue;
                }

                parent[nextNode] = currentNode;

                depth[nextNode] =
                    depth[currentNode] + 1;

                bfsQueue.push(nextNode);
            }
        }


        /*
        ----------------------------------------------------
        Build Binary Lifting table.

        up[node][0]
            direct parent

        up[node][1]
            2^1 ancestor

        up[node][2]
            2^2 ancestor

        and so on.
        ----------------------------------------------------
        */
        for (int node = 1; node <= n; node++) {
            up[node][0] = parent[node];
        }

        for (int jump = 1; jump < LOG; jump++) {

            for (int node = 1; node <= n; node++) {

                up[node][jump] =
                    up[up[node][jump - 1]][jump - 1];
            }
        }


        vector<int> answer;


        /*
        ====================================================
        PROCESS EACH QUERY
        ====================================================
        */
        for (auto &query : queries) {

            int u = query[0];
            int v = query[1];


            /*
            Find Lowest Common Ancestor.
            */
            int commonAncestor = lca(u, v);


            /*
            Path length (number of edges)
            between u and v.

            distance(u,v)
            =
            depth[u]
            +
            depth[v]
            -
            2 * depth[lca]
            */
            long long pathEdges =
                depth[u]
                + depth[v]
                - 2LL * depth[commonAncestor];


            /*
            ------------------------------------------------
            Special case:

            Same node.

            No edges exist in path.

            Cost is always 0 (even).

            Therefore no assignment can
            make the cost odd.
            ------------------------------------------------
            */
            if (pathEdges == 0) {

                answer.push_back(0);
            }
            else {

                /*
                ------------------------------------------------
                Key Observation

                Every edge can be assigned:

                    1 (odd)
                    2 (even)

                Let path length = d.

                Total assignments:
                    2^d

                Path cost is odd iff
                the number of edges assigned 1
                is odd.

                Among all binary assignments:

                    Half produce odd parity
                    Half produce even parity

                Therefore:

                    valid assignments
                    =
                    2^d / 2
                    =
                    2^(d-1)
                ------------------------------------------------
                */
                answer.push_back(
                    modPow(2, pathEdges - 1)
                );
            }
        }

        return answer;
    }
};

/*
Time Complexity:

Building adjacency list:
    O(n)

BFS for parent/depth:
    O(n)

Building Binary Lifting table:
    O(n log n)

Each query:
    O(log n)

Total:
    O(n log n + q log n)

------------------------------------------------

Space Complexity:

Adjacency List:
    O(n)

Parent + Depth:
    O(n)

Binary Lifting Table:
    O(n log n)

Total:
    O(n log n)
*/
