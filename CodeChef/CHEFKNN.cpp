
// Chef and Interval Painting
// https://www.codechef.com/problems/CHEFKNN
// Number theoretic transform
// O(N log N)

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 163577857;
const int MAX_N = 1e6 + 5;
const int MAX_T = 111;

long long powmod(long long a, int p) {
    long long r = 1;
    while (p) {
        if (p & 1) r = r * a % MOD;
        p >>= 1; a = a * a % MOD;
    }
    return r;
}

namespace NTT {
    const long long P = MOD;
    const int K = 20;
    const int ROOT = 23;
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

int T, ans[MAX_T];
pair<pair<int, int>, int> A[MAX_T];
long long fact[MAX_N], invfact[MAX_N];

void init() {
    fact[0] = invfact[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        fact[i] = i * fact[i - 1] % MOD;
        invfact[i] = powmod(fact[i], MOD - 2);
    }
}

vector<int> calcR(vector<int> L, int n) {
    vector<int> a(n + 1), b(n + 1);
    long long npow = 1;
    for (int i = n; i >= 0; i--) {
        a[i] = L[i] * fact[i] % MOD;
        b[i] = npow * invfact[n - i] % MOD;
        npow = npow * n % MOD;
    }
    NTT::convolve(a, b);
    b.resize(n + 1);
    for (int i = 0; i <= n; i++)
        b[i] = a[i + n] * invfact[i] % MOD;
    return b;
}

vector<int> recur(int L, int R) {
    if (L == R) return vector<int>({L, 1});
    int n = R - L + 1, n2 = n >> 1;
    vector<int> polyL = recur(L, L + n2 - 1);
    vector<int> polyR = calcR(polyL, n2);
    NTT::convolve(polyL, polyR);
    if (n & 1) {
        polyL.push_back(0);
        for (int i = n; i > 0; i--) {
            polyL[i] = polyL[i - 1] + 1LL * R * polyL[i] % MOD;
            if (polyL[i] >= MOD) polyL[i] -= MOD;
        }
        polyL[0] = 1LL * R * polyL[0] % MOD;
    }
    return polyL;
}

void solve() {
    init();
    NTT::init();

    sort(A, A + T);
    int prev = 0;
    vector<int> prevpoly({1});
    for (int t = 0; t < T; t++) {
        int N, K; tie(N, K) = A[t].first;
        if (prev < N) {
            vector<int> poly = recur(prev + 1, N);
            NTT::convolve(prevpoly, poly);
            prev = N;
        }
        long long sum = 0;
        for (int i = 1; i <= K; i++)
            sum += fact[K - 1] * invfact[i - 1] % MOD * invfact[K - i] % MOD * prevpoly[N - i] % MOD;
        ans[A[t].second] = sum % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for (int i = 0; i < T; i++) {
        cin >> A[i].first.first >> A[i].first.second;
        A[i].second = i;
    }

    solve();

    for (int i = 0; i < T; i++)
        cout << ans[i] << "\n";

    return 0;
}