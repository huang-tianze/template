## STL 函数


## 字符串

### kmp



### 多项式 hash、子串 hash


### 二进制:



## 数据结构

### 树状数组

TODO: 树状数组有问题
[树状数组](./dataStruct/binaryIndexedTree.h)


### 并查集

TODO: nedd to update
[并查集](./dataStruct/disjointSet.h)

### trie(定长数组版)


### next_permutation (algorithm)

```

## 树

### 线段树

```cpp

```

---

```cpp
// // needed: 原数组a[], 线段树数组d[], (可选)懒惰标记数组sign[]


// // 原数组a[],线段树d[]
// void init(int left, int right, int par, int a[],int d[]){
//     if (left == right) {
//         d[par] = a[left];
//         return;
//     }
//     int mid = left + ((right - left) >>1);
//     init(left, mid, par*2, a, d);
//     init(mid+1, right, par*2+1, a, d);
//     d[par] = d[par*2] + d[par*2+1];
// }

// // 区间查询
// int getsum(int left, int right, int s, int t, int p,int d[]){
//     if (left <= s && right <= t) {
//         return d[p];
//     }
//     int m = left + ((right - left)>>1);
//     int sum = 0;
//     if(left <= m) sum += getsum(left,right,s,m,p*2,d);
//     if(right > m) sum += getsum(left,right,m+1,t,p*2+1,d);
//     return sum;
// }

// // 区间修改与懒惰标记
```

## 动态规划

1. 背包

```cpp


```

2. 最长公共子序列

```cpp

char a[1001], b[1001];
int dp[1001][1001], len1, len2;
void lcs(int i,int j)
{
    for(i=1; i<=len1; i++)
    {
        for(j=1; j<=len2; j++)
        {
            if(a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else if(dp[i-1][j] > dp[i][j-1])
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = dp[i][j-1];
        }
    }
}
printf("%d\n",dp[len1][len2])
```

### LCA

```cpp
Treenode LCA(Treenode root,Treenode p,treenode q){
    if(root==NULL||root==p||root==q) return root;
    Treenode l=LCA(root.left,p,q);
    Treenode r=LCA(root.right,p,q);
    if(l!=NULL&&r!=NULL){
        return root;
    }
    if(l==NULL&&r==NULL){
        return NULL;
    }
    return l!=NULL?l:r;
}
```

## 数论

### 错排

$$ D[n] = n \* (~ D[n-1] + D[n-2]~) $$

### 卡特兰数

入栈顺序为 $1,2,\ldots ,n$，求所有可能的出栈顺序的总数
$$ H[n] = \sum\_{i=0}^{n-1} H[i] \* H[n-i-1] $$

```cpp
#include <iostream>
using namespace std;
int n;
long long f[25];

int main() {
  f[0] = 1;
  cin >> n;
  for (int i = 1; i <= n; i++) f[i] = f[i - 1] * (4 * i - 2) / (i + 1);
  // 这里用的是常见公式2
  cout << f[n] << endl;
  return 0;
}
```

### 中国剩余定理

```cpp

```

### exgcd、欧拉函数

### 模 b 下快速幂

```cpp

```

### 线性筛

```cpp
```

### 图论

## 最小生成树、判负环

### 最短路 spfa

```cpp
vector<int> spfa(int s) {
    vector<int> dist(n, INT_MAX);
    vector<bool> inq(n, false);
    vector<int> cnt(n, 0);

    queue<int> q;
    dist[s] = 0;
    inq[s] = true;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;

        for (auto &e : adj[u]) {
            if (dist[u] != INT_MAX && dist[e.to] > dist[u] + e.weight) {
                dist[e.to] = dist[u] + e.weight;

                if (!inq[e.to]) {
                    q.push(e.to);
                    inq[e.to] = true;

                    if (++cnt[e.to] > n) {
                        return {};
                    }
                }
            }
        }
    } return dist;
}
```

### spaf 判负环：

```cpp

```

### Dijstra 最短路

```cpp

```

### A\*

```cpp


```

### 拓扑排序

```cpp

```

## 杂项

### FAST_IO



### BigInt 1

```cpp
/**   高精度（BigInt）
 *    2023-09-11: https://qoj.ac/submission/176420
**/


```

### BigInt 2

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInt {
private:
    std::vector<int> digits;
    bool is_negative;

public:
    BigInt() : is_negative(false) {}
    BigInt(const std::string &num) {
        if (num.empty()) {
            digits.push_back(0);
            is_negative = false;
            return;
        }

        size_t start = 0;
        is_negative = (num[0] == '-');
        if (is_negative) start = 1;

        for (size_t i = start; i < num.size(); i++) {
            if (!isdigit(num[i])) throw std::invalid_argument("Invalid BigInt string");
            digits.push_back(num[i] - '0');
        }
        std::reverse(digits.begin(), digits.end());
    }

    BigInt operator+(const BigInt &other) const {
        if (is_negative == other.is_negative) {
            BigInt result;
            result.is_negative = is_negative;
            result.digits = add(digits, other.digits);
            return result;
        }
        return is_negative ? (other - abs()) : (*this - other.abs());
    }

    BigInt operator-(const BigInt &other) const {
        if (is_negative != other.is_negative) {
            BigInt result;
            result.is_negative = is_negative;
            result.digits = add(digits, other.digits);
            return result;
        }
        if (abs() < other.abs()) {
            return -(other - *this);
        }
        BigInt result;
        result.digits = subtract(digits, other.digits);
        result.is_negative = is_negative;
        return result;
    }

    BigInt operator*(const BigInt &other) const {
        BigInt result;
        result.digits = multiply(digits, other.digits);
        result.is_negative = (is_negative != other.is_negative);
        return result;
    }

    bool operator<(const BigInt &other) const {
        if (is_negative != other.is_negative) return is_negative;
        if (digits.size() != other.digits.size())
            return (digits.size() < other.digits.size()) ^ is_negative;
        for (int i = digits.size() - 1; i >= 0; i--)
            if (digits[i] != other.digits[i])
                return (digits[i] < other.digits[i]) ^ is_negative;
        return false;
    }

    BigInt abs() const {
        BigInt result = *this;
        result.is_negative = false;
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInt &num) {
        if (num.is_negative) os << '-';
        for (int i = num.digits.size() - 1; i >= 0; i--)
            os << num.digits[i];
        return os;
    }

private:
    static std::vector<int> add(const std::vector<int> &a, const std::vector<int> &b) {
        std::vector<int> result;
        int carry = 0, i = 0;
        while (i < a.size() || i < b.size() || carry) {
            int sum = carry + (i < a.size() ? a[i] : 0) + (i < b.size() ? b[i] : 0);
            result.push_back(sum % 10);
            carry = sum / 10;
            i++;
        }
        return result;
    }

    static std::vector<int> subtract(const std::vector<int> &a, const std::vector<int> &b) {
        std::vector<int> result(a);
        int borrow = 0;
        for (size_t i = 0; i < b.size() || borrow; i++) {
            result[i] -= (i < b.size() ? b[i] : 0) + borrow;
            borrow = result[i] < 0;
            if (borrow) result[i] += 10;
        }
        while (result.size() > 1 && result.back() == 0)
            result.pop_back();
        return result;
    }

    static std::vector<int> multiply(const std::vector<int> &a, const std::vector<int> &b) {
        std::vector<int> result(a.size() + b.size(), 0);
        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < b.size(); j++) {
                result[i + j] += a[i] * b[j];
                if (result[i + j] >= 10) {
                    result[i + j + 1] += result[i + j] / 10;
                    result[i + j] %= 10;
                }
            }
        }
        while (result.size() > 1 && result.back() == 0)
            result.pop_back();
        return result;
    }
};

int main() {
    BigInt num1("12345678901234567890");
    BigInt num2("98765432109876543210");

    std::cout << "Sum: " << num1 + num2 << std::endl;
    std::cout << "Diff: " << num2 - num1 << std::endl;
    std::cout << "Product: " << num1 * num2 << std::endl;
    return 0;
}

```

