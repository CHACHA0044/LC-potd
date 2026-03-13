// 3296. Minimum Number of Seconds to Make Mountain Height Zero
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer mountainHeight denoting the height of a mountain.

// You are also given an integer array workerTimes representing the work time of workers in seconds.

// The workers work simultaneously to reduce the height of the mountain. For worker i:

// To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For example:
// To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
// To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.
// Return an integer representing the minimum number of seconds required for the workers to make the height of the mountain 0.

 

// Example 1:

// Input: mountainHeight = 4, workerTimes = [2,1,1]

// Output: 3

// Explanation:

// One way the height of the mountain can be reduced to 0 is:

// Worker 0 reduces the height by 1, taking workerTimes[0] = 2 seconds.
// Worker 1 reduces the height by 2, taking workerTimes[1] + workerTimes[1] * 2 = 3 seconds.
// Worker 2 reduces the height by 1, taking workerTimes[2] = 1 second.
// Since they work simultaneously, the minimum time needed is max(2, 3, 1) = 3 seconds.

// Example 2:

// Input: mountainHeight = 10, workerTimes = [3,2,2,4]

// Output: 12

// Explanation:

// Worker 0 reduces the height by 2, taking workerTimes[0] + workerTimes[0] * 2 = 9 seconds.
// Worker 1 reduces the height by 3, taking workerTimes[1] + workerTimes[1] * 2 + workerTimes[1] * 3 = 12 seconds.
// Worker 2 reduces the height by 3, taking workerTimes[2] + workerTimes[2] * 2 + workerTimes[2] * 3 = 12 seconds.
// Worker 3 reduces the height by 2, taking workerTimes[3] + workerTimes[3] * 2 = 12 seconds.
// The number of seconds needed is max(9, 12, 12, 12) = 12 seconds.

// Example 3:

// Input: mountainHeight = 5, workerTimes = [1]

// Output: 15

// Explanation:

// There is only one worker in this example, so the answer is workerTimes[0] + workerTimes[0] * 2 + workerTimes[0] * 3 + workerTimes[0] * 4 + workerTimes[0] * 5 = 15.

 

// Constraints:

// 1 <= mountainHeight <= 105
// 1 <= workerTimes.length <= 104
// 1 <= workerTimes[i] <= 106

// solu = 
class Solution {
public:

    /*
    -----------------------------------------------------------
    FUNCTION: maxHeight
    -----------------------------------------------------------
    Calculates the maximum height a single worker can reduce
    within a given time.

    Worker time per unit = t

    Total time to reduce x height:
        t * (1 + 2 + ... + x)
      = t * x(x+1)/2

    We binary search x such that:
        t * x(x+1)/2 <= time
    -----------------------------------------------------------
    */
    long long maxHeight(long long time, long long t) {

        long long left = 0;
        long long right = 100000;  // maximum possible height
        long long ans = 0;

        while(left <= right) {

            long long mid = (left + right) / 2;

            // total time needed to reduce 'mid' height
            long long cost = t * (mid * (mid + 1) / 2);

            if(cost <= time) {
                ans = mid;           // worker can reduce 'mid'
                left = mid + 1;      // try larger height
            }
            else {
                right = mid - 1;     // reduce height
            }
        }

        return ans;
    }


    /*
    -----------------------------------------------------------
    FUNCTION: can
    -----------------------------------------------------------
    Checks if all workers combined can reduce the mountain
    height within the given time.

    Steps:
    1) For each worker calculate how much height they can reduce.
    2) Sum the heights.
    3) If total ≥ mountainHeight → feasible.
    -----------------------------------------------------------
    */
    bool can(long long time, int mountainHeight, vector<int>& workerTimes) {

        long long totalReduced = 0;

        for(long long t : workerTimes) {

            // compute max height this worker can reduce
            totalReduced += maxHeight(time, t);

            // early stopping if already enough
            if(totalReduced >= mountainHeight)
                return true;
        }

        return false;
    }



    /*
    -----------------------------------------------------------
    MAIN FUNCTION
    -----------------------------------------------------------
    We binary search the minimum time required.

    left  = 1 second
    right = very large time (1e18)

    For each time mid:
        check feasibility
    -----------------------------------------------------------
    */
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {

        long long left = 1;
        long long right = 1e18;   // safe upper bound
        long long ans = right;

        while(left <= right) {

            long long mid = (left + right) / 2;

            if(can(mid, mountainHeight, workerTimes)) {

                // possible → try smaller time
                ans = mid;
                right = mid - 1;
            }
            else {

                // not possible → increase time
                left = mid + 1;
            }
        }

        return ans;
    }
};
// tc = O(n × log(H) × log(T))
// sc = O(1)

// n = number of workers
// H = mountainHeight
// Binary Search on Time
// log(1e18) ≈ 60
// Worker computation

// For each worker we run a binary search for x:

// log(H) ≈ log(1e5) ≈ 17
// Total
// TC = O(n × log(H) × log(T))

// Substitute limits:

// n ≤ 10^4
// log(H) ≈ 17
// log(T) ≈ 60

// Final:

// TC ≈ 10^4 × 17 × 60
//    ≈ 1.02 × 10^7 operations

// Which runs easily within limits.
