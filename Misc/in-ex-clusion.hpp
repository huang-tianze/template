#include <vector>
// 容斥原理，集合编号为0,1,...,n，calc给出a内编号的集合的交的大小，solve给出N个集合并的大小。O((T_calc+N)2^N)
int calc(const std::vector<int> &a);

long long solve(int N) {
    long long ans = 0;

    for (int mask = 1; mask < (1 << N); ++mask) {
        std::vector<int> a;
        for (int i = 0; i < N; ++i) {
            if (mask >> i & 1) a.push_back(i);
        }
        int count = __builtin_popcount(mask);
        ans += (count & 1 ? 1 : -1) * calc(a);
    }

    return ans;
}