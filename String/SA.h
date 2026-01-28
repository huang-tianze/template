#include <bits/stdc++.h>
using namespace std;

class SA {
  public:
    vector<int> sa;
    vector<int> rk;
    vector<int> oldrk;
    vector<int> id;
    vector<int> cnt;

  public:
    explicit SA(std::string &s) {
        const int n = s.size(); // NOLINT
        int m = 128;
        int p = 0;
        sa.resize(n * 2 + 2);
        rk.resize(n + 1);
        oldrk.resize(n + 1);
        id.resize(n + 1);
        cnt.resize(n + 1);

        for (int i = 1; i <= n; i++)
            cnt[rk[i] = s[i - 1]]++; // NOLINT
        for (int i = 1; i <= m; i++)
            cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--)
            sa[cnt[rk[i]]--] = i;

        for (int w = 1;; w <<= 1, m = p) { // m = p 即为值域优化
            int cur = 0;
            for (int i = n - w + 1; i <= n; i++)
                id[++cur] = i;
            for (int i = 1; i <= n; i++)
                if (sa[i] > w)
                    id[++cur] = sa[i] - w;

            memset(cnt.data(), 0,
                   cnt.size() * sizeof(decltype(cnt)::value_type));
            for (int i = 1; i <= n; i++)
                cnt[rk[i]]++;
            for (int i = 1; i <= m; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n; i >= 1; i--)
                sa[cnt[rk[id[i]]]--] = id[i];

            p = 0;
            memcpy(oldrk.data(), rk.data(),
                   oldrk.size() * sizeof(decltype(oldrk)::value_type));
            for (int i = 1; i <= n; i++) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                    oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
                    rk[sa[i]] = p;
                else
                    rk[sa[i]] = ++p;
            }

            if (p == n)
                break; // p = n 时无需再排序
        }
    }
};
