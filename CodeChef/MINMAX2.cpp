
// Minimum Maximum Confusion
// https://www.codechef.com/problems/MINMAX2
// Dynamic programming with convex hull trick
// O(KN^2) optimized to O(KN)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1111;

struct line {
    long long m, c;
 
    line(long long cc, long long mm) : m(mm), c(cc) {}
 
    long long eval(long long x) {
        return m * x + c;
    }
    
    double intersectX(line l) {
        return (c - l.c) * 1.0 / (l.m - m);
    }
};

int T, N, K;
long long p[MAX_N], q[MAX_N], dp[MAX_N][MAX_N];

void addmin(line &l, deque<line> &dq) {
    line top = dq.front(); dq.pop_front();
    if(l.m == top.m) {
        if(top.c < l.c) l = top;
        if(dq.empty()) {dq.push_front(l); return;}
        top = dq.front(), dq.pop_front();
    }
    while(!dq.empty() && top.intersectX(l) > top.intersectX(dq.front()))
        top = dq.front(), dq.pop_front();
    dq.push_front(top);
    dq.push_front(l);
}

void addmax(line &l, deque<line> &dq) {
    line bot = dq.back(); dq.pop_back();
    if(l.m == bot.m) {
        if(bot.c > l.c) l = bot;
        if(dq.empty()) {dq.push_back(l); return;}
        bot = dq.back(), dq.pop_back();
    }
    while(!dq.empty() && bot.intersectX(l) < bot.intersectX(dq.back()))
        bot = dq.back(), dq.pop_back();
    dq.push_back(bot);
    dq.push_back(l);
}

long long calc(bool mn) {
    deque<line> dq;
    for(int n=1; n<=N; n++) dp[1][n] = p[1] * q[n];
    for(int k=2; k<=K; k++) {
        dq.clear();
        for(int n=k; n<=N; n++) {
            line l(dp[k-1][n-1], p[n]);
            if(dq.empty()) dq.push_back(l);
            else if(mn) addmin(l, dq);
            else addmax(l, dq);
            line top = dq.front(); dq.pop_front();
            while(!dq.empty() && mn ^ top.eval(q[n]) < dq.front().eval(q[n]))
                top = dq.front(), dq.pop_front();
            dq.push_front(top);
            dp[k][n] = top.eval(q[n]);
        }
    }
    return dp[K][N];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    while(T--) {
        cin >> N >> K;
        for(int i=1; i<=N; i++)
            cin >> p[i] >> q[i];
        for(int i=N-1; i>0; i--)
            p[i] = min(p[i+1], p[i]);
        for(int i=2; i<=N; i++)
            q[i] = max(q[i-1], q[i]);
        
        cout << calc(1) << " " << calc(0) << "\n";
    }
    
    return 0;
}