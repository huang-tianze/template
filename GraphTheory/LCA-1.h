#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 10005;
vector<int> tree[MAXN]; // 邻接表
int parent[MAXN];

// 预处理 DFS，存储父节点
void preprocess(int root, int n) {
    dfs(root, 0);
}

// DFS 计算每个节点的父节点
void dfs(int node, int par) {
    parent[node] = par;
    for (int child : tree[node]) {
        if (child != par) dfs(child, node);
    }
}

// 朴素查找 LCA
int LCA(int u, int v) {
    while (u != v) {
        if (u > v)
            u = parent[u];
        else
            v = parent[v];
    }
    return u;
}
