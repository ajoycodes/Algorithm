#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;

struct Link {
    int from;
    int to;
    long long wt;
};

const long long o = 9e18;

pair<long long, vector<Link>> em(int n, int rt, const vector<Link> &edges) {
    long long totalcst = 0;
    vector<Link> fEdge;

    int N = n;
    int root = rt;
    vector<Link> cur = edges;

    while (true) {
        vector<long long> minIn(N, o);
        vector<int> par(N, -1);

        for (int i = 0; i < (int)cur.size(); i++) {
            int u = cur[i].from;
            int v = cur[i].to;
            long long w = cur[i].wt;
            if (u != v && w < minIn[v]) {
                minIn[v] = w;
                par[v] = u;
            }
        }

        minIn[root] = 0;

        for (int i = 0; i < N; i++) {
            if (minIn[i] == o) return make_pair(o, vector<Link>());
        }

        for (int i = 0; i < N; i++) totalcst += minIn[i];

        vector<int> vis(N, -1), comp(N, -1);
        int compCnt = 0;

        for (int i = 0; i < N; i++) {
            int v = i;
            while (v != root && comp[v] == -1 && vis[v] != i) {
                vis[v] = i;
                v = par[v];
            }
            if (v != root && comp[v] == -1) {
                comp[v] = compCnt;
                int u = par[v];
                while (u != v) {
                    comp[u] = compCnt;
                    u = par[u];
                }
                compCnt++;
            }
        }

        if (compCnt == 0) {
            for (int i = 0; i < N; i++) {
                if (i != root) fEdge.push_back({par[i], i, minIn[i]});
            }
            return make_pair(totalcst, fEdge);
        }

        for (int i = 0; i < N; i++) {
            if (comp[i] == -1) comp[i] = compCnt++;
        }

        vector<Link> nxt;
        nxt.reserve(cur.size());

        for (int i = 0; i < (int)cur.size(); i++) {
            int uo = cur[i].from;
            int vo = cur[i].to;
            long long wo = cur[i].wt;
            int un = comp[uo];
            int vn = comp[vo];
            long long wn = wo;
            if (un != vn) wn -= minIn[vo];
            if (un != vn) nxt.push_back({un, vn, wn});
        }

        root = comp[root];
        N = compCnt;
        cur = nxt;
    }
}

int getId(const string &s, map<string,int> &mp, vector<string> &names, int &cnt) {
    if (mp.find(s) == mp.end()) {
        mp[s] = cnt;
        names.push_back(s);
        cnt++;
    }
    return mp[s];
}

int main() {
    int n, m;
    cin >> n >> m;

    string rtName;
    cin >> rtName;

    map<string,int> mp;
    vector<string> names;
    int idCnt = 0;

    int rt = getId(rtName, mp, names, idCnt);

    vector<Link> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        string a, b;
        long long w;
        cin >> a >> b >> w;
        int u = getId(a, mp, names, idCnt);
        int v = getId(b, mp, names, idCnt);
        edges.push_back({u, v, w});
    }

    auto res = em(n, rt, edges);

    cout << "Root: " << rtName << "\n";

    if (res.first >= o / 2) {
        cout << "No directed spanning arborescence exists (some nodes are unreachable).\n";
        return 0;
    }

    cout << "Edges:\n";
    for (int i = 0; i < (int)res.second.size(); i++) {
        Link e = res.second[i];
        cout << names[e.from] << " " << names[e.to] << " " << e.wt << "\n";
    }

    cout << "Total Cost: " << res.first << "\n";
    return 0;
}