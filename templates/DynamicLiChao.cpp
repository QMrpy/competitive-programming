
// LiChao Segment Tree
// Supports insertion of lines and min queries

// https://e-maxx-eng.appspot.com/geometry/convex_hull_trick.html

const long long INF = 1e18;

struct line {
    long long m, c;

    inline long long eval(long long x) const {
        return m * x + c;
    }
};

namespace LiChao {
    struct node {
        int s, e, m;
        line cur;
        int lt, rt;
    } pool[MAX_NODES];
    int p = 1;

    int newnode(int ss, int ee) {
        node &n = pool[p];
        n.s = ss; n.e = ee; n.m = (ss + ee) >> 1;
        n.cur = {0, INF};
        return p++;
    }

    long long query(int i, int x) {
        node &n = pool[i];
        long long y = n.cur.eval(x);
        if (n.s == n.e) return y;
        if (x < n.m && n.lt) y = min(y, query(n.lt, x));
        if (x > n.m && n.rt) y = min(y, query(n.rt, x));
        return y;
    }

    void addline(int i, line l) {
        node &n = pool[i];
        if (n.cur.c == INF) {
            n.cur = l;
            return;
        }
        bool b1 = l.eval(n.s) < n.cur.eval(n.s);
        bool b2 = l.eval(n.m) < n.cur.eval(n.m);
        bool b3 = l.eval(n.e) < n.cur.eval(n.e);
        if (b2) swap(n.cur, l);
        if (b1 == b2 && b2 == b3) return;
        if (n.s == n.e) return;
        if (b1 != b2) {
            if (!n.lt) n.lt = newnode(n.s, n.m);
            addline(n.lt, l);
        } else {
            if (!n.rt) n.rt = newnode(n.m + 1, n.e);
            addline(n.rt, l);
        }
    }
}