
// Lonely Cycles
// https://www.codechef.com/AUG18A/problems/LONCYC

// Trees, depth first search
// O(N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;
const int MAX_M = 5e6 + 6;

int N, M, T;
int edg[2][MAX_M], is_cyc[MAX_M], no_cyc_cnt[2][MAX_M], one_cyc_cnt[2][MAX_M];
vector<int> g[MAX_N];
int cyc[2][MAX_N], inc[MAX_N], dep[MAX_N], vis[MAX_N], no_cyc_cnt_sum[MAX_N], one_cyc_cnt_sum[MAX_N];
long long ans[MAX_M];

inline int other(int u, int e) {
    return u ^ edg[0][e] ^ edg[1][e];
}

inline int which(int u, int e) {
    return u == edg[1][e];
}

void mark_cycle(int e) {
    is_cyc[e] = 1;
    int u = edg[0][e], v = edg[1][e];
    if (dep[u] < dep[v]) swap(u, v);
    cyc[1][u] = cyc[0][v] = e;
    while (dep[u] > dep[v]) {
        is_cyc[inc[u]] = 1;
        int par = other(u, inc[u]);
        cyc[0][u] = cyc[1][par] = inc[u];
        u = par;
    }
    while (u != v) {
        is_cyc[inc[u]] = is_cyc[inc[v]] = 1;
        int par = other(u, inc[u]);
        cyc[0][u] = cyc[1][par] = inc[u];
        u = par;
        par = other(v, inc[v]);
        cyc[1][v] = cyc[0][par] = inc[v];
        v = par;
    }
}

void find_cycles() {
    fill_n(inc, N + 1, 0);
    fill_n(cyc[0], N + 1, 0);
    fill_n(cyc[1], N + 1, 0);
    fill_n(is_cyc, M + 1, 0);

    vector<int> stack;
    stack.push_back(1);
    dep[1] = 0;
    while (!stack.empty()) {
        int u = stack.back(); stack.pop_back();
        for (int e : g[u]) if (e != inc[u]) {
            int v = other(u, e);
            if (inc[v]) {
                mark_cycle(e);
            } else {
                inc[v] = e; dep[v] = dep[u] + 1;
                stack.push_back(v);
            }
        }
    }
    for (int u = 1; u <= N; u++)
        g[u].erase(remove_if(g[u].begin(), g[u].end(), [&](int &e) { return e == cyc[0][u] || e == cyc[1][u]; }), g[u].end());
}

int dfs_no_cyc1(int u, int in) {
    vis[u] = 1;
    no_cyc_cnt_sum[u] = 1;
    for (int e : g[u]) if (e != in)
        no_cyc_cnt_sum[u] += dfs_no_cyc1(other(u, e), e);
    no_cyc_cnt[which(u, in)][in] = no_cyc_cnt_sum[u];
    return no_cyc_cnt_sum[u];
}

void dfs_no_cyc2(int u, int in) {
    no_cyc_cnt_sum[u] += no_cyc_cnt[!which(u, in)][in];
    for (int e : g[u]) if (e != in)
        no_cyc_cnt[which(u, e)][e] = no_cyc_cnt_sum[u] - no_cyc_cnt[!which(u, e)][e];
    for (int e : g[u]) if (e != in)
        dfs_no_cyc2(other(u, e), e);
}

int dfs_one_cyc1(int u, int in) {
    vis[u] = 1;
    one_cyc_cnt_sum[u] = 0;
    if (cyc[0][u])
        one_cyc_cnt_sum[u] += no_cyc_cnt_sum[other(u, cyc[0][u])] + no_cyc_cnt_sum[other(u, cyc[1][u])];
    for (int e : g[u]) if (e != in)
        one_cyc_cnt_sum[u] += dfs_one_cyc1(other(u, e), e);
    one_cyc_cnt[which(u, in)][in] = one_cyc_cnt_sum[u];
    return one_cyc_cnt_sum[u];
}

void dfs_one_cyc2(int u, int in) {
    one_cyc_cnt_sum[u] += one_cyc_cnt[!which(u, in)][in];
    for (int e : g[u]) if (e != in)
        one_cyc_cnt[which(u, e)][e] = one_cyc_cnt_sum[u] - one_cyc_cnt[!which(u, e)][e];
    for (int e : g[u]) if (e != in)
        dfs_one_cyc2(other(u, e), e);
}

void calc_counts() {
    fill_n(vis, N + 1, 0);
    for (int u = 1; u <= N; u++) if (!vis[u]) {
        dfs_no_cyc1(u, 0);
        dfs_no_cyc2(u, 0);
    }
    fill_n(vis, N + 1, 0);
    for (int u = 1; u <= N; u++) if (!vis[u]) {
        dfs_one_cyc1(u, 0);
        dfs_one_cyc2(u, 0);
    }
}

void calc_ans() {
    for (int e = 1; e <= M; e++) {
        if (is_cyc[e])
            ans[e] = 1LL * no_cyc_cnt_sum[edg[0][e]] * no_cyc_cnt_sum[edg[1][e]];
        else
            ans[e] = 1LL * no_cyc_cnt[0][e] * no_cyc_cnt[1][e]
                     + 1LL * no_cyc_cnt[0][e] * one_cyc_cnt[1][e]
                     + 1LL * one_cyc_cnt[0][e] * no_cyc_cnt[1][e];
    }
}

void solve() {
    find_cycles();
    calc_counts();
    calc_ans();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N >> M;
        for (int u = 1; u <= N; u++) g[u].clear();
        for (int i = 1; i <= M; i++) {
            cin >> edg[0][i] >> edg[1][i];
            g[edg[0][i]].emplace_back(i);
            g[edg[1][i]].emplace_back(i);
        }

        solve();

        for (int i = 1; i <= M; i++) cout << ans[i] << "\n";
    }

    return 0;
}
