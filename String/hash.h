// NOLINTBEGIN
#include <string>
#include <unordered_map>
// 字符串哈希以及子串哈希的模版（滚动哈希）
// 题面位：
// 给定字符串S和字符串str，查看str在S是否以子串形式出现，以及出现了几次。有T组str需要检测
// 多项式哈希先将字符集映射到0~n，然后定义为hash(abcd)= a*K^3+b*K^2+c*K+d
using namespace std;
const int N = 1e5 + 5;
const int K = 51; // 进制数
const long long K2 = 131;
const int M = 998244353; // 模数 9e8左右
const long long M2 = 1e16 + 61;
const int M3 = 19260817;
const int M4 = 1e9 + 7;
const int S = 5e3 + 3; // 字符串S的最大长度;
int powMod[N] = {1};
int prefixHash[N];                // 多项式哈希hash(abcd) = hash(abc)*K + d  (mod M)，因而可以使用类似前缀和(prefix_sum)的方式处理哈希以及查询子串
unordered_map<int, int> count[S]; // count[i]为长度为i的字符串的无序映射

int addMod(int x, int y) {
    return (x + y) % M; // x+y <=2M<2e9
}

int minusMod(int x, int y) {
    return (x - y + M) % M; // +M防止负数
}

int timesMod(int x, int y) { return (1LL * x * y) % M; }

void pre(string str, int prefix[]) {
    int len = str.size();
    for (int i = 1; i <= len; i++) {
        prefix[i] = addMod(timesMod(prefix[i - 1], K), str[i - 1] - 'a' + 1); // 这里str用i-1是因为str索引从0开始，而prefix从1开始，prefix[0]=0;
        powMod[i] = timesMod(powMod[i - 1], K);
    }
}

int subHash(/*int* prefixHash,*/ int left,
            int right) { // 传参式的可以加一个int *prefixHash参数
    return minusMod(
        prefixHash[right],
        timesMod(prefixHash[left - 1], // 由于这里有left减一，故prefixhash为，字符串从1开始索引，而prefix[0]=0;
                 powMod[right - left +
                        1])); // 当成数看：hash(bc) = hash(abc)-hash(a)*K^2
}

int myHash(string str) {
    int len = str.size();
    int hashNum = 0;
    for (int i = 1; i <= len; i++) {
        hashNum = addMod(timesMod(hashNum, K), str[i - 1] - 'a' + 1);
    }
    return hashNum;
}

// NOLINTEND
