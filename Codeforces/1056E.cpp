
// Check Transcription
// https://codeforces.com/contest/1056/problem/E

// Polynomial string hashing
// O(|t|), see editorial for proof (https://codeforces.com/blog/entry/63461)

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e6 + 5;

long long powmod(long long a, long long b, long long m) {
    long long r = 1;
    while (b) {
        if (b & 1) r = r * a % m;
        b >>= 1; a = a * a % m;
    }
    return r;
}

struct hpair {
    long long x, y;
    hpair(): x(0), y(0) {}
    hpair(long long _x, long long _y): x(_x), y(_y) {}
    hpair operator+(hpair p) { return hpair(x + p.x, y + p.y); }
    hpair operator-(hpair p) { return hpair(x - p.x, y - p.y); }
    hpair operator*(hpair p) { return hpair(x * p.x, y * p.y); }
    hpair operator%(hpair p) { return hpair(x % p.x, y % p.y); }
    bool operator==(hpair p) { return x == p.x && y == p.y; }
    bool operator!=(hpair p) { return x != p.x || y != p.y; }
};
const hpair B(257, 259), M(1e9 + 7, 1e9 + 9);

struct strhash {
    vector<hpair> hash, bpow;

    inline hpair inv(hpair a, hpair m) {
        return hpair(powmod(a.x, m.x - 2, m.x), powmod(a.y, m.y - 2, m.y));
    }

    strhash(char *s, int n) {
        hash.resize(n + 1);
        bpow.resize(n + 1);
        bpow[0] = {1, 1};
        for (int i = 1; i <= n; i++) {
            hash[i] = (hash[i - 1] + hpair(s[i - 1], s[i - 1]) * bpow[i - 1]) % M;
            bpow[i] = bpow[i - 1] * B % M;
        }
    }

    inline hpair get(int i, int j) {
        return (hash[j + 1] - hash[i] + M) * inv(bpow[i], M) % M;
    }
};

char s[MAX_N], t[MAX_N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> s;
    int n = strlen(s);
    cin >> t;
    int m = strlen(t);

    int o = 0, z = 0, fo, fz;
    for (int i = 0; i < n; i++)
        if (s[i] == '0') z++;
        else o++;

    strhash sh(t, m);

    long long ans = 0;
    for (int len = 1; ; len++) {
        int rem = m - z * len;
        if (rem <= 0) break;
        if (rem % o) continue;
        int leno = rem / o;
        hpair zh = {-1, -1}, oh = {-1, -1};
        int j = 0, ok = 1;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                if (zh.x == -1) zh = sh.get(j, j + len - 1);
                else if (sh.get(j, j + len - 1) != zh) { ok = 0; break; }
                j += len;
            } else {
                if (oh.x == -1) oh = sh.get(j, j + leno - 1);
                else if (sh.get(j, j + leno - 1) != oh) {ok = 0; break; }
                j += leno;
            }
        }
        if (ok && oh != zh) ans++;
    }

    cout << ans << " ";
    
    return 0;
}
