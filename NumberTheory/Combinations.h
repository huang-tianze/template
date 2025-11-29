#include <bits/stdc++.h>

/*
先init
C(m,n)见$fn solve_prime
*/

long long typedef num_type;

const long long p = 1e9 + 7;
std::array<num_type, 500005> fa{};
std::array<num_type, 500005> ifa{};

// p为模数，该函数给出a的b次方 mod p的结果
constexpr long long qpow(long long a, long long b, long long p) {
    long long ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1)
            ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}

auto init() {
    fa[0] = 1;
    for (int i = 1; i < 500005; ++i) {
        fa[i] = (long long)fa[i - 1] * i % p;
    }
    ifa[500004] = qpow(fa[500004], p - 2, p);
    for (int i = 500005 - 1; i > 0; --i)
        ifa[i - 1] = (long long)ifa[i] * i % p;
}

void solve_prime() {
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::cout << 1LL * fa[m] * ifa[n] % p * ifa[m - n] % p << '\n';
    }
}
