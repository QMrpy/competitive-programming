// Segment Sum
// https://codeforces.com/contest/1073/problem/E
// Digit DP

#include <bits/stdc++.h>
using namespace std;

const int MAX_L = 20;
const int MAX_D = 10;
const long long MOD = 998244353;

long long l, r;
int k;

pair<long long, long long> dp[MAX_L][1 << MAX_D];
bool mem[MAX_L][1 << MAX_D];
long long pow10[MAX_L];

pair<long long, long long> recur(int n, int mask) {
    if (mask == 1) mask = 0;
    if (__builtin_popcount(mask) > k)
        return {0, 0};
    if (n == 0) return {1, 0};
    if (!mem[n][mask]) {
        mem[n][mask] = 1;
        for (int d = 0; d < MAX_D; d++) {
            auto p = recur(n - 1, mask | 1 << d);
            dp[n][mask].first += p.first;
            dp[n][mask].second += (p.first * pow10[n - 1] % MOD * d + p.second) % MOD;
        }
        dp[n][mask].first %= MOD;
        dp[n][mask].second %= MOD;
    }
    return dp[n][mask];
}

long long count(long long x) {
    stringstream ss; ss << x; string s = ss.str();
    long long ans = 0, cursum = 0;
    int n = s.size();
    int mask = 0;
    for (int i = 0; i < n; i++) {
        int cur = s[i] - '0';
        for (int d = 0; d < cur; d++) {
            auto p = recur(n - i - 1, mask | 1 << d);
            ans += (p.first * (cursum + pow10[n - i - 1] * d % MOD) % MOD + p.second) % MOD;
        }
        ans %= MOD;
        mask |= 1 << cur;
        cursum += pow10[n - i - 1] * cur % MOD;
        cursum %= MOD;
    }
    return ans;
}

long long solve() {
    pow10[0] = 1;
    for (int i = 1; i < MAX_L; i++)
        pow10[i] = pow10[i - 1] * 10 % MOD;
    long long ll = count(l), rr = count(r + 1);
    return (rr - ll + MOD) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> l >> r >> k;

    cout << solve() << "\n";
    
    return 0;
}