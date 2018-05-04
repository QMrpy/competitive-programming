
// Escape Through Leaf
// http://codeforces.com/contest/932/problem/F
// Dynamic programming with fully dynamic convex hull trick
// Maintains hull with LiChao segment tree
// Small-to-large merging
// O(N log^2 N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_NODES = MAX_N * 25;
const int MIN_X = -1e5 - 5;
const int MAX_X = 1e5 + 5;
const long long INF = 1e18;

struct line {
    long long m, c;

    inline long long eval(long long x) const {
        return m * x + c;
    }
};

namespace LiChao {
    struct node {
        int s, e, m;
        line cur;
        int lt, rt;
    } pool[MAX_NODES];
    int p = 1;

    int newnode(int ss, int ee) {
        node &n = pool[p];
        n.s = ss; n.e = ee; n.m = (ss + ee) >> 1;
        n.cur = {0, INF};
        return p++;
    }

    long long query(int i, int x) {
        node &n = pool[i];
        long long y = n.cur.eval(x);
        if (n.s == n.e) return y;
        if (x < n.m && n.lt) y = min(y, query(n.lt, x));
        if (x > n.m && n.rt) y = min(y, query(n.rt, x));
        return y;
    }

    void addline(int i, line l) {
        node &n = pool[i];
        if (n.cur.c == INF) {
            n.cur = l;
            return;
        }
        bool b1 = l.eval(n.s) < n.cur.eval(n.s);
        bool b2 = l.eval(n.m) < n.cur.eval(n.m);
        bool b3 = l.eval(n.e) < n.cur.eval(n.e);
        if (b2) swap(n.cur, l);
        if (b1 == b2 && b2 == b3) return;
        if (n.s == n.e) return;
        if (b1 != b2) {
            if (!n.lt) n.lt = newnode(n.s, n.m);
            addline(n.lt, l);
        } else {
            if (!n.rt) n.rt = newnode(n.m + 1, n.e);
            addline(n.rt, l);
        }
    }
}

int N, A[MAX_N], B[MAX_N];
vector<int> g[MAX_N];
int root[MAX_N];
vector<line> lines[MAX_N];
long long ans[MAX_N];

int dfs(int u, int p) {
    int h = u;
    root[h] = LiChao::newnode(MIN_X, MAX_X);
    for (int v : g[u]) if (v != p) {
        int h1 = dfs(v, u);
        if (lines[h].size() < lines[h1].size()) swap(h, h1);
        for (auto &l : lines[h1]) LiChao::addline(root[h], l);
        lines[h].insert(lines[h].end(), lines[h1].begin(), lines[h1].end());

    }
    ans[u] = u == h ? 0 : LiChao::query(root[h], A[u]);
    LiChao::addline(root[h], {B[u], ans[u]});
    lines[h].push_back({B[u], ans[u]});
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