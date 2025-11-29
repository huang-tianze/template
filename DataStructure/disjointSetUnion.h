// NOLINTBEGIN
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int fa[N];
int Rank[N];

// 建立：
void init(int n) {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        Rank[i] = 1;
    }
}

// 查询：
int find(int x) {
    if (fa[x] == x)
        return x; // 已经是根节点
    else
        return fa[x] = find(fa[x]); // 继续找
}

// 合并：
void merge(int i, int j) {
    int x = find(i), y = find(j);
    if (x == y) return;

    if (Rank[x] > Rank[y]) {
        fa[y] = x;
    } else if (Rank[x] < Rank[y]) {
        fa[x] = y;
    } else {
        fa[y] = x;
        Rank[x]++;
    }
}

// NOLINTEND
