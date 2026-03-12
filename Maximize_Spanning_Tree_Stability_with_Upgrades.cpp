// 3600. Maximize Spanning Tree Stability with Upgrades
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer n, representing n nodes numbered from 0 to n - 1 and a list of edges, where edges[i] = [ui, vi, si, musti]:

// ui and vi indicates an undirected edge between nodes ui and vi.
// si is the strength of the edge.
// musti is an integer (0 or 1). If musti == 1, the edge must be included in the spanning tree. These edges cannot be upgraded.
// You are also given an integer k, the maximum number of upgrades you can perform. Each upgrade doubles the strength of an edge, and each eligible edge (with musti == 0) can be upgraded at most once.

// The stability of a spanning tree is defined as the minimum strength score among all edges included in it.

// Return the maximum possible stability of any valid spanning tree. If it is impossible to connect all nodes, return -1.

// Note: A spanning tree of a graph with n nodes is a subset of the edges that connects all nodes together (i.e. the graph is connected) without forming any cycles, and uses exactly n - 1 edges.

 

// Example 1:

// Input: n = 3, edges = [[0,1,2,1],[1,2,3,0]], k = 1

// Output: 2

// Explanation:

// Edge [0,1] with strength = 2 must be included in the spanning tree.
// Edge [1,2] is optional and can be upgraded from 3 to 6 using one upgrade.
// The resulting spanning tree includes these two edges with strengths 2 and 6.
// The minimum strength in the spanning tree is 2, which is the maximum possible stability.
// Example 2:

// Input: n = 3, edges = [[0,1,4,0],[1,2,3,0],[0,2,1,0]], k = 2

// Output: 6

// Explanation:

// Since all edges are optional and up to k = 2 upgrades are allowed.
// Upgrade edges [0,1] from 4 to 8 and [1,2] from 3 to 6.
// The resulting spanning tree includes these two edges with strengths 8 and 6.
// The minimum strength in the tree is 6, which is the maximum possible stability.
// Example 3:

// Input: n = 3, edges = [[0,1,1,1],[1,2,1,1],[2,0,1,1]], k = 0

// Output: -1

// Explanation:

// All edges are mandatory and form a cycle, which violates the spanning tree property of acyclicity. Thus, the answer is -1.
 

// Constraints:

// 2 <= n <= 105
// 1 <= edges.length <= 105
// edges[i] = [ui, vi, si, musti]
// 0 <= ui, vi < n
// ui != vi
// 1 <= si <= 105
// musti is either 0 or 1.
// 0 <= k <= n
// There are no duplicate edges.

//solu = 
#include <bits/stdc++.h>
using namespace std;

/*
-------------------------------------------------------------
PROBLEM IDEA
-------------------------------------------------------------

We want to build a SPANNING TREE of the graph.

Definition:
A spanning tree of n nodes:
- connects all nodes
- has exactly n-1 edges
- contains NO cycles

The "stability" of a spanning tree is defined as:
    the minimum strength among its edges

Our goal:
    maximize this minimum strength.

-------------------------------------------------------------
KEY OBSERVATION
-------------------------------------------------------------

This is a classic problem type:

    "MAXIMIZE the MINIMUM value"

Whenever we see this pattern, we can try:

    BINARY SEARCH ON THE ANSWER

We will binary search the value X such that:

    "Can we build a valid spanning tree
     where every edge has strength ≥ X ?"

If YES → try larger X
If NO  → try smaller X

-------------------------------------------------------------
EDGE TYPES
-------------------------------------------------------------

Each edge has:
    [u, v, s, must]

u, v  -> endpoints
s     -> strength
must  -> if 1, edge MUST be included

IMPORTANT RULES:

1) Mandatory edges must be used.
2) Mandatory edges cannot be upgraded.
3) Optional edges can be upgraded once:
       strength becomes 2*s
4) At most k upgrades allowed.

-------------------------------------------------------------
GRAPH BUILDING TOOL
-------------------------------------------------------------

To construct a spanning tree efficiently we use:

    UNION-FIND / DISJOINT SET (DSU)

DSU helps us:
- connect components
- detect cycles
- build the tree greedily

-------------------------------------------------------------
*/


