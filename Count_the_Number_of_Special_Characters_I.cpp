// 3120. Count the Number of Special Characters I
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.

// Return the number of special letters in word.

 

// Example 1:

// Input: word = "aaAbcBC"

// Output: 3

// Explanation:

// The special characters in word are 'a', 'b', and 'c'.

// Example 2:

// Input: word = "abc"

// Output: 0

// Explanation:

// No character in word appears in uppercase.

// Example 3:

// Input: word = "abBCab"

// Output: 1

// Explanation:

// The only special character in word is 'b'.

 

// Constraints:

// 1 <= word.length <= 50
// word consists of only lowercase and uppercase English letters.
class Solution {
public:
    int numberOfSpecialChars(string word) {

        /*
        Store all lowercase letters seen.
        */
        unordered_set<char> lower;


        /*
        Store all uppercase letters seen.
        */
        unordered_set<char> upper;


        /*
        Traverse the string and separate
        lowercase and uppercase letters.
        */
        for (char ch : word) {

            if (islower(ch)) {
                lower.insert(ch);
            }
            else {
                upper.insert(ch);
            }
        }


        /*
        Count letters that appear in both forms.

        Example:
        'a' in lower
        'A' in upper

        => special character
        */
        int count = 0;

        for (char ch = 'a'; ch <= 'z'; ch++) {

            if (lower.count(ch) &&
                upper.count(toupper(ch))) {

                count++;
            }
        }


        return count;
    }
};
// Time Complexity
// O(n)
// Traversing the string takes O(n).
// Checking all 26 letters is O(26) = constant.
// Space Complexity
// O(1)
// At most 26 lowercase and 26 uppercase letters are stored.
