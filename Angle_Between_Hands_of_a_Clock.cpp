// 1344. Angle Between Hands of a Clock
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given two numbers, hour and minutes, return the smaller angle (in degrees) formed between the hour and the minute hand.

// Answers within 10-5 of the actual value will be accepted as correct.

 

// Example 1:


// Input: hour = 12, minutes = 30
// Output: 165
// Example 2:


// Input: hour = 3, minutes = 30
// Output: 75
// Example 3:


// Input: hour = 3, minutes = 15
// Output: 7.5
 

// Constraints:

// 1 <= hour <= 12
// 0 <= minutes <= 59
class Solution {
public:
    double angleClock(int hour, int minutes) {

        /*
        Minute hand moves:

        360 degrees in 60 minutes

        => 6 degrees per minute
        */
        double minuteAngle = minutes * 6.0;


        /*
        Hour hand moves:

        360 degrees in 12 hours

        => 30 degrees per hour

        It also moves continuously as minutes pass:

        => 0.5 degrees per minute
        */
        double hourAngle = (hour % 12) * 30.0 + minutes * 0.5;


        /*
        Angle between the two hands.
        */
        double angle = abs(hourAngle - minuteAngle);


        /*
        Return the smaller angle.

        Example:
        If angle = 270,
        smaller angle = 360 - 270 = 90.
        */
        return min(angle, 360.0 - angle);
    }
};

/*
Time Complexity: O(1)

Space Complexity: O(1)
*/
