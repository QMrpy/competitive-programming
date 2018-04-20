
// A humongous Query
// https://www.codechef.com/JAN18/problems/XYHUMOQ
// Binary search on Stern-Brocot tree
// https://discuss.codechef.com/questions/121386/xyhumoq-editorial?page=1#121480
// O(X |S|)

#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
    
struct frac {
    int num, den;
    
    frac(int n, int d): num(n), den(d) {}

    bool operator==(frac &f) {
        return num == f.num && den == f.den;
    }

    bool operator<(frac &f) {
        return 1LL * num * f.den < 1LL * den * f.num;
    }
};

int T, N, X, S;

int solve() {
    X++;
    int ans = N + 1;
    for(int i=1; i<X; i++) {
        if(gcd(i, X) != 1)
            continue;
        frac k(i, X);
        frac l(0, 1), h(1, 1), m(-1, 1);
        int dep = 0, idx = 0;
        while(dep <= N) {
            m = frac(l.num + h.num, l.den + h.den);
            if(m == k)
                break;
            dep++;
            idx <<= 1;
            if(k < m)
                h = m;
            else {
                l = m;
                idx++;
            }
        }
        if(k == m && dep == N)
            ans = min(ans, __builtin_popcount(S ^ idx));
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while(T--) {
        string s; cin >> s;
        s.erase(s.begin()); s.erase(--s.end());
        N = s.size();
        S = 0;
        for(int i=0; i<N; i++)
            S |= (s[i] - '0') << i;
        cin >> X;
        int ans = solve();
        if(ans > N) cout << "NO\n";
        else cout << "YES\n" << ans << "\n";
    }

    return 0;
}