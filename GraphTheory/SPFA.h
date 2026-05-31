#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int v;
    int w;
};

bool spfa(int n, vector<vector<Edge>> &e) { //
    queue<int> q;
    vector<long long> dis(n + 1, 0x3f3f3f3f);
    vector<bool> vis(n + 1, false);
    vector<int> cnt(n + 1, 0);

    // 所有节点为源找负环，存在负环即false
    // for (int i = 1; i <= n; i++) {
    //     q.push(i);
    //     dis[i] = 0, vis[i] = 1;
    // }

    // 结点1可达负环即false
    q.push(1);
    dis[1] = 0;
    vis[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop(), vis[u] = 0;
        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n)
                    return false;
                if (!vis[v])
                    q.push(v), vis[v] = 1;
            }
        }
    }
    return true;
}