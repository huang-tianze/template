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
