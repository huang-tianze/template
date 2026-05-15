#include <bits/stdc++.h>
#include <cassert>
#include <cstdint>
#include <vector>

using namespace std;
template <class T, class Op>
struct BIT {
    int n;
    T identity;
    vector<T> bit;
    vector<T> arr; // 原数组，用于支持区间查找
    Op merge;

public:
    BIT(int n, T id, Op op) : n(n), identity(id), bit(n + 1, identity), arr(n + 1, identity), merge(op) {}
    BIT(vector<T> &a, T id, Op op) : n(a.size() - 1), identity(id), bit(n + 1, identity), arr(a), merge(op) {
        for (int i = 1; i <= n; i++) { // 子节点贡献给父节点，O(n)建树
            bit[i] = merge(bit[i], arr[i]);
            int j = i + lowbit(i);                      // parent
            if (j <= n) bit[j] = merge(bit[j], bit[i]); // bit[j]是左侧聚合的结果，因此在左
        }
    }

    static inline int64_t lowbit(int64_t x) { return x & -x; }

    void assign(int64_t i, T val) {
        assert(0 < i && i <= n);
        arr[i] = val;
        for (; i <= n; i += lowbit(i)) {
            bit[i] = arr[i];
            for (int j = 1; j < lowbit(i); j *= 2) {
                bit[i] = merge(bit[i - j], bit[i]); // remark: 顺序
            }
        }
    }

    [[nodiscard]] T query(int64_t i) const { // [1,i]
        assert(i >= 0 && i <= n);
        T ans = identity;
        for (; i > 0; i -= lowbit(i)) {
            ans = merge(bit[i], ans); // 由于从右往左遍历，为支持不可交换的运算，bit[i]在左边
        }
        return ans;
    }

    [[nodiscard]] T query(int64_t l, int64_t r) const { // [l,r]
        assert(l <= r && l >= 1 && r <= n);
        T ans = identity;
        while (l <= r) {
            if (r - lowbit(r) + 1 >= l) {
                ans = merge(bit[r], ans);
                r -= lowbit(r);
            } else {
                ans = merge(arr[r], ans);
                r--;
            }
        }
        return ans;
    }

    void push_back(T val) {
        n++;
        arr.push_back(val);
        bit.push_back(val);
        for (int j = 1; j < lowbit(n); j *= 2) {
            bit[n] = merge(bit[n - j], bit[n]);
        }
    }
};