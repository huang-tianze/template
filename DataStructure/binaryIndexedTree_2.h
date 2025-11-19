#include <bits/stdc++.h>

// 注意这个BIT的索引是1-base

class BIT {
    int n;
    std::vector<int> su;

  public:
    BIT(int n) : n(n), su(n + 1) {}

    // Add v to the x-th number.
    void add(int x, int v) {
        for (; x <= n; x += x & (-x)) {
            su[x] += v;
        }
    }

    // Get the cumulative sum till the x-th number.
    int query(int x) {
        int res = 0;
        for (; x; x &= x - 1) {
            res += su[x];
        }
        return res;
    }

    // Set every number 1
    void fill() {
        for (int x = 1; x <= n; ++x) {
            su[x] += x & (-x);
        }
    }

    // 找到前缀和>=k的最小下标
    int find_kth(int k) {
        int ps = 0, x = 0;
        for (int i = log2(n); i >= 0; --i) {
            x += 1 << i;
            if (x >= n || ps + su[x] >= k) {
                x -= 1 << i;
            } else {
                ps += su[x];
            }
        }
        return x + 1;
    }
};
