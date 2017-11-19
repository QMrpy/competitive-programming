
// Product on the segment by modulo
// https://www.codechef.com/NOV17/problems/SEGPROD

// Solution using disjoint sparse table
// https://discuss.codechef.com/questions/117696/tutorial-disjoint-sparse-table
// O(N log N) for construction
// O(1) per query
// Overall O(N log N + Q)


#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1 << 21;
const int MAX_Q = 2e7 + 5;
const int MAX_LG_N = 21;
const int INT_SIZ = sizeof(int) << 3;

int T, N, Q;
int B[(MAX_Q>>6) + 2];
long long A[MAX_N], P;
long long t[MAX_LG_N][MAX_N];

void init() {
    int n = 1; while(n < N) n <<= 1;
    int range, half;
    for(int h=1; (range = 1<<h) <= n; h++) {
        half = range>>1;
        for(int i=half; i<n; i+=range) {
            t[h][i] = A[i];
            t[h][i-1] = A[i-1];
            for(int j=i-2; j>=i-half; j--)
                t[h][j] = t[h][j+1] * A[j] % P;
            for(int j=i+1; j<i+half; j++)
                t[h][j] = t[h][j-1] * A[j] % P;
        }
    }
}

int query(int L, int R) {
    if(L == R) return A[L];
    int h = INT_SIZ - __builtin_clz(L ^ R);
    return t[h][L] * t[h][R] % P;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while(T--) {
        cin >> N >> P >> Q;
        for(int i=0; i<N; i++)
            cin >> A[i];
        for(int i=0; i<(Q>>6)+2; i++)
            cin >> B[i];

        init();

        int L, R, x=0;
        for(int i=0; i<Q; i++) {
            if(i & 63)
                L = (L + x) % N, R = (R + x) % N;
            else
                L = (B[i>>6] +  x) % N, R = (B[(i>>6)+1] + x) % N;
            if(L > R) swap(L, R);
            x = (query(L, R) + 1) % P;
        }
        cout << x << "\n";
    }

    return 0;
}