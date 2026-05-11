#include <array>
#include <iostream>

// 编译期计算前 N 个数的最小质因子表
template <int N>
struct FactorTable {
    std::array<int, N + 1> spf{};

    constexpr FactorTable() {
        for (int i = 2; i <= N; ++i) spf[i] = i;
        for (int i = 2; i * i <= N; ++i) {
            if (spf[i] == i) { // i 是质数
                for (int j = i * i; j <= N; j += i)
                    if (spf[j] == j) spf[j] = i;
            }
        }
    }
};

// 编译期生成常量表
static constexpr auto Table = FactorTable<100>();

int main() {
    int n = 84;
    std::cout << n << " 的质因数分解: ";
    int temp = n;
    while (temp > 1) {
        std::cout << Table.spf[temp] << " ";
        temp /= Table.spf[temp];
    }
    return 0;
}