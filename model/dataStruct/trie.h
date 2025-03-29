// NOLINTBEGIN
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 5;
const int S = N * 50; // 可能出现的最长长度

struct trie {
    int nextNode[S][26]; // only lowwer
                         // letter，S表示当前节点，第二个维表示要加的char
    int nodeCount;
    bool exist[S];

    // int tag[S];  这里可以加一个表示额外的tag信息，在find里判断返回

    void insert(std::string &str) {
        int len = str.size();
        int index = 0;
        for (int i = 0; i < len; i++) {
            int ch = str[i] - 'a';
            if (!nextNode[index]
                         [ch]) { // 如果节点不存在，创建新节点（一个整数表示）
                nodeCount++;
                nextNode[index][ch] = nodeCount;
            }
            index = nextNode[index][ch];
        }
        exist[index] = true;
    }

    bool find(std::string &str) {
        int index = 0;
        int len = str.size();
        for (int i = 0; i < len; i++) {
            int ch = str[i] - 'a';
            if (!nextNode[index][ch])
                return 0;
            index = nextNode[index][ch];
        }
        return exist[index];
    }
};

// -----

struct TrieNode {
    int cnt_ = 0;
    unordered_map<char, TrieNode *> map_;

    ~TrieNode() {
        for (auto [i, j] : map_) {
            delete j;
        }
    }

    void insert(const char *str) {
        if (!str)
            return;
        auto nex = this->map_[str[0]] ? this->map_[str[0]] : new TrieNode;
        ++nex->cnt_;
        nex->insert(str + 1);
    }

    int find(const char *str) {
        if (this->map_[str[0]]) {
            return this->map_[str[0]]->find(str + 1);
        } else
            return 0;
    }
};

// NOLINTEND
