
// Powerful array
// http://codeforces.com/contest/86/problem/D
// Mo's algorithm
// O(N ^ 1.5)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;
const int MAX_V = 1e6 + 5;

int N, Q, a[MAX_N];
long long ans[MAX_N];
struct query {
    int l, r, id;
} q[MAX_N];

int bsize, cnt[MAX_V];
long long cur;

bool compare(query &q1, query &q2) {
    int b1 = q1.l / bsize, b2 = q2.l / bsize;
    return b1 != b2 ? b1 < b2 : b1 & 1 ? q1.r < q2.r : q2.r < q1.r;
}

inline void add(int x) {
    cur += x * (cnt[x]++ << 1 | 1LL);
}

inline void rem(int x) {
    cur -= x * (--cnt[x] << 1 | 1LL);
}

void mo() {
    bsize = 2*sqrt(N) + 0.5;
    sort(q, q+Q, compare);
    
    int l = 1, r = 0;
    cur = 0;
    for(int i=0; i<Q; i++) {
        while(l < q[i].l)
            rem(a[l++]);
        while(l > q[i].l)
            add(a[--l]);
        while(r < q[i].r)
            add(a[++r]);
        while(r > q[i].r)
            rem(a[r--]);
        ans[q[i].id] = cur;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> Q;
    for(int i=1; i<=N; i++)
        cin >> a[i];
        
    for(int i=0; i<Q; i++) {
        q[i].id = i;
        cin >> q[i].l >> q[i].r;
    }
    
    mo();
    
    for(int i=0; i<Q; i++)
        cout << ans[i] << "\n";
    
    return 0;
}