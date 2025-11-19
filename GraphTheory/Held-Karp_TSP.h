#include <bits/stdc++.h>
long long typedef ll;

/*
node为节点的定义(实际实现不重要)
dis获得任意两个节点间的距离
时间复杂度O(2^n), 空间O(n^2)
*/

struct node {};

// #[Commutative]
extern ll dis(const node &, const node &);

ll tsp(const std::vector<node> &nodes) {
    using namespace std;
    const int n = (int)nodes.size();
    if (n == 0)
        return 0;

    vector<vector<ll>> dist(n, vector<ll>(n, 0LL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = dis(nodes[i], nodes[j]);
        }
    }

    const int N = 1 << n;
    const ll INF = numeric_limits<ll>::max() / 4;
    vector<vector<ll>> dp(N, vector<ll>(n, INF));

    dp[1 << 0][0] = 0;

    for (int mask = 0; mask < N; ++mask) {
        if (!(mask & 1))
            continue;
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)))
                continue;
            ll cur = dp[mask][u];
            if (cur == INF)
                continue;
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v))
                    continue;
                int nm = mask | (1 << v);
                dp[nm][v] = min(dp[nm][v], cur + dist[u][v]);
            }
        }
    }

    ll ans = INF;
    int full = N - 1;
    if (n == 1)
        return 0;
    for (int u = 1; u < n; ++u) {
        ans = min(ans, dp[full][u] + dist[u][0]);
    }
    return ans;
}
