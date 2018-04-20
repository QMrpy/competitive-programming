
// Simplify the Square Root
// https://www.codechef.com/JAN18/problems/SQRGOOD

// Solution based on
// Counting Square-Free Numbers, Jakub Pawlewicz
// https://arxiv.org/abs/1107.4890

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 3e7 + 5;

long long N;
int pr[MAX_N], lp[MAX_N], pc;
int mu[MAX_N]; // Möbius function
int M[MAX_N]; // Mertens function
unordered_map<int, int> Mcache;

void init() {
    M[1] = mu[1] = 1;
    for(int i=2; i<MAX_N; i++) {
        if(!lp[i]) {
            lp[i] = i;
            pr[pc++] = i;
        }
        if((i / lp[i]) % lp[i] == 0) mu[i] = 0;
        else mu[i] = -mu[i / lp[i]];
        M[i] = M[i-1] + mu[i];
        for(int j=0; j<pc && pr[j]<=lp[i] && i*pr[j]<MAX_N; j++)
            lp[i * pr[j]] = pr[j];
    }
}

long long getS1(long long n, int D) {
    long long sum = 0;
    for(int i=1; i<=D; i++)
        sum += mu[i] * (n / i / i);
    return sum;
}

int getMx(int x) {
    if(x < MAX_N)
        return M[x];
    if(Mcache.count(x))
        return Mcache[x];
    int Mx = 0;
    for(int d=1; d<=x; ) {
        int e = x / d, f = x / e;
        if(e < x) Mx += getMx(e) * (f - d + 1);
        d = f + 1;
    }
    Mx = 1 - Mx;
    return Mcache[x] = Mx;
}

long long getS2(long long n, int I) {
    int xI = sqrt(n * 1.0 / I);
    long long sum = -(I - 1LL) * getMx(xI);
    for(int i=I-1; i>=1; i--) {
        int xi = sqrt(n * 1.0 / i);
        sum += getMx(xi);
    }
    return sum;
}

long long count(long long n) {
    if(n < 1e7)
        return n - getS1(n, sqrt(n) + 10);
    int I = pow(n, 0.333), D = sqrt(n / I);
    D = min(D, MAX_N - 1);
    I = n / D / D;
    return n - getS1(n, D) - getS2(n, I);
}

long long solve() {
    long long lo, hi, mid;
    if(N < 1e8) lo = N, hi = N * 5;
    else if(N < 1e14) lo = N * 2.550545, hi = N * 2.550547;
    else lo = N * 2.55054609672, hi = N * 2.55054609674;
    while(lo < hi) {
        mid = (lo + hi) >> 1;
        if(count(mid) < N) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    init();
    cin >> N;
    cout << solve();

    return 0;
}