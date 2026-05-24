#include <bits/stdc++.h>
#include <cassert>
#include <vector>
using namespace std;

// IO形式不一，需要根据实际情况改；IO内容见注释

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

// 二进制分组优化的多重背包
int64_t dpMultiKnapsackBinary() {
    int n, capacity;
    cin >> n >> capacity;
    int64_t w, v, k; // 重量、价值、次数
    vector<int64_t> weight, value;
    for (int i = 0; i < n; i++) {
        cin >> w >> v >> k;
        int64_t cur = 1;
        while (k > cur) {
            k -= cur;
            weight.push_back(cur * w);
            value.push_back(cur * v);
            cur *= 2;
        }
        weight.push_back(k * w);
        value.push_back(k * v);
    }

    vector<int64_t> dp(capacity + 1, 0);
    for (int i = 0; i < weight.size(); i++) {
        for (int j = capacity; j >= weight[i]; j--) {
            dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
        }
    }
    return dp[capacity];
}

// 完全背包及远程模板所需的全局变量
const int MAXN = 1e4 + 3;
const int MAXW = 1e7 + 3;
long long dp[MAXW];

// 带 相同w使用最大v 优化的完全背包
long long dpCompleteBags(int n, int capacity) {
    vector<long long> dp(capacity + 1, 0);
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

// ==================== [本地新增] 其他扩展背包 ====================
// 分组背包
#define MAX_GROUP_CNT 105
int64_t dpGroupedKnapsack() {
    int n, capacity;
    cin >> n >> capacity;
    vector<int64_t> w(n, 0), v(n, 0), k(n, 0); // 重量、价值、所属的组别
    vector<vector<int>> groupIdx(MAX_GROUP_CNT);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> v[i] >> k[i];
        groupIdx[k[i]].push_back(i);
    }
    vector<int64_t> dp(capacity + 1, 0);
    for (auto &i : groupIdx) {
        for (int j = capacity; j >= 0; j--) {

            for (auto idx : i) {
                if (j - w[idx] >= 0)
                    dp[j] = max(dp[j], dp[j - w[idx]] + v[idx]);
            }
        }
    }

    return dp[capacity];
}

// 超大背包
int64_t solve() {
    int64_t n, capacity;
    cin >> n >> capacity; // n需要在40左右
    vector<int64_t> w(n, 0), v(n, 0);
    for (int i = 0; i < n; i++) cin >> w[i] >> v[i];

    if (n == 1) return w[0] <= capacity ? v[0] : 0;

    auto power_set = [&w, &v](int L, int R) {
        int k = R - L;
        vector<pair<int64_t, int64_t>> res(1 << k);
        res[0] = {0, 0};
        for (int s = 1; s < (1 << k); ++s) {
            int p = __builtin_ctz(s);
            int prev = s & (s - 1);

            res[s] = {res[prev].first + w[L + p], res[prev].second + v[L + p]};
        }
        return res;
    };

    auto filter = [capacity](vector<pair<int64_t, int64_t>> &list) {
        assert(!list.empty());
        sort(list.begin(), list.end());
        int sz = 0;
        for (int i = 0; i < list.size(); i++) {
            auto [w, c] = list[i];
            if (w > capacity) break;
            if (sz == 0 || c > list[sz - 1].second) {
                list[sz++] = list[i]; // overwrite unneeded item directly
            }
        }
        list.resize(sz);
    };

    auto list1 = power_set(0, n / 2);
    auto list2 = power_set(n / 2, n);

    filter(list1);
    filter(list2);

    int64_t ans = 0;

    auto it2 = list2.rbegin();
    for (auto [w1, c1] : list1) {
        while (it2 != list2.rend() && w1 + it2->first > capacity) it2++;
        if (it2 != list2.rend()) {
            ans = max(ans, c1 + it2->second);
        }
    }
    return ans;
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
    return Dp01Bag((int)nw.size() - 1, c, nw, nv);
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
    // 这里的 dp 使用了前面定义的全局数组 long long dp[MAXW];
    for (int k = 1; k < group.size(); k++) {
        for (long long i = c; i >= 0; i--) {
            for (int j = 1; j < group[k].size(); j++) {
                if (i >= w[group[k][j]]) {
                    dp[i] = max(dp[i], dp[i - w[group[k][j]]] + v[group[k][j]]);
                }
            }
        }
    }
    return dp[c];
}