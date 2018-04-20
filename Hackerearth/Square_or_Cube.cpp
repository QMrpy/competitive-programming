
// Square or Cube
// https://www.hackerearth.com/challenge/competitive/airtel-crack-the-code/algorithm/square-and-cube-2-dd08d321/description/
// Polynomial hash
// O((MAX + N) log MAX) for precomputation
// O(1) per query

#include <bits/stdc++.h>
using namespace std;

const int MAX_VAL = 1e5 + 5;
const int MAX_N = 3e5 + 5;

const int BASE = 100003;
const long long MOD = 1e9 + 7;

int N, Q, A[MAX_N];
int cnt2[MAX_VAL], cnt3[MAX_VAL];
int zero[MAX_N], neg[MAX_N];
long long basepow[MAX_VAL], hash2[MAX_N], hash3[MAX_N];

int lp[MAX_VAL];
vector<int> pr;
vector<int> p2[MAX_VAL];
vector<pair<int, int> > p3[MAX_VAL];
void init() {
    for (int i = 2; i < MAX_VAL; i++) {
        if (lp[i] == 0) lp[i] = i, pr.push_back(i);
        for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] < MAX_VAL; j++)
            lp[i * pr[j]] = pr[j];
        int j = i;
        while (j != 1) {
            int cur = lp[j], cnt = 0;
            while (lp[j] == cur)
                j /= lp[j], cnt++;
            if (cnt & 1) p2[i].push_back(cur);
            if (cnt % 3) p3[i].emplace_back(cur, cnt % 3);
        }
    }
    basepow[0] = 1;
    for (int i = 1; i < MAX_VAL; i++)
        basepow[i] = (basepow[i - 1] * BASE) % MOD;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        zero[i] = zero[i - 1];
        neg[i] = neg[i - 1];
        hash2[i] = hash2[i - 1];
        hash3[i] = hash3[i - 1];
        if (A[i] == 0)
            zero[i]++;
        if (A[i] < 0) {
            neg[i]++;
            A[i] = -A[i];
        }
        for (int p : p2[A[i]]) {
            hash2[i] = (hash2[i] - cnt2[p] * basepow[p]) % MOD;
            cnt2[p] ^= 1;
            hash2[i] = (hash2[i] + MOD + cnt2[p] * basepow[p]) % MOD;
        }
        for (auto &x : p3[A[i]]) {
            int p, c; tie(p, c) = x;
            hash3[i] = (hash3[i] - cnt3[p] * basepow[p]) % MOD;
            cnt3[p] += c; cnt3[p] %= 3;
            hash3[i] = (hash3[i] + MOD + cnt3[p] * basepow[p]) % MOD;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    init();
    
    cin >> N >> Q;
    for(int i = 1; i <= N; i++)
        cin >> A[i];

    solve();
        
    for(int i = 0; i < Q; i++) {
        int L, R; cin >> L >> R;
        int z, n, c2, c3;
        z = zero[R] - zero[L - 1];
        n = neg[R] - neg[L - 1];
        c2 = hash2[R] - hash2[L - 1];
        c3 = hash3[R] - hash3[L - 1];
        int ans = (!c3) << 1 | (!c2 && !(n & 1));
        if (z) ans = 3;

        if (ans == 0) cout << "None";
        else if (ans == 1) cout << "Square";
        else if (ans == 2) cout << "Cube";
        else cout << "Both";
        cout << "\n";
    }
    
    return 0;
}