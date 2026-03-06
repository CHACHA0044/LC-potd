// 1784. Check if Binary String Has at Most One Segment of Ones
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given a binary string s ​​​​​without leading zeros, return true​​​ if s contains at most one contiguous segment of ones. Otherwise, return false.

 

// Example 1:

// Input: s = "1001"
// Output: false
// Explanation: The ones do not form a contiguous segment.
// Example 2:

// Input: s = "110"
// Output: true
 

// Constraints:

// 1 <= s.length <= 100
// s[i]​​​​ is either '0' or '1'.
// s[0] is '1'.
//solu =
class Solution {
public:
    bool checkOnesSegment(string s) {
        
        /*
        The string starts with '1' (given in constraints).

        If the string contains more than one segment of '1's,
        it must look like this pattern:

        111...000...111

        That means we will encounter the substring "01"
        and then later another '1'.

        However, the simple observation is:
        If "01" appears, the first segment of 1s has ended.
        If the string continues after that with '1',
        it means a second segment exists.

        Therefore, the string should NOT contain "01".
        */

        return s.find("01") == string::npos;
    }
};
//tc = O(n)
//sc = O(1)
