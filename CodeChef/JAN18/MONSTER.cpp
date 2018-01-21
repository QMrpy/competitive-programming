
// Killing Monsters
// https://www.codechef.com/JAN18/problems/MONSTER
// Editorial's approach
// https://discuss.codechef.com/questions/121220/monster-editorial

// Square-root decomposition, sum-over-subset dynamic programming
// Around O(sqrt(Q) N log N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_LG_N = 17;
const int MAX_N = 1 << MAX_LG_N;
const int MAX_Q = 1 << 18;

int N, Q, u[2][MAX_Q], dead[MAX_N];
long long h[MAX_N], dmg[MAX_N];

void solve() {
    int bsize = 1000;
    fill_n(dead, N, Q);
    for(int s=0; s<Q; s+=bsize) {
        fill_n(dmg, MAX_N, 0);
        for(int q=s; q<s+bsize && q<Q; q++)
            dmg[u[0][q]] += u[1][q];
        for(int j=0; j<MAX_LG_N; j++) {
            for(int mask=MAX_N-1; mask>=0; mask--)
                if(mask & 1 << j) dmg[mask ^ 1 << j] += dmg[mask];
        }
        for(int i=0; i<N; i++) {
            if(h[i] <= 0 || h[i] - dmg[i] > 0) { h[i] -= dmg[i]; continue; }
            for(int q=s; q<s+bsize && q<Q; q++) {
                if((u[0][q] & i) == i) h[i] -= u[1][q];
                if(h[i] <= 0) { dead[i] = q; break; }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i=0; i<N; i++)
        cin >> h[i];

    cin >> Q;
    for(int i=0; i<Q; i++) {
        int x, y; cin >> x >> y;
        x &= MAX_N - 1;
        u[0][i] = x, u[1][i] = y;
    }

    solve();
    
    sort(dead, dead+N);
    dead[N] = Q;
    
    int p = 0;
    for(int i=0; i<Q; i++) {
        while(dead[p] <= i) p++;
        cout << N - p << "\n";
    }
    
    return 0;
}