extern long long exgcd(long long a, long long b, long long &x, long long &y);

// k表示同余方程的个数，数组a和r（从1开始）表示各个同余方程的余数和模数
// 即x mod r[i] = a[i], i=1,2,...,k ;
long long CRT(int k, long long *a, long long *r) {
    long long n = 1, ans = 0;
    for (int i = 1; i <= k; i++)
        n = n * r[i];
    for (int i = 1; i <= k; i++) {
        long long m = n / r[i], b, y;
        exgcd(m, r[i], b, y); // b * m mod r[i] = 1
        ans = (ans + a[i] * m * b % n) % n;
    }
    return (ans % n + n) % n;
}
