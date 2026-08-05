#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

void bfs(int src, vector<vector<int>> &adj, int n) {
    vector<bool> vis(n, false);
    queue<int> q;
    q.push(src);
    vis[src] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << " "; // do something to u

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}

void visit(int u, vector<vector<int>> &adj, vector<bool> &vis) {
    vis[u] = true;

    cout << u << " "; // do sth to u
    for (int v : adj[u]) {
        if (!vis[v]) {
            visit(v, adj, vis);
        }
    }
}

void dfs(int src, vector<vector<int>> &adj, int n) {
    vector<bool> vis(n, false);
    visit(src, adj, vis);
}

// 注：vis等价于在图中删除节点
// 变种 bfs

void variant_BFS() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> special(k), cnt(n + 1, 0);
    for (auto &v : special) cin >> v;
    vector<bool> vis(n + 1, false);
    set<int> winNode;

    queue<int> q;

    for (auto v : special) {
        q.push(v);
        vis[v] = true;
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : adj[u]) {
            if (vis[v]) continue;
            cnt[v]++;
            if (cnt[v] == 2) {
                q.push(v);
                vis[v] = true;
            }
            winNode.insert(v);
        }
    }
    cout << winNode.size() << '\n';
    for (auto v : winNode) cout << v << ' ';
    cout << '\n';
}