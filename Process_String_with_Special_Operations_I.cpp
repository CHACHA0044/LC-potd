// 3612. Process String with Special Operations I
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s consisting of lowercase English letters and the special characters: *, #, and %.

// Build a new string result by processing s according to the following rules from left to right:

// If the letter is a lowercase English letter append it to result.
// A '*' removes the last character from result, if it exists.
// A '#' duplicates the current result and appends it to itself.
// A '%' reverses the current result.
// Return the final string result after processing all characters in s.

 

// Example 1:

// Input: s = "a#b%*"

// Output: "ba"

// Explanation:

// i	s[i]	Operation	Current result
// 0	'a'	Append 'a'	"a"
// 1	'#'	Duplicate result	"aa"
// 2	'b'	Append 'b'	"aab"
// 3	'%'	Reverse result	"baa"
// 4	'*'	Remove the last character	"ba"
// Thus, the final result is "ba".

// Example 2:

// Input: s = "z*#"

// Output: ""

// Explanation:

// i	s[i]	Operation	Current result
// 0	'z'	Append 'z'	"z"
// 1	'*'	Remove the last character	""
// 2	'#'	Duplicate the string	""
// Thus, the final result is "".

 

// Constraints:

// 1 <= s.length <= 20
// s consists of only lowercase English letters and special characters *, #, and %.
class Solution {
public:
    string processStr(string s) {

        /*
        Stores the string being built
        after processing each character.
        */
        string result;

        for (char ch : s) {

            /*
            Lowercase letter:
            append it to the result.
            */
            if (ch >= 'a' && ch <= 'z') {
                result.push_back(ch);
            }

            /*
            '*' operation:
            remove the last character
            if the result is not empty.
            */
            else if (ch == '*') {
                if (!result.empty()) {
                    result.pop_back();
                }
            }

            /*
            '#' operation:
            duplicate the current result
            and append it to itself.

            Example:
            "abc" -> "abcabc"
            */
            else if (ch == '#') {
                result += result;
            }

            /*
            '%' operation:
            reverse the entire string.

            Example:
            "abcd" -> "dcba"
            */
            else {
                reverse(result.begin(), result.end());
            }
        }

        return result;
    }
};

/*
Time Complexity: O(n * m)

n = length of s (<= 20)
m = current length of result

Since n <= 20, this is easily efficient.

Space Complexity: O(m)

m = length of final result
*/