<!-- #endregion -->



## Addition 博弈论

### 巴什博奕

> 有 $N$ 个石子，两名玩家轮流行动，按以下规则取石子：
> 
> 规定：每人每次可以取走 $X(1 \le X \le M)$ 个石子，拿到最后一颗石子的一方获胜。
> 
> 双方均采用最优策略，询问谁会获胜。

> 两名玩家轮流报数。
> 
> 规定：第一个报数的人可以报 $X(1 \le X \le M)$ ，后报数的人需要比前者所报数大 $Y(1 \le Y \le M)$ ，率先报到 $N$ 的人获胜。
> 
> 双方均采用最优策略，询问谁会获胜。

- $N=K\cdot(M+1)$ （其中 $K \in \mathbb{N}^+$ ），后手必胜（后手可以控制每一回合结束时双方恰好取走 $M+1$ 个，重复 $K$ 轮后即胜利）；
- $N=K\cdot(M+1)+R$ （其中 $K \in \mathbb{N}^+,0 < R < M + 1$ ），先手必胜（先手先取走 $R$ 个，之后控制每一回合结束时双方恰好取走 $M+1$ 个，重复 $K$ 轮后即胜利）。

### 扩展巴什博弈

> 有 $N$ 颗石子，两名玩家轮流行动，按以下规则取石子：。
> 
> 规定：每人每次可以取走 $X(a \le X \le b)$ 个石子，如果最后剩余物品的数量小于 $a$ 个，则不能再取，拿到最后一颗石子的一方获胜。
> 
> 双方均采用最优策略，询问谁会获胜。

- $N = K\cdot(a+b)$ 时，后手必胜；
- $N = K\cdot(a+b)+R_1$ （其中 $K \in \mathbb{N}^+,0 < R_1 < a$ ） 时，后手必胜（这些数量不够再取一次，先手无法逆转局面）；
- $N = K\cdot(a+b)+R_2$ （其中 $K \in \mathbb{N}^+,a \le R_2 \le b$ ） 时，先手必胜；
- $N = K\cdot(a+b)+R_3$ （其中 $K \in \mathbb{N}^+,b < R_3 < a + b$ ） 时，先手必胜（这些数量不够再取一次，后手无法逆转局面）；

### Nim 博弈

> 有 $N$ 堆石子，给出每一堆的石子数量，两名玩家轮流行动，按以下规则取石子：
> 
> 规定：每人每次任选一堆，取走正整数颗石子，拿到最后一颗石子的一方获胜（注：几个特点是**不能跨堆**、**不能不拿**）。
> 
> 双方均采用最优策略，询问谁会获胜。

记初始时各堆石子的数量 $(A_1,A_2,\dots,A_n)$ ，定义尼姆和 $Sum_N = A_1 \oplus A_2 \oplus \dots \oplus A_n$ 。

**当** $\pmb{ Sum_N = 0 }$ **时先手必败，反之先手必胜。**

### Nim 游戏具体取法

先计算出尼姆和，再对每一堆石子计算 $A_i \oplus Sum_N$ ，记为 $X_i$ 。

若得到的值 $X_i<A_i$ ，$X_i$ 即为一个可行解，即**剩下** $\pmb X_i$ **颗石头，取走** $\pmb {A_i - X_i}$ **颗石头**（这里取小于号是因为至少要取走 $1$ 颗石子）。

### Moore’s Nim 游戏（Nim-K 游戏）

> 有 $N$ 堆石子，给出每一堆的石子数量，两名玩家轮流行动，按以下规则取石子：
> 
> 规定：每人每次任选不超过 $K$ 堆，对每堆都取走不同的正整数颗石子，拿到最后一颗石子的一方获胜。
> 
> 双方均采用最优策略，询问谁会获胜。

把每一堆石子的石子数用二进制表示，定义 $One_i$ 为二进制第 $i$ 位上 $1$ 的个数。

**以下局面先手必胜：**

**对于每一位，** $\pmb{One_1,One_2,\dots ,One_N}$ **均不为** $\pmb{K+1}$ **的倍数。**

### Anti-Nim 游戏（反 Nim 游戏）

> 有 $N$ 堆石子，给出每一堆的石子数量，两名玩家轮流行动，按以下规则取石子：
> 
> 规定：每人每次任选一堆，取走正整数颗石子，拿到最后一颗石子的一方**出局**。
> 
> 双方均采用最优策略，询问谁会获胜。

- 所有堆的石头数量均不超过 $1$ ，且 $\pmb {Sum_N=0}$ （也可看作“且有偶数堆”）；
- 至少有一堆的石头数量大于 $1$ ，且 $\pmb{Sum_N \neq 0}$ 。

### 阶梯 - Nim 博弈

> 有 $N$ 级台阶，每一级台阶上均有一定数量的石子，给出每一级石子的数量，两名玩家轮流行动，按以下规则操作石子：
> 
> 规定：每人每次任选一级台阶，拿走正整数颗石子放到下一级台阶中，已经拿到地面上的石子不能再拿，拿到最后一颗石子的一方获胜。
> 
> 双方均采用最优策略，询问谁会获胜。

**对奇数台阶做传统** $\pmb{\tt{}Nim}$ **博弈，当** $\pmb{Sum_N=0}$** 时先手必败，反之先手必胜。**

### SG 游戏（有向图游戏）

我们使用以下几条规则来定义暴力求解的过程：

- 使用数字来表示输赢情况，$0$ 代表局面必败，非 $0$ 代表**存在必胜可能**，我们称这个数字为这个局面的SG值；
- 找到最终态，根据题意人为定义最终态的输赢情况；
- 对于非最终态的某个节点，其SG值为所有子节点的SG值取 $\tt{}mex$ ；
- 单个游戏的输赢态即对应根节点的SG值是否为 $0$ ，为 $0$ 代表先手必败，非 $0$ 代表先手必胜；
- 多个游戏的总SG值为单个游戏SG值的异或和。

