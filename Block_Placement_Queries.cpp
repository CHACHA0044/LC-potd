// 3161. Block Placement Queries
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.

// You are given a 2D array queries, which contains two types of queries:

// For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
// For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
// Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.

 

// Example 1:

// Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]

// Output: [false,true,true]

// Explanation:



// For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.

// Example 2:

// Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]

// Output: [true,true,false]

// Explanation:



// Place an obstacle at x = 7 for query 0. A block of size at most 7 can be placed before x = 7.
// Place an obstacle at x = 2 for query 2. Now, a block of size at most 5 can be placed before x = 7, and a block of size at most 2 before x = 2.
 

// Constraints:

// 1 <= queries.length <= 15 * 104
// 2 <= queries[i].length <= 3
// 1 <= queries[i][0] <= 2
// 1 <= x, sz <= min(5 * 104, 3 * queries.length)
// The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
// The input is generated such that there is at least one query of type 2.
class Fenwick {
public:
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    /*
    Update position idx with value val.

    Fenwick tree stores prefix maximums,
    not prefix sums.
    */
    void update(int idx, int val) {
        idx++;

        while (idx <= n) {
            bit[idx] = max(bit[idx], val);
            idx += idx & -idx;
        }
    }

    /*
    Returns maximum value in range [0...idx].
    */
    int query(int idx) {
        int res = 0;
        idx++;

        while (idx > 0) {
            res = max(res, bit[idx]);
            idx -= idx & -idx;
        }

        return res;
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {

        /*
        Find the maximum coordinate that
        ever appears in any query.
        */
        int mx = 0;

        for (auto &q : queries) {
            mx = max(mx, q[1]);
        }

        /*
        Store all obstacle positions.

        We process queries in reverse,
        so first build the final state
        containing every obstacle.
        */
        set<int> pos;

        pos.insert(0);
        pos.insert(mx);

        for (auto &q : queries) {
            if (q[0] == 1) {
                pos.insert(q[1]);
            }
        }

        /*
        Fenwick tree maintains:

        For every obstacle position R,
        store the gap length between
        its previous obstacle and R.
        */
        Fenwick bit(mx + 1);

        auto it = pos.begin();

        int last = *it;
        ++it;

        /*
        Build all initial gaps.
        */
        for (; it != pos.end(); ++it) {

            bit.update(*it, *it - last);

            last = *it;
        }

        vector<bool> ans;

        /*
        Process queries backwards.

        Type 1:
        Remove obstacle.

        Type 2:
        Check whether a block of size sz
        can fit somewhere in [0, x].
        */
        for (int i = (int)queries.size() - 1; i >= 0; i--) {

            auto &q = queries[i];

            if (q[0] == 2) {

                int x = q[1];
                int sz = q[2];

                /*
                Find rightmost obstacle
                not greater than x.
                */
                int p = *std::prev(pos.upper_bound(x));

                /*
                Candidate 1:
                Largest complete gap ending
                before obstacle p.

                Candidate 2:
                Remaining segment [p, x].
                */
                int best = max(
                    bit.query(p),
                    x - p
                );

                ans.push_back(best >= sz);
            }
            else {

                int x = q[1];

                /*
                Reverse of obstacle insertion.

                Merge two adjacent gaps into
                one larger gap.
                */
                auto cur = pos.find(x);

                auto left = prev(cur);
                auto right = next(cur);

                /*
                New merged gap length.
                */
                bit.update(
                    *right,
                    *right - *left
                );

                pos.erase(cur);
            }
        }

        /*
        Answers were generated in reverse order.
        */
        reverse(ans.begin(), ans.end());

        return ans;
    }
};
// Time Complexity
// O(Q log M)
// Where:
// Q = number of queries
// M = maximum coordinate (<= 50000)
// Operations on set and Fenwick Tree take O(log M).
// Space Complexity
// O(M + O)
// Where:
// M = maximum coordinate used by Fenwick Tree
// O = number of obstacle positions
// In constraints:
// M <= 50000
// So space is effectively:
// O(M)
