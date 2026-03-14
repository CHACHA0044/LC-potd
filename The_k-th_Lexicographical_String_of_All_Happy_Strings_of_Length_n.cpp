// 1415. The k-th Lexicographical String of All Happy Strings of Length n
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// A happy string is a string that:

// consists only of letters of the set ['a', 'b', 'c'].
// s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
// For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

// Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.

// Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

 

// Example 1:

// Input: n = 1, k = 3
// Output: "c"
// Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".
// Example 2:

// Input: n = 1, k = 4
// Output: ""
// Explanation: There are only 3 happy strings of length 1.
// Example 3:

// Input: n = 3, k = 9
// Output: "cab"
// Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"
 

// Constraints:

// 1 <= n <= 10
// 1 <= k <= 100

// solu = 
class Solution {
public:
    // This will store the kth happy string once we find it.
    string answer = "";

    // This keeps track of how many valid happy strings
    // we have generated so far in lexicographical order.
    int count = 0;

    // Backtracking function to build all happy strings of length n
    void backtrack(string &curr, int n, int k) {
        // If we have already found the kth string,
        // no need to continue further recursion.
        if (!answer.empty()) {
            return;
        }

        // Base case:
        // If current string has reached length n,
        // then it is one complete happy string.
        if (curr.length() == n) {
            count++;  // count this valid happy string

            // If this is the kth happy string, save it.
            if (count == k) {
                answer = curr;
            }
            return;
        }

        // Try adding characters in lexicographical order
        // so that generated strings are automatically sorted.
        for (char ch : {'a', 'b', 'c'}) {

            // Happy string condition:
            // current character must not be equal to previous character
            if (!curr.empty() && curr.back() == ch) {
                continue;
            }

            // Choose
            curr.push_back(ch);

            // Explore further
            backtrack(curr, n, k);

            // Undo the choice (backtrack)
            curr.pop_back();
        }
    }

    string getHappyString(int n, int k) {
        // Total number of happy strings of length n:
        // 3 choices for first character
        // 2 choices for every next character
        // => 3 * 2^(n-1)
        int total = 3 * (1 << (n - 1));

        // If k is greater than total possible happy strings,
        // then kth string does not exist.
        if (k > total) {
            return "";
        }

        string curr = "";

        // Start generating happy strings
        backtrack(curr, n, k);

        return answer;
    }
};
// tc = O(3 * 2^(n-1))
// sc = O(n)
// At most, number of happy strings is:
// 3 * 2^(n-1)
// because:
// first position: 3 choices
// every next position: 2 choices

// optimal without generating all string = 
class Solution {
public:
    // This will store the kth happy string once we find it.
    string answer = "";

    // This keeps track of how many valid happy strings
    // we have generated so far in lexicographical order.
    int count = 0;

    // Backtracking function to build all happy strings of length n
    void backtrack(string &curr, int n, int k) {
        // If we have already found the kth string,
        // no need to continue further recursion.
        if (!answer.empty()) {
            return;
        }

        // Base case:
        // If current string has reached length n,
        // then it is one complete happy string.
        if (curr.length() == n) {
            count++;  // count this valid happy string

            // If this is the kth happy string, save it.
            if (count == k) {
                answer = curr;
            }
            return;
        }

        // Try adding characters in lexicographical order
        // so that generated strings are automatically sorted.
        for (char ch : {'a', 'b', 'c'}) {

            // Happy string condition:
            // current character must not be equal to previous character
            if (!curr.empty() && curr.back() == ch) {
                continue;
            }

            // Choose
            curr.push_back(ch);

            // Explore further
            backtrack(curr, n, k);

            // Undo the choice (backtrack)
            curr.pop_back();
        }
    }

    string getHappyString(int n, int k) {
        // Total number of happy strings of length n:
        // 3 choices for first character
        // 2 choices for every next character
        // => 3 * 2^(n-1)
        int total = 3 * (1 << (n - 1));

        // If k is greater than total possible happy strings,
        // then kth string does not exist.
        if (k > total) {
            return "";
        }

        string curr = "";

        // Start generating happy strings
        backtrack(curr, n, k);

        return answer;
    }
};
// tc = O(n)
// sc = O(n)
