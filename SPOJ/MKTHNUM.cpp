
// MKTHNUM - K-th Number
// http://www.spoj.com/problems/MKTHNUM/

// Using persistent segment tree
// https://blog.anudeep2011.com/persistent-segment-trees-explained-with-spoj-problems/
// O( (n+m) log n )

// Dynamically allocated nodes, ~1.2s


#include <bits/stdc++.h>
using namespace std;

struct stnode {
    int val, s, e;
    stnode *lt, *rt;

    stnode(int x, int v) : s(x), e(x), val(v) {}

    stnode(stnode *l, stnode *r) :
        s(l->s), e(r->e),
        val(l->val + r->val),
        lt(l), rt(r) {}
};

stnode *stbuild(int s, int e) {
    if(s==e)
        return new stnode(s, 0);
    int m = (s + e) >> 1;
    return new stnode(stbuild(s, m), stbuild(m+1, e));
}

stnode *stinsert(stnode *node, int x) {
    if(x < node->s || node->e < x)
        return node;
    if(node->s==node->e)
        return new stnode(x, 1);
    return new stnode(stinsert(node->lt, x), stinsert(node->rt, x));
}

int stquery(stnode *frnode, stnode *tonode, int k) {
    if(frnode->s==frnode->e)
        return frnode->s;
    int c = tonode->lt->val - frnode->lt->val;
    if(k<=c) return stquery(frnode->lt, tonode->lt, k);
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

