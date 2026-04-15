// 2515. Shortest Distance to Target String in a Circular Array
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given a 0-indexed circular string array words and a string target. A circular array means that the array's end connects to the array's beginning.

// Formally, the next element of words[i] is words[(i + 1) % n] and the previous element of words[i] is words[(i - 1 + n) % n], where n is the length of words.
// Starting from startIndex, you can move to either the next word or the previous word with 1 step at a time.

// Return the shortest distance needed to reach the string target. If the string target does not exist in words, return -1.

 

// Example 1:

// Input: words = ["hello","i","am","leetcode","hello"], target = "hello", startIndex = 1
// Output: 1
// Explanation: We start from index 1 and can reach "hello" by
// - moving 3 units to the right to reach index 4.
// - moving 2 units to the left to reach index 4.
// - moving 4 units to the right to reach index 0.
// - moving 1 unit to the left to reach index 0.
// The shortest distance to reach "hello" is 1.
// Example 2:

// Input: words = ["a","b","leetcode"], target = "leetcode", startIndex = 0
// Output: 1
// Explanation: We start from index 0 and can reach "leetcode" by
// - moving 2 units to the right to reach index 2.
// - moving 1 unit to the left to reach index 2.
// The shortest distance to reach "leetcode" is 1.
// Example 3:

// Input: words = ["i","eat","leetcode"], target = "ate", startIndex = 0
// Output: -1
// Explanation: Since "ate" does not exist in words, we return -1.
 

// Constraints:

// 1 <= words.length <= 100
// 1 <= words[i].length <= 100
// words[i] and target consist of only lowercase English letters.
// 0 <= startIndex < words.length

// solu - 
class Solution {
public:
    
    int closestTarget(vector<string>& words, string target, int startIndex) {
        
        // Total number of words in the circular array
        int n = words.size();

        
        // Initialize answer with a very large value
        // This will store the minimum distance found
        int minDistance = INT_MAX;

        
        // Traverse through every index in the array
        for (int i = 0; i < n; i++) {

            // Process only those positions where the word matches target
            if (words[i] == target) {

                
                // Direct distance if we move normally without wrapping
                // Example: startIndex = 1, i = 4 -> directDistance = 3
                int directDistance = abs(i - startIndex);

                
                // Because array is circular, we can also wrap around the ends
                // Circular distance = Total size - direct distance
                // Example: n = 5, directDistance = 3 -> wrap distance = 2
                int wrapAroundDistance = n - directDistance;

                
                // Actual shortest distance to this target occurrence
                // is minimum of direct path and wrap-around path
                int shortestToCurrentTarget = min(directDistance, wrapAroundDistance);

                
                // Update global minimum answer
                minDistance = min(minDistance, shortestToCurrentTarget);
            }
        }

        
        // If target never appeared in words,
        // minDistance would remain unchanged
        if (minDistance == INT_MAX) {
            return -1;
        }

        
        // Return the minimum circular distance found
        return minDistance;
    }
};
// Time Complexity
// O(n)
// Single traversal of array
// Space Complexity
// O(1)
// Constant extra space