使用哈希表，以 $\mathcal{O} (N + M)$ 的复杂度计算。

```c++
int n, m, a[N], num[N];
int sg(int x) {
    if (num[x] != -1) return num[x];
    
    unordered_set<int> S;
    for (int i = 1; i <= m; ++ i) 
        if(x >= a[i]) 
            S.insert(sg(x - a[i]));
    
    for (int i = 0; ; ++ i)
        if (S.count(i) == 0)
            return num[x] = i;
}
void Solve() {
    cin >> m;
    for (int i = 1; i <= m; ++ i) cin >> a[i];
    cin >> n;
    
    int ans = 0; memset(num, -1, sizeof num);
    for (int i = 1; i <= n; ++ i) {
        int x; cin >> x;
        ans ^= sg(x);
    }
    
    if (ans == 0) no;
    else yes;
}
```

### Anti-SG 游戏（反 SG 游戏）

SG 游戏中最先不能行动的一方获胜。

**以下局面先手必胜：**

- **单局游戏的SG值均不超过** $\pmb 1$ **，且总SG值为** $\pmb 0$；
- **至少有一局单局游戏的SG值大于** $\pmb 1$ **，且总SG值不为** $\pmb 0$ 。

在本质上，这与 Anti-Nim 游戏的结论一致。

### Lasker’s-Nim 游戏（ Multi-SG 游戏）

> 有 $N$ 堆石子，给出每一堆的石子数量，两名玩家轮流行动，每人每次任选以下规定的一种操作石子：
> 
> - 任选一堆，取走正整数颗石子；
> - 任选数量大于 $2$ 的一堆，分成两堆非空石子。
> 
> 拿到最后一颗石子的一方获胜。双方均采用最优策略，询问谁会获胜。

**本题使用SG函数求解，SG值定义为：**

$$\pmb{ SG(x) = 
\begin{cases}
x-1 & \text{ , } x\mod 4= 0\\ 
x & \text{ , } x \mod 4 = 1\\ 
x & \text{ , } x \mod 4 = 2\\ 
x+1 & \text{ , } x \mod 4 = 3
\end{cases}}$$

### Every-SG 游戏

> 给出一个有向无环图，其中 $K$ 个顶点上放置了石子，两名玩家轮流行动，按以下规则操作石子：
> 
> 移动图上所有还能够移动的石子；
> 
> 无法移动石子的一方出局。双方均采用最优策略，询问谁会获胜。

定义 $step$ 为某一局游戏至多需要经过的回合数。

**以下局面先手必胜：**$\pmb{step}$ **为奇数** 。

### 威佐夫博弈

> 有两堆石子，给出每一堆的石子数量，两名玩家轮流行动，每人每次任选以下规定的一种操作石子：
> 
> - 任选一堆，取走正整数颗石子；
> - 从两队中同时取走正整数颗石子。
> 
> 拿到最后一颗石子的一方获胜。双方均采用最优策略，询问谁会获胜。

**以下局面先手必败：**

$\pmb{ (1, 2), (3, 5), (4, 7), (6, 10), …}$ 具体而言，每一对的第一个数为此前没出现过的最小整数，第二个数为第一个数加上 $\pmb{1,2,3,4,…}$ 。

更一般地，对于第 $\pmb k$ 对数，第一个数为 $\pmb {First_k= \left \lfloor \frac{k*(1+\sqrt 5)}{2} \right \rfloor}$ ，第二个数为 $\pmb{Second_k=First_k+k}$ 。

其中，在两堆石子的数量均大于 $10^9$ 次时，由于需要使用高精度计算，我们需要人为定义 $\frac{1+\sqrt 5}{2}$ 的取值为 $lorry = 1.618033988749894848204586834$ 。

```c++
const double lorry = (sqrt(5.0) + 1.0) / 2.0;
//const double lorry = 1.618033988749894848204586834;
void Solve() {
    int n, m; cin >> n >> m;
    if (n < m) swap(n, m);
    double x = n - m;
    if ((int)(lorry * x) == m) cout << "lose\n";
    else cout << "win\n";
}
```

### 斐波那契博弈

> 有一堆石子，数量为 $N$ ，两名玩家轮流行动，按以下规则取石子：
> 
> 先手第1次可以取任意多颗，但不能全部取完，此后每人取的石子数不能超过上个人的两倍，拿到最后一颗石子的一方获胜。
> 
> 双方均采用最优策略，询问谁会获胜。

当且仅当 $N$ 为斐波那契数时先手必败。

```c++
int fib[100] = {1, 2};
map<int, bool> mp;
void Force() {
  for (int i = 2; i <= 86; ++ i) fib[i] = fib[i - 1] + fib[i - 2];
    for (int i = 0; i <= 86; ++ i) mp[fib[i]] = 1;
}
void Solve() {
    int n; cin >> n;
    if (mp[n] == 1) cout << "lose\n";
    else cout << "win\n";
}
```

### 树上删边游戏

> 给出一棵 $N$ 个节点的有根树，两名玩家轮流行动，按以下规则操作：
> 
> 选择任意一棵子树并删除（即删去任意一条边，不与根相连的部分会同步被删去）；
> 
> 删掉最后一棵子树的一方获胜（换句话说，删去根节点的一方失败）。双方均采用最优策略，询问谁会获胜。

结论：当根节点SG值非 $1$ 时先手必胜。

**相较于传统SG值的定义，本题的SG函数值定义为：**

- 叶子节点的SG值为 $\pmb 0$ 。
- 非叶子节点的SG值为其所有孩子节点SG值 $\pmb + 1$ 的异或和。

```c++
auto dfs = [&](auto self, int x, int fa) -> int {
    int x = 0;
    for (auto y : ver[x]) {
        if (y == fa) continue;
        x ^= self(self, y, x);
    }
    return x + 1;
};
cout << (dfs(dfs, 1, 0) == 1 ? "Bob\n" : "Alice\n");
```

### 无向图删边游戏（Fusion Principle 定理）

> 给出一张 $N$ 个节点的无向联通图，有一个点作为图的根，两名玩家轮流行动，按以下规则操作：
> 
> 选择任意一条边删除，不与根相连的部分会同步被删去；
> 
> 删掉最后一条边的一方获胜。双方均采用最优策略，询问谁会获胜。

- **对于奇环，我们将其缩成一个新点+一条新边；**
- **对于偶环，我们将其缩成一个新点；**
- **所有连接到原来环上的边全部与新点相连。**

此时，本模型转化为“树上删边游戏”。

<div style="page-break-after:always">/END/</div>

## Addition 动态规划

### 01背包

