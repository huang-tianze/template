#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;
using Point = int; // 节点编号

struct Edge {
    int to;
    double cost;
};
using Graph = unordered_map<Point, vector<Edge>>;

struct Node {
    Point id;
    double g, h;
    Node *parent;
    Node(Point _id, double _g, double _h, Node *_parent = nullptr)
        : id(_id), g(_g), h(_h), parent(_parent) {}
    double f() const { return g + h; }
    bool operator>(const Node &other) const { return f() > other.f(); }
};

double heuristic(Point a, Point b) { return abs(a - b); } // 启发式函数（可修改）

vector<Point> a_star(const Graph &graph, Point start, Point goal) {
    priority_queue<Node, vector<Node>, greater<Node>> open_set;
    unordered_map<Point, double> g_score;
    unordered_map<Point, Node *> all_nodes;

    open_set.emplace(start, 0, heuristic(start, goal));
    g_score[start] = 0;
    all_nodes[start] = new Node(start, 0, heuristic(start, goal));

    while (!open_set.empty()) {
        Node *current = new Node(open_set.top());
        open_set.pop();
        if (current->id == goal) { // 找到目标，回溯路径
            vector<Point> path;
            while (current) {
                path.push_back(current->id);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (const auto &edge : graph.at(current->id)) { // 遍历邻接表
            double tentative_g = g_score[current->id] + edge.cost;
            if (!g_score.count(edge.to) || tentative_g < g_score[edge.to]) {
                g_score[edge.to] = tentative_g;
                Node *new_node = new Node(edge.to, tentative_g, heuristic(edge.to, goal), current);
                open_set.push(*new_node);
                all_nodes[edge.to] = new_node;
            }
        }
    }
    return {};
}

int main() {
    Graph graph = {
        {0, {{1, 1}, {2, 4}}},
        {1, {{2, 2}, {3, 5}}},
        {2, {{3, 1}}},
        {3, {}}};
    vector<Point> path = a_star(graph, 0, 3);
    for (Point p : path) cout << p << " -> ";
    cout << "Goal\n";
    return 0;
}