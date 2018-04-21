
// Chef and Same Old Recurrence
// https://www.codechef.com/APRIL18A/problems/JADUGAR
// Proof: https://discuss.codechef.com/questions/125517/jadugar-editorial?page=1#125650
// O(N)

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAX_N = 2e7 + 5;

int N, K, A, B;
long long inv[MAX_N], fact[MAX_N], ifact[MAX_N];

inline long long powmod(long long a, long long p) {
    long long r = 1;
    while (p) {
        if (p & 1) r = r * a % MOD;
        p >>= 1; a = a * a % MOD;
    }
    return r;
}

inline long long choose(int n, int k) {
    return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int solve() {
    fact[0] = ifact[0] = fact[1] = ifact[1] = inv[1] = 1;
    for (int i = 2; i <= 2 * N; i++) {
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD + MOD;
        fact[i] = fact[i - 1] * i % MOD;
        ifact[i] = ifact[i - 1] * inv[i] % MOD;
    }

    N--;
    long long Apow = 1, BK = 1LL * B * K % MOD, BKpow = 1, Ainv, ans = 0;
    if (A == 0) {
        ans = inv[N + 1] * choose(2 * N, N) % MOD * powmod(BK, N) % MOD;
        return ans * K % MOD;
    }

    Apow = powmod(A, N); Ainv = powmod(A, MOD - 2);
    for (int i = 0; i <= N; i++) {
        long long s = inv[i + 1] * choose(2 * i, i) % MOD * BKpow % MOD;
        s = s * choose(N + i, N - i) % MOD * Apow % MOD;
        BKpow = BKpow * BK % MOD;
        Apow = Apow * Ainv % MOD;
        ans += s;
    }
    return ans % MOD * K % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> A >> B;
    cout << solve() << "\n";

    return 0;
}