// 进制为 sqrt(-2)的数域
#include <vector>
using namespace std;

// 需要保证num.size() > 5

void changeBase_10_sqrt2i(vector<long long> &num) {
    for (int i = 0; i < num.size() - 3; i++) {
        long long carry_div = num[i] / 2;
        long long rem = num[i] % 2;

        num[i + 2] -= carry_div;
        if (rem < 0) {
            rem += 2;
            num[i + 2]++;
        }
        num[i] = rem;
    }
}
