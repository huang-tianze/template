#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    int n = rng() % 10 + 1; // [1, 10]
    cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        cout << (rng() % 100) << " ";
    }
    cout << '\n';
    return 0;
}
