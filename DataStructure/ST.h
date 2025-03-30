#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005, LOG = 17;
int st[MAXN][LOG], log2Table[MAXN];

// 预处理 log2Table
void initLog(int n) {
    log2Table[1] = 0;
    for (int i = 2; i <= n; i++)
        log2Table[i] = log2Table[i / 2] + 1;
}

// 预处理 ST 表
void buildST(const vector<int> &arr, int n) {
    for (int i = 0; i < n; i++)
        st[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        }
    }
}

// 区间最小值查询 RMQ(l, r)
int query(int l, int r) {
    int j = log2Table[r - l + 1];
    return min(st[l][j], st[r - (1 << j) + 1][j]);
}
