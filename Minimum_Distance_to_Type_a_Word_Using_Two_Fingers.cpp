// 1320. Minimum Distance to Type a Word Using Two Fingers
// Hard
// Topics
// premium lock icon
// Companies
// Hint

// You have a keyboard layout as shown above in the X-Y plane, where each English uppercase letter is located at some coordinate.

// For example, the letter 'A' is located at coordinate (0, 0), the letter 'B' is located at coordinate (0, 1), the letter 'P' is located at coordinate (2, 3) and the letter 'Z' is located at coordinate (4, 1).
// Given the string word, return the minimum total distance to type such string using only two fingers.

// The distance between coordinates (x1, y1) and (x2, y2) is |x1 - x2| + |y1 - y2|.

// Note that the initial positions of your two fingers are considered free so do not count towards your total distance, also your two fingers do not have to start at the first letter or the first two letters.

 

// Example 1:

// Input: word = "CAKE"
// Output: 3
// Explanation: Using two fingers, one optimal way to type "CAKE" is: 
// Finger 1 on letter 'C' -> cost = 0 
// Finger 1 on letter 'A' -> cost = Distance from letter 'C' to letter 'A' = 2 
// Finger 2 on letter 'K' -> cost = 0 
// Finger 2 on letter 'E' -> cost = Distance from letter 'K' to letter 'E' = 1 
// Total distance = 3
// Example 2:

// Input: word = "HAPPY"
// Output: 6
// Explanation: Using two fingers, one optimal way to type "HAPPY" is:
// Finger 1 on letter 'H' -> cost = 0
// Finger 1 on letter 'A' -> cost = Distance from letter 'H' to letter 'A' = 2
// Finger 2 on letter 'P' -> cost = 0
// Finger 2 on letter 'P' -> cost = Distance from letter 'P' to letter 'P' = 0
// Finger 1 on letter 'Y' -> cost = Distance from letter 'A' to letter 'Y' = 4
// Total distance = 6
 

// Constraints:

// 2 <= word.length <= 300
// word consists of uppercase English letters.

// solu = 
class Solution {
public:

    // --------------------------------------------------
    // Helper Function: Compute Manhattan Distance
    // --------------------------------------------------
    // Keyboard layout is:
    //
    // A B C D E F
    // G H I J K L
    // M N O P Q R
    // S T U V W X
    // Y Z
    //
    // Each letter index maps to:
    // row = index / 6
    // col = index % 6
    //
    // Distance = Manhattan Distance
    //
    int cal(int a, int b) {
        int ax = a / 6, ay = a % 6;
        int bx = b / 6, by = b % 6;

        return abs(ax - bx) + abs(ay - by);
    }

    
    int minimumDistance(string s) {
        
        int n = s.size();
        
        
        // --------------------------------------------------
        // DP Definition:
        // --------------------------------------------------
        // dp[i][j][k] =
        // Minimum cost to type first i characters
        // where:
        //   finger1 is at letter j
        //   finger2 is at letter k
        //
        // Letter positions are stored as:
        // A=0, B=1, ..., Z=25
        //
        // Note:
        // dp is auto-initialized to 0 because it is local stack array?
        // Actually NOT guaranteed for local arrays.
        // But problem's accepted trick relies on dp[0][*][*] = 0,
        // meaning before typing anything:
        // both fingers can start anywhere for FREE.
        //
        
        int dp[300][26][26] = {};
        
        
        // --------------------------------------------------
        // Process each character of the word
        // --------------------------------------------------
        for (int i = 0; i < n; i++) {
            
            // Current character to type
            int t = s[i] - 'A';

            
            // --------------------------------------------------
            // Initialize next layer with large value
            // --------------------------------------------------
            // We are computing dp[i+1] from dp[i]
            //
            for (int j = 0; j < 26; j++) {
                for (int k = 0; k < 26; k++) {
                    dp[i + 1][j][k] = 1e6;
                }
            }

            
            // --------------------------------------------------
            // Transition from all previous finger positions
            // --------------------------------------------------
            for (int j = 0; j < 26; j++) {
                for (int k = 0; k < 26; k++) {

                    
                    // ------------------------------------------
                    // Option 1:
                    // Finger 2 types current character
                    // ------------------------------------------
                    //
                    // Finger1 remains at j
                    // Finger2 moves from k → t
                    //
                    dp[i + 1][j][t] = min(
                        dp[i + 1][j][t],
                        dp[i][j][k] + cal(k, t)
                    );

                    
                    // ------------------------------------------
                    // Option 2:
                    // Finger 1 types current character
                    // ------------------------------------------
                    //
                    // Finger2 remains at k
                    // Finger1 moves from j → t
                    //
                    dp[i + 1][t][k] = min(
                        dp[i + 1][t][k],
                        dp[i][j][k] + cal(j, t)
                    );
                }
            }
        }

        
        // --------------------------------------------------
        // Final Answer:
        // --------------------------------------------------
        // After typing all n characters,
        // answer is minimum over all finger positions
        //
        int ans = 1e6;

        for (int j = 0; j < 26; j++) {
            for (int k = 0; k < 26; k++) {
                ans = min(ans, dp[n][j][k]);
            }
        }

        return ans;
    }
};
// Time Complexity
// n states for characters
// 26 * 26 finger position combinations
// O(1) work per transition
// Time = O(n * 26 * 26)
//      = O(676n)
//      ≈ O(n)
// Space Complexity
// DP array:
// 300 * 26 * 26
// So:
// Space = O(n * 26 * 26)

