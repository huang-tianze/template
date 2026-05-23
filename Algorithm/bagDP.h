// 背包dp, 仅供参考, 自己写
#include <bits/stdc++.h>
#include <vector>
using namespace std;

// 01背包
pair<int, int> dp01bags(int bagSize, vector<int> &weight, vector<int> &value) {
    vector<int> dp(weight.size() + 1, 0);
    for (int i = 1; i <= weight.size(); i++)
        for (int l = bagSize; l >= weight[i]; l--)
            dp[l] = max(dp[l], dp[l - weight[i]] + value[i]);

    return {dp[bagSize], 0};
}

// 多重背包
int dpMultiBags(int n, int W, vector<int> &w, vector<int> &v,
                vector<int> &cnt) {
    vector<int> dp(W + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int weight = W; weight >= w[i]; weight--) {
            // 多遍历一层物品数量
            for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
                dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
            }
        }
    }
    return dp[W];
}

// 完全背包
const int MAXN = 1e4 + 3;
const int MAXW = 1e7 + 3;
long long dp[MAXW];

// 带 相同w使用最大v 优化的完全背包
long long dpCompleteBags(int n, int capacity) {
    map<int, int> best_v;
    for (int i = 0; i < n; i++) {
        int cur_w, cur_v;
        cin >> cur_w >> cur_v;
        if (cur_w <= capacity) {
            best_v[cur_w] = max(best_v[cur_w], cur_v);
        }
    }
    for (auto const &[w, v] : best_v) {
        for (int j = w; j <= capacity; j++) {
            dp[j] = max(dp[j], dp[j - w] + v);
        }
    }
    return dp[capacity];
}

// 混合背包
int dpMixedBags(int n, int W, vector<int> &w, vector<int> &v,
                vector<int> &cnt) {
    vector<int> dp(W + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (cnt[i] == 0) { // 如果数量没有限制使用完全背包的核心代码
            for (int weight = w[i]; weight <= W; weight++) {
                dp[weight] = max(dp[weight], dp[weight - w[i]] + v[i]);
            }
        } else { // 物品有限使用多重背包的核心代码，它也可以处理0-1背包问题
            for (int weight = W; weight >= w[i]; weight--) {
                for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
                    dp[weight] =
                        max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
                }
            }
        }
    }
    return dp[W];
}

// 1-base
long long Dp01Bag(int n, long long c, vector<long long> &w,
                  vector<long long> &v) {
    vector<long long> dp(c + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (long long j = c; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[c];
}

long long DpMultiBag(int n, long long c, vector<long long> &w,
                     vector<long long> &v, vector<long long> &k) {
    vector<long long> nw(1); // 1-base
    vector<long long> nv(1); // 1-base
    for (int i = 1; i <= n; i++) {
        long long c = 1;
        while (k[i] > c) {
            k[i] -= c;
            nw.push_back(c * w[i]);
            nv.push_back(c * v[i]);
            c *= 2;
        }
        nw.push_back(k[i] * w[i]);
        nv.push_back(k[i] * v[i]);
    }
    return Dp01Bag((int)nw.size(), c, nw, nv);
}

long long DpCompleteBag(int n, long long c, vector<long long> &w,
                        vector<long long> &v) {
    vector<long long> dp(c + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (long long j = w[i]; j <= c; j++) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[c];
}

// group: 1-base, 1-base
long long DpGroupBag(long long c, vector<long long> &w, vector<long long> &v,
                     vector<vector<int>> &group) {
    for (int k = 1; k <= group.size(); k++) {
        for (long long i = c; i >= 0; i--) {
            for (int j = 1; j <= group[k].size(); j++) {
                if (i >= w[group[k][j]]) {
                    dp[i] = max(dp[i], dp[i - w[group[k][j]]] + v[group[k][j]]);
                }
            }
        }
    }
    return dp[c];
}
