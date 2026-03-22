#include <cstdint>
const int M = 998244353;
int64_t qpow(int64_t a, int64_t b, int64_t p = M) {
    long long ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}

const int MAXN = 1e6 + 5;
long long fac[MAXN];

void pre() {
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++) fac[i] = (1LL * fac[i - 1] * i) % M;
}

int64_t binomial(int64_t n, int64_t k) {
    if (k > n) return 0;
    if (k == 0) return 1;
    if (n == 0) return 0;
    if (!(k > 0 && n > 0)) return 0;
    int64_t a = fac[n];
    int64_t b = qpow(fac[k], M - 2);
    int64_t c = qpow(fac[n - k], M - 2);
    return a * b % M * c % M;
}