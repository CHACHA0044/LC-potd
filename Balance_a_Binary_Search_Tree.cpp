// 1382. Balance a Binary Search Tree
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// Given the root of a binary search tree, return a balanced binary search tree with the same node values. If there is more than one answer, return any of them.

// A binary search tree is balanced if the depth of the two subtrees of every node never differs by more than 1.

 

// Example 1:


// Input: root = [1,null,2,null,3,null,4,null,null]
// Output: [2,1,3,null,null,null,4]
// Explanation: This is not the only correct answer, [3,1,4,null,2] is also correct.
// Example 2:


// Input: root = [2,1,3]
// Output: [2,1,3]
 

// Constraints:

// The number of nodes in the tree is in the range [1, 104].
// 1 <= Node.val <= 105

//solu= 
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    void inorder(TreeNode* root, vector<int>& values) {
        // If the current node is null, there is nothing to process.
        // We simply return to stop this recursive path.
        if (root == nullptr) {
            return;
        }

        // First, recursively traverse the left subtree.
        // This ensures we visit smaller values first in a BST.
        inorder(root->left, values);

        // After finishing the left subtree, we record the value
        // of the current node. This keeps values in sorted order.
        values.push_back(root->val);

        // Finally, recursively traverse the right subtree,
        // which contains values larger than the current node.
        inorder(root->right, values);
    }

    TreeNode* buildBalancedBST(vector<int>& values, int left, int right) {
        // If the left index goes beyond the right index,
        // it means there are no elements left to form a subtree.
        // In this case, we return null.
        if (left > right) {
            return nullptr;
        }

        // We choose the middle element of the current range.
        // This element becomes the root to keep the tree balanced.
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(values[mid]);

        // All elements to the left of mid form the left subtree.
        // We recursively build a balanced subtree from them.
        root->left = buildBalancedBST(values, left, mid - 1);

        // All elements to the right of mid form the right subtree.
        // We recursively build a balanced subtree from them.
        root->right = buildBalancedBST(values, mid + 1, right);

        // Once both subtrees are attached, we return the root node.
        return root;
    }

    TreeNode* balanceBST(TreeNode* root) {
        // This vector will store all the values from the BST
        // in sorted order using inorder traversal.
        vector<int> values;

        // We perform inorder traversal to flatten the BST
        // into a sorted list of values.
        inorder(root, values);

        // Using the sorted values, we rebuild a balanced BST
        // by always choosing the middle element as the root.
        return buildBalancedBST(values, 0, values.size() - 1);
    }
};

//tc= O(n)
//sc= O(n)
