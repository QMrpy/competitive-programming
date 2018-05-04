
// High Interview
// https://www.codechef.com/problems/HIGHINT

// Number-theoretic transform
// Polynomial multiplication with divide and conquer
// https://discuss.codechef.com/questions/124856/highint-editorial/124877
// O (N log^2 N)

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 786433;
const int MAX_N = 1e5 + 5;

long long powmod(long long a, int p) {
    long long r = 1;
    while (p) {
        if (p & 1) r = r * a % MOD;
        p >>= 1; a = a * a % MOD;
    }
    return r;
}

namespace NTT {
    const long long P = MOD; // 2 ^ 18 * 3 + 1
    const int K = 18;
    const int ROOT = 10;
    const int N = 1 << K;
    vector<int> W, invW;
    vector<int> rev;

    void init() {
        int n2 = N >> 1;
        W.resize(n2 + 1); W[0] = 1;
        W[1] = powmod(ROOT, (P - 1) / N);
        for (int i = 2; i <= n2; i++)
            W[i] = 1LL * W[i - 1] * W[1] % P;
        invW.resize(n2 + 1); invW[n2] = W[n2];
        for (int i = n2 - 1; i >= 0; i--)
            invW[i] = 1LL * invW[i + 1] * W[1] % P;
        rev.resize(N);
    }

    void transform(vector<int> &a, bool inv=false) {
        int k = 0; while ((1 << k) < a.size()) k++;
        int n = 1 << k;
        a.resize(n, 0);
        rev[0] = 0;
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (k - 1));
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        vector<int> &twiddle = inv ? invW : W;
        for (int len = 2; len <= n; len <<= 1) {
            int half = len >> 1, diff = N / len;
            for (int i = 0; i < n; i += len) {
                int pw = 0;
                for (int j = i; j < i + half; j++) {
                    int v = 1LL * a[j + half] * twiddle[pw] % P;
                    a[j + half] = a[j] - v;
                    if (a[j + half] < 0) a[j + half] += P;
                    a[j] += v;
                    if (a[j] >= P) a[j] -= P;
                    pw += diff;
                }
            }
        }

        if (inv) {
            long long inv_n = powmod(n, P - 2);
            for (int &x : a) x = x * inv_n % P;
        }
    }

    void convolve(vector<int> &a, vector<int> &b) {
        int m = a.size() + b.size() - 1;
        a.resize(m, 0); transform(a);
        b.resize(m, 0); transform(b);
        for (int i = 0; i < a.size(); i++)
            a[i] = 1LL * a[i] * b[i] % P;
        transform(a, true);
        a.resize(m);
    }
};

int N, K, p[MAX_N], B[MAX_N];

pair<vector<int>, vector<int> > recur(int L, int R) {
    if (L == R)
        return {{1LL * p[L] * B[L] % MOD},
                {(1 - p[L] + MOD) % MOD, p[L]}};
    int M = (L + R) >> 1;
    auto Lpoly = recur(L, M);
    auto Rpoly = recur(M + 1, R);
    auto &num1 = Lpoly.first, &num2 = Rpoly.first;
    auto den1 = Lpoly.second, den2 = Rpoly.second;
    NTT::convolve(num1, Rpoly.second);
    NTT::convolve(num2, Lpoly.second);
    int n = max(num1.size(), num2.size());
    num1.resize(n);
    for (int i = 0; i < num2.size(); i++) {
        num1[i] += num2[i];
        if (num1[i] >= MOD) num1[i] -= MOD;
    }
    NTT::convolve(den1, den2);
    return {num1, den1};
}

int solve() {
    NTT::init();
    auto poly = recur(0, N - 1).first;
    return poly[K - 1];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int P, Q; cin >> P >> Q >> B[i];
        p[i] = (P * powmod(Q, MOD - 2)) % MOD;
    }

    cout << solve() << "\n";

    return 0;
}