// 61. Rotate List
// Medium
// Topics
// premium lock icon
// Companies
// Given the head of a linked list, rotate the list to the right by k places.

 

// Example 1:


// Input: head = [1,2,3,4,5], k = 2
// Output: [4,5,1,2,3]
// Example 2:


// Input: head = [0,1,2], k = 4
// Output: [2,0,1]
 

// Constraints:

// The number of nodes in the list is in the range [0, 500].
// -100 <= Node.val <= 100
// 0 <= k <= 2 * 109
// sol=
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        
        // Edge cases: empty list or single node
        if (!head || !head->next || k == 0)
            return head;


        /*
        STEP 1: Find length of list
        and get the tail node
        */
        int n = 1;  // start from 1 because head exists
        ListNode* tail = head;

        while (tail->next) {
            tail = tail->next;
            n++;
        }


        /*
        STEP 2: Make the list circular
        
        tail → head
        */
        tail->next = head;


        /*
        STEP 3: Reduce k
        
        Rotating n times gives same list
        */
        k = k % n;


        /*
        STEP 4: Find new tail
        
        New tail is at:
        (n - k - 1) steps from head
        
        Why?
        Because last k nodes will come to front
        */
        int steps = n - k;

        ListNode* newTail = head;

        for (int i = 1; i < steps; i++) {
            newTail = newTail->next;
        }


        /*
        STEP 5: Set new head
        
        Next of newTail becomes new head
        */
        ListNode* newHead = newTail->next;


        /*
        STEP 6: Break the circle
        */
        newTail->next = NULL;


        return newHead;
    }
};
// Time:
// O(n)
// Space:
// O(1)
// Pattern
// Linked list rotation → make circular + break
