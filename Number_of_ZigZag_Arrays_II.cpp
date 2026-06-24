// 3700. Number of ZigZag Arrays II
// Hard
// Topics
// premium lock icon
// Companies
// Hint
// You are given three integers n, l, and r.

// A ZigZag array of length n is defined as follows:

// Each element lies in the range [l, r].
// No two adjacent elements are equal.
// No three consecutive elements form a strictly increasing or strictly decreasing sequence.
// Return the total number of valid ZigZag arrays.

// Since the answer may be large, return it modulo 109 + 7.

// A sequence is said to be strictly increasing if each element is strictly greater than its previous one (if exists).

// A sequence is said to be strictly decreasing if each element is strictly smaller than its previous one (if exists).

 

// Example 1:

// Input: n = 3, l = 4, r = 5

// Output: 2

// Explanation:

// There are only 2 valid ZigZag arrays of length n = 3 using values in the range [4, 5]:

// [4, 5, 4]
// [5, 4, 5]
// Example 2:

// Input: n = 3, l = 1, r = 3

// Output: 10

// Explanation:

// ​​​​​​​There are 10 valid ZigZag arrays of length n = 3 using values in the range [1, 3]:

// [1, 2, 1], [1, 3, 1], [1, 3, 2]
// [2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
// [3, 1, 2], [3, 1, 3], [3, 2, 3]
// All arrays meet the ZigZag conditions.

 

// Constraints:

// 3 <= n <= 109
// 1 <= l < r <= 75​​
class Solution {
public:
    static const int MOD = 1000000007;

    using ll = long long;
    using Matrix = vector<vector<ll>>;

    /*
    Matrix multiplication.
    */
    Matrix multiply(const Matrix& A,const Matrix& B){

        int n=A.size();

        Matrix C(n,vector<ll>(n,0));

        for(int i=0;i<n;i++){
            for(int k=0;k<n;k++){

                if(!A[i][k]) continue;

                for(int j=0;j<n;j++){

                    if(!B[k][j]) continue;

                    C[i][j]=
                        (C[i][j]+A[i][k]*B[k][j])%MOD;
                }
            }
        }

        return C;
    }

    /*
    Fast matrix exponentiation.
    */
    Matrix power(Matrix base,long long exp){

        int n=base.size();

        Matrix res(n,vector<ll>(n,0));

        for(int i=0;i<n;i++){
            res[i][i]=1;
        }

        while(exp){

            if(exp&1){
                res=multiply(res,base);
            }

            base=multiply(base,base);
            exp>>=1;
        }

        return res;
    }

    int zigZagArrays(int n,int l,int r) {

        /*
        Number of available values.
        */
        int m=r-l+1;

        if(n==1){
            return m;
        }

        /*
        State layout:

        [0 ... m-1]
            = UP states

        [m ... 2m-1]
            = DOWN states

        State value stores the
        ending value of the array.
        */
        int S=2*m;

        vector<ll> init(S,0);

        /*
        Build all valid arrays of length 2.

        a < b  => UP ending at b
        a > b  => DOWN ending at b
        */
        for(int a=0;a<m;a++){

            for(int b=0;b<m;b++){

                if(a==b) continue;

                if(a<b){
                    init[b]++;
                }
                else{
                    init[m+b]++;
                }
            }
        }

        if(n==2){

            ll ans=0;

            for(ll x:init){
                ans=(ans+x)%MOD;
            }

            return ans;
        }

        Matrix T(S,vector<ll>(S,0));

        /*
        Transition rules:

        UP can only follow DOWN.

        DOWN can only follow UP.

        This prevents two consecutive
        increasing or decreasing moves.
        */
        for(int y=0;y<m;y++){

            /*
            DOWN ending at y
            -> UP ending at x

            requires y < x.
            */
            for(int x=y+1;x<m;x++){
                T[x][m+y]=1;
            }

            /*
            UP ending at y
            -> DOWN ending at x

            requires y > x.
            */
            for(int x=0;x<y;x++){
                T[m+x][y]=1;
            }
        }

        /*
        Extend length-2 arrays
        to length n arrays.
        */
        Matrix P=power(T,n-2);

        vector<ll> state(S,0);

        for(int i=0;i<S;i++){
            for(int j=0;j<S;j++){

                state[i]=
                    (state[i]+P[i][j]*init[j])%MOD;
            }
        }

        ll ans=0;

        for(ll x:state){
            ans=(ans+x)%MOD;
        }

        return ans;
    }
};

/*
Time Complexity:
O((2m)^3 * log n)

m <= 75

Space Complexity:
O((2m)^2)
*/​​​​​