有 $n$ 件物品和一个容量为 $W$ 的背包，第 $i$ 件物品的体积为 $w[i]$，价值为 $v[i]$，求解将哪些物品装入背包中使总价值最大。

**思路：**

当放入一个价值为 $w[i]$ 的物品后，价值增加了 $v[i]$，于是我们可以构建一个二维的 $dp[i][j]$ 数组，装入第 $i$ 件物品时，背包容量为 $j$ 能实现的 **最大价值**，可以得到 **转移方程** $dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i])$。

```c++
for (int i = 1; i <= n; i++)
    for (int j = 0; j <= W; j++){
        dp[i][j] = dp[i - 1][j];
        if (j >= w[i])
            dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + v[i]);
    }
```

我们可以发现，第 $i$ 个物品的状态是由第 $i - 1$ 个物品转移过来的，每次的 $j$ 转移过来后，第 $i - 1$ 个方程的 $j$ 已经没用了，于是我们想到可以把二维方程压缩成 **一维** 的，用以 **优化空间复杂度**。 

```c++
for (int i = 1; i <= n; i++)  //当前装第 i 件物品
    for (int j = W; j >= w[i]; j--)  //背包容量为 j
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);  //判断背包容量为 j 的情况下能是实现总价值最大是多少
```

### 完全背包

有 $n$ 件物品和一个容量为 $W$ 的背包，第 $i$ 件物品的体积为 $w[i]$，价值为 $v[i]$，每件物品有**无限个**，求解将哪些物品装入背包中使总价值最大。

**思路:**

思路和**01背包**差不多，但是每一件物品有**无限个**，其实就是从每 **种** 物品中取 $0, 1, 2,... $ 件物品加入背包中

```c++
for (int i = 1; i <= n; i++)
    for (int j = 0; j <= W; j++)
        for (int k = 0; k * w[i] <= j; k++)    //选取几个物品 
            dp[i][j] = max(dp[i][j], dp[i - 1][j - k * w[i]] + k * v[i]);
```

实际上，我们可以发现，取 $k$ 件物品可以从取 $k - 1$ 件转移过来，那么我们就可以将 $k$ 的循环优化掉

```c++
for (int i = 1; i <= n; i++)
    for (int j = 0; j <= W; j++){
        dp[i][j] = dp[i - 1][j];
        if (j >= w[i])
            dp[i][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
    }
```

和 01 背包 类似地压缩成一维

```c++
for (int i = 1; i <= n; i++)
    for (int j = w[i]; j <= W; j++)
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
```

### 多重背包

有 $n$ **种**物品和一个容量为 $W$ 的背包，第 $i$ **种**物品的体积为 $w[i]$，价值为 $v[i]$，数量为 $s[i]$，求解将哪些物品装入背包中使总价值最大。

**思路：**

对于每一种物品，都有 $s[i]$ 种取法，我们可以将其转化为**01背包**问题

```c++
for (int i = 1; i <= n; i++){
    for (int j = W; j >= 0; j--)
        for (int k = 0; k <= s[i]; k++){
            if (j - k * w[i] < 0) break;
            dp[j] = max(dp[j], dp[j - k * w[i]] + k * v[i]);
        }
```

上述方法的时间复杂度为 $O(n * m * s)$。

```c++
for (int i = 1; i <= n; i++){
    scanf("%lld%lld%lld", &x, &y, &s);  //x 为体积， y 为价值， s 为数量
    t = 1;
    while (s >= t){
        w[++num] = x * t;
        v[num] = y * t;
        s -= t;
        t *= 2;
    }
    w[++num] = x * s;
    v[num] = y * s;
}
for (int i = 1; i <= num; i++)
    for (int j = W; j >= w[i]; j--)
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
```

尽管采用了 **二进制优化**，时间复杂度还是太高，采用 **单调队列优化**，将时间复杂度优化至 $O(n * m)$

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, W, w, v, s, f[N], g[N], q[N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n >> W;
    for (int i = 0; i < n; i ++ ){
        memcpy ( g, f, sizeof f);
        cin >> w >> v >> s;
        for (int j = 0; j < w; j ++ ){
            int head = 0, tail = -1;
            for (int k = j; k <= W; k += w){
                if ( head <= tail && k - s * w > q[head] ) head ++ ;//保证队列长度 <= s 
                while ( head <= tail && g[q[tail]] - (q[tail] - j) / w * v <= g[k] - (k - j) / w * v ) tail -- ;//保证队列单调递减 
                q[ ++ tail] = k;
                f[k] = g[q[head]] + (k - q[head]) / w * v;
            }
        }
    }
    cout << f[W] << "\n";
    return 0;
}
```

### 混合背包

放入背包的物品可能只有 **1** 件（01背包），也可能有**无限**件（完全背包），也可能只有**可数的几件**（多重背包）。

**思路：**

分类讨论即可，哪一类就用哪种方法去 $dp$。

```c++
#include <bits/stdc++.h>
using namespace std;
int n, W, w, v, s;
int main(){
    cin >> n >> W;
    vector <int> f(W + 1);
    for (int i = 0; i < n; i ++ ){
        cin >> w >> v >> s;
        if (s == -1){
            for (int j = W; j >= w; j -- )
                f[j] = max(f[j], f[j - w] + v);
        }
        else if (s == 0){
            for (int j = w; j <= W; j ++ )
                f[j] = max(f[j], f[j - w] + v);
        }
        else {
            int t = 1, cnt = 0;
            vector <int> x(s + 1), y(s + 1);
            while (s >= t){
                x[++cnt] = w * t;
                y[cnt] = v * t;
                s -= t;
                t *= 2;
            }
            x[++cnt] = w * s;
            y[cnt] = v * s;
            for (int i = 1; i <= cnt; i ++ )
                for (int j = W; j >= x[i]; j -- )
                    f[j] = max(f[j], f[j - x[i]] + y[i]);
        }
    }
    cout << f[W] << "\n";
    return 0;
}
```

### 二维费用的背包

有 $n$ 件物品和一个容量为 $W$ 的背包，背包能承受的最大重量为 $M$，每件物品只能用一次，第 $i$ 件物品的体积是 $w[i]$，重量为 $m[i]$，价值为 $v[i]$，求解将哪些物品放入背包中使总体积不超过背包容量，总重量不超过背包最大容量，且总价值最大。

**思路：**

背包的限制条件由一个变成两个，那么我们的循环再多一维即可。

```c++
for (int i = 1; i <= n; i++)
    for (int j = W; j >= w; j--)  //容量限制
        for (int k = M; k >= m; k--)  //重量限制
            dp[j][k] = max(dp[j][k], dp[j - w][k - m] + v);
