// 要求b为质数，且当a不是p的倍数下，可以用qpow(a,p-2)来求乘法逆元
long long p = 998244353;

// p为模数，
long long qpow(long long a, int b) {
    long long ans = 1;
    a = (a % p + p) % p;
    for (; b; b >>= 1) {
        if (b & 1)
            ans = (a * ans) % p;
        a = (a * a) % p;
    }
    return ans;
}
