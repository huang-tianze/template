#include <bits/stdc++.h>
using namespace std;

struct TransitiveClosure {
    static const int N = 110;
    bitset<N> a[N];
    int n;

    void read() {
        cin >> n;
        int d;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                a[i][j] = (cin >> d, d);
    }

    void compute() {
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                if (a[i][k]) a[i] |= a[k];
    }

    void print() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                cout << a[i][j];
            cout << '\n';
        }
    }
};

int main() {
    TransitiveClosure tc;
    tc.read();
    tc.compute();
    tc.print();
    return 0;
}