```

### 分组背包

有 $n$ **组**物品，一个容量为 $W$ 的背包，每组物品有若干，同一组的物品最多选一个，第 $i$ 组第 $j$ 件物品的体积为 $w[i][j]$，价值为 $v[i][j]$，求解将哪些物品装入背包，可使物品总体积不超过背包容量，且使总价值最大。

**思路：**

考虑每**组**中的**某件**物品选不选，可以选的话，去下一组选下一个，否则在这组继续寻找可以选的物品，当这组遍历完后，去下一组寻找。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, W, s[N], w[N][N], v[N][N], dp[N];
int main(){
    cin >> n >> W;
    for (int i = 1; i <= n; i++){
        scanf("%d", &s[i]);
        for (int j = 1; j <= s[i]; j++)
            scanf("%d %d", &w[i][j], &v[i][j]);
    }
    for (int i = 1; i <= n; i++)
        for (int j = W; j >= 0; j--)
            for (int k = 1; k <= s[i]; k++)
                if (j - w[i][k] >= 0)
                    dp[j] = max(dp[j], dp[j - w[i][k]] + v[i][k]);
    cout << dp[W] << "\n";
    return 0;
}
```

### 有依赖的背包

有 $n$ 个物品和一个容量为 $W$ 的背包，物品之间有依赖关系，且之间的依赖关系组成一颗 **树** 的形状，如果选择一个物品，则必须选择它的 **父节点**，第 $i$ 件物品的体积是 $w[i]$，价值为 $v[i]$，依赖的父节点的编号为 $p[i]$，若 $p[i]$ 等于 -1，则为 **根节点**。求将哪些物品装入背包中，使总体积不超过总容量，且总价值最大。

**思路：**

