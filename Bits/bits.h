// 反转二进制
int reversebit(int n) {
    n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
    n = ((n & 0xcccccccc) >> 1) | ((n & 0x33333333) << 1);
    n = ((n & 0xf0f0f0f0) >> 1) | ((n & 0x0f0f0f0f) << 1);
    n = ((n & 0xff00ff00) >> 1) | ((n & 0x00ff00ff) << 1);
    return n;
}

// 位图
