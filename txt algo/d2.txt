#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <set>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

vector<vector<pair<int,ll>>> g;
vector<ll> dist;
vector<int> parent;

void dijkstra(int src) {
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    dist[src] = 0;
    parent.assign(dist.size(), -1);
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;

        for (auto &[v, w] : g[u]) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u; //Optimal path update
                pq.push({dist[v], v});
            }
        }
    }
}

//pathConstruction
vector<int> getPath(int dest) {
    vector<int> path;
    for(int cur = dest; cur != -1; cur = parent[cur])
        path.push_back(cur);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;

    g.assign(n+1, {});
    dist.assign(n+1, INF);

    while(m--) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    int src, dest;
    cin >> src >> dest;

    dijkstra(src);

    if(dist[dest] == INF) {
        cout << "No path\n";
        return 0;
    }

    cout << "Distance: " << dist[dest] << "\n";
    cout << "Path: ";

    vector<int> path = getPath(dest);
    for(int x : path) cout << x << " ";
}