定义 $f[i][j]$ 为以第 $i$ 个节点为根，容量为 $j$ 的背包的最大价值。那么结果就是 $f[root][W]$，为了知道根节点的最大价值，得通过其子节点来更新。所以采用递归的方式。
对于每一个点，先将这个节点装入背包，然后找到剩余容量可以实现的最大价值，最后更新父节点的最大价值即可。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int n, W, w[N], v[N], p, f[N][N], root;
vector <int> g[N];
void dfs(int u){
    for (int i = w[u]; i <= W; i ++ )
        f[u][i] = v[u];
    for (auto v : g[u]){
        dfs(v);
        for (int j = W; j >= w[u]; j -- )
            for (int k = 0; k <= j - w[u]; k ++ )
                f[u][j] = max(f[u][j], f[u][j - k] + f[v][k]);
    }
}
int main(){
    cin >> n >> W;
    for (int i = 1; i <= n; i ++ ){
        cin >> w[i] >> v[i] >> p;
        if (p == -1) root = i;
        else g[p].push_back(i);
    }
    dfs(root);
    cout << f[root][W] << "\n";
    return 0;
}
```

### 背包问题求方案数

有 $n$ 件物品和一个容量为 $W$ 的背包，每件物品只能用一次，第 $i$ 件物品的重量为 $w[i]$，价值为 $v[i]$，求解将哪些物品放入背包使总重量不超过背包容量，且总价值最大，输出 **最优选法的方案数**，答案可能很大，输出答案模 $10^9 + 7$ 的结果。

**思路：**

开一个储存方案数的数组 $cnt$，$cnt[i]$ 表示容量为 $i$ 时的 **方案数**，先将 $cnt$ 的每一个值都初始化为 1，因为 **不装任何东西就是一种方案**，如果装入这件物品使总的价值 **更大**，那么装入后的方案数 **等于** 装之前的方案数，如果装入后总价值 **相等**，那么方案数就是 **二者之和**

```c++
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int mod = 1e9 + 7, N = 1010;
LL n, W, cnt[N], f[N], w, v;
int main(){
    cin >> n >> W;
    for (int i = 0; i <= W; i ++ )
        cnt[i] = 1;
    for (int i = 0; i < n; i ++ ){
        cin >> w >> v;
        for (int j = W; j >= w; j -- )
            if (f[j] < f[j - w] + v){
                f[j] = f[j - w] + v;
                cnt[j] = cnt[j - w];
            }
            else if (f[j] == f[j - w] + v){
                cnt[j] = (cnt[j] + cnt[j - w]) % mod;
            }
    }
    cout << cnt[W] << "\n";
    return 0;
}
```

### 背包问题求具体方案

有 $n$ 件物品和一个容量为 $W$ 的背包，每件物品只能用一次，第 $i$ 件物品的重量为 $w[i]$，价值为 $v[i]$，求解将哪些物品放入背包使总重量不超过背包容量，且总价值最大，输出 **字典序最小的方案**

**思路：**

01 背包求解最优方案中 **字典序最小的方案**，**首先** 我们先求 **01背包**，因为这道题需要输出方案，所以我们 **不能压缩空间**，得保留每一步的方案。
**又** 由于输出字典序最小的，所以我们应该反着来，从 $n$ 到 1 求解最优解，那么 $dp[1][W]$ 就是最优的解。

```c++
for (int i = n; i >= 1; i--)
    for (int j = 0; j <= W; j++){
        dp[i][j] = dp[i + 1][j];
        if (j >= w[i])
            dp[i][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
    }
```

**接下来** 就是输出的问题，如何判断这个物品**被选中**，如果 $dp[i][k] = dp[i + 1][k - w[i]] + v[i]$，说明选择了第 $i$ 个物品是最优的选择方案。

```c++
for (int i = 1; i <= n; i++)
    if (W - w[i] >= 0 && dp[i][W] == dp[i + 1][W - w[i]] + v[i]){
        cout << i << " ";
        W -= w[i];
    }
```

### 数位 DP

```c++
/* pos 表示当前枚举到第几位
sum 表示 d 出现的次数
limit 为 1 表示枚举的数字有限制
zero 为 1 表示有前导 0
d 表示要计算出现次数的数 */
const int N = 15;
LL dp[N][N];
int num[N];
LL dfs(int pos, LL sum, int limit, int zero, int d) {
    if (pos == 0) return sum;
    if (!limit && !zero && dp[pos][sum] != -1) return dp[pos][sum];
    LL ans = 0;
    int up = (limit ? num[pos] : 9);
    for (int i = 0; i <= up; i++) {
        ans += dfs(pos - 1, sum + ((!zero || i) && (i == d)), limit && (i == num[pos]),
                   zero && (i == 0), d);
    }
    if (!limit && !zero) dp[pos][sum] = ans;
    return ans;
}
LL solve(LL x, int d) {
    memset(dp, -1, sizeof dp);
    int len = 0;
    while (x) {
        num[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, 0, 1, 1, d);
}
```

### 状压 DP

**题意：**在 $n * n$ 的棋盘里面放 $k$ 个国王，使他们互不攻击，共有多少种摆放方案。国王能攻击到它上下左右，以及左上左下右上右下八个方向上附近的各一个格子，共8个格子。

```c++
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int N = 15, M = 150, K = 1500;
LL n, k;
LL cnt[K];    //每个状态的二进制中 1 的数量
LL tot;    //合法状态的数量
LL st[K];    //合法的状态
LL dp[N][M][K];    //第 i 行，放置了 j 个国王，状态为 k 的方案数
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n >> k;
    for (int s = 0; s < (1 << n); s ++ ){  //找出合法状态
        LL sum = 0, t = s;
        while(t){  //计算 1 的数量
            sum += (t & 1);
            t >>= 1;
        }
        cnt[s] = sum;
        if ( (( (s << 1) | (s >> 1) ) & s) == 0 ){  //判断合法性
            st[ ++ tot] = s;
        }
    }
    dp[0][0][0] = 1;
    for (int i = 1; i <= n + 1; i ++ ){
        for (int j1 = 1; j1 <= tot; j1 ++ ){    //当前的状态
            LL s1 = st[j1];
            for (int j2 = 1; j2 <= tot; j2 ++ ){    //上一行的状态
                LL s2 = st[j2];
                if ( ( (s2 | (s2 << 1) | (s2 >> 1)) & s1 ) == 0 ){
                    for (int j = 0; j <= k; j ++ ){
                        if (j - cnt[s1] >= 0)
                            dp[i][j][s1] += dp[i - 1][j - cnt[s1]][s2];
                    }
                }
            }
        }
    }
    cout << dp[n + 1][k][0] << "\n";
    return 0;
}
```

### 常用例题

题意：在一篇文章（包含大小写英文字母、数字、和空白字符（制表/空格/回车））中寻找 ${\tt helloworld}$（任意一个字母的大小写都行）的子序列出现了多少次，输出结果对 $10^9+7$ 的余数。

字符串 DP ，构建一个二维 DP 数组，$dp[i][j]$ 的 $i$ 表示文章中的第几个字符，$j$ 表示寻找的字符串的第几个字符，当字符串中的字符和文章中的字符相同时，即找到符合条件的字符， `dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]` ，因为字符串中的每个字符不会对后面的结果产生影响，所以 DP 方程可以优化成一维的， 由于字符串中有重复的字符，所以比较时应该从后往前。

```c++
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const int mod = 1e9 + 7;
char c, s[20] = "!helloworld";
LL dp[20];
int main(){
    dp[0] = 1;
    while ((c = getchar()) != EOF)
        for (int i = 10; i >= 1; i--)
            if (c == s[i] || c == s[i] - 32)
                dp[i] = (dp[i] + dp[i - 1]) % mod;
    cout << dp[10] << "\n";
    return 0;
}
```

***

题意：（最长括号匹配）给一个只包含‘(’，‘)’，‘[’，‘]’的非空字符串，“()”和“[]”是匹配的，寻找字符串中最长的括号匹配的子串，若有两串长度相同，输出靠前的一串。

设给定的字符串为 $\tt{}s$ ，可以定义数组 $dp[i], dp[i]$ 表示以 $s[i]$ 结尾的字符串里最长的括号匹配的字符。显然，从 $i - dp[i] + 1$ 到 $i$ 的字符串是括号匹配的，当找到一个字符是‘)’或‘]’时，再去判断第 $i - 1 - dp[i - 1]$ 的字符和第 $i$ 位的字符是否匹配，如果是，那么 `dp[i] = dp[i - 1] + 2 + dp[i - 2 - dp[i - 1]]` 。

```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;
string s;
int len, dp[maxn], ans, id;
int main(){
    cin >> s;
    len = s.length();
    for (int i = 1; i < len; i++){
        if ((s[i] == ')' && s[i - 1 - dp[i - 1]] == '(' ) || (s[i] == ']' && s[i - 1 - dp[i - 1]] == '[')){
            dp[i] = dp[i - 1] + 2 + dp[i - 2 - dp[i - 1]];
            if (dp[i] > ans) {
                ans = dp[i];  //记录长度
                id = i;  //记录位置
            }
        }
    }
    for (int i = id - ans + 1; i <= id; i++)
        cout << s[i];
    cout << "\n";
    return 0;
}
```

***

题意：去掉区间内包含“4”和“62”的数字，输出剩余的数字个数

```c++
int T,n,m,len,a[20];//a数组用于判断每一位能取到的最大值
ll l,r,dp[20][15];
ll dfs(int pos,int pre,int limit){//记搜
    //pos搜到的位置，pre前一位数
    //limit判断是否有最高位限制
    if(pos>len) return 1;//剪枝
    if(dp[pos][pre]!=-1 && !limit) return dp[pos][pre];//记录当前值
    ll ret=0;//暂时记录当前方案数
    int res=limit?a[len-pos+1]:9;//res当前位能取到的最大值
    for(int i=0;i<=res;i++)
        if(!(i==4 || (pre==6 && i==2)))
            ret+=dfs(pos+1,i,i==res&&limit);
    if(!limit) dp[pos][pre]=ret;//当前状态方案数记录
    return ret;
}
ll part(ll x){//把数按位拆分
    len=0;
    while(x) a[++len]=x%10,x/=10;
    memset(dp,-1,sizeof dp);//初始化-1（因为有可能某些情况下的方案数是0）
    return dfs(1,0,1);//进入记搜
}
int main(){
    cin>>n;
    while(n--){
        cin>>l>>r;
        if(l==0 && r==0)break;
        if(l) printf("%lld\n",part(r)-part(l-1));//[l,r](l!=0)
        else printf("%lld\n",part(r)-part(l));//从0开始要特判
    }
}
```

<div style="page-break-after:always">/END/</div>

## Addition 串

### 子串与子序列

| 中文名称 |   常见英文名称    |                                  解释                                  |
| :------: | :---------------: | :--------------------------------------------------------------------: |
|   子串   |  $\tt substring$  |         连续的选择一段字符（可以全选、可以不选）组成的新字符串         |
|  子序列  | $\tt subsequence$ | 从左到右取出若干个字符（可以不取、可以全取、可以不连续）组成的新字符串 |

### 字符串模式匹配算法 KMP

> 应用：
> 
> 1. 在字符串中查找子串；
> 2. 最小周期：字符串长度-整个字符串的 $\tt border$ ；
> 3. 最小循环节：区别于周期，当字符串长度 $n \bmod (n - nxt[n]) = 0$ 时，等于最小周期，否则为 $n$ 。

以最坏 $\mathcal O(N+M)$ 的时间计算 $t$ 在 $s$ 中出现的全部位置。

```c++
auto kmp = [&](string s, string t) {
    int n = s.size(), m = t.size();
    vector<int> kmp(m + 1), ans;
    s = "@" + s;
    t = "@" + t;
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && t[i] != t[j + 1]) {
            j = kmp[j];
        }
        j += t[i] == t[j + 1];
        kmp[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && s[i] != t[j + 1]) {
            j = kmp[j];
        }
        if (s[i] == t[j + 1] && ++j == m) {
            ans.push_back(i - m + 1); // t 在 s 中出现的位置
        }
    }
    return ans;
};
```

### Z函数（扩展 KMP）

获取字符串 $s$ 和 $s[i,n-1]$ （即以 $s[i]$ 开头的后缀）的最长公共前缀（LCP）的长度，总复杂度 $\mathcal O(N)$。

```c++
vector<int> zFunction(string s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = max(0, min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}
```

### 最长公共子序列 LCS

求解两个串的最长公共子序列的长度。

#### 小数据解

针对 $10^3$ 以内的数据。

```c++
const int N = 1e3 + 10;
char a[N], b[N];
int n, m, f[N][N];
void solve(){
    cin >> n >> m >> a + 1 >> b + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++){
            f[i][j] = max(f[i - 1][j], f[i][j - 1]);
            if (a[i] == b[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
        }
    cout << f[n][m] << "\n";
}
int main(){
    solve();
    return 0;
}
```

#### 大数据解

针对 $10^5$ 以内的数据。

```c++
const int INF = 0x7fffffff;
int n, a[maxn], b[maxn], f[maxn], p[maxn];
int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        p[a[i]] = i;  //将第二个序列中的元素映射到第一个中
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        f[i] = INF;
    }
    int len = 0;
    f[0] = 0;
    for (int i = 1; i <= n; i++){
        if (p[b[i]] > f[len]) f[++len] = p[b[i]];
        else {
            int l = 0, r = len;
            while (l < r){
                int mid = (l + r) >> 1;
                if (f[mid] > p[b[i]]) r = mid;
                else l = mid + 1;
            }
            f[l] = min(f[l], p[b[i]]);
        }
    }
    cout << len << "\n";
    return 0;
}
```

### 字符串哈希

#### 双哈希封装

随机质数列表：1111111121、1211111123、1311111119。

```c++
const int N = 1 << 21;
static const int mod1 = 1E9 + 7, base1 = 127;
static const int mod2 = 1E9 + 9, base2 = 131;
using U = Zmod<mod1>;
using V = Zmod<mod2>;
vector<U> val1;
vector<V> val2;
void init(int n = N) {
    val1.resize(n + 1), val2.resize(n + 2);
    val1[0] = 1, val2[0] = 1;
    for (int i = 1; i <= n; i++) {
        val1[i] = val1[i - 1] * base1;
        val2[i] = val2[i - 1] * base2;
    }
}
struct String {
    vector<U> hash1;
    vector<V> hash2;
    string s;
    
