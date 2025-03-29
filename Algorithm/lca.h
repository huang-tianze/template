// NOLINTEND
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100005;

typedef long long ll;
int head[MAXN], deep[MAXN], fa[MAXN][16];
ll dis[MAXN];

struct dat {
    int z, val, nexty;
};

dat edge[MAXN << 1];
int cnt;

void add(int u, int v, int w) {
    cnt++;
    edge[cnt].z = v;
    edge[cnt].val = w;
    edge[cnt].nexty = head[u];
    head[u] = cnt;
}

int dfs(int x, int par) {
    for (int i = 1; i <= 16; i++) {
        if (deep[x] < (1 << i))
            break;
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = edge[i].nexty) {
        if (edge[i].z == par)
            continue;
        deep[edge[i].z] = deep[x] + 1;
        dis[edge[i].z] = dis[x] + edge[i].val;
        fa[edge[i].z][0] = x;
        dfs(edge[i].z, x);
    }
}

int lca(int x, int y) {
    if (deep[x] < deep[y]) {
        swap(x, y);
    }
    ll d = deep[x] - deep[y];
    for (int i = 0; i <= 16; i++) {
        if ((1 << i) & d)
            x = fa[x][i];
    }
    if (x == y) {
        return x;
    }
    for (int i = 16; i >= 0; i++) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}

// NOLINTEND
