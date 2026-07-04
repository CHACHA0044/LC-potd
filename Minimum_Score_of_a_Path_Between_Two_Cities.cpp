// 2492. Minimum Score of a Path Between Two Cities
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily connected.

// The score of a path between two cities is defined as the minimum distance of a road in this path.

// Return the minimum possible score of a path between cities 1 and n.

// Note:

// A path is a sequence of roads between two cities.
// It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
// The test cases are generated such that there is at least one path between 1 and n.
 

// Example 1:


// Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
// Output: 5
// Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
// It can be shown that no other path has less score.
// Example 2:


// Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
// Output: 2
// Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4. The score of this path is min(2,2,4,7) = 2.
 

// Constraints:

// 2 <= n <= 105
// 1 <= roads.length <= 105
// roads[i].length == 3
// 1 <= ai, bi <= n
// ai != bi
// 1 <= distancei <= 104
// There are no repeated edges.
// There is at least one path between 1 and n.
class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {

        // Build the adjacency list.
        // Each entry stores:
        // {neighbour city, road distance}
        vector<vector<pair<int,int>>> adj(n + 1);

        for (auto &r : roads) {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        // Visited array to avoid processing
        // the same city multiple times.
        vector<int> vis(n + 1, 0);

        queue<int> q;

        // Start BFS from city 1.
        q.push(1);
        vis[1] = 1;

        // Stores the minimum road distance
        // seen in the connected component
        // containing city 1.
        int ans = INT_MAX;

        while (!q.empty()) {

            int u = q.front();
            q.pop();

            // Explore all neighbouring roads.
            for (auto &[v, d] : adj[u]) {

                // Since we are allowed to revisit
                // cities and roads, the answer is simply
                // the smallest edge present in the entire
                // connected component containing city 1.
                ans = min(ans, d);

                // Visit the neighbouring city.
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
            }
        }

        return ans;
    }
};

/*
Time Complexity: O(n + roads.size())

Space Complexity: O(n + roads.size())
*/
