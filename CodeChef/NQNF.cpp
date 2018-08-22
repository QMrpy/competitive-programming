
// No Queries No Fun
// https://www.codechef.com/COOK97A/problems/NQNF

// Square root decomposition, convex hull trick
// Based on solution by uwi: https://www.codechef.com/viewsolution/19801773


#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;
const int MAX_NODES = 1e7;
const int MAX_N = 2e5;
const int MAX_Q = 2e5;
const int MAX_B = 1e4;

int N, Q;
long long A[MAX_N], B[MAX_N];
long long adif[MAX_B], bdif[MAX_B];
int q[4][MAX_B], typ2cnt[MAX_B], root[MAX_B];

struct line {
    long long m, c;

    inline long long eval(long long x) {
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

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
        cin >> A[i];
    for (int i = 1; i <= N; i++)
        cin >> B[i];

    int bsz = sqrt(Q) + 0.5;

    for (int blk = 0; blk * bsz < Q; blk++) {
        int qcnt = min(Q, blk * bsz + bsz) - blk * bsz;
        set<int> s;
        for (int j = 0; j < qcnt; j++) {
            cin >> q[0][j] >> q[1][j] >> q[2][j];
            if (q[0][j] > 2) cin >> q[3][j];
            s.insert(q[1][j]);
            s.insert(q[2][j] + 1);
        }
        vector<int> pos(s.begin(), s.end());
        for (int k = 0; k < pos.size() - 1; k++) {
            root[k] = LiChao::newnode(0, qcnt);
            for (int i = pos[k]; i < pos[k + 1]; i++)
                LiChao::addline(root[k], {-B[i], -A[i]});
        }

        fill_n(typ2cnt, pos.size(), 0);
        fill_n(adif, pos.size(), 0);
        fill_n(bdif, pos.size(), 0);
        for (int j = 0; j < qcnt; j++) {
            int l = lower_bound(pos.begin(), pos.end(), q[1][j]) - pos.begin();
            int r = lower_bound(pos.begin(), pos.end(), q[2][j] + 1) - pos.begin();
            if (q[0][j] == 1) {
                long long ans = -INF;
                for (int k = l; k < r; k++)
                    ans = max(ans, -LiChao::query(root[k], typ2cnt[k]) + adif[k]);
                cout << ans << "\n";
            } else if (q[0][j] == 2) {
                for (int k = l; k < r; k++) {
                    typ2cnt[k]++;
                    adif[k] += bdif[k];
                }
            } else if (q[0][j] == 3) {
                for (int k = l; k < r; k++)
                    bdif[k] += q[3][j];
            } else {
                for (int k = l; k < r; k++)
                    adif[k] += q[3][j];
            }
        }
        
        for (int k = 0; k < pos.size() - 1; k++) {
            for (int i = pos[k]; i < pos[k + 1]; i++) {
                A[i] += adif[k] + B[i] * typ2cnt[k];
                B[i] += bdif[k];
            }
        }
    }

    return 0;
}
