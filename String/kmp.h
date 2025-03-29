#include <bits/stdc++.h>
using namespace std;

// NOLINTBEGIN
/*
int kmpmatch(string* s,string* sub){
    if(sub->len==0){
        return 0;
    }
    int pi[s->len];
    pi[0]=0;
    for(int i=1;i<s->len;i++){
        int len=pi[i-1];
        while(len!=0&&s->data[i]!=s->data[len]){
            len=pi[len-1];
        }
        if(s->data[i]==s->data[len]){
            len++;
            pi[i]=len;
        }
        else{
            pi[i]=0;
        }
    }
    //创建next数组
    int ans=0;
    for(int i=0;i<s->len;i++){
        if(pi[i]==sub->len){
            ans++;
        }
    }
    //比对子字符串与next数组
    return ans;
}*/

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> find_occurrences(string text, string pattern) {
    string cur = pattern + '#' + text;
    int sz1 = text.size(), sz2 = pattern.size();
    vector<int> v;
    vector<int> lps = prefix_function(cur);
    for (int i = sz2 + 1; i <= sz1 + sz2; i++) {
        if (lps[i] == sz2)
            v.push_back(i - 2 * sz2);
    }
    return v;
}

// NOLINTEND
