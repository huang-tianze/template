/// 用于二维平面上的并查集
/// 认为由 点 与 其8个方向的点 组成边
/// 边可以围成一个区域
/// 默认不对点的并查集结果做保证
/// 默认有界区域
/// NOTE 由于二维下等价集需要的点数较多, 因此不提供merge
/// NOTE 同时实际上即使对于与无穷远等价的点, 若该行无点在mp中, 则DSU对于未作处理
/// @ref 蔡光<nowcoder@832134074>

#include "../DataStructure/DSU.h"

struct Dsu2d {
    const int inf = 2e6;

    map<int, vector<array<int, 3>>> seg;
    int posCnt = 1;
    DSU d{0};

    /// pos : 按照y排序的x, 默认x从小到大排序
    /// s : 无限远或与无限远意义相同的点
    Dsu2d(map<int, vector<int>> mp) {
        for (auto &[y, v] : mp) {
            int cur = -inf;
            for (int x : v) {
                if (x > cur) {
                    seg[y].push_back({cur, x - 1, posCnt});
                    posCnt++;
                }
                cur = x + 1;
            }
            if (cur <= inf) {
                seg[y].push_back({cur, inf, posCnt});
                posCnt++;
            }
        }
        d = DSU(posCnt + 10, 1);

        vector<int> Y;
        Y.reserve(seg.size());
        for (auto &[y, _] : seg) {
            Y.push_back(y);
        }
        for (int i = 0; i < Y.size(); i++) {
            int y = Y[i];
            auto &cur = seg[y];
            for (auto [l, r, id] : cur) {
                if (l <= -inf || r >= inf) {
                    d.merge(id, 0);
                }
            }
            if (i == 0) {
                for (auto [l, r, id] : cur) {
                    d.merge(id, 0);
                }
                continue;
            }
            int pre_y = Y[i - 1];
            auto &pre = seg[pre_y];

            if (y > pre_y + 1) {
                for (auto [l, r, id] : pre) {
                    d.merge(0, id);
                }
                for (auto [l, r, id] : cur) {
                    d.merge(0, id);
                }
            } else {
                int j = 0, k = 0;
                while (j < pre.size() && k < cur.size()) {
                    int L = max(pre[j][0], cur[k][0]);
                    int R = min(pre[j][1], cur[k][1]);
                    if (L <= R) {
                        d.merge(pre[j][2], cur[k][2]);
                    }

                    if (pre[j][1] < cur[k][1]) {
                        j++;
                    } else {
                        k++;
                    }
                }
            }
        }
        if (Y.size()) {
            for (auto [l, r, id] : seg[Y.back()]) {
                d.merge(id, 0);
            }
        }
    }

    int find(std::pair<int, int> pos) {
        auto [x, y] = pos;
        if (seg.count(y)) {
            auto &v = seg[y];

            int L = -1, R = v.size();
            while (L + 1 < R) {
                int mid = (L + 1 + R) >> 1;
                if (v[mid][1] < x) {
                    L = mid;
                } else {
                    R = mid;
                }
            }

            if (R < v.size() && v[R][0] <= x) {
                if (d.find(0) != d.find(v[R][2])) {
                    return false;
                }
            }
        }
        return true;
    }
};
