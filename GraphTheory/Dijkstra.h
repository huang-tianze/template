#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

struct edge {
    int v, w;
};

struct node {
    int dis;
    int u;

    bool operator>(const node &a) const { return dis > a.dis; }
};

vector<edge> e[MAXN]; // 邻接表
int dis[MAXN];
int vis[MAXN];
priority_queue<node, vector<node>, greater<>> pq;

void dijkstra(int s, int n) {
    memset(dis, 0x3f, (n + 1) * sizeof(int));
    memset(vis, 0, (n + 1) * sizeof(int));
    dis[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto ed : e[u]) {
            int v = ed.v, w = ed.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
            }
        }
    }
}

// 写法二
struct Edge {
    int64_t u, v;
};

struct Node {
    int64_t u, d;
    bool operator<(const Node &o) const {
        return d > o.d;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n + 1, vector<Edge>());
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    vector<int64_t> dis(n + 1, INT_MAX);

    auto dijkstra = [&dis](int s, vector<vector<Edge>> &adj) -> void {
        priority_queue<Node> pq;
        dis[s] = 0;
        pq.push({s, 0});
        while (!pq.empty()) {
            auto [u, d] = pq.top();
            pq.pop();
            if (d > dis[u]) continue; // 必要的剪枝，O(ElogV)，无则可能O(M 2^N)
            for (auto [v, w] : adj[u]) {
                if (d + w < dis[v]) {
                    dis[v] = d + w;
                    pq.push({v, dis[v]});
                }
            }
        }
    };
}