// 求拓扑序数量，O(V2^V)

#include <iostream>
#include <vector>

using namespace std;

/**
 * 状态定义：使用一个整数 S 表示当前已经排入序列的节点集合。S 的第 i 位为 1 表示节点 i
 * 已在序列中，为 0 表示不在序列中。dp[S] 即为集合 S 的合法拓扑排列总数。 前置条件记录（pre
 * 数组）：在拓扑排序中，节点 i
 * 能被加入序列的充要条件是：它的所有入边对应的起点都已经排在它前面。模板中使用 pre[i]
 * 以二进制形式存储节点 i 的所有直接前驱节点。在转移状态时，通过位运算 (S & pre[i]) == pre[i] 可以
 * O(1) 地判断节点 i 的前置条件是否已全部满足。 状态转移方程：已知状态 S，若节点 i \notin S 且节点 i
 * 的前置节点全在 S 中，则可以将 i 附加到该序列末尾，形成新状态 S \cup \{i\}。方程为：dp[S \vert{}
 * (1 \ll i)] += dp[S]
 */

/**
 * 计算 DAG 的拓扑序数量
 * @param n 节点数量 (0 到 n-1)
 * @param edges 边集，每条边表示为 {u, v}，即 u 指向 v
 * @return 拓扑序的总数
 */
long long countTopologicalSorts(int n, vector<pair<int, int>> &edges) {
    if (n <= 0) return 0;

    // pre[i] 存储节点 i 的所有前置节点的状态压缩表示
    vector<int> pre(n, 0);
    for (auto [u, v] : edges) {
        pre[v] |= (1 << u);
    }

    int max_state = 1 << n;
    // dp[S] 表示当前已经排好序的节点集合为 S 时的拓扑序数量
    vector<long long> dp(max_state, 0);

    // 初始状态：空集的拓扑序数量为 1
    dp[0] = 1;

    // 遍历所有状态
    for (int S = 0; S < max_state; ++S) {
        if (dp[S] == 0) continue; // 当前状态不可达

        // 尝试将未加入集合的节点 i 加入到当前状态 S 中
        for (int i = 0; i < n; ++i) {
            // 条件 1: 节点 i 尚未在集合 S 中
            if ((S & (1 << i)) == 0) {
                // 条件 2: 节点 i 的所有前置节点都已经在集合 S 中
                if ((S & pre[i]) == pre[i]) {
                    int next_state = S | (1 << i);
                    dp[next_state] += dp[S];
                }
            }
        }
    }

    // 返回包含所有节点状态的拓扑序数量
    return dp[max_state - 1];
}

// 测试示例
int main() {
    // 示例：4个节点，3条边
    // 0 -> 1
    // 0 -> 2
    // 1 -> 3
    // 2 -> 3
    int n = 4;
    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};

    long long result = countTopologicalSorts(n, edges);
    cout << "拓扑序数量: " << result << endl; // 期望输出: 2 (0-1-2-3 和 0-2-1-3)

    return 0;
}