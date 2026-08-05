#include <bits/stdc++.h>
using namespace std;

long long dfs_vertex(int u, int p, const vector<vector<int>> &adj,
                     vector<long long> &dp, long long mod) {
    long long res = 1;
    for (int v : adj[u]) {
        if (v == p)
            continue;
        long long sub_res = dfs_vertex(v, u, adj, dp, mod);
        res = (res * (sub_res + 1)) % mod;
    }
    return dp[u] = res;
}

// 求包含顶点 v 的子树数量
long long count_subtrees_with_vertex(int n, const vector<vector<int>> &adj,
                                     int v, long long mod) {
    vector<long long> dp(n + 1, 0);
    dfs_vertex(v, 0, adj, dp, mod);
    return dp[v];
}

long long dfs_edge_part(int u, int p, const vector<vector<int>> &adj,
                        long long mod) {
    long long res = 1;
    for (int v : adj[u]) {
        if (v == p)
            continue;
        long long sub_res = dfs_edge_part(v, u, adj, mod);
        res = (res * (sub_res + 1)) % mod;
    }
    return res;
}

// 求包含边 e(u, v) 的子树数量
long long count_subtrees_with_edge(int n, const vector<vector<int>> &adj,
                                   pair<int, int> e, long long mod) {
    int u = e.first;
    int v = e.second;

    long long count_u = dfs_edge_part(u, v, adj, mod);

    long long count_v = dfs_edge_part(v, u, adj, mod);

    return (count_u * count_v) % mod;
}
