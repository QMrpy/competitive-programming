
// Sereja and Functions (Challenge) 
// https://www.codechef.com/SEPT17/problems/SEAFUNC

// Solution for 51.282 points

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 105;
const int MAX_DISTINCT = 100;

int T, N;
char A[MAX_N][MAX_N];
int wt[MAX_N][MAX_N];

void getlongest(int &typ, int &sx, int &sy, int &len, int &maxw) {
    typ = len = maxw = 0;
    
    /** vertical | **/
    for(int j=1; j<=N; j++) {
        int i = N, c = 0, w = 0;
        while(i>=0) {
            if(A[i][j] != A[i+1][j]) {
                if(A[i+1][j]=='1') {
                    if(w > maxw) {
                        maxw = w;
                        len = c;
                        typ = 1;
                        sx = i+1, sy = j;
                    }
                }
                w = c = 0;
            }
            c++;
            w += wt[i][j];
            i--;
        }
    }
    
    /** diagonal \ **/
    for(int j=1; j<=N; j++) {
        int d = 0, c = 0, w = 0;
        while(1) {
            int x = N-d, y = j-d;
            if(y<0) break;
            
            if(A[x][y]!=A[x+1][y+1]) {
                if(A[x+1][y+1]=='1' && w > maxw) {
                    maxw = w;
                    len = c;
                    typ = 2;
                    sx = x+1, sy = y+1;
                }
                w = c = 0;
            }
            c++;
            w += wt[x][y];
            d++;
        }
    }
    for(int i=1; i<=N; i++) {
        int d = 0, c = 0, w = 0;
        while(1) {
            int x = i-d, y = N-d;
            if(x<0) break;
            
            if(A[x][y]!=A[x+1][y+1]) {
                if(A[x+1][y+1]=='1' && w > maxw) {
                    maxw = w;
                    len = c;
                    typ = 2;
                    sx = x+1, sy = y+1;
                }
                w = c = 0;
            }
            c++;
            w += wt[x][y];
            d++;
        }
    }
    
    /** diagonal / **/
    for(int j=1; j<=N; j++) {
        int d = 0, c = 0, w = 0;
        while(1) {
            int x = N-d, y = j+d;
            if(y>N+1) break;
            
            if(A[x][y]!=A[x+1][y-1]) {
                if(A[x+1][y-1]=='1' && w > maxw) {
                    if(x+1 + y-1 <= N) {
                        maxw = w;
                        len = c;
                        typ = 3;
                        sx = x+1, sy = y-1;
                    }
                }
                w = c = 0;
            }
            c++;
            w += wt[x][y];
            d++;
        }
    }
    for(int i=1; i<=N; i++) {
        int d = 0, c = 0, w = 0;
        while(1) {
            int x = i-d, y = 1+d;
            if(x<0) break;
            
            if(A[x][y]!=A[x+1][y-1]) {
                if(A[x+1][y-1]=='1' && w > maxw) {
                    if(x+1 + y-1 <= N) {
                        maxw = w;
                        len = c;
                        typ = 3;
                        sx = x+1, sy = y-1;
                    }
                }
                w = c = 0;
            }
            c++;
            w += wt[x][y];
            d++;
        }
    }
    
    /** update **/
    if(typ==1) {
        for(int i=0; i<len; i++)
            wt[sx+i][sy] = 0;
    }
    else if(typ==2) {
        for(int i=0; i<len; i++)
            wt[sx+i][sy+i] = 0;
    }
    else if(typ==3) {
        for(int i=0; i<len; i++)
            wt[sx+i][sy-i] = 0;
    }
}

void solve() {
    int ones = 0;
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++)
        if(A[i][j]=='1') wt[i][j] = 1, ones++;
        
    int reqd = ones - MAX_DISTINCT, cur = 0;
    
    vector<string> vout;
    while(cur < reqd) {
        int typ, sx, sy, len, maxw;
        getlongest(typ, sx, sy, len, maxw);
        if(maxw==0) break;
        cur += maxw;
        
        stringstream ss;
        if(typ==1)
            ss << "0 1 0 1 0 1 " << sy << " " << sx << " " << sx+len-1;
        else if(typ==2)
            ss << "0 1 0 1 1 1 " << sy-sx << " " << sx << " " << sx+len-1;
        else if(typ==3)
            ss << "0 1 0 1 -1 1 " << sy+sx << " " << sx << " " << sx+len-1;
        vout.push_back(ss.str());
    }
    
    cout << vout.size() << "\n";
        for(string s : vout)
            cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    while(T--) {
        cin >> N;
        for(int i=1; i<=N; i++)
            cin >> A[i]+1;
        
        solve();
    }
    
    return 0;
}