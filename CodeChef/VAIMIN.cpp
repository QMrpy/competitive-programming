
// Vaibhav and Ministers
// https://www.codechef.com/APRIL18A/problems/VAIMIN
// Combinatorics, Dynamic programming
// O(N^2)

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAX_N = 4e6 + 5;

long long inv[MAX_N], fact[MAX_N], ifact[MAX_N];

int P, Q, C, M;
vector<pair<int, int> > pts;
long long dp[MAX_N];

void init() {
    fact[0] = fact[1] = ifact[0] = ifact[1] = inv[1] = 1;
    for (int i = 2; i < MAX_N; i++) {
        inv[i] = (-MOD / i) * inv[MOD % i] % MOD + MOD;
        fact[i] = i * fact[i - 1] % MOD;
        ifact[i] = inv[i] * ifact[i - 1] % MOD;
    }
}

inline long long choose(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}

inline long long cntgood(int h, int sx, int sy) {
    return choose(sx + sy, sx) - choose(sx + sy, sx + h);
}

long long solve() {
    P -= C;
    if (P < Q) return 0;
    set<pair<int, int> > imp;
    imp.emplace(P + C, Q);
    for (int x = 0; x <= C; x++) imp.emplace(x, 0);

    set<tuple<int, int, int> > s;
    for (auto &p : pts) {
        if (imp.count(p)) return 0;
        int x, y; tie(x, y) = p;
        x -= C;
        if (x < y || x + y >= P + Q) continue;
        s.emplace(x + y, x, y);
    }
    pts.clear();
    for (auto &p : s) pts.emplace_back(get<1>(p), get<2>(p));
    pts.emplace_back(P, Q);
    
    for (int i = 0; i < pts.size(); i++) {
        int x, y; tie(x, y) = pts[i];
        dp[i] = cntgood(1, x, y);
        for (int j = 0; j < i; j++) {
            int x2, y2; tie(x2, y2) = pts[j];
            dp[i] -= dp[j] * cntgood(1 + x2 - y2, x - x2, y - y2) % MOD;
        }
        dp[i] %= MOD;
    }
    return (dp[pts.size() - 1] + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    init();

    cin >> P >> Q >> C >> M;
    for (int i = 0; i < M; i++) {
        int g, b; cin >> g >> b;
        pts.emplace_back(g, b);
    }

    cout << solve() << "\n";

    return 0;
}