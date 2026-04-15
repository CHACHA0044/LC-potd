// 2463. Minimum Total Distance Traveled
// Solved
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// There are some robots and factories on the X-axis. You are given an integer array robot where robot[i] is the position of the ith robot. You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.

// The positions of each robot are unique. The positions of each factory are also unique. Note that a robot can be in the same position as a factory initially.

// All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.

// At any moment, you can set the initial direction of moving for some robot. Your target is to minimize the total distance traveled by all the robots.

// Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.

// Note that

// All robots move at the same speed.
// If two robots move in the same direction, they will never collide.
// If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
// If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
// If the robot moved from a position x to a position y, the distance it moved is |y - x|.
 

// Example 1:


// Input: robot = [0,4,6], factory = [[2,2],[6,2]]
// Output: 4
// Explanation: As shown in the figure:
// - The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
// - The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
// - The third robot at position 6 will be repaired at the second factory. It does not need to move.
// The limit of the first factory is 2, and it fixed 2 robots.
// The limit of the second factory is 2, and it fixed 1 robot.
// The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.
// Example 2:


// Input: robot = [1,-1], factory = [[-2,1],[2,1]]
// Output: 2
// Explanation: As shown in the figure:
// - The first robot at position 1 moves in the positive direction. It will be repaired at the second factory.
// - The second robot at position -1 moves in the negative direction. It will be repaired at the first factory.
// The limit of the first factory is 1, and it fixed 1 robot.
// The limit of the second factory is 1, and it fixed 1 robot.
// The total distance is |2 - 1| + |(-2) - (-1)| = 2. It can be shown that we cannot achieve a better total distance than 2.
 

// Constraints:

// 1 <= robot.length, factory.length <= 100
// factory[j].length == 2
// -109 <= robot[i], positionj <= 109
// 0 <= limitj <= robot.length
// The input will be generated such that it is always possible to repair every robot.

// solu = 
class Solution {
public:
    
    // dp[i][j] stores the minimum total distance required
    // to repair all robots starting from index i
    // using factories starting from index j onward
    long long dp[105][105];

    
    long long solve(int i, int j, vector<int>& robot, vector<vector<int>>& factory) {
        
        // Base Case 1:
        // If all robots have been assigned/repaired,
        // no more distance is needed
        if (i == robot.size()) return 0;

        
        // Base Case 2:
        // If factories are exhausted but robots remain,
        // this is an invalid assignment
        // Return a very large number so this path is never chosen
        if (j == factory.size()) return 1e18;

        
        // If already computed, return stored result
        if (dp[i][j] != -1) return dp[i][j];

        
        // Option 1:
        // Skip current factory completely
        // Try solving with next factory
        long long ans = solve(i, j + 1, robot, factory);

        
        // dist stores cumulative distance of assigning robots
        // to current factory one by one
        long long dist = 0;

        
        // Try assigning k+1 robots to current factory
        // (k starts from 0, so k+1 robots are assigned)
        for (int k = 0; k < factory[j][1] && i + k < robot.size(); k++) {
            
            // Add distance of current robot to this factory
            dist += abs((long long)robot[i + k] - factory[j][0]);

            
            // Total cost if we assign robots i to i+k to this factory:
            // Current cumulative distance +
            // Solve remaining robots with next factories
            ans = min(ans, dist + solve(i + k + 1, j + 1, robot, factory));
        }

        
        // Memoize and return answer
        return dp[i][j] = ans;
    }

    
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        
        // Sort robots by position
        // So nearby robots stay consecutive
        sort(robot.begin(), robot.end());

        
        // Sort factories by position
        sort(factory.begin(), factory.end());

        
        // Initialize DP table with -1 (uncomputed)
        memset(dp, -1, sizeof(dp));

        
        // Start from first robot and first factory
        return solve(0, 0, robot, factory);
    }
};

// Time Complexity
// R = number of robots
// F = number of factories
// L = max factory limit
// DP States:
// O(R * F)
// Each State Tries:
// Up to L assignments
// Total:
// O(R * F * L)
// Worst Case:
// O(100 * 100 * 100) = O(10^6)

// Space Complexity
// DP Table:
// O(R * F)
// Recursive Stack:
// O(F)
// Total:
// O(R * F)
