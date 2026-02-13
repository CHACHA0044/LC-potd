// 3714. Longest Balanced Substring II
// Solved
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given a string s consisting only of the characters 'a', 'b', and 'c'.

// A substring of s is called balanced if all distinct characters in the substring appear the same number of times.

// Return the length of the longest balanced substring of s.

 

// Example 1:

// Input: s = "abbac"

// Output: 4

// Explanation:

// The longest balanced substring is "abba" because both distinct characters 'a' and 'b' each appear exactly 2 times.

// Example 2:

// Input: s = "aabcc"

// Output: 3

// Explanation:

// The longest balanced substring is "abc" because all distinct characters 'a', 'b' and 'c' each appear exactly 1 time.

// Example 3:

// Input: s = "aba"

// Output: 2

// Explanation:

// One of the longest balanced substrings is "ab" because both distinct characters 'a' and 'b' each appear exactly 1 time. Another longest balanced substring is "ba".

 

// Constraints:

// 1 <= s.length <= 105
// s contains only the characters 'a', 'b', and 'c'.

//solu= 
class Solution {
public:
    int mono(const string& s){
        if(s.empty()) return 0;

        int cnt = 1;
        int ans = 1;

        // CASE 1: Substrings containing only one distinct character.
        // Any substring with a single unique character is always balanced
        // because all occurrences are trivially equal.
        // We simply track the longest continuous block of the same character.
        for(int i = 1; i < (int)s.size(); i++){
            if(s[i] == s[i - 1]) cnt++;
            else cnt = 1;
            ans = max(ans, cnt);
        }
        return ans;
    }

    int duo(const string& s, char c1, char c2){
        map<int, int> pos;
        pos[0] = -1;

        int ans = 0;
        int delta = 0;

        // CASE 2: Substrings containing exactly two distinct characters.
        // We assign +1 to c1 and -1 to c2.
        // If the same delta value appears again, the substring between
        // the two positions has equal counts of c1 and c2, hence balanced.
        for(int i = 0; i < (int)s.size(); i++){
            if(s[i] != c1 && s[i] != c2){
                // Encountering a third character invalidates any current
                // two-character balance, so we reset the state.
                pos.clear();
                pos[0] = i;
                delta = 0;
                continue;
            }

            if(s[i] == c1) delta++;
            else delta--;

            if(pos.find(delta) != pos.end()){
                ans = max(ans, i - pos[delta]);
            }
            else{
                pos[delta] = i;
            }
        }
        return ans;
    }

    int trio(const string& s){
        vector<int> cnt(3, 0);
        map<vector<int>, int> pos;
        pos[{0, 0}] = -1;

        int ans = 0;

        // CASE 3: Substrings containing all three characters a, b, and c.
        // For such a substring to be balanced:
        // count(a) = count(b) = count(c).
        // This condition holds when both (b - a) and (c - a) repeat.
        for(int i = 0; i < (int)s.size(); i++){
            cnt[s[i] - 'a']++;

            vector<int> key = {
                cnt[1] - cnt[0],
                cnt[2] - cnt[0]
            };

            if(pos.find(key) != pos.end()){
                ans = max(ans, i - pos[key]);
            }
            else{
                pos[key] = i;
            }
        }
        return ans;
    }

    int longestBalanced(string s) {
        // A balanced substring can only belong to one of these cases:
        // 1) One unique character
        // 2) Any pair of characters
        // 3) All three characters together
        // evaluate all cases independently and take the maximum.
        return max({
            mono(s),
            duo(s, 'a', 'b'),
            duo(s, 'a', 'c'),
            duo(s, 'b', 'c'),
            trio(s)
        });
    }
};

//tc= O(n)
//sc= O(n)
