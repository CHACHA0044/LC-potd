// 1331. Rank Transform of an Array
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// Given an array of integers arr, replace each element with its rank.

// The rank represents how large the element is. The rank has the following rules:

// Rank is an integer starting from 1.
// The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
// Rank should be as small as possible.
 

// Example 1:

// Input: arr = [40,10,20,30]
// Output: [4,1,2,3]
// Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.
// Example 2:

// Input: arr = [100,100,100]
// Output: [1,1,1]
// Explanation: Same elements share the same rank.
// Example 3:

// Input: arr = [37,12,28,9,100,56,80,5,12]
// Output: [5,3,4,2,8,6,7,1,3]
 

// Constraints:

// 0 <= arr.length <= 105
// -109 <= arr[i] <= 109
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {

        // ------------------------------------------------------------
        // Step 1:
        // Make a copy of the original array.
        //
        // We will sort this copy to determine the rank of every
        // distinct number without changing the original order.
        // ------------------------------------------------------------
        vector<int> sorted = arr;

        sort(sorted.begin(), sorted.end());

        // ------------------------------------------------------------
        // Step 2:
        // Assign ranks to every unique element.
        //
        // Since the array is sorted:
        // - Smaller numbers appear first.
        // - Equal numbers appear together.
        //
        // Rank starts from 1.
        // ------------------------------------------------------------
        unordered_map<int, int> rank;

        int curRank = 1;

        for (int x : sorted) {

            // Assign a rank only the first time we see a value.
            if (!rank.count(x))
                rank[x] = curRank++;
        }

        // ------------------------------------------------------------
        // Step 3:
        // Replace every element in the original array
        // with its corresponding rank.
        // ------------------------------------------------------------
        vector<int> ans;

        for (int x : arr)
            ans.push_back(rank[x]);

        return ans;
    }
};
// Complexity Analysis
// Time Complexity
// Copy array: O(n)
// Sort array: O(n log n)
// Assign ranks: O(n)
// Build answer: O(n)
// Overall:
// O(n log n)
// Space Complexity
// Copy of array: O(n)
// Hash map: O(n)
// Answer array: O(n)
// Overall:
// O(n)
