#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

using ll = long long;

struct Edge {
    int u, v;
    ll w;
};

struct DSU {
    vector<int> parent, sz;

    DSU(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
    }

    int find(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find(parent[v]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

// ---------------------------------------------------
// Kruskal IST function
// Returns: MST cost
// If no MST exists (graph disconnected) return -1
// ---------------------------------------------------
ll kruskal_mst(int n, vector<Edge> &edges) {

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b) { return a.w < b.w; });

    DSU dsu(n);
    ll cost = 0;
    int used = 0;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cost += e.w;
            used++;
        }
    }

    if (used != n - 1) return -1;  // no MST
    return cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {

        int n, m;
        cin >> n >> m;

        vector<Edge> edges(m);

        for (int i = 0; i < m; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        ll ans = kruskal_mst(n, edges);

        if (ans == -1) cout << "NO MST\n";
        else cout << ans << "\n";

        if (T) cout << "\n";
    }

    return 0;
}