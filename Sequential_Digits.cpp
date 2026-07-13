// 1291. Sequential Digits
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

// Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

 

// Example 1:

// Input: low = 100, high = 300
// Output: [123,234]
// Example 2:

// Input: low = 1000, high = 13000
// Output: [1234,2345,3456,4567,5678,6789,12345]
 

// Constraints:

// 10 <= low <= high <= 10^9
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {

        // ------------------------------------------------------------
        // All sequential digit numbers are substrings of
        // "123456789".
        //
        // Example:
        //
        // Length 2:
        // 12,23,34,...,89
        //
        // Length 3:
        // 123,234,...,789
        //
        // Length 4:
        // 1234,2345,...,6789
        // ------------------------------------------------------------
        string digits = "123456789";

        vector<int> ans;

        // ------------------------------------------------------------
        // Determine the minimum and maximum number of digits
        // that need to be checked.
        //
        // Example:
        //
        // low = 100
        // high = 13000
        //
        // We only need lengths from 3 to 5.
        // ------------------------------------------------------------
        int minLen = to_string(low).size();
        int maxLen = to_string(high).size();

        // ------------------------------------------------------------
        // Generate every possible sequential number
        // having lengths between minLen and maxLen.
        // ------------------------------------------------------------
        for (int len = minLen; len <= maxLen; len++) {

            // Starting position inside "123456789".
            //
            // Example:
            //
            // len = 3
            //
            // 123
            // 234
            // 345
            // ...
            // 789
            for (int i = 0; i + len <= 9; i++) {

                // Extract the substring.
                string cur = digits.substr(i, len);

                // Convert it into an integer.
                int num = stoi(cur);

                // Keep only numbers lying inside the range.
                if (num >= low && num <= high)
                    ans.push_back(num);
            }
        }

        return ans;
    }
};

/*
------------------------------------------------------------
Why does this work?

Every sequential digit number is simply a contiguous
substring of

"123456789"

Examples:

Length 2

12
23
34
45
56
67
78
89

---------------------------------------

Length 3

123
234
345
456
567
678
789

---------------------------------------

Length 4

1234
2345
3456
4567
5678
6789

There are only a total of

8 + 7 + 6 + ... + 1 = 36

possible sequential numbers.

Hence generating all of them is very efficient.

------------------------------------------------------------
Dry Run

Input:

low = 100
high = 300

minLen = 3
maxLen = 3

Generate:

123 ✓
234 ✓
345 ✗
456 ✗
...
789 ✗

Answer:

[123,234]

------------------------------------------------------------
Edge Cases

1. low and high have the same number of digits.

Example:

low = 500
high = 700

Generated:

567

Answer:

[567]

------------------------------------------------------------

2. Single valid number.

Example:

low = 1234
high = 1234

Output:

[1234]

------------------------------------------------------------

3. No valid sequential number.

Example:

low = 900
high = 1000

Output:

[]

------------------------------------------------------------

4. Largest possible range.

low = 10
high = 1e9

We still generate only 36 numbers.

------------------------------------------------------------
Time Complexity

There are at most 36 sequential numbers.

Time = O(36)

which is effectively

O(1)

------------------------------------------------------------
Space Complexity

O(1)

(excluding the output array)

------------------------------------------------------------
*/
