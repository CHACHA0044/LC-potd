// 2685. Count the Number of Complete Components
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.

// Return the number of complete connected components of the graph.

// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.

// A connected component is said to be complete if there exists an edge between every pair of its vertices.

 

// Example 1:



// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
// Example 2:



// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4],[3,5]]
// Output: 1
// Explanation: The component containing vertices 0, 1, and 2 is complete since there is an edge between every pair of two vertices. On the other hand, the component containing vertices 3, 4, and 5 is not complete since there is no edge between vertices 4 and 5. Thus, the number of complete components in this graph is 1.
 

// Constraints:

// 1 <= n <= 50
// 0 <= edges.length <= n * (n - 1) / 2
// edges[i].length == 2
// 0 <= ai, bi <= n - 1
// ai != bi
// There are no repeated edges.
class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        // ------------------------------------------------------------
        // Step 1: Build the adjacency list of the graph.
        //
        // Since the graph is undirected, every edge is stored
        // in both directions.
        // ------------------------------------------------------------
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Keeps track of which vertices have already been visited.
        vector<bool> vis(n, false);

        // Stores the number of complete connected components.
        int ans = 0;

        // ------------------------------------------------------------
        // Step 2: Traverse every connected component using BFS.
        //
        // Every unvisited node starts a new connected component.
        // ------------------------------------------------------------
        for (int i = 0; i < n; i++) {

            if (vis[i])
                continue;

            queue<int> q;
            q.push(i);
            vis[i] = true;

            // Stores all vertices belonging to the current component.
            vector<int> nodes;

            while (!q.empty()) {

                int u = q.front();
                q.pop();

                nodes.push_back(u);

                // Visit all adjacent vertices.
                for (int v : adj[u]) {

                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }

            // --------------------------------------------------------
            // Step 3: Check whether this component is complete.
            //
            // Suppose the component contains k vertices.
            //
            // In a complete graph:
            //
            // Every vertex must be connected to
            // every other vertex.
            //
            // Therefore,
            //
            // degree = k - 1
            //
            // for every vertex.
            // --------------------------------------------------------
            int componentSize = nodes.size();

            bool complete = true;

            for (int node : nodes) {

                // If any node does not have exactly
                // (componentSize - 1) neighbours,
                // this component cannot be complete.
                if (adj[node].size() != componentSize - 1) {
                    complete = false;
                    break;
                }
            }

            // Count this connected component if it is complete.
            if (complete)
                ans++;
        }

        return ans;
    }
};
// Complexity Analysis
// Time Complexity: O(V + E)
// Building adjacency list: O(E)
// BFS over all vertices: O(V + E)
// Degree verification: O(V)
// Space Complexity: O(V + E)
// Adjacency list
// Visited array
// BFS queue
