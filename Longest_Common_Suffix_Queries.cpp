// 3093. Longest Common Suffix Queries
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given two arrays of strings wordsContainer and wordsQuery.

// For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.

// Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].

 

// Example 1:

// Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]

// Output: [1,1,1]

// Explanation:

// Let's look at each wordsQuery[i] separately:

// For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// Example 2:

// Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]

// Output: [2,0,2]

// Explanation:

// Let's look at each wordsQuery[i] separately:

// For wordsQuery[0] = "gh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
// For wordsQuery[1] = "acbfgh", only the string at index 0 shares the longest common suffix "fgh". Hence it is the answer, even though the string at index 2 is shorter.
// For wordsQuery[2] = "acbfegh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
 

// Constraints:

// 1 <= wordsContainer.length, wordsQuery.length <= 104
// 1 <= wordsContainer[i].length <= 5 * 103
// 1 <= wordsQuery[i].length <= 5 * 103
// wordsContainer[i] consists only of lowercase English letters.
// wordsQuery[i] consists only of lowercase English letters.
// Sum of wordsContainer[i].length is at most 5 * 105.
// Sum of wordsQuery[i].length is at most 5 * 105.

class Solution {
public:

    /*
    Each trie node stores:

    1. child[26]
       Links to next characters

    2. idx
       Best index answer for this suffix

    3. len
       Length of the shortest string
       passing through this node
    */
    struct Node {

        int child[26];

        int idx;

        int len;


        /*
        Initialize all children as absent (-1)

        idx = -1 initially

        len = very large value
        */
        Node() {

            memset(child, -1, sizeof(child));

            idx = -1;

            len = INT_MAX;
        }
    };


    /*
    Trie container

    We use vector instead of pointers
    to reduce memory usage.
    */
    vector<Node> trie;


    /*
    Update the best answer stored at a trie node.

    Rules:
    - Smaller string length is preferred
    - If lengths are equal,
      earlier index automatically stays
      because we process left to right.
    */
    void update(int node, int idx, int len) {

        if (len < trie[node].len) {

            trie[node].len = len;

            trie[node].idx = idx;
        }
    }


    vector<int> stringIndices(vector<string>& wordsContainer,
                              vector<string>& wordsQuery) {

        /*
        Create root node.
        */
        trie.push_back(Node());


        /*
        =====================================================
        BUILD REVERSED TRIE
        =====================================================

        Since we need longest common SUFFIX,
        we insert strings in reverse order.

        Example:
        "abcd"

        Insert:
        d -> c -> b -> a
        */
        for (int i = 0; i < wordsContainer.size(); i++) {

            string s = wordsContainer[i];

            int len = s.size();

            int node = 0;


            /*
            Root node should also store
            the globally best string.

            This handles cases where
            no suffix matches at all.
            */
            update(node, i, len);


            /*
            Insert characters from end to start.
            */
            for (int j = s.size() - 1; j >= 0; j--) {

                int c = s[j] - 'a';


                /*
                Create new trie node if needed.
                */
                if (trie[node].child[c] == -1) {

                    trie[node].child[c] = trie.size();

                    trie.push_back(Node());
                }


                /*
                Move to next node.
                */
                node = trie[node].child[c];


                /*
                Update best answer for this suffix path.
                */
                update(node, i, len);
            }
        }


        /*
        Store final answers.
        */
        vector<int> ans;


        /*
        =====================================================
        PROCESS EACH QUERY
        =====================================================
        */
        for (string &s : wordsQuery) {

            int node = 0;


            /*
            Traverse query in reverse order
            to match suffixes.
            */
            for (int j = s.size() - 1; j >= 0; j--) {

                int c = s[j] - 'a';


                /*
                If path does not exist,
                stop traversal.

                Current node already contains
                the best possible answer.
                */
                if (trie[node].child[c] == -1) {

                    break;
                }


                /*
                Move deeper into trie.
                */
                node = trie[node].child[c];
            }


            /*
            Best matching index for this query.
            */
            ans.push_back(trie[node].idx);
        }


        return ans;
    }
};

// Time Complexity
// O(total length of wordsContainer + total length of wordsQuery)
// Each character is inserted once into the trie.
// Each query character is traversed once.
// Space Complexity
// O(total length of wordsContainer)
// Trie stores at most one node per inserted character.
