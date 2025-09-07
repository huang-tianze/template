#include <bits/stdc++.h>
using namespace std;

void countingSort(vector<int> &arr, int maxVal) { // 要求非负
    int n = arr.size();
    vector<int> count(maxVal + 1, 0); //  统计数组
    vector<int> output(n);            // 结果数组

    // 1. 统计频率
    for (int x : arr) {
        count[x]++; // 次数为x出现的次数
    }

    // 2. 前缀和
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1]; // 此时count[x]等价于小于等于x的元素出现的次数,也就相当于x的排名
        // 小于等于x的有count[x]个，因而x不会放到count[x]还右
    }

    // 3. 倒序放置，这里相当于遍历arr，去算每个元素应该在的位置.。 倒序是为了稳定性，相等的元素保持原来的顺序
    for (int i = n - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    // 4. 写回原数组
    arr = output;

    // 另一种想法是遍历值域，不需要前缀和

    // 可以统计频率的过程中计算最大值和最小值，然后用值域长度和n比较以决定用哪个遍历，优化到O(min(n,w))，虽然貌似数组初始化的部分已经是O(n+w)
}
