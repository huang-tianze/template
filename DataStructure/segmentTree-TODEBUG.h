// 线段树
const int MAX_N = 1e5;
int tree[MAX_N * 4];
int lazy[MAX_N * 4];
int a[MAX_N];

// 建树
void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * p + 1, l, m);
    build(2 * p + 2, m + 1, r);
    tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
}

// 区间更新
void push_down(int p, int l, int r) {
    if (lazy[p] != 0) {
        int m = (l + r) / 2;
        tree[2 * p + 1] += (m - l + 1) * lazy[p];
        tree[2 * p + 2] += (r - m) * lazy[p];
        lazy[2 * p + 1] += lazy[p];
        lazy[2 * p + 2] += lazy[p];
        lazy[p] = 0;
    }
}

void update(int p, int l, int r, int ul, int ur, int val) {
    if (ur < l || r < ul)
        return;
    if (ul <= l && r <= ur) {
        tree[p] += (r - l + 1) * val;
        if (l != r) { // 非叶子节点存储懒标记
            lazy[p] += val;
            return;
        }
        push_down(p, l, r);
        int m = (l + r) / 2;
        update(2 * p + 1, l, m, ul, ur, val);
        update(2 * p + 2, m + 1, r, ul, ur, val);
        tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
    }
}

// 查询
int query(int p, int l, int r, int ql, int qr) {
    if (qr < l || r < ql)
        return 0;
    if (ql <= l && r <= qr)
        return tree[p];
    push_down(p, l, r); // 处理懒标记
    int m = (l + r) / 2;
    return query(2 * p + 1, l, m, ql, qr) + query(2 * p + 2, m + 1, r, ql, qr);
}
