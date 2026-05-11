#include <cstdint>
using namespace std;
// remark：如果N在50左右，使用memset(mat,0,sizeof(mat))可能会比两个for更快
template <int N>
struct Matrix {
    int64_t mat[N][N];
    void clear(int n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) mat[i][j] = 0;
    }
    void init_identity(int n) {
        clear(n);
        for (int i = 0; i < n; i++) mat[i][i] = 1;
    }
    explicit Matrix(int n) { clear(n); }
    int64_t *operator[](int i) {
        return mat[i];
    }
    const int64_t *operator[](int i) const {
        return mat[i];
    }
};

/**
 * @param a The first matrix to multiply.
 * @param b The second matrix to multiply.
 * @param n The size of the square matrices.
 * @param mod The modulus for the multiplication operation.
 * @return Matrix<N> The result of (a * b) % mod.
 * @note 若矩阵值要用于指数，由费马小定理 a^p = a (mod p)，此时指数应该取摸数为p-1
 */
template <int N>
Matrix<N> multiply(const Matrix<N> &a, const Matrix<N> &b, int n, int64_t mod) {
    Matrix<N> res(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (!a[i][k]) continue;
            for (int j = 0; j < n; j++) {
                res.mat[i][j] = (res.mat[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return res;
}

template <int N>
Matrix<N> qpow(Matrix<N> a, int64_t b, int n, int64_t mod) {
    Matrix<N> res(n);
    res.init_identity(n);
    for (; b; b >>= 1) {
        if (b & 1) res = multiply(res, a, n, mod);
        a = multiply(a, a, n, mod);
    }
    return res;
}