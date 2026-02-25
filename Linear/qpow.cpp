#include <bits/stdc++.h>
#include <cassert>
#include <cstring>
using namespace std;

const int N = 3;

void multiply(long long self[N][N], long long b[N][N], long long p) {
    long long tmp[N][N];
    memset(tmp, 0, sizeof(tmp));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                tmp[i][j] += self[i][k] * b[k][j] % p;
                tmp[i][j] %= p;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            self[i][j] = tmp[i][j];
        }
    }
}

void matrixPos(long long a[3][3], long long k, long long p) {
    long long res[N][N] = {0}; // NOLINT
    for (int i = 0; i < N; i++)
        res[i][i] = 1;
    while (k > 0) {
        if (k & 1) {
            multiply(res, a, p);
        }
        multiply(a, a, p);
        k >>= 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = res[i][j];
        }
    }
}
