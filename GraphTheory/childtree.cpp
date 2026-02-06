#include <bits/stdc++.h>
using namespace std;

// extern vector<vector<int>> edge;
extern long long mod; // NOLINT

/**
 * @brief
 * 计算有根树下以curr为根的所有的子树的数量
 *
 * 可选项:
 * - 记录每个节点的父节点 -> pa
 * - 记录以curr为根的子树的根节点 -> ct
 * @param curr
 * @param p
 * @param ret
 * @param pa
 * @param ct
 */
void dfs(int curr, int p, vector<int> &ret, vector<vector<int>> &edge
         // vector<int> &pa
         // vector<vector<int>> &ct
) {
    ret[curr] = 1;
    // pa[curr] = p;
    for (auto v : edge[curr]) {
        if (v == p) {
            continue;
        }
        // ct[curr].push_back(v);
        dfs(v, curr, ret, edge);
        ret[curr] = 1ll * ret[curr] * (1 + ret[v]) % mod; // NOLINT
    }
}
