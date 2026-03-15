// 1622. Fancy Sequence
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// Write an API that generates fancy sequences using the append, addAll, and multAll operations.

// Implement the Fancy class:

// Fancy() Initializes the object with an empty sequence.
// void append(val) Appends an integer val to the end of the sequence.
// void addAll(inc) Increments all existing values in the sequence by an integer inc.
// void multAll(m) Multiplies all existing values in the sequence by an integer m.
// int getIndex(idx) Gets the current value at index idx (0-indexed) of the sequence modulo 109 + 7. If the index is greater or equal than the length of the sequence, return -1.
 

// Example 1:

// Input
// ["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", "append", "multAll", "getIndex", "getIndex", "getIndex"]
// [[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
// Output
// [null, null, null, null, null, 10, null, null, null, 26, 34, 20]

// Explanation
// Fancy fancy = new Fancy();
// fancy.append(2);   // fancy sequence: [2]
// fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
// fancy.append(7);   // fancy sequence: [5, 7]
// fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]
// fancy.getIndex(0); // return 10
// fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
// fancy.append(10);  // fancy sequence: [13, 17, 10]
// fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]
// fancy.getIndex(0); // return 26
// fancy.getIndex(1); // return 34
// fancy.getIndex(2); // return 20
 

// Constraints:

// 1 <= val, inc, m <= 100
// 0 <= idx <= 105
// At most 105 calls total will be made to append, addAll, multAll, and getIndex.

//solu = 
class Fancy {
public:
    static const int MOD = 1e9 + 7;

    // We store each appended value in "normalized" form.
    // If current global transformation is:
    // actual_value = stored_value * mul + add
    // then when appending val, we store:
    // stored_value = (val - add) / mul  (mod MOD)
    vector<long long> arr;

    // Global transformation applied to every stored value:
    // actual = stored * mul + add
    long long mul = 1;
    long long add = 0;

    Fancy() {
    }

    // Fast modular exponentiation to compute a^b % MOD
    long long modPow(long long a, long long b) {
        long long result = 1;
        a %= MOD;

        while (b > 0) {
            if (b & 1) {
                result = (result * a) % MOD;
            }
            a = (a * a) % MOD;
            b >>= 1;
        }

        return result;
    }

    // Modular inverse using Fermat's Little Theorem:
    // a^(-1) % MOD = a^(MOD-2) % MOD, because MOD is prime
    long long modInverse(long long a) {
        return modPow(a, MOD - 2);
    }

    void append(int val) {
        // We want stored_value such that:
        // stored_value * mul + add = val
        //
        // So:
        // stored_value = (val - add) / mul
        //              = (val - add) * inverse(mul) mod MOD

        long long normalized = (val - add + MOD) % MOD;
        normalized = (normalized * modInverse(mul)) % MOD;

        arr.push_back(normalized);
    }

    void addAll(int inc) {
        // If current transformation is:
        // actual = stored * mul + add
        //
        // After adding inc to all:
        // actual = stored * mul + (add + inc)
        add = (add + inc) % MOD;
    }

    void multAll(int m) {
        // If current transformation is:
        // actual = stored * mul + add
        //
        // After multiplying all by m:
        // actual = (stored * mul + add) * m
        //        = stored * (mul * m) + (add * m)

        mul = (mul * m) % MOD;
        add = (add * m) % MOD;
    }

    int getIndex(int idx) {
        // If index is out of bounds, return -1
        if (idx >= arr.size()) {
            return -1;
        }

        // Recover actual value using current transformation:
        // actual = stored * mul + add
        long long ans = (arr[idx] * mul) % MOD;
        ans = (ans + add) % MOD;

        return (int)ans;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
// tc = 
// append → O(log MOD) because of modular inverse
// addAll → O(1)
// multAll → O(1)
// getIndex → O(1)
// sc = O(n) to store appended elements
