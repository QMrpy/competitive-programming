
// MKTHNUM - K-th Number
// http://www.spoj.com/problems/MKTHNUM/

// Using wavelet tree on compressed values [1, 1e5]
// https://users.dcc.uchile.cl/~jperez/papers/ioiconf16.pdf
// O( (n+m) log n )
// ~0.6s


#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_VAL = 1e9;

struct wtnode {
    int s, e;
    vector<int> maplt;
    wtnode *lt, *rt;

    wtnode(int ss, int ee, int n) :
        s(ss), e(ee),
        maplt(n) {}
};

wtnode *wtbuild(int s, int e, int *a, int n) {
    if(s>e || n==0)
        return NULL;
    wtnode *node = new wtnode(s, e, n);
    if(s==e)
        return node;
    int m = (s + e) >> 1;
    int lcnt = 0;
    for(int i=0; i<n; i++) {
        if(a[i]<=m) lcnt++;
        node->maplt[i] = lcnt-1;
    }
    stable_partition(a, a+n, [m](int x){return x<=m;});
    node->lt = wtbuild(s, m, a, lcnt);
    node->rt = wtbuild(m+1, e, a+lcnt, n-lcnt);
    return node;
}

int wtquery(wtnode *node, int ql, int qr, int k) {
    if(node->s==node->e)
        return node->s;
    int tmpll = ql ? node->maplt[ql-1] : -1;
    int c = node->maplt[qr] - tmpll;
    if(k<=c)
        return wtquery(node->lt, tmpll + 1, node->maplt[qr], k);
    int tmprl = ql-1 - tmpll - 1;
    int tmprr = qr - node->maplt[qr] - 1;
    return wtquery(node->rt, tmprl + 1, tmprr, k-c);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m, a[MAX_N];
    cin >> n >> m;
    for(int i=1; i<=n; i++)
        cin >> a[i];

    vector<int> vs(a, a+n+1);
    sort(vs.begin()+1, vs.end());
    map<int, int> mp;
    for(int i=1; i<=n; i++)
        mp[vs[i]] = i;
    for(int i=1; i<=n; i++)
        a[i] = mp[a[i]];

    wtnode *root = wtbuild(-MAX_VAL, MAX_VAL, a, n+1);

    while(m--) {
        int i, j, k;
        cin >> i >> j >> k;
        int x = wtquery(root, i, j, k);
        cout << vs[x] << "\n";
    }

    return 0;
}

