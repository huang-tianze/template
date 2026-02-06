#### Gray Code 格雷码 反射二进制码 循环二进制码
任意的相邻的两个格雷码只有一位不同
计算方式
`gray_code = m ^ (m>>1)`

Tips:
1. 如果将m的格雷码g再进行转换, 则得到的一系列g位于`[2^p , 2^(p+1)-1]`内, 即这是个循环
   其中`2^p < m < 2^(p+1)`

#### Xor 异或
1. $$
   \bigoplus_{i = 1}^{n} i = 
   \begin{cases}
      n & n\%4 = 0 \\
      1 & n\%4 = 1 \\
      n+1 & n\%4=2 \\
      0 & n\%4=3
   \end{cases}
   $$

#### 0-1 Matrix
1. 矩阵从0开始计数, 即从偶数行(列)开始
   要求
   - 每一行数字的和构成{0,1,2,3,··· ,n−1}的数字集合
   - 每一列数字的和构成{0,1,2,3,··· ,n−1}的数字集合
   - 数字连通块恰好有n个
   
   结果
   1. a_{i,j} = min(i,j).bit_and(1)
   2. 考虑偶数行从左向右排列n-i-1个1 奇数行全为0; 考虑奇数列从上到下为n-i个0, 然后为i个1
      将两个矩阵 点或 即可
      111110
      000000
      111010
      000010
      101010
      001010

#### gcd
1. $\forall n$, $\gcd(x,y)=n$, 同时`x^y`最小, 则$x,y$的一个可能的取值`(n << __bit_width(n))`,`(n << __bit_width(n) | n)`

#### mex
1. 对于集合$A = \{x: x \in [L,R]\}$
   记操作op: 从集合中任意选取至少一个元素, 计算这些元素的bit_and, 并将新元素加入集合
   则最终$mex(A)$由以下函数输出
   ```
   int solve(int L, int R) {
       int b1 = bit_width(L) ? bit_width(L) : -1;
       int b2 = bit_width(R) ? bit_width(R) : -1;
       if(b1 == -1) {
           return R + 1;
       } else if(b1 == b2) {
           return 0;
       } else if(b2 > (b1 + 1)) {
           return R + 1;
       } else {
           int ans = R - (1LL << b2) + 1;
           int l = 0; // L 能自己构造的下限
           for(int j = b1; j >= 0; j--) {
               if((L >> j & 1) == 0) {
                   break;
               } else {
                   l |= (1LL << j);
               }
           } 
           if(l <= ans) {
               ans = R + 1;
           }
           return ans;
       }
   }

   ```