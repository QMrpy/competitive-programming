
// The Prestige
// https://www.codechef.com/problems/PRESTIGE
// Implicit treap that supports range flip and range sum
// O((N + M) log N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;

namespace ImplicitTreap {
    const int POOL_SZ = 5e6;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    struct node {
        int lt, rt, sz;
        unsigned prio;
        int val1, val2;
        long long sum1, sum2;
        bool flipped;
    } P[POOL_SZ];
    int pool_cur = 1;

    inline int newnode(int val1, int val2) {
        P[pool_cur].sum1 = P[pool_cur].val1 = val1;
        P[pool_cur].sum2 = P[pool_cur].val2 = val2;
        P[pool_cur].prio = rng();
        P[pool_cur].sz = 1;
        return pool_cur++;
    }

    inline int getsz(int idx) { return idx == 0 ? 0 : P[idx].sz; }
    inline long long getsum1(int idx) { return idx == 0 ? 0 : P[idx].flipped ? P[idx].sum2 : P[idx].sum1; }
    inline long long getsum2(int idx) { return idx == 0 ? 0 : P[idx].flipped ? P[idx].sum1 : P[idx].sum2; }
    inline void mark(int idx) { if (idx) P[idx].flipped ^= 1; }

    inline void update(int idx) {
        if (!idx) return;
        P[idx].sz = getsz(P[idx].lt) + 1 + getsz(P[idx].rt);
        P[idx].sum1 = getsum1(P[idx].lt) + P[idx].val1 + getsum1(P[idx].rt);
        P[idx].sum2 = getsum2(P[idx].lt) + P[idx].val2 + getsum2(P[idx].rt);
    }

    void push(int idx) {
        if (!idx || !P[idx].flipped) return;
        P[idx].flipped = 0;
        swap(P[idx].val1, P[idx].val2);
        swap(P[idx].sum1, P[idx].sum2);
        swap(P[idx].lt, P[idx].rt);
        mark(P[idx].lt); mark(P[idx].rt);
    }

    void merge(int lt, int rt, int &idx) {
        push(lt); push(rt);
        if (!lt) idx = rt;
        else if (!rt) idx = lt;
        else if (P[lt].prio > P[rt].prio)
            merge(P[lt].rt, rt, P[lt].rt), idx = lt;
        else
            merge(lt, P[rt].lt, P[rt].lt), idx = rt;
        update(idx);
    }

    void split(int idx, int pos, int &lt, int &rt) {
        if (!idx) { lt = rt = 0; return; }
        push(idx);
        int curpos = getsz(P[idx].lt) + 1;
        if (pos < curpos)
            split(P[idx].lt, pos, lt, P[idx].lt), rt = idx;
        else
            split(P[idx].rt, pos - curpos, P[idx].rt, rt), lt = idx;
        update(idx);
    }

    void flip(int &idx, int pos1, int pos2) {
        int idx2, idx3;
        split(idx, pos2, idx, idx3);
        split(idx, pos1 - 1, idx, idx2);
        mark(idx2);
        merge(idx, idx2, idx);
        merge(idx, idx3, idx);
    }

    long long getsum(int &idx, int pos1, int pos2) {
        int idx2, idx3;
        split(idx, pos2, idx, idx3);
        split(idx, pos1 - 1, idx, idx2);
        long long res = getsum1(idx2);
        merge(idx, idx2, idx);
        merge(idx, idx3, idx);
        return res;
    }
}

int N, M;
int card1[MAX_N], card2[MAX_N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> card1[i];
    for (int i = 1; i <= N; i++) cin >> card2[i];

    int root = 0;        
    for (int i = 1; i <= N; i++)
        ImplicitTreap::merge(root, ImplicitTreap::newnode(card1[i], card2[i]), root);

    int neg = 0;
    while (M--) {
        int typ; cin >> typ;
        if (typ == 1) {
            int L, R; cin >> L >> R;
            ImplicitTreap::flip(root, L, R);
        } else if (typ == 2) {
            int K; cin >> K;
            neg = K - neg;
        } else {
            int A, B, C, D; cin >> A >> B >> C >> D;
            long long sum = ImplicitTreap::getsum(root, A, B);
            int negcnt = max(0, min(neg, D) - C + 1);
            if (negcnt) sum -= 2 *  ImplicitTreap::getsum(root, A, A + negcnt - 1);
            cout << sum << "\n";
        }
    }

    return 0;
}
