
// Genetics
// https://www.codechef.com/problems/GENETICS
// Persistent implicit treap with range sum
// Complexity: Hard to say due to the "CROSS" operation

#include <bits/stdc++.h>
using namespace std;

namespace ImplicitTreap {
    const int BASES = 4;
    const string BASES_STR = "AGTC";
    const int POOL_SZ = 5e6;

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    struct node {
        int val, cnt[BASES];
        unsigned prio;
        int lt, rt, sz;
    } P[POOL_SZ];
    int pool_cur = 1;

    inline int newnode(char base) {
        P[pool_cur].val = BASES_STR.find(base);
        P[pool_cur].cnt[P[pool_cur].val] = 1;
        P[pool_cur].prio = rng();
        P[pool_cur].sz = 1;
        return pool_cur++;
    }

    inline int copynode(int idx) {
        P[pool_cur] = P[idx];
        return pool_cur++;
    }

    inline int getsz(int idx) { return idx == 0 ? 0 : P[idx].sz; }
    inline int getcnt(int idx, int i) { return idx == 0 ? 0 : P[idx].cnt[i]; }

    inline void update(int idx) {
        if (!idx) return;
        P[idx].sz = getsz(P[idx].lt) + 1 + getsz(P[idx].rt);
        for (int i = 0; i < BASES; i++)
            P[idx].cnt[i] = getcnt(P[idx].lt, i) + getcnt(P[idx].rt, i);
        P[idx].cnt[P[idx].val]++;
    }

    void merge(int lt, int rt, int &idx) {
        if (!lt) idx = rt;
        else if (!rt) idx = lt;
        else if (P[lt].prio > P[rt].prio) {
            idx = copynode(lt);
            merge(P[idx].rt, rt, P[idx].rt);
        } else {
            idx = copynode(rt);
            merge(lt, P[idx].lt, P[idx].lt);
        }
        update(idx);
    }

    void split(int idx, int pos, int &lt, int &rt) {
        if (!idx) { lt = rt = 0; return; }
        int curpos = getsz(P[idx].lt) + 1;
        idx = copynode(idx);
        if (pos < curpos)
            split(P[idx].lt, pos, lt, P[idx].lt), rt = idx;
        else
            split(P[idx].rt, pos - curpos, P[idx].rt, rt), lt = idx;
        update(idx);
    }

    pair<int, int> cross(int idx1, int idx2, int k1, int k2) {
        int idx12, idx22;
        split(idx1, k1, idx1, idx12);
        split(idx2, k2, idx2, idx22);
        merge(idx1, idx22, idx1);
        merge(idx2, idx12, idx2);
        return {idx1, idx2};
    }

    void mutate(int &idx, int k, char m) {
        int idx2, _;
        split(idx, k - 1, idx, idx2);
        split(idx2, 1, _, idx2);
        merge(idx, newnode(m), idx);
        merge(idx, idx2, idx);
    }

    int *count(int idx, int k1, int k2) {
        int _;
        split(idx, k2, idx, _);
        split(idx, k1 - 1, _, idx);
        return P[idx].cnt;
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    int N; cin >> N;
    vector<int> roots = {0};
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        roots.push_back(0);
        for (char base : s)
            ImplicitTreap::merge(roots.back(), ImplicitTreap::newnode(base), roots.back());
    }

    int Q; cin >> Q;
    while (Q--) {
        string op; cin >> op;
        if (op[1] == 'R') {
            int id1, id2, k1, k2; cin >> id1 >> id2 >> k1 >> k2;
            auto p = ImplicitTreap::cross(roots[id1], roots[id2], k1, k2);
            roots.push_back(p.first);
            roots.push_back(p.second);
        } else if (op[1] == 'U') {
            int id, k; char m; cin >> id >> k >> m;
            ImplicitTreap::mutate(roots[id], k, m);
        } else {
            int id, k1, k2; cin >> id >> k1 >> k2;
            int *cnt = ImplicitTreap::count(roots[id], k1, k2);
            for (int i = 0; i < ImplicitTreap::BASES; i++)
                cout << cnt[i] << " ";
            cout << "\n";
        }
    }

    return 0;
}
