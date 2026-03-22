#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

/**
 * @brief kruskal O(nlogn)
 * @date 25-4-3
 * @details 有 n 个节点, 将其连为 k 组, 将 u, v连接起来的需要代价 l
 * @return 返回最小的代价
 */

#define MAXN 1005
int fa[MAXN];
int n, m, k;

struct Edge {
    int u_, v_, w_;

    bool operator<(Edge b) const { return this->w_ < b.w_; }
};

int l;
Edge g[MAXN];

void add_edge(int u, int v, int w) {
    l++;
    g[l].u_ = u;
    g[l].v_ = v;
    g[l].w_ = w;
}

int find_root(int x) { return fa[x] == x ? x : fa[x] = find_root(fa[x]); }

void merge(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    fa[x] = y;
}

int kruskal() {
    int tot = 0; // 已经选了的边数
    int ans = 0; // 存总的代价
    for (int i = 1; i <= m; ++i) {
        int xr = find_root(g[i].u_), yr = find_root(g[i].v_);
        if (xr != yr) {
            merge(xr, yr);
            tot++;
            ans += g[i].w_;
        }
        if (tot >= (n - k)) {
            return ans;
        }
    }
    return -1;
}
