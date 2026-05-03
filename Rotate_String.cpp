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

    /*
    Helper function: checks whether a number is "good"

    A number is GOOD if:
    1. All digits are valid after rotation
       → invalid digits: 3, 4, 7
    2. At least one digit changes after rotation
       → changing digits: 2, 5, 6, 9
    */
    bool isGood(int num) {

        bool change = false;  // tracks if at least one digit changes

        /*
        Process each digit of the number
        */
        while (num > 0) {

            int d = num % 10;  // extract last digit
            num /= 10;         // remove last digit


            /*
            CASE 1: Invalid digit

            If any digit is 3, 4, or 7:
            → after rotation, it becomes invalid
            → entire number becomes invalid
            */
            if (d == 3 || d == 4 || d == 7)
                return false;


            /*
            CASE 2: Digit changes after rotation

            2 ↔ 5
            6 ↔ 9

            If at least one such digit exists,
            the number becomes different → GOOD candidate
            */
            if (d == 2 || d == 5 || d == 6 || d == 9)
                change = true;
        }


        /*
        Final condition:

        - If no digit was invalid → we survived loop
        - But we must ensure at least one digit changed

        Example:
        1 → valid but unchanged → NOT good
        */
        return change;
    }


    int rotatedDigits(int n) {

        int count = 0;  // counts number of good numbers


        /*
        Iterate through all numbers from 1 to n
        */
        for (int i = 1; i <= n; i++) {

            /*
            Only increment count IF number is good

            IMPORTANT:
            We must check function result.
            Calling function alone does nothing.
            */
            if (isGood(i)) {
                count++;
            }
        }


        /*
        Return total count of good numbers
        */
        return count;
    }
};
// Time:
// O(n * digits) ≈ O(n log n)
// Space:
// O(1)
