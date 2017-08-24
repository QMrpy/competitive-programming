#include <bits/stdc++.h>
using namespace std;

// hacky approach

const int MAX_N = 1e5+5;
const int MAX_LG_N = 18;
const int MAX_Q = 1e5+5;
const int MAX_JUMP = 100;

int N, Q, a[MAX_N];
int dep[MAX_N], anc[MAX_LG_N][MAX_N];
unordered_set<int> ch[MAX_N];

long long tmp[MAX_N];
int nxt[MAX_N];
int top, stck[MAX_N];

int qry[MAX_Q][4];


int tree_n;
long long tree[MAX_N<<2];

long long tree_query(int i) {
    long long res = a[i];
    for(i+=tree_n; i>0; i>>=1)
        res += tree[i];
    return res;
}

void tree_update(int i, int j, int X) {
    for(i+=tree_n, j+=tree_n; i<j; i>>=1, j>>=1) {
        if(i&1) tree[i++] += X;
        if(j&1) tree[--j] += X;
    }
}


inline void updateanc(int i) {
    for(int j=1; j<MAX_LG_N; j++)
        anc[j][i] = anc[j-1][anc[j-1][i]];
}

void dfsupdate(int i) {
    updateanc(i);
    for(int j : ch[i])
        dfsupdate(j);
}

void update(int i) {
    if(anc[0][i]!=i) ch[anc[0][i]].erase(i);
    if(nxt[i]!=i) ch[nxt[i]].insert(i);
    anc[0][i] = nxt[i];
    
    updateanc(i);
    for(int j : ch[i])
        dfsupdate(j);
}

int calcnxt(int p1, int p2, bool first=false) {
    for(int i=p1; i<=p2; i++)
        tmp[i] = first ? a[i] : tree_query(i);
    top = -1;
    stck[++top] = p1;
    nxt[p1] = p1;
    for(int i=p1+1; i<=p2; i++) {
        nxt[i] = i;
        while(top>=0 && tmp[stck[top]] < tmp[i]) {
            if(i <= stck[top]+MAX_JUMP)
                nxt[stck[top]] = i;
            top--;
        }
        stck[++top] = i;
    }
}

void rangeupdate(int L, int R, int X) {
    tree_update(L, R+1, X);
    
    int p1, p2;
    p1 = max(L, R-MAX_JUMP+1);
    p2 = min(N, R+MAX_JUMP);
    calcnxt(p1, p2);
    for(int i=R; i>=max(L, R-MAX_JUMP+1); i--)
        if(nxt[i]!=anc[0][i])
            update(i);
    
            
    p1 = max(1, L-MAX_JUMP);
    p2 = min(N, L-1+MAX_JUMP);
    calcnxt(p1, p2);
    for(int i=L-1; i>=max(1, L-MAX_JUMP); i--)
        if(nxt[i]!=anc[0][i])
            update(i);
}

void rangeupdate_easy(int L, int R, int X) {
    tree_update(L, R+1, X);
    
    int p1, p2;
    p1 = max(L, R-MAX_JUMP+1);
    p2 = min(N, R+MAX_JUMP);
    calcnxt(p1, p2);
    for(int i=R; i>=max(L, R-MAX_JUMP+1); i--)
        anc[0][i] = nxt[i];
    
            
    p1 = max(1, L-MAX_JUMP);
    p2 = min(N, L-1+MAX_JUMP);
    calcnxt(p1, p2);
    for(int i=L-1; i>=max(1, L-MAX_JUMP); i--)
        anc[0][i] = nxt[i];
}

int getkth(int i, int k) {
    for(int j=0; k && anc[j][i]!=i; j++) {
        if(k&1) i = anc[j][i];
        k >>= 1;
    }
    return i;
}

int getkth_easy(int i, int k) {
    while(k-- && i!=anc[0][i])
        i = anc[0][i];
    return i;
}

void init() {
    tree_n = 1;
    while(tree_n <= N)
        tree_n <<= 1;
    calcnxt(1, N, true);
    for(int i=N; i>=1; i--) {
        if(nxt[i]!=i) ch[nxt[i]].insert(i);
        anc[0][i] = nxt[i];
        updateanc(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N >> Q;
    for(int i=1; i<=N; i++)
        cin >> a[i];
    
    init();
    
    int typ_1 = 0, typ_2 = 0;
    for(int q=0; q<Q; q++) {
        cin >> qry[q][0];
        if(qry[q][0]==1) {
            cin >> qry[q][1] >> qry[q][2];
            typ_1++;
        }
        else {
            cin >> qry[q][1] >> qry[q][2] >> qry[q][3];
            typ_2++;
        }
    }
    
    if(typ_1<=1000) {
        for(int q=0; q<Q; q++)
            if(qry[q][0]==1)
                cout << getkth_easy(qry[q][1], qry[q][2]) << "\n";
            else
                rangeupdate_easy(qry[q][1], qry[q][2], qry[q][3]);
    }
    else {
        for(int q=0; q<Q; q++)
            if(qry[q][0]==1)
                cout << getkth(qry[q][1], qry[q][2]) << "\n";
            else
                rangeupdate(qry[q][1], qry[q][2], qry[q][3]);
    }
    
    return 0;
}