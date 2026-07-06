// 1288. Remove Covered Intervals
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are covered by another interval in the list.

// The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.

// Return the number of remaining intervals.

 

// Example 1:

// Input: intervals = [[1,4],[3,6],[2,8]]
// Output: 2
// Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
// Example 2:

// Input: intervals = [[1,4],[2,3]]
// Output: 1
 

// Constraints:

// 1 <= intervals.length <= 1000
// intervals[i].length == 2
// 0 <= li < ri <= 105
// All the given intervals are unique.
class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {

        // Sort intervals by:
        // 1. Increasing start point.
        // 2. If start points are equal,
        //    larger end point comes first.
        // This ensures that a larger interval
        // appears before the intervals it may cover.
        sort(intervals.begin(), intervals.end(),
        [](vector<int> &a, vector<int> &b) {

            if (a[0] == b[0])
                return a[1] > b[1];

            return a[0] < b[0];
        });

        // Number of intervals that remain.
        int ans = 0;

        // Largest ending point seen so far.
        int end = -1;

        for (auto &interval : intervals) {

            // If the current interval extends beyond
            // every previous interval, it is NOT covered.
            if (interval[1] > end) {

                ans++;

                // Update the farthest ending point.
                end = interval[1];
            }

            // Otherwise:
            // interval[1] <= end
            // Since its starting point is also
            // not smaller than previous intervals
            // (because of sorting),
            // this interval is completely covered.
        }

        return ans;
    }
};

/*
Time Complexity: O(n log n)

Space Complexity: O(1)
*/
