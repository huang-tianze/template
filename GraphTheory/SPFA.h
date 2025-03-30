#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

const int INF = 1e9;
const int MAX_NODES = 10005;

struct Edge {
    int to, weight;
};

vector<Edge> graph[MAX_NODES]; // 邻接表存储图
int dis[MAX_NODES];            // 记录最短距离
int visitCount[MAX_NODES];     // 记录节点被更新次数
bool inQueue[MAX_NODES];       // 标记节点是否在队列中

bool spfa(int startNode, int nodeCount) {
    queue<int> q;
    fill(dis, dis + nodeCount + 1, INF);
    memset(visitCount, 0, sizeof(visitCount));
    memset(inQueue, false, sizeof(inQueue));

    // 初始化起点
    dis[startNode] = 0;
    q.push(startNode);
    inQueue[startNode] = true;
    visitCount[startNode] = 1;

    while (!q.empty()) {
        int currentNode = q.front();
        q.pop();
        inQueue[currentNode] = false;

        for (auto edge : graph[currentNode]) {
            int nextNode = edge.to;
            int weight = edge.weight;

            // 松弛操作
            if (dis[nextNode] > dis[currentNode] + weight) {
                dis[nextNode] = dis[currentNode] + weight;
                visitCount[nextNode]++;

                // 负环检测
                if (visitCount[nextNode] > nodeCount) {
                    return false; // 发现负环
                }

                if (!inQueue[nextNode]) {
                    q.push(nextNode);
                    inQueue[nextNode] = true;
                }
            }
        }
    }
    return true; // 没有负环
}

int main() {
    int nodeCount, edgeCount, startNode;
    cin >> nodeCount >> edgeCount >> startNode;

    for (int i = 0; i < edgeCount; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
    }

    if (spfa(startNode, nodeCount)) {
        for (int i = 1; i <= nodeCount; i++) {
            if (dis[i] == INF)
                cout << "INF ";
            else
                cout << dis[i] << " ";
        }
    } else {
        cout << "Graph contains a negative weight cycle";
    }
    return 0;
}
