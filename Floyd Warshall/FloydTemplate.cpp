#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;


// ---------------------------------------------------
// Floyd–Warshall (only dist[][]) — clean contest version
// ---------------------------------------------------
void floyd_warshall(vector<vector<ll>> &dist, int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;

        // Initialize matrix
        vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
        for (int i = 1; i <= n; i++) dist[i][i] = 0;

        // Read edges
        for (int i = 0; i < m; i++) {
            int u, v;
            ll w;
            cin >> u >> v >> w;

            dist[u][v] = min(dist[u][v], w); // directed
            // For undirected: dist[v][u] = min(dist[v][u], w);
        }

        // Run Floyd–Warshall
        floyd_warshall(dist, n);

        // Answer queries
        while (q--) {
            int u, v;
            cin >> u >> v;
            if (dist[u][v] >= INF / 2) cout << "NO PATH\n";
            else cout << dist[u][v] << "\n";
        }

        if (T) cout << "\n";  // blank line between cases (common in UVA)
    }

    return 0;
}