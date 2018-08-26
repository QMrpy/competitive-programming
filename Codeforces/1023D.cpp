
// Array Restoration
// https://codeforces.com/contest/1023/problem/D

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 5e5 + 5;

int N, Q, A[MAX_N];
vector<int> pos[MAX_N];

struct Segtree {
    vector<int> tree;
    int N;

    Segtree(int n) {
        N = 1;
        while (N < n) N <<= 1;
        tree.resize(N << 1);
    }

    void update(int i, int j, int v) {
        for(i += N, j += N; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if ((i & 1) == 1) tree[i] = v;
            if ((j & 1) == 0) tree[j] = v;
        }
    }

    int query(int i){
        int v = 0;
        for(i += N; i > 0; i >>= 1) v = max(v, tree[i]);
        return v;
    }
};

int solve() {
    for (int i = 1; i <= N; i++)
        pos[A[i]].push_back(i);
    if (pos[Q].empty() && pos[0].empty()) return 0;
    if (pos[Q].empty()) {
        A[pos[0].back()] = Q;
        pos[Q].push_back(pos[0].back());
        pos[0].pop_back();
    }

    set<int> less;
    less.insert(0);
    less.insert(N + 1);
    Segtree st(N + 5);
    for (int q = 1; q <= Q; q++) {
        int ll = -1, rr = -1;
        if (pos[q].empty())
            continue;
        for (int i : pos[q]) {
            int l = *prev(less.lower_bound(i));
            int r = *less.upper_bound(i);
            if (ll == -1)
                ll = l, rr = r;
            else if (ll != l || rr != r)
                return 0;
        }
        for (int i : pos[q])
            less.insert(i);
        st.update(ll + 1, rr - 1, q);
    }

    for (int i : pos[0])
        A[i] = st.query(i);
    return 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    if (solve()) {
        cout << "YES\n";
        for (int i = 1; i <= N; i++) cout << A[i] << " ";
    } else {
        cout << "NO\n";
    }

    return 0;
}