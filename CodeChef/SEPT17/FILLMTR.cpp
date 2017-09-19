
// Fill The Matrix
// https://www.codechef.com/SEPT17/problems/FILLMTR

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

int T, N, Q;
map<pair<int, int>, int> mp;
map<int, vector<pair<int, int> > > g;
int vis[MAX_N], dist[MAX_N];

bool dfs(int u, int v) {
    vis[u] = T;
    dist[u] = v;
    for(auto p : g[u]) {
        int v, w;
        tie(v, w) = p;
        if(vis[v] == T) {
            if(w != abs(dist[v] - dist[u]))
                return true;
        }
        else {
            bool b = dfs(v, (dist[u] + w) & 1);
            if(b) return b;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    while(T--) {
        cin >> N >> Q;
        bool impossible = false;
        
        for(int q=0; q<Q; q++) {
            int i, j, val;
            cin >> i >> j >> val;
            
            if(i==j) {
                if(val==1) impossible = true;
                continue;
            }
            
            if(i>j) swap(i, j);
            auto pij = make_pair(i, j);
            if(mp.count(pij)) {
                if(mp[pij]!=val) impossible = true;
                continue;
            }
            
            mp[pij] = val;
            g[i].emplace_back(j, val);
            g[j].emplace_back(i, val);
        }
        
        for(auto p : g) {
            if(impossible) break;
            int u = p.first;
            if(vis[u] != T)
                impossible = dfs(u, 0);
        }
        
        cout << (impossible ? "no\n" : "yes\n");
        
        mp.clear();
        g.clear();
    }
    
    return 0;
}