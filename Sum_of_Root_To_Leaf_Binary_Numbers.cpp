// 1022. Sum of Root To Leaf Binary Numbers
// Easy
// Topics
// premium lock icon
// Companies
// Hint
// You are given the root of a binary tree where each node has a value 0 or 1. Each root-to-leaf path represents a binary number starting with the most significant bit.

// For example, if the path is 0 -> 1 -> 1 -> 0 -> 1, then this could represent 01101 in binary, which is 13.
// For all leaves in the tree, consider the numbers represented by the path from the root to that leaf. Return the sum of these numbers.

// The test cases are generated so that the answer fits in a 32-bits integer.

 

// Example 1:


// Input: root = [1,0,1,0,1,0,1]
// Output: 22
// Explanation: (100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
// Example 2:

// Input: root = [0]
// Output: 0
 

// Constraints:

// The number of nodes in the tree is in the range [1, 1000].
// Node.val is 0 or 1.

//solu=
class Solution {
public:
    // Helper DFS function
    // 'currentValue' stores the binary number formed so far
    int dfs(TreeNode* node, int currentValue) {

        // If node is null, there is nothing to contribute
        if (node == nullptr)
            return 0;

        // Shift current value left by 1 (multiply by 2)
        // and add the current node's bit (0 or 1)
        // This builds the binary number step by step
        currentValue = (currentValue << 1) | node->val;

        // If we reach a leaf node, return the formed binary number
        // because this path is complete
        if (node->left == nullptr && node->right == nullptr)
            return currentValue;

        // Recursively calculate the sum from left and right subtrees
        // and return their total
        int leftSum = dfs(node->left, currentValue);
        int rightSum = dfs(node->right, currentValue);

        return leftSum + rightSum;
    }

    int sumRootToLeaf(TreeNode* root) {
        // Start DFS traversal with initial value 0
        return dfs(root, 0);
    }
};
//tc= O(n)
//sc= O(h)
