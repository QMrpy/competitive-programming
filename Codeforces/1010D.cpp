
// Mars rover
// https://codeforces.com/contest/1010/problem/D

// Depth first search, Small to large merge
// O(N log^2 N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 10;

int N;
vector<int> g[MAX_N];
set<int> ch[MAX_N];
int val[MAX_N];

inline int merge(int i, int j) {
    if (ch[i].size() > ch[j].size()) {
        for (int x : ch[j]) ch[i].insert(x);
        return i;
    }
    for (int x : ch[i]) ch[j].insert(x);
    return j;
}

int dfs(int u) {
    int typ = g[u][0], lt, rt, lptr, rptr, tmp;
    if (typ == 'I') { ch[u].insert(u); return u; }
    lt = g[u][1], lptr = dfs(lt);
    if (typ == 'N') { val[lptr] = !val[lptr]; return lptr; }
    rt = g[u][2], rptr = dfs(rt);
    switch (typ) {
        case 'X':
            tmp = val[lptr] ^ val[rptr]; lptr = merge(lptr, rptr); val[lptr] = tmp; return lptr;
        case 'O':
            if (val[lptr] && val[rptr]) { val[u] = 1; return u; }
            if (val[lptr] && !val[rptr]) { val[lptr] = 1; return lptr; }
            if (!val[lptr] && val[rptr]) { val[rptr] = 1; return rptr; } 
            lptr = merge(lptr, rptr); val[lptr] = 0; return lptr;
        case 'A':
            if (!val[lptr] && !val[rptr]) { val[u] = 0; return u; }
            if (!val[lptr] && val[rptr]) { val[lptr] = 0; return lptr; }
            if (val[lptr] && !val[rptr]) { val[rptr] = 0; return rptr; }
            lptr = merge(lptr, rptr); val[lptr] = 1; return lptr;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<int> inps;
    for (int u = 1; u <= N; u++) {
        string s; cin >> s;
        int x, y; cin >> x;
        if (s == "IN") g[u] = {s[0]}, val[u] = x, inps.push_back(u);
        else if (s == "NOT") g[u] = {s[0], x};
        else {
            cin >> y;
            if (s == "XOR") g[u] = {s[0], x, y};
            else if (s == "OR") g[u] = {s[0], x, y};
            else g[u] = {s[0], x, y};
        }
    }

    int w = dfs(1);
    for (int x : inps) cout << (val[w] ^ ch[w].count(x));

    return 0;
}