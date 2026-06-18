// 3614. Process String with Special Operations II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s consisting of lowercase English letters and the special characters: '*', '#', and '%'.

// You are also given an integer k.

// Build a new string result by processing s according to the following rules from left to right:

// If the letter is a lowercase English letter append it to result.
// A '*' removes the last character from result, if it exists.
// A '#' duplicates the current result and appends it to itself.
// A '%' reverses the current result.
// Return the kth character of the final string result. If k is out of the bounds of result, return '.'.

 

// Example 1:

// Input: s = "a#b%*", k = 1

// Output: "a"

// Explanation:

// i	s[i]	Operation	Current result
// 0	'a'	Append 'a'	"a"
// 1	'#'	Duplicate result	"aa"
// 2	'b'	Append 'b'	"aab"
// 3	'%'	Reverse result	"baa"
// 4	'*'	Remove the last character	"ba"
// The final result is "ba". The character at index k = 1 is 'a'.

// Example 2:

// Input: s = "cd%#*#", k = 3

// Output: "d"

// Explanation:

// i	s[i]	Operation	Current result
// 0	'c'	Append 'c'	"c"
// 1	'd'	Append 'd'	"cd"
// 2	'%'	Reverse result	"dc"
// 3	'#'	Duplicate result	"dcdc"
// 4	'*'	Remove the last character	"dcd"
// 5	'#'	Duplicate result	"dcddcd"
// The final result is "dcddcd". The character at index k = 3 is 'd'.

// Example 3:

// Input: s = "z*#", k = 0

// Output: "."

// Explanation:

// i	s[i]	Operation	Current result
// 0	'z'	Append 'z'	"z"
// 1	'*'	Remove the last character	""
// 2	'#'	Duplicate the string	""
// The final result is "". Since index k = 0 is out of bounds, the output is '.'.

 

// Constraints:

// 1 <= s.length <= 105
// s consists of only lowercase English letters and special characters '*', '#', and '%'.
// 0 <= k <= 1015
// The length of result after processing s will not exceed 1015.
class Solution {
public:
    char processStr(string s, long long k) {

        int n = s.size();

        /*
        len[i] = length of the generated string
        after processing first i characters.
        */
        vector<long long> len(n + 1, 0);

        const long long LIM = 1e15 + 5;

        /*
        Build only the lengths.
        Never build the actual string.
        */
        for (int i = 0; i < n; i++) {

            char ch = s[i];

            /*
            Append one character.
            */
            if ('a' <= ch && ch <= 'z') {
                len[i + 1] = min(LIM, len[i] + 1);
            }

            /*
            Remove last character if present.
            */
            else if (ch == '*') {
                len[i + 1] = max(0LL, len[i] - 1);
            }

            /*
            Duplicate current string.
            */
            else if (ch == '#') {
                len[i + 1] = min(LIM, len[i] * 2);
            }

            /*
            Reverse keeps length unchanged.
            */
            else {
                len[i + 1] = len[i];
            }
        }

        /*
        k is outside the final string.
        */
        if (k >= len[n]) {
            return '.';
        }

        /*
        Walk backwards and determine
        where index k came from.
        */
        for (int i = n - 1; i >= 0; i--) {

            char ch = s[i];

            /*
            Letter appended at position len[i].

            If k equals that position,
            we found the answer.
            */
            if ('a' <= ch && ch <= 'z') {

                if (k == len[i]) {
                    return ch;
                }
            }

            /*
            Before duplication:

            X -> X + X

            If k lies in the second half,
            map it back into the first half.
            */
            else if (ch == '#') {

                long long oldLen = len[i];

                if (k >= oldLen) {
                    k -= oldLen;
                }
            }

            /*
            Before reversal:

            position k came from

            oldLen - 1 - k
            */
            else if (ch == '%') {

                long long oldLen = len[i];

                k = oldLen - 1 - k;
            }

            /*
            For '*', all surviving positions
            remain unchanged when moving
            backward, so nothing to do.
            */
        }

        return '.';
    }
};

/*
Time Complexity: O(n)

Space Complexity: O(n)
*/
