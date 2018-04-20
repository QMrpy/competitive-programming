
// Evaluate the polynomial
// https://www.codechef.com/problems/POLYEVAL
// Number theoretic transform
// O(N log N)

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 786433;
const int MAX_N = 8e5 + 5;

namespace NTT {
    const long long P = MOD;    // P = 2 ^ 18 * 3 + 1
    const int K = 18;
    const int ROOT = 10;
    const int N = 1 << K;
    vector<int> W;
    vector<int> rev;

    void init() {
        W.resize(N); W[0] = 1;
        W[1] = ROOT * ROOT * ROOT;
        for (int i = 2; i < N; i++)
            W[i] = 1LL * W[i - 1] * W[1] % P;
        rev.resize(N); rev[0] = 0;
        for (int i = 1; i < N; i++)
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (K - 1));
    }

    void transform(vector<int> &a) {
        for (int i = 1; i < N; i++) if (i < rev[i])
            swap(a[i], a[rev[i]]);
        for (int len = 2; len <= N; len <<= 1) {
            int half = len >> 1, diff = N / len;
            for (int i = 0; i < N; i += len) {
                int pw = 0;
                for (int j = i; j < i + half; j++) {
                    int v = 1LL * a[j + half] * W[pw] % P;
                    a[j + half] = a[j] - v;
                    if (a[j + half] < 0) a[j + half] += P;
                    a[j] += v;
                    if (a[j] >= P) a[j] -= P;
                    pw += diff;
                }
            }
        }
    }
};

int N, Q, A[MAX_N], ans[MAX_N];

void solve() {
    NTT::init();
    vector<int> a0(A, A + N + 1), a1(NTT::N), a2(NTT::N); a0.resize(NTT::N);
    long long shift = 1;
    for (int i = 0; i <= N; i++) {
        a1[i] = a0[i] * shift % MOD;
        a2[i] = a1[i] * shift % MOD;
        shift = shift * NTT::ROOT % MOD;
    }
    NTT::transform(a0);
    NTT::transform(a1);
    NTT::transform(a2);
    ans[0] = A[0];
    for (int i = 0; i < NTT::N; i++) {
        long long x = NTT::W[i]; ans[x] = a0[i];
        x = x * NTT::ROOT % MOD; ans[x] = a1[i];
        x = x * NTT::ROOT % MOD; ans[x] = a2[i];
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for (int i = 0; i <= N; i++)
        cin >> A[i];

    solve();

    cin >> Q;
    while (Q--) {
        int x; cin >> x;
        cout << ans[x] << "\n";
    }

    return 0;
}