// 2751. Robot Collisions
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// There are n 1-indexed robots, each having a position on a line, health, and movement direction.

// You are given 0-indexed integer arrays positions, healths, and a string directions (directions[i] is either 'L' for left or 'R' for right). All integers in positions are unique.

// All robots start moving on the line simultaneously at the same speed in their given directions. If two robots ever share the same position while moving, they will collide.

// If two robots collide, the robot with lower health is removed from the line, and the health of the other robot decreases by one. The surviving robot continues in the same direction it was going. If both robots have the same health, they are both removed from the line.

// Your task is to determine the health of the robots that survive the collisions, in the same order that the robots were given, i.e. final health of robot 1 (if survived), final health of robot 2 (if survived), and so on. If there are no survivors, return an empty array.

// Return an array containing the health of the remaining robots (in the order they were given in the input), after no further collisions can occur.

// Note: The positions may be unsorted.

 
 

// Example 1:



// Input: positions = [5,4,3,2,1], healths = [2,17,9,15,10], directions = "RRRRR"
// Output: [2,17,9,15,10]
// Explanation: No collision occurs in this example, since all robots are moving in the same direction. So, the health of the robots in order from the first robot is returned, [2, 17, 9, 15, 10].
// Example 2:



// Input: positions = [3,5,2,6], healths = [10,10,15,12], directions = "RLRL"
// Output: [14]
// Explanation: There are 2 collisions in this example. Firstly, robot 1 and robot 2 will collide, and since both have the same health, they will be removed from the line. Next, robot 3 and robot 4 will collide and since robot 4's health is smaller, it gets removed, and robot 3's health becomes 15 - 1 = 14. Only robot 3 remains, so we return [14].
// Example 3:



// Input: positions = [1,2,5,6], healths = [10,10,11,11], directions = "RLRL"
// Output: []
// Explanation: Robot 1 and robot 2 will collide and since both have the same health, they are both removed. Robot 3 and 4 will collide and since both have the same health, they are both removed. So, we return an empty array, [].
 

// Constraints:

// 1 <= positions.length == healths.length == directions.length == n <= 105
// 1 <= positions[i], healths[i] <= 109
// directions[i] == 'L' or directions[i] == 'R'
// All values in positions are distinct

// solu =
class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        
        int n = positions.size();
        
        
        // ----------------------------------------------------------
        // STEP 1: Combine all robot information into one structure
        // ----------------------------------------------------------
        // We store:
        // (position, health, direction, original index)
        // 
        // Why original index?
        // Because after sorting, we need to return results
        // in the original input order
        
        vector<tuple<int,int,char,int>> robots;
        
        for(int i = 0; i < n; i++) {
            robots.push_back({positions[i], healths[i], directions[i], i});
        }
        
        
        // ----------------------------------------------------------
        // STEP 2: Sort robots by position
        // ----------------------------------------------------------
        // Collisions depend on spatial order (left to right),
        // not input order
        
        sort(robots.begin(), robots.end());
        
        
        // ----------------------------------------------------------
        // STEP 3: Use stack to track right-moving robots
        // ----------------------------------------------------------
        // Why stack?
        // Because the most recent right-moving robot
        // is the first one a left-moving robot will collide with
        
        stack<int> st;  // stores indices in the 'robots' array
        
        
        // ----------------------------------------------------------
        // STEP 4: Process each robot
        // ----------------------------------------------------------
        
        for(int i = 0; i < n; i++) {
            
            auto& [pos, health, dir, idx] = robots[i];
            
            
            // ------------------------------------------
            // CASE 1: Robot moving RIGHT
            // ------------------------------------------
            // It may collide later with a left-moving robot
            // So we push it into stack
            
            if(dir == 'R') {
                st.push(i);
            }
            
            
            // ------------------------------------------
            // CASE 2: Robot moving LEFT
            // ------------------------------------------
            // It can collide with previous right-moving robots
            
            else {
                
                // Keep resolving collisions while:
                // 1. There is a right-moving robot available
                // 2. Current robot is still alive (health > 0)
                
                while(!st.empty() && get<1>(robots[i]) > 0) {
                    
                    int j = st.top();  // index of last right-moving robot
                    
                    
                    // ------------------------------------------
                    // Compare healths
                    // ------------------------------------------
                    
                    if(get<1>(robots[j]) < get<1>(robots[i])) {
                        // Right robot is weaker → it dies
                        
                        get<1>(robots[i]) -= 1;   // left robot loses 1 health
                        get<1>(robots[j]) = 0;   // right robot removed
                        
                        st.pop();  // remove dead robot
                    }
                    
                    else if(get<1>(robots[j]) > get<1>(robots[i])) {
                        // Left robot is weaker → it dies
                        
                        get<1>(robots[j]) -= 1;  // right robot loses 1 health
                        get<1>(robots[i]) = 0;   // left robot removed
                        
                        break;  // no more collisions for this robot
                    }
                    
                    else {
                        // Equal health → both die
                        
                        get<1>(robots[j]) = 0;
                        get<1>(robots[i]) = 0;
                        
                        st.pop();
                        break;
                    }
                }
            }
        }
        
        
        // ----------------------------------------------------------
        // STEP 5: Collect surviving robots
        // ----------------------------------------------------------
        // We need to return healths in ORIGINAL order
        
        vector<int> result(n, 0);
        
        for(auto& [pos, health, dir, idx] : robots) {
            if(health > 0) {
                result[idx] = health;
            }
        }
        
        
        // ----------------------------------------------------------
        // STEP 6: Build final answer
        // ----------------------------------------------------------
        // Only include surviving robots (health > 0)
        
        vector<int> ans;
        
        for(int i = 0; i < n; i++) {
            if(result[i] > 0) {
                ans.push_back(result[i]);
            }
        }
        
        return ans;
    }
};
// Time Complexity: O(n log n)
// Space Complexity: O(n)
