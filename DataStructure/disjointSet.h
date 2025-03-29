// NOLINTBEGIN
#include <bits/stdc++.h>
using namespace std;

// TODO
int fa[0];
int Rank[0];

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
void merge(int i, int j) // 合并
{
    int x = find(i), y = find(j);
    if (Rank[x] <= Rank[y]) {
        fa[x] = y;
    } else {
        fa[y] = x;
    }
    if (Rank[x] == Rank[y] && x != y) {
        Rank[y]++;
    }
}

// NOLINTEND
