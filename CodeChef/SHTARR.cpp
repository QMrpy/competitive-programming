
// Shooting on the array
// https://www.codechef.com/OCT17/problems/SHTARR

// Segment tree
// Each node stores max in its range (mx) and answer for L=0, R=INF (ch)
// O(log^2 N) per query

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 5;
const int MAX_Q = 1e5 + 5;

int T, N, Q, A[MAX_N];

struct st_node {
    int mx, ch;
    int s, e, m;
} nodes[MAX_N<<3];
st_node dummy;

st_node query1(int id, int lo) {
    st_node &cur = nodes[id],
            &lt = nodes[id<<1],
            &rt = nodes[id<<1|1];
    if(cur.s==cur.e) {
        if(cur.mx>=lo)
            return cur;
        return dummy;
    }
    st_node res = dummy;
    if(lt.mx>=lo) {
        res = query1(id<<1, lo);
        res.ch = cur.ch - lt.ch + res.ch;
        res.mx = max(lt.mx, rt.mx);
    }
    else if(rt.mx>=lo) 
        res = query1(id<<1|1, lo);
    return res;
}

void build(int id, int s, int e) {
    st_node &cur = nodes[id],
            &lt = nodes[id<<1],
            &rt = nodes[id<<1|1];
    cur.s = s; cur.e = e; cur.m = (s+e)>>1;
    if(s==e) {
        cur.mx = A[s]; cur.ch = 1;
        return;
    }
    build(id<<1, s, cur.m);
    build(id<<1|1, cur.m+1, e);

    st_node res = query1(id<<1|1, lt.mx+1);
    cur.mx = max(lt.mx, rt.mx);
    cur.ch = lt.ch + res.ch;
}

void update(int id, int i, int x) {
    st_node &cur = nodes[id],
            &lt = nodes[id<<1],
            &rt = nodes[id<<1|1];
    if(cur.s==cur.e) {
        cur.mx += x;
        return;
    }
    if(i<=cur.m) update(id<<1, i, x);
    else update(id<<1|1, i, x);

    st_node res = query1(id<<1|1, lt.mx+1);
    cur.mx = max(lt.mx, rt.mx);
    cur.ch = lt.ch + res.ch;
}

st_node query2(int id, int lo, int s, int e) {
    st_node &cur = nodes[id],
            &lt = nodes[id<<1],
            &rt = nodes[id<<1|1];
    if(s<=cur.s && cur.e<=e)
        return query1(id, lo);
    
    st_node lres = dummy, rres = dummy;
    if(s<=cur.m) lres = query2(id<<1, lo, s, e);
    if(cur.m<e) rres = query2(id<<1|1, max(lres.mx+1, lo), s, e);
    st_node res;
    res.mx = max(lres.mx, rres.mx);
    res.ch = lres.ch + rres.ch;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while(T--) {
        cin >> N >> Q;
        for(int i=1; i<=N; i++)
            cin >> A[i];

        build(1, 1, N);
        while(Q--) {
            char s[2];
            cin >> s;
            if(s[0]=='+') {
                int i, X;
                cin >> i >> X;
                update(1, i, X);
            }
            else {
                int i, L, R;
                cin >> i >> L >> R;
                int ansL = query2(1, L, i, N).ch,
                    ansR = query2(1, R, i, N).ch;
                int ans = ansL - ansR;
                if(ansR>0) ans++;
                cout << ans << "\n";
            }
        }
    }
    
    return 0;
}
