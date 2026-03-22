#include <bits/stdc++.h>
#include <vector>
using namespace std;

int diameter(vector<vector<int>> &adj, int n) {
    vector<int> max_len(n + 1, 0), sub_len(n + 1, 0);

    auto update = [](int len, int &max, int &sub) {
        if (len > max)
            sub = max, max = len;
        else if (len > sub)
            sub = len;
    };

    int ans = 0;
    auto dfs = [&](auto &self, int u, int parent) -> void {
        for (auto v : adj[u]) {
            if (v == parent) continue;
            self(self, v, u);
            int len = max_len[v] + 1;
            update(len, max_len[u], sub_len[u]);
        }
        ans = max(ans, max_len[u] + sub_len[u]);
    };
    dfs(dfs, 1, 0);
    return ans;
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
    cout << diameter(adj, n);
}