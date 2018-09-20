
// Sasha and Photos
// https://www.codechef.com/SEPT18A/problems/PHOTOCOM

// O(h1 * w1 + h2 * w2)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 5;

int T, h1, w1, h2, w2;
vector<int> g1[MAX_N], g2[MAX_N];
vector<int> pre[MAX_N];

int initpre() {
    pre[0].resize(w1 + 1);
    for (int i = 1; i <= h1; i++) {
        pre[i].resize(w1 + 1);
        for (int j = 1; j <= w1; j++)
            pre[i][j] = g1[i - 1][j - 1] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    }
}

inline int rectsum(int i1, int i2, int j1, int j2) {
    if (i2 < i1 || j2 < j1) return 0;
    return pre[i2 + 1][j2 + 1] - pre[i2 + 1][j1] - pre[i1][j2 + 1] + pre[i1][j1];
}

long long solve() {
    initpre();

    int hgcd = __gcd(h1, h2), wgcd = __gcd(w1, w2);
    long long h1mul = h2 / hgcd, h2mul = h1 / hgcd;
    long long w1mul = w2 / wgcd, w2mul = w1 / wgcd;

    long long ans = 0;

    for (int i = 0; i < h2; i++) for (int j = 0; j < w2; j++) {
        // scaled up photo 2
        long long h2s = i * h2mul, h2e = h2s + h2mul - 1;
        long long w2s = j * w2mul, w2e = w2s + w2mul - 1;

        // original photo 1
        int i1s = h2s / h1mul, i1e = h2e / h1mul;
        int j1s = w2s / w1mul, j1e = w2e / w1mul;

        long long cnt = 0;
        if (i1s == i1e && j1s == j1e) {
            cnt = g1[i1s][j1s] * h2mul * w2mul;

        } else if (i1s == i1e && j1s < j1e) {
            int inside = rectsum(i1s, i1s, j1s + 1, j1e - 1);

            long long wmulleft = w1mul - w2s % w1mul;
            long long wmulright = 1 + w2e % w1mul;

            cnt = inside * w1mul;
            cnt += g1[i1s][j1s] * wmulleft;
            cnt += g1[i1s][j1e] * wmulright;
            cnt *= h2mul;

        } else if (i1s < i1e && j1s == j1e) {
            int inside = rectsum(i1s + 1, i1e - 1, j1s, j1s);

            long long hmultop = h1mul - h2s % h1mul;
            long long hmulbot = 1 + h2e % h1mul;

            cnt = inside * h1mul;
            cnt += g1[i1s][j1s] * hmultop;
            cnt += g1[i1e][j1s] * hmulbot;
            cnt *= w2mul;

        } else {
            int inside = rectsum(i1s + 1, i1e - 1, j1s + 1, j1e - 1);
            int top = rectsum(i1s, i1s, j1s + 1, j1e - 1);
            int bot = rectsum(i1e, i1e, j1s + 1, j1e - 1);
            int left = rectsum(i1s + 1, i1e - 1, j1s, j1s);
            int right = rectsum(i1s + 1, i1e - 1, j1e, j1e);

            long long hmultop = h1mul - h2s % h1mul;
            long long hmulbot = 1 + h2e % h1mul;
            long long wmulleft = w1mul - w2s % w1mul;
            long long wmulright = 1 + w2e % w1mul;

            cnt = inside * h1mul * w1mul;
            cnt += top * hmultop * w1mul;
            cnt += bot * hmulbot * w1mul;
            cnt += left * h1mul * wmulleft;
            cnt += right * h1mul * wmulright;
            cnt += g1[i1s][j1s] * hmultop * wmulleft;
            cnt += g1[i1s][j1e] * hmultop * wmulright;
            cnt += g1[i1e][j1s] * hmulbot * wmulleft;
            cnt += g1[i1e][j1e] * hmulbot * wmulright;
        }

        if (g2[i][j]) ans += cnt;
        else ans += h2mul * w2mul - cnt;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while (T--) {
        string tmp;
        cin >> h1 >> w1 >> tmp;
        for (int i = 0; i < h1 * w1; i++)
            g1[i / w1].push_back(tmp[i] & 1);
        cin >> h2 >> w2 >> tmp;
        for (int i = 0; i < h2 * w2; i++)
            g2[i / w2].push_back(tmp[i] & 1);

        cout << solve() << "\n";

        for (int i = 0; i < h1; i++)
            g1[i].clear();
        for (int i = 0; i < h2; i++)
            g2[i].clear();
    }

    return 0;
}