// Fast Fourier Transform
#include <complex>
#include <iostream>
#include <vector>
using namespace std;

using cp = std::complex<double>;

const double PI = acos(-1);
int rev[(1 << 21) + 1];

int init(int n, int m) {
    int k = 1, s = 2;
    while ((1 << k) < n + m - 1)
        k++, s <<= 1;
    // assert(s < (1 << 21) + 1);
    for (int i = 0; i < s; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    return s;
}

void fft(vector<cp> &fa, int n, int flag) {
    for (int i = 0; i < n; i++) {
        if (i < rev[i])
            swap(fa[i], fa[rev[i]]);
    }
    for (int h = 1; h < n; h *= 2) {
        cp wn = exp(cp(0, flag * PI / h));
        for (int j = 0; j < n; j += h * 2) {
            cp w(1, 0);
            for (int k = j; k < j + h; k++) {
                cp x = fa[k];
                cp y = w * fa[k + h];
                fa[k] = x + y;
                fa[k + h] = x - y;
                w *= wn;
            }
        }
    }
    if (flag == -1)
        for (int i = 0; i < n; i++)
            fa[i] /= n;
}

/*
init()传入两个多项式的次数, 返回值代表fft的vector的长度
flag=1 为fft, flag=-1 为ifft

多项式计算步骤为
init
copy
fft *2
operator *
ifft
round()
handle carries
cout

建议ans.size() = init() +5
保证rev.size()为2^k+1的形式, 且2^k > 传入的多项式的进制的和-1
*/
