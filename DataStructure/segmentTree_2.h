#include <bits/stdc++.h>
using namespace std;

template <typename Node, typename Tag, typename RangeT = int>
#if __cplusplus >= 202002LL
    requires requires(Node n, const Node &l, const Node &r, const Tag &t,
                      RangeT range) {
        // Node需要支持构造基本结构, 用于构造tree_和ans的初始值
        { Node{} } -> std::same_as<Node>;
        // 需要支持构造不会对Node产生影响的Tag
        { Tag{} } -> std::same_as<Tag>;
        // 从左右子树更新父节点
        { n.set(l, r) } -> std::same_as<void>;
        // 从左右两侧的查询结果更新ans
        { n.update(l) } -> std::same_as<void>;
        // 懒标记更新闭区间对应的子树的根节点
        { n.range_update(t, range, range) } -> std::same_as<void>;
        // 支持从Node构造懒标记
        { static_cast<Tag>(n) } -> std::same_as<Tag>;
    }
/*
为防止Node{0}和Tag{0}存在特殊含义或者不能从单一元素构造(例如矩阵)
使用Node{}和Tag{}作为默认值, 实际使用时需要根据具体情况重写对应的构造函数
同时, 使得所有的出现的Node以及Tag均为默认构造得到或者由外部传入, 保证通用性
*/
#endif
class SegTreeLazy {
    vector<Node> tree_;
    vector<Tag> lazy_;
    vector<Node> *arr_;
    vector<bool> if_lazy_;
    RangeT n_;
    RangeT root_;
    RangeT n4_;
    RangeT end_;

    void maintain_(RangeT cl, RangeT cr, RangeT p) {
        int cm = cl + (cr - cl) / 2;
        if (cl != cr && if_lazy_[p]) {
            lazy_[p * 2] = lazy_[p];
            if_lazy_[p * 2] = 1;

            lazy_[p * 2 + 1] = lazy_[p];
            if_lazy_[p * 2 + 1] = 1;

            tree_[p * 2].range_update(lazy_[p], cl, cm);
            tree_[p * 2 + 1].range_update(lazy_[p], cm + 1, cr);

            lazy_[p] = Tag{};
            if_lazy_[p] = 0;
        }
    }

    Node range_query_(RangeT l, RangeT r, RangeT cl, RangeT cr, RangeT p) {
        if (l <= cl && cr <= r) {
            return tree_[p];
        }

        RangeT m = cl + (cr - cl) / 2;
        Node ans = Node{};

        maintain_(cl, cr, p);

        if (l <= m) {
            ans.update(range_query_(l, r, cl, m, p * 2));
        }
        if (r > m) {
            ans.update(range_query_(l, r, m + 1, cr, p * 2 + 1));
        }
        return ans;
    }

    void range_update_(RangeT l, RangeT r, Node val, RangeT cl, RangeT cr,
                       RangeT p) {
        if (l <= cl && cr <= r) {
            lazy_[p] = static_cast<Tag>(val);
            if_lazy_[p] = 1;
            tree_[p].range_update(lazy_[p], cl, cr);
            return;
        }

        RangeT m = cl + (cr - cl) / 2;
        maintain_(cl, cr, p);

        if (l <= m) {
            range_update_(l, r, val, cl, m, p * 2);
        }

        if (r > m) {
            range_update_(l, r, val, m + 1, cr, p * 2 + 1);
        }

        tree_[p].set(tree_[p * 2], tree_[p * 2 + 1]);
    }

    void build_(RangeT s, RangeT t, RangeT p) {
        if (s == t) {
            tree_[p] = (*arr_)[s];
            return;
        }

        RangeT m = s + (t - s) / 2;

        build_(s, m, p * 2);
        build_(m + 1, t, p * 2 + 1);

        tree_[p].set(tree_[p * 2], tree_[p * 2 + 1]);
    }

  public:
    explicit SegTreeLazy(std::vector<Node> v) {
        n_ = v.size();
        n4_ = n_ * 4;
        tree_ = vector<Node>(n4_, Node{});
        lazy_ = vector<Tag>(n4_, Tag{});
        if_lazy_ = vector<bool>(n4_, 0);
        arr_ = &v;
        end_ = n_ - 1;
        root_ = 1;
        build_(0, end_, 1);
        arr_ = nullptr;
    }

    Node range_query(RangeT l, RangeT r) {
        return range_query_(l, r, 0, end_, root_);
    }

    void range_update(RangeT l, RangeT r, Node val) {
        range_update_(l, r, val, 0, end_, root_);
    }
};

template <typename T>
struct Tag {
    T tag;

    explicit Tag() : tag(0) {}

    explicit Tag(T tag) : tag(tag) {}
};

template <typename T, typename RangeT = int>
class Node {

    T val_;

  public:
    explicit Node(T val) : val_(val) {}

    explicit Node() : val_(0) {}

    void set(const Node &l, const Node &r) { val_ = max(l.val_, r.val_); }

    void update(const Node kN) { val_ = max(val_, kN.val_); }

    void range_update(const Tag<T> &tag, RangeT l, RangeT r) { val_ = tag.tag; }

    T &get() { return val_; }

    explicit operator Tag<T>() { return Tag<T>{val_}; }
};
