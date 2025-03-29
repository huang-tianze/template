const int N = 1e3;
int pri[(N + 9) >> 1], now;
bool vis[N + 9];

void init() {
    for (int i = 2; i <= N; i++) {
        if (!vis[i])
            pri[++now] = i;
        for (int j = 1; j <= now && pri[j] * i <= N; j++) {
            vis[pri[j] * i] = 1;
            if (i % pri[j] == 0)
                break;
        }
    }
}
