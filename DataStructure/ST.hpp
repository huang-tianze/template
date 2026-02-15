#include <functional>
#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct ST {
    vector<vector<T>> st;
    int sz;
    function<T(T, T)> op;                                      // op can be max,min,gcd,lcm,&,|,etc.
    ST(vector<T> &x, function<T(T, T)> f) : op(std::move(f)) { // use lambda
        sz = x.size();
        int K = __lg(sz);
        st.resize(sz, vector<T>(K + 1));
        for (int i = 0; i < sz; i++) st[i][0] = x[i];
        for (int j = 1; j <= K; j++) {
            for (int i = 0; i + (1 << j) - 1 < sz; i++) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    T get(int l, int r) {
        int K = __lg(r - l + 1);
        return op(st[l][K], st[r - (1 << K) + 1][K]);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    ST<int> getMin(a, [&](int a, int b) { return min(a, b); });
    ST<int> getMax(a, [&](int a, int b) { return max(a, b); });
    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        int l, r;
        cin >> l >> r;
        if (op == 1) {
            cout << getMin.get(l, r) << endl;
        } else {
            cout << getMax.get(l, r) << endl;
        }
    }
}
