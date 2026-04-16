// 3488. Closest Equal Element Queries
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a circular array nums and an array queries.

// For each query i, you have to find the following:

// The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
// Return an array answer of the same size as queries, where answer[i] represents the result for query i.

 

// Example 1:

// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]

// Output: [2,-1,3]

// Explanation:

// Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
// Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
// Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
// Example 2:

// Input: nums = [1,2,3,4], queries = [0,1,2,3]

// Output: [-1,-1,-1,-1]

// Explanation:

// Each value in nums is unique, so no index shares the same value as the queried element. This results in -1 for all queries.

 

// Constraints:

// 1 <= queries.length <= nums.length <= 105
// 1 <= nums[i] <= 106
// solu =
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        
        int n = nums.size();

        unordered_map<int, vector<int>> positions;

        
        // Store all indices for every value
        // Example:
        // nums = [1,3,1,4,1]
        // positions[1] = [0,2,4]
        for (int i = 0; i < n; i++) {
            positions[nums[i]].push_back(i);
        }

        
        vector<int> answer;

        
        // Process every query independently
        for (int queryIndex : queries) {

            int value = nums[queryIndex];

            
            // All indices where this value occurs
            vector<int>& samePositions = positions[value];

            
            // If value appears only once,
            // no other equal element exists
            if (samePositions.size() == 1) {
                answer.push_back(-1);
                continue;
            }

            
            // Find current query index position inside sorted occurrence list
            int pos = lower_bound(
                samePositions.begin(),
                samePositions.end(),
                queryIndex
            ) - samePositions.begin();

            
            // Previous occurrence in circular occurrence list
            int prevIndex = samePositions[
                (pos - 1 + samePositions.size()) % samePositions.size()
            ];

            
            // Next occurrence in circular occurrence list
            int nextIndex = samePositions[
                (pos + 1) % samePositions.size()
            ];

            
            // Distance if moving directly to previous/next occurrence
            int distPrev = abs(queryIndex - prevIndex);
            int distNext = abs(queryIndex - nextIndex);

            
            // Since array is circular,
            // shortest circular distance between two indices is:
            // min(direct distance, wrap-around distance)
            distPrev = min(distPrev, n - distPrev);
            distNext = min(distNext, n - distNext);

            
            // Minimum among nearest previous and next equal element
            answer.push_back(min(distPrev, distNext));
        }

        
        return answer;
    }
};

// Time Complexity
// Preprocessing Positions Map
// O(n)
// Each Query
// lower_bound on occurrence list:
// O(log k)
// where k = frequency of that number
// Total
// O(n + q log n)
// Space Complexity
// O(n)
// HashMap stores all indices
// // 0 <= queries[i] < nums.length
