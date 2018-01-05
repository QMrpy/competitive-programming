
// Sum of distances
// https://www.codechef.com/problems/SUMDIS
// Editorial's approach
// https://discuss.codechef.com/questions/92942/sumdis-editorial
// Divide and conquer with a sweepline algorithm at every level
// O(N log^2 N)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5 + 5;
const int INF = 1 << 30;

struct point {
    int x, y, w;

    bool operator<(const point &p) const {
        return x == p.x ? w < p.w : x < p.x;
    }
};

int fenwick[MAX_N], fenwickn;
void fenwickinit(int n) {
    fenwickn = n; fill_n(fenwick+1, n, 0);
}
void fenwickincr(int i) {
    for(; i<=fenwickn; i+=i&-i) fenwick[i]++;
}
int fenwickquery(int i) {
    int s = 0;
    for(; i; i-=i&-i) s += fenwick[i];
    return s;
}


int T, N, a[3][MAX_N];
int dto[3][MAX_N], dfr[3][MAX_N];   // distance to/from M-1, M and M+1

long long calcfr(int start, int R, int d[]) {
    long long s = 0;
    fill(d+start, d+R+1, INF);
    d[start] = 0;
    for(int i=start; i<=R; i++) {
        for(int j=1; j<=3; j++) d[i+j] = min(d[i+j], d[i] + a[j-1][i]);
        s += d[i];
    }
    return s;
}

long long calcto(int L, int end, int d[]) {
    long long s = 0;
    fill(d+L, d+end, INF);
    d[end] = 0;
    for(int i=end-1; i>=L; i--) {
        for(int j=1; j<=3 && i+j<=end; j++) d[i] = min(d[i], d[i+j] + a[j-1][i]);
        s += d[i];
    }
    return s;
}

long long naive(int L, int R) {
    long long s = 0;
    for(int i=L; i<R; i++) s += calcfr(i, R, dfr[0]);
    return s;
}

long long sweepline(vector<point> &v1, vector<point> &v2) {
    // For each point (x_i, y_i) in v1, add to sum w_i multiplied by
    // the number of points (x_j, y_j) in v2 that satisfy x_j <= x_i and y_j <= y_i

    // Approach requires a sweepline algorithm with an order statistic tree
    // More compact implementation below avoids the order statistic tree using
    // coordinate compression and a fenwick tree

    vector<point> events(v1.begin(), v1.end());
    for(point &p : v2) events.push_back({p.x, p.y, -1});
    sort(events.begin(), events.end());

    vector<int> vals;
    for(point &p : events) vals.push_back(p.y);
    sort(vals.begin(), vals.end());
    auto last = unique(vals.begin(), vals.end());
    vals.erase(last, vals.end());

    long long s = 0;
    fenwickinit(vals.size());
    for(point &p : events) {
        p.y = lower_bound(vals.begin(), vals.end(), p.y) - vals.begin() + 1;
        if(p.w == -1) fenwickincr(p.y);
        else s += fenwickquery(p.y) * 1LL * p.w;
    }
    return s;
}

long long recur(int L, int R) {
    if(R-L < 5) return naive(L, R);
    int M = (R + L) >> 1;

    long long s = recur(L, M-2) + recur(M+2, R);
    long long g = calcto(L, M-1, dto[0]) + calcto(L, M, dto[1])
                  + calcfr(M, R, dfr[1]) + calcfr(M+1, R, dfr[2]);
    calcfr(M-1, R, dfr[0]);
    calcto(L, M+1, dto[2]);

    long long f = 0;
    for(int m=0; m<3; m++) {
        int m1=1, m2=2;
        if(m==1) m1=0, m2=2;
        if(m==2) m1=0, m2=1;

        vector<point> v1, v2;
        for(int i=L; i<M; i++) v1.push_back({dto[m1][i] - dto[m][i], dto[m2][i] - dto[m][i], dto[m][i]});
        for(int j=M+1; j<=R; j++) v2.push_back({dfr[m][j] - dfr[m1][j], dfr[m][j] - dfr[m2][j], dfr[m][j]});
        f += sweepline(v1, v2);

        for(point &p : v1) p.x = -p.x, p.y = -p.y;
        for(point &p : v2) p.x = -p.x, p.y = -p.y;
        f += sweepline(v2, v1);

        // avoid double-counting ties
        for(int i=L; i<M; i++) dto[m][i]--;
    }
    return s + g + f;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while(T--) {
        cin >> N;
        for(int i=1; i<N; i++) cin >> a[0][i];
        for(int i=1; i<N-1; i++) cin >> a[1][i];
        for(int i=1; i<N-2; i++) cin >> a[2][i];

        cout << recur(1, N) << "\n";
    }

    return 0;
}