// 1980. Find Unique Binary String
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.

 

// Example 1:

// Input: nums = ["01","10"]
// Output: "11"
// Explanation: "11" does not appear in nums. "00" would also be correct.
// Example 2:

// Input: nums = ["00","01"]
// Output: "11"
// Explanation: "11" does not appear in nums. "10" would also be correct.
// Example 3:

// Input: nums = ["111","011","001"]
// Output: "101"
// Explanation: "101" does not appear in nums. "000", "010", "100", and "110" would also be correct.
 

// Constraints:

// n == nums.length
// 1 <= n <= 16
// nums[i].length == n
// nums[i] is either '0' or '1'.

//solu=
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        
        int n = nums.size();
        string result = "";
        
        /*
        We construct the result using Cantor's Diagonalization:
        
        For each i:
        - Look at nums[i][i]
        - Flip the bit
        
        This guarantees the new string differs from nums[i]
        at position i, so it cannot be equal to nums[i].
        */
        
        for(int i = 0; i < n; i++) {
            
            if(nums[i][i] == '0')
                result += '1';
            else
                result += '0';
        }
        
        return result;
    }
};
//tc = O(n)
//sc = O(n)
// All the strings of nums are unique.
