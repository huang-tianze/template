#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
constexpr int N = 1000;
using namespace std;

// 你不该用到a[N/2, N) !!!
// 特别是要乘法时

struct BigInt {
    std::vector<int> a;
    int l;

    BigInt(int x = 0) : a(N, 0), l(x ? 0 : 1) {
        for (int i = 0; x; i++) {
            a[i] = x % 10;
            x /= 10;
            l++;
        }
    }

    BigInt &operator*=(int x) {
        for (int i = 0; i < N; i++) {
            a[i] *= x;
        }
        for (int i = 0; i < N - 1; i++) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
        return *this;
    }

    BigInt &operator/=(int x) {
        for (int i = N - 1; i >= 0; i--) {
            if (i) {
                a[i - 1] += a[i] % x * 10;
            }
            a[i] /= x;
        }
        return *this;
    }

    BigInt &operator+=(const BigInt &x) {
        for (int i = 0; i < N - 1; i++) {
            a[i] += x.a[i];
            if (a[i] >= 10) {
                a[i + 1] += 1;
                a[i] -= 10;
            }
        }
        return *this;
    }

    BigInt &operator*=(const BigInt &);
};

std::ostream &operator<<(std::ostream &o, const BigInt &a) {
    int t = N - 1;
    while (a.a[t] == 0) {
        t--;
    }
    for (int i = t; i >= 0; i--) {
        o << a.a[i];
    }
    return o;
}

using cp = std::complex<double>;
const double PI = acos(-1);
int rev[(1 << 21) + 1];
extern int init(int, int);
extern void fft(std::vector<cp> &, int, int);

BigInt &BigInt::operator*=(const BigInt &bi) {
    if (l == 0 || bi.l == 0) {
        a.assign(N, 0);
        l = 0;
        return *this;
    }
    int n = init(l, bi.l);
    std::vector<cp> fa(n), fb(n);

    for (int i = 0; i < n; i++) {
        fa[i] = a[i];
        fb[i] = bi.a[i];
    }

    fft(fa, n, 1);
    fft(fb, n, 1);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    fft(fa, n, -1);

    a.assign(N, 0);

    for (int i = 0; i < n; i++) {
        a[i] = round(fa[i].real());
    }

    for (int i = 0; i < N - 1; i++) {
        if (a[i] >= 10) {
            a[i + 1] += a[i] / 10;
            a[i] %= 10;
        }
    }

    l = N;
    while (l > 0 && a[l - 1] == 0)
        l--;

    return *this;
}
