#include <bits/stdc++.h>
using namespace std;

const long long MODVAL = 1e9 + 7;
const long long MAXSIZE = 60;
const long long MAXVAL = 150;

int T, n, a[MAXSIZE];
long long dp[MAXSIZE][MAXVAL][MAXVAL];

long long f(int i, int x, int y) {
    if(i==n-2)
        return 1;
    if(dp[i][x][y]==-1) {
        long long cnt = 0;
        int x1 = x, y1 = y, z = a[i+2];
        while(x1>=0 && y1>=0) {
            cnt = (cnt + f(i+1, y1, z)) % MODVAL;
            x1--; y1--; z++;
        }
        dp[i][x][y] = cnt;
    }
    return dp[i][x][y];
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> T;
    while(T--) {
        memset(a, 0, sizeof a);
        memset(dp, -1, sizeof dp);
        
        cin >> n;
        for(int i=0; i<n; i++)
            cin >> a[i];
        n += 10;
        
        long long ans = f(0, a[0], a[1]);
        cout << ans << "\n";
    }
    
    return 0;
}