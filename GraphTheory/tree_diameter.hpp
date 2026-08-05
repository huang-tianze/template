#include <bits/stdc++.h>
#include <vector>
using namespace std;

pair<int, pair<int, int>> diameter(vector<vector<int>> &adj, int n) {
    vector<int> max_len(n + 1, 0), sub_len(n + 1, 0);
    vector<int> max_end(n + 1), sub_end(n + 1);
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) {
        max_end[i] = i;
        sub_end[i] = i;
    }

    int ans = 0;
    pair<int, int> ans_endpoints = {1, 1};

    auto update = [&](int len, int end_node, int u) {
        if (len > max_len[u]) {
            sub_len[u] = max_len[u];
            sub_end[u] = max_end[u];
            max_len[u] = len;
            max_end[u] = end_node;
        } else if (len > sub_len[u]) {
            sub_len[u] = len;
            sub_end[u] = end_node;
        }
    };

    auto dfs = [&](auto &self, int u, int parent) -> void {
        visited[u] = true;
        for (auto v : adj[u]) {
            if (v == parent)
                continue;
            self(self, v, u);
            int len = max_len[v] + 1;
            update(len, max_end[v], u);
        }
        if (max_len[u] + sub_len[u] > ans) {
            ans = max_len[u] + sub_len[u];
            ans_endpoints = {max_end[u], sub_end[u]};
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(dfs, 1, 0);
        }
    }
    return {ans, ans_endpoints};
}

int main() {
input:
    std::ios::sync_with_stdio(false), cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
solve:
    auto res = diameter(adj, n);
    cout << res.first << " " << res.second.first << " " << res.second.second
         << "\n";
}
