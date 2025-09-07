#include <bits/stdc++.h>
using namespace std;
// 二分插入排序，在数组几乎有序的时候效率高，最优时间复杂度为O(n)，可以作为一些中间过程
void insertion_sort(int arr[], int len) {
    if (len < 2) return;
    for (int i = 1; i != len; ++i) {
        int key = arr[i];
        auto index = upper_bound(arr, arr + i, key) - arr;
        // 使用 memmove 移动元素，比使用 for 循环速度更快，时间复杂度仍为 O(n)
        memmove(arr + index + 1, arr + index, (i - index) * sizeof(int));
        arr[index] = key;
    }
}