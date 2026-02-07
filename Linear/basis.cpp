#include <bits/stdc++.h>
using namespace std;
// 需要保证 0 <= arr < 2^max_bit_len
const int max_bit_len = 60;

struct XorLinearBasis {
    vector<long long> a;
    unsigned long long cnt;
    array<unsigned long long, max_bit_len + 1> mask;
    array<long long, max_bit_len + 1> raw;

    XorLinearBasis()
        : a(vector<long long>(max_bit_len + 1, 0)), cnt(0), mask{}, raw{} {}

    void insert(long long t) {
        long long cur = t;
        unsigned long long cur_mask = 1ull << cnt;
        for (int j = max_bit_len; j >= 0; j--) {
            if (!(cur & (1LL << j)))
                continue;
            if (a[j]) {
                cur ^= a[j];
                cur_mask ^= mask[j];
            } else {
                for (int k = 0; k < j; k++)
                    if (cur & (1LL << k)) {
                        cur ^= a[k];
                        cur_mask ^= mask[k];
                    }
                for (int k = j + 1; k <= max_bit_len; k++)
                    if (a[k] & (1LL << j)) {
                        a[k] ^= cur;
                        mask[k] ^= cur_mask;
                    }
                a[j] = cur;
                mask[j] = cur_mask;
                raw[cnt] = t;
                cnt++;
                return;
            }
        }
    }

    // 注意, merge以后不保证represent的ret是全段有序的, ret将会是分段有序的,
    // 除非保证other的每一个raw位置都比this->raw靠后
    void merge_from(const XorLinearBasis &other) {
        for (int i = 0; i <= other.cnt; i++)
            this->insert(other.raw[i]);
    }

    long long query_max() const {
        long long ans = 0;
        for (auto i : a)
            ans ^= i;
        return ans;
    }

    bool contain(long long x) const {
        for (int j = max_bit_len; j >= 0; j--) {
            if (x & (1LL << j)) {
                if (!a[j])
                    return false;
                x ^= a[j];
            }
        }
        return true;
    }

    long long query_kth(long long k) {
        long long res = 0;
        for (int j = max_bit_len; j >= 0; j--) {
            if (k & (1LL << j)) {
                res ^= a[j];
            }
        }
        return res;
    }

    bool represent(long long x, vector<long long> &ret) {
        unsigned long long ret_mask = 0;
        for (int j = max_bit_len; j >= 0; j--) {
            if (x & (1LL << j)) {
                if (!a[j]) {
                    return false;
                }
                x ^= a[j];
                ret_mask ^= mask[j];
            }
        }
        for (int i = 0; i <= max_bit_len; i++) {
            if (ret_mask & (1LL << i)) {
                ret.push_back(raw[i]);
            }
        }
        return true;
    }
};
