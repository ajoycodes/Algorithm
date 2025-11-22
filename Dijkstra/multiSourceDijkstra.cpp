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

void multisource_dijkstra(vector<int> &sources) {
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;

    // Initialize all distances as INF
    int n = dist.size() - 1;
    for(int i = 1; i <= n; i++) dist[i] = INF;

    // Push all sources with dist = 0
    for(int s : sources) {
        dist[s] = 0;
        pq.push({0, s});
    }

    // Dijkstra
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;

        for(auto &[v, w] : g[u]) {
            if(dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    g.assign(n+1, {});
    dist.assign(n+1, INF);

    while(m--) {
        int u, v; ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    int k;
    cin >> k;

    vector<int> sources(k);
    for(int i = 0; i < k; i++)
        cin >> sources[i];   // multiple start points

    multisource_dijkstra(sources);

    // output distances
    for(int i = 1; i <= n; i++) {
        if(dist[i] == INF) cout << "-1 ";
        else cout << dist[i] << " ";
    }

    return 0;
}