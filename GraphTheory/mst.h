#include <bits/stdc++.h>
#include <cstdint>
#include <vector>
using namespace std;

struct Edge {
    int64_t u, v, w;

    bool operator<(Edge o) const { return w < o.w; }
};

struct DSU {
    vector<int> fa, sz;
    int component;
    DSU(int n, int base = 0) : fa(n + base), sz(n + base, 1) {
        iota(fa.begin(), fa.end(), 0);
        component = n;
    }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        fa[b] = a;
        sz[a] += sz[b];
        component--;
    }
    int operator()(int x) { return find(x); }
};
// e边集，n:顶点数(1-based)；图不连通返回-1，否则返回最小生成树边权
int64_t kruskal(vector<Edge> &e, int n) {
    sort(e.begin(), e.end());
    DSU dsu(n, 1);
    int64_t ans = 0;
    for (auto [u, v, w] : e) {
        if (dsu(u) == dsu(v)) continue;
        ans += w;
        dsu.merge(u, v);
    }

    return dsu.component == 1 ? ans : -1;
}
