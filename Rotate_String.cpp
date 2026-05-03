// 796. Rotate String
// Solved
// Easy
// Topics
// premium lock icon
// Companies
// Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

// A shift on s consists of moving the leftmost character of s to the rightmost position.

// For example, if s = "abcde", then it will be "bcdea" after one shift.
 

// Example 1:

// Input: s = "abcde", goal = "cdeab"
// Output: true
// Example 2:

// Input: s = "abcde", goal = "abced"
// Output: false
 

// Constraints:

// 1 <= s.length, goal.length <= 100
// s and goal consist of lowercase English letters.

// solu = 
class Solution {
public:
    bool rotateString(string s, string goal) {
        
        // Length must match
        if (s.size() != goal.size()) return false;

        
        // Trick: check if goal is substring of s+s
        string temp = s + s;

        return temp.find(goal) != string::npos;
    }
};

// Time:
// O(n * digits) ≈ O(n log n)
// Space:
// O(1)
