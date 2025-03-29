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

/* 多重背包
for (int i = 1; i <= n; i++) {
     for (int weight = W; weight >= w[i]; weight--) {
          // 多遍历一层物品数量
        for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
            dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
        }
    }
}

//混合背包
for (int i = 1; i <= n; i++) {
  if (cnt[i] == 0) {  // 如果数量没有限制使用完全背包的核心代码
    for (int weight = w[i]; weight <= W; weight++) {
      dp[weight] = max(dp[weight], dp[weight - w[i]] + v[i]);
    }
  } else {  // 物品有限使用多重背包的核心代码，它也可以处理0-1背包问题
    for (int weight = W; weight >= w[i]; weight--) {
      for (int k = 1; k * w[i] <= weight && k <= cnt[i]; k++) {
        dp[weight] = max(dp[weight], dp[weight - k * w[i]] + k * v[i]);
      }
    }
  }
}
*/
