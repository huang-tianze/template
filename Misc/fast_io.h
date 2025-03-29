#include <iostream>
using namespace std;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}

int read() {
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') { // ch 不是数字时
        if (ch == '-')
            w = -1;     // 判断是否为负
        ch = getchar(); // 继续读入
    }
    while (ch >= '0' && ch <= '9') { // ch 是数字时
        x = x * 10 + (ch - '0');     // 将新读入的数字「加」在 x 的后面
        // x 是 int 类型，char 类型的 ch 和 '0' 会被自动转为其对应的
        // ASCII 码，相当于将 ch 转化为对应数字
        // 此处也可以使用 (x<<3)+(x<<1) 的写法来代替 x*10
        ch = getchar(); // 继续读入
    }
    return x * w; // 数字 * 正负号 = 实际数值
}

void write(int x) {
    if (x < 0) { // 判负 + 输出负号 + 变原数为正数
        x = -x;
        putchar('-');
    }
    if (x > 9)
        write(x / 10);     // 递归，将除最后一位外的其他部分放到递归中输出
    putchar(x % 10 + '0'); // 已经输出（递归）完 x 末位前的所有数字，输出末位
}
