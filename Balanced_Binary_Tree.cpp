// 110. Balanced Binary Tree
// Solved
// Easy
// Topics
// premium lock icon
// Companies
// Given a binary tree, determine if it is height-balanced.

 

// Example 1:


// Input: root = [3,9,20,null,null,15,7]
// Output: true
// Example 2:


// Input: root = [1,2,2,3,3,null,null,4,4]
// Output: false
// Example 3:

// Input: root = []
// Output: true
 

// Constraints:

// The number of nodes in the tree is in the range [0, 5000].
// -104 <= Node.val <= 104

//solu=

class Solution {
public:
    int height(TreeNode* root) {
        // If the current node is null, it means we have reached
        // beyond a leaf node. The height of an empty subtree is 0.
        if (root == nullptr) {
            return 0;
        }

        // Recursively calculate the height of the left subtree.
        // This call will also detect if the left subtree is unbalanced.
        int leftHeight = height(root->left);

        // If the left subtree is already unbalanced, there is no need
        // to continue further. We immediately return -1 to propagate
        // the imbalance upward.
        if (leftHeight == -1) {
            return -1;
        }

        // Recursively calculate the height of the right subtree.
        // Just like the left side, this also checks for imbalance.
        int rightHeight = height(root->right);

        // If the right subtree is unbalanced, we again stop processing
        // and return -1 so that higher calls know the tree is not balanced.
        if (rightHeight == -1) {
            return -1;
        }

        // At this node, we compare the heights of the left and right subtrees.
        // If their difference is more than 1, the tree violates the
        // height-balanced condition.
        if (abs(leftHeight - rightHeight) > 1) {
            return -1;
        }

        // If the current node is balanced, we return its height.
        // Height is defined as the maximum of the left and right subtree
        // heights plus one for the current node itself.
        return max(leftHeight, rightHeight) + 1;
    }

    bool isBalanced(TreeNode* root) {
        // The tree is balanced if the height function does not return -1.
        // A return value of -1 means an imbalance was detected somewhere.
        return height(root) != -1;
    }
};

//tc= O(n)
//sc= O(h)
