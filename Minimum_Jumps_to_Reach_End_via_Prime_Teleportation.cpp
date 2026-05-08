// 3629. Minimum Jumps to Reach End via Prime Teleportation
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given an integer array nums of length n.

// You start at index 0, and your goal is to reach index n - 1.

// From any index i, you may perform one of the following operations:

// Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
// Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] % p == 0.
// Return the minimum number of jumps required to reach index n - 1.

 

// Example 1:

// Input: nums = [1,2,4,6]

// Output: 2

// Explanation:

// One optimal sequence of jumps is:

// Start at index i = 0. Take an adjacent step to index 1.
// At index i = 1, nums[1] = 2 is a prime number. Therefore, we teleport to index i = 3 as nums[3] = 6 is divisible by 2.
// Thus, the answer is 2.

// Example 2:

// Input: nums = [2,3,4,7,9]

// Output: 2

// Explanation:

// One optimal sequence of jumps is:

// Start at index i = 0. Take an adjacent step to index i = 1.
// At index i = 1, nums[1] = 3 is a prime number. Therefore, we teleport to index i = 4 since nums[4] = 9 is divisible by 3.
// Thus, the answer is 2.

// Example 3:

// Input: nums = [4,6,5,8]

// Output: 3

// Explanation:

// Since no teleportation is possible, we move through 0 → 1 → 2 → 3. Thus, the answer is 3.
 

// Constraints:

// 1 <= n == nums.length <= 105
// 1 <= nums[i] <= 106
// solu=
class Solution {
public:

    /*
    =========================================================
    Helper Function: Check if a number is prime
    =========================================================

    A prime number:
    - greater than 1
    - divisible only by 1 and itself
    */
    bool isPrime(int x) {

        // 0 and 1 are not prime
        if (x < 2)
            return false;

        /*
        Check divisibility from 2 to sqrt(x)

        If any divisor exists,
        number is not prime.
        */
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0)
                return false;
        }

        return true;
    }


    int minJumps(vector<int>& nums) {

        int n = nums.size();

        
        /*
        If already at last index,
        no jumps needed.
        */
        if (n == 1)
            return 0;


        /*
        =========================================================
        STEP 1: Build Map for Prime Teleportation
        =========================================================

        For every PRIME p appearing in nums,
        store all indices j where:

            nums[j] % p == 0

        Example:
        nums = [1,2,4,6]

        prime = 2

        divisible indices:
        [1,2,3]
        */
        unordered_map<int, vector<int>> divisibleIndices;

for (int i = 0; i < n; i++) {

    int x = nums[i];

    /*
    Find PRIME FACTORS of nums[i]
    */
    for (int d = 2; d * d <= x; d++) {

        if (x % d == 0) {

            /*
            d is a prime factor
            */
            divisibleIndices[d].push_back(i);

            /*
            Remove all occurrences of d
            */
            while (x % d == 0) {
                x /= d;
            }
        }
    }

    /*
    Remaining x > 1 means
    it itself is prime
    */
    if (x > 1) {
        divisibleIndices[x].push_back(i);
    }
}


        /*
        =========================================================
        STEP 2: BFS for Minimum Jumps
        =========================================================

        This is an unweighted graph problem.

        Each move costs 1:
        - adjacent move
        - teleport move

        BFS guarantees shortest path.
        */
        queue<pair<int,int>> q;

        /*
        visited[i] = whether index i
        was already processed
        */
        vector<bool> visited(n, false);


        /*
        Start BFS from index 0
        with 0 jumps used.
        */
        q.push({0, 0});
        visited[0] = true;


        /*
        To avoid reprocessing same prime teleport
        many times.

        Once teleportation for a prime is used,
        clear it forever.
        */
        unordered_set<int> usedPrime;


        while (!q.empty()) {

            auto [i, steps] = q.front();
            q.pop();


            /*
            Reached destination
            */
            if (i == n - 1)
                return steps;


            /*
            =====================================================
            OPTION 1: Move Left
            =====================================================
            */
            if (i - 1 >= 0 && !visited[i - 1]) {

                visited[i - 1] = true;

                q.push({i - 1, steps + 1});
            }


            /*
            =====================================================
            OPTION 2: Move Right
            =====================================================
            */
            if (i + 1 < n && !visited[i + 1]) {

                visited[i + 1] = true;

                q.push({i + 1, steps + 1});
            }


            /*
            =====================================================
            OPTION 3: Prime Teleportation
            =====================================================

            Allowed only if nums[i] itself is prime.
            */
            int val = nums[i];

            if (isPrime(val) && !usedPrime.count(val)) {

                /*
                Jump to every index divisible by val
                */
                for (int nextIndex : divisibleIndices[val]) {

                    if (!visited[nextIndex]) {

                        visited[nextIndex] = true;

                        q.push({nextIndex, steps + 1});
                    }
                }

                /*
                Mark this prime teleport as used.

                Prevents repeated O(n) traversals.
                */
                usedPrime.insert(val);
            }
        }


        /*
        Problem guarantees reachable answer,
        but return -1 for safety.
        */
        return -1;
    }
};
// Time Complexity
// Building prime factor mappings:
// O(n × √max(nums))
// BFS traversal:
// O(n + teleport_edges)
// Overall:
// O(n × √max(nums))
  
// Space Complexity
// Used for:
// teleport map
// visited array
// queue
// Overall:
// O(n + teleport_edges)
// Approximately:
// O(n)