    String(string s_) : s(s_), hash1{1}, hash2{1} {
        for (auto it : s) {
            hash1.push_back(hash1.back() * base1 + it);
            hash2.push_back(hash2.back() * base2 + it);
        }
    }
    pair<U, V> get() { // 输出整串的哈希值
        return {hash1.back(), hash2.back()};
    }
    pair<U, V> substring(int l, int r) { // 输出子串的哈希值
        if (l > r) swap(l, r);
        U ans1 = hash1[r + 1] - hash1[l] * val1[r - l + 1];
        V ans2 = hash2[r + 1] - hash2[l] * val2[r - l + 1];
        return {ans1, ans2};
    }
    pair<U, V> modify(int idx, char x) { // 修改 idx 位为 x
        int n = s.size() - 1;
        U ans1 = hash1.back() + val1[n - idx] * (x - s[idx]);
        V ans2 = hash2.back() + val2[n - idx] * (x - s[idx]);
        return {ans1, ans2};
    }
};
```

#### 前后缀去重

`sample please ease` 去重后得到 `samplease`。

```c++
string compress(vector<string> in) { // 前后缀压缩
    vector<U> hash1{1};
    vector<V> hash2{1};
    string ans = "#";
    for (auto s : in) {
        s = "#" + s;
        int st = 0;
        U chk1 = 0;
        V chk2 = 0;
        for (int j = 1; j < s.size() && j < ans.size(); j++) {
            chk1 = chk1 * base1 + s[j];
            chk2 = chk2 * base2 + s[j];
            if ((hash1.back() == hash1[ans.size() - 1 - j] * val1[j] + chk1) &&
                (hash2.back() == hash2[ans.size() - 1 - j] * val2[j] + chk2)) {
                st = j;
            }
        }
        for (int j = st + 1; j < s.size(); j++) {
            ans += s[j];
            hash1.push_back(hash1.back() * base1 + s[j]);
            hash2.push_back(hash2.back() * base2 + s[j]);
        }
    }
    return ans.substr(1);
}
```

### 马拉车

$\mathcal O(N)$ 时间求出字符串的最长回文子串。

```c++
string s;
cin >> s;
int n = s.length();
string t = "-#";
for (int i = 0; i < n; i++) {
    t += s[i];
    t += '#';
}
int m = t.length();
t += '+';
int mid = 0, r = 0;
vector<int> p(m);
for (int i = 1; i < m; i++) {
    p[i] = i < r ? min(p[2 * mid - i], r - i) : 1;
    while (t[i - p[i]] == t[i + p[i]]) p[i]++;
    if (i + p[i] > r) {
        r = i + p[i];
        mid = i;
    }
}
```

### 字典树 trie

#### 基础封装

```c++
struct Trie {
    int ch[N][63], cnt[N], idx = 0;
    map<char, int> mp;
    void init() {
        LL id = 0;
        for (char c = 'a'; c <= 'z'; c++) mp[c] = ++id;
        for (char c = 'A'; c <= 'Z'; c++) mp[c] = ++id;
        for (char c = '0'; c <= '9'; c++) mp[c] = ++id;
    }
    void insert(string s) {
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            if (!ch[u][v]) ch[u][v] = ++idx;
            u = ch[u][v];
            cnt[u]++;
        }
    }
    LL query(string s) {
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            int v = mp[s[i]];
            if (!ch[u][v]) return 0;
            u = ch[u][v];
        }
        return cnt[u];
    }
    void Clear() {
        for (int i = 0; i <= idx; i++) {
            cnt[i] = 0;
            for (int j = 0; j <= 62; j++) {
                ch[i][j] = 0;
            }
        }
        idx = 0;
    }
} trie;
```

#### 01 字典树

```c++
struct Trie {
    int n, idx;
    vector<vector<int>> ch;
    Trie(int n) {
        this->n = n;
        idx = 0;
        ch.resize(30 * (n + 1), vector<int>(2));
    }
    void insert(int x) {
        int u = 0;
        for (int i = 30; ~i; i--) {
            int &v = ch[u][x >> i & 1];
            if (!v) v = ++idx;
            u = v;
        }
    }
    int query(int x) {
        int u = 0, res = 0;
        for (int i = 30; ~i; i--) {
            int v = x >> i & 1;
            if (ch[u][!v]) {
                res += (1 << i);
                u = ch[u][!v];
            } else {
                u = ch[u][v];
            }
        }
        return res;
    }
};
```

### 后缀数组 SA

以 $\mathcal O(N)$ 的复杂度求解。

```c++
struct SuffixArray {
    int n;
    vector<int> sa, rk, lc;
    SuffixArray(const string &s) {
        n = s.length();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b) { return s[a] < s[b]; });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        }
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; ++i) {
                tmp.push_back(n - k + i);
            }
            for (auto i : sa) {
                if (i >= k) {
                    tmp.push_back(i - k);
                }
            }
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i) {
                ++cnt[rk[i]];
            }
            for (int i = 1; i < n; ++i) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; --i) {
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            }
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i) {
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n ||
                                             tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            }
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (rk[i] == 0) {
                j = 0;
                continue;
            }
            for (j -= j > 0;
                 i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j];) {
                ++j;
            }
            lc[rk[i] - 1] = j;
        }
    }
};
```

### AC 自动机

定义 $|s_i|$ 是模板串的长度，$|S|$ 是文本串的长度，$|\Sigma|$ 是字符集的大小（常数，一般为 $26$），时间复杂度为 $\mathcal O(\sum|s_i|+|S|)$ 。

```c++
// Trie+Kmp，多模式串匹配
struct ACAutomaton {
    static constexpr int N = 1e6 + 10;
    int ch[N][26], fail[N], cntNodes;
    int cnt[N];
    ACAutomaton() {
        cntNodes = 1;
    }
    void insert(string s) {
        int u = 1;
        for (auto c : s) {
            int &v = ch[u][c - 'a'];
            if (!v) v = ++cntNodes;
            u = v;
        }
        cnt[u]++;
    }
    void build() {
        fill(ch[0], ch[0] + 26, 1);
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                int &v = ch[u][i];
                if (!v)
                    v = ch[fail[u]][i];
                else {
                    fail[v] = ch[fail[u]][i];
                    q.push(v);
                }
            }
        }
    }
    LL query(string t) {
        LL ans = 0;
        int u = 1;
        for (auto c : t) {
            u = ch[u][c - 'a'];
            for (int v = u; v && ~cnt[v]; v = fail[v]) {
                ans += cnt[v];
                cnt[v] = -1;
            }
        }
        return ans;
    }
};
```

### 回文自动机 PAM（回文树）

> 应用：
> 
> 1. 本质不同的回文串个数：$idx - 2$ ；
> 2. 回文子串出现次数。

对于一个字符串 $s$，它的本质不同回文子串个数最多只有 $|s|$ 个，那么，构造 $s$ 的回文树的时间复杂度是 $\mathcal O(|s|)$ 。

```c++
struct PalindromeAutomaton {
    constexpr static int N = 5e5 + 10;
    int tr[N][26], fail[N], len[N];
    int cntNodes, last;
    int cnt[N];
    string s;
    PalindromeAutomaton(string s) {
        memset(tr, 0, sizeof tr);
        memset(fail, 0, sizeof fail);
        len[0] = 0, fail[0] = 1;
        len[1] = -1, fail[1] = 0;
        cntNodes = 1;
        last = 0;
        this->s = s;
    }
    void insert(char c, int i) {
        int u = get_fail(last, i);
        if (!tr[u][c - 'a']) {
            int v = ++cntNodes;
            fail[v] = tr[get_fail(fail[u], i)][c - 'a'];
            tr[u][c - 'a'] = v;
            len[v] = len[u] + 2;
            cnt[v] = cnt[fail[v]] + 1;
        }
        last = tr[u][c - 'a'];
    }
    int get_fail(int u, int i) {
        while (i - len[u] - 1 <= -1 || s[i - len[u] - 1] != s[i]) {
            u = fail[u];
        }
        return u;
    }
};
```

### 后缀自动机 SAM

定义 $|\Sigma|$ 是字符集的大小，复杂度为 $\mathcal O(N\log |\Sigma|)$ 。

```c++
// 有向无环图
struct SuffixAutomaton {
    static constexpr int N = 1e6;
    struct node {
        int len, link, nxt[26];
        int siz;
    } t[N << 1];
    int cntNodes;
    SuffixAutomaton() {
        cntNodes = 1;
        fill(t[0].nxt, t[0].nxt + 26, 1);
        t[0].len = -1;
    }
    int extend(int p, int c) {
        if (t[p].nxt[c]) {
            int q = t[p].nxt[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = ++cntNodes;
            t[r].siz = 0;
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            copy(t[q].nxt, t[q].nxt + 26, t[r].nxt);
            t[q].link = r;
            while (t[p].nxt[c] == q) {
                t[p].nxt[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = ++cntNodes;
        t[cur].len = t[p].len + 1;
        t[cur].siz = 1;
        while (!t[p].nxt[c]) {
            t[p].nxt[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
};
```

### 子序列自动机

对于给定的长度为 $n$ 的主串 $s$ ，以 $\mathcal O(n)$ 的时间复杂度预处理、$\mathcal O(m + \log \textrm{size:}s)$ 的复杂度判定长度为 $m$ 的询问串是否是主串的子序列。

#### 自动离散化、自动类型匹配封装

```c++
template<class T> struct SequenceAutomaton {
    vector<T> alls;
    vector<vector<int>> ver;

    SequenceAutomaton(auto in) {
        for (auto &i : in) {
            alls.push_back(i);
        }
        sort(alls.begin(), alls.end());
        alls.erase(unique(alls.begin(), alls.end()), alls.end());

        ver.resize(alls.size() + 1);
        for (int i = 0; i < in.size(); i++) {
            ver[get(in[i])].push_back(i + 1);
        }
    }
    bool count(T x) {
        return binary_search(alls.begin(), alls.end(), x);
    }
    int get(T x) {
        return lower_bound(alls.begin(), alls.end(), x) - alls.begin();
    }
    bool contains(auto in) {
        int at = 0;
        for (auto &i : in) {
            if (!count(i)) {
                return false;
            }

            auto j = get(i);
            auto it = lower_bound(ver[j].begin(), ver[j].end(), at + 1);
            if (it == ver[j].end()) {
                return false;
            }
            at = *it;
        }
        return true;
    }
};
```

#### 朴素封装

原时间复杂度中的 $\textrm{size:}s$ 需要手动设置。类型需要手动设置。

```c++
struct SequenceAutomaton {
    vector<vector<int>> ver;

    SequenceAutomaton(vector<int> &in, int size) : ver(size + 1) {
        for (int i = 0; i < in.size(); i++) {
            ver[in[i]].push_back(i + 1);
        }
    }
    bool contains(vector<int> &in) {
        int at = 0;
        for (auto &i : in) {
            auto it = lower_bound(ver[i].begin(), ver[i].end(), at + 1);
            if (it == ver[i].end()) {
                return false;
            }
            at = *it;
        }
        return true;
    }
};
```

<div style="page-break-after:always">/END/</div>
