// 3661. Maximum Walls Destroyed by Robots
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// There is an endless straight line populated with some robots and walls. You are given integer arrays robots, distance, and walls:
// robots[i] is the position of the ith robot.
// distance[i] is the maximum distance the ith robot's bullet can travel.
// walls[j] is the position of the jth wall.
// Every robot has one bullet that can either fire to the left or the right at most distance[i] meters.

// A bullet destroys every wall in its path that lies within its range. Robots are fixed obstacles: if a bullet hits another robot before reaching a wall, it immediately stops at that robot and cannot continue.

// Return the maximum number of unique walls that can be destroyed by the robots.

// Notes:

// A wall and a robot may share the same position; the wall can be destroyed by the robot at that position.
// Robots are not destroyed by bullets.
 

// Example 1:

// Input: robots = [4], distance = [3], walls = [1,10]

// Output: 1

// Explanation:

// robots[0] = 4 fires left with distance[0] = 3, covering [1, 4] and destroys walls[0] = 1.
// Thus, the answer is 1.
// Example 2:

// Input: robots = [10,2], distance = [5,1], walls = [5,2,7]

// Output: 3

// Explanation:

// robots[0] = 10 fires left with distance[0] = 5, covering [5, 10] and destroys walls[0] = 5 and walls[2] = 7.
// robots[1] = 2 fires left with distance[1] = 1, covering [1, 2] and destroys walls[1] = 2.
// Thus, the answer is 3.
// Example 3:
// Input: robots = [1,2], distance = [100,1], walls = [10]

// Output: 0

// Explanation:

// In this example, only robots[0] can reach the wall, but its shot to the right is blocked by robots[1]; thus the answer is 0.

 

// Constraints:

// 1 <= robots.length == distance.length <= 105
// 1 <= walls.length <= 105
// 1 <= robots[i], walls[j] <= 109
// 1 <= distance[i] <= 105
// All values in robots are unique
// All values in walls are unique

