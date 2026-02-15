// 在O(N)内求1~N的逆元，即(i)^(-1) mod M;
// 要求M为质数
// 原理基于欧几里得除法 p = (p mod i) + floor(p/i)*i 两边乘inv[i]，最终得到递推
// inv[i] = (p-floor(p/i))* inv[p mod i] mod p
const int N = 1e5 + 5;
int inv[N];
int M = 1e9 + 7;

void pre() {
    inv[1] = 1;
    for (int i = 2; i <= N; ++i) {
        inv[i] = (M - M / i) * inv[M % i] % M;
    }
}
