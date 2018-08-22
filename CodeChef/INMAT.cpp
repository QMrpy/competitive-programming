
// Interactive Matrix
// https://www.codechef.com/AUG18A/problems/INMAT

// Ad-hoc
// Solution nearly same as editorial: https://discuss.codechef.com/questions/133988/inmat-editorial

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1005;

int N, K, V;
pair<int, pair<int, int> > grid[MAX_N][MAX_N];
bool rdec[MAX_N], cdec[MAX_N];
int qcnt;

inline int get(int r, int c) {
    if (grid[r][c].first) return grid[r][c].first;
    assert(++qcnt <= K);
    int r_, c_; tie(r_, c_) = grid[r][c].second;
    cout << "1 " << r_ << " " << c_ << endl;
    cin >> grid[r][c].first;
    if (grid[r][c].first == V) {
        cout << "2 " << r_ << " " << c_ << endl;
        exit(0);
    }
    return grid[r][c].first;
}

inline void transpose() {
    for (int i = 1; i <= N; i++) {
        swap(rdec[i], cdec[i]);
        for (int j = 1; j < i; j++) swap(grid[i][j], grid[j][i]);
    }
}

inline void flip_all_rows() {
    for (int c1 = 1, c2 = N; c1 < c2; c1++, c2--) {
        swap(cdec[c1], cdec[c2]);
        for (int r = 1; r <= N; r++) swap(grid[r][c1], grid[r][c2]);
    }
    for (int r = 1; r <= N; r++) rdec[r] = !rdec[r];
}

inline void flip_col(int r11, int r22, int c) {
    for (int r1 = r11, r2 = r22; r1 < r2; r1++, r2--) swap(grid[r1][c], grid[r2][c]);
}

void solve_rows_sorted(int r1, int r2, int c1, int c2) {
    bool flipped_rows = 0;
    if (rdec[r1]) {
        flip_all_rows();
        swap(c1, c2);
        c1 = N + 1 - c1;
        c2 = N + 1 - c2;
        flipped_rows = 1;
    }
    vector<int> flipped_cols;
    for (int c = c1; c <= c2; c++) if (cdec[c]) {
        flip_col(r1, r2, c);
        flipped_cols.push_back(c);
    }

    int r = r1, c = c2;
    while (r <= r2 && c >= c1) {
        if (get(r, c) < V) r++;
        else c--;
    }

    for (int c : flipped_cols) flip_col(r1, r2, c);
    if (flipped_rows) flip_all_rows();
}

void solve_naive() {
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) get(i, j);

    cout << "2 -1 -1" << endl;
    exit(0);
}

void solve() {
    for (int r = 1; r <= N; r++) for (int c = 1; c <= N; c++)
        grid[r][c].second = {r, c};

    if (N * N <= K) solve_naive();

    int frcnt = 0, fccnt = 0;
    for (int i = 1; i <= N; i++) {
        int j = N + 1 - i;
        if (i == j) j++;
        rdec[i] = i > j ^ get(i, i) > get(i, j);
        cdec[i] = i > j ^ get(i, i) > get(j, i);
        if (i > 1) {
            if (rdec[i] != rdec[i - 1]) frcnt++;
            if (cdec[i] != cdec[i - 1]) fccnt++;
        }
    }

    if (frcnt == 0) {
        solve_rows_sorted(1, N, 1, N);
    } else if (fccnt == 0) {
        transpose();
        solve_rows_sorted(1, N, 1, N);
    } else {
        assert(frcnt == 1 && fccnt == 1);
        assert(rdec[1] == cdec[1]);
        if (rdec[1]) flip_all_rows();

        int fx = 1, fy = 1;
        while (rdec[++fx] == 0);
        while (cdec[++fy] == 0);

        if (V < get(fx - 1, fy - 1))
            solve_rows_sorted(1, fx - 1, 1, fy - 1);
        if (get(fx - 1, fy) < V)
            solve_rows_sorted(1, fx - 1, fy, N);
        if (get(fx, fy - 1) < V)
            solve_rows_sorted(fx, N, 1, fy - 1);
        if (V < get(fx, fy))
            solve_rows_sorted(fx, N, fy, N);
    }

    cout << "2 -1 -1" << endl;
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> V;
    solve();

    return 0;
}
