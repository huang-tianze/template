#include <bits/stdc++.h>

using namespace std;
int a[2];
int tree[2];
int n;

// 建立：
void build() {
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tree[i] = i;
    } // 一开始先赋初值
}

// 维护：
int lowbit(int x) { return x & (-x); }

void updata(int x, int k) {
    for (; x <= n; x += lowbit(x))
        tree[x] += k;
}

// 查询：
long long query(int x) {
    int ans;
    for (; x; x -= lowbit(x))
        ans = ans + tree[x];
    return ans;
}

// 区间值：
inline long long my_union(int x, int y) { return query(x) - query(y - 1); }
