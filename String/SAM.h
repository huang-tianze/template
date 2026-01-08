#include <bits/stdc++.h>
using namespace std;

/*
s -> string
ss -> sub string
占用空间为|s| * 2
*/
class SAM {
    struct State {
        int len = 0, link = -1;
        map<char, int> next;
    };

    vector<State> st;
    int last = 0;
    int sz = 0;

  public:
    // O(|s|)
    explicit SAM(std::string &s) : last(0) {
        st.resize(s.size() * 2 + 2);
        sz++;
        for (auto c : s) {
            add(c);
        }
    }

    void add(const char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) { // NOLINT
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    // O(|s|)
    // s 是否为 SAM 的子串
    bool is_sub_str(const std::string &s) {
        int curr = 0;
        for (auto c : s) {
            if (!st[curr].next.count(c)) {
                return false;
            }
            curr = st[curr].next[c];
        }
        return true;
    }

    // O(st.size())
    // 求SAM的所有不同子串的个数和
    long long all_sub_str_num() {
        long long ret = 0;
        for (const auto &i : st) {
            ret += i.len - st[i.link].len;
        }
        return ret;
    }

    // O(st.size())
    // 求SAM的所有不同子串的长度的和
    long long all_sub_str_len() {
        long long ret = 0;
        for (const auto &i : st) {
            ret += (i.len + st[i.link].len + 1) * (i.len - st[i.link].len) / 2;
        }
        return ret;
    }
};
