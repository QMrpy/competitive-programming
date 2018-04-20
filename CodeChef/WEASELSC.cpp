
// Weasel finds Staircase
// https://www.codechef.com/problems/WEASELSC

// Dynamic Programming on tree with convex hull trick
// O(K N log N)


#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 50;
const int MAX_N = 101010;
const int MAX_K = 55;

int T, N, K, par[MAX_N];
long long hist[MAX_N], dp[MAX_K][MAX_N];
vector<int> g[MAX_N];

struct line {
    long long m, c;

    line() {}
    line(long long mm, long long cc) : m(mm), c(cc) {}

    long long eval(long long x) {
        return m * x + c;
    }

    double intersectX(line &l) {
        return (c - l.c) * 1.0 / (l.m - m);
    }
};

line dq[MAX_N];
line dummy;


void buildtree() {
    for(int i=0; i<=N; i++) g[i].clear();
    deque<int> st;
    hist[0] = -1;
    st.push_back(0);
    for(int i=1; i<=N; i++) {
        while(hist[st.back()] >= hist[i])
            st.pop_back();
        par[i] = st.back();
        g[st.back()].push_back(i);
        st.push_back(i);
    }
    hist[0] = 0;
}

int bin_search(int lt, int rt, int x, line &l=dummy) {
    if(rt-lt <= 1) return rt - 1;

    rt--;
    double xel = x==-1 ? dq[rt].intersectX(l) : x;
    double xep = dq[rt].intersectX(dq[rt-1]);
    if(xep < xel)
        return rt;

    rt--;
    while(lt < rt) {
        int m = (lt + rt) >> 1;
        double xl = x==-1 ? dq[m].intersectX(l) : x;
        double xn = dq[m].intersectX(dq[m+1]);
        if(xl <= xn)
            rt = m;
        else
            lt = m + 1;
    }
    return lt;
}

void dfs(int k, int u, int dq_f, int dq_r) {

    line cur(hist[u], dp[k-1][par[u]] - hist[u] * par[u]);

    dq_r = bin_search(dq_f, dq_r, -1, cur);
    line rem = dq[++dq_r];
    int rem_p = dq_r;
    dq[dq_r++] = cur;

    dq_f = bin_search(dq_f, dq_r, u);

    dp[k][u] = dq[dq_f].eval(u);

    for(int v : g[u])
        dfs(k, v, dq_f, dq_r);

    dq[rem_p] = rem;
}

long long solve() {

    buildtree();

    for(int k=1; k<=K; k++)
        dfs(k, 0, 0, 0);

    long long ans = 0;
    for(int i=1; i<=N; i++)
        ans = max(ans, dp[K][i]);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while(T--) {
        cin >> N >> K;
        K++;
        for(int i=1; i<=N; i++)
            cin >> hist[i];

        long long ans1 = solve();
        reverse(hist+1, hist+N+1);
        long long ans2 = solve();

        cout << max(ans1, ans2) << "\n";
    }
    return 0;
}
