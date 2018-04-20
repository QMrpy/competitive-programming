
// Rotate Point
// https://www.codechef.com/problems/ROTPTS
// Segment tree
// O(N log N)

#include <bits/stdc++.h>
using namespace std;

const long long MODVAL = 1e9 + 7;
const int MAX_N = 1e5 + 5;

struct RotMat {
    vector<long long> mat;

    /*
    [cos r   - sin r     x (1 - cos r) + y sin r]
    [sin r     cos r   - x sin r + y (1 - cos r)]
    [  0         0                  1           ]
    */

    RotMat() {
        mat = {1, 0, 0,  0, 1, 0};
    }

    RotMat(int x, int y, int r) {
        if(r==0)        mat = { 1,  0,    0,   0,  1,    0};
        else if(r==90)  mat = { 0, -1,  x+y,   1,  0, -x+y};
        else if(r==180) mat = {-1,  0,  2*x,   0, -1,  2*y};
        else            mat = { 0,  1,  x-y,  -1,  0,  x+y};
    }

    RotMat operator*(RotMat &m) {
        RotMat res;
        for(int i=0; i<6; i++) {
            int x = i/3*3, y = i%3;
            res.mat[i] = mat[x]*m.mat[y] + mat[x+1]*m.mat[y+3];
            if(i%3 == 2) res.mat[i] += mat[x+2];
            res.mat[i] %= MODVAL;
        }
        return res;
    }

    void operateOn(int &x, int &y) {
        long long x1 = mat[0]*x + mat[1]*y + mat[2];
        long long y1 = mat[3]*x + mat[4]*y + mat[5];
        x = (x1 % MODVAL + MODVAL) % MODVAL;
        y = (y1 % MODVAL + MODVAL) % MODVAL;
    }
};

struct SegTree{
    int N;
    RotMat *tree;

    SegTree(int x[], int y[], int r[], int n){
        N = 1;
        while(N < n) N <<= 1;
        tree = new RotMat[N<<1];
        for(int i=0; i<n; i++)
            tree[N+i] = RotMat(x[i], y[i], r[i]);
        for(int i=N-1; i>0; i--)
            tree[i] = tree[i<<1|1] * tree[i<<1];
    }

    void query(int i, int j, int &x, int &y){
        RotMat l, r;
        for(i+=N, j+=N; i<=j; i=(i+1)>>1, j=(j-1)>>1){
            if((i&1) == 1) l = tree[i] * l;
            if((j&1) == 0) r = r * tree[j];
        }
        (r * l).operateOn(x, y);
    }

    void update(int i, int x, int y, int r){
        tree[i+N] = RotMat(x, y, r);
        for(i=(i+N)>>1; i>0; i>>=1)
            tree[i] = tree[i<<1|1] * tree[i<<1];
    }
};

int N, Q;
int x[MAX_N], y[MAX_N], r[MAX_N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for(int i=1; i<=N; i++)
        cin >> x[i] >> y[i] >> r[i];

    SegTree st(x, y, r, N+1);

    cin >> Q;
    while(Q--) {
        int typ; cin >> typ;
        if(typ == 1) {
            int x, y, l, r; cin >> x >> y >> l >> r;
            st.query(l, r, x, y);
            cout << x << " " << y << "\n";
        }
        else {
            int u, x, y, b; cin >> u >> x >> y >> b;
            st.update(u, x, y, b);
        }
    }

    return 0;
}