#include <bits/stdc++.h>
using namespace std;
template <class T>
inline bool prev_submask(T &submask, T mask) { // do-while遍历到最小字典序后false
    return (submask = (submask - 1) & mask) != mask;
}
template <class T>
inline bool next_submask(T &submask, T mask) { // 到最大字典序后false
    submask ^= mask;
    bool ret = prev_submask(submask, mask);
    submask ^= mask;
    return ret;
}

int main() {
    int mask = 0b1111;
    int s = 0000; //  若要从非空集开始遍历，可以s = mask & -mask
    do {
        cout << bitset<8>(s) << endl;
    } while (next_submask(s, mask));
}