#ifndef GENLIB_HPP
#define GENLIB_HPP

#include <bits/stdc++.h>
using namespace std;

mt19937 rng((unsigned int)chrono::steady_clock::now().time_since_epoch().count());

int randInt(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

// 1. 数组生成器
vector<int> genArray(int n, int L = 1, int R = 1000) {
    vector<int> a(n);
    for (int &x : a) x = randInt(L, R);
    return a;
}

// 2. 字符串生成器
string genString(int len, int range = 26) {
    string s;
    for (int i = 0; i < len; ++i)
        s += 'a' + randInt(0, range - 1);
    return s;
}

// 3. 排列生成器
vector<int> genPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}

// 4. 区间生成器
vector<pair<int, int>> genIntervals(int n, int maxVal) {
    vector<pair<int, int>> res;
    for (int i = 0; i < n; ++i) {
        int l = randInt(1, maxVal);
        int r = randInt(l, maxVal);
        res.emplace_back(l, r);
    }
    return res;
}

// 5. 树生成器（无向无根树）
vector<pair<int, int>> genTree(int n) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= n; ++i) {
        int u = i, v = randInt(1, i - 1);
        edges.emplace_back(u, v);
    }
    shuffle(edges.begin(), edges.end(), rng);
    return edges;
}

// 6. 图生成器（连通无向图）
vector<pair<int, int>> genUndirectedGraph(int n, int m) {
    assert(m >= n - 1);
    set<pair<int, int>> edgeSet;
    vector<pair<int, int>> edges = genTree(n);
    for (auto e : edges) edgeSet.insert(minmax(e.first, e.second));
    while ((int)edgeSet.size() < m) {
        int u = randInt(1, n), v = randInt(1, n);
        if (u != v) edgeSet.insert(minmax(u, v));
    }
    return vector<pair<int, int>>(edgeSet.begin(), edgeSet.end());
}

// 7. 矩阵生成器（int 矩阵）
vector<vector<int>> genMatrix(int rows, int cols, int L = 1, int R = 1000) {
    vector<vector<int>> mat(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat[i][j] = randInt(L, R);
    return mat;
}

// 8. 并查集操作模拟器（合并/查找操作）
vector<pair<int, int>> genUnionFindOps(int n, int q) {
    vector<pair<int, int>> ops;
    for (int i = 0; i < q; ++i) {
        int opType = randInt(0, 1); // 0 = union, 1 = find
        int u = randInt(1, n), v = randInt(1, n);
        ops.emplace_back(opType == 0 ? u : -1, v); // -1 表示 find
    }
    return ops;
}

#endif // GENLIB_HPP