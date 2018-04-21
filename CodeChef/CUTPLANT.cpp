
// Cutting Plants
// https://www.codechef.com/APRIL18A/problems/CUTPLANT
// Segment tree
// O(N log N)

#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1e5 + 5;

int T, N, A[MAX_N], B[MAX_N];

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) {
        N = 1; while (N < n) N <<= 1;
        tree.resize(N << 1, INF);
    }

    int query(int i, int j) {
        int v = INF;
        for(i += N, j += N; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1) {
            if((i & 1) == 1) v = min(v, tree[i]);
            if((j & 1) == 0) v = min(v, tree[j]);
        }
        return v;
    }

    void update(int i, int v) {
        tree[i + N] = v;
        for(i = (i + N) >> 1; i > 0; i >>= 1)
            tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
    }
};

int solve() {
    map<int, vector<int> > m;
    SegTree st(N);
    for (int i = 0; i < N; i++) {
        if (A[i] < B[i]) return -1;
        m[B[i]].push_back(i);
        st.update(i, A[i]);
    }
    int ans = 0;
    for (auto it = m.rbegin(); it != m.rend(); it++) {
        int b = it->first;
        auto &v = it->second;
        for (int i = 0; i < v.size(); ) {
            int j = i + 1, c = 0;
            while (j < v.size() && st.query(v[i], v[j]) >= b) j++;
            for (; i < j; i++) {
                if (st.query(v[i], v[i]) > b) c = 1;
                st.update(v[i], 0);
            }
            if (c) ans++;
            i = j;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> A[i];
        for (int i = 0; i < N; i++) cin >> B[i];

        cout << solve() << "\n";
    }

    return 0;
}