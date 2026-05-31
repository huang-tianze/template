extern int get_lca(int u, int v);
extern int depth[];

inline int dis(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

inline bool in(int x, int u, int v) { // 树中判断x在u,v的简单路径上
    return dis(u, x) + dis(x, v) == dis(u, v);
}
// 路径包含关系可以按两个点包含关系得到