/*
-------------------------------------------------------------
DSU (Disjoint Set Union) STRUCTURE
-------------------------------------------------------------
Used for quickly merging components and checking cycles.
-------------------------------------------------------------
*/
struct DSU {

    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.resize(n,0);

        // initially each node is its own parent
        for(int i=0;i<n;i++)
            parent[i]=i;
    }

    /*
    Find the root parent of node x
    with path compression
    */
    int find(int x){
        if(parent[x]!=x)
            parent[x]=find(parent[x]);
        return parent[x];
    }

    /*
    Merge two sets
    Return false if they already belong to same component
    (which would create a cycle)
    */
    bool unite(int a,int b){

        a=find(a);
        b=find(b);

        if(a==b) return false;

        // union by rank optimization
        if(rankv[a]<rankv[b])
            swap(a,b);

        parent[b]=a;

        if(rankv[a]==rankv[b])
            rankv[a]++;

        return true;
    }
};



class Solution {
public:

    /*
    -------------------------------------------------------------
    CHECK FUNCTION
    -------------------------------------------------------------

    Determines if we can construct a spanning tree such that

        minimum edge strength ≥ x

    while using at most k upgrades.
    */
    bool can(int n, vector<vector<int>>& edges, int k, int x){

        DSU dsu(n);

        int usedUpgrades=0;   // upgrades used so far
        int edgeCount=0;      // edges included in tree

        vector<vector<int>> optional;

        /*
        ---------------------------------------------------------
        STEP 1: Process mandatory edges
        ---------------------------------------------------------

        Mandatory edges must:
        - be included
        - cannot be upgraded

        If a mandatory edge has strength < x
        → impossible to satisfy stability requirement.
        */

        for(auto &e: edges){

            int u=e[0];
            int v=e[1];
            int s=e[2];
            int must=e[3];

            if(must==1){

                // mandatory edge too weak
                if(s < x)
                    return false;

                // detect cycle
                if(!dsu.unite(u,v))
                    return false;

                edgeCount++;
            }
            else{
                optional.push_back(e);
            }
        }

        /*
        ---------------------------------------------------------
        STEP 2: Use optional edges WITHOUT upgrades
        ---------------------------------------------------------

        If strength already ≥ x
        we can safely include it.
        */

        for(auto &e: optional){

            int u=e[0];
            int v=e[1];
            int s=e[2];

            if(s >= x){

                if(dsu.unite(u,v))
                    edgeCount++;
            }
        }

        /*
        ---------------------------------------------------------
        STEP 3: Use optional edges WITH upgrades
        ---------------------------------------------------------

        If:

            s < x  BUT
            2*s ≥ x

        then upgrading the edge makes it valid.
        */

        for(auto &e: optional){

            int u=e[0];
            int v=e[1];
            int s=e[2];

            if(s < x && 2*s >= x && usedUpgrades < k){

                if(dsu.unite(u,v)){
                    edgeCount++;
                    usedUpgrades++;
                }
            }
        }

        /*
        A valid spanning tree must contain exactly n-1 edges
        */

        return edgeCount == n-1;
    }



    /*
    -------------------------------------------------------------
    MAIN FUNCTION
    -------------------------------------------------------------
    Uses binary search to maximize stability.
    */
    int maxStability(int n, vector<vector<int>>& edges, int k) {

        /*
        Strength can go up to:

            2 * max(si)

        since upgrades double the strength.
        */

        int left=1;
        int right=200000;

        int ans=-1;

        while(left<=right){

            int mid=(left+right)/2;

            if(can(n,edges,k,mid)){

                // possible → try larger stability
                ans=mid;
                left=mid+1;
            }
            else{

                // not possible → reduce
                right=mid-1;
            }
        }

        return ans;
    }
};
// tc = O(E log S)
// sc = O(N + E)

// E = number of edges
// N = number of nodes
// S = max strength
