#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

vector<Edge> edges;
vector<long long> dist;
vector<int> parent;

// returns true if NO negative cycle reachable from src
bool bellmanFord(int n, int src) {
    dist.assign(n + 1, INF);
    parent.assign(n + 1, -1);
    dist[src] = 0;

    // Relax edges n-1 times
    for (int i = 1; i <= n - 1; i++) {
        bool changed = false;
        for (auto &e : edges) {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
                dist[e.v] = dist[e.u] + e.w;
                parent[e.v] = e.u;
                changed = true;
            }
        }
        if (!changed) break;
    }

    // Check for negative cycle reachable from src
    for (auto &e : edges) {
        if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.w) {
            return false; // negative cycle exists
        }
    }
    return true;
}

vector<int> getPath(int dest) {
    vector<int> path;
    if (dist[dest] == INF) return path; // empty means no path

    for (int cur = dest; cur != -1; cur = parent[cur])
        path.push_back(cur);

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    edges.clear();
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w}); // directed edge
    }

    int src, dest;
    cin >> src >> dest;

    bool ok = bellmanFord(n, src);

    if (ok) {
        cout << "NO" <<endl;;
        return 0;
    }else{
        cout<< "YES" <<endl;
        vector<int> path = getPath(dest);
        for (int x : path) cout << x << " ";
        cout << "\n";
    }

    return 0;
}