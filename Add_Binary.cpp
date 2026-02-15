// 67. Add Binary
// Easy
// Topics
// premium lock icon
// Companies
// Given two binary strings a and b, return their sum as a binary string.

 

// Example 1:

// Input: a = "11", b = "1"
// Output: "100"
// Example 2:

// Input: a = "1010", b = "1011"
// Output: "10101"
 

// Constraints:

// 1 <= a.length, b.length <= 104
// a and b consist only of '0' or '1' characters.
// Each string does not contain leading zeros except for the zero itself.

//solu=
class Solution {
public:
    string addBinary(string a, string b) {
        // Start from the last characters of both strings (least significant bits)
        int i = a.size() - 1;
        int j = b.size() - 1;

        // This will store the carry generated during addition
        int carry = 0;

        // This string will store the result in reverse order initially
        string res;

        // Continue until both strings are processed and no carry is left
        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;

            // If there are still bits left in string a, add them
            if (i >= 0) {
                sum += a[i] - '0';
                i--;
            }

            // If there are still bits left in string b, add them
            if (j >= 0) {
                sum += b[j] - '0';
                j--;
            }

            // The current binary digit is sum % 2
            res.push_back((sum % 2) + '0');

            // Update carry for the next iteration
            carry = sum / 2;
        }

        // The result is built in reverse, so reverse it before returning
        reverse(res.begin(), res.end());
        return res;
    }
};


//tc = O(n)
//sc= O(n)
