/**
 * 用于维护区间的更改, 比线段树好写
 * 复杂度O(n loglog n)
 * 在hack下会退化到 o(n^2)更高 只perform不assign
 * 若保证perform后一定进行assign, 复杂度为均摊O(m log n), m为操作次数,
 * n为树中最大的区间数
 *
 */
#include <bits/stdc++.h>

class ChthollyTree {
  public:
    struct Node_t {
        int l;
        int r;
        mutable double v;

        Node_t(int l, int r, double v) : l(l), r(r), v(v) {}

        friend bool operator<(const Node_t &a, const Node_t b) {
            return a.l < b.l;
        }
    };

    std::set<Node_t> odt;

  public:
    ChthollyTree(int n, double init) { odt.insert({1, n + 1, init}); }

    ChthollyTree(int n, std::vector<double> &init) {
        for (int i = 1; i <= n; i++)
            odt.insert({i, i, init[i - 1]});
    }

    // spilt an interval [l,r), which contains x, to [l,x) and [x,r),
    // then return an iterator pointing at [x,r)
    auto split(int x) {
        auto it = odt.lower_bound(Node_t(x, 0, 0));
        if (it != odt.end() && it->l == x)
            return it;
        --it;
        int l = it->l, r = it->r;
        double v = it->v;
        odt.erase(it);
        odt.insert(Node_t(l, x - 1, v));
        return odt.insert(Node_t(x, r, v)).first;
    }

    // make interval [l,r)'s value eq v;
    void assign(int l, int r, double v) {
        auto itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.insert(Node_t(l, r, v));
    }

    // like assign, but don't delete subinterval in [l,r)
    double perform(int l, int r) {
        int L = l;
        int R = r;
        double ret = 0;
        auto itr = split(r + 1), itl = split(l);
        for (; itl != itr; ++itl) {
            R = std::max(R, itl->r);
            ret += itl->v * (itl->r - itl->l + 1);
        }
        return ret / (R - L + 1);
    }

    // merge link DSU, include position r !!!
    void merge(int l, int r) {
        auto it = odt.upper_bound({l, 0, 0});
        --it;
        if (it != odt.begin() && (it == odt.end() || it->l > l)) {
            --it;
        }
        auto itl = it;
        int L = it->l;
        int R = r;
        double sum = 0;
        while (it != odt.end() && it->l <= r) {
            sum += it->v * (it->r - it->l + 1);
            R = std::max(R, it->r);
            it++;
        }
        double nv = sum / (R - L + 1);
        odt.erase(itl, it);
        odt.insert({L, R, nv});
    }
};
