
// Coordinate Compression
// https://www.codechef.com/AUG18A/problems/KCOMPRES

// Binary search + Segment tree
// O(N log^2 N)
// Note: Problem is a mess with unclear problem statement, not sure what was actually intended
// See discussion at https://discuss.codechef.com/questions/133405/kcompres-editorial/133804

#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 30;
const int MAX_N = 1e5 + 5;

int T, N, A[MAX_N];
long long S;
map<int, vector<int> > pos;

struct SegTree {
    int N;
    vector<int> tree;

    SegTree(int n) {
        N = 1; while (N < n) N <<= 1;
        tree.resize(N << 1);
    }

    int query(int i, int j) {
        int v = 0;
        for (i += N, j += N; i <= j; i = (i + 1) >> 1, j = (j - 1) >> 1){
            if ((i & 1) == 1) v = max(v, tree[i]);
            if ((j & 1) == 0) v = max(v, tree[j]);
        }
        return v;
    }

    void update(int i, int v) {
        tree[i + N] = v;
        for(i = (i + N) >> 1; i > 0; i >>= 1)
            tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }
};

long long cost(int k) {
    SegTree st(N);
    long long sum = 0;
    for (auto &p : pos) {
        auto &v = p.second;
        for (int i = 0; i < v.size(); ) {
            int j = i + 1;
            while (j < v.size() && v[j] - v[j - 1] <= k) j++;
            int label = st.query(max(0, v[i] - k), min(v[j - 1] + k, N - 1)) + 1;
            for (int x = i; x < j; x++)
                st.update(v[x], label);
            sum += 1LL * (j - i) * label;
            i = j;
        }
    }
    return sum;
}

int solve() {
    pos.clear();
    for (int i = 0; i < N; i++)
        pos[A[i]].push_back(i);

    int lo = -1, hi = N, mid;
    while (lo < hi) {
        mid = (lo + hi + 1) >> 1;
        if (cost(mid) <= S)
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo + 1;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N >> S;
        for (int i = 0; i < N; i++)
            cin >> A[i];

        cout << solve() << "\n";
    }

    return 0;
}
