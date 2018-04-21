
// Chef and Same Old Recurrence 2
// https://www.codechef.com/APRIL18A/problems/JADUGAR2
// O(N)

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAX_N = 1e7 + 10;
const int MAX_VAL = 2 * MAX_N + 10;

int N, K, A, B, Q;
long long inv[MAX_VAL], pre[MAX_N];

void solve() {
    inv[1] = 1;
    for (int i = 2; i < 2 * N + 10; i++)
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD + MOD;

    N--;
    pre[0] = K % MOD;
    pre[1] = K * (A + 1LL * B * K % MOD) % MOD;
    long long a1, a2, t1, t2;
    a1 = (2 * A + 4LL * B * K) % MOD;
    a2 = (-1LL * A * A % MOD + MOD) % MOD;
    for (int i = 1; i < N; i++) {
        t1 = pre[i] * a1 % MOD * (2 * i + 1) % MOD;
        t2 = pre[i - 1] * a2 % MOD * (2 * i - 2) % MOD;
        pre[i + 1] = (t1 + t2) * inv[2 * i + 4] % MOD;
    }

    pre[0] = pre[0] * pre[0] % MOD;
    for (int i = 1; i <= N; i++)
        pre[i] = (pre[i - 1] + pre[i] * pre[i]) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> A >> B;

    solve();

    cin >> Q;
    while (Q--) {
        int L, R; cin >> L >> R; R--; L--;
        long long ans = pre[R] - (L ? pre[L - 1] : 0);
        if (ans < 0) ans += MOD;
        cout << ans << "\n";
    }

    return 0;
}