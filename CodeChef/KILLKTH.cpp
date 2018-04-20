
// Killjee and k-th letter
// https://www.codechef.com/JAN18/problems/KILLKTH
// Suffix array, Longest common prefix array, Binary search

// Precalculation: O(N log^2 N)
// Queries: O(Q log N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 2e5 + 5;

int N, Q;
char S[MAX_N];
long long G, P, M, K;
long long pre[MAX_N];
vector<long long> a[MAX_N], b[MAX_N];
int sa[MAX_N], lcp[MAX_N];

void init_sa_lcp() {
    vector<pair<pair<int, int>, int> > v(N + 1);
    vector<int> rank(N + 1);
    for(int i=1; i<=N; i++)
        rank[i] = S[i] - 'a' + 1;
    if(N == 1) rank[1] = 1;

    for(int j=1, k=1; k<N; j++, k<<=1) {
        for(int i=1; i<=N; i++)
            v[i] = {{rank[i], i+k<=N ? rank[i+k] : -1}, i};
        sort(v.begin() + 1, v.end());
        for(int i=1; i<=N; i++)
            rank[v[i].second] = v[i-1].first==v[i].first ? rank[v[i-1].second] : i;
    }
    for(int i=1; i<=N; i++)
        sa[rank[i]] = i;

    int k = 0;
    for(int i=1; i<=N; i++) {
        if(rank[i] == N) {k = 0; continue;}
        int j = sa[rank[i] + 1];
        while(i+k <= N && j+k <= N && S[i+k] == S[j+k]) k++;
        lcp[rank[i]] = k;
        if(k) k--;
    }
}

inline long long getcnt(int i, int j, long long x) {
    return (a[i][j-1] * x + x * (x + 1) / 2) * (a[i].size() - j);
}

void init_precalc() {
    for(int i=1; i<=N; i++) {
        int cur = N - sa[i] + 1;
        for(int j=i; j<=N; j++) {
            if(cur <= lcp[i-1]) break;
            a[i].push_back(cur);
            cur = min(cur, lcp[j]);
        }
        a[i].push_back(lcp[i-1]);
        reverse(a[i].begin(), a[i].end());
        b[i].resize(a[i].size());
        for(int j=1; j<a[i].size(); j++) {
            int dif = a[i][j] - a[i][j-1];
            b[i][j] = b[i][j-1] + getcnt(i, j, dif);
        }
        pre[i] = pre[i-1] + b[i].back();
    }
}

char query() {
    int i = lower_bound(pre, pre+N+1, K) - pre;
    K -= pre[i-1];
    
    int j = lower_bound(b[i].begin(), b[i].end(), K) - b[i].begin();
    K -= b[i][j-1];
    
    int lo, hi, mid;
    lo = 1, hi = a[i][j] - a[i][j-1];
    while(lo < hi) {
        mid = (lo + hi) >> 1;
        if(getcnt(i, j, mid) >= K) hi = mid;
        else lo = mid + 1;
    }
    K -= getcnt(i, j, lo-1);
    
    K = (K - 1) % (a[i][j-1] + lo);
    return S[sa[i] + K];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> S + 1;
    N = strlen(S + 1);

    init_sa_lcp();
    init_precalc();

    cin >> Q;
    while(Q--) {
        cin >> P >> M;
        K = (P * G) % M + 1;
        char c = query();
        cout << c << "\n";
        G += c;
    }

    return 0;
}
