// 788. Rotated Digits
// Medium
// Topics
// premium lock icon
// Companies
// An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

// A number is valid if each digit remains a digit after rotation. For example:

// 0, 1, and 8 rotate to themselves,
// 2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
// 6 and 9 rotate to each other, and
// the rest of the numbers do not rotate to any other number and become invalid.
// Given an integer n, return the number of good integers in the range [1, n].

 

// Example 1:

// Input: n = 10
// Output: 4
// Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
// Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
// Example 2:

// Input: n = 1
// Output: 0
// Example 3:

// Input: n = 2
// Output: 1
 

// Constraints:

// 1 <= n <= 104

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
  
// Pattern
// Digit processing + validation + flag tracking
