#include <bits/stdc++.h>
using namespace std;

#include "../DataStructure/binaryIndexedTree_2.h"

// 根据排列求其rank
// Get the rank of a permutation of 1~n.
long long find_rank(const std::vector<int> &nums) {
    int n = nums.size(); // NOLINT
    BIT bit(n);
    long long fac = 1;
    long long res = 0;
    // Reverse iteration.
    for (int i = n - 1; i >= 0; --i) {
        // Count the number of elements smaller than the current one.
        res += bit.query(nums[i] - 1) * fac;
        // Insert the current element into the BIT.
        bit.add(nums[i], 1);
        // Update the factorial.
        fac *= n - i;
    }
    return res + 1;
}

// 根据rank求排列1~n
std::vector<int> find_permutation(int n, long long k) {
    --k;
    // Expand rank to Lehmer code.
    std::vector<int> lehmer(n);
    for (int i = 1; i <= n; ++i) {
        lehmer[n - i] = k % i;
        k /= i;
    }
    BIT bit(n);
    // Set all values in BIT to one.
    bit.fill();
    std::vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        // Find the lehmer[i]-th smallest unused element.
        res[i] = bit.find_kth(lehmer[i] + 1);
        // Remove it from the BIT.
        bit.add(res[i], -1);
    }
    return res;
}
