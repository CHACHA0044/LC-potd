// 3721. Longest Balanced Subarray II
// Solved
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums.

// A subarray is called balanced if the number of distinct even numbers in the subarray is equal to the number of distinct odd numbers.

// Return the length of the longest balanced subarray.

 

// Example 1:

// Input: nums = [2,5,4,3]

// Output: 4

// Explanation:

// The longest balanced subarray is [2, 5, 4, 3].
// It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [5, 3]. Thus, the answer is 4.
// Example 2:

// Input: nums = [3,2,2,5,4]

// Output: 5

// Explanation:

// The longest balanced subarray is [3, 2, 2, 5, 4].
// It has 2 distinct even numbers [2, 4] and 2 distinct odd numbers [3, 5]. Thus, the answer is 5.
// Example 3:

// Input: nums = [1,2,3,2]

// Output: 3

// Explanation:

// The longest balanced subarray is [2, 3, 2].
// It has 1 distinct even number [2] and 1 distinct odd number [3]. Thus, the answer is 3.
 

// Constraints:

// 1 <= nums.length <= 105
// 1 <= nums[i] <= 105

//solu=
class SegmentTree {
public:
    int n;
    vector<int> sum, mn, mx;

    SegmentTree(int n_) : n(n_), sum(4 * n_, 0), mn(4 * n_, 0), mx(4 * n_, 0) {}

    /*
        This function recomputes the information of the current node
        using the already computed information of its left and right children.

        sum[node] stores the total sum of the segment.
        mn[node] stores the minimum prefix sum inside this segment.
        mx[node] stores the maximum prefix sum inside this segment.

        These three values together allow us to later check
        whether a desired prefix sum exists inside any segment.
    */
    void pull(int node) {
        int lc = node * 2, rc = node * 2 + 1;

        sum[node] = sum[lc] + sum[rc];
        mn[node] = std::min(mn[lc], sum[lc] + mn[rc]);
        mx[node] = std::max(mx[lc], sum[lc] + mx[rc]);
    }

    /*
        Public wrapper for point update.
        Updates the value at a single index in the original array.
    */
    void update(int idx, int val) { 
        update(1, 0, n - 1, idx, val); 
    }

    /*
        Recursively updates the segment tree.
        When we reach the leaf corresponding to idx,
        we store val as sum, min prefix, and max prefix
        because a single element segment has only one prefix.
    */
    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            sum[node] = val;
            mn[node] = val;
            mx[node] = val;
            return;
        }

        int m = (l + r) / 2;
        if (idx <= m) 
            update(node * 2, l, m, idx, val);
        else 
            update(node * 2 + 1, m + 1, r, idx, val);

        pull(node);
    }

    /*
        Checks whether there exists a prefix inside this segment
        such that the total prefix sum becomes equal to target.

        sum_before is the prefix sum accumulated before this segment.
        If target lies between mn and mx after adjusting with sum_before,
        then such a prefix is guaranteed to exist.
    */
    bool exist(int node, int sum_before, int target) const {
        int need = target - sum_before;
        return mn[node] <= need && need <= mx[node];
    }

    /*
        Finds the rightmost index r such that
        the prefix sum from index 0 to r equals target.
    */
    int find_rightmost_prefix(int target = 0) {
        return find_rightmost_prefix(1, 0, n - 1, 0, target);
    }

    /*
        Recursively searches for the rightmost valid prefix.
        We always try the right child first because we want
        the maximum possible index r.
    */
    int find_rightmost_prefix(int node, int l, int r, int sum_before, int target) {
        if (!exist(node, sum_before, target)) 
            return -1;

        if (l == r) 
            return l;

        int m = (l + r) / 2;
        int lc = node * 2, rc = node * 2 + 1;

        int sum_before_right = sum_before + sum[lc];
        if (exist(rc, sum_before_right, target))
            return find_rightmost_prefix(rc, m + 1, r, sum_before_right, target);

        return find_rightmost_prefix(lc, l, m, sum_before, target);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();

        /*
            Segment tree stores a balance array where
            +1 represents the first occurrence of a distinct even number
            -1 represents the first occurrence of a distinct odd number
            0 represents all other positions
        */
        SegmentTree stree(n);

        /*
            This map keeps track of the first occurrence index
            of each value for the current left boundary l.
        */
        unordered_map<int, int> first;

        int result = 0;

        /*
            We move the left boundary from right to left.
            For each l, we maintain a correct balance array
            representing distinct elements inside [l, r].
        */
        for (int l = n - 1; l >= 0; --l) {
            int x = nums[l];

            /*
                If x already appeared to the right,
                its previous first occurrence must be invalidated
                because the first occurrence is now at index l.
            */
            auto it = first.find(x);
            if (it != first.end())
                stree.update(it->second, 0);

            /*
                Mark the new first occurrence of x at index l.
                Even numbers contribute +1
                Odd numbers contribute -1
            */
            first[x] = l;
            stree.update(l, ((x & 1) == 0) ? 1 : -1);

            /*
                We now search for the farthest r >= l
                such that the sum of balance values in [l, r] is zero.
                This means the number of distinct evens equals
                the number of distinct odds in that subarray.
            */
            int r = stree.find_rightmost_prefix(0);
            if (r >= l) 
                result = std::max(result, r - l + 1);
        }

        return result;
    }
};

//tc= O(nlog n)
//sc= O(n)
