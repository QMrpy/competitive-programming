
// [IOI] Guardians of the Lunatics
// https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/guardians-lunatics-ioi14
// Dynamic programming with divide and conquer optimization
// O(G L log L)

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;
const int MAX_L = 8080;
const int MAX_G = 808;

int L, G;
long long C[MAX_L], pre[MAX_L], dp[MAX_G][MAX_L];

void recur(int g, int iL, int iR, int jL, int jR) {
    if(iL > iR)
        return;
    int iM = (iL + iR) >> 1;
    int jBest = -1;
    long long &res = dp[g][iM] = INF;
    for(int j=jL; j<=min(jR, iM-1); j++) {
        long long v = dp[g-1][j] + (pre[iM] - pre[j]) * (iM - j);
        if(v < res) {
            res = v;
            jBest = j;
        }
    }
    recur(g, iL, iM-1, jL, jBest);
    recur(g, iM+1, iR, jBest, jR);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> L >> G;
    for(int i=1; i<=L; i++) {
        cin >> C[i];
        pre[i] = pre[i-1] + C[i];
    }
        
    for(int i=1; i<=L; i++) dp[0][i] = INF;
    
    for(int g=1; g<=G; g++)
        recur(g, 1, L, 0, L-1);
        
    cout << dp[G][L] << "\n";
    
    return 0;
}

