#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

using namespace std;

template <typename T, typename MergeOp = plus<T>,
          typename GetInverseOp = negate<T>>
class BIT {
  private:
    int n;
    T identity;
    MergeOp merge;
    GetInverseOp inv;
    std::vector<T> bit;

    [[nodiscard]] constexpr int lowbit(int x) const noexcept {
        return x & (-x);
    }

  public:
    explicit BIT(int size, T id = T(), MergeOp merge_op = MergeOp(),
                 GetInverseOp inv_op = GetInverseOp())
        : n(size), bit(size + 1, id), identity(id), merge(merge_op),
          inv(inv_op) {}

    explicit BIT(const vector<T> &a, T id = T(), MergeOp op = MergeOp(),
                 GetInverseOp inv_op = GetInverseOp())
        : n(a.size() - 1), identity(id), merge(op), inv(inv_op),
          bit(n + 1, identity) {
        for (int i = 1; i <= n; i++) {
            bit[i] = merge(bit[i], a[i]);
            int j = i + lowbit(i);
            if (j <= n)
                bit[j] =
                    merge(bit[j], bit[i]); // bit[j]是左侧聚合的结果，因此在左
        }
    }

    void add(int i, T delta) { // apply op
        assert(i > 0 && i <= n);
        for (; i <= n; i += lowbit(i)) {
            bit[i] = merge(bit[i], delta);
        }
    }

    T query(int i) const {
        assert(i >= 0 && i <= n);
        T res = identity;
        for (; i > 0; i -= lowbit(i)) {
            res = merge(res, bit[i]);
        }
        return res;
    }

    T query(int L, int R) const {
        if (L > R)
            return identity;

        return merge(query(R), inv(query(L - 1)));
    }

    void push_back(T val) {
        n++;
        bit.push_back(val);
        for (int j = 1; j < lowbit(n);
             j *= 2) { // u - 2^t, 另一种遍历子节点是u-=1, 遍历u-=lowbit(u)
            bit[n] = merge(bit[n - j], bit[n]);
        }
    }

    // 以下为权值数组的应用

    /**
     * @brief 获取原数组第 k 小的元素的下标 (即满足前缀和 >= k 的最小下标)
     * @details 时间复杂度 O(log N), 利用倍增
     *          注意：此函数仅在树状数组作为值域频次数组 (维护频次)
     *          且 merge 为加法时具有实际数学意义。
     *          需要提前将数组建为权值数组（建桶后塞入）
     *
     * @param k 目标排名 (需要保证 1 <= k <= 整个数组的总和)
     * @return int 满足条件的最小下标。如果找不到 (k 太大)，返回 n + 1。
     */
    [[nodiscard]] int find_kth(T k) const {
        int x = 0;

        int step = 1;
        while (step <= n)
            step <<= 1;
        step >>= 1; // 最大的2^k使得2^k<=n

        for (; step > 0; step >>= 1) {
            if (x + step <= n && bit[x + step] < k) {
                x += step;
                k -= bit[x];
            }
        }
        return x + 1;
    }
};

#include <algorithm>

int discretize(vector<int64_t> &a) {
    int n = a.size() - 1;
    vector<int64_t> sorted_a(a.begin() + 1, a.end());

    sort(sorted_a.begin(), sorted_a.end());
    sorted_a.erase(unique(sorted_a.begin(), sorted_a.end()), sorted_a.end());

    int max_rank = sorted_a.size();

    // 1-based 排名
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(sorted_a.begin(), sorted_a.end(), a[i]) -
               sorted_a.begin() + 1;
    }

    return max_rank;
}

// 求逆序数（二维偏序计数都可以用类似的思路解决）
int64_t count_inversions(vector<int64_t> a) {
    int n = a.size() - 1;
    if (n <= 1)
        return 0;
    int m = discretize(a);

    BIT<int64_t> bit(m, 0LL);

    int64_t inversions = 0;
    for (int i = n; i >= 1; --i) {
        inversions += bit.query(a[i] - 1);
        bit.add(a[i], 1LL);
    }

    return inversions;
}
