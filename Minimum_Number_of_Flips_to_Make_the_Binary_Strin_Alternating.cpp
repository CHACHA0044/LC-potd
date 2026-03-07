// 1888. Minimum Number of Flips to Make the Binary String Alternating
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:

// Type-1: Remove the character at the start of the string s and append it to the end of the string.
// Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
// Return the minimum number of type-2 operations you need to perform such that s becomes alternating.

// The string is called alternating if no two adjacent characters are equal.

// For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
 

// Example 1:

// Input: s = "111000"
// Output: 2
// Explanation: Use the first operation two times to make s = "100011".
// Then, use the second operation on the third and sixth elements to make s = "101010".
// Example 2:

// Input: s = "010"
// Output: 0
// Explanation: The string is already alternating.
// Example 3:

// Input: s = "1110"
// Output: 1
// Explanation: Use the second operation on the second element to make s = "1010".
 

// Constraints:

// 1 <= s.length <= 105
// s[i] is either '0' or '1'.

//solu=
class Solution {
public:
    int minFlips(string s) {
        
        int n = s.size();
        
        /*
        To simulate all rotations efficiently,
        we double the string. Every rotation of s
        will appear as a substring of length n in s+s.
        */
        string s2 = s + s;
        
        /*
        Build the two alternating target patterns
        for length 2n:
        
        pattern1: 010101...
        pattern2: 101010...
        */
        string pattern1 = "", pattern2 = "";
        
        for(int i = 0; i < 2*n; i++) {
            if(i % 2 == 0) {
                pattern1 += '0';
                pattern2 += '1';
            } else {
                pattern1 += '1';
                pattern2 += '0';
            }
        }
        
        int diff1 = 0; // mismatches with pattern1
        int diff2 = 0; // mismatches with pattern2
        
        int left = 0;
        int result = INT_MAX;
        
        /*
        Sliding window of size n over s2.
        Each window represents a possible rotation.
        */
        for(int right = 0; right < 2*n; right++) {
            
            // Add the new character to mismatch counts
            if(s2[right] != pattern1[right])
                diff1++;
            
            if(s2[right] != pattern2[right])
                diff2++;
            
            
            /*
            If window becomes larger than n,
            remove the leftmost character from counts.
            */
            if(right - left + 1 > n) {
                
                if(s2[left] != pattern1[left])
                    diff1--;
                
                if(s2[left] != pattern2[left])
                    diff2--;
                
                left++;
            }
            
            
            /*
            Once the window size is exactly n,
            compute the minimum flips needed.
            */
            if(right - left + 1 == n) {
                result = min(result, min(diff1, diff2));
            }
        }
        
        return result;
    }
};
//tc = O(n)
//sc = O(n)
