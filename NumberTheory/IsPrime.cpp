long long qmul(long long a, long long b, long long p) {
    long long c = (long double)a / p * b;
    long long res = (unsigned long long)a * b - (unsigned long long)c * p;
    return (res + p) % p;
}

long long qpow(long long a, long long b, long long p) {
    long long ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1)
            ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}

constexpr bool miller_rabin(long long n) {
    if (n < 3 || n % 2 == 0)
        return n == 2;
    if (n % 3 == 0)
        return n == 3;
    long long u = n - 1, t = 0;
    while (u % 2 == 0) {
        u /= 2;
        t++;
    }
    long long ud[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (long long a : ud) {
        long long v = qpow(a, u, n);
        if (v == 1 || v == n - 1 || v == 0)
            continue;
        for (int j = 1; j < t; j++) {
            v = qmul(v, v, n);
            if (v == n - 1 && j != t) {
                v = 1;
                break;
            }
            if (v == 1) {
                return false;
            }
        }
        if (v != 1) {
            return false;
        }
    }
    return true;
}
