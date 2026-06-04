// 3751. Total Waviness of Numbers in Range I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given two integers num1 and num2 representing an inclusive range [num1, num2].

// The waviness of a number is defined as the total count of its peaks and valleys:

// A digit is a peak if it is strictly greater than both of its immediate neighbors.
// A digit is a valley if it is strictly less than both of its immediate neighbors.
// The first and last digits of a number cannot be peaks or valleys.
// Any number with fewer than 3 digits has a waviness of 0.
// Return the total sum of waviness for all numbers in the range [num1, num2].
 

// Example 1:

// Input: num1 = 120, num2 = 130

// Output: 3

// Explanation:

// In the range [120, 130]:
// 120: middle digit 2 is a peak, waviness = 1.
// 121: middle digit 2 is a peak, waviness = 1.
// 130: middle digit 3 is a peak, waviness = 1.
// All other numbers in the range have a waviness of 0.
// Thus, total waviness is 1 + 1 + 1 = 3.

// Example 2:

// Input: num1 = 198, num2 = 202

// Output: 3

// Explanation:

// In the range [198, 202]:
// 198: middle digit 9 is a peak, waviness = 1.
// 201: middle digit 0 is a valley, waviness = 1.
// 202: middle digit 0 is a valley, waviness = 1.
// All other numbers in the range have a waviness of 0.
// Thus, total waviness is 1 + 1 + 1 = 3.

// Example 3:

// Input: num1 = 4848, num2 = 4848

// Output: 2

// Explanation:

// Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

 

// Constraints:
// 1 <= num1 <= num2 <= 105
class Solution {
public:

    /*
    --------------------------------------------------
    Returns waviness of a single number.

    Waviness = number of peaks + valleys

    Peak:
        digit > left digit
        digit > right digit

    Valley:
        digit < left digit
        digit < right digit
    --------------------------------------------------
    */
    int waviness(int num) {

        string s = to_string(num);

        int count = 0;


        /*
        First and last digits can never be
        peaks or valleys.

        Therefore check only middle digits.
        */
        for (int i = 1; i < s.size() - 1; i++) {

            /*
            Check if current digit is a peak.

            Example:
            121

            2 > 1 and 2 > 1
            */
            if (s[i] > s[i - 1] &&
                s[i] > s[i + 1]) {

                count++;
            }


            /*
            Check if current digit is a valley.

            Example:
            202

            0 < 2 and 0 < 2
            */
            else if (s[i] < s[i - 1] &&
                     s[i] < s[i + 1]) {

                count++;
            }
        }

        return count;
    }


    int totalWaviness(int num1, int num2) {

        /*
        Stores total waviness of all numbers
        in the range [num1, num2].
        */
        int ans = 0;


        /*
        Compute waviness for every number
        in the range.
        */
        for (int num = num1; num <= num2; num++) {

            ans += waviness(num);
        }


        return ans;
    }
};
// Time Complexity
// O((num2 - num1 + 1) * d)
// We process every number in the range.
// d = number of digits in the number.
// Since:
// num2 ≤ 100000
// we have:
// d ≤ 6
// So practically:
// O(num2 - num1 + 1)
// Space Complexity
// O(d)
// Used by the string representation of a number.
// Since d ≤ 6, this is effectively constant space.
