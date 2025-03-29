// exgcd 用于求解ax+by=gcd(a,b)的解(x,y)，并返回gcd(a,b)
long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// 简单的gcd
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
