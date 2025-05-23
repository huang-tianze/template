#include <bits/stdc++.h>
using namespace std;

// 假装你写了个更快的算法，比如计数排序
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    // vector<int> bucket(101, 0);
    // for (int x : a) bucket[x]++;
    // for (int i = 0; i <= 100; ++i)
    //     while (bucket[i]--) cout << i << " ";
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}
