// 3464. Maximize the Distance Between Points on a Square
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.

// You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.

// You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.

// Return the maximum possible minimum Manhattan distance between the selected k points.

// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

 

// Example 1:

// Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4

// Output: 2

// Explanation:



// Select all four points.

// Example 2:

// Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4

// Output: 1

// Explanation:



// Select the points (0, 0), (2, 0), (2, 2), and (2, 1).

// Example 3:

// Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5

// Output: 1

// Explanation:



// Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).

 

// Constraints:

// 1 <= side <= 109
// 4 <= points.length <= min(4 * side, 15 * 103)
// points[i] == [xi, yi]
// The input is generated such that:
// points[i] lies on the boundary of the square.
// All points[i] are unique.
// 4 <= k <= min(25, points.length)
// solu= 
class Solution {
public:
    int maxDistance(int side, vector<vector<int>>& points, int k) {
        
        // Step 1: Convert 2D boundary points → 1D positions along square perimeter
        // We traverse the square boundary in a fixed order (clockwise):
        // left edge → top → right → bottom (based on given mapping)
        
        vector<long long> res;

        for (auto& p : points) {
            int x = p[0], y = p[1];

            // Each condition maps (x, y) to a unique position on perimeter

            if (x == 0) 
                // Left edge: (0, y)
                // Distance from bottom-left corner going upward
                res.push_back(y);

            else if (y == side) 
                // Top edge: (x, side)
                // Continue from left edge → add 'side'
                res.push_back((long long)side + x);

            else if (x == side) 
                // Right edge: (side, y)
                // Continue → add 2*side, but reversed direction
                res.push_back((long long)side * 3 - y);

            else 
                // Bottom edge: (x, 0)
                // Final segment → wrap back
                res.push_back((long long)side * 4 - x);
        }

        
        // Sort positions along perimeter
        // This allows greedy selection in increasing order
        sort(res.begin(), res.end());



        // Step 2: Check function
        // Given a minimum distance 'n', can we select k points
        // such that every consecutive chosen point is ≥ n apart?
        auto check = [&](int n) {

            int m = res.size();

            // idx[] stores indices of chosen points
            vector<int> idx(k);

            
            // Try greedy selection starting from first point
            long long curr = res[0];
            idx[0] = 0;

            
            // Pick remaining k-1 points greedily
            for (int i = 1; i < k; i++) {

                // Find first point ≥ curr + n
                auto it = lower_bound(res.begin(), res.end(), curr + n);

                // If no such point exists → not possible
                if (it == res.end()) 
                    return false;

                // Store index of chosen point
                idx[i] = distance(res.begin(), it);

                curr = *it;
            }

            
            // Now check circular condition:
            // Distance between last and first (wrap-around)
            // should also be ≥ n
            if (res[idx[k - 1]] - res[0] <= (long long)side * 4 - n) 
                return true;



            // Step 3: Try shifting starting point
            // Because greedy from index 0 may not always work
            for (idx[0] = 1; idx[0] < idx[1]; idx[0]++) {

                // Try building k points again from new start
                for (int j = 1; j < k; j++) {

                    // Move forward until distance condition satisfied
                    while (idx[j] < m && res[idx[j]] < res[idx[j - 1]] + n) {
                        idx[j]++;
                    }

                    // If we run out of points → fail
                    if (idx[j] == m) 
                        return false;
                }

                // Check circular condition again
                if (res[idx[k - 1]] - res[idx[0]] <= (long long)side * 4 - n) 
                    return true;
            }

            
            return false;
        };



        // Step 4: Binary Search on answer
        // We maximize minimum distance

        int left = 1;

        // Upper bound:
        // Max possible distance ≈ perimeter / k
        int right = (1LL * side * 4) / k + 1;

        
        while (left + 1 < right) {

            int mid = left + (right - left) / 2;

            // If we can achieve 'mid', try bigger
            if (check(mid)) 
                left = mid;
            else 
                right = mid;
        }

        
        // Final answer
        return left;
    }
};
// Time Complexity
// Sorting:
// O(n log n)
// Binary Search:
// O(log(side))
// Check Function:
// O(k log n + k * shift)
// ≈ O(n * k) worst-case
// Overall:
// O(n log n + log(side) * n * k)
// Since:
// k ≤ 25 → efficient
// Space Complexity
// O(n)
// storing positions + helper arrays
