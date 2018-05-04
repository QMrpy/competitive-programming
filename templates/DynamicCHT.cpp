
// Dynamic Convex Hull
// Supports insertion of lines and min/max queries

// https://wcipeg.com/wiki/Convex_hull_trick
// http://codeforces.com/blog/entry/11155#comment-162462

struct DynamicHull {
    static constexpr double LOOOOW = -1e100;
    static const bool MINHULL = true;  // true = lower-hull, false = upper-hull
    struct line {
        long long m, c;
        bool query;
        mutable double left;

        inline long long eval(long long x) const {
            return m * x + c;
        }

        inline double intersectX(const line &l) const {
            return (c - l.c) * 1.0 / (l.m - m);
        }

        inline bool operator<(const line &l) const {
            if (l.query) return left < l.m;
            return MINHULL ? m > l.m : m < l.m;
        }

        static inline bool ok(const line &a, const line &b, const line &c) {
            return a.intersectX(b) < b.intersectX(c);
        }
    };
    set<line> hull;

    void insert(line l) {
        if (hull.empty()) {
            l.left = LOOOOW;
            hull.insert(l);
            return;
        }
        auto it = hull.lower_bound(l);
        if (it != hull.end() && it->m == l.m) {
            if (MINHULL && it->c <= l.c || !MINHULL && it->c >= l.c) return;
            hull.erase(it++);
            if (hull.empty()) {
                l.left = LOOOOW;
                hull.insert(l);
                return;
            }
        }
        auto itL = it, itR = it;
        bool first = itL == hull.begin();
        if (!first) {
            it = --itL;
            while (it != hull.begin()) {
                if (line::ok(*--it, *itL, l)) break;
                hull.erase(itL);
                itL = it;
            }
        }
        if (itR != hull.end()) {
            it = itR;
            while (++it != hull.end()) {
                if (line::ok(l, *itR, *it)) break;
                hull.erase(itR);
                itR = it;
            }
        }
        if (first) {
            itR->left = itR->intersectX(l);
            l.left = LOOOOW;
            hull.insert(itR, l);
        } else if (itR == hull.end()) {
            l.left = itL->intersectX(l);
            hull.insert(itR, l);
        } else if (line::ok(*itL, l, *itR)) {
            itR->left = itR->intersectX(l);
            l.left = itL->intersectX(l);
            hull.insert(itR, l);
        }
    }

    long long query(long long x) {
        line l = {x, 0, true};
        auto it = hull.lower_bound(l); it--;
        return it->eval(x);
    }
};