// solu = 
class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance,
                 vector<int>& walls) {
        
        // ------------------------------------------
        // STEP 1: Combine robot position + distance
        // ------------------------------------------
        // We store robots as (position, distance)
        // so we can sort them and process left → right
        
        int n = robots.size();
        vector<pair<int, int>> robotDist;
        
        for (int i = 0; i < n; i++) {
            robotDist.push_back({robots[i], distance[i]});
        }
        
        
        // ------------------------------------------
        // STEP 2: Sort robots and walls
        // ------------------------------------------
        // Sorting is CRITICAL because:
        // - Robots block each other in order
        // - Walls need binary-like traversal
        
        sort(robotDist.begin(), robotDist.end());
        sort(walls.begin(), walls.end());

        int m = walls.size();
        
        
        // ------------------------------------------
        // STEP 3: Initialize pointers
        // ------------------------------------------
        // These pointers help us scan walls efficiently
        // WITHOUT re-scanning from beginning each time
        
        int rightPtr = 0;  // moves forward to count walls on right
        int leftPtr = 0;   // moves forward to count walls on left
        int curPtr = 0;    // helps find walls >= robot position
        int robotPtr = 0;  // tracks walls before previous robot

        
        // ------------------------------------------
        // STEP 4: DP variables (space optimized)
        // ------------------------------------------
        // Instead of full DP array, we only keep previous state
        
        // subLeft  = best result when current robot shoots LEFT
        // subRight = best result when current robot shoots RIGHT
        
        int prevLeft = 0, prevRight = 0, prevNum = 0;
        int subLeft = 0, subRight = 0;

        
        // ------------------------------------------
        // STEP 5: Process each robot
        // ------------------------------------------
        for (int i = 0; i < n; i++) {
            
            int robotPos = robotDist[i].first;
            int robotDistVal = robotDist[i].second;

            
            // --------------------------------------------------
            // Find walls <= robotPos (for LEFT side counting)
            // --------------------------------------------------
            // rightPtr acts like upper_bound(robotPos)
            
            while (rightPtr < m && walls[rightPtr] <= robotPos) {
                rightPtr++;
            }
            
            int pos1 = rightPtr;  // first wall strictly > robotPos

            
            // --------------------------------------------------
            // Find walls < robotPos (for RIGHT side starting)
            // --------------------------------------------------
            // curPtr acts like lower_bound(robotPos)
            
            while (curPtr < m && walls[curPtr] < robotPos) {
                curPtr++;
            }
            
            int pos2 = curPtr;  // first wall >= robotPos

            
            // --------------------------------------------------
            // LEFT RANGE CALCULATION
            // --------------------------------------------------
            
            // Compute left boundary:
            // - robot cannot shoot beyond its distance
            // - cannot cross previous robot
            
            int leftBound = (i >= 1) 
                ? max(robotPos - robotDistVal, robotDist[i - 1].first + 1)
                : robotPos - robotDistVal;
            
            
            // Move leftPtr to first wall inside left range
            while (leftPtr < m && walls[leftPtr] < leftBound) {
                leftPtr++;
            }
            
            int leftPos = leftPtr;
            
            
            // Number of walls in LEFT interval
            int currentLeft = pos1 - leftPos;

            
            // --------------------------------------------------
            // RIGHT RANGE CALCULATION
            // --------------------------------------------------
            
            // Compute right boundary:
            // - limited by distance
            // - cannot cross next robot
            
            int rightBound = (i < n - 1) 
                ? min(robotPos + robotDistVal, robotDist[i + 1].first - 1)
                : robotPos + robotDistVal;
            
            
            // Move rightPtr further to include valid right walls
            while (rightPtr < m && walls[rightPtr] <= rightBound) {
                rightPtr++;
            }
            
            int rightPos = rightPtr;
            
            
            // Number of walls in RIGHT interval
            int currentRight = rightPos - pos2;

            
            // --------------------------------------------------
            // Count walls between previous robot and current
            // --------------------------------------------------
            // This helps in avoiding double counting
            
            int currentNum = 0;
            
            if (i > 0) {
                
                // Move robotPtr to first wall >= previous robot
                while (robotPtr < m &&
                       walls[robotPtr] < robotDist[i - 1].first) {
                    robotPtr++;
                }
                
                int pos3 = robotPtr;
                
                // walls between prev robot and current robot
                currentNum = pos1 - pos3;
            }

            
            // --------------------------------------------------
            // DP TRANSITION
            // --------------------------------------------------
            
            if (i == 0) {
                // Base case: first robot
                subLeft = currentLeft;
                subRight = currentRight;
            } 
            else {
                
                // If current robot shoots LEFT:
                // Two options:
                // 1. Previous robot also shot LEFT
                // 2. Previous robot shot RIGHT → adjust overlap
                
                int newsubLeft =
                    max(subLeft + currentLeft,
                        subRight - prevRight +
                            min(currentLeft + prevRight, currentNum));
                
                
                // If current robot shoots RIGHT:
                // Either previous shot LEFT or RIGHT
                int newsubRight =
                    max(subLeft + currentRight, subRight + currentRight);
                
                
                // Update DP states
                subLeft = newsubLeft;
                subRight = newsubRight;
            }

            
            // --------------------------------------------------
            // Save current values for next iteration
            // --------------------------------------------------
            prevLeft = currentLeft;
            prevRight = currentRight;
            prevNum = currentNum;
        }

        
        // Final answer = best of last robot shooting left or right
        return max(subLeft, subRight);
    }
};
// Time Complexity
// Sorting:
// O(n log n + m log m)
// Pointer traversal:
// Each pointer (leftPtr, rightPtr, curPtr, robotPtr) moves only forward
// Total across all loops → O(m)
// Total: O(n log n + m log m + n + m)
// ≈ O(n log n + m log m)
// 📦 Space Complexity
// O(n)
// robotDist vector
// No DP array (only variables used → space optimized)
