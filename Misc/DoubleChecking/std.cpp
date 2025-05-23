#include <bits/stdc++.h>
using namespace std;

// 正确暴力：排序一组数
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    sort(a.begin(), a.end());
    for (int x : a) cout << x << " ";
    cout << '\n';
    return 0;
}
