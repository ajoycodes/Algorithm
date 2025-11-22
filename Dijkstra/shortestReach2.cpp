#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 1e18;

vector<vector<pair<int,ll>>> g;
vector<ll> dist;


void dijkstra(int src) {
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d,u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;

        for (auto &e : g[u]) {
            int v = e.first;
            ll w = e.second;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        g.assign(n+1, {});
        dist.assign(n+1, INF);

        while (m--) {
            int u,v; ll w;
            cin >> u >> v >> w;
            g[u].push_back({v,w});
            g[v].push_back({u,w});
        }

        int src; cin >> src;
        dijkstra(src);

        for(int i=1;i<=n;i++) {
            if (i == src) continue;
            if (dist[i]==INF) cout<< "-1";
            else {
                cout << dist[i];
            }
            if (i!=n) cout << " ";
        }
        cout << endl;
    }
    return 0;

}