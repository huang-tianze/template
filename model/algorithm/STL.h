// ```cpp
// #include <algorithm>
// unique()                                     // 去除 相邻的 && 重复的 元素
//     iterator lower_bound(beign, end, target) //  寻找 >= x 的第一个元素的位置
// iterator upper_bound(begin, end, target)     // 寻找 <= x 的第一个元素的位置
//     void for_each(iterator beg, iterator end, _func);
// iterator find_if(iterator beg, iterator end, _Pred); // 顺序查找
// bool binary_find(iterator beg, iterator end, value) gcd() /
//     lcm() // if GCC __gcd()

// #include <numeric>
//     accumulate(iterator beg, iterator end, value /*初始值*/);
// ```
// NOLINTBEGIN
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <numeric>
#include <sstream>
#include <string>
using namespace std;

signed main() {
    // init
    vector<int> a;
    int target;

    // <algorithm>

    // 去除 相邻的 && 重复的 元素
    auto b = unique(a.begin(), a.end());
    // 寻找 >= target 的第一个元素的位置
    auto c = upper_bound(a.begin(), a.end(), target);
    // 寻找 <= target 的第一个元素的位置
    auto d = lower_bound(a.begin(), a.end(), target);
    // 二分查找
    auto e = binary_search(a.begin(), a.end(), target);

    // <numeric>
    // 返回累加值
    auto i = accumulate(a.begin(), a.end(), 0);

    // <sstream>
    string str;                       // 源字符串
    istringstream stringistream(str); // 临时流
    string output;                    // 输出
    char delim;                       // 分隔符
    std::getline(stringistream, output, delim);
}

// NOLINTEND
