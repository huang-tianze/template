#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int a[N];
int b[N];
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int len_b = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + len_b + 1, a[i]) - b;
}