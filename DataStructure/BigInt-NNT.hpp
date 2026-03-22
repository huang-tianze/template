#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace NTT {
    // 常用模数: 998244353, 原根 g: 3
    const long long MOD = 998244353;
    const long long G = 3;

    // 快速幂: (base^exp) % mod
    long long qpow(long long base, long long exp) {
        long long res = 1;
        while (exp > 0) {
            if (exp & 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    // 模逆元
    long long modInverse(long long n) {
        return qpow(n, MOD - 2);
    }

    // NTT 变换
    // a: 系数向量
    // invert: false 为 NTT, true 为 INTT (逆变换)
    void ntt(vector<long long> &a, bool invert) {
        int n = a.size();

        // 1. 位逆序置换 (Bit-reversal permutation)
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }

        // 2. 蝴蝶操作
        for (int len = 2; len <= n; len <<= 1) {
            long long wlen = qpow(G, (MOD - 1) / len);
            if (invert) wlen = modInverse(wlen);

            for (int i = 0; i < n; i += len) {
                long long w = 1;
                for (int j = 0; j < len / 2; j++) {
                    long long u = a[i + j];
                    long long v = (a[i + j + len / 2] * w) % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + len / 2] = (u - v + MOD) % MOD;
                    w = (w * wlen) % MOD;
                }
            }
        }

        // 3. 如果是逆变换，需要除以 n
        if (invert) {
            long long n_inv = modInverse(n);
            for (long long &x : a)
                x = (x * n_inv) % MOD;
        }
    }

    // 多项式乘法
    vector<long long> multiply(vector<long long> const &a, vector<long long> const &b) {
        vector<long long> fa(a.begin(), a.end());
        vector<long long> fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size())
            n <<= 1;

        fa.resize(n);
        fb.resize(n);

        ntt(fa, false);
        ntt(fb, false);

        for (int i = 0; i < n; i++)
            fa[i] = (fa[i] * fb[i]) % MOD;

        ntt(fa, true);
        return fa;
    }
}

// --- BigInt 封装 ---
struct BigInt {
    vector<int> digits; // 倒序存储，digits[0] 是个位

    BigInt() = default;
    explicit BigInt(long long v) {
        if (v == 0) digits.push_back(0);
        while (v > 0) {
            digits.push_back(v % 10);
            v /= 10;
        }
    }

    explicit BigInt(string s) {
        for (int i = s.length() - 1; i >= 0; i--) {
            digits.push_back(s[i] - '0');
        }
        trim();
    }

    // 去除前导零
    void trim() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
    }

    // NTT 乘法
    BigInt operator*(const BigInt &other) const {
        if ((digits.size() == 1 && digits[0] == 0) || (other.digits.size() == 1 && other.digits[0] == 0))
            return BigInt(0);

        // 转换成 long long vector 以适配 NTT
        vector<long long> a(digits.begin(), digits.end());
        vector<long long> b(other.digits.begin(), other.digits.end());

        // 执行 NTT 卷积
        vector<long long> res = NTT::multiply(a, b);

        // 处理进位
        BigInt result;
        result.digits.resize(res.size());
        long long carry = 0;
        for (int i = 0; i < res.size(); i++) {
            long long current = res[i] + carry;
            result.digits[i] = current % 10;
            carry = current / 10;
        }

        // 处理剩余进位
        while (carry) {
            result.digits.push_back(carry % 10);
            carry /= 10;
        }

        result.trim();
        return result;
    }

    // 输出
    friend ostream &operator<<(ostream &os, const BigInt &bi) {
        if (bi.digits.empty()) {
            os << 0;
            return os;
        }
        for (int i = bi.digits.size() - 1; i >= 0; i--) {
            os << bi.digits[i];
        }
        return os;
    }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    string s1, s2;
    if (cin >> s1 >> s2) {
        BigInt a(s1);
        BigInt b(s2);

        BigInt c = a * b;

        cout << c << endl;
    }

    return 0;
}