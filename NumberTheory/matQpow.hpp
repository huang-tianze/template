#include <cstdint>
using namespace std;

const int64_t MOD = 1e9 + 7;

template <int N>
struct Matrix {
    int64_t mat[N][N]{};

    void init_identity() {
        memset(mat, 0, sizeof(mat));
        for (int i = 0; i < N; i++) mat[i][i] = 1;
    }

    Matrix operator*(const Matrix &b) const {
        Matrix res;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (!mat[i][k]) continue;
                for (int j = 0; j < N; j++) {
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * b.mat[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

template <int N>
Matrix<N> qpow(Matrix<N> a, int64_t b) {
    Matrix<N> res;
    res.init_identity();
    for (; b; b >>= 1, a = a * a) {
        if (b & 1) res = res * a;
    }
    return res;
}