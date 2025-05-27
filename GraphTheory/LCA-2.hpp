/*
 * 倍增法求树上任意两点的最近公共祖先（LCA）
 *
 * 时间复杂度：
 *   - 预处理：O(n log n)
 *   - 查询：O(log n)
 *
 * 使用说明：
 *   - 假设节点编号从 1 到 n
 *   - 使用前需调用 preprocess(root)
 *   - 多组数据时需调用 reset(n)
 *   - 支持任意树（非二叉树也可）
 */

#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10005;
constexpr int LOG = __lg(MAXN) + 1; // __lg(x)返回floor(log2(x)), 标识不超过x的最大二进制对数

vector<int> tree[MAXN];
int depth[MAXN], ancestor[MAXN][LOG];

// 清空所有数据（适用于多组测试）
void reset(int n)
{
    for (int i = 0; i <= n; ++i)
    {
        tree[i].clear();
        depth[i] = 0;
        for (int j = 0; j < LOG; ++j)
            ancestor[i][j] = 0;
    }
}

// DFS 初始化深度与倍增数组
void dfs(int node, int par)
{
    ancestor[node][0] = par;
    depth[node] = depth[par] + 1;
    for (int j = 1; j < LOG; ++j)
        ancestor[node][j] = ancestor[ancestor[node][j - 1]][j - 1];

    for (int child : tree[node])
    {
        if (child != par)
            dfs(child, node);
    }
}

// 预处理：初始化倍增数组
void pre(int root)
{
    depth[0] = -1; // 虚拟父节点深度为 -1，确保 root 深度为 0
    dfs(root, 0);
}

// 查询 u 与 v 的最近公共祖先
int LCA(int u, int v)
{
    if (depth[u] < depth[v]) swap(u, v);

    // 将 u 提升到与 v 同一深度
    for (int j = LOG - 1; j >= 0; --j)
        if (depth[u] - (1 << j) >= depth[v])
            u = ancestor[u][j];

    if (u == v) return u;

    // 同时向上跳，直到它们的祖先相同
    for (int j = LOG - 1; j >= 0; --j)
        if (ancestor[u][j] != ancestor[v][j])
            u = ancestor[u][j], v = ancestor[v][j];

    return ancestor[u][0];
}

int main()
{
    int n;
    cin >> n; // 节点数

    reset(n); // 清空前一组数据

    // 读入 n - 1 条边
    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    pre(1); // 假设根节点为 1

    int q;
    cin >> q; // 查询次数
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << '\n';
    }

    return 0;
}
