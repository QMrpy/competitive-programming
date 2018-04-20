
// L-R queries
// https://www.codechef.com/problems/LRQUER
// Segment tree
// O((N + Q) log^2 N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;

struct SegTree{
    int N;
    multiset<int> *tree;

    SegTree(int *a, int n){
        N = 1;
        while(N < n) N <<= 1;
        tree = new multiset<int>[N<<1];
        for(int i=0; i<n; i++)
            tree[N+i].insert(a[i]);
        for(int i=N-1; i>0; i--) {
            tree[i].insert(tree[i<<1].begin(), tree[i<<1].end());
            tree[i].insert(tree[i<<1|1].begin(), tree[i<<1|1].end());
        }
    }

    void check(multiset<int> &ms, int key, long long &best) {
        auto it = ms.lower_bound(key);
        if(it == ms.end()) it--;
        if(abs(*it - key) < abs(best - key)) best = *it;
        if(it != ms.begin()) it--;
        if(abs(*it - key) < abs(best - key)) best = *it;
    }

    int query(int i, int j, int key){
        long long best = 1e10;
        for(i+=N, j+=N; i<=j; i=(i+1)>>1, j=(j-1)>>1){
            if((i&1) == 1) check(tree[i], key, best);
            if((j&1) == 0) check(tree[j], key, best);
        }
        return best;
    }

    void update(int i, int x, int v){
        for(i+=N; i>0; i>>=1)
            tree[i].erase(tree[i].find(x)), tree[i].insert(v);
    }
};

int T, N, Q;
int a[MAX_N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while(T--) {
        cin >> N >> Q;
        for(int i=1; i<=N; i++) {
            cin >> a[i];
            a[i] <<= 1;
        }

        SegTree st(a, N+1);

        while(Q--) {
            int typ, L, R;
            cin >> typ >> L >> R;
            if(typ == 1) {
                long long best = st.query(L, R, (0LL + a[L] + a[R]) >> 1);
                long long ans = ((best - a[L]) * (a[R] - best)) >> 2;
                cout << ans << "\n";
            }
            else {
                R <<= 1;
                st.update(L, a[L], R);
                a[L] = R;
            }
        }
    }

    return 0;
}