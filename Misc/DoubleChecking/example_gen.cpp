#include "genlib.hpp"

int main() {
    int n = randInt(5, 10), m = randInt(n-1, n+5);
    cout << "Array:" << endl;
    for (int x : genArray(n, 1, 100)) cout << x << " "; cout << endl;

    cout << "String:" << endl;
    cout << genString(n) << endl;

    cout << "Permutation:" << endl;
    for (int x : genPermutation(n)) cout << x << " "; cout << endl;

    cout << "Intervals:" << endl;
    for (auto [l, r] : genIntervals(n, 100)) cout << l << " " << r << endl;

    cout << "Tree:" << endl;
    for (auto [u, v] : genTree(n)) cout << u << " " << v << endl;

    cout << "Graph:" << endl;
    for (auto [u, v] : genUndirectedGraph(n, m)) cout << u << " " << v << endl;

    cout << "Matrix:" << endl;
    auto mat = genMatrix(n, 3);
    for (auto &row : mat) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }

    cout << "Union-Find Ops:" << endl;
    for (auto [u, v] : genUnionFindOps(n, m)) {
        if (u == -1) cout << "find " << v << endl;
        else cout << "union " << u << " " << v << endl;
    }

    return 0;
}