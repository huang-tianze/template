// NOLINTBEGIN
#include <bits/stdc++.h>
using namespace std;

// sz[i]表以i为根的树/集合的元素数量（包含i）
struct DSU {
    vector<int> fa, sz;
    int component;

    DSU(int n, int type = 0) : fa(n + type), sz(n + type, 1) {
        iota(fa.begin(), fa.end(), 0); // fa[i] = i
        component = n;
    }

    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

    void merge(int a, int b) {
        a = find(a), b = find(b);
        if (a == b)
            return;
        if (sz[a] < sz[b])
            swap(a, b);
        fa[b] = a;
        sz[a] += sz[b];
        component--;
    }

    bool connected() const { return component == 1; }
};

int main() {
    int n;
    cin >> n;
    DSU dsu(n);
    dsu.merge(1, 2); // 1,2在同一集合
    if (dsu.find(1) == dsu.find(2))
        cout << "连通";
}

// NOLINTEND
