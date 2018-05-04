
// Mixing Colors
// https://www.codechef.com/problems/LIKECS05

// Fast Fourier transform for polynomial multiplication
// O(N + M + N log N)

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

struct cplex {
    double re, im;
    cplex(double a=0.0, double b=0.0): re(a), im(b) {}
    cplex conj() {return cplex(re, -im); }
    cplex operator+(cplex c) { return cplex(re + c.re, im + c.im); }
    cplex operator-(cplex c) { return cplex(re - c.re, im - c.im); }
    cplex operator*(double x) { return cplex(re * x, im * x); }
    cplex operator/(double x) { return cplex(re / x, im / x); }
    cplex operator*(cplex c) { return cplex(re * c.re - im * c.im, re * c.im + im * c.re); }
    cplex operator/(cplex c) { return c.conj() * *this / (c.re * c.re + c.im * c.im); }

    static const cplex ZERO, ONE, I;
};

const cplex cplex::ZERO(0.), cplex::ONE(1.), cplex::I(0., 1.);

namespace FFT {
    const int K = 18;
    const int N = 1 << K;
    vector<cplex> W, invW;
    vector<int> rev;

    void init() {
        int n2 = N >> 1;
        W.resize(n2); invW.resize(n2);
        double ang = 2 * PI / N;
        for (int i = 0; i < n2; i++)
            W[i] = cplex(cos(i * ang), sin(i * ang)), invW[i] = W[i].conj();
        rev.resize(N);
    }

    vector<int> toint(vector<cplex> a) {
        vector<int> v(a.size());
        for (int i = 0; i < a.size(); i++) v[i] = a[i].re + 0.5;
        return v;
    }

    void transform(vector<cplex> &a, bool inv=false) {
        int k = 0; while ((1 << k) < a.size()) k++;
        int n = 1 << k;
        a.resize(n, cplex::ZERO);
        rev[0] = 0;
        for (int i = 1; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (k - 1));
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        }

        vector<cplex> &twiddle = inv ? invW : W;
        for (int len = 2; len <= n; len <<= 1) {
            int half = len >> 1, diff = N / len;
            for (int i = 0; i < n; i += len) {
                int pw = 0;
                for (int j = i; j < i + half; j++) {
                    cplex v = a[j + half] * twiddle[pw];
                    a[j + half] = a[j] - v;
                    a[j] = a[j] + v;
                    pw += diff;
                }
            }
        }

        if (inv) for (cplex &x : a) x = x / n;
    }

    void convolve(vector<cplex> &a, vector<cplex> &b) {
        int m = a.size() + b.size() - 1;
        a.resize(m, cplex::ZERO); transform(a);
        b.resize(m, cplex::ZERO); transform(b);
        for (int i = 0; i < a.size(); i++)
            a[i] = a[i] * b[i];
        transform(a, true);
        a.resize(m);
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    FFT::init();

    int N, M; cin >> N >> M;
    set<int> row[3], col[3], diag[3];
    for (int i = 0; i < M; i++) {
        int typ, idx, color; cin >> typ >> idx >> color;
        if (typ == 1) {
            row[color].insert(idx);
            row[2].insert(idx);
        } else if (typ == 2) {
            col[color].insert(idx);
            col[2].insert(idx);
        } else {
            diag[color].insert(idx);
            diag[2].insert(idx);
        }
    }

    long long colorcnt[3];
    for (int i = 0; i < 3; i++) {
        vector<cplex> Pr(N + 1, cplex::ONE), Pc(N + 1, cplex::ONE);
        Pr[0] = Pc[0] = cplex::ZERO;
        for (int x : row[i]) Pr[x] = cplex::ZERO;
        for (int x : col[i]) Pc[x] = cplex::ZERO;
        FFT::convolve(Pr, Pc);
        vector<int> P = FFT::toint(Pr);
        P.resize(2 * N + 1);

        long long rcnt = row[i].size(), ccnt = col[i].size();
        colorcnt[i] = N * (rcnt + ccnt) - rcnt * ccnt;
        for (int x : diag[i]) colorcnt[i] += P[x];
    }

    long long ans[4];
    ans[3] = colorcnt[0] + colorcnt[1] - colorcnt[2];
    ans[2] = colorcnt[0] - ans[3];
    ans[1] = colorcnt[1] - ans[3];
    ans[0] = 1LL * N * N - ans[1] - ans[2] - ans[3];
    cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";

    return 0;
}