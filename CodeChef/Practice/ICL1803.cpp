
// Replace and Substring Queries
// https://www.codechef.com/problems/ICL1803
// Segment tree
// Preprocessing O(N log N + M * ALPHA * log M)
// Per query O(log N + ALPHA * log M + ALPHA * ALPHA)

#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 20;

struct SegTree {
    int n;
    vector<int> tree;

    SegTree(string &a): n(a.size()), tree(n << 2) {
        build(1, 0, n - 1, a);
    }

    void build(int i, int s, int e, string &a) {
        if (s == e) {
            tree[i] = 1 << (a[s] - 'a');
            return;
        }
        int m = (s + e) >> 1;
        build(i << 1, s, m, a); build(i << 1 | 1, m + 1, e, a);
        tree[i] = tree[i << 1] | tree[i << 1 | 1];
    }

    void update(int i, int s, int e, int qs, int qv) {
        if (s == e) {
            tree[i] = 1 << qv;
            return;
        }
        int m = (s + e) >> 1;
        if (qs <= m) update(i << 1, s, m, qs, qv);
        else update(i << 1 | 1, m + 1, e, qs, qv);
        tree[i] = tree[i << 1] | tree[i << 1 | 1];
    }

    int query(int i, int s, int e, int qs, int qe) {
        if (qe < s || e < qs)
            return 0;
        if (qs <= s && e <= qe)
            return tree[i];
        int m = (s + e) >> 1;
        return query(i << 1, s, m, qs, qe) | query(i << 1 | 1, m + 1, e, qs, qe);
    }

    int countFrom(int i, int s, int e, int qs, int mask) {
        if (s == e)
            return (tree[i] | mask) == mask ? s : qs;
        if (qs <= s && (tree[i] | mask) == mask)
            return e;
        int m = (s + e) >> 1;
        if (qs > m)
            return countFrom(i << 1 | 1, m + 1, e, qs, mask);
        int res = countFrom(i << 1, s, m, qs, mask);
        if (res < m) return res;
        return countFrom(i << 1 | 1, m + 1, e, res, mask);
    }

    int countUpto(int i, int s, int e, int qe, int mask) {
        if (s == e)
            return (tree[i] | mask) == mask ? s : qe;
        if (e <= qe && (tree[i] | mask) == mask)
            return s;
        int m = (s + e) >> 1;
        if (qe <= m)
            return countUpto(i << 1, s, m, qe, mask);
        int res = countUpto(i << 1 | 1, m + 1, e, qe, mask);
        if (res > m + 1) return res;
        return countUpto(i << 1, s, m, res, mask);
    }
};

long long ans[1 << ALPHA];
string A, B;

void addrem(int x, SegTree &sA, SegTree &sB, long long sign, bool build) {
    vector<pair<int, int> > vFrom = {{0, 1}}, vUpto;
    int mask;
    if (!build) {
        mask = 0;
        for (int i = x + 1; i < sB.n; ) {
            mask |= 1 << (B[i] - 'a');
            int j = sB.countFrom(1, 0, sB.n - 1, i, mask);
            vFrom.emplace_back(mask, j - i + 1);
            i = j + 1;
        }
    }
    mask = 0;
    for (int i = x; i >= 0; ) {
        mask |= 1 << (B[i] - 'a');
        int j = sB.countUpto(1, 0, sB.n - 1, i, mask);
        vUpto.emplace_back(mask, i - j + 1);
        i = j - 1;
    }

    for (auto &p1 : vFrom) for (auto &p2 : vUpto) 
        ans[p1.first | p2.first] += sign * p1.second * p2.second;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int T; cin >> T;
    while (T--) {
        cin >> A >> B;
        SegTree sA(A), sB(B);
        for (int i = 0; i < B.size(); i++)
            addrem(i, sA, sB, +1, true);

        int Q; cin >> Q;
        while (Q--) {
            int t; cin >> t;
            if (t == 1) {
                int x; char y; cin >> x >> y; x--;
                A[x] = y;
                sA.update(1, 0, sA.n - 1, x, y - 'a');
            } else if (t == 2) {
                int x; char y; cin >> x >> y; x--;
                addrem(x, sA, sB, -1, false);
                B[x] = y;
                sB.update(1, 0, sB.n - 1, x, y - 'a');
                addrem(x, sA, sB, +1, false);
            } else {
                int l, r; cin >> l >> r; l--; r--;
                int mask = sA.query(1, 0, sA.n - 1, l, r);
                cout << ans[mask] << "\n";
            }
        }

        fill_n(ans, 1 << ALPHA, 0);
    }

    return 0;
}