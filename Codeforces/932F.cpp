
// Escape Through Leaf
// http://codeforces.com/contest/932/problem/F
// Dynamic programming with fully dynamic convex hull trick
// Small-to-large merging
// O(N log^2 N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

struct DynamicHull {
    static constexpr double LOOOOW = -1e100;
    static const int MINHULL = 1;
    struct line {
        long long m, c;
        bool query;
        mutable double left;

        inline long long eval(long long x) const {
            return m * x + c;
        }

        inline double intersectX(const line &l) const {
            return (c - l.c) * 1.0 / (l.m - m);
        }

        inline bool operator<(const line &l) const {
            if (l.query) return left < l.m;
            return MINHULL ? m > l.m : m < l.m;
        }

        static inline bool ok(const line &a, const line &b, const line &c) {
            return a.intersectX(b) < b.intersectX(c);
        }
    };
    set<line> hull;

    void insert(line l) {
        if (hull.empty()) {
            l.left = LOOOOW;
            hull.insert(l);
            return;
        }
        auto it = hull.lower_bound(l);
        if (it != hull.end() && it->m == l.m) {
            if (MINHULL && it->c <= l.c || !MINHULL && it->c >= l.c) return;
            hull.erase(it++);
            if (hull.empty()) {
                l.left = LOOOOW;
                hull.insert(l);
                return;
            }
        }
        auto itL = it, itR = it;
        bool first = itL == hull.begin();
        if (!first) {
            it = --itL;
            while (it != hull.begin()) {
                if (line::ok(*--it, *itL, l)) break;
                hull.erase(itL);
                itL = it;
            }
        }
        if (itR != hull.end()) {
            it = itR;
            while (++it != hull.end()) {
                if (line::ok(l, *itR, *it)) break;
                hull.erase(itR);
                itR = it;
            }
        }
        if (first) {
            itR->left = itR->intersectX(l);
            l.left = LOOOOW;
            hull.insert(itR, l);
        } else if (itR == hull.end()) {
            l.left = itL->intersectX(l);
            hull.insert(itR, l);
        } else if (line::ok(*itL, l, *itR)) {
            itR->left = itR->intersectX(l);
            l.left = itL->intersectX(l);
            hull.insert(itR, l);
        }
    }

    long long query(long long x) {
        line l = {x, 0, true};
        auto it = hull.lower_bound(l); it--;
        return it->eval(x);
    }
};

int N, A[MAX_N], B[MAX_N];
vector<int> g[MAX_N];
DynamicHull hull[MAX_N];
long long ans[MAX_N];

int dfs(int u, int p) {
    int h = u;
    for (int v : g[u]) if (v != p) {
        int h1 = dfs(v, u);
        if (hull[h].hull.size() < hull[h1].hull.size()) swap(h, h1);
        for (auto &l : hull[h1].hull) hull[h].insert(l);
    }
    ans[u] = u == h ? 0 : hull[h].query(A[u]);
    hull[h].insert({B[u], ans[u]});
    return h;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];
    for (int i = 0; i < N - 1; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 1);
    for (int i = 1; i <= N; i++)
        cout << ans[i] << " ";

    return 0;
}