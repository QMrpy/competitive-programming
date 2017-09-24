
// MKTHNUM - K-th Number
// http://www.spoj.com/problems/MKTHNUM/

// Using persistent segment tree
// https://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/
// O( (n+m) log n )

// Static allocation of nodes, ~0.9s


#include <bits/stdc++.h>
using namespace std;

const int MAX_NODES = 4e6;

struct stnode {
    int val, s, e;
    stnode *lt, *rt;
} stnodes[MAX_NODES];
int cur = 0;

stnode *getnewnode(int x, int v) {
    stnodes[cur].s = stnodes[cur].e = x;
    stnodes[cur].val = v;
    return &stnodes[cur++];
}

stnode *getnewnode(stnode *l, stnode *r) {
    stnodes[cur].s = l->s; stnodes[cur].e = r->e;
    stnodes[cur].val = l->val + r->val;
    stnodes[cur].lt = l; stnodes[cur].rt = r;
    return &stnodes[cur++];
}

stnode *stbuild(int s, int e) {
    if(s==e)
        return getnewnode(s, 0);
    int m = (s + e) >> 1;
    return getnewnode(stbuild(s, m), stbuild(m+1, e));
}

stnode *stinsert(stnode *node, int x) {
    if(x < node->s || node->e < x)
        return node;
    if(node->s==node->e)
        return getnewnode(x, 1);
    return getnewnode(stinsert(node->lt, x), stinsert(node->rt, x));
}

int stquery(stnode *frnode, stnode *tonode, int k) {
    if(frnode->s==frnode->e)
        return frnode->s;
    int c = tonode->lt->val - frnode->lt->val;
    if(k<=c)
        return stquery(frnode->lt, tonode->lt, k);
    return stquery(frnode->rt, tonode->rt, k-c);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> v(n+1);
    for(int i=1; i<=n; i++)
        cin >> v[i];

    vector<int> vs(v.begin(), v.end());
    sort(vs.begin()+1, vs.end());
    map<int, int> mp;
    for(int i=1; i<=n; i++)
        mp[vs[i]] = i;

    vector<stnode *> trees(n+1);
    trees[0] = stbuild(0, n);
    for(int i=1; i<=n; i++)
        trees[i] = stinsert(trees[i-1], mp[v[i]]);

    while(m--) {
        int i, j, k;
        cin >> i >> j >> k;
        int x = stquery(trees[i-1], trees[j], k);
        cout << vs[x] << "\n";
    }

    return 0;
}

