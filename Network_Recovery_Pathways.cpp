// 3620. Network Recovery Pathways
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given a directed acyclic graph of n nodes numbered from 0 to n − 1. This is represented by a 2D array edges of length m, where edges[i] = [ui, vi, costi] indicates a one‑way communication from node ui to node vi with a recovery cost of costi.

// Some nodes may be offline. You are given a boolean array online where online[i] = true means node i is online. Nodes 0 and n − 1 are always online.

// A path from 0 to n − 1 is valid if:

// All intermediate nodes on the path are online.
// The total recovery cost of all edges on the path does not exceed k.
// For each valid path, define its score as the minimum edge‑cost along that path.

// Return the maximum path score (i.e., the largest minimum-edge cost) among all valid paths. If no valid path exists, return -1.

 

// Example 1:

// Input: edges = [[0,1,5],[1,3,10],[0,2,3],[2,3,4]], online = [true,true,true,true], k = 10

// Output: 3

// Explanation:



// The graph has two possible routes from node 0 to node 3:

// Path 0 → 1 → 3

// Total cost = 5 + 10 = 15, which exceeds k (15 > 10), so this path is invalid.

// Path 0 → 2 → 3

// Total cost = 3 + 4 = 7 <= k, so this path is valid.

// The minimum edge‐cost along this path is min(3, 4) = 3.

// There are no other valid paths. Hence, the maximum among all valid path‐scores is 3.

// Example 2:

// Input: edges = [[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]], online = [true,true,true,false,true], k = 12

// Output: 6

// Explanation:



// Node 3 is offline, so any path passing through 3 is invalid.

// Consider the remaining routes from 0 to 4:

// Path 0 → 1 → 4

// Total cost = 7 + 5 = 12 <= k, so this path is valid.

// The minimum edge‐cost along this path is min(7, 5) = 5.

// Path 0 → 2 → 3 → 4

// Node 3 is offline, so this path is invalid regardless of cost.

// Path 0 → 2 → 4

// Total cost = 6 + 6 = 12 <= k, so this path is valid.

// The minimum edge‐cost along this path is min(6, 6) = 6.

// Among the two valid paths, their scores are 5 and 6. Therefore, the answer is 6.

 

// Constraints:

// n == online.length
// 2 <= n <= 5 * 104
// 0 <= m == edges.length <= min(105, n * (n - 1) / 2)
// edges[i] = [ui, vi, costi]
// 0 <= ui, vi < n
// ui != vi
// 0 <= costi <= 109
// 0 <= k <= 5 * 1013
// online[i] is either true or false, and both online[0] and online[n − 1] are true.
// The given graph is a directed acyclic graph.
class Solution {
public:
    using ll = long long;

    int findMaxPathScore(vector<vector<int>>& edges,
                         vector<bool>& online,
                         long long k) {

        // Number of nodes.
        // The problem does not pass 'n' separately,
        // so we get it from the size of the online array.
        int n = online.size();

        // Adjacency list:
        // adj[u] = {v, edgeCost}
        vector<vector<pair<int,int>>> adj(n);

        // Used for topological sorting.
        vector<int> indegree(n, 0);

        // Maximum edge weight present in the graph.
        // This becomes the upper bound for binary search.
        int maxEdge = 0;

        // Build the graph.
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];

            adj[u].push_back({v, w});
            indegree[v]++;

            maxEdge = max(maxEdge, w);
        }

        // -------------------------------------------------------
        // Topological Sort
        // -------------------------------------------------------
        // Since the graph is guaranteed to be a DAG,
        // we process vertices in topological order.
        // This lets us perform shortest path relaxation
        // in O(n + m) time.
        vector<int> topo;
        queue<int> q;

        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {

            int u = q.front();
            q.pop();

            topo.push_back(u);

            for (auto &[v, w] : adj[u]) {
                indegree[v]--;

                if (indegree[v] == 0)
                    q.push(v);
            }
        }

        // -------------------------------------------------------
        // Check Function
        // -------------------------------------------------------
        // Returns true if there exists a path from
        // node 0 to node n-1 such that:
        //
        // 1. Every edge has weight >= limit.
        // 2. Every intermediate node is online.
        // 3. Total path cost <= k.
        //
        auto check = [&](int limit) {

            const ll INF = 4e18;

            // dist[i] = minimum total cost required
            // to reach node i.
            vector<ll> dist(n, INF);

            dist[0] = 0;

            // Traverse nodes in topological order.
            for (int u : topo) {

                // Skip unreachable nodes.
                if (dist[u] == INF)
                    continue;

                // Intermediate offline nodes
                // cannot be used.
                // Source and destination are always online,
                // but this check makes the code safer.
                if (u != 0 && u != n - 1 && !online[u])
                    continue;

                // Relax outgoing edges.
                for (auto &[v, w] : adj[u]) {

                    // We are searching for paths whose
                    // minimum edge value is at least 'limit'.
                    // So ignore smaller edges.
                    if (w < limit)
                        continue;

                    // Intermediate offline nodes
                    // cannot appear in the path.
                    if (v != n - 1 && !online[v])
                        continue;

                    // Update shortest cost.
                    dist[v] = min(dist[v], dist[u] + (ll)w);
                }
            }

            // A valid path exists only if
            // its total cost is within k.
            return dist[n - 1] <= k;
        };

        // -------------------------------------------------------
        // Binary Search
        // -------------------------------------------------------
        // The answer is the maximum possible minimum edge.
        //
        // If a path exists for X,
        // then it also exists for every value <= X.
        //
        // Hence the answer is monotonic,
        // making binary search applicable.
        int low = 0;
        int high = maxEdge;

        int answer = -1;

        while (low <= high) {

            int mid = low + (high - low) / 2;

            if (check(mid)) {

                // Try to increase the minimum edge value.
                answer = mid;
                low = mid + 1;

            } else {

                // Current value is too large.
                high = mid - 1;
            }
        }

        return answer;
    }
};

/*
Time Complexity:
Topological Sort : O(n + m)

Each check()      : O(n + m)

Binary Search     : O(log(MaxEdgeWeight))

Overall:
O((n + m) * log(MaxEdgeWeight))

Space Complexity:
O(n + m)
*/
