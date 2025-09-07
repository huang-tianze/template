#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10005, LOG = 14;
vector<int> tree[MAXN];
int depth[MAXN], ancestor[MAXN][LOG];

// 预处理 DFS
void preprocess(int root, int n) {
    dfs(root, 0);
}

// DFS 计算父节点和深度，并预处理倍增表
void dfs(int node, int par) {
    ancestor[node][0] = par;
    depth[node] = depth[par] + 1;
    for (int j = 1; j < LOG; j++)
        ancestor[node][j] = ancestor[ancestor[node][j - 1]][j - 1];

    for (int child : tree[node]) {
        if (child != par) dfs(child, node);
    }
}

// 倍增查找 LCA
int LCA(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = LOG - 1; j >= 0; j--)
        if (depth[u] - (1 << j) >= depth[v]) u = ancestor[u][j];

    if (u == v) return u;

    for (int j = LOG - 1; j >= 0; j--)
        if (ancestor[u][j] != ancestor[v][j])
            u = ancestor[u][j], v = ancestor[v][j];

    return ancestor[u][0];
}
