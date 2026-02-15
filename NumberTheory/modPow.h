// 要求b为质数；
// 当a不是p的倍数下，可以用qpow(a,p-2,p)来求乘法逆元

// p为模数，该函数给出a的b次方 mod p的结果
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

// 扩展欧几里得, 对于本题做了特殊优化
void ex_gcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1;
        y = 0;
    } else {
        ex_gcd(b, a % b, y, x);
        y -= a / b * x;
    }
}

// 给出在模m情况下, a的乘法逆元
// 充要条件 gcd(a,m) = 1
int inverse(int a, int m) {
    int x, y;
    ex_gcd(a, m, x, y);
    return (x % m + m) % m;
}
