// 401. Binary Watch
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// A binary watch has 4 LEDs on the top to represent the hours (0-11), and 6 LEDs on the bottom to represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on the right.

// For example, the below binary watch reads "4:51".


// Given an integer turnedOn which represents the number of LEDs that are currently on (ignoring the PM), return all possible times the watch could represent. You may return the answer in any order.

// The hour must not contain a leading zero.

// For example, "01:00" is not valid. It should be "1:00".
// The minute must consist of two digits and may contain a leading zero.

// For example, "10:2" is not valid. It should be "10:02".
 

// Example 1:

// Input: turnedOn = 1
// Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
// Example 2:

// Input: turnedOn = 9
// Output: []
 

// Constraints:

// 0 <= turnedOn <= 10

//solu=
class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> result;

        // Iterate through all possible hours (0 to 11)
        for (int h = 0; h < 12; h++) {

            // Iterate through all possible minutes (0 to 59)
            for (int m = 0; m < 60; m++) {

                // Count total number of LEDs that are ON
                // __builtin_popcount counts number of 1-bits in an integer
                int totalBits = __builtin_popcount(h) + __builtin_popcount(m);

                // If total LEDs ON equals the given turnedOn value
                if (totalBits == turnedOn) {

                    // Format the time string properly
                    // Hour should not have leading zero
                    string time = to_string(h) + ":";

                    // Minute must always be two digits
                    if (m < 10)
                        time += "0";

                    time += to_string(m);

                    // Add the valid time to the result list
                    result.push_back(time);
                }
            }
        }
        return result;
    }
};

//tc = O(710) -> O(1)
//sc = depends upon no of valid outputs
