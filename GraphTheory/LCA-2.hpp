/*
 * 倍增法求树上任意两点的最近公共祖先（LCA）
 *
 * 时间复杂度：
 *   - 预处理：O(n log n)
 *   - 查询：O(log n)
 *
 * 使用说明：
 *   - 假设节点编号从 1 到 n
 *   - 使用前需调用 dfs(root,0)
 *   - 多组数据时需调用 reset(n)
 *   - 支持任意树（非二叉树也可）
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 5e5 + 5;
constexpr int LOG = __lg(MAXN) + 1;

vector<vector<int>> adj;
int depth[MAXN], up[MAXN][LOG];

// 初始化（多组测试数据时调用）
void reset(int n) {
    adj.assign(n + 1, vector<int>());
    fill(depth, depth + n + 1, 0);
}

// DFS 初始化深度与倍增数组 (初始调用: dfs(root, 0))
void dfs(int u, int p) { // node,parent
    up[u][0] = p;
    depth[u] = depth[p] + 1;

    for (int j = 1; j < LOG; ++j)
        up[u][j] = up[up[u][j - 1]][j - 1];

    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int j = LOG - 1; j >= 0; --j)
        if (depth[u] - (1 << j) >= depth[v])
            u = up[u][j];

    if (u == v) return u;

    for (int j = LOG - 1; j >= 0; --j)
        if (up[u][j] != up[v][j])
            u = up[u][j], v = up[v][j];

    return up[u][0];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, root;
    cin >> n >> q >> root;

    adj.resize(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(root, 0);

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << get_lca(u, v) << '\n';
    }

    return 0;
}