#include <vector>
using namespace std;
const int N = 1e6;

int spf[N + 1];
int phi[N + 1];
int mu[N + 1];
int factorCnt[N + 1];
vector<int> primes;

void pre() {
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= N; ++i) {
        spf[i] = i; // 初始假设所有数的最小质因数是自己
    }
    factorCnt[1] = 0;

    for (int i = 2; i <= N; ++i) {
        if (spf[i] == i) {
            primes.push_back(i);
            phi[i] = i - 1;
            mu[i] = -1;
            factorCnt[i] = 1;
        }

        for (int p : primes) {
            if (i * p > N) break;

            spf[i * p] = p;
            factorCnt[i * p] = factorCnt[i] + 1;

            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                mu[i * p] = 0;
                break; // 保证每个数只被其最小质因数筛掉，核心剪枝
            } else {
                // 互质
                phi[i * p] = phi[i] * (p - 1);
                mu[i * p] = -mu[i];
            }
        }
    }
}

bool is_prime(int n) {
    if (n < 2) return false;
    return spf[n] == n;
}

std::vector<int> factors(int n) {
    std::vector<int> res;
    while (n > 1) {
        res.push_back(spf[n]);
        n /= spf[n];
    }
    return res;
}