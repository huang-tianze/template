
#include <cstddef>
#include <cstdint>
#include <vector>
/**
 * @brief static segment tree, supports interval infomation maintainance(e.g. sum) and modification, can not add new node
 * @note segVals are 1-based, node[0]'s right -> 1, left:2i, right:2i+1
 * @note inner index is 1-based for binary heap(idx parameter), while outer index could be 1-based or 0-based, dependent on parameters passed in(left, right)
 */

// TODO: subscript maintainance, init left and right memoriezed

template <class T>
class SegmentTree {
public:
private:
    std::vector<T> segVal; // indexed like heap
    size_t sz = 0;
    std::vector<T> lazyTag;

public:
    explicit SegmentTree(const std::vector<T> &arr) : sz(arr.size()), lazyTag(sz * 2, T(0)) {
        segVal.resize(sz * 2);
        build(1, 0, sz, arr);
    }
    SegmentTree(const std::vector<T> &arr, size_t left, size_t right) : sz(arr.size()), lazyTag(sz * 2, T(0)) {
        segVal.resize(sz * 2);
        build(1, left, right, arr);
    }

    T range_sum(size_t lower, size_t upper) {
        return range_sum(1,lower,upper,0,sz);
    }

protected:
    T range_sum(int idx, size_t lower, size_t upper,size_t left, size_t right) {
        if(lower>=left&&upper<=right) return segVal[idx];
        if(upper<right||lower>right) return T(0);
        
    }
    void build(uint64_t idx, size_t left, size_t right, const std::vector<T> &arr) { // 1-based, left: 2i, right:2i+1 <
        if(left > right) return;
        if (left == right) {
            segVal[idx] = arr[left];
            return;
        }
        uint64_t mid = left + (right - left) > 1;
        build(2 * idx, left, mid, arr);
        build(2 * idx + 1, mid + 1, right, arr);
        segVal[idx] = segVal[idx * 2] + segVal[idx * 2 + 1];
    }
    void pullDown(size_t idx) {
        if (lazyTag[idx]) {
            segVal[idx] += lazyTag[idx]; //TODO: interval sum
            lazyTag[idx * 2] += lazyTag[idx];
            lazyTag[idx * 2 + 1] += lazyTag[idx];
            lazyTag[idx] = 0;
        }
    }
};