class Solution {
public:

    // --------------------------------------------------
    // Compute Manhattan Distance Between Two Letters
    // --------------------------------------------------
    int cal(int a, int b) {
        int ax = a / 6, ay = a % 6;
        int bx = b / 6, by = b % 6;

        return abs(ax - bx) + abs(ay - by);
    }


    int minimumDistance(string s) {
        
        int n = s.size();
        
        
        // --------------------------------------------------
        // prev[j][k] =
        // Minimum cost after typing processed characters
        // with:
        //   finger1 at letter j
        //   finger2 at letter k
        // --------------------------------------------------
        
        vector<vector<int>> prev(26, vector<int>(26, 0));
        
        
        // --------------------------------------------------
        // Process each character in word
        // --------------------------------------------------
        for(int i = 0; i < n; i++) {
            
            int t = s[i] - 'A';  // current target character
            
            
            // Initialize next DP layer with large values
            vector<vector<int>> curr(26, vector<int>(26, 1e9));
            
            
            // Try all previous finger positions
            for(int j = 0; j < 26; j++) {
                for(int k = 0; k < 26; k++) {
                    
                    
                    // ------------------------------------------
                    // Option 1:
                    // Finger 2 types current character
                    // ------------------------------------------
                    curr[j][t] = min(
                        curr[j][t],
                        prev[j][k] + cal(k, t)
                    );
                    
                    
                    // ------------------------------------------
                    // Option 2:
                    // Finger 1 types current character
                    // ------------------------------------------
                    curr[t][k] = min(
                        curr[t][k],
                        prev[j][k] + cal(j, t)
                    );
                }
            }
            
            
            // Move current layer to previous
            prev = curr;
        }
        
        
        // --------------------------------------------------
        // Find minimum among all ending finger positions
        // --------------------------------------------------
        int ans = 1e9;
        
        for(int j = 0; j < 26; j++) {
            for(int k = 0; k < 26; k++) {
                ans = min(ans, prev[j][k]);
            }
        }
        
        return ans;
    }
};
// ime Complexity
// Foor each character:
// Try all 26 * 26 finger position pairs
// O(n * 26 * 26)
// ≈ O(n)
// Space Complexity
// Only storing:
// 2 layers of 26x26 DP
// So:
// O(26 * 26)
// = O(1)
