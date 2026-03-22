#include <utility>
using namespace std;

pair<int, int> ternary() {
    double l = 0, r = 1e9;
    const double eps = 1e-7;

    auto f = [](double x) {
        // x= ....
        return x;
    };

    while (r - l > eps) {
        double mid = (l + r) / 2;
        double lmid = mid - eps / 3;
        double rmid = mid + eps / 3;
        double lval = f(lmid), rval = f(rmid);

        // find max
        if (rval == lval) {
            l = lmid;
            r = rmid;
        } else if (rval > lval) {
            l = lmid;
        } else
            r = rmid;
    }
    return {l, f(l)};
}