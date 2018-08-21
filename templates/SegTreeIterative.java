
// Iterative segment tree
// Support either range update + point query or point update + range query.
// Source: http://bababadalgharaghtakamminarronnkonnbro.blogspot.com/2012/06/kempe-tree-data-structure-for.html
// Similar to http://codeforces.com/blog/entry/18051

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) {
        N = 1; while (N < n) N <<= 1;
        tree.resize(N << 1);
    }

    /**   Mode 1   **/
    void update(int i, int v) {
        tree[i + N] = v;
        for(i = (i + N) >> 1; i > 0; i >>= 1)
            tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
    
    int query(int i, int j) {
        int v = 0;
        for (i += N, j += N; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if ((i & 1) == 1) v += tree[i];
            if ((j & 1) == 0) v += tree[j];
        }
        return v;
    }

    /**   Mode 2   **/
    void update(int i, int j, int v) {
        for (i += N, j += N; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if((i & 1) == 1) tree[i] += v;
            if((j & 1) == 0) tree[j] += v;
        }
    }

    int query(int i) {
        int v = 0;
        for(i += N; i > 0; i >>= 1)
            v += tree[i];
        return v;
    }
};
