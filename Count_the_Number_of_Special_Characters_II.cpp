// 3121. Count the Number of Special Characters II
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.

// Return the number of special letters in word.

 

// Example 1:

// Input: word = "aaAbcBC"

// Output: 3

// Explanation:

// The special characters are 'a', 'b', and 'c'.

// Example 2:

// Input: word = "abc"

// Output: 0

// Explanation:

// There are no special characters in word.

// Example 3:

// Input: word = "AbBCab"

// Output: 0

// Explanation:

// There are no special characters in word.

 

// Constraints:

// 1 <= word.length <= 2 * 105
// word consists of only lowercase and uppercase English letters.
class Solution {
public:
    int numberOfSpecialChars(string word) {

        /*
        firstUpper[i] =
        first occurrence index of uppercase letter

        lastLower[i] =
        last occurrence index of lowercase letter

        i represents:
        0 -> 'a'
        1 -> 'b'
        ...
        25 -> 'z'
        */
        vector<int> firstUpper(26, -1);
        vector<int> lastLower(26, -1);


        /*
        ----------------------------------------------------
        Traverse the string
        ----------------------------------------------------
        */
        for (int i = 0; i < word.size(); i++) {

            char ch = word[i];


            /*
            Lowercase letter

            Store latest occurrence index.
            */
            if (islower(ch)) {

                lastLower[ch - 'a'] = i;
            }


            /*
            Uppercase letter

            Store FIRST occurrence only.
            */
            else {

                int idx = ch - 'A';

                if (firstUpper[idx] == -1) {
                    firstUpper[idx] = i;
                }
            }
        }


        /*
        ----------------------------------------------------
        A character is special if:

        1. Lowercase exists
        2. Uppercase exists
        3. Every lowercase appears BEFORE
           first uppercase

        Which means:
            lastLower < firstUpper
        ----------------------------------------------------
        */
        int count = 0;

        for (int i = 0; i < 26; i++) {

            if (lastLower[i] != -1 &&
                firstUpper[i] != -1 &&
                lastLower[i] < firstUpper[i]) {

                count++;
            }
        }


        return count;
    }
};
// Time Complexity
// O(n)
// One traversal of the string
// One loop over 26 characters
// Space Complexity
// O(1)
// Only fixed-size arrays of length 26 are used.
