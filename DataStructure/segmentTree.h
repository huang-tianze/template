#include <cstdio>
#include <iostream>
using namespace std;

#define int long long

#define MAX_LEN 10005
// a为初始数组，下标从1开始，存储原始数据; d维护区间和; flag为lazyTag
int a[MAX_LEN], d[MAX_LEN * 4], flag[MAX_LEN * 4]; // *2 改成*4了

void build(int l, int r, int p) {
    if (l == r) {
        d[p] = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, p * 2), build(mid + 1, r, p * 2 + 1);
    d[p] = d[p * 2] + d[p * 2 + 1];
}

int getsum(int left, int right, int start, int end, int par) {
    if (left <= start && end <= right) {
        return d[par];
    }
    int mid = (start + end) >> 1;
    if (flag[par]) {
        d[par * 2] += flag[par] * (mid - start + 1);
        d[par * 2 + 1] += flag[par] * (end - mid);
        flag[par * 2] += flag[par];
        flag[par * 2 + 1] += flag[par];
        flag[par] = 0;
    }
    int sum = 0;
    if (left <= mid) sum += getsum(left, right, start, mid, par * 2);
    if (right > mid) sum += getsum(left, right, mid + 1, end, par * 2 + 1);
    return sum;
}

void add(int left, int right, int value, int start, int end, int par) {
    if (left <= start && end <= right) {
        d[par] += value * (end - start + 1);
        flag[par] += value;
        return;
    }
    int mid = (start + end) >> 1;
    if (flag[par] && start != end) {
        d[par * 2] += flag[par] * (mid - start + 1);
        d[par * 2 + 1] += flag[par] * (end - mid);
        flag[par * 2] += flag[par];
        flag[par * 2 + 1] += flag[par];
        flag[par] = 0;
    }
    if (left <= mid) add(left, right, value, start, mid, par * 2);
    if (right > mid) add(left, right, value, mid + 1, end, par * 2 + 1);
    d[par] = d[par * 2] + d[par * 2 + 1];
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    build(1, n, 1);
    while (m--) {
        int type;
        scanf("%lld", &type);
        if (type == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            add(x, y, k, 1, n, 1);
        } else {
            int x, y;
            cin >> x >> y;
            cout << getsum(x, y, 1, n, 1) << endl;
            ;
        }
    }
}