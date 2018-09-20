
// AND Square Subsegments
// https://www.codechef.com/SEPT18A/problems/ANDSQR

// Offline solution
// Uses segment tree with lazy propagation
// O(N log MAX_B + N log N + Q log N)


#include <bits/stdc++.h>
using namespace std;

const int MAX_B = 30;
const int MAX_N = 1e5 + 5;
const int MAX_Q = 5e5 + 5;

struct SegTree {
    vector<int> s, e;
    vector<long long> val, lazy;

    SegTree(int n): s(n << 2), e(n << 2), val(n << 2), lazy(n << 2) {
        build(1, 1, n);
    }

    void build(int i, int ss, int ee) {
        s[i] = ss, e[i] = ee;
        if (ss == ee) return;
        int m = (ss + ee) >> 1;
        build(i << 1, ss, m); build(i << 1 | 1, m + 1, ee);
    }

    void push(int i) {
        if (!lazy[i]) return;
        val[i] += lazy[i] * (e[i] - s[i] + 1);
        if (s[i] != e[i]) lazy[i << 1] += lazy[i], lazy[i << 1 | 1] += lazy[i];
        lazy[i] = 0;
    }

    void update(int i, int us, int ue) {
        if (ue < s[i] || e[i] < us) return;
        if (us <= s[i] && e[i] <= ue) { lazy[i]++; push(i); return; }
        update(i << 1, us, ue); update(i << 1 | 1, us, ue);
        val[i] = val[i << 1] + val[i << 1 | 1];
    }

    long long query(int i, int qs, int qe) {
        if (qe < s[i] || e[i] < qs) return 0;
        push(i);
        if (qs <= s[i] && e[i] <= qe) return val[i];
        return query(i << 1, qs, qe) + query(i << 1 | 1, qs, qe);
    }
};

int T, N, Q, A[MAX_N];
vector<pair<int, int> > qr[MAX_N];
long long ans[MAX_Q];
set<int> sq;

void init() {
    for (int i = 0; i * i < (1 << MAX_B); i++)
        sq.insert(i * i);
}

void solve() {
    vector<int> one(MAX_B, 1);

    SegTree st(N);

    for (int i = 1; i <= N; i++) {

        vector<pair<int, int> > v;
        for (int b = 0; b < MAX_B; b++) {
            if ((A[i] & 1 << b) == 0) one[b] = i + 1;
            else v.emplace_back(one[b], b);
        }
        sort(v.begin(), v.end());

        int cur = A[i], end = i;
        for (int j = v.size() - 1; j >= 0; j--) {
            if (sq.count(cur)) {
                int beg = v[j].first;
                if (beg <= end) st.update(1, beg, end);
            }
            cur ^= 1 << v[j].second;
            end = v[j].first - 1;
        }
        assert(cur == 0);
        if (1 <= end) st.update(1, 1, end);

        for (auto &p: qr[i]) {
            int L, idx; tie(L, idx) = p;
            ans[idx] = st.query(1, L, i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    init();

    cin >> T;
    while (T--) {
        cin >> N >> Q;
        for (int i = 1; i <= N; i++)
            cin >> A[i];
        for (int i = 0; i < Q; i++) {
            int L, R; cin >> L >> R;
            qr[R].emplace_back(L, i);
        }

        solve();
        
        for (int i = 0; i < Q; i++)
            cout << ans[i] << "\n";

        for (int i = 1; i <= N; i++)
            qr[i].clear();
    }

    return 